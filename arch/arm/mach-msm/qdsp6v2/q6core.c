/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <mach/msm_smd.h>
#include <mach/qdsp6v2/apr.h>

struct dentry *dentry;
struct apr_svc_ch_dev *handle;
struct apr_svc *apr_handle_q;
struct apr_svc *apr_handle_m;
struct apr_svc *core_handle_q;
struct apr_client_data clnt_data;
char l_buf[4096];

#define TIMEOUT_MS 1000
int32_t query_adsp_ver;
wait_queue_head_t adsp_version_wait;
uint32_t adsp_version;

static int32_t aprv2_core_fn_q(struct apr_client_data *data, void *priv)
{
	struct adsp_get_version *payload;
	uint32_t *payload1;
	struct adsp_service_info *svc_info;
	int i;

	pr_aud_info("core msg: payload len = %d\n", data->payload_size);
	switch (data->opcode) {
	case APR_BASIC_RSP_RESULT:{
		payload1 = data->payload;
		if (payload1[0] == ADSP_CMD_SET_POWER_COLLAPSE_STATE) {
			pr_aud_info("Cmd[0x%x] status[0x%x]\n", payload1[0],
							payload1[1]);
			break;
		} else
			pr_aud_err("Invalid cmd rsp[0x%x][0x%x]\n", payload1[0],
								payload1[1]);
		break;
	}
	case ADSP_GET_VERSION_RSP:{
		if (data->payload_size) {
			payload = data->payload;
			if (query_adsp_ver == 1) {
				query_adsp_ver = 0;
				adsp_version  = payload->build_id;
				wake_up(&adsp_version_wait);
			}
			svc_info = (struct adsp_service_info *)
			((char *)payload + sizeof(struct adsp_get_version));
			pr_aud_info("----------------------------------------\n");
			pr_aud_info("Build id          = %x\n", payload->build_id);
			pr_aud_info("Number of services= %x\n", payload->svc_cnt);
			pr_aud_info("----------------------------------------\n");
			for (i = 0; i < payload->svc_cnt; i++) {
				pr_aud_info("svc-id[%d]\tver[%x.%x]\n",
					svc_info[i].svc_id,
					(svc_info[i].svc_ver & 0xFFFF0000) >> 16,
					(svc_info[i].svc_ver & 0xFFFF));
			}
			pr_aud_info("-----------------------------------------\n");
		} else
			pr_aud_info("zero payload for ADSP_GET_VERSION_RSP\n");
		break;
	}
	case RESET_EVENTS:{
		pr_debug("Reset event received in Core service");
		apr_reset(core_handle_q);
		core_handle_q = NULL;
		break;
	}

	default:
		pr_aud_err("Message id from adsp core svc: %d\n", data->opcode);
		break;
	}

	return 0;
}

static int32_t aprv2_debug_fn_q(struct apr_client_data *data, void *priv)
{
	pr_debug("Q6_Payload Length = %d\n", data->payload_size);
	if (memcmp(data->payload, l_buf + 20, data->payload_size))
		pr_aud_info("FAIL: %d\n", data->payload_size);
	else
		pr_aud_info("SUCCESS: %d\n", data->payload_size);
	return 0;
}

static int32_t aprv2_debug_fn_m(struct apr_client_data *data, void *priv)
{
	pr_aud_info("M_Payload Length = %d\n", data->payload_size);
	return 0;
}

static ssize_t apr_debug_open(struct inode *inode, struct file *file)
{
	file->private_data = inode->i_private;
	pr_debug("apr debugfs opened\n");
	return 0;
}

void *core_open(void)
{
	if (core_handle_q == NULL) {
		core_handle_q = apr_register("ADSP", "CORE",
					aprv2_core_fn_q, 0xFFFFFFFF, NULL);
	}
	pr_aud_info("Open_q %p\n", core_handle_q);
	if (core_handle_q == NULL) {
		pr_aud_err("%s: Unable to register CORE\n", __func__);
		return NULL;
	}
	return core_handle_q;
}
EXPORT_SYMBOL(core_open);

int32_t core_close(void)
{
	int ret = 0;
	if (core_handle_q == NULL) {
		pr_aud_err("CORE is already closed\n");
		ret = -EINVAL;
		return ret;
	}
	apr_deregister(core_handle_q);
	return ret;
}
EXPORT_SYMBOL(core_close);

uint32_t core_get_adsp_version(void)
{
	struct apr_hdr *hdr;
	int32_t rc = 0, ret = 0;
	core_open();
	if (core_handle_q) {
		hdr = (struct apr_hdr *)l_buf;
		hdr->hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_EVENT,
					APR_HDR_LEN(APR_HDR_SIZE), APR_PKT_VER);
		hdr->pkt_size = APR_PKT_SIZE(APR_HDR_SIZE, 0);
		hdr->src_port = 0;
		hdr->dest_port = 0;
		hdr->token = 0;
		hdr->opcode = ADSP_GET_VERSION;

		apr_send_pkt(core_handle_q, (uint32_t *)l_buf);
		query_adsp_ver = 1;
		pr_aud_info("Write_q\n");
		ret = wait_event_timeout(adsp_version_wait,
					(query_adsp_ver == 0),
					msecs_to_jiffies(TIMEOUT_MS));
		rc = adsp_version;
		if (!ret) {
			pr_aud_err("%s: wait_event timeout\n", __func__);
			rc = -ENODEV;
		}
	} else
		pr_aud_info("apr registration failed\n");
	return rc;
}
EXPORT_SYMBOL(core_get_adsp_version);

static ssize_t apr_debug_write(struct file *file, const char __user *buf,
				size_t count, loff_t *ppos)
{
	int len;
	static int t_len;

	if (count < 0)
		return 0;
	len = count > 63 ? 63 : count;
	if (copy_from_user(l_buf + 20 , buf, len)) {
		pr_aud_info("Unable to copy data from user space\n");
		return -EFAULT;
	}
	l_buf[len + 20] = 0;
	if (l_buf[len + 20 - 1] == '\n') {
		l_buf[len + 20 - 1] = 0;
		len--;
	}
	if (!strncmp(l_buf + 20, "open_q", 64)) {
		apr_handle_q = apr_register("ADSP", "TEST", aprv2_debug_fn_q,
							0xFFFFFFFF, NULL);
		pr_aud_info("Open_q %p\n", apr_handle_q);
	} else if (!strncmp(l_buf + 20, "open_m", 64)) {
		apr_handle_m = apr_register("MODEM", "TEST", aprv2_debug_fn_m,
							0xFFFFFFFF, NULL);
		pr_aud_info("Open_m %p\n", apr_handle_m);
	} else if (!strncmp(l_buf + 20, "write_q", 64)) {
		struct apr_hdr *hdr;

		t_len++;
		t_len = t_len % 450;
		if (!t_len % 99)
			msleep(2000);
		hdr = (struct apr_hdr *)l_buf;
		hdr->hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_EVENT,
					APR_HDR_LEN(20), APR_PKT_VER);
		hdr->pkt_size = APR_PKT_SIZE(20, t_len);
		hdr->src_port = 0;
		hdr->dest_port = 0;
		hdr->token = 0;
		hdr->opcode = 0x12345678;
		memset(l_buf + 20, 9, 4060);

		apr_send_pkt(apr_handle_q, (uint32_t *)l_buf);
		pr_debug("Write_q\n");
	} else if (!strncmp(l_buf + 20, "write_m", 64)) {
		struct apr_hdr *hdr;

		hdr = (struct apr_hdr *)l_buf;
		hdr->hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_EVENT,
					APR_HDR_LEN(20), APR_PKT_VER);
		hdr->pkt_size = APR_PKT_SIZE(20, 8);
		hdr->src_port = 0;
		hdr->dest_port = 0;
		hdr->token = 0;
		hdr->opcode = 0x12345678;
		memset(l_buf + 30, 9, 4060);

		apr_send_pkt(apr_handle_m, (uint32_t *)l_buf);
		pr_aud_info("Write_m\n");
	} else if (!strncmp(l_buf + 20, "write_q4", 64)) {
		struct apr_hdr *hdr;

		hdr = (struct apr_hdr *)l_buf;
		hdr->hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_EVENT,
					APR_HDR_LEN(20), APR_PKT_VER);
		hdr->pkt_size = APR_PKT_SIZE(20, 4076);
		hdr->src_port = 0;
		hdr->dest_port = 0;
		hdr->token = 0;
		hdr->opcode = 0x12345678;
		memset(l_buf + 30, 9, 4060);

		apr_send_pkt(apr_handle_q, (uint32_t *)l_buf);
		pr_aud_info("Write_q\n");
	} else if (!strncmp(l_buf + 20, "write_m4", 64)) {
		struct apr_hdr *hdr;

		hdr = (struct apr_hdr *)l_buf;
		hdr->hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_EVENT,
					APR_HDR_LEN(20), APR_PKT_VER);
		hdr->pkt_size = APR_PKT_SIZE(20, 4076);
		hdr->src_port = 0;
		hdr->dest_port = 0;
		hdr->token = 0;
		hdr->opcode = 0x12345678;
		memset(l_buf + 30, 9, 4060);

		apr_send_pkt(apr_handle_m, (uint32_t *)l_buf);
		pr_aud_info("Write_m\n");
	} else if (!strncmp(l_buf + 20, "close", 64)) {
		if (apr_handle_q)
			apr_deregister(apr_handle_q);
	} else if (!strncmp(l_buf + 20, "loaded", 64)) {
		change_q6_state(APR_Q6_LOADED);
	} else if (!strncmp(l_buf + 20, "boom", 64)) {
		q6audio_dsp_not_responding();
	} else if (!strncmp(l_buf + 20, "dsp_ver", 64)) {
			core_get_adsp_version();
	} else if (!strncmp(l_buf + 20, "en_pwr_col", 64)) {
		struct adsp_power_collapse pc;

		core_handle_q = core_open();
		if (core_handle_q) {
			pc.hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_EVENT,
					APR_HDR_LEN(APR_HDR_SIZE), APR_PKT_VER);
			pc.hdr.pkt_size = APR_PKT_SIZE(APR_HDR_SIZE,
						sizeof(uint32_t));;
			pc.hdr.src_port = 0;
			pc.hdr.dest_port = 0;
			pc.hdr.token = 0;
			pc.hdr.opcode = ADSP_CMD_SET_POWER_COLLAPSE_STATE;
			pc.power_collapse = 0x00000000;
			apr_send_pkt(core_handle_q, (uint32_t *)&pc);
			pr_aud_info("Write_q :enable power collapse\n");
		}
	} else if (!strncmp(l_buf + 20, "dis_pwr_col", 64)) {
		struct adsp_power_collapse pc;

		core_handle_q = core_open();
		if (core_handle_q) {
			pc.hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_EVENT,
					APR_HDR_LEN(APR_HDR_SIZE), APR_PKT_VER);
			pc.hdr.pkt_size = APR_PKT_SIZE(APR_HDR_SIZE,
							sizeof(uint32_t));
			pc.hdr.src_port = 0;
			pc.hdr.dest_port = 0;
			pc.hdr.token = 0;
			pc.hdr.opcode = ADSP_CMD_SET_POWER_COLLAPSE_STATE;
			pc.power_collapse = 0x00000001;
			apr_send_pkt(core_handle_q, (uint32_t *)&pc);
			pr_aud_info("Write_q:disable power collapse\n");
		}
	} else
		pr_aud_info("Unknown Command\n");

	return count;
}

static const struct file_operations apr_debug_fops = {
	.write = apr_debug_write,
	.open = apr_debug_open,
};

static int __init core_init(void)
{
#ifdef CONFIG_DEBUG_FS
	dentry = debugfs_create_file("apr", 0644,
				NULL, (void *) NULL, &apr_debug_fops);
#endif /* CONFIG_DEBUG_FS */
	query_adsp_ver = 0;
	init_waitqueue_head(&adsp_version_wait);
	adsp_version = 0;
	core_handle_q = NULL;
	return 0;
}
device_initcall(core_init);

