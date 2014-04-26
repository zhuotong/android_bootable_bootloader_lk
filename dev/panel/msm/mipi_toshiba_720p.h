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

#ifndef	_MIPI_TOSHIBA_720P_H_
#define	_MIPI_TOSHIBA_720P_H_

#include <stdint.h>
#include <msm_panel.h>
#include <mipi_dsi.h>
#include <sys/types.h>
#include <err.h>
#include <reg.h>
#include <debug.h>
#include <target/display.h>
#include <dev/gpio.h>

/* Toshiba MDV24 panel commands */
static const unsigned char toshiba_mdv24_mcap[4] = {
	0xB0, 0x00, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdv24_acr[4] = {
	0xB2, 0x00, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdv24_intf[4] = {
	0xB3, 0x0c, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdv24_pixel[4] = {
	0xB4, 0x02, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdv24_drive_setting[12] = {
	0x06, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC0, 0x40, 0x02, 0x7F,
	0xC8, 0x08, 0xFF, 0xFF
};

static const unsigned char toshiba_mdv24_display_h_timing[20] = {
	0x10, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC1, 0x00, 0xA8, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x9D, 0x08, 0x27, 0x00,
	0x00, 0x00, 0x00, 0x00
};

static const unsigned char toshiba_mdv24_source_output[12] = {
	0x06, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC2, 0x00, 0x00, 0x09,
	0x00, 0x00, 0xFF, 0xFF
};

static const unsigned char toshiba_mdv24_gate_control[4] = {
	0xC3, 0x04, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdv24_ltps_control_c4[8] = {
	0x04, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC4, 0x4d, 0x83, 0x00
};

static const unsigned char toshiba_mdv24_source_output_mode[16] = {
	0x0B, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC6, 0x12, 0x00, 0x08,
	0x71, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x04, 0xFF
};

static const unsigned char toshiba_mdv24_ltps_control_c7[4] = {
	0xC7, 0x22, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdv24_gamma_ctrl[12] = {
	0x05, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC8, 0x4C, 0x0C, 0x0C,
	0x0C, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdv24_gamma_ctrl_a_pos[20] = {
	0x0E, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xC9, 0x00, 0x40, 0x00,
	0x16, 0x32, 0x2E, 0x3A,
	0x43, 0x3E, 0x3C, 0x45,
	0x79, 0x3F, 0xFF, 0xFF
};

static const unsigned char toshiba_mdv24_gamma_ctrl_a_neg[20] = {
	0x0E, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xCA, 0x00, 0x46, 0x1A,
	0x23, 0x21, 0x1C, 0x25,
	0x31, 0x2D, 0x49, 0x5F,
	0x7F, 0x3F, 0xFF, 0xFF
};

static const unsigned char toshiba_mdv24_gamma_ctrl_b_pos[20] = {
	0x0E, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xCb, 0x00, 0x4c, 0x20,
	0x3A, 0x42, 0x40, 0x47,
	0x4B, 0x42, 0x3E, 0x46,
	0x7E, 0x3F, 0xFF, 0xFF
};

static const unsigned char toshiba_mdv24_gamma_ctrl_b_neg[20] = {
	0x0E, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xCC, 0x00, 0x41, 0x19,
	0x21, 0x1D, 0x14, 0x18,
	0x1F, 0x1D, 0x25, 0x3F,
	0x73, 0x3F, 0xFF, 0xFF
};

static const unsigned char toshiba_mdv24_gamma_ctrl_c_pos[20] = {
	0x0E, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xCD, 0x23, 0x79, 0x5A,
	0x5F, 0x57, 0x4C, 0x51,
	0x51, 0x45, 0x3F, 0x4B,
	0x7F, 0x3F, 0xFF, 0xFF
};

static const unsigned char toshiba_mdv24_gamma_ctrl_c_neg[20] = {
	0x0E, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xCE, 0x00, 0x40, 0x14,
	0x20, 0x1A, 0x0E, 0x0E,
	0x13, 0x08, 0x00, 0x05,
	0x46, 0x1C, 0xFF, 0xFF
};

static const unsigned char toshiba_mdv24_pwr_setting1[8] = {
	0x04, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD0, 0x6A, 0x64, 0x01
};

static const unsigned char toshiba_mdv24_pwr_setting2[8] = {
	0x03, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD1, 0x77, 0xd4, 0xFF
};

static const unsigned char toshiba_mdv24_pwr_setting_internal[4] = {
	0xD3, 0x33, DTYPE_GEN_WRITE2, 0x80,
};

static const unsigned char toshiba_mdv24_lvl_setting[8] = {
	0x03, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD5, 0x0F, 0x0F, 0xFF
};

static const unsigned char toshiba_mdv24_vcomdc_setting1[12] = {
	0x07, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xD8, 0x34, 0x64, 0x23,
	0x25, 0x62, 0x32, 0xFF
};

static const unsigned char toshiba_mdv24_vcomdc_setting2[16] = {
	0x0C, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xDE, 0x10, 0x7B, 0x11,
	0x0A, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
};

static const unsigned char toshiba_mdv24_init_fd[16] = {
	0x09, 0x00, DTYPE_GEN_LWRITE, 0xC0,
	0xFD, 0x04, 0x55, 0x53,
	0x00, 0x70, 0xFF, 0x10,
	0x73, 0xFF, 0xFF, 0xFF
};

static const unsigned char toshiba_mdv24_nvm_load_ctrl[4] = {
	0xE2, 0x00, DTYPE_GEN_WRITE2, 0x80,
};

/* End of Toshiba MDV24 commands */

static struct mipi_dsi_cmd toshiba_mdv24_video_mode_cmds[] = {
	{sizeof(toshiba_mdv24_mcap), (char *)toshiba_mdv24_mcap, 0},
	{sizeof(toshiba_mdv24_acr),
	 (char *)toshiba_mdv24_acr, 0},
	{sizeof(toshiba_mdv24_intf), (char *)toshiba_mdv24_intf, 0},
	{sizeof(toshiba_mdv24_pixel), (char *)toshiba_mdv24_pixel, 0},
	{sizeof(toshiba_mdv24_drive_setting),
	 (char *)toshiba_mdv24_drive_setting, 0},
	{sizeof(toshiba_mdv24_display_h_timing),
	 (char *)toshiba_mdv24_display_h_timing, 0},
	{sizeof(toshiba_mdv24_source_output),
	 (char *)toshiba_mdv24_source_output, 0},
	{sizeof(toshiba_mdv24_gate_control),
	 (char *)toshiba_mdv24_gate_control, 0},
	{sizeof(toshiba_mdv24_ltps_control_c4),
	 (char *)toshiba_mdv24_ltps_control_c4, 0},
	{sizeof(toshiba_mdv24_source_output_mode),
	 (char *)toshiba_mdv24_source_output_mode, 0},
	{sizeof(toshiba_mdv24_ltps_control_c7),
	 (char *)toshiba_mdv24_ltps_control_c7, 0},
	{sizeof(toshiba_mdv24_gamma_ctrl),
	 (char *)toshiba_mdv24_gamma_ctrl, 0},
	{sizeof(toshiba_mdv24_gamma_ctrl_a_pos),
	 (char *)toshiba_mdv24_gamma_ctrl_a_pos, 0},
	{sizeof(toshiba_mdv24_gamma_ctrl_a_neg),
	 (char *)toshiba_mdv24_gamma_ctrl_a_neg, 0},
	{sizeof(toshiba_mdv24_gamma_ctrl_b_pos),
	 (char *)toshiba_mdv24_gamma_ctrl_b_pos, 0},
	{sizeof(toshiba_mdv24_gamma_ctrl_b_neg),
	 (char *)toshiba_mdv24_gamma_ctrl_b_neg, 0},
	{sizeof(toshiba_mdv24_gamma_ctrl_c_pos),
	 (char *)toshiba_mdv24_gamma_ctrl_c_pos, 0},
	{sizeof(toshiba_mdv24_gamma_ctrl_c_neg),
	 (char *)toshiba_mdv24_gamma_ctrl_c_neg, 0},
	{sizeof(toshiba_mdv24_pwr_setting1),
	 (char *)toshiba_mdv24_pwr_setting1, 0},
	{sizeof(toshiba_mdv24_pwr_setting2),
	 (char *)toshiba_mdv24_pwr_setting2, 0},
	{sizeof(toshiba_mdv24_pwr_setting_internal),
	 (char *)toshiba_mdv24_pwr_setting_internal, 0},
	{sizeof(toshiba_mdv24_lvl_setting),
	 (char *)toshiba_mdv24_lvl_setting, 0},
	{sizeof(toshiba_mdv24_vcomdc_setting1),
	 (char *)toshiba_mdv24_vcomdc_setting1, 0},
	{sizeof(toshiba_mdv24_vcomdc_setting2),
	 (char *)toshiba_mdv24_vcomdc_setting2, 0},
	{sizeof(toshiba_mdv24_init_fd),
	 (char *)toshiba_mdv24_init_fd, 0},
	{sizeof(toshiba_mdv24_nvm_load_ctrl),
	 (char *)toshiba_mdv24_nvm_load_ctrl, 0},
	{sizeof(dsi_display_exit_sleep), (char *)dsi_display_exit_sleep, 0},
	{sizeof(dsi_display_display_on), (char *)dsi_display_display_on, 0},
};

#endif /* _MIPI_TOSHIBA_720P_H_ */
