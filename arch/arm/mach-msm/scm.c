/* Copyright (c) 2010, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <linux/slab.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/errno.h>
#include <linux/err.h>

#include <asm/cacheflush.h>

#include <mach/scm.h>

static int simlock_mask = 0;
static int unlock_mask = 0;
static char *simlock_code = "";
static int security_level = 0;

module_param_named(simlock_code, simlock_code, charp, S_IRUGO | S_IWUSR | S_IWGRP);

#define SCM_ENOMEM		-5
#define SCM_EOPNOTSUPP		-4
#define SCM_EINVAL_ADDR		-3
#define SCM_EINVAL_ARG		-2
#define SCM_ERROR		-1
#define SCM_INTERRUPTED		1

static DEFINE_MUTEX(scm_lock);

/**
 * struct scm_command - one SCM command buffer
 * @len: total available memory for command and response
 * @buf_offset: start of command buffer
 * @resp_hdr_offset: start of response buffer
 * @id: command to be executed
 *
 * An SCM command is layed out in memory as follows:
 *
 *	------------------- <--- struct scm_command
 *	| command header  |
 *	------------------- <--- scm_get_command_buffer()
 *	| command buffer  |
 *	------------------- <--- struct scm_response and
 *	| response header |      scm_command_to_response()
 *	------------------- <--- scm_get_response_buffer()
 *	| response buffer |
 *	-------------------
 *
 * There can be arbitrary padding between the headers and buffers so
 * you should always use the appropriate scm_get_*_buffer() routines
 * to access the buffers in a safe manner.
 */
struct scm_command {
	u32	len;
	u32	buf_offset;
	u32	resp_hdr_offset;
	u32	id;
};

/**
 * struct scm_response - one SCM response buffer
 * @len: total available memory for response
 * @buf_offset: start of response data relative to start of scm_response
 * @is_complete: indicates if the command has finished processing
 */
struct scm_response {
	u32	len;
	u32	buf_offset;
	u32	is_complete;
};

struct oem_simlock_unlock_req {
	u32	unlock;
	void *code;
};

struct oem_log_oper_req {
	u32	address;
	u32	size;
	u32	buf_addr;
	u32	buf_len;
	int	revert;
};

/**
 * alloc_scm_command() - Allocate an SCM command
 * @cmd_size - size of the command buffer
 * @resp_size - size of the response buffer
 *
 * Allocate an SCM command, including enough room for the command
 * and response headers as well as the command and response buffers.
 *
 * Returns a valid &scm_command on success or %NULL if the allocation fails.
 */
static struct scm_command *alloc_scm_command(size_t cmd_size, size_t resp_size)
{
	struct scm_command *cmd;
	size_t len = sizeof(*cmd) + sizeof(struct scm_response) + cmd_size +
		resp_size;

	cmd = kzalloc(len, GFP_KERNEL);
	if (cmd) {
		cmd->len = len;
		cmd->buf_offset = sizeof(*cmd);
		cmd->resp_hdr_offset = cmd->buf_offset + cmd_size;
	}
	return cmd;
}

/**
 * kfree_scm_command() - Free an SCM command
 * @cmd - command to free
 *
 * Free an SCM command.
 */
static void kfree_scm_command(const struct scm_command *cmd)
{
	kfree(cmd);
}

/**
 * scm_command_to_response() - Get a pointer to a scm_response
 * @cmd - command
 *
 * Returns a pointer to a response for a command.
 */
static inline struct scm_response *scm_command_to_response(
		const struct scm_command *cmd)
{
	return (void *)cmd + cmd->resp_hdr_offset;
}

/**
 * scm_get_command_buffer() - Get a pointer to a command buffer
 * @cmd - command
 *
 * Returns a pointer to the command buffer of a command.
 */
static inline void *scm_get_command_buffer(const struct scm_command *cmd)
{
	return (void *)cmd + cmd->buf_offset;
}

/**
 * scm_get_response_buffer() - Get a pointer to a response buffer
 * @rsp - response
 *
 * Returns a pointer to a response buffer of a response.
 */
static inline void *scm_get_response_buffer(const struct scm_response *rsp)
{
	return (void *)rsp + rsp->buf_offset;
}

static int scm_remap_error(int err)
{
	switch (err) {
	case SCM_ERROR:
		return -EIO;
	case SCM_EINVAL_ADDR:
	case SCM_EINVAL_ARG:
		return -EINVAL;
	case SCM_EOPNOTSUPP:
		return -EOPNOTSUPP;
	case SCM_ENOMEM:
		return -ENOMEM;
	}
	return -EINVAL;
}

static u32 smc(u32 cmd_addr)
{
	int context_id;
	register u32 r0 asm("r0") = 1;
	register u32 r1 asm("r1") = (u32)&context_id;
	register u32 r2 asm("r2") = cmd_addr;
	asm(
		__asmeq("%0", "r0")
		__asmeq("%1", "r0")
		__asmeq("%2", "r1")
		__asmeq("%3", "r2")
		".arch_extension sec\n"
		"1:smc	#0	@ switch to secure world\n"
		"cmp	r0, #1				\n"
		"beq	1b				\n"
		: "=r" (r0)
		: "r" (r0), "r" (r1), "r" (r2)
		: "r3", "cc");
	return r0;
}

static int __scm_call(const struct scm_command *cmd)
{
	int ret;
	u32 cmd_addr = virt_to_phys(cmd);

	/*
	 * Flush the entire cache here so callers don't have to remember
	 * to flush the cache when passing physical addresses to the secure
	 * side in the buffer.
	 */
	flush_cache_all();
	do {
		ret = smc(cmd_addr);
		if (ret < 0) {
			pr_info("smc ret = %d (%x)\n", ret, ret);
			ret = scm_remap_error(ret);
			pr_info("smc remaped ret = %d (%x)\n", ret, ret);
			break;
		}
	} while (ret == SCM_INTERRUPTED);

	return ret;
}

/**
 * scm_call() - Send an SCM command
 * @svc_id - service identifier
 * @cmd_id - command identifier
 * @cmd_buf - command buffer
 * @cmd_len - length of the command buffer
 * @resp_buf - response buffer
 * @resp_len - length of the response buffer
 *
 * Sends a command to the SCM and waits for the command to finish processing.
 */
int scm_call(u32 svc_id, u32 cmd_id, const void *cmd_buf, size_t cmd_len,
		void *resp_buf, size_t resp_len)
{
	int ret;
	struct scm_command *cmd;
	struct scm_response *rsp;

	cmd = alloc_scm_command(cmd_len, resp_len);
	if (!cmd)
		return -ENOMEM;

	cmd->id = (svc_id << 10) | cmd_id;
	if (cmd_buf)
		memcpy(scm_get_command_buffer(cmd), cmd_buf, cmd_len);

	mutex_lock(&scm_lock);
	ret = __scm_call(cmd);
	mutex_unlock(&scm_lock);
	if (ret)
		goto out;

	rsp = scm_command_to_response(cmd);
	do {
		dmac_inv_range((void *)rsp,
				scm_get_response_buffer(rsp) + resp_len);
	} while (!rsp->is_complete);

	if (resp_buf)
		memcpy(resp_buf, scm_get_response_buffer(rsp), resp_len);
out:
	kfree_scm_command(cmd);
	return ret;
}
EXPORT_SYMBOL(scm_call);

u32 scm_get_version(void)
{
	int context_id;
	static u32 version = -1;
	register u32 r0 asm("r0") = 0x1 << 8;
	register u32 r1 asm("r1") = (u32)&context_id;

	if (version != -1)
		return version;

	mutex_lock(&scm_lock);
	asm(
		__asmeq("%0", "r1")
		__asmeq("%1", "r0")
		__asmeq("%2", "r1")
		".arch_extension sec\n"
		"1:smc	#0	@ switch to secure world\n"
		"cmp	r0, #1				\n"
		"beq	1b				\n"
		: "=r" (r1)
		: "r" (r0), "r" (r1)
		: "r2", "r3", "cc");
	version = r1;
	mutex_unlock(&scm_lock);

	return version;
}
EXPORT_SYMBOL(scm_get_version);

int secure_read_simlock_mask(void)
{
	int ret;
	u32 dummy;

	ret = scm_call(SCM_SVC_OEM, TZ_HTC_SVC_READ_SIMLOCK_MASK,
			&dummy, sizeof(dummy), NULL, 0);

	pr_info("TZ_HTC_SVC_READ_SIMLOCK_MASK ret = %d\n", ret);
	if (ret > 0)
		ret &= 0x1F;
	pr_info("TZ_HTC_SVC_READ_SIMLOCK_MASK modified ret = %d\n", ret);

	return ret;
}
EXPORT_SYMBOL(secure_read_simlock_mask);

int secure_simlock_unlock(unsigned int unlock, unsigned char *code)
{
	int ret;
	struct oem_simlock_unlock_req req;

	req.unlock = unlock;
	req.code = (void *)virt_to_phys(code);

	ret = scm_call(SCM_SVC_OEM, TZ_HTC_SVC_SIMLOCK_UNLOCK,
			&req, sizeof(req), NULL, 0);

	pr_info("TZ_HTC_SVC_SIMLOCK_UNLOCK ret = %d\n", ret);
	return ret;
}
EXPORT_SYMBOL(secure_simlock_unlock);

int secure_get_security_level(void)
{
	int ret;
	u32 dummy;

	ret = scm_call(SCM_SVC_OEM, TZ_HTC_SVC_GET_SECURITY_LEVEL,
			&dummy, sizeof(dummy), NULL, 0);

	pr_info("TZ_HTC_SVC_GET_SECURITY_LEVEL ret = %d\n", ret);
	if (ret > 0)
		ret &= 0x0F;
	pr_info("TZ_HTC_SVC_GET_SECURITY_LEVEL modified ret = %d\n", ret);

	return ret;
}
EXPORT_SYMBOL(secure_get_security_level);

int secure_memprot(void)
{
	int ret;
	u32 dummy;

	ret = scm_call(SCM_SVC_OEM, TZ_HTC_SVC_MEMPROT,
			&dummy, sizeof(dummy), NULL, 0);

	pr_info("TZ_HTC_SVC_MEMPROT ret = %d\n", ret);
	return ret;
}
EXPORT_SYMBOL(secure_memprot);

int secure_log_operation(unsigned int address, unsigned int size,
		unsigned int buf_addr, unsigned buf_len, int revert)
{
	int ret;
	struct oem_log_oper_req req;
	req.address = address;
	req.size = size;
	req.buf_addr = buf_addr;
	req.buf_len = buf_len;
	req.revert = revert;
	ret = scm_call(SCM_SVC_OEM, TZ_HTC_SVC_LOG_OPERATOR,
			&req, sizeof(req), NULL, 0);
	pr_info("TZ_HTC_SVC_LOG_OPERATOR ret = %d\n", ret);
	return ret;
}
EXPORT_SYMBOL(secure_log_operation);

static int __init scm_init(void)
{
	u32 version = scm_get_version();
	pr_info("SCM Remote Version %d.%d\n", version >> 16, version & 0xFF);
	return 0;
}
arch_initcall(scm_init);

static int lock_set_func(const char *val, struct kernel_param *kp)
{
	int ret;

	printk(KERN_INFO "%s started(%d)...\n", __func__, strlen(val));
	ret = param_set_int(val, kp);
	printk(KERN_INFO "%s finished(%d): %d...\n", __func__, ret, simlock_mask);

	return ret;
}

static int lock_get_func(char *val, struct kernel_param *kp)
{
	int ret;

	simlock_mask = secure_read_simlock_mask();
	ret = param_get_int(val, kp);
	printk(KERN_INFO "%s: %d, %d(%x)...\n", __func__, ret, simlock_mask, simlock_mask);

	return ret;
}

static int unlock_set_func(const char *val, struct kernel_param *kp)
{
	int ret, ret2;
	static unsigned char scode[17];

	printk(KERN_INFO "%s started(%d)...\n", __func__, strlen(val));
	ret = param_set_int(val, kp);
	ret2 = strlen(simlock_code);
	strcpy(scode, simlock_code);
	scode[ret2 - 1] = 0;
	printk(KERN_INFO "%s finished(%d): %d, '%s'...\n", __func__, ret, unlock_mask, scode);
	ret2 = secure_simlock_unlock(unlock_mask, scode);
	printk(KERN_INFO "secure_simlock_unlock ret %d...\n", ret2);

	return ret;
}

static int unlock_get_func(char *val, struct kernel_param *kp)
{
	int ret;

	ret = param_get_int(val, kp);
	printk(KERN_INFO "%s: %d, %d(%x)...\n", __func__, ret, unlock_mask, unlock_mask);

	return ret;
}

static int level_set_func(const char *val, struct kernel_param *kp)
{
	int ret;

	printk(KERN_INFO "%s started(%d)...\n", __func__, strlen(val));
	ret = param_set_int(val, kp);
	printk(KERN_INFO "%s finished(%d): %d...\n", __func__, ret, security_level);

	return ret;
}

static int level_get_func(char *val, struct kernel_param *kp)
{
	int ret;

	security_level = secure_get_security_level();
	ret = param_get_int(val, kp);
	printk(KERN_INFO "%s: %d, %d(%x)...\n", __func__, ret, security_level, security_level);

	return ret;
}

module_param_call(simlock_mask, lock_set_func, lock_get_func, &simlock_mask, S_IRUGO | S_IWUSR | S_IWGRP);
module_param_call(unlock_mask, unlock_set_func, unlock_get_func, &unlock_mask, S_IRUGO | S_IWUSR | S_IWGRP);
module_param_call(security_level, level_set_func, level_get_func, &security_level, S_IRUGO | S_IWUSR | S_IWGRP);
