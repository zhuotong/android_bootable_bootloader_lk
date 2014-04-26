/* Copyright (c) 2012, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef	_MIPI_SHARP_H_
#define	_MIPI_SHARP_H_

#include <stdint.h>
#include <msm_panel.h>
#include <mipi_dsi.h>
#include <sys/types.h>
#include <err.h>
#include <reg.h>
#include <debug.h>
#include <target/display.h>
#include <dev/gpio.h>

static char sharp_panel_sw_reset[4] = { 0x01, 0x00, 0x05, 0x00 };	/* DTYPE_DCS_WRITE */
static char sharp_panel_exit_sleep[4] = { 0x11, 0x00, 0x05, 0x80 };	/* DTYPE_DCS_WRITE */
static char sharp_panel_display_on[4] = { 0x29, 0x00, 0x05, 0x80 };	/* DTYPE_DCS_WRITE */
static char sharp_panel_set_twolane[4] = { 0xae, 0x03, 0x15, 0x80 };	/* DTYPE_DCS_WRITE1 */
static char sharp_panel_rgb_888[4] = { 0x3A, 0x77, 0x15, 0x80 };	/* DTYPE_DCS_WRITE1 */

/* Commands to control Backlight */
static char sharp_panel_set_led_pwm1[8] = {	/* DTYPE_DCS_LWRITE */
	0x02, 0x00, 0x39, 0xC0,	//1 last packet
	0x51, 0xFA, 0xFF, 0xFF,	// Brightness level set to 0xFA -> 250
};

static char sharp_panel_set_led_pwm2[8] = {	/* DTYPE_DCS_LWRITE */
	0x02, 0x00, 0x39, 0xC0,
	0x53, 0x24, 0xFF, 0xFF,
};

static char sharp_panel_set_led_pwm3[8] = {	/* DTYPE_DCS_LWRITE */
	0x02, 0x00, 0x39, 0xC0,
	0x55, 0x00, 0xFF, 0xFF,
};


static struct mipi_dsi_cmd sharp_qhd_video_mode_cmds[] = {
	{sizeof(sharp_panel_sw_reset), sharp_panel_sw_reset, 0}
	,
	{sizeof(sharp_panel_exit_sleep), sharp_panel_exit_sleep, 0}
	,
	{sizeof(sharp_panel_display_on), sharp_panel_display_on, 0}
	,
	{sizeof(sharp_panel_set_twolane), sharp_panel_set_twolane, 0}
	,
	{sizeof(sharp_panel_rgb_888), sharp_panel_rgb_888, 0}
	,
	{sizeof(sharp_panel_set_led_pwm1), sharp_panel_set_led_pwm1, 0}
	,
	{sizeof(sharp_panel_set_led_pwm2), sharp_panel_set_led_pwm2, 0}
	,
	{sizeof(sharp_panel_set_led_pwm3), sharp_panel_set_led_pwm3, 0}
};

#endif /* _MIPI_SHARP_H_ */
