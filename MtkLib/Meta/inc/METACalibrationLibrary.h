/*****************************************************************************
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of MediaTek Inc. (C) 2005
 *
 *  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 *  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
 *  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 *  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 *  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 *  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
 *  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
 *  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
 *  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 *  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 *  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
 *  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
 *  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
 *  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
 *  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/
/*******************************************************************************
 * Filename:
 * ---------
 *  METACalibrationLibrary.h
 *
 * Project:
 * --------
 *   META Calibration Library
 *
 * Description:
 * ------------
 *   This module contains the definitions of Calibration library
 *
 * Author:
 * -------
 *  ShuMin Chen (mtk01569)
 *
 *==============================================================================
 *           HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 *
 * 06 25 2013 eason.lai
 * [STP100007207]  cotsx change naming to gps co clock
 * .
 *
 * 06 17 2013 eason.lai
 * [STP100007190]  multi-port instrument multi-phone feature
 * .
 *
 * 06 13 2013 eason.lai
 * [STP100007098]  GPSCOCLOCK add nvram values check criterion and (steps, duration) generation tool
 * .
 *
 * 05 03 2013 eason.lai
 * [STP100006974]  GGE NSFT single-end BER, RX level, and RX Quality porting
 * .
 *
 * 04 09 2013 eason.lai
 * [STP100006899]  New feature of acquiring C0 & C1 from temperature-frequency values for CO-TSX
 * .
 *
 * 04 09 2013 eason.lai
 * [STP100006900]  New feature of cableloss calibration
 * .
 *
 * 04 09 2013 eason.lai
 * [STP100006899]  New feature of acquiring C0 & C1 from temperature-frequency values for CO-TSX
 * GPSCOCLOCK file revisions
 *
 * 03 07 2013 eason.lai
 * [STP100006814]  Renaming the ambiguous naming of high speed pcl cabliration with FHC
 * .
 *
 * 03 07 2013 eason.lai
 * [STP100006808]  Two port RXD calibration
 * .
 *
 * 03 05 2013 eason.lai
 * [STP100006807]  Skyworks dc offset calibration
 * .
 *
 * 02 06 2013 eason.lai
 * [STP100006742]  Add LPM check and merge CMU200 frequency offset measurement command
 * .
 *
 * 02 05 2013 eason.lai
 * [STP100006406]  Add "Full EDGE SW + EDGE RX only HW" check in calibraion flow in META
 * .
 *
 * 12 25 2012 vend_brog.chu
 * [STP100006561] Add TDD NSFT RSCP function
 * Add TDD NSFT RSCP TEST
 *
 * 12 19 2012 eason.lai
 * [STP100006547]  WCDM NSFT uarfcn to band mapping
 * .
 *
 * 12 03 2012 eason.lai
 * [STP100006503]  Reset WCDMA RX path to both when calibraton for preventing user changed the rx path to single antenna in RF tool
 * .
 *
 * 11 16 2012 eason.lai
 * [STP100006413]  Fixed power measurement failed but the calibration may pass issue due to measurement report power is zero
 * .
 *
 * 10 18 2012 eason.lai
 * [STP100006301]  Fix build error and remove MT6280 internal compile option
 * .
 *
 * 09 26 2012 eason.lai
 * [STP100006213]  GSMK/EPSK TX PCL high speed calibration
 * .
 *
 * 09 17 2012 eason.lai
 * [STP100006183]  Share library MT6140 FHC & MT6252 33 steps AFC
 * .
 *
 * 09 06 2012 yh.sung
 * [STP100006026]  [META] Dual Talk META API
 * Sync project file setting to Trunk
 * remove the MFC library inclusion in calibration library and instrument library
 *
 * 08 30 2012 yh.sung
 * [STP100006026]  [META] Dual Talk META API
 * Merge calibration library
 *
 * 08 22 2012 eason.lai
 * [STP100006107]  [Share library] MT6280 pa drift compensation
 * .
 *
 * 08 09 2012 eason.lai
 * [STP100006050]  Merg from CAL_LIB_DEV and start to release share library from customer release branch
 * .
 *
 * 07 18 2012 eason.lai
 * [STP100006012]  [Share libraray]MT6280 RxD pathloss calibration porting and WCDMA NSFT RSSI test
 * .
 *
 * 07 16 2012 eason.lai
 * [STP100005998]  Share libraray add FtaAgent.dll existing check and exception
 * .
 *
 * 06 29 2012 eason.lai
 * [STP100005862]  Merge share library FHC and insturment control ocde from CAL_LIB_DEV branch for MT6280 FHC
 * 1.
 * Merged MT6280 FHC from CAL_LIB_DEV branch
 * .
 * 2. Merged aquire specific settings from instrument setting API.
 *
 * 05 31 2012 eason.lai
 * [STP100005791]  MT6280 dev branch merge to trunk
 * .
 *
 * 04 19 2012 eason.lai
 * [STP100005381]  Calibration Library Porting: W coefficient calibration
 * .
 *
 * 03 29 2012 eason.lai
 * [STP100005632]  META calibartion sharelibrary porting
 * .
 *
 * 02 02 2012 eason.lai
 * [STP100005437]  2G AFC calibration result share with TD AFC calibration
 * [STP100005437] 2G AFC calibration result share with TD AFC calibration
 *
 * 12 20 2011 yh.sung
 * [STP100005306]  [Calibration Library] MT6140 APC calibration / MT6162 3G APC calibration
 * Calibration library modification MT6140 APC calibration
 *  / MT6162 3G APC calibration
 *
 * 12 02 2011 yh.sung
 * [STP100005274]  [META] FB DAC / Slope skew / TX IQ / TRX offset calibration for calibration library
 * .
 *
 * 12 01 2011 yh.sung
 * [STP100004863]  DCXO Low-Power Mode (LPM) coarse & fine calibration
 * Port DCXO Low power mode calibration into calibraion library
 *
 * 11 23 2011 yh.sung
 * [STP100004949]  Meta tool modify for 3G AFC calibration of DCXO
 * Porting 3G DCXO AFC calibration to calibration library
 *
 * 11 01 2011 yh.sung
 * [STP100005152]  [Calibration Library] MT6162 2G calibration and 2G NSFT
 * 2G SOC calibration library (MT6253 / MT6252) calibration flow
 *
 * 10 25 2011 yh.sung
 * [STP100005152]  [Calibration Library] MT6162 2G calibration and 2G NSFT
 * Resolve naming conflict and build warnings.
 *
 * 10 24 2011 yh.sung
 * [STP100005152]  [Calibration Library] MT6162 2G calibration and 2G NSFT
 * Merge changes from AE2.
 *
 * 09 08 2011 yh.sung
 * [STP100005004]  [Calibration Library] MT6163 APC Calibration
 * update DLL version logging too.
 *
 * 09 07 2011 yh.sung
 * [STP100004997]  [Calibration Library] 3G FDD / TDD CAP ID calibration
 * .
 *
 * 09 01 2011 yh.sung
 * [STP100004945]  Meta tool can support 8960 to do AFC sweep in TD mode
 * .
 *
 * 06 29 2011 yh.sung
 * [STP100004806]  [META Calibration Library] 3G FDD item porting
 * .
 *
 * 06 13 2011 yh.sung
 * [STP100004761]  [4N tool customer release verification] - FP_Tools W1124
 * Import BROM DLL v5.1124.0
 *
 * 03 05 2011 yh.sung
 * [STP100004338]  MT6276 + OH calibration (Traditional calibration (RX LNA / 8-level PA control,  FHC (RX LNA / 8-level PA control),  NSFT)
 * CMU200 initialization.
 *
 * 02 23 2011 yh.sung
 * [STP100004338]  MT6276 + OH FHC & NSFT
 * [STP100004338] MT6276 + OH FHC & NSFT
 * .
 *
 * 02 01 2011 yh.sung
 * [STP100004338]  MT6276 + OH FHC & NSFT
 * OH FHC
 *
 * 01 26 2011 yh.sung
 * [STP100004040]  [META] [Instrument] Support AG8960 TD FHC+NSFT
 * TD FHC
 *
 * 01 20 2011 yh.sung
 * [STP100004338]  MT6276 + OH FHC & NSFT
 * [STP100004338] MT6276 + OH FHC & NSFT
 * HSDPA/HSUPA NSFT integration
 *
 * 01 01 2011 yh.sung
 * [STP100004038]  [META] [Instrument] Support SP6010 TD Trad+NSFT
 * .
 *
 * 12 29 2010 yh.sung
 * [STP100103442]  [4N tool customer release verification] - TD_Tools W1052
 * .
 *
 * 11 08 2010 shumin.chen
 * [STP100004226]  [META APP, DLL] Check in TD-Astronaut Codes with new branch
 * sharing library support TD-NSFT on Agilent8960
*
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/

#ifndef __META_CALIBRATION_LIBRARY_H__
#define __META_CALIBRATION_LIBRARY_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    E_METACalibrationLibrary_STATUS_SUCCESS = 0,
    E_METACalibrationLibrary_STATUS_LIB_INIT_FAILED = 1,
    E_METACalibrationLibrary_STATUS_INVALID_HANDLE = 2,
    E_METACalibrationLibrary_STATUS_CREATE_LOG_FILE_FAILED = 3,
    E_METACalibrationLibrary_STATUS_CREATE_REPORT_FILE_FAILED = 4,
    E_METACalibrationLibrary_STATUS_GENERATE_OUTPUT_FILE_FAILED = 5,
    E_METACalibrationLibrary_STATUS_CFG_FILE_INVALID = 6,
    E_METACalibrationLibrary_STATUS_INI_FILE_INVALID = 7,
    E_METACalibrationLibrary_STATUS_GET_NVRAM_RECLEN_FAILED = 8,
    E_METACalibrationLibrary_STATUS_COMPOSE_NVRAM_FAILED = 9,
    E_METACalibrationLibrary_STATUS_WRITE_NVRAM_FAILED = 10,
    E_METACalibrationLibrary_STATUS_WRITE_CAL_FILE_FAILED = 11,
    E_METACalibrationLibrary_STATUS_TESTER_CTRL_FAILED = 12,
    E_METACalibrationLibrary_STATUS_TESTER_CTRL_DEINIT_FAILED = 13,
    E_METACalibrationLibrary_STATUS_USER_TERMINATED = 14,
    E_METACalibrationLibrary_STATUS_STOP_RF_FAILED = 15,
    E_METACalibrationLibrary_STATUS_READ_NVRAM_FAILED = 16,
    E_METACalibrationLibrary_STATUS_GET_NVRAM_BUFFER_FIELD_FAILED = 17,
    E_METACalibrationLibrary_STATUS_WCDMA_SET_POWER_CONTROL_MODE_FAILED = 18,
    E_METACalibrationLibrary_STATUS_WCDMA_REPLACE_GAIN_TABLE_FAILED = 19,
    E_METACalibrationLibrary_STATUS_WCDMA_GET_CAPABILITY_FAILED = 20,
    E_METACalibrationLibrary_STATUS_WCDMA_SET_PA_DRIFT_COMPENSATION_FAILED = 21,
    E_METACalibrationLibrary_STATUS_NOT_SUPPORTED_MATH_MODE = 22,
    E_METACalibrationLibrary_STATUS_INCONSISTENT_W_CAL_MODE = 23,
    E_METACalibrationLibrary_STATUS_GGE_GET_CAPABILITY_FAILED = 24,
    E_METACalibrationLibrary_STATUS_TESTER_OCCUPY_HANDLE_FAILED = 25,
    E_METACalibrationLibrary_STATUS_TESTER_INITIALIZE_FAILED = 26,
    E_METACalibrationLibrary_STATUS_TESTER_RESET_FAILED = 27,
    E_METACalibrationLibrary_STATUS_TESTER_SWITCH_PORT_FAILED = 28,
    E_METACalibrationLibrary_STATUS_UNEXPECTED_EXCEPTION = 29,
    /***************************************
     * WCDMA START
     **************************************/
    // WCDMA TADC
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_START = 64,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_MEASURE_FAILED = 65,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_GET_NVRAM_RECORD_LENGTH_FAILED = 66,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_COMPOSE_NVRAM_FAILED = 67,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_WRITE_NVRAM_INITIAL_VALUE_FAILED = 68,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_WRITE_NVRAM_CAL_DATA_FAILED = 69,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_INVALID_CURRENT_TEMPERATURE = 70,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_CHECK_START = 71,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_CHECK_FAILED = 72,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_DONE = 73,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_PARSE_CONFIG_FAILED = 74,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_PARSE_INI_FAILED = 75,
    E_METACalibrationLibrary_STATUS_WCDMA_TADC_INVALID_SENSOR_STATUS = 76,
    // WCDMA AFC
    E_METACalibrationLibrary_STATUS_WCDMA_AFC_START = 128,
    E_METACalibrationLibrary_STATUS_WCDMA_AFC_MEASURE_FAILED = 129,
    E_METACalibrationLibrary_STATUS_WCDMA_AFC_CHECK_START = 130,
    E_METACalibrationLibrary_STATUS_WCDMA_AFC_CHECK_FAILED = 131,
    E_METACalibrationLibrary_STATUS_WCDMA_AFC_DONE = 132,
    // WCDMA AGC
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_START = 192,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_CHECK_START = 193,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_DONE = 194,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_MEASURE_FAILED = 195,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_CHECK_HIGH_FAILED = 196,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_CHECK_MID_FAILED = 197,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_CHECK_LOW_FAILED = 198,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_CHECK_LNA_MODE_FAILED = 199,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_WRITE_INIT_VALUE_FAILED = 200,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_WRITE_CAL_DATA_FAILED = 201,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_PARSE_CONFIG_FAILED = 202,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_TESTER_PRESETTING_FAILED = 203,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_TESTER_CHANGE_BAND_FAILED = 204,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_TESTER_CHANGE_CHANNEL_FAILED = 205,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_TESTER_CHANGE_POWER_FAILED = 206,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_GAIN_OFFSET_OVERFLOW = 207,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_SET_GAIN_OFFSET_FAILED = 208,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_SET_ANTENNA_PATH_FAILED = 209,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_GET_TEMP_INFO_FAILED = 210,
    E_METACalibrationLibrary_STATUS_WCDMA_AGC_GET_GAIN_OFFSET_FAILED = 211,
    // WCDMA APC
    E_METACalibrationLibrary_STATUS_WCDMA_APC_START = 256,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_CHECK_START = 257,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_DONE = 258,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_COUPLER_LOSS_OUT_OF_RANGE = 259,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_PA_GAIN_PING_PONG_DETECTED = 260,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_PA_GAIN_CAL_EXCEEDS_MAX_ITERATION = 261,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_PA_SUBBAND_COMPENSATION_OUT_OF_RANGE = 262,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_COUPLER_SUBBAND_COMPENSATION_OUT_OF_RANGE = 263,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_SET_PA_OCT_LEVEL_CONTROL_TO_TARGET_FAILED = 264,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_SET_COMPENSATION_TO_TARGET_FAILED = 265,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_DETECTOR_MEASUREMENT_FAILED = 266,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_DUT_TX_FAILED = 267,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_PA_GAIN_CHECK_FAILED = 268,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_COUPLER_LOSS_CHECK_FAILED = 269,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_PA_SUBBAND_COMPENSATION_CHECK_FAILED = 270,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_COUPLER_LOSS_SUBBAND_COMPENSATION_CHECK_FAILED = 271,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_INIT_TX_MEASUREMENT_FAILED = 272,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_FETCH_TX_MEASUREMENT_FAILED = 273,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_PA_CAL_INIT_TX_MEASUREMENT_FAILED = 274,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_PA_CAL_DUT_TX_FAILED = 275,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_PA_CAL_FETCH_TX_MEASUREMENT_FAILED = 276,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_COUPLER_LOSS_CAL_INIT_TX_MEASUREMENT_FAILED = 277,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_COUPLER_LOSS_CAL_DUT_TX_FAILED = 278,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_COUPLER_LOSS_CAL_FETCH_TX_MEASUREMENT_FAILED = 279,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_SUBBAND_CAL_INIT_TX_MEASUREMENT_FAILED = 280,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_SUBBAND_CAL_DUT_TX_FAILED = 281,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_SUBBAND_CAL_FETCH_TX_MEASUREMENT_FAILED = 282,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_COUPLER_LOSS_CAL_DETECTOR_MEASUREMENT_FAILED = 283,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_SUBBAND_CAL_DETECTOR_MEASUREMENT_FAILED = 284,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_WRITE_INIT_VALUE_FAILED = 285,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_WRITE_CAL_DATA_FAILED = 286,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_PARSE_CONFIG_FAILED = 287,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_TESTER_PRESETTING_FAILED = 288,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_TESTER_CHANGE_BAND_FAILED = 289,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_TESTER_CHANGE_EXPECTED_POWER_IN_PA_GAIN_CAL_FAILED = 290,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_TESTER_CHANGE_EXPECTED_POWER_IN_SUBBAND_CAL_FAILED = 291,
    E_METACalibrationLibrary_STATUS_WCDMA_APC_TESTER_CHANGE_EXPECTED_POWER_IN_COUPLER_LOSS_CAL_FAILED = 292,
    // WCDMA FHC START
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_START = 320,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_START_FAILED = 321,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_QUERY_FAILED = 322,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_CHECK_FAILED = 323,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_DONE = 324,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_AGC_CHECK_HIGH_FAILED = 325,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_AGC_CHECK_MID_FAILED = 326,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_AGC_CHECK_LOW_FAILED = 327,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_AGC_LNA_MODE_CHECK_FAILED = 328,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_APC_PA_GAIN_CHECK_FAILED = 329,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_APC_COUPLER_LOSS_CHECK_FAILED = 330,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_APC_PA_SUBBAND_COMPENSATION_CHECK_FAILED = 331,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_APC_COUPLER_LOSS_SUBBAND_COMPENSATION_CHECK_FAILED = 332,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_AGC_WRITE_INIT_VALUE_FAILED = 333,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_APC_WRITE_INIT_VALUE_FAILED = 334,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_AGC_WRITE_CAL_DATA_FAILED = 335,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_APC_WRITE_CAL_DATA_FAILED = 336,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_AGC_PARSE_CONFIG_FAILED = 337,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_APC_PARSE_CONFIG_FAILED = 338,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_PARSE_CONFIG_FAILED = 339,
    E_METACalibrationLibrary_STATUS_WCDMA_FHC_TESTER_PRESETTING_FAILED = 340,
    // WCDMA NSFT
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_START = 384,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_TARGET_START_FAILED = 385,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_TARGET_STOP_FAILED = 386,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_TX_MEASURE_FAILED = 387,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_BER_MEASURE_FAILED = 388,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_CHECK_FAILED = 389,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_DONE = 390,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_CONFIG_DUT_TPC_ALGO_FAILED = 391,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_TX_TEST_MAX_POWER_FAILED = 392,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_TX_TEST_MIN_POWER_FAILED = 393,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_TX_TEST_ILPC_FAILED = 394,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_BER_TEST_FAILED = 395,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_DUT_OPEN_LOOP_POWER_CONTROL_FAILED = 396,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_DUT_OPEN_LOOP_POWER_TEST_FAILED = 397,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_PARSE_CONFIG_FAILED = 398,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_TESTER_PRESETTING_IN_SYNC_TEST_FAILED = 399,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_TESTER_PRESETTING_IN_PRACH_TEST_FAILED = 400,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_TESTER_TESTCASE_SETTING_IN_SYNC_TEST_FAILED = 401,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_TESTER_TESTCASE_SETTING_IN_PRACH_TEST_FAILED = 402,
    E_METACalibrationLibrary_STATUS_WCDMA_NSFT_NOT_SUPPORTED_BAND = 403,
    // WCDMA HSDPA NSFT
    E_METACalibrationLibrary_STATUS_WCDMA_HSDPA_NSFT_START = 448,
    E_METACalibrationLibrary_STATUS_WCDMA_HSDPA_NSFT_TARGET_START_FAILED = 449,
    E_METACalibrationLibrary_STATUS_WCDMA_HSDPA_NSFT_TARGET_STOP_FAILED = 450,
    E_METACalibrationLibrary_STATUS_WCDMA_HSDPA_NSFT_TX_MEASURE_FAILED = 451,
    E_METACalibrationLibrary_STATUS_WCDMA_HSDPA_NSFT_CHECK_FAILED = 452,
    E_METACalibrationLibrary_STATUS_WCDMA_HSDPA_NSFT_DONE = 453,
    // WCDMA HSUPA NSFT
    E_METACalibrationLibrary_STATUS_WCDMA_HSUPA_NSFT_START = 512,
    E_METACalibrationLibrary_STATUS_WCDMA_HSUPA_NSFT_TARGET_START_FAILED = 513,
    E_METACalibrationLibrary_STATUS_WCDMA_HSUPA_NSFT_TARGET_STOP_FAILED = 514,
    E_METACalibrationLibrary_STATUS_WCDMA_HSUPA_NSFT_TX_MEASURE_FAILED = 515,
    E_METACalibrationLibrary_STATUS_WCDMA_HSUPA_NSFT_CHECK_FAILED = 516,
    E_METACalibrationLibrary_STATUS_WCDMA_HSUPA_NSFT_DONE = 517,
    // WCDMA DCXO AFC
    E_METACalibrationLibrary_STATUS_WCDMA_DCXO_AFC_START = 576,
    E_METACalibrationLibrary_STATUS_WCDMA_DCXO_AFC_DONE = 577,
    E_METACalibrationLibrary_STATUS_WCDMA_DCXO_AFC_CHECK_FAILED = 578,
    E_METACalibrationLibrary_STATUS_WCDMA_DCXO_AFC_MEASURE_FAILED = 579,
    E_METACalibrationLibrary_STATUS_WCDMA_DCXO_AFC_GET_MAX_CAPID_FAILED = 580,
    E_METACalibrationLibrary_STATUS_WCDMA_DCXO_AFC_BINARY_SEARCH_FAILED = 581,
    E_METACalibrationLibrary_STATUS_WCDMA_DCXO_AFC_SET_CAPID_FAILED = 582,
    /***************************************
     * WCDMA END
     **************************************/
    /***************************************
     * TDSCDMA (AST) END
     **************************************/
    E_METACalibrationLibrary_STATUS_TDSCDMA_INIT_RF_FAILED = 640,
    E_METACalibrationLibrary_STATUS_TDSCDMA_DUT_CONTROL_FAILED = 641,
    E_METACalibrationLibrary_STATUS_TDSCDMA_LOAD_LIBRARY_FAILED = 642,
    E_METACalibrationLibrary_STATUS_TDSCDMA_GET_CAPABILITY_FAILED = 643,
    // TD Temp. ADC
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_START = 704,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_MEASURE_FAILED = 705,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_GET_NVRAM_RECORD_LENGTH_FAILED = 706,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_COMPOSE_NVRAM_FAILED = 707,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_WRITE_NVRAM_INITIAL_VALUE_FAILED = 708,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_WRITE_NVRAM_CAL_DATA_FAILED = 709,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_INVALID_CURRENT_TEMPERATURE = 710,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_CHECK_START = 711,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_CHECK_FAILED = 712,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_DONE = 713,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_PARSE_CONFIG_FAILED = 714,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_PARSE_INI_FAILED = 715,
    E_METACalibrationLibrary_STATUS_TDSCDMA_TADC_INVALID_SENSOR_STATUS = 716,
    // TD AFC
    E_METACalibrationLibrary_STATUS_TDSCDMA_AFC_START = 768,
    E_METACalibrationLibrary_STATUS_TDSCDMA_AFC_MEASURE_FAILED = 769,
    E_METACalibrationLibrary_STATUS_TDSCDMA_AFC_CHECK_START = 770,
    E_METACalibrationLibrary_STATUS_TDSCDMA_AFC_CHECK_FAILED = 771,
    E_METACalibrationLibrary_STATUS_TDSCDMA_AFC_DONE = 772,
    // TD AGC
    E_METACalibrationLibrary_STATUS_TDSCDMA_AGC_START = 832,
    E_METACalibrationLibrary_STATUS_TDSCDMA_AGC_MEASURE_FAILED = 833,
    E_METACalibrationLibrary_STATUS_TDSCDMA_AGC_CHECK_START = 834,
    E_METACalibrationLibrary_STATUS_TDSCDMA_AGC_CHECK_FAILED = 835,
    E_METACalibrationLibrary_STATUS_TDSCDMA_AGC_DONE = 836,
    E_METACalibrationLibrary_STATUS_TDSCDMA_AGC_PARSE_CONFIG_FAILED = 837,
    E_METACalibrationLibrary_STATUS_TDSCDMA_AGC_PARSE_INI_FAILED = 838,
    // TD APC
    E_METACalibrationLibrary_STATUS_TDSCDMA_APC_START = 869,
    E_METACalibrationLibrary_STATUS_TDSCDMA_APC_MEASURE_FAILED = 870,
    E_METACalibrationLibrary_STATUS_TDSCDMA_APC_CHECK_START = 871,
    E_METACalibrationLibrary_STATUS_TDSCDMA_APC_CHECK_FAILED = 872,
    E_METACalibrationLibrary_STATUS_TDSCDMA_APC_INVALID_PA_MODE_CAL_NUM = 873,
    E_METACalibrationLibrary_STATUS_TDSCDMA_APC_DONE = 874,
    E_METACalibrationLibrary_STATUS_TDSCDMA_APC_PD_MEASURE_FAILED = 875,
    // TD NSFT
    E_METACalibrationLibrary_STATUS_TDSCDMA_NSFT_START = 960,
    E_METACalibrationLibrary_STATUS_TDSCDMA_NSFT_TARGET_START_FAILED = 961,
    E_METACalibrationLibrary_STATUS_TDSCDMA_NSFT_TARGET_STOP_FAILED = 962,
    E_METACalibrationLibrary_STATUS_TDSCDMA_NSFT_TX_MEASURE_FAILED = 963,
    E_METACalibrationLibrary_STATUS_TDSCDMA_NSFT_BER_MEASURE_FAILED = 964,
    E_METACalibrationLibrary_STATUS_TDSCDMA_NSFT_CHECK_FAILED = 965,
    E_METACalibrationLibrary_STATUS_TDSCDMA_NSFT_RSCP_MEASURE_FAILED = 966,
    E_METACalibrationLibrary_STATUS_TDSCDMA_NSFT_DONE = 967,
    E_METACalibrationLibrary_STATUS_TDSCDMA_FT_START = 968,
    E_METACalibrationLibrary_STATUS_TDSCDMA_FT_DONE = 969,
    E_METACalibrationLibrary_STATUS_TDSCDMA_FT_CHECK_FAILED = 970,
    // TD FHC
    E_METACalibrationLibrary_STATUS_TDSCDMA_FHC_START = 1024,
    E_METACalibrationLibrary_STATUS_TDSCDMA_FHC_START_FAILED = 1025,
    E_METACalibrationLibrary_STATUS_TDSCDMA_FHC_QUERY_FAILED = 1026,
    E_METACalibrationLibrary_STATUS_TDSCDMA_FHC_CHECK_FAILED = 1027,
    E_METACalibrationLibrary_STATUS_TDSCDMA_FHC_DONE = 1028,
    // TD CAP ID
    E_METACalibrationLibrary_STATUS_TDSCDMA_CAP_ID_START = 1088,
    E_METACalibrationLibrary_STATUS_TDSCDMA_CAP_ID_DONE = 1089,
    E_METACalibrationLibrary_STATUS_TDSCDMA_CAP_CHECK_FAILED = 1090,
    /***************************************
     * TDSCDMA (AST) END
     **************************************/
    /***************************************
     * GSM START
     **************************************/
    // GSM AFC
    E_METACalibrationLibrary_STATUS_GSM_AFC_START = 1152,
    E_METACalibrationLibrary_STATUS_GSM_AFC_MEASURE_FAILED = 1153,
    E_METACalibrationLibrary_STATUS_GSM_AFC_CHECK_START = 1154,
    E_METACalibrationLibrary_STATUS_GSM_AFC_CHECK_FAILED = 1155,
    E_METACalibrationLibrary_STATUS_GSM_AFC_DONE = 1156,
    E_METACalibrationLibrary_STATUS_GSM_AFC_GET_CAPIBILITY3_FAILED = 1157,
    E_METACalibrationLibrary_STATUS_GSM_AFC_GET_TD_LID_LEN_FAILED = 1158,
    E_METACalibrationLibrary_STATUS_GSM_AFC_COMPOSE_TD_FAILED = 1159,
    E_METACalibrationLibrary_STATUS_GSM_AFC_LOW_HIGH_BAND_SWITCH_FAILED = 1160,
    // GSM AGC
    E_METACalibrationLibrary_STATUS_GSM_AGC_START = 1216,
    E_METACalibrationLibrary_STATUS_GSM_AGC_CHECK_START = 1217,
    E_METACalibrationLibrary_STATUS_GSM_AGC_DONE = 1218,
    E_METACalibrationLibrary_STATUS_GSM_AGC_MEASURE_FAILED = 1219,
    E_METACalibrationLibrary_STATUS_GSM_AGC_CHECK_HIGH_FAILED = 1220,
    E_METACalibrationLibrary_STATUS_GSM_AGC_CHECK_MID_FAILED = 1221,
    E_METACalibrationLibrary_STATUS_GSM_AGC_CHECK_LOW_FAILED = 1222,
    E_METACalibrationLibrary_STATUS_GSM_AGC_CHECK_LNA_MODE_FAILED = 1223,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WRITE_CAL_DATA_FAILED = 1224,
    E_METACalibrationLibrary_STATUS_GSM_AGC_PARSE_INIT_FAILED = 1225,
    E_METACalibrationLibrary_STATUS_GSM_AGC_PARSE_CONFIG_FAILED = 1226,
    E_METACalibrationLibrary_STATUS_GSM_AGC_TESTER_PRESETTING_FAILED = 1227,
    E_METACalibrationLibrary_STATUS_GSM_AGC_TESTER_CHANGE_BAND_FAILED = 1228,
    E_METACalibrationLibrary_STATUS_GSM_AGC_TESTER_CHANGE_CHANNEL_FAILED = 1229,
    E_METACalibrationLibrary_STATUS_GSM_AGC_TESTER_CHANGE_POWER_FAILED = 1230,
    E_METACalibrationLibrary_STATUS_GSM_AGC_GAIN_OFFSET_OVERFLOW = 1231,
    E_METACalibrationLibrary_STATUS_GSM_AGC_LOW_HIGH_BAND_SWITCH_FAILED = 1232,
    // GSM APC
    E_METACalibrationLibrary_STATUS_GSM_APC_START = 1280,
    E_METACalibrationLibrary_STATUS_GSM_APC_CHECK_START = 1281,
    E_METACalibrationLibrary_STATUS_GSM_APC_DONE = 1282,
    E_METACalibrationLibrary_STATUS_GSM_APC_COUPLER_LOSS_OUT_OF_RANGE = 1283,
    E_METACalibrationLibrary_STATUS_GSM_APC_PA_GAIN_PING_PONG_DETECTED = 1284,
    E_METACalibrationLibrary_STATUS_GSM_APC_PA_GAIN_CAL_EXCEEDS_MAX_ITERATION = 1285,
    E_METACalibrationLibrary_STATUS_GSM_APC_PA_SUBBAND_COMPENSATION_OUT_OF_RANGE = 1286,
    E_METACalibrationLibrary_STATUS_GSM_APC_COUPLER_SUBBAND_COMPENSATION_OUT_OF_RANGE = 1287,
    E_METACalibrationLibrary_STATUS_GSM_APC_SET_PA_OCT_LEVEL_CONTROL_TO_TARGET_FAILED = 1288,
    E_METACalibrationLibrary_STATUS_GSM_APC_SET_COMPENSATION_TO_TARGET_FAILED = 1289,
    E_METACalibrationLibrary_STATUS_GSM_APC_DETECTOR_MEASUREMENT_FAILED = 1290,
    E_METACalibrationLibrary_STATUS_GSM_APC_DUT_TX_FAILED = 1291,
    E_METACalibrationLibrary_STATUS_GSM_APC_PA_GAIN_CHECK_FAILED = 1292,
    E_METACalibrationLibrary_STATUS_GSM_APC_COUPLER_LOSS_CHECK_FAILED = 1293,
    E_METACalibrationLibrary_STATUS_GSM_APC_PA_SUBBAND_COMPENSATION_CHECK_FAILED = 1294,
    E_METACalibrationLibrary_STATUS_GSM_APC_COUPLER_LOSS_SUBBAND_COMPENSATION_CHECK_FAILED = 1295,
    E_METACalibrationLibrary_STATUS_GSM_APC_INIT_TX_MEASUREMENT_FAILED = 1296,
    E_METACalibrationLibrary_STATUS_GSM_APC_FETCH_TX_MEASUREMENT_FAILED = 1297,
    E_METACalibrationLibrary_STATUS_GSM_APC_PA_CAL_INIT_TX_MEASUREMENT_FAILED = 1298,
    E_METACalibrationLibrary_STATUS_GSM_APC_PA_CAL_DUT_TX_FAILED = 1299,
    E_METACalibrationLibrary_STATUS_GSM_APC_PA_CAL_FETCH_TX_MEASUREMENT_FAILED = 1300,
    E_METACalibrationLibrary_STATUS_GSM_APC_COUPLER_LOSS_CAL_INIT_TX_MEASUREMENT_FAILED = 1301,
    E_METACalibrationLibrary_STATUS_GSM_APC_COUPLER_LOSS_CAL_DUT_TX_FAILED = 1302,
    E_METACalibrationLibrary_STATUS_GSM_APC_COUPLER_LOSS_CAL_FETCH_TX_MEASUREMENT_FAILED = 1303,
    E_METACalibrationLibrary_STATUS_GSM_APC_SUBBAND_CAL_INIT_TX_MEASUREMENT_FAILED = 1304,
    E_METACalibrationLibrary_STATUS_GSM_APC_SUBBAND_CAL_DUT_TX_FAILED = 1305,
    E_METACalibrationLibrary_STATUS_GSM_APC_SUBBAND_CAL_FETCH_TX_MEASUREMENT_FAILED = 1306,
    E_METACalibrationLibrary_STATUS_GSM_APC_COUPLER_LOSS_CAL_DETECTOR_MEASUREMENT_FAILED = 1307,
    E_METACalibrationLibrary_STATUS_GSM_APC_SUBBAND_CAL_DETECTOR_MEASUREMENT_FAILED = 1308,
    E_METACalibrationLibrary_STATUS_GSM_APC_WRITE_INIT_VALUE_FAILED = 1309,
    E_METACalibrationLibrary_STATUS_GSM_APC_WRITE_CAL_DATA_FAILED = 1310,
    E_METACalibrationLibrary_STATUS_GSM_APC_PARSE_CONFIG_FAILED = 1311,
    E_METACalibrationLibrary_STATUS_GSM_APC_TESTER_PRESETTING_FAILED = 1312,
    E_METACalibrationLibrary_STATUS_GSM_APC_TESTER_CHANGE_BAND_FAILED = 1313,
    E_METACalibrationLibrary_STATUS_GSM_APC_TESTER_CHANGE_EXPECTED_POWER_IN_PA_GAIN_CAL_FAILED = 1314,
    E_METACalibrationLibrary_STATUS_GSM_APC_TESTER_CHANGE_EXPECTED_POWER_IN_SUBBAND_CAL_FAILED = 1315,
    E_METACalibrationLibrary_STATUS_GSM_APC_TESTER_CHANGE_EXPECTED_POWER_IN_COUPLER_LOSS_CAL_FAILED = 1316,
    E_METACalibrationLibrary_STATUS_GSM_APC_LOW_HIGH_BAND_SWITCH_FAILED = 1317,
    E_METACalibrationLibrary_STATUS_GSM_APC_POWER_CHECK_FAILED = 1318,
    E_METACalibrationLibrary_STATUS_GSM_APC_POWER_CAL_EXCEEDS_MAX_ITERATION = 1319,
    E_METACalibrationLibrary_STATUS_GSM_APC_SET_PCL_DAC_TO_TARGET_FAILED = 1320,
    E_METACalibrationLibrary_STATUS_GSM_APC_GET_TEMP_INFO_FAILED = 1321,
    E_METACalibrationLibrary_STATUS_GSM_APC_MEASUREMENT_STEP_EXCEED_MAXIMUM = 1322,
    // GSM High Speed APC
    E_METACalibrationLibrary_STATUS_GSM_OGPC_APC_START = 1344,
    E_METACalibrationLibrary_STATUS_GSM_OGPC_APC_DONE = 1345,
    E_METACalibrationLibrary_STATUS_GSM_OGPC_CSYPP_FAILED = 1346,
    E_METACalibrationLibrary_STATUS_GSM_OGPC_CSINT_FAILED = 1347,
    E_METACalibrationLibrary_STATUS_GSM_OGPC_LINEAR_INT_FAILED = 1348,
    // GSM APC DC offset
    E_METACalibrationLibrary_STATUS_GSM_APC_DC_OFFSET_START = 1408,
    E_METACalibrationLibrary_STATUS_GSM_APC_DC_OFFSET_DONE = 1409,
    E_METACalibrationLibrary_STATUS_GSM_APC_DC_OFFSET_INIT_FAILED = 1410,
    E_METACalibrationLibrary_STATUS_GSM_APC_DC_OFFSET_CONFIG_FAILED = 1411,
    E_METACalibrationLibrary_STATUS_GSM_APC_DC_OFFSET_WRITE_CAL_FAILED = 1412,
    E_METACalibrationLibrary_STATUS_GSM_APC_DC_OFFSET_POWER_CHECK_FAILED = 1413,
    E_METACalibrationLibrary_STATUS_GSM_APC_DC_OFFSET_LOW_HIGH_BAND_SWITCH_FAILED = 1414,
    // EDGE APC
    E_METACalibrationLibrary_STATUS_EDGE_APC_START = 1472,
    E_METACalibrationLibrary_STATUS_EDGE_APC_CHECK_START = 1473,
    E_METACalibrationLibrary_STATUS_EDGE_APC_DONE = 1474,
    E_METACalibrationLibrary_STATUS_EDGE_APC_COUPLER_LOSS_OUT_OF_RANGE = 1475,
    E_METACalibrationLibrary_STATUS_EDGE_APC_PA_GAIN_PING_PONG_DETECTED = 1476,
    E_METACalibrationLibrary_STATUS_EDGE_APC_PA_GAIN_CAL_EXCEEDS_MAX_ITERATION = 1477,
    E_METACalibrationLibrary_STATUS_EDGE_APC_PA_SUBBAND_COMPENSATION_OUT_OF_RANGE = 1478,
    E_METACalibrationLibrary_STATUS_EDGE_APC_COUPLER_SUBBAND_COMPENSATION_OUT_OF_RANGE = 1479,
    E_METACalibrationLibrary_STATUS_EDGE_APC_SET_PA_OCT_LEVEL_CONTROL_TO_TARGET_FAILED = 1480,
    E_METACalibrationLibrary_STATUS_EDGE_APC_SET_COMPENSATION_TO_TARGET_FAILED = 1481,
    E_METACalibrationLibrary_STATUS_EDGE_APC_DETECTOR_MEASUREMENT_FAILED = 1482,
    E_METACalibrationLibrary_STATUS_EDGE_APC_DUT_TX_FAILED = 1483,
    E_METACalibrationLibrary_STATUS_EDGE_APC_PA_GAIN_CHECK_FAILED = 1484,
    E_METACalibrationLibrary_STATUS_EDGE_APC_COUPLER_LOSS_CHECK_FAILED = 1485,
    E_METACalibrationLibrary_STATUS_EDGE_APC_PA_SUBBAND_COMPENSATION_CHECK_FAILED = 1486,
    E_METACalibrationLibrary_STATUS_EDGE_APC_COUPLER_LOSS_SUBBAND_COMPENSATION_CHECK_FAILED = 1487,
    E_METACalibrationLibrary_STATUS_EDGE_APC_INIT_TX_MEASUREMENT_FAILED = 1488,
    E_METACalibrationLibrary_STATUS_EDGE_APC_FETCH_TX_MEASUREMENT_FAILED = 1489,
    E_METACalibrationLibrary_STATUS_EDGE_APC_PA_CAL_INIT_TX_MEASUREMENT_FAILED = 1490,
    E_METACalibrationLibrary_STATUS_EDGE_APC_PA_CAL_DUT_TX_FAILED = 1491,
    E_METACalibrationLibrary_STATUS_EDGE_APC_PA_CAL_FETCH_TX_MEASUREMENT_FAILED = 1492,
    E_METACalibrationLibrary_STATUS_EDGE_APC_COUPLER_LOSS_CAL_INIT_TX_MEASUREMENT_FAILED = 1493,
    E_METACalibrationLibrary_STATUS_EDGE_APC_COUPLER_LOSS_CAL_DUT_TX_FAILED = 1494,
    E_METACalibrationLibrary_STATUS_EDGE_APC_COUPLER_LOSS_CAL_FETCH_TX_MEASUREMENT_FAILED = 1495,
    E_METACalibrationLibrary_STATUS_EDGE_APC_SUBBAND_CAL_INIT_TX_MEASUREMENT_FAILED = 1496,
    E_METACalibrationLibrary_STATUS_EDGE_APC_SUBBAND_CAL_DUT_TX_FAILED = 1497,
    E_METACalibrationLibrary_STATUS_EDGE_APC_SUBBAND_CAL_FETCH_TX_MEASUREMENT_FAILED = 1498,
    E_METACalibrationLibrary_STATUS_EDGE_APC_COUPLER_LOSS_CAL_DETECTOR_MEASUREMENT_FAILED = 1499,
    E_METACalibrationLibrary_STATUS_EDGE_APC_SUBBAND_CAL_DETECTOR_MEASUREMENT_FAILED = 1500,
    E_METACalibrationLibrary_STATUS_EDGE_APC_WRITE_INIT_VALUE_FAILED = 1501,
    E_METACalibrationLibrary_STATUS_EDGE_APC_WRITE_CAL_DATA_FAILED = 1502,
    E_METACalibrationLibrary_STATUS_EDGE_APC_PARSE_CONFIG_FAILED = 1503,
    E_METACalibrationLibrary_STATUS_EDGE_APC_TESTER_PRESETTING_FAILED = 1504,
    E_METACalibrationLibrary_STATUS_EDGE_APC_TESTER_CHANGE_BAND_FAILED = 1505,
    E_METACalibrationLibrary_STATUS_EDGE_APC_TESTER_CHANGE_EXPECTED_POWER_IN_PA_GAIN_CAL_FAILED = 1506,
    E_METACalibrationLibrary_STATUS_EDGE_APC_TESTER_CHANGE_EXPECTED_POWER_IN_SUBBAND_CAL_FAILED = 1507,
    E_METACalibrationLibrary_STATUS_EDGE_APC_TESTER_CHANGE_EXPECTED_POWER_IN_COUPLER_LOSS_CAL_FAILED = 1508,
    E_METACalibrationLibrary_STATUS_EDGE_APC_LOW_HIGH_BAND_SWITCH_FAILED = 1509,
    E_METACalibrationLibrary_STATUS_EDGE_APC_POWER_CHECK_FAILED = 1510,
    E_METACalibrationLibrary_STATUS_EDGE_APC_POWER_CAL_EXCEEDS_MAX_ITERATION = 1511,
    E_METACalibrationLibrary_STATUS_EDGE_APC_SET_PCL_DAC_TO_TARGET_FAILED = 1512,
    E_METACalibrationLibrary_STATUS_EDGE_APC_GAIN_RF_QUERY_NUM_OF_GAIN_RF_FAILED = 1513,
    E_METACalibrationLibrary_STATUS_EDGE_APC_GAIN_RF_QUERY_BB_POWER_FAILED = 1514,
    E_METACalibrationLibrary_STATUS_EDGE_APC_GAIN_RF_START = 1515,
    E_METACalibrationLibrary_STATUS_EDGE_APC_GAIN_RF_DONE = 1516,
    // EDGE High Speed APC
    E_METACalibrationLibrary_STATUS_EDGE_OGPC_APC_START = 1536,
    E_METACalibrationLibrary_STATUS_EDGE_OGPC_APC_DONE = 1537,
    E_METACalibrationLibrary_STATUS_EDGE_OGPC_CSYPP_FAILED = 1538,
    E_METACalibrationLibrary_STATUS_EDGE_OGPC_CSINT_FAILED = 1539,
    E_METACalibrationLibrary_STATUS_EDGE_OGPC_LINEAR_INT_FAILED = 1540,
    // EDGE 6140 APC
    E_METACalibrationLibrary_STATUS_EDGE_6140_APC_START = 1600,
    E_METACalibrationLibrary_STATUS_EDGE_6140_APC_DONE = 1601,
    E_METACalibrationLibrary_STATUS_EDGE_6140_GET_ITC_PCL_FAILED = 1602,
    E_METACalibrationLibrary_STATUS_EDGE_6140_FHC_EVALUATE_FAILED = 1603,
    // GSM FHC START
    E_METACalibrationLibrary_STATUS_GSM_FHC_START = 1664,
    E_METACalibrationLibrary_STATUS_GSM_FHC_START_FAILED = 1665,
    E_METACalibrationLibrary_STATUS_GSM_FHC_QUERY_FAILED = 1666,
    E_METACalibrationLibrary_STATUS_GSM_FHC_CHECK_FAILED = 1667,
    E_METACalibrationLibrary_STATUS_GSM_FHC_DONE = 1668,
    E_METACalibrationLibrary_STATUS_GSM_FHC_AGC_CHECK_HIGH_FAILED = 1669,
    E_METACalibrationLibrary_STATUS_GSM_FHC_AGC_CHECK_MID_FAILED = 1670,
    E_METACalibrationLibrary_STATUS_GSM_FHC_AGC_CHECK_LOW_FAILED = 1671,
    E_METACalibrationLibrary_STATUS_GSM_FHC_AGC_LNA_MODE_CHECK_FAILED = 1672,
    E_METACalibrationLibrary_STATUS_GSM_FHC_APC_PA_GAIN_CHECK_FAILED = 1673,
    E_METACalibrationLibrary_STATUS_GSM_FHC_APC_COUPLER_LOSS_CHECK_FAILED = 1674,
    E_METACalibrationLibrary_STATUS_GSM_FHC_APC_PA_SUBBAND_COMPENSATION_CHECK_FAILED = 1675,
    E_METACalibrationLibrary_STATUS_GSM_FHC_APC_COUPLER_LOSS_SUBBAND_COMPENSATION_CHECK_FAILED = 1676,
    E_METACalibrationLibrary_STATUS_GSM_FHC_AGC_WRITE_INIT_VALUE_FAILED = 1677,
    E_METACalibrationLibrary_STATUS_GSM_FHC_APC_WRITE_INIT_VALUE_FAILED = 1678,
    E_METACalibrationLibrary_STATUS_GSM_FHC_AGC_WRITE_CAL_DATA_FAILED = 1679,
    E_METACalibrationLibrary_STATUS_GSM_FHC_APC_WRITE_CAL_DATA_FAILED = 1680,
    E_METACalibrationLibrary_STATUS_GSM_FHC_AGC_PARSE_CONFIG_FAILED = 1681,
    E_METACalibrationLibrary_STATUS_GSM_FHC_APC_PARSE_CONFIG_FAILED = 1682,
    E_METACalibrationLibrary_STATUS_GSM_FHC_PARSE_CONFIG_FAILED = 1683,
    E_METACalibrationLibrary_STATUS_GSM_FHC_TESTER_PRESETTING_FAILED = 1684,
    E_METACalibrationLibrary_STATUS_GSM_FHC_AFC_CHECK_FAILED = 1685,
    // GSM NSFT
    E_METACalibrationLibrary_STATUS_GSM_NSFT_START = 1728,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_TARGET_START_FAILED = 1729,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_TARGET_STOP_FAILED = 1730,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_TX_MEASURE_FAILED = 1731,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_BER_MEASURE_FAILED = 1732,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_CHECK_FAILED = 1733,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_DONE = 1734,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_CONFIG_DUT_TPC_ALGO_FAILED = 1735,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_TX_TEST_MAX_POWER_FAILED = 1736,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_TX_TEST_MIN_POWER_FAILED = 1737,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_TX_TEST_ILPC_FAILED = 1738,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_BER_TEST_FAILED = 1739,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_DUT_OPEN_LOOP_POWER_CONTROL_FAILED = 1740,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_DUT_OPEN_LOOP_POWER_TEST_FAILED = 1741,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_PARSE_CONFIG_FAILED = 1742,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_TESTER_PRESETTING_IN_SYNC_TEST_FAILED = 1743,
    E_METACalibrationLibrary_STATUS_GSM_NSFT_TESTER_PRESETTING_IN_PRACH_TEST_FAILED = 1744,
    E_METACalibrationLibrary_STATUS_GSM_EDGE_NSFT_TARGET_START_FAILED = 1745,
    E_METACalibrationLibrary_STATUS_GSM_EDGE_NSFT_TX_MEASURE_FAILED = 1746,
    E_METACalibrationLibrary_STATUS_GSM_EDGE_NSFT_START = 1747,
    E_METACalibrationLibrary_STATUS_GSM_EDGE_NSFT_DONE = 1748,
    // GSM NSFT list mode
    E_METACalibrationLibrary_STATUS_GSM_EDGE_LIST_MODE_NSFT_PARSE_CONFIG_FAILED = 1749,
    E_METACalibrationLibrary_STATUS_GSM_EDGE_LIST_MODE_NSFT_PARSE_TEST_CASE_FAILED = 1750,
    E_METACalibrationLibrary_STATUS_GGE_LIST_MODE_NSFT_TESTER_PRESETTING_FAILED = 1751,
    E_METACalibrationLibrary_STATUS_GSM_EDGE_LIST_MODE_NSFT_START_FAILED = 1752,
    E_METACalibrationLibrary_STATUS_GSM_EDGE_LIST_MODE_NSFT_FETCH_RESULT_FAILED = 1753,
    E_METACalibrationLibrary_STATUS_GGE_LIST_MODE_NSFT_CHECK_RESULT_FAILED = 1754,

    // GSM CAP ID
    E_METACalibrationLibrary_STATUS_GSM_CAP_ID_START = 1792,
    E_METACalibrationLibrary_STATUS_GSM_CAP_ID_DONE = 1793,
    E_METACalibrationLibrary_STATUS_GSM_CAP_ID_CHECK_FAILED = 1794,
    E_METACalibrationLibrary_STATUS_GSM_CAP_ID_BAND_SELECT_FAILED = 1795,
    E_METACalibrationLibrary_STATUS_GSM_CAP_ID_NB_TX_FAILED = 1796,
    E_METACalibrationLibrary_STATUS_GSM_CAP_ID_DYNAMIC_RANGE_CHECK_FAILED = 1797,
    E_METACalibrationLibrary_STATUS_GSM_CAP_ID_GET_CENTER_FREQUENCY_FAILED = 1798,
    E_METACalibrationLibrary_STATUS_GSM_CAP_GET_CAPIBILITY3_FAILED = 1799,
    E_METACalibrationLibrary_STATUS_GSM_CAP_GET_TD_LID_LEN_FAILED = 1800,
    E_METACalibrationLibrary_STATUS_GSM_CAP_COMPOSE_TD_FAILED = 1801,
    // GGE TADC
    E_METACalibrationLibrary_STATUS_GGE_TADC_START = 1856,
    E_METACalibrationLibrary_STATUS_GGE_TADC_MEASURE_FAILED = 1857,
    E_METACalibrationLibrary_STATUS_GGE_TADC_GET_NVRAM_RECORD_LENGTH_FAILED = 1858,
    E_METACalibrationLibrary_STATUS_GGE_TADC_COMPOSE_NVRAM_FAILED = 1859,
    E_METACalibrationLibrary_STATUS_GGE_TADC_WRITE_NVRAM_INITIAL_VALUE_FAILED = 1860,
    E_METACalibrationLibrary_STATUS_GGE_TADC_WRITE_NVRAM_CAL_DATA_FAILED = 1861,
    E_METACalibrationLibrary_STATUS_GGE_TADC_INVALID_CURRENT_TEMPERATURE = 1862,
    E_METACalibrationLibrary_STATUS_GGE_TADC_CHECK_START = 1863,
    E_METACalibrationLibrary_STATUS_GGE_TADC_CHECK_FAILED = 1864,
    E_METACalibrationLibrary_STATUS_GGE_TADC_DONE = 1865,
    E_METACalibrationLibrary_STATUS_GGE_TADC_PARSE_CONFIG_FAILED = 1866,
    E_METACalibrationLibrary_STATUS_GGE_TADC_PARSE_INI_FAILED = 1867,
    E_METACalibrationLibrary_STATUS_GGE_TADC_INVALID_SENSOR_STATUS = 1868,
    // GGE DCXO LOW POWER
    E_METACalibrationLibrary_STATUS_GGE_DCXO_LPM_CAL_NB_TX_FAILED = 1920,
    E_METACalibrationLibrary_STATUS_GGE_DCXO_LPM_CAL_SET_FREQUENCY_BAND_FAILED = 1921,
    E_METACalibrationLibrary_STATUS_GGE_DCXO_LPM_CAL_SET_POWER_MODE_FAILED = 1922,
    E_METACalibrationLibrary_STATUS_GGE_DCXO_LPM_CAL_CHECK_FAILED = 1923,
    //GSM APC AD6546 (FB DAC & Slope Skew)
    E_METACalibrationLibrary_STATUS_GSM_APC_AD6546_START = 1984,
    E_METACalibrationLibrary_STATUS_GSM_APC_AD6546_DONE = 1985,
    E_METACalibrationLibrary_STATUS_GSM_APC_AD6546_SET_SPEC_COEF_FAILED = 1986,
    E_METACalibrationLibrary_STATUS_GSM_APC_AD6546_SET_APC_RAMP_LEVEL_FAILED = 1987,
    E_METACalibrationLibrary_STATUS_GSM_APC_AD6546_WRITE_CAL_DATA_FAILED = 1988,
    E_METACalibrationLibrary_STATUS_GSM_APC_AD6546_GET_SEP_CH_FAILED = 1989,
    E_METACalibrationLibrary_STATUS_GSM_APC_AD6546_REQ_RF_START_FAILED = 1990,
    E_METACalibrationLibrary_STATUS_GSM_APC_AD6546_SLOPE_SKEW_CHECK_FAILED = 1991,
    E_METACalibrationLibrary_STATUS_GSM_APC_AD6546_MULTI_SLOT_SUPPORT_FAILED = 1992,
    //GSM AFC (Crystal TX Afc Offset)
    E_METACalibrationLibrary_STATUS_GSM_AFC_TRXOFFSET_START = 2048,
    E_METACalibrationLibrary_STATUS_GSM_AFC_TRXOFFSET_DONE = 2049,
    E_METACalibrationLibrary_STATUS_GSM_AFC_TRXOFFSET_SLOPE_FAILED = 2050,
    E_METACalibrationLibrary_STATUS_GSM_AFC_TRXOFFSET_NB_TX_FAILED = 2051,
    E_METACalibrationLibrary_STATUS_GSM_AFC_TRXOFFSET_COUNT_LIMIT_FAILED = 2052,
    E_METACalibrationLibrary_STATUS_GSM_AFC_TRXOFFSET_TXOFFSET_FAILED = 2053,
    //GSM TX IQ Calibration
    E_METACalibrationLibrary_STATUS_GSM_TXIQ_START = 2112,
    E_METACalibrationLibrary_STATUS_GSM_TXIQ_DONE = 2113,
    E_METACalibrationLibrary_STATUS_GSM_TXIQ_GET_RFID_FAILED = 2114,
    E_METACalibrationLibrary_STATUS_GSM_TXIQ_GET_BBTX_CFG_FAILED = 2115,
    E_METACalibrationLibrary_STATUS_GSM_TXIQ_CAL_FAILED = 2116,
    E_METACalibrationLibrary_STATUS_GSM_TXIQ_MULTI_SLOT_SUPPORT_FAILED = 2117,
    E_METACalibrationLibrary_STATUS_GSM_TXIQ_GET_MSCAPABILITY_FAILED = 2118,
    // GSM AGC W coefficient
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_START = 2176,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_DONE = 2177,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_GET_FAILED = 2178,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_GET_LID_VERSION_FAILED = 2179,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_LID_VERSION_NOT_SUPPORT = 2180,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_COMPOSE_FAILED = 2181,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_GET_RUNTIME_FAILED = 2182,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_SELECT_BAND_FAILED = 2183,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_SEND_PM_FAILED = 2184,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_RETRY_FAILED = 2185,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_SET_DTS_FAILED = 2186,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_SET_MS_FAILED = 2187,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_PARSE_INIT_FAILED = 2188,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_PARSE_CONFIG_FAILED = 2189,
    E_METACalibrationLibrary_STATUS_GSM_AGC_WCoef_WRITE_CAL_FAILED = 2190,
    // EDGE TX TEST
    E_METACalibrationLibrary_STATUS_EDGE_TX_TEST_START = 2240,
    E_METACalibrationLibrary_STATUS_EDGE_TX_TEST_DONE = 2241,
    E_METACalibrationLibrary_STATUS_EDGE_TX_TEST_TESTER_PRESETTING_FAILED = 2242,
    E_METACalibrationLibrary_STATUS_EDGE_TX_TEST_DUT_TX_FAILED = 2243,
    E_METACalibrationLibrary_STATUS_EDGE_TX_TEST_FETCH_TX_MEASUREMENT_FAILED = 2244,
    E_METACalibrationLibrary_STATUS_EDGE_TX_TEST_POWER_CHECK_FAILED = 2245,
    // GSM PATH TEST
    E_METACalibrationLibrary_STATUS_GSM_PATH_TEST_START = 2304,
    E_METACalibrationLibrary_STATUS_GSM_PATH_TEST_DONE = 2305,
    E_METACalibrationLibrary_STATUS_GSM_PATH_TEST_TESTER_PRESETTING_FAILED = 2306,
    E_METACalibrationLibrary_STATUS_GSM_PATH_TEST_TESTER_CHANGE_BAND_FAILED = 2307,
    E_METACalibrationLibrary_STATUS_GSM_PATH_TEST_DUT_CHANGE_BAND_FAILED = 2308,
    E_METACalibrationLibrary_STATUS_GSM_PATH_TEST_DUT_TX_FAILED = 2309,
    E_METACalibrationLibrary_STATUS_GSM_PATH_TEST_FETCH_TX_MEASUREMENT_FAILED = 2310,
    E_METACalibrationLibrary_STATUS_GSM_PATH_TEST_POWER_CHECK_FAILED = 2311,
    /***************************************
     * GSM END
     **************************************/
    /***************************************
     * Utility START
     **************************************/
    // cable loss
    E_METACalibrationLibrary_STATUS_CABLELOSS_START = 2314,
    E_METACalibrationLibrary_STATUS_CABLELOSS_DONE = 2315,
    E_METACalibrationLibrary_STATUS_CABLELOSS_FAILED = 2316,
    E_METACalibrationLibrary_STATUS_CABLELOSS_CHECK_FAILED = 2317,
    /***************************************
     * Utility END
     **************************************/
    /***************************************
     * Others START
     **************************************/
    // GPSCOCLOCK
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_START = 2368,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_DONE = 2369,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_PARSE_CONFIG_FAILED = 2370,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_BAND_SELECT_FAILED = 2371,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_C0C1_CAL_FAILED = 2372,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_CHECK_FAILED = 2373,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_DUT_TX_FAILED = 2374,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_SWITCH_TO_AP_FAILED = 2375,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_SWITCH_TO_MODEM_FAILED = 2376,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_GPS_TCXO_TYPE_CHECK_FAILED = 2377,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_GPS_FIXED_AFC_CHECK_FAILED = 2378,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_GET_GPS_TCXO_TYPE_FAILED = 2379,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_PARAMETER_INCORRECT_0 = 2380,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_PARAMETER_INCORRECT_2 = 2381,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_PARAMETER_INCORRECT_OTHERS = 2382,
    E_METACalibrationLibrary_STATUS_GPSCOCLOCK_SP_META_INIT_DATABASE_FAILED = 2383,
    /***************************************
     * Others END
     **************************************/
#if defined(__META_LTE__)
    /***************************************
     * LTE START
     **************************************/
    // LTE Common
    E_METACalibrationLibrary_STATUS_LTE_PARSE_COMMON_CFG_FAILED = 2432,
    E_METACalibrationLibrary_STATUS_LTE_GET_CAPABILITY_FAILED = 2433,
    E_METACalibrationLibrary_STATUS_LTE_GET_AFC_DAC_FAILED = 2434,
    E_METACalibrationLibrary_STATUS_LTE_SET_TOOL_USAGE_FAILED = 2435,
    E_METACalibrationLibrary_STATUS_LTE_GET_CA_CONFIG_FAILED = 2436,
    E_METACalibrationLibrary_STATUS_LTE_STOP_TEST_MODE_FAILED = 2437,
    // AGC
    E_METACalibrationLibrary_STATUS_LTE_AGC_START = 2496,
    E_METACalibrationLibrary_STATUS_LTE_AGC_DONE = 2497,
    E_METACalibrationLibrary_STATUS_LTE_AGC_PARSE_CONFIG_FAILED = 2498,
    E_METACalibrationLibrary_STATUS_LTE_AGC_TESTER_PRESETTING_FAILED = 2499,
    E_METACalibrationLibrary_STATUS_LTE_AGC_TESTER_CHANGE_BAND_FAILED = 2500,
    E_METACalibrationLibrary_STATUS_LTE_AGC_GAIN_OFFSET_OVERFLOW = 2501,
    E_METACalibrationLibrary_STATUS_LTE_AGC_RXD_GAIN_OFFSET_OVERFLOW = 2502,
    E_METACalibrationLibrary_STATUS_LTE_AGC_TESTER_CHANGE_POWER_FAILED = 2503,
    E_METACalibrationLibrary_STATUS_LTE_AGC_TESTER_CHANGE_DL_FREQ_FAILED = 2504,
    E_METACalibrationLibrary_STATUS_LTE_AGC_WRITE_INIT_VALUE_FAILED = 2505,
    E_METACalibrationLibrary_STATUS_LTE_AGC_WRITE_CAL_DATA_FAILED = 2506,
    E_METACalibrationLibrary_STATUS_LTE_AGC_VALUE_CHECK_FAILED = 2507,
    E_METACalibrationLibrary_STATUS_LTE_AGC_MEASURE_FAILED = 2508,
    E_METACalibrationLibrary_STATUS_LTE_AGC_LNA_MODE_MISMATCH = 2509,
    E_METACalibrationLibrary_STATUS_LTE_AGC_GET_TEMP_INFO_FAILED = 2510,
    // AFC
    E_METACalibrationLibrary_STATUS_LTE_AFC_START = 2560,
    E_METACalibrationLibrary_STATUS_LTE_AFC_DONE = 2561,
    E_METACalibrationLibrary_STATUS_LTE_AFC_PARSE_CONFIG_FAILED = 2562,
    E_METACalibrationLibrary_STATUS_LTE_AFC_PARSE_INI_FAILED = 2563,
    E_METACalibrationLibrary_STATUS_LTE_AFC_TESTER_PRESETTING_FAILED = 2564,
    E_METACalibrationLibrary_STATUS_LTE_AFC_WRITE_INIT_VALUE_FAILED = 2565,
    E_METACalibrationLibrary_STATUS_LTE_AFC_WRITE_CAL_DATA_FAILED = 2566,
    E_METACalibrationLibrary_STATUS_LTE_AFC_WRITE_NVRAM_FAILED = 2567,
    E_METACalibrationLibrary_STATUS_LTE_AFC_VALUE_CHECK_FAILED = 2568,
    E_METACalibrationLibrary_STATUS_LTE_AFC_DUT_TX_FAILED = 2569,
    E_METACalibrationLibrary_STATUS_LTE_AFC_READ_NVRAM_FAILED = 2570,
    // APC
    E_METACalibrationLibrary_STATUS_LTE_APC_START = 2624,
    E_METACalibrationLibrary_STATUS_LTE_APC_DONE = 2625,
    E_METACalibrationLibrary_STATUS_LTE_APC_PA_SUBBAND_COMPENSATION_OUT_OF_RANGE = 2626,
    E_METACalibrationLibrary_STATUS_LTE_APC_COUPLER_SUBBAND_COMPENSATION_OUT_OF_RANGE = 2627,
    E_METACalibrationLibrary_STATUS_LTE_APC_SUBBAND_CAL_INIT_TX_MEASUREMENT_FAILED = 2628,
    E_METACalibrationLibrary_STATUS_LTE_APC_SUBBAND_CAL_DUT_TX_FAILED = 2629,
    E_METACalibrationLibrary_STATUS_LTE_APC_SUBBAND_CAL_FETCH_TX_MEASUREMENT_FAILED = 2630,
    E_METACalibrationLibrary_STATUS_LTE_APC_SET_PA_OCT_LEVEL_CONTROL_TO_TARGET_FAILED = 2631,
    E_METACalibrationLibrary_STATUS_LTE_APC_COUPLER_LOSS_OUT_OF_RANGE = 2632,
    E_METACalibrationLibrary_STATUS_LTE_APC_PA_GAIN_PING_PONG_DETECTED = 2633,
    E_METACalibrationLibrary_STATUS_LTE_APC_PA_GAIN_CAL_EXCEEDS_MAX_ITERATION = 2634,
    E_METACalibrationLibrary_STATUS_LTE_APC_PA_CAL_INIT_TX_MEASUREMENT_FAILED = 2635,
    E_METACalibrationLibrary_STATUS_LTE_APC_PA_CAL_FETCH_TX_MEASUREMENT_FAILED = 2636,
    E_METACalibrationLibrary_STATUS_LTE_APC_COUPLER_LOSS_CAL_DETECTOR_MEASUREMENT_FAILED = 2637,
    E_METACalibrationLibrary_STATUS_LTE_APC_DUT_TX_FAILED = 2638,
    E_METACalibrationLibrary_STATUS_LTE_APC_WRITE_CAL_DATA_FAILED = 2639,
    E_METACalibrationLibrary_STATUS_LTE_APC_WRITE_INIT_VALUE_FAILED = 2640,
    E_METACalibrationLibrary_STATUS_LTE_APC_PA_GAIN_CHECK_FAILED = 2641,
    E_METACalibrationLibrary_STATUS_LTE_APC_COUPLER_LOSS_CHECK_FAILED = 2642,
    E_METACalibrationLibrary_STATUS_LTE_APC_PA_SUBBAND_COMPENSATION_CHECK_FAILED = 2643,
    E_METACalibrationLibrary_STATUS_LTE_APC_COUPLER_LOSS_SUBBAND_COMPENSATION_CHECK_FAILED = 2644,
    E_METACalibrationLibrary_STATUS_LTE_APC_TESTER_PRESETTING_FAILED = 2645,
    E_METACalibrationLibrary_STATUS_LTE_APC_TESTER_CHANGE_BAND_FAILED = 2646,
    E_METACalibrationLibrary_STATUS_LTE_APC_TESTER_CHANGE_EXPECTED_POWER_IN_PA_GAIN_CAL_FAILED = 2647,
    E_METACalibrationLibrary_STATUS_LTE_APC_TESTER_CHANGE_UL_FREQUENCY_FAILED = 2648,
    E_METACalibrationLibrary_STATUS_LTE_APC_PARSE_CONFIG_FAILED = 2649,
    E_METACalibrationLibrary_STATUS_LTE_APC_GET_TPC_TABLE_INDEX_ERROR = 2650,
    E_METACalibrationLibrary_STATUS_LTE_APC_GET_TEMP_INFO_FAILED = 2651,
    // FHC
    E_METACalibrationLibrary_STATUS_LTE_FHC_START = 2688,
    E_METACalibrationLibrary_STATUS_LTE_FHC_DONE = 2689,
    E_METACalibrationLibrary_STATUS_LTE_FHC_AGC_PARSE_CONFIG_FAILED = 2690,
    E_METACalibrationLibrary_STATUS_LTE_FHC_APC_PARSE_CONFIG_FAILED = 2691,
    E_METACalibrationLibrary_STATUS_LTE_TESTER_SETTING_PRESETTING_FAILED = 2692,
    E_METACalibrationLibrary_STATUS_LTE_FHC_AGC_WRITE_INIT_VALUE_FAILED = 2693,
    E_METACalibrationLibrary_STATUS_LTE_FHC_APC_WRITE_INIT_VALUE_FAILED = 2694,
    E_METACalibrationLibrary_STATUS_LTE_FHC_AGC_WRITE_CAL_DATA_FAILED = 2695,
    E_METACalibrationLibrary_STATUS_LTE_FHC_APC_WRITE_CAL_DATA_FAILED = 2696,
    E_METACalibrationLibrary_STATUS_LTE_FHC_AGC_CHECK_FAILED = 2697,
    E_METACalibrationLibrary_STATUS_LTE_FHC_APC_CHECK_FAILED = 2698,
    E_METACalibrationLibrary_STATUS_LTE_FHC_START_FAILED = 2699,
    E_METACalibrationLibrary_STATUS_LTE_FHC_AGC_EVALUATE_FAILED = 2700,
    E_METACalibrationLibrary_STATUS_LTE_FHC_AGC_LNA_MODE_MISMATCH = 2701,
    // LTE TADC
    E_METACalibrationLibrary_STATUS_LTE_TADC_START = 2752,
    E_METACalibrationLibrary_STATUS_LTE_TADC_MEASURE_FAILED = 2753,
    E_METACalibrationLibrary_STATUS_LTE_TADC_GET_NVRAM_RECORD_LENGTH_FAILED = 2754,
    E_METACalibrationLibrary_STATUS_LTE_TADC_COMPOSE_NVRAM_FAILED = 2755,
    E_METACalibrationLibrary_STATUS_LTE_TADC_WRITE_NVRAM_INITIAL_VALUE_FAILED = 2756,
    E_METACalibrationLibrary_STATUS_LTE_TADC_WRITE_NVRAM_CAL_DATA_FAILED = 2757,
    E_METACalibrationLibrary_STATUS_LTE_TADC_INVALID_CURRENT_TEMPERATURE = 2758,
    E_METACalibrationLibrary_STATUS_LTE_TADC_CHECK_START = 2759,
    E_METACalibrationLibrary_STATUS_LTE_TADC_CHECK_FAILED = 2760,
    E_METACalibrationLibrary_STATUS_LTE_TADC_DONE = 2761,
    E_METACalibrationLibrary_STATUS_LTE_TADC_PARSE_CONFIG_FAILED = 2762,
    E_METACalibrationLibrary_STATUS_LTE_TADC_PARSE_INI_FAILED = 2763,
    E_METACalibrationLibrary_STATUS_LTE_TADC_INVALID_SENSOR_STATUS = 2764,
    // LTE NSFT
    E_METACalibrationLibrary_STATUS_LTE_NSFT_START = 2816,
    E_METACalibrationLibrary_STATUS_LTE_NSFT_DONE = 2817,
    E_METACalibrationLibrary_STATUS_LTE_NSFT_PARSE_CONFIG_FAILED = 2818,
    E_METACalibrationLibrary_STATUS_LTE_NSFT_TESTER_PRESETTING_IN_SYNC_TEST_FAILED = 2819,
    E_METACalibrationLibrary_STATUS_LTE_NSFT_TARGET_RX_START_FAILED = 2820,
    E_METACalibrationLibrary_STATUS_LTE_NSFT_TESTER_TESTCASE_SETTING_IN_RX_SYNC_TEST_FAILED = 2821,
    E_METACalibrationLibrary_STATUS_LTE_NSFT_RX_TEST_FAILED = 2822,
    E_METACalibrationLibrary_STATUS_LTE_NSFT_CHECK_FAILED = 2823,
    E_METACalibrationLibrary_STATUS_LTE_NSFT_TARGET_TX_START_FAILED = 2824,
    E_METACalibrationLibrary_STATUS_LTE_NSFT_MCS_MODE_INCONSISTENCY = 2825,
    /***************************************
     * LTE END
     **************************************/
#endif //#if defined(__META_LTE__)
    // multi-RAT TADC
    E_METACalibrationLibrary_STATUS_MULTIRAT_TADC_START = 2880,
    E_METACalibrationLibrary_STATUS_MULTIRAT_TADC_DONE = 2881,
    E_METACalibrationLibrary_STATUS_MULTIRAT_TADC_CAPABILITY_INCONSISTENT = 2882,
    E_METACalibrationLibrary_STATUS_MULTIRAT_TADC_ALL_RAT_CFG_INI_INCOMPLETE = 2883,
    // GGE List Mode NSFT
    E_METACalibrationLibrary_STATUS_GGE_NSFT_LIST_START = 2944,
    E_METACalibrationLibrary_STATUS_GGE_NSFT_LIST_DONE = 2945,
    // WCDMA List Mode NSFT
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_START = 3008,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_TARGET_START_FAILED = 3009,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_TARGET_STOP_FAILED = 3010,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_TX_MEASURE_FAILED = 3011,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_BER_MEASURE_FAILED = 3012,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_CHECK_FAILED = 3013,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_DONE = 3014,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_CONFIG_DUT_TPC_ALGO_FAILED = 3015,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_TX_TEST_MAX_POWER_FAILED = 3016,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_TX_TEST_MIN_POWER_FAILED = 3017,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_TX_TEST_ILPC_FAILED = 3018,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_BER_TEST_FAILED = 3019,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_PARSE_CONFIG_FAILED = 3020,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_TESTER_PRESETTING_FAILED = 3021,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_NOT_SUPPORTED_BAND = 3022,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_TESTER_SETTING_IN_SYNC_TEST_FAILED = 3023,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_TARGET_START_SYNC_CS_FAILED = 3024,
    E_METACalibrationLibrary_STATUS_WCDMA_LIST_MODE_NSFT_TARGET_START_SYNC_SFN_FAILED = 3025,
    // TDSCDMA List Mode NSFT
    E_METACalibrationLibrary_STATUS_TDSCDMA_NSFT_LIST_START = 3072,
    E_METACalibrationLibrary_STATUS_TDSCDMA_NSFT_LIST_DONE = 3073,
#if defined(__META_LTE__)
    // LTE PATH TEST
    E_METACalibrationLibrary_STATUS_LTE_PATH_TEST_START = 3136,
    E_METACalibrationLibrary_STATUS_LTE_PATH_TEST_DONE = 3137,
    E_METACalibrationLibrary_STATUS_LTE_PATH_TEST_TESTER_PRESETTING_FAILED = 3138,
    E_METACalibrationLibrary_STATUS_LTE_PATH_TEST_TESTER_CHANGE_BAND_FAILED = 3139,
    E_METACalibrationLibrary_STATUS_LTE_PATH_TEST_DUT_CHANGE_BAND_FAILED = 3140,
    E_METACalibrationLibrary_STATUS_LTE_PATH_TEST_DUT_TX_FAILED = 3141,
    E_METACalibrationLibrary_STATUS_LTE_PATH_TEST_FETCH_TX_MEASUREMENT_FAILED = 3142,
    E_METACalibrationLibrary_STATUS_LTE_PATH_TEST_POWER_CHECK_FAILED = 3143,
    // LTE ETM
    E_METACalibrationLibrary_STATUS_LTE_ETM_START = 3200,
    E_METACalibrationLibrary_STATUS_LTE_ETM_DONE = 3201,
    E_METACalibrationLibrary_STATUS_LTE_ETM_CALIBRATION_FAILED = 3202,
    E_METACalibrationLibrary_STATUS_LTE_ETM_GET_ET_CALIBRATION_RESULT_FAILED = 3203,
    // LTE CAP ID
    E_METACalibrationLibrary_STATUS_LTE_CAP_ID_START = 3264,
    E_METACalibrationLibrary_STATUS_LTE_CAP_ID_DONE = 3265,
    E_METACalibrationLibrary_STATUS_LTE_CAP_ID_CHECK_FAILED = 3266,
    E_METACalibrationLibrary_STATUS_LTE_CAP_ID_SET_CAPID_FAILED = 3267,
    E_METACalibrationLibrary_STATUS_LTE_CAP_ID_GET_AFC_DATA_FAILED = 3268,
    E_METACalibrationLibrary_STATUS_LTE_CAP_ID_VALUE_CHECK_FAILED = 3269,
    // LTE DPD
    E_METACalibrationLibrary_STATUS_LTE_DPD_START = 3328,
    E_METACalibrationLibrary_STATUS_LTE_DPD_DONE = 3329,
    E_METACalibrationLibrary_STATUS_LTE_DPD_PARSE_COMMON_CFG_FAILED = 3330,
    E_METACalibrationLibrary_STATUS_LTE_DPD_CALIBRATION_FAILED = 3331,
    E_METACalibrationLibrary_STATUS_LTE_DPD_WRITE_NVRAM_INITIAL_VALUE_FAILED = 3332,
    E_METACalibrationLibrary_STATUS_LTE_DPD_GET_CALIBRATION_RESULT_FAILED = 3333,
    E_METACalibrationLibrary_STATUS_LTE_DPD_SET_CALIBRATION_RESULT_FAILED = 3334,
    // LTE DPD PA gain
    E_METACalibrationLibrary_STATUS_LTE_DPD_PA_GAIN_START = 3392,
    E_METACalibrationLibrary_STATUS_LTE_DPD_PA_GAIN_DONE = 3393,
    E_METACalibrationLibrary_STATUS_LTE_DPD_PA_GAIN_PARSE_COMMON_CFG_FAILED = 3394,
    E_METACalibrationLibrary_STATUS_LTE_DPD_PA_GAIN_CALIBRATION_FAILED = 3395,
    E_METACalibrationLibrary_STATUS_LTE_DPD_PA_GAIN_WRITE_NVRAM_INITIAL_VALUE_FAILED = 3336,
    E_METACalibrationLibrary_STATUS_LTE_DPD_PA_GAIN_GET_CALIBRATION_RESULT_FAILED = 3397,
    E_METACalibrationLibrary_STATUS_LTE_DPD_PA_GAIN_SET_CALIBRATION_RESULT_FAILED = 3398,
    // LTE CIM3
    E_METACalibrationLibrary_STATUS_LTE_CIM3_START = 3456,
    E_METACalibrationLibrary_STATUS_LTE_CIM3_DONE = 3457,
    E_METACalibrationLibrary_STATUS_LTE_CIM3_PARSE_COMMON_CFG_FAILED = 3458,
    E_METACalibrationLibrary_STATUS_LTE_CIM3_CALIBRATION_FAILED = 3459,
    E_METACalibrationLibrary_STATUS_LTE_CIM3_WRITE_NVRAM_INITIAL_VALUE_FAILED = 3360,
    E_METACalibrationLibrary_STATUS_LTE_CIM3_GET_CALIBRATION_RESULT_FAILED = 3361,
    E_METACalibrationLibrary_STATUS_LTE_CIM3_SET_CALIBRATION_RESULT_FAILED = 3362,
#endif //#if defined(__META_LTE__)
#if defined(__META_C2K__)
    /***************************************
     * C2K START
     **************************************/
    E_METACalibrationLibrary_STATUS_SET_C2K_POWER_CONTROL_MODE_FAILED = 4000,
    E_METACalibrationLibrary_STATUS_C2K_PS_POWER_FAILED = 4001,
    E_METACalibrationLibrary_STATUS_C2K_GET_CAPABILITY_FAILED = 4002,
    E_METACalibrationLibrary_STATUS_SET_C2K_PA_DRIFT_COMPENSATION_FAILED = 4003,
    // C2K TADC
    E_METACalibrationLibrary_STATUS_C2K_TADC_START = 4004,
    E_METACalibrationLibrary_STATUS_C2K_TADC_MEASURE_FAILED = 4005,
    E_METACalibrationLibrary_STATUS_C2K_TADC_GET_NVRAM_RECORD_LENGTH_FAILED = 4006,
    E_METACalibrationLibrary_STATUS_C2K_TADC_COMPOSE_NVRAM_FAILED = 4007,
    E_METACalibrationLibrary_STATUS_C2K_TADC_WRITE_NVRAM_INITIAL_VALUE_FAILED = 4008,
    E_METACalibrationLibrary_STATUS_C2K_TADC_WRITE_NVRAM_CAL_DATA_FAILED = 4009,
    E_METACalibrationLibrary_STATUS_C2K_TADC_INVALID_CURRENT_TEMPERATURE = 4010,
    E_METACalibrationLibrary_STATUS_C2K_TADC_CHECK_START = 4011,
    E_METACalibrationLibrary_STATUS_C2K_TADC_CHECK_FAILED = 4012,
    E_METACalibrationLibrary_STATUS_C2K_TADC_DONE = 4013,
    E_METACalibrationLibrary_STATUS_C2K_TADC_PARSE_CONFIG_FAILED = 4014,
    // C2K AFC
    E_METACalibrationLibrary_STATUS_C2K_AFC_START = 4015,
    E_METACalibrationLibrary_STATUS_C2K_AFC_TX_FAILED = 4016,
    E_METACalibrationLibrary_STATUS_C2K_AFC_CONFIG_FAILED = 4017,
    E_METACalibrationLibrary_STATUS_C2K_AFC_CHECK_FAILED = 4018,
    E_METACalibrationLibrary_STATUS_C2K_AFC_DONE = 4019,
    // C2K AGC
    E_METACalibrationLibrary_STATUS_C2K_AGC_START = 4020,
    E_METACalibrationLibrary_STATUS_C2K_AGC_CHECK_START = 4021,
    E_METACalibrationLibrary_STATUS_C2K_AGC_DONE = 4022,
    E_METACalibrationLibrary_STATUS_C2K_AGC_MEASURE_FAILED = 4023,
    E_METACalibrationLibrary_STATUS_C2K_AGC_CHECK_DIGI_GAIN_FAILED = 4024,
    E_METACalibrationLibrary_STATUS_C2K_AGC_CHECK_GAIN_STEP_DELTA_FAILED = 4025,
    E_METACalibrationLibrary_STATUS_C2K_AGC_CHECK_SUBBAND_COMPENSATION_FAILED = 4026,
    E_METACalibrationLibrary_STATUS_C2K_AGC_CHECK_LNA_MODE_FAILED = 4027,
    E_METACalibrationLibrary_STATUS_C2K_AGC_WRITE_INIT_VALUE_FAILED = 4028,
    E_METACalibrationLibrary_STATUS_C2K_AGC_WRITE_CAL_DATA_FAILED = 4029,
    E_METACalibrationLibrary_STATUS_C2K_AGC_PARSE_CONFIG_FAILED = 4030,
    E_METACalibrationLibrary_STATUS_C2K_AGC_TESTER_PRESETTING_FAILED = 4031,
    E_METACalibrationLibrary_STATUS_C2K_AGC_TESTER_CHANGE_BAND_FAILED = 4032,
    E_METACalibrationLibrary_STATUS_C2K_AGC_TESTER_CHANGE_CHANNEL_FAILED = 4033,
    E_METACalibrationLibrary_STATUS_C2K_AGC_TESTER_CHANGE_POWER_FAILED = 4034,
    E_METACalibrationLibrary_STATUS_C2K_AGC_RECEIVER_CTRL_FAILED = 4035,
    E_METACalibrationLibrary_STATUS_C2K_AGC_SET_GAIN_STATE_FAILED = 4036,
    E_METACalibrationLibrary_STATUS_C2K_AGC_SET_ANTENNA_PATH_FAILED = 4037,
    // C2K APC
    E_METACalibrationLibrary_STATUS_C2K_APC_START = 4038,
    E_METACalibrationLibrary_STATUS_C2K_APC_CHECK_START = 4039,
    E_METACalibrationLibrary_STATUS_C2K_APC_DONE = 4040,
    E_METACalibrationLibrary_STATUS_C2K_APC_COUPLER_LOSS_OUT_OF_RANGE = 4041,
    E_METACalibrationLibrary_STATUS_C2K_APC_PA_GAIN_PING_PONG_DETECTED = 4042,
    E_METACalibrationLibrary_STATUS_C2K_APC_PA_GAIN_CAL_EXCEEDS_MAX_ITERATION = 4043,
    E_METACalibrationLibrary_STATUS_C2K_APC_PA_SUBBAND_COMPENSATION_OUT_OF_RANGE = 4044,
    E_METACalibrationLibrary_STATUS_C2K_APC_COUPLER_SUBBAND_COMPENSATION_OUT_OF_RANGE = 4045,
    E_METACalibrationLibrary_STATUS_C2K_APC_SET_PA_OCT_LEVEL_CONTROL_TO_TARGET_FAILED = 4046,
    E_METACalibrationLibrary_STATUS_C2K_APC_SET_COMPENSATION_TO_TARGET_FAILED = 4047,
    E_METACalibrationLibrary_STATUS_C2K_APC_DETECTOR_MEASUREMENT_FAILED = 4048,
    E_METACalibrationLibrary_STATUS_C2K_APC_DUT_TX_FAILED = 4049,
    E_METACalibrationLibrary_STATUS_C2K_APC_PA_GAIN_CHECK_FAILED = 4050,
    E_METACalibrationLibrary_STATUS_C2K_APC_COUPLER_LOSS_CHECK_FAILED = 4051,
    E_METACalibrationLibrary_STATUS_C2K_APC_PA_SUBBAND_COMPENSATION_CHECK_FAILED = 4052,
    E_METACalibrationLibrary_STATUS_C2K_APC_COUPLER_LOSS_SUBBAND_COMPENSATION_CHECK_FAILED = 4053,
    E_METACalibrationLibrary_STATUS_C2K_APC_INIT_TX_MEASUREMENT_FAILED = 4054,
    E_METACalibrationLibrary_STATUS_C2K_APC_FETCH_TX_MEASUREMENT_FAILED = 4055,
    E_METACalibrationLibrary_STATUS_C2K_APC_PA_CAL_INIT_TX_MEASUREMENT_FAILED = 4056,
    E_METACalibrationLibrary_STATUS_C2K_APC_PA_CAL_DUT_TX_FAILED = 4057,
    E_METACalibrationLibrary_STATUS_C2K_APC_PA_CAL_FETCH_TX_MEASUREMENT_FAILED = 4058,
    E_METACalibrationLibrary_STATUS_C2K_APC_COUPLER_LOSS_CAL_INIT_TX_MEASUREMENT_FAILED = 4059,
    E_METACalibrationLibrary_STATUS_C2K_APC_COUPLER_LOSS_CAL_DUT_TX_FAILED = 4060,
    E_METACalibrationLibrary_STATUS_C2K_APC_COUPLER_LOSS_CAL_FETCH_TX_MEASUREMENT_FAILED = 4061,
    E_METACalibrationLibrary_STATUS_C2K_APC_SUBBAND_CAL_INIT_TX_MEASUREMENT_FAILED = 4062,
    E_METACalibrationLibrary_STATUS_C2K_APC_SUBBAND_CAL_DUT_TX_FAILED = 4063,
    E_METACalibrationLibrary_STATUS_C2K_APC_SUBBAND_CAL_FETCH_TX_MEASUREMENT_FAILED = 4064,
    E_METACalibrationLibrary_STATUS_C2K_APC_COUPLER_LOSS_CAL_DETECTOR_MEASUREMENT_FAILED = 4065,
    E_METACalibrationLibrary_STATUS_C2K_APC_SUBBAND_CAL_DETECTOR_MEASUREMENT_FAILED = 4066,
    E_METACalibrationLibrary_STATUS_C2K_APC_WRITE_INIT_VALUE_FAILED = 4067,
    E_METACalibrationLibrary_STATUS_C2K_APC_WRITE_CAL_DATA_FAILED = 4068,
    E_METACalibrationLibrary_STATUS_C2K_APC_PARSE_CONFIG_FAILED = 4069,
    E_METACalibrationLibrary_STATUS_C2K_APC_TESTER_PRESETTING_FAILED = 4070,
    E_METACalibrationLibrary_STATUS_C2K_APC_TESTER_CHANGE_BAND_FAILED = 4071,
    E_METACalibrationLibrary_STATUS_C2K_APC_TESTER_CHANGE_EXPECTED_POWER_IN_PA_GAIN_CAL_FAILED = 4072,
    E_METACalibrationLibrary_STATUS_C2K_APC_TESTER_CHANGE_EXPECTED_POWER_IN_SUBBAND_CAL_FAILED = 4073,
    E_METACalibrationLibrary_STATUS_C2K_APC_TESTER_CHANGE_EXPECTED_POWER_IN_COUPLER_LOSS_CAL_FAILED = 4074,
    // C2K FHC START
    E_METACalibrationLibrary_STATUS_C2K_FHC_START = 4075,
    E_METACalibrationLibrary_STATUS_C2K_FHC_START_FAILED = 4076,
    E_METACalibrationLibrary_STATUS_C2K_FHC_QUERY_FAILED = 4077,
    E_METACalibrationLibrary_STATUS_C2K_FHC_CHECK_FAILED = 4078,
    E_METACalibrationLibrary_STATUS_C2K_FHC_DONE = 4079,
    E_METACalibrationLibrary_STATUS_C2K_FHC_AGC_CHECK_DIGI_GAIN_FAILED = 4080,
    E_METACalibrationLibrary_STATUS_C2K_FHC_AGC_CHECK_GAIN_STEP_DELTA_FAILED = 4081,
    E_METACalibrationLibrary_STATUS_C2K_FHC_AGC_CHECK_SUBBAND_COMPENSATION_FAILED = 4082,
    E_METACalibrationLibrary_STATUS_C2K_FHC_AGC_LNA_MODE_CHECK_FAILED = 4083,
    E_METACalibrationLibrary_STATUS_C2K_FHC_APC_PA_GAIN_CHECK_FAILED = 4084,
    E_METACalibrationLibrary_STATUS_C2K_FHC_APC_COUPLER_LOSS_CHECK_FAILED = 4085,
    E_METACalibrationLibrary_STATUS_C2K_FHC_APC_PA_SUBBAND_COMPENSATION_CHECK_FAILED = 4086,
    E_METACalibrationLibrary_STATUS_C2K_FHC_APC_COUPLER_LOSS_SUBBAND_COMPENSATION_CHECK_FAILED = 4087,
    E_METACalibrationLibrary_STATUS_C2K_FHC_AGC_WRITE_INIT_VALUE_FAILED = 4088,
    E_METACalibrationLibrary_STATUS_C2K_FHC_APC_WRITE_INIT_VALUE_FAILED = 4089,
    E_METACalibrationLibrary_STATUS_C2K_FHC_AGC_WRITE_CAL_DATA_FAILED = 4090,
    E_METACalibrationLibrary_STATUS_C2K_FHC_APC_WRITE_CAL_DATA_FAILED = 4091,
    E_METACalibrationLibrary_STATUS_C2K_FHC_AGC_PARSE_CONFIG_FAILED = 4092,
    E_METACalibrationLibrary_STATUS_C2K_FHC_APC_PARSE_CONFIG_FAILED = 4093,
    E_METACalibrationLibrary_STATUS_C2K_FHC_PARSE_CONFIG_FAILED = 4094,
    E_METACalibrationLibrary_STATUS_C2K_FHC_TESTER_PRESETTING_FAILED = 4095,
    // C2K NSFT
    E_METACalibrationLibrary_STATUS_C2K_NSFT_START = 4096,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_TARGET_START_FAILED = 4097,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_TARGET_STOP_FAILED = 4098,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_TX_MEASURE_FAILED = 4099,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_FER_MEASURE_FAILED = 4100,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_CHECK_FAILED = 4101,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_DONE = 4102,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_CONFIG_DUT_TPC_FAILED = 4103,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_TX_TEST_MAX_POWER_FAILED = 4104,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_TX_TEST_MIN_POWER_FAILED = 4105,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_TX_TEST_ILPC_FAILED = 4106,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_FER_TEST_FAILED = 4107,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_POWER_UP_FAILED = 4108,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_DUT_OPEN_LOOP_POWER_TEST_FAILED = 4109,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_PARSE_CONFIG_FAILED = 4110,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_TESTER_PRESETTING_IN_SYNC_TEST_FAILED = 4111,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_TESTER_PRESETTING_IN_APP_TEST_FAILED = 4112,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_TESTER_TESTCASE_SETTING_IN_SYNC_TEST_FAILED = 4113,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_TESTER_TESTCASE_SETTING_IN_APP_TEST_FAILED = 4114,
    E_METACalibrationLibrary_STATUS_C2K_NSFT_NOT_SUPPORTED_BAND = 4115,
    // C2K HSDPA NSFT
    //E_METACalibrationLibrary_STATUS_C2K_HSDPA_NSFT_START = ,
    //E_METACalibrationLibrary_STATUS_C2K_HSDPA_NSFT_TARGET_START_FAILED = ,
    //E_METACalibrationLibrary_STATUS_C2K_HSDPA_NSFT_TARGET_STOP_FAILED = ,
    //E_METACalibrationLibrary_STATUS_C2K_HSDPA_NSFT_TX_MEASURE_FAILED = ,
    //E_METACalibrationLibrary_STATUS_C2K_HSDPA_NSFT_CHECK_FAILED = ,
    //E_METACalibrationLibrary_STATUS_C2K_HSDPA_NSFT_DONE = ,
    // C2K HSUPA NSFT
    //E_METACalibrationLibrary_STATUS_C2K_HSUPA_NSFT_START = ,
    //E_METACalibrationLibrary_STATUS_C2K_HSUPA_NSFT_TARGET_START_FAILED = ,
    //E_METACalibrationLibrary_STATUS_C2K_HSUPA_NSFT_TARGET_STOP_FAILED = ,
    //E_METACalibrationLibrary_STATUS_C2K_HSUPA_NSFT_TX_MEASURE_FAILED = ,
    //E_METACalibrationLibrary_STATUS_C2K_HSUPA_NSFT_CHECK_FAILED = ,
    //E_METACalibrationLibrary_STATUS_C2K_HSUPA_NSFT_DONE = ,
    // C2K DCXO AFC
    E_METACalibrationLibrary_STATUS_C2K_DCXO_AFC_START = 4116,
    E_METACalibrationLibrary_STATUS_C2K_DCXO_AFC_DONE = 4117,
    E_METACalibrationLibrary_STATUS_C2K_DCXO_AFC_CHECK_FAILED = 4118,
    E_METACalibrationLibrary_STATUS_C2K_DCXO_AFC_TX_FAILED = 4119,
    E_METACalibrationLibrary_STATUS_C2K_DCXO_AFC_GET_MAX_CAPID_FAILED = 4120,
    E_METACalibrationLibrary_STATUS_C2K_DCXO_AFC_BINARY_SEARCH_FAILED = 4121,
    E_METACalibrationLibrary_STATUS_C2K_DCXO_AFC_SET_CAPID_FAILED = 4122,
    // C2K COMMON
    E_METACalibrationLibrary_STATUS_C2K_COMMON_START = 4123,
    E_METACalibrationLibrary_STATUS_C2K_COMMON_DONE = 4124,
    E_METACalibrationLibrary_STATUS_C2K_COMMON_WRITE_CAL_DATA_FAILED = 4125,
    E_METACalibrationLibrary_STATUS_C2K_CLEAR_RF_NVRAM_FAILED = 4126,
    E_METACalibrationLibrary_STATUS_C2K_FLUSH_NVRAM_FAILED = 4127,
    E_METACalibrationLibrary_STATUS_C2K_CAL_INIT_NVRAM_FAILED = 4128,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_START = 4131,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_TARGET_START_FAILED = 4132,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_TARGET_STOP_FAILED = 4133,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_TX_MEASURE_FAILED = 4134,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_FER_MEASURE_FAILED = 4135,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_CHECK_FAILED = 4136,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_DONE = 4137,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_TX_TEST_MAX_POWER_FAILED = 4138,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_TX_TEST_MIN_POWER_FAILED = 4139,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_FER_TEST_FAILED = 4140,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_PARSE_CONFIG_FAILED = 4141,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_TESTER_PRESETTING_FAILED = 4142,
    E_METACalibrationLibrary_STATUS_C2K_LIST_MODE_NSFT_TESTER_SETTING_IN_SYNC_TEST_FAILED = 4143,
    /***************************************
     * C2K END
     **************************************/
#endif //#if defined(__META_C2K__)
    /***************************************
     * Self calibration START
     **************************************/
    E_METACalibrationLibrary_STATUS_MMRF_SELF_CAL_START = 5000,
    E_METACalibrationLibrary_STATUS_MMRF_SELF_CAL_START_FAILED = 5001,
    E_METACalibrationLibrary_STATUS_MMRF_SELF_CAL_GET_RESULT_FAILED = 5002,
    E_METACalibrationLibrary_STATUS_MMRF_SELF_CAL_SET_RESULT_FAILED = 5003,
    E_METACalibrationLibrary_STATUS_MMRF_SELF_CAL_DONE  = 5004,
    /***************************************
     * Self calibration END
     **************************************/

    E_METACalibrationLibrary_STATUS_CODE_END = 65536
}
E_METACalibrationLibrary_STATUS_CODE;

typedef enum
{
    E_METACalibrationLibrary_STATUS_CODE_TYPE_INFO = 0,
    E_METACalibrationLibrary_STATUS_CODE_TYPE_ERROR = 1,
    E_METACalibrationLibrary_STATUS_CODE_TYPE_END = 65536
} E_METACalibrationLibrary_STATUS_CODE_TYPE;


typedef struct
{
    /// calibration status code to indicate the status
    E_METACalibrationLibrary_STATUS_CODE       m_eStatuCode;
    /// calibration status type to indicate the status code is error or information
    E_METACalibrationLibrary_STATUS_CODE_TYPE  m_eStatusType;
    /// status message
    char                                       m_cErrorMsgbuf[256];
} S_METACalibrationLibrary_STATUS_T;
/**
 * removed!
 */
typedef enum
{
    E_METACalibrationLibrary_RESULT_SUCCESS = 0,
    E_METACalibrationLibrary_RESULT_FAILED = 1,
    E_METACalibrationLibrary_RESULT_END = 65536
} E_METACalibrationLibrary_RESULT;
/**
 * removed!
 */
typedef struct
{
    /// GGE Temperature sensor calibration
    bool b_gge_tadc_cal;
    /// GGE CAP ID calibration
    bool b_gge_cap_id_cal;
    /// GGE FB DAC calibration
    bool b_gge_fb_dac_cal;
    /// GGE Slope Skew caliration
    bool b_gge_slope_skew_cal;
    /// GGE AFC calibration
    bool b_gge_afc_cal;
    /// GGE AFC TRX Offset calibration
    bool b_gge_afc_trx_offset_cal;
    /// GGE AGC calibration
    bool b_gge_agc_cal;
    /// GGE APC calibration
    bool b_gge_apc_cal;
    /// GGE EDGE APC calibration
    bool b_gge_edge_apc_cal;
    /// GGE txiq calibration
    bool b_gge_txiq_cal;
    /// GGE FHC calibration attribute (to enable FHC or not)
    bool b_gge_fhc_cal;
    /// GGE TX sub-band calibration attribute (to enable sub-band calibration or not)
    bool b_gge_tpc_subband_cal;
    /// GGE APC W coefficient calibration
    bool b_gge_agc_w_cal;
    /// GGE AD6546 APC calibration
    bool b_gge_AD6546_apc_cal;
    /// GGE GSM APC Power Check
    bool b_gge_apc_check;
    /// GGE EDGE APC Power Check
    bool b_gge_edge_apc_check;
    /// GGE Optimized GSM PCL Calibration, enabled with b_gge_apc_cal
    bool b_gge_OGPC_apc_cal;
    /// GGE Optimized GSM PCL Calibration, enabled with b_gge_edge_apc_cal
    bool b_gge_edge_OGPC_apc_cal;
    /// APC DC offset calibration
    bool b_gge_apc_dc_offset_cal;
} S_METACalibrationLibrary_GGE_CAL_ITEM_T;
/**
 * removed!
 */
typedef struct
{
    /// GGE NSFT R99 TX performance test
    bool b_gge_nsft_gmsk;
    /// GGE NSFT BER test
    bool b_gge_nsft_ber;
    /// GGE NSFT PRACH test (open loop power)
    bool b_gge_nsft_epsk;
    /// GGE list mode NSFT
    bool b_gge_nsft_list_mode;
} S_METACalibrationLibrary_GGE_NSFT_ITEM_T;
/**
 * removed!
 */
typedef struct
{
    /// WCDMA Temperature sensor calibration
    bool b_wcdma_tadc_cal;
    /// WCDMA DCXO AFC calibration
    bool b_wcdma_dcxo_afc_cal;
    /// WCDMA AFC calibration
    bool b_wcdma_afc_cal;
    /// WCDMA AGC calibration
    bool b_wcdma_agc_cal;
    /// WCDMA APC calibration
    bool b_wcdma_apc_cal;
    /// WCDMA FHC calibration attribute (to enable FHC or not)
    bool b_wcdma_fhc_cal;
    /// WCDMA TX sub-band calibration attribute (to enable sub-band calibration or not)
    bool b_wcdma_tpc_subband_cal;
    /// WCDMA RX diversity check(to enable pathloss check or not)
    bool b_wcdma_rxd_pathloss_check;
    /// WCDMA RX diversity calibrated by another port (for users without combiner)
    bool b_wcdma_rxd_another_port_cal;
} S_METACalibrationLibrary_WCDMA_CAL_ITEM_T;
/**
 * removed!
 */
typedef struct
{
    /// WCDMA NSFT R99 TX performance test
    bool b_wcdma_nsft_tpc;
    /// WCDMA NSFT BER test
    bool b_wcdma_nsft_ber;
    /// WCDMA NSFT PRACH test (open loop power)
    bool b_wcdma_nsft_prach;
    /// WCDMA NSFT HSDPA performance test
    bool b_wcdma_hsdpa_nsft;
    /// WCDMA NSFT HSUPA performance test
    bool b_wcdma_hsupa_nsft;
    /// WCDMA NSFT list mode performance test
    bool b_wcdma_list_mode;
} S_METACalibrationLibrary_WCDMA_NSFT_ITEM_T;
/**
 * removed!
 */
typedef struct
{
    /// TDSCDMA temperature sensor calibration
    bool b_tda_tadc_cal;
    /// TDSCDMA CAP ID calibration
    bool b_tda_cap_id_cal;
    /// TDSCDMA AFC calibration
    bool b_tda_afc_cal;
    /// TDSCDMA AGC calibration
    bool b_tda_rx_path_loss_cal;
    /// TDSCDMA APC calibration
    bool b_tda_tpc_cal;
    /// TDSCDMA TX sub-band calibration attribute (to enable sub-band calibration or not)
    bool b_tda_tpc_subband_cal;
    /// TDSCDMA FHC attribute (to enable FHC or not)
    bool b_tda_fhc_cal;
} S_METACalibrationLibrary_TD_CAL_ITEM_T;
/**
 * removed!
 */
typedef struct
{
    /// TDSCDMA NSFT TX performance test
    bool b_tda_nsft_tpc;
    /// TDSCDMA NSFT BER test
    bool b_tda_nsft_ber;

    /// TDSCDMA FT TX performance test
    bool b_tda_ft_tpc;
    /// TDSCDMA FT BER test
    bool b_tda_ft_ber;

} S_METACalibrationLibrary_TD_NSFT_ITEM_T;

/**
 * removed!
 */
typedef struct
{
    /// GGE cableloss calibration
    bool b_utility_gge_cableloss;
    /// WCDMA cableloss calibration
    bool b_utility_wcdma_cableloss;
    /// TDSCDMA cableloss calibration
    bool b_utility_tdscdma_cableloss;
    /// LTE cableloss calibration
    bool b_utility_lte_cableloss;
#if defined(__META_C2K__)
    /// C2K cableloss calibration
    bool b_utility_c2k_cableloss;
#endif
} S_METACalibrationLibrary_Utilities_ITEM_T;

/**
 * removed!
 */
typedef struct
{
    /// GPS CO-CLOCK calibration
    bool b_others_GPSCOCLOCK;
} S_METACalibrationLibrary_Others_ITEM_T;

#if defined(__META_LTE__)
/**
 * LTE FHC calibration items
 */
typedef struct
{
    /// LTE temperature sensor calibration
    bool b_lte_tadc_cal;
    /// LTE CAP ID calibration
    bool b_lte_cap_id_cal;
    /// LTE AFC calibration
    bool b_lte_afc_cal;
    /// LTE AGC calibration
    bool b_lte_rx_path_loss_cal;
    /// LTE APC calibration
    bool b_lte_tpc_cal;
    /// LTE TX sub-band calibration attribute (to enable sub-band calibration or not)
    bool b_lte_tpc_subband_cal;
    /// LTE FHC attribute (to enable FHC or not)
    bool b_lte_fhc_cal;
    /// LTE RX diversity calibrated by another port (for users without combiner)
    bool b_lte_rxd_another_port_cal;
    /// With LTE RX another port calibration, enable main path calibration
    bool b_lte_rxd_another_port_cal_main_path_enabled;
    /// With LTE RX another port calibration, enable div path calibration
    bool b_lte_rxd_another_port_cal_div_path_enabled;
} S_METACalibrationLibrary_LTE_CAL_ITEM_T;
/**
 * LTE FHC calibration items
 */
typedef struct
{
    /// LTE NSFT TX performance test
    bool b_lte_nsft_tx;
    /// LTE NSFT RX test
    bool b_lte_nsft_rx;
    /// LTE RX diversity test by another port (for users without combiner)
    bool b_lte_rxd_another_port_test;
} S_METACalibrationLibrary_LTE_NSFT_ITEM_T;
#endif //#if defined(__META_LTE__)
#if defined(__META_C2K__)
typedef struct
{
    /// C2K Temperature sensor calibration
    bool b_c2k_tadc_cal;
    /// C2K DCXO AFC calibration
    bool b_c2k_dcxo_afc_cal;
    /// C2K AFC calibration
    bool b_c2k_afc_cal;
    /// C2K AGC calibration
    bool b_c2k_agc_cal;
    /// C2K APC calibration
    bool b_c2k_apc_cal;
    /// C2K FHC calibration attribute (to enable FHC or not)
    bool b_c2k_fhc_cal;
    /// C2K TX sub-band calibration attribute (to enable sub-band calibration or not)
    bool b_c2k_tpc_subband_cal;
    /// C2K RX diversity check(to enable pathloss check or not)
    bool b_c2k_rxd_pathloss_check;
    /// C2K RX diversity calibrated by another port (for users without combiner)
    bool b_c2k_rxd_another_port_cal;
} S_METACalibrationLibrary_C2K_CAL_ITEM_T;
typedef struct
{
    /// C2K NSFT CS0011 TX performance test
    bool b_c2k_nsft_tpc;
    /// C2K NSFT FER test
    bool b_c2k_nsft_fer;
    /// C2K NSFT list mode
    bool b_c2k_nsft_list_mode;
    /// C2K NSFT EVDO performance test
    bool b_c2k_evdo_nsft;
} S_METACalibrationLibrary_C2K_NSFT_ITEM_T;
#endif //#if defined(__META_C2K__)
/**
 * removed!
 */
typedef struct
{
    /// cfg file path  (*.cfg)
    char* cfg_path;
    /// ini file path  (*.ini)
    char* ini_path;
    /// log file path  (*.log)
    char* log_path;
    /// output file path (*.cal)
    char* output_path;
    /// result file path (report)
    char* cal_result_path;
    /// smart phone nvram database path
    char* sp_nvram_database_path;
    /// MD nvram database path
    char* md_nvram_database_path;
    /// GSM/GPRS/EDGE device type
    int   i_device_type;
    /// WCDMA device type
    int   i_device_type_wcdma;
    /// TD-SCDMA device type
    int   i_device_type_tdscdma;
#if defined(__META_LTE__)
    /// LTE device type
    int   i_device_type_lte;
#endif //#if defined(__META_LTE__)
#if defined(__META_C2K__)
    /// C2K device type
    int   i_device_type_c2k;
#endif //#if defined(__META_C2K__)
    /// reset tester
    bool  resetTester;
    /// RF port of tester
    int   i_tester_rf_port;
    /// GGE calibration items
    S_METACalibrationLibrary_GGE_CAL_ITEM_T      ggeCalibrationItems;
    /// GGE NSFT items (GMSK, BER, EPSK)
    S_METACalibrationLibrary_GGE_NSFT_ITEM_T     ggeNsftItems;
    /// WCDMA calibration items
    S_METACalibrationLibrary_WCDMA_CAL_ITEM_T    wcdmaCalibrationItems;
    /// WCDMA NSFT items (R99: TPC/BER/PRACH, R5, R6)
    S_METACalibrationLibrary_WCDMA_NSFT_ITEM_T   wcdmaNsftItems;
    /// TDSCDMA calibration items (AST)
    S_METACalibrationLibrary_TD_CAL_ITEM_T       tdscdmaCalibrationItems;
    /// TDSCDMA NSFT items (AST)
    S_METACalibrationLibrary_TD_NSFT_ITEM_T      tdscdmaNsftItems;
#if defined(__META_LTE__)
    /// LTE calibration items
    S_METACalibrationLibrary_LTE_CAL_ITEM_T      lteCalibrationItems;
    /// LTE NSFT items
    S_METACalibrationLibrary_LTE_NSFT_ITEM_T     lteNsftItems;
#endif //#if defined(__META_LTE__)
#if defined(__META_C2K__)
    /// C2K calibration items
    S_METACalibrationLibrary_C2K_CAL_ITEM_T      c2kCalibrationItems;
    /// C2K NSFT items (CS0011: TPC/FER/APP)
    S_METACalibrationLibrary_C2K_NSFT_ITEM_T     c2kNsftItems;
#endif //#if defined(__META_C2K__)
    /// Utitlies calibration items
    S_METACalibrationLibrary_Utilities_ITEM_T    utlitiesCalibrationItems;
    /// Others calibration times
    S_METACalibrationLibrary_Others_ITEM_T       othersCalibrationItems;
} METACalibrationLibrary_COMMON_CFG_T;
typedef void (__stdcall* METACalibrationLibrary_Log_Display_CallBack)(const char* logBuf);
typedef void (__stdcall* METACalibrationLibrary_STATUS_CallBack)(const S_METACalibrationLibrary_STATUS_T status);

E_METACalibrationLibrary_RESULT __stdcall METACalibrationLibrary_RegisterCallBack(const int meta_handle, const METACalibrationLibrary_Log_Display_CallBack cb);
E_METACalibrationLibrary_RESULT __stdcall METACalibrationLibrary_Init(const int meta_handle);
E_METACalibrationLibrary_RESULT __stdcall METACalibrationLibrary_DeInit(const int meta_handle);
E_METACalibrationLibrary_RESULT __stdcall METACalibrationLibrary_Start(const int meta_handle,
        const METACalibrationLibrary_COMMON_CFG_T* cfg,
        const METACalibrationLibrary_STATUS_CallBack cb,
        int* pStopFlag);
E_METACalibrationLibrary_RESULT __stdcall METACalibrationLibrary_StartWithRetrunedStatusCode(const int meta_handle,
        const METACalibrationLibrary_COMMON_CFG_T* cfg,
        S_METACalibrationLibrary_STATUS_T* status,
        int* pStopFlag);
const char* __stdcall METACalibrationLibrary_GetStatusCodeString(E_METACalibrationLibrary_STATUS_CODE code);
E_METACalibrationLibrary_STATUS_CODE_TYPE __stdcall METACalibrationLibrary_GetStatusType(E_METACalibrationLibrary_STATUS_CODE code);
const S_METACalibrationLibrary_STATUS_T* __stdcall METACalibrationLibrary_GetLastError(const int meta_handle);
int __stdcall METACalibrationLibrary_GetDLLVer(unsigned int* major_ver, unsigned int* minor_ver, unsigned int* build_num, unsigned int* patch_num);

#ifdef __cplusplus
}
#endif
#endif  // end if __META_CALIBRATION_LIBRARY_H__
