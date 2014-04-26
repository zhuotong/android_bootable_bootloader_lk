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

#ifndef	_MIPI_TOSHIBA_H_
#define	_MIPI_TOSHIBA_H_

#include <stdint.h>
#include <msm_panel.h>
#include <mipi_dsi.h>
#include <sys/types.h>
#include <err.h>
#include <reg.h>
#include <debug.h>
#include <target/display.h>
#include <dev/gpio.h>

/* Toshiba mdt61 panel cmds */
static const unsigned char toshiba_mdt61_mcap_start[4] = {
	0xB0, 0x04, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdt61_num_out_pixelform[8] = {
	0x03, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xB3, 0x00, 0x87, 0xFF
};

static const unsigned char toshiba_mdt61_dsi_ctrl[8] = {
	0x03, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xB6, 0x30, 0x83, 0xFF
};

static const unsigned char toshiba_mdt61_panel_driving[12] = {
	0x07, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC0, 0x01, 0x00, 0x85,
	0x00, 0x00, 0x00, 0xFF
};

static const unsigned char toshiba_mdt61_dispV_timing[12] = {
	0x05, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC1, 0x00, 0x10, 0x00,
	0x01, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_dispCtrl[8] = {
	0x03, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC3, 0x00, 0x19, 0xFF
};

static const unsigned char toshiba_mdt61_test_mode_c4[4] = {
	0xC4, 0x03, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdt61_dispH_timing[20] = {
	0x0F, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC5, 0x00, 0x01, 0x05,
	0x04, 0x5E, 0x00, 0x00,
	0x00, 0x00, 0x0B, 0x17,
	0x05, 0x00, 0x00, 0xFF
};

static const unsigned char toshiba_mdt61_test_mode_c6[4] = {
	0xC6, 0x00, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdt61_gamma_setA[20] = {
	0x0D, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC8, 0x0A, 0x15, 0x18,
	0x1B, 0x1C, 0x0D, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_gamma_setB[20] = {
	0x0D, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC9, 0x0D, 0x1D, 0x1F,
	0x1F, 0x1F, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_gamma_setC[20] = {
	0x0D, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xCA, 0x1E, 0x1F, 0x1E,
	0x1D, 0x1D, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_powerSet_ChrgPmp[12] = {
	0x05, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD0, 0x02, 0x00, 0xA3,
	0xB8, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_testMode_d1[12] = {
	0x06, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD1, 0x10, 0x14, 0x53,
	0x64, 0x00, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_powerSet_SrcAmp[8] = {
	0x03, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD2, 0xB3, 0x00, 0xFF
};

static const unsigned char toshiba_mdt61_powerInt_PS[8] = {
	0x03, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD3, 0x33, 0x03, 0xFF
};

static const unsigned char toshiba_mdt61_vreg[4] = {
	0xD5, 0x00, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdt61_test_mode_d6[4] = {
	0xD6, 0x01, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdt61_timingCtrl_d7[16] = {
	0x09, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD7, 0x09, 0x00, 0x84,
	0x81, 0x61, 0xBC, 0xB5,
	0x05, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_timingCtrl_d8[12] = {
	0x07, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD8, 0x04, 0x25, 0x90,
	0x4C, 0x92, 0x00, 0xFF
};

static const unsigned char toshiba_mdt61_timingCtrl_d9[8] = {
	0x04, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD9, 0x5B, 0x7F, 0x05
};

static const unsigned char toshiba_mdt61_white_balance[12] = {
	0x06, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xCB, 0x00, 0x00, 0x00,
	0x1C, 0x00, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_vcs_settings[4] = {
	0xDD, 0x53, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdt61_vcom_dc_settings[4] = {
	0xDE, 0x43, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdt61_testMode_e3[12] = {
	0x05, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xE3, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_testMode_e4[12] = {
	0x06, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xE4, 0x00, 0x00, 0x22,
	0xAA, 0x00, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_testMode_e5[4] = {
	0xE5, 0x00, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdt61_testMode_fa[8] = {
	0x04, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xFA, 0x00, 0x00, 0x00
};

static const unsigned char toshiba_mdt61_testMode_fd[12] = {
	0x05, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xFD, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_testMode_fe[12] = {
	0x05, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xFE, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdt61_mcap_end[4] = {
	0xB0, 0x03, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdt61_set_add_mode[4] = {
	0x36, 0x00, DTYPE_DCS_WRITE1, 0x80,
};

static const unsigned char toshiba_mdt61_set_pixel_format[4] = {
	0x3A, 0x70, DTYPE_DCS_WRITE1, 0x80,
};

/* Done Toshiba MDT61 Panel Commands */
/* Toshiba MDT61 (R69320) End */

static struct mipi_dsi_cmd toshiba_mdt61_video_mode_cmds[] = {
	{sizeof(toshiba_mdt61_mcap_start), (char *)toshiba_mdt61_mcap_start, 0},
	{sizeof(toshiba_mdt61_num_out_pixelform),
	 (char *)toshiba_mdt61_num_out_pixelform, 0},
	{sizeof(toshiba_mdt61_dsi_ctrl), (char *)toshiba_mdt61_dsi_ctrl, 0},
	{sizeof(toshiba_mdt61_panel_driving),
	 (char *)toshiba_mdt61_panel_driving, 0},
	{sizeof(toshiba_mdt61_dispV_timing),
	 (char *)toshiba_mdt61_dispV_timing, 0},
	{sizeof(toshiba_mdt61_dispCtrl), (char *)toshiba_mdt61_dispCtrl, 0},
	{sizeof(toshiba_mdt61_test_mode_c4),
	 (char *)toshiba_mdt61_test_mode_c4, 0},
	{sizeof(toshiba_mdt61_dispH_timing),
	 (char *)toshiba_mdt61_dispH_timing, 0},
	{sizeof(toshiba_mdt61_test_mode_c6),
	 (char *)toshiba_mdt61_test_mode_c6, 0},
	{sizeof(toshiba_mdt61_gamma_setA), (char *)toshiba_mdt61_gamma_setA, 0},
	{sizeof(toshiba_mdt61_gamma_setB), (char *)toshiba_mdt61_gamma_setB, 0},
	{sizeof(toshiba_mdt61_gamma_setC), (char *)toshiba_mdt61_gamma_setC, 0},
	{sizeof(toshiba_mdt61_powerSet_ChrgPmp),
	 (char *)toshiba_mdt61_powerSet_ChrgPmp, 0},
	{sizeof(toshiba_mdt61_testMode_d1), (char *)toshiba_mdt61_testMode_d1, 0},
	{sizeof(toshiba_mdt61_powerSet_SrcAmp),
	 (char *)toshiba_mdt61_powerSet_SrcAmp, 0},
	{sizeof(toshiba_mdt61_powerInt_PS), (char *)toshiba_mdt61_powerInt_PS, 0},
	{sizeof(toshiba_mdt61_vreg), (char *)toshiba_mdt61_vreg, 0},
	{sizeof(toshiba_mdt61_test_mode_d6),
	 (char *)toshiba_mdt61_test_mode_d6, 0},
	{sizeof(toshiba_mdt61_timingCtrl_d7),
	 (char *)toshiba_mdt61_timingCtrl_d7, 0},
	{sizeof(toshiba_mdt61_timingCtrl_d8),
	 (char *)toshiba_mdt61_timingCtrl_d8, 0},
	{sizeof(toshiba_mdt61_timingCtrl_d9),
	 (char *)toshiba_mdt61_timingCtrl_d9, 0},
	{sizeof(toshiba_mdt61_white_balance),
	 (char *)toshiba_mdt61_white_balance, 0},
	{sizeof(toshiba_mdt61_vcs_settings),
	 (char *)toshiba_mdt61_vcs_settings, 0},
	{sizeof(toshiba_mdt61_vcom_dc_settings),
	 (char *)toshiba_mdt61_vcom_dc_settings, 0},
	{sizeof(toshiba_mdt61_testMode_e3), (char *)toshiba_mdt61_testMode_e3, 0},
	{sizeof(toshiba_mdt61_testMode_e4), (char *)toshiba_mdt61_testMode_e4, 0},
	{sizeof(toshiba_mdt61_testMode_e5), (char *)toshiba_mdt61_testMode_e5, 0},
	{sizeof(toshiba_mdt61_testMode_fa), (char *)toshiba_mdt61_testMode_fa, 0},
	{sizeof(toshiba_mdt61_testMode_fd), (char *)toshiba_mdt61_testMode_fd, 0},
	{sizeof(toshiba_mdt61_testMode_fe), (char *)toshiba_mdt61_testMode_fe, 0},
	{sizeof(toshiba_mdt61_mcap_end), (char *)toshiba_mdt61_mcap_end, 0},
	{sizeof(toshiba_mdt61_set_add_mode),
	 (char *)toshiba_mdt61_set_add_mode, 0},
	{sizeof(toshiba_mdt61_set_pixel_format),
	 (char *)toshiba_mdt61_set_pixel_format, 0},
	{sizeof(dsi_display_exit_sleep), (char *)dsi_display_exit_sleep, 0},
	{sizeof(dsi_display_display_on), (char *)dsi_display_display_on, 0},
};

#endif /* _MIPI_TOSHIBA_H_ */
