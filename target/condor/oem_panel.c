/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of The Linux Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <debug.h>
#include <err.h>
#include <smem.h>
#include <msm_panel.h>
#include <board.h>
#include <mipi_dsi.h>

#include "include/panel.h"
#include "panel_display.h"

/*---------------------------------------------------------------------------*/
/* GCDB Panel Database                                                       */
/*---------------------------------------------------------------------------*/
#include "include/panel_mot_inx_qhd_video.h"
#include "include/panel_mot_tianma_qhd_video.h"

/* Number of dectectable panels */
#define DISPLAY_MAX_PANEL_DETECTION 2

/*---------------------------------------------------------------------------*/
/* static panel selection variable                                           */
/*---------------------------------------------------------------------------*/
enum {
MOT_INX_QHD_VIDEO_PANEL,
MOT_TIANMA_QHD_VIDEO_PANEL,
UNKNOWN_PANEL
};

static uint32_t panel_id;

int oem_panel_rotation()
{
	/* OEM can keep there panel spefic on instructions in this
	function */
	return NO_ERROR;
}


int oem_panel_on()
{
	/* OEM can keep there panel spefic on instructions in this
	function */
	return NO_ERROR;
}

int oem_panel_off()
{
	/* OEM can keep there panel spefic off instructions in this
	function */
	return NO_ERROR;
}

static bool init_panel_data(struct panel_struct *panelstruct,
			struct msm_panel_info *pinfo,
			struct mdss_dsi_phy_ctrl *phy_db)
{
	switch (panel_id) {
	case MOT_INX_QHD_VIDEO_PANEL:
		panelstruct->paneldata    = &mot_inx_qhd_video_panel_data;
		panelstruct->panelres     = &mot_inx_qhd_video_panel_res;
		panelstruct->color        = &mot_inx_qhd_video_color;
		panelstruct->videopanel   = &mot_inx_qhd_video_video_panel;
		panelstruct->commandpanel = &mot_inx_qhd_video_command_panel;
		panelstruct->state        = &mot_inx_qhd_video_state;
		panelstruct->laneconfig   = &mot_inx_qhd_video_lane_config;
		panelstruct->paneltiminginfo
					 = &mot_inx_qhd_video_timing_info;
		panelstruct->panelresetseq
					 = &mot_inx_qhd_video_panel_reset_seq;
		panelstruct->backlightinfo = &mot_inx_qhd_video_backlight;
		pinfo->mipi.panel_cmds
					= mot_inx_qhd_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= MOT_INX_QHD_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				mot_inx_qhd_video_timings, TIMING_SIZE);
		break;
	case MOT_TIANMA_QHD_VIDEO_PANEL:
		panelstruct->paneldata    = &mot_tianma_qhd_video_panel_data;
		panelstruct->panelres     = &mot_tianma_qhd_video_panel_res;
		panelstruct->color        = &mot_tianma_qhd_video_color;
		panelstruct->videopanel   = &mot_tianma_qhd_video_video_panel;
		panelstruct->commandpanel = &mot_tianma_qhd_video_command_panel;
		panelstruct->state        = &mot_tianma_qhd_video_state;
		panelstruct->laneconfig   = &mot_tianma_qhd_video_lane_config;
		panelstruct->paneltiminginfo
					 = &mot_tianma_qhd_video_timing_info;
		panelstruct->panelresetseq
					 = &mot_tianma_qhd_video_panel_reset_seq;
		panelstruct->backlightinfo = &mot_tianma_qhd_video_backlight;
		pinfo->mipi.panel_cmds
					= mot_tianma_qhd_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= MOT_TIANMA_QHD_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				mot_tianma_qhd_video_timings, TIMING_SIZE);
		break;
	case UNKNOWN_PANEL:
		memset(panelstruct, 0, sizeof(struct panel_struct));
		memset(pinfo->mipi.panel_cmds, 0, sizeof(struct mipi_dsi_cmd));
		pinfo->mipi.num_of_panel_cmds = 0;
		memset(phy_db->timing, 0, TIMING_SIZE);
		pinfo->mipi.signature = 0;
		dprintf(CRITICAL, "Unknown Panel");
		return false;
	default:
		dprintf(CRITICAL, "Panel ID not detected %d\n", panel_id);
		return false;
	}
	return true;
}

uint32_t oem_panel_max_auto_detect_panels()
{
	return target_panel_auto_detect_enabled() ?
			DISPLAY_MAX_PANEL_DETECTION : 0;
}

bool oem_panel_select(const char *panel_name, struct panel_struct *panelstruct,
			struct msm_panel_info *pinfo,
			struct mdss_dsi_phy_ctrl *phy_db)
{
	uint32_t platform_subtype = board_hardware_subtype();

	panel_id = MOT_INX_QHD_VIDEO_PANEL;

	return init_panel_data(panelstruct, pinfo, phy_db);
}
