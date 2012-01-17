/* arch/arm/mach-msm/qdsp6v2/timpani_profile_8x60_lead.h
 *
 * Copyright (C) 2010 HTC Corporation
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __TIMPANI_PROFILE_LEAD_H
#define __TIMPANI_PROFILE_LEAD_H

/* RX HPH CLASS AB CAPLESS, STEREO OR MONO OR MONO-DIFF */
#define HEADSET_STEREO_AB_CPLS_48000_OSR_256 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x02, 0x02)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x02, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x03, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x03)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xA3, 0x02, 0x02)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x84, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x85, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x0C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x81, 0xFF, 0x0E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x03, 0x03)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x24, 0x6F, 0x6C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xB7, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x55)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xCA)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xBB8}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0xFD)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xC8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x27, 0x27)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x04, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x36, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x37, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x03)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x27, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x04, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }


/* RX EAR MONO*/
#define EAR_PRI_MONO_48000_OSR_256 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x02, 0x02)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x02, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x03, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x03)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xA3, 0x02, 0x02)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x84, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x85, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x0C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x81, 0xFF, 0x0E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x03, 0x03)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x24, 0x6F, 0x6C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xB7, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x55)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xCA)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xBB8}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0xFD)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xC8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x27, 0x23)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x04, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x36, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x37, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x03)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x27, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x04, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }

/* RX SPK, STEREO OR MONO OR MONO-DIFF */
#define SPEAKER_PRI_48000_OSR_256 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x02, 0x02)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x02, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x03, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x03)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xA3, 0x02, 0x02)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x84, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x85, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x0C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x81, 0xFF, 0x0E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x03, 0x03)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x24, 0x6F, 0x6C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xB7, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x55)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xCA)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xBB8}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0xFD)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xC8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x27, 0x23)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x04, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x36, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x37, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x03)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x27, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x04, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }


/* ANALOG IMIC Primary MONO */
#define AMIC_PRI_MONO_48000_OSR_256 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x05, 0x05)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x05, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0x30)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x86, 0xFF, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x87, 0xFF, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xF0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x82, 0xFF, 0x1E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xA3, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x93, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x94, 0xFF, 0x1B)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x99, 0x0F, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x9F, 0x03, 0x03)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x0D, 0xFF, 0xD0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x11, 0xFF, 0xBC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x12, 0xFF, 0xBC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x14, 0xFF, 0x65)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xbb8}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x0C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x86, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x87, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xC0)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xF0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x0D, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x14, 0xFF, 0x64)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x11, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x12, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }


/* Headset MIC */
#define HS_AMIC2_MONO_48000_OSR_256 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x05, 0x05)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x05, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0x30)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x86, 0xFF, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x87, 0xFF, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xF0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x82, 0xFF, 0x1E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xA3, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x93, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x94, 0xFF, 0x1B)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x99, 0x0F, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x9F, 0x03, 0x03)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x0D, 0xFF, 0xC8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x11, 0xFF, 0xBC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x12, 0xFF, 0xBC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x14, 0xFF, 0x65)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xbb8 }, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x0C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x86, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x87, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xC0)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xF0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x0D, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x14, 0xFF, 0x64)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x11, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x12, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }


/* Headset MIC */
#define HS_AMIC2_MONO_8000_OSR_256 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x05, 0x05)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x05, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0x30)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x86, 0xFF, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x87, 0xFF, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xF0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x82, 0xFF, 0x1E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xA3, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x93, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x94, 0xFF, 0x1B)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x99, 0x0F, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x9F, 0x03, 0x03)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x0D, 0xFF, 0xC8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x11, 0xFF, 0xBC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x12, 0xFF, 0xBC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x14, 0xFF, 0x65)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xbb8 }, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x0C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x86, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x87, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xC0)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xF0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x0D, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x14, 0xFF, 0x64)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x11, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x12, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }


/* TTY RX */
#define TTY_HEADSET_MONO_RX_48000_OSR_256 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x02, 0x02)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x02, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x03, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x03)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x81, 0xFF, 0x0E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xA3, 0x02, 0x02)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x97, 0xFF, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x84, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x06)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x81, 0xFF, 0x0E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x03, 0x01)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x24, 0x6F, 0x4C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xB7, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x45)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xCA)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xBB8}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0xC5)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xC8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x27, 0x20)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x20, 0x20)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x10)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x08)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x03)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }


/* TTY TX */
#define TTY_HEADSET_MONO_TX_48000_OSR_256 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x05, 0x05)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x05, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0x30)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x86, 0xFF, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x87, 0xFF, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xF0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x82, 0xFF, 0x1E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xA3, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x93, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x94, 0xFF, 0x1B)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x99, 0x0F, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x9F, 0x03, 0x03)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x0D, 0xFF, 0xA8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x11, 0xFF, 0xBC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x12, 0xFF, 0xBC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x14, 0xFF, 0x65)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xBB8}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x0C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x86, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x87, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xC0)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xF0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x0D, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x14, 0xFF, 0x64)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x11, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x12, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }


/* FM HPH, RX HPH CLASS AB CAPLESS, STEREO OR MONO OR MONO-DIFF */
#define AUXPGA_HEADSET_AB_CPLS_RX_48000 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x33, 0xF0, 0xC0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x2F, 0x88, 0x88)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x30, 0x90, 0x90)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x24, 0x6F, 0x6C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xB7, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x55)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xCA)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xBB8}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x33, 0xF0, 0x30)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0xF5)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xC8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x38, 0xEE, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x90, 0x90)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x90, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x38, 0xEE, 0x55)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x38, 0xEE, 0xAA)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x38, 0xEE, 0x55)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x38, 0xEE, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x90, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x90, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x33, 0xF0, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }
	
	
/* FM SPK, RX SPK, STEREO OR MONO OR MONO-DIFF */
#define AUXPGA_SPEAKER_RX \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x33, 0xF0, 0xC0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x2F, 0x88, 0x88)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x30, 0x90, 0x90)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x24, 0x6F, 0x6C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xB7, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x55)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xCA)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xBB8}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x33, 0xF0, 0x30)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0xF5)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xC8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x38, 0xEE, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x90, 0x80)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x10, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x38, 0xEE, 0x55)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x38, 0xEE, 0xAA)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x38, 0xEE, 0x55)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x38, 0xEE, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x90, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x90, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x33, 0xF0, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }


#define SPEAKER_HPH_AB_CPL_PRI_48000_OSR_256 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x02, 0x02)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x02, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x03, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x03)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xA3, 0x02, 0x02)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x84, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x85, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0x0F, 0x0C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x81, 0xFF, 0x0E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x03, 0x03)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x24, 0x6F, 0x6C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xB7, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x55)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x32, 0xF8, 0x08)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xCA)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0x1388}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0xF5)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x4C, 0xFE, 0xC8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x32, 0xF8, 0x48)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0x1388}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x32, 0xF8, 0xF8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE0, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE1, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3A, 0x24, 0x24)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3B, 0x04, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE0, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE1, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE0, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE1, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE0, 0xFE, 0x10)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE1, 0xFE, 0x10)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x27, 0x24)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x04, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x04)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE0, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE1, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE0, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE1, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE0, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE1, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x1C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFE, 0x3C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE2, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xE3, 0xFC, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3C, 0x27, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3D, 0x04, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x32, 0xF8, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x31, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3A, 0x24, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x3B, 0x04, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF},	\
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }

#define DUAL_MIC_STEREO_TX_48000_OSR_256 \
	{{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_FLASH_IMAGE},  \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x05, 0x05)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x80, 0x05, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0x30)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x86, 0xFF, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x87, 0xFF, 0xAC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xF0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x82, 0xFF, 0x1E)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0xA3, 0x01, 0x01)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x93, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x94, 0xFF, 0x1B)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x99, 0x0F, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x9F, 0x03, 0x03)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x0D, 0xFF, 0xC8)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x11, 0xFF, 0xBC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x12, 0xFF, 0xBC)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x14, 0xFF, 0x65)}, \
	{ADIE_CODEC_ACTION_DELAY_WAIT, 0xbb8 }, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x0C)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x86, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x87, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xC0)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_ANALOG_READY}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x8A, 0xF0, 0xF0)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x83, 0x0C, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_ANALOG_OFF}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x0D, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x14, 0xFF, 0x64)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x11, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_ENTRY, ADIE_CODEC_PACK_ENTRY(0x12, 0xFF, 0x00)}, \
	{ADIE_CODEC_ACTION_STAGE_REACHED, ADIE_CODEC_DIGITAL_OFF} }

#endif
