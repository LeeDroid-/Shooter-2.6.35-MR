/* include/asm-arm/arch-msm/usbdiag.h
 *
 * Copyright (c) 2008-2010, Code Aurora Forum. All rights reserved.
 *
 * All source code in this file is licensed under the following license except
 * where indicated.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can find it at http://www.fsf.org
 */

#ifndef _DRIVERS_USB_DIAG_H_
#define _DRIVERS_USB_DIAG_H_

/*-------------------------------------------------------------------------*/


/*DRIVER_DIAG_FUNCTION*/
#define DIAG_ERR(fmt, args...) \
	printk(KERN_ERR "[USBDIAG:ERR] " fmt, ## args)
#define DIAG_WARNING(fmt, args...) \
	printk(KERN_WARNING "[USBDIAG] " fmt, ## args)
#define DIAG_INFO(fmt, args...) \
	printk(KERN_INFO "[USBDIAG] " fmt, ## args)
#define DIAG_DBUG(fmt, args...) \
	printk(KERN_DEBUG "[USBDIAG] " fmt, ## args)

/*DRIVER_DIAGFWD_FUNCTION*/
#define DIAGFWD_ERR(fmt, args...) \
	printk(KERN_ERR "[USBDIAG:ERR] " fmt, ## args)
#define DIAGFWD_WARNING(fmt, args...) \
	printk(KERN_WARNING "[USBDIAG] " fmt, ## args)
#define DIAGFWD_INFO(fmt, args...) \
	printk(KERN_INFO "[USBDIAG] " fmt, ## args)
#define DIAGFWD_DBUG(fmt, args...) \
	printk(KERN_DEBUG "[USBDIAG] " fmt, ## args)

/* DRIVER_SDLOG_FUNCTION*/
#define SDLOG_ERR(fmt, args...) \
	printk(KERN_ERR "[USBDIAG:ERR] " fmt, ## args)
#define SDLOG_WARNING(fmt, args...) \
	printk(KERN_WARNING "[USBDIAG] " fmt, ## args)
#define SDLOG_INFO(fmt, args...) \
	printk(KERN_INFO "[USBDIAG] " fmt, ## args)
#define SDLOG_DBUG(fmt, args...) \
	printk(KERN_DEBUG "[USBDIAG] " fmt, ## args)

/*-------------------------------------------------------------------------*/


#define SDQXDM_DEBUG
#define DIAG_XPST 1

#define DIAG_LEGACY		"diag"
#define DIAG_MDM		"diag_mdm"

#define USB_DIAG_CONNECT	0
#define USB_DIAG_DISCONNECT	1
#define USB_DIAG_WRITE_DONE	2
#define USB_DIAG_READ_DONE	3

struct diag_request {
	char *buf;
	int length;
	int actual;
	int status;
	void *context;
#ifdef SDQXDM_DEBUG
	int second;
#endif
};

struct usb_diag_ch {
	char *name;
	struct list_head list;
	void (*notify)(void *priv, unsigned event, struct diag_request *d_req);
	void *priv;
	void *priv_usb;
};

struct usb_diag_ch *usb_diag_open(const char *name, void *priv,
		void (*notify)(void *, unsigned, struct diag_request *));
void usb_diag_close(struct usb_diag_ch *ch);
int usb_diag_alloc_req(struct usb_diag_ch *ch, int n_write, int n_read);
void usb_diag_free_req(struct usb_diag_ch *ch);
int usb_diag_read(struct usb_diag_ch *ch, struct diag_request *d_req);
int usb_diag_write(struct usb_diag_ch *ch, struct diag_request *d_req);
struct usb_diag_ch *diag_setup(void);

int diag_read_from_cb(unsigned char * , int);

/* platform data for usb diag */
struct usb_diag_platform_data {
	char *ch_name;
	int (*update_pid_and_serial_num)(uint32_t, const char *);
};

struct diag2sd_platform_data {
	void (*enable_sd_log)(unsigned int enable);
};

#endif
