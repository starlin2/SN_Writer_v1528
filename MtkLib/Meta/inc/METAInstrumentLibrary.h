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
 *  METAInstrumentLibrary.h
 *
 * Project:
 * --------
 *   Standalone Factory Calibration sample code
 *
 * Description:
 * ------------
 *   This module contains the definitions of InstrumentDrivers
 *
 * Author:
 * -------
 *  YH Sung (mtk02607)
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
 * 05 31 2013 zhchao.zhao
 * [STP100007075]  Check in instrument code for Aeroflex
 * Add instrument code of Aeroflex PXI3000.
 *
 * 05 27 2013 eason.lai
 * [STP100007071]  FHC v2 calibration time reduction
 * .
 *
 * 05 09 2013 emerson.liu
 * [STP100006999] Add Litepoint IQxstream
 *
 * 04 18 2013 vend_brog.chu
 * [STP100006920] Add PCCPCH setting for TDD RSCP test
 * 1. Add iPCCPCH setting for each instrument
 * 2. Add RSCP delay in cfg
 * 3. Bug fix for RSCP check
 *
 * 04 17 2013 eason.lai
 * [STP100006916]  Query TDSCDMA single-end BER bit pattern from instrument
 * .
 *
 * 03 20 2013 eason.lai
 * [STP100006808]  Two port RXD calibration
 * .
 *
 * 03 07 2013 eason.lai
 * [STP100006807]  Skyworks dc offset calibration
 * Change interface of pedestal dc offset iteration; removed PCL
 *
 * 03 06 2013 eason.lai
 * [STP100006808]  Two port RXD calibration
 * .
 *
 * 03 05 2013 eason.lai
 * [STP100006808]  Two port RXD calibration
 * .
 *
 * 03 05 2013 eason.lai
 * [STP100006807]  Skyworks dc offset calibration
 * .
 *
 * 02 05 2013 vend_brog.chu
 * [STP100006739] 2G FHC time Reduction
 * Extend Instrument Library function for 2G FHC enhancement
 *
 * 02 04 2013 eason.lai
 * [STP100006731]  Instrument library multi-thread support feature
 * .
 *
 * 02 04 2013 eason.lai
 * [STP100006731]  Instrument library multi-thread support feature
 * .
 *
 * 12 19 2012 vend_brog.chu
 * [STP100006555] MT6280 / MT6589 WCDMA TX calibration Modification for SKY77761
 * Add "WCDMA_APC_PreSetting_Ex" for adding "trigger type" information
 *
 * 11 16 2012 yintong.zhang
 * [STP100006419]  [Meta Share Library] Support Agilent EXT 2G(FHC&NSFT) & WCDMA(FHC&NSFT) & TD(FHC&NSFT)
 * Add new instrument Agilent EXT.
 *
 * 11 15 2012 yintong.zhang
 * [STP100006407]  META Instrument sharelibrary porting
 * Add new instrument T6280.
 *
 * 11 12 2012 eason.lai
 * [STP100006396]  Fixed prach test change cell power fail in CMU200 issue due to cell power control commands of signalling mod and nonsignal mode those are different
 * .
 *
 * 10 30 2012 eason.lai
 * [STP100006325]  Add WCDMA NSFT TX BER reverse flag
 * .
 *
 * 09 10 2012 huangfei.xiao
 * [STP100006164] Add instrument CTP3110 support
 * Add instrument "CTP3110"
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
 * 08 16 2012 eason.lai
 * [STP100006022]  Customized intstrument porting interface
 * .
 *
 * 07 23 2012 eason.lai
 * [STP100005632]  META calibartion sharelibrary porting
 * Merge from CAL_LIB_DEV
 *
 * 07 23 2012 eason.lai
 * [STP100006023]  Share library instrument application support query API
 * .
 *
 * 07 23 2012 eason.lai
 * [STP100006022]  Customized intstrument porting interface
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
 * [STP100005632]  META calibartion sharelibrary porting
 * Merged CAL_LIB_DEV branch
 *
 * 04 19 2012 eason.lai
 * [STP100005632]  META calibartion sharelibrary porting
 * Merge ATE's instrument porting and log callback function
 *
 * 02 01 2012 yh.sung
 * [STP100005435]  [META] VS2008 project conversion
 * .
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
 * 06 29 2011 yh.sung
 * [STP100004806]  [META Calibration Library] 3G FDD item porting
 * .
 *
 * 06 13 2011 yh.sung
 * [STP100004761]  [4N tool customer release verification] - FP_Tools W1124
 * Import BROM DLL v5.1124.0
 *
 * 03 09 2011 yh.sung
 * [STP100004338]  MT6276 + OH calibration (Traditional calibration (RX LNA / 8-level PA control,  FHC (RX LNA / 8-level PA control),  NSFT)
 * CMU200 HSPA commands.
 *
 * 03 07 2011 yh.sung
 * [STP100004338]  MT6276 + OH calibration (Traditional calibration (RX LNA / 8-level PA control,  FHC (RX LNA / 8-level PA control),  NSFT)
 * Fix HSPA NSFT Bc/Bd settings
 *
 * 03 05 2011 yh.sung
 * [STP100004338]  MT6276 + OH calibration (Traditional calibration (RX LNA / 8-level PA control,  FHC (RX LNA / 8-level PA control),  NSFT)
 * CMU200 initialization.
 *
 * 03 04 2011 yh.sung
 * [STP100004338]  MT6276 + OH calibration (Traditional calibration (RX LNA / 8-level PA control,  FHC (RX LNA / 8-level PA control),  NSFT)
 * CMU200 FHC initial version
 *
 * 03 02 2011 yh.sung
 * [STP100004338]  MT6276 + OH calibration
 Traditional calibration (RX LNA / 8-level PA control
 FHC (RX LNA / 8-level PA control)
 NSFT

 *
 * set WCDMA channel power for LNA calibration
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
 * 09 09 2010 yh.sung
 * [STP100004118]  [META] Instrument shared library development
 * 20100909 check-in
 *
 * 08 07 2010 yh.sung
 * [STP100004118]  [META] Instrument shared library development
 * 0807 development
 *
 * 08 02 2010 yh.sung
 * [STP100004118]  [META] Instrument shared library development
 * [STP100004118] [META] Instrument shared library development
 * initial development branch creation
 *
*
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/
#ifndef _META_INSTRUMENT_LIBRARY_H_
#define _META_INSTRUMENT_LIBRARY_H_
#ifdef __cplusplus
extern "C" {
#endif
#if defined(__CHECK_REENTRANCY__)
#define NON_REENTRANT_FUNC __declspec(deprecated("this is not a reentrant function"))
#else
#define NON_REENTRANT_FUNC
#endif // #if !defined(__BORLANDC__)
/*****************************************************************
 * This header MUST contain only common definitions and functions
 * DO NOT include ANY RCT-dependent definitions
 *****************************************************************/
/// RCT return status code successful
const int RCTLIB_SUCCESS =  0;
/// RCT return status code failed or error
const int RCTLIB_ERROR   = -1;
/// RCT return status code successful
const int RCTLIB_ABORTED =  1;
/// RCT retrun status code not yet implemented
const int RCTLIB_NOT_YET_IMPLEMENTED = 2;

/// RCT operating mode enum value (Active Cell)
const unsigned int RCTLIB_OPERATING_MODE_ACTIVE              = 0;
/// RCT operating mode enum value (GSM BCH slot:0 BCCH, other: dummy)
const unsigned int RCTLIB_OPERATING_MODE_GSM_BCH             = 1;
/// RCT operating mode enum value (GSM BCH slot:0 BCCH, TCH and dummy)
const unsigned int RCTLIB_OPERATING_MODE_GSM_BCH_TCH         = 2;
/// RCT operating mode enum value (continuous wave)
const unsigned int RCTLIB_OPERATING_MODE_GSM_CW              = 3;
/// RCT operating mode enum value (GPRS BCH slot:0 BCCH other:dummy)
const unsigned int RCTLIB_OPERATING_MODE_GPRS_BCH            = 4;
/// RCT operating mode enum value (GPRS BCH slot:0 BCCH, PDTCH and dummy)
const unsigned int RCTLIB_OPERATING_MODE_GPRS_BCH_PDTCH      = 5;
/// RCT operating mode enum value (EGPRS BCH slot:0 other:dummy)
const unsigned int RCTLIB_OPERATING_MODE_EGPRS_BCH           = 6;
/// RCT operating mode enum value (GPRS BCH slot:0 BCCH, PDTCH and dummy)
const unsigned int RCTLIB_OPERATING_MODE_EGPRS_BCH_PDTCH     = 7;
/// RCT operating mode enum value (GSM fast handeset calibration mode)
const unsigned int RCTLIB_OPERATING_MODE_FDT                 = 8;
/// RCT operating mode enum value (WCDMA FDD test mode)
const unsigned int RCTLIB_OPERATING_MODE_WCDMA_FDD           = 9;
/// RCT operating mode enum value (cell off)
const unsigned int RCTLIB_OPERATING_MODE_CELL_OFF            = 10;
/// RCT operating mode enum value (TD test mode)
const unsigned int RCTLIB_OPERATING_MODE_TD_TEST             = 11;
const unsigned int RCTLIB_OPERATING_MODE_SIGNALING           = 12;
const unsigned int RCTLIB_OPERATING_MODE_NONSIGNALING        = 13;
#ifdef __META_C2K__
const unsigned int RCTLIB_OPERATING_MODE_C2K_TEST            = 14;
const unsigned int RCTLIB_OPERATING_MODE_C2K_CW              = 15;
const unsigned int RCTLIB_OPERATING_MODE_EVDO_TEST           = 16;
#endif //#ifdef __META_C2K__

typedef enum
{
    RCTLIB_DEVICE_UNDEF = -1,
    RCTLIB_DEVICE_AGILENT_8960 = 0,
    RCTLIB_DEVICE_CMU_200 = 1,
    RCTLIB_DEVICE_CMW_500 = 2,
    RCTLIB_DEVICE_StarPoint_6010 = 3,
    RCTLIB_DEVICE_MT_8820 = 4,
    RCTLIB_DEVICE_MT_8870 = 5,
    RCTLIB_DEVICE_CTP_3110 = 6,
    RCTLIB_DEVICE_Transcom_6280 = 7,
    RCTLIB_DEVICE_AGILENT_EXT = 8,
    RCTLIB_DEVICE_LP_IQXSTREAM = 9,
    RCTLIB_DEVICE_PXI_3000 = 10,
    RCTLIB_DEVICE_Transcom_6290 = 11,
    RCTLIB_DEVICE_CALLBACK = 12,
    /*************************
     * Add RCT support above
     ************************/
    RCTLIB_DEVICE_DUMMY,
    RCTLIB_DEVICE_NUM,

} E_RCTLIB_DEVICE_TYPE;

/* Appliaction format */
typedef enum
{
    E_INSTRMENT_APP_FORMAT_GSM_GPRS = 0,
    E_INSTRMENT_APP_FORMAT_WCDMA = 1,
    E_INSTRMENT_APP_FORMAT_TDSCDMA = 2,
#ifdef __META_LTE__
    E_INSTRMENT_APP_FORMAT_LTE = 3,
#endif //#ifdef __META_LTE__
#ifdef __META_C2K__
    E_INSTRMENT_APP_FORMAT_C2K = 4,
#endif //#ifdef __META_C2K__
    E_INSTRMENT_APP_FORMAT_COUNT
} E_INSTRMENT_APP_FORMAT;

/* Instument port enum */
typedef enum
{
    RCTLIB_RF_MAIN_INOUT_PORT = 0,
    RCTLIB_RF_RXD_OUTPUT_PORT = 1,
    RCTLIB_RF_INOUT_PORT1 = 2,
    RCTLIB_RF_INOUT_PORT2 = 3,
    RCTLIB_RF_INOUT_PORT3 = 4,
    RCTLIB_RF_INOUT_PORT4 = 5,
    RCTLIB_RF_PORT_TYPE_END
} E_RCTLIB_PORT_TYPE;

typedef int (__cdecl* ApplicationLoggingCallback_T)(void* object, const char* fmt, void* arg);
typedef int (__cdecl* ApplicationStopCallback_T)(void* object);
typedef struct
{
    /// full file path to the CFG file
    char* cfg_file_path;
    /// the instrument type
    int i_device_type;
    /// init GGE tester
    bool b_init_GGE;
    /// the instrument type for WCDMA calibration
    int i_device_type_wcdma;
    /// init WCDMA tester
    bool b_init_WCDMA;
    /// the instrument type for TD calibration
    int i_device_type_tdscdma;
    /// init TDSCDMA tester
    bool b_init_TDSCDMA;
#ifdef __META_LTE__
    /// the instrument type for LTE calibration
    int i_device_type_lte;
    /// init LTE tester
    bool b_init_LTE;
#endif //#ifdef __META_LTE__
#ifdef __META_C2K__
    /// the instrument type for C2K calibration
    int i_device_type_c2k;
    /// init C2K tester
    bool b_init_C2K;
#endif //#ifdef __META_C2K__
    /// application handle
    void* applicationHandle;
    /// callback function pointer for application;
    ApplicationLoggingCallback_T LogFunction;
    /// callback function to check the user termination
    ApplicationStopCallback_T CheckStopFunction;
} S_RCTLIB_INIT_CFG_T;
/*****************************
 * common
 *****************************/
NON_REENTRANT_FUNC int __stdcall RCTLIB_Common_Initialize(const S_RCTLIB_INIT_CFG_T* arg, size_t arg_size);
NON_REENTRANT_FUNC int __stdcall RCTLIB_Common_Connect(void);
NON_REENTRANT_FUNC int __stdcall RCTLIB_Common_Disconnect(void);
NON_REENTRANT_FUNC int __stdcall RCTLIB_Common_Reset(void);
NON_REENTRANT_FUNC int __stdcall RCTLIB_Common_SetApplicationFormat(unsigned int application_format);
NON_REENTRANT_FUNC int __stdcall RCTLIB_Common_SetOperatingMode(unsigned int operating_mode);
NON_REENTRANT_FUNC int __stdcall RCTLIB_Common_Deinitialize(void);
NON_REENTRANT_FUNC int __stdcall RCTLIB_Common_SwitchPort(E_INSTRMENT_APP_FORMAT eRctToChange, E_RCTLIB_PORT_TYPE ePort);

// reentrant functions
int __stdcall RCTLIB_Common_Initialize_r(const int meta_handle, const S_RCTLIB_INIT_CFG_T* arg, size_t arg_size);
int __stdcall RCTLIB_Common_Connect_r(const int meta_handle);
int __stdcall RCTLIB_Common_Disconnect_r(const int meta_handle);
int __stdcall RCTLIB_Common_Reset_r(const int meta_handle);
int __stdcall RCTLIB_Common_SetApplicationFormat_r(const int meta_handle, unsigned int application_format);
int __stdcall RCTLIB_Common_SetOperatingMode_r(const int meta_handle, unsigned int operating_mode);
int __stdcall RCTLIB_Common_Deinitialize_r(const int meta_handle);
int __stdcall RCTLIB_CheckStat_r(const int meta_handle, int status);
int __stdcall RCTLIB_Common_SwitchPort_r(const int meta_handle, E_INSTRMENT_APP_FORMAT eRctToChange, E_RCTLIB_PORT_TYPE ePort);

// thread safe function
int __stdcall RCTLIB_OccupyHandler(int meta_handle);
int __stdcall RCTLIB_CheckStat(int status);
int __stdcall RCTLIB_Common_GetDLLVer(unsigned int* major_ver, unsigned int* minor_ver, unsigned int* build_num, unsigned int* patch_num);
const char* __stdcall RCTLIB_Common_GetDeviceString(E_RCTLIB_DEVICE_TYPE type);
void __stdcall RCTLIB_Common_GetInsAppFormatSupport(E_RCTLIB_DEVICE_TYPE eDeviceNum, E_INSTRMENT_APP_FORMAT eAppFormat,
        bool* bTrandCalSupport, bool* bFastCalSupport);
/*****************************
 * GGE
 *****************************/
/**********************************************
 * GGE structure (shared library defined START)
 **********************************************/
/**
 * The structure for storing GGE FHC TX USS command
 */
typedef struct
{
    /// frequency band
    unsigned band;
    double m_ul_calbleloss[4];
    double m_dl_calbleloss[4];
} S_RCTLIB_GGE_Cableloss_CONFIG_T;

typedef struct
{
    /// frequency band indicator for the USS
    unsigned char           band;
    /// TCH/PDTCH ARFCN for the USS
    unsigned int                    arfcn;

    /// TCH/PDTCH mHz for the USS
    double d_mHz;

    /// mult-slot configuration for each frame in the USS
    char                                    timeslot_per_frame;
    /// APC DAC or PCL (0: PCL 1: DAC)
    unsigned char           apc_dac_pcl_sel;
    /// APC DAC selection for the USS (1: APC DAC 0: PCL)
    short                   apc_dac_pcl_value[4];
    /// PA vbias setting
    unsigned char           pa_vbias_val[4];
    /// low PCL
    unsigned char           is_low_pcl[4];
    /// repeat frame count in the USS
    int                         repeat_cnt;
} S_RCTLIB_GGE_FHC_TX_USS_T;
/**
 * The structure for storing GGE FHC TX UTS request (50 USS)
 */
typedef struct
{
    /// number of USS in the UTS
    unsigned char                      step_cnt;
    /// modulation (0:GMSK 1: EPSK)
    unsigned char                  modulation;
    /// total samples
    short                          s_measure_samples;
    /// UTS type (0: APC DAC calibration, 1: TX subband cal, 2: PCL check)
    unsigned char                  uts_type;
    /// max expected nominal power
    double                         d_max_expected_power;
    /// the number of uplink TDMA frames required in an uplink sequence step
    int                            num_frame;
    /// USS configurations
    S_RCTLIB_GGE_FHC_TX_USS_T          ApcUSS[50];
} S_RCTLIB_GGE_FHC_TX_UTS_T;
/**
 * The structure for storing GGE FHC TX UTS request (100 USS)
 */
typedef struct
{
    /// number of USS in the UTS
    unsigned char                      step_cnt;
    /// modulation (0:GMSK 1: EPSK)
    unsigned char                  modulation;
    /// total samples
    short                          s_measure_samples;
    /// UTS type (0: APC DAC calibration, 1: TX subband cal, 2: PCL check)
    unsigned char                  uts_type;
    /// max expected nominal power
    double                         d_max_expected_power;
    /// the number of uplink TDMA frames required in an uplink sequence step
    int                            num_frame;
    /// USS configurations
    S_RCTLIB_GGE_FHC_TX_USS_T          ApcUSS[100];
} S_RCTLIB_GGE_FHC_TX_UTS_BIG_T;

typedef enum
{
    RCTLIB_DB_FCB_DB = 0,
    RCTLIB_FSB_DB,
    RCTLIB_DB
} E_RCTLIB_FHC_DL_BURST_TYPE_T;

typedef struct
{
    E_RCTLIB_FHC_DL_BURST_TYPE_T BurstType[100];
    double        Freq_MHz[100];
    int           RepeatCount[100];
    double        Power_dBm[100];
    unsigned char band[100];
    short         arfcn;
    int           step_count;
    bool          doAFC;
} S_RCTLIB_FHC_DL_List_T;


/**
 * The structure for storing GGE FHC TX USS measurement result (upto 4 slots)
 */
typedef struct
{
    /// TX power measurement of slot 0 ~ slot 3
    double              d_power[4];
} S_RCTLIB_GGE_FHC_TX_USS_RESULT_T;
/**
 * The structure for storing GGE FHC TX UTS measurement resutl (upto 50 USS)
 */
typedef struct
{
    /// step counts in the UTS measurement
    unsigned char                      step_cnt;
    /// measurement results for each USS
    S_RCTLIB_GGE_FHC_TX_USS_RESULT_T   uss_result[50];
} S_RCTLIB_GGE_FHC_TX_UTS_RESULT_T;
/**
 * The structure for storing GGE FHC TX UTS measurement resutlt (upto 100 USS)
 */
typedef struct
{
    /// step counts in the UTS measurement
    unsigned char                      step_cnt;
    /// measurement results for each USS
    S_RCTLIB_GGE_FHC_TX_USS_RESULT_T   uss_result[100];
} S_RCTLIB_GGE_FHC_TX_UTS_BIG_RESULT_T;
/**
 * The structure for setting TX IQ measurement settings
 */
typedef struct
{
    /// frequency band
    unsigned int band;
    /// TCH & BCH ARFCN
    unsigned int arfcn;
    /// expected MS TX PCL
    unsigned int pcl;
    /// TSC
    unsigned int tsc;
    /// coding scheme
    unsigned int mcs;
    /// EPSK (1: EPSK, 0:GMSK)
    unsigned int epsk;
    /// config power time out
    unsigned int iTimeout;
    /// measurement count
    unsigned int iMeasureCount;
} S_RCTLIB_GGE_TXIQ_SETTINGS_T;

/**
 * The structure for fetching TX IQ measurement results
 */
typedef struct
{
    double d_sbs;
    double d_oos;
} S_RCTLIB_GGE_TXIQ_RESULT_T;

/**
 * The structure for storing GGE NSFT TEST config
 */
typedef struct
{
    /// frequency band
    unsigned band;
    /// cell power
    double bch_power;
    /// TCH power reduction
    double tch_reduction;
    /// BCH arfcn
    unsigned int bch;
    /// TCH arfcn
    unsigned int tch;
    /// initial PCL
    unsigned int pcl;
    /// timeslot
    unsigned int timeslot;
    /// TSC
    unsigned int tsc;
    /// coding scheme
    unsigned int cs;
#if 0
    // 20120402: YH commented
    // I don't know what's this?
    /// SP6010_BCH_TCH_indicator
    //unsigned int SP6010_BCH_TCH_indicator;
#endif // #if 0
} S_RCTLIB_GGE_NSFT_TESTCONFIG_T;
/**
 * The structure for storing GGE NSFT BER measurement result
 */
typedef struct
{
    /// integrity
    long   FBERIntegrity;
    /// tested bits
    double FBERBitsTested;
    /// BER
    double FBERRatio;
    /// Bit error count
    double FBERCount;
    /// progress
    double progress;
    /// number of CRC errors
    double crc_error;
} S_RCTLIB_GGE_NSFT_BER_RESULT_T;
/**
 * The structure for storing GGE NSFT TX measurement result (PFER part)
 */
typedef struct
{
    /// min frequency error
    double MinFErr;
    /// max frequency error
    double MaxFErr;
    /// average frequency error
    double AvgFErr;
    /// worst peak frequency error
    double WorstFErr;
    /// min peak phase error
    double MinPKPErr;
    /// max peak phase error
    double MaxPKPErr;
    /// average peak phase error
    double AvgPKPErr;
    /// min RMS phase error
    double MinRMSPErr;
    /// max RMS phase error
    double MaxRMSPErr;
    /// average RMS phse error
    double AvgRMSPErr;
} S_RCTLIB_GGE_NSFT_PFER_RESULT_T;
/**
 * The structure for storing GGE NSFT TX measurement result (ORFS part)
 */
typedef struct
{
    /// modulation specturm (relative)
    double mod_spectrum[22];
    /// modulation specturm (absolute)
    double mod_spectrum_abs[22];
    /// switching specturm
    double switch_spectrum[8];
    /// ref. power of modulation spectrum
    double mod_ref_power;
} S_RCTLIB_GGE_NSFT_ORFS_RESULT_T;
/**
 * The structure for storing GGE NSFT EPSK measurement result (EVM part)
 */
typedef struct
{
    /// EVM 95 percentile
    double EVM_95P;
    /// magnitude error 95 percentile
    double MagErr_95P;
    /// phase error 95 percentile Agilent8960 is not supported
    double Pherr_95P;
    /// peak EVM Agilent8960 is not supported
    double PK_EVM;
    /// RMS EVM
    double RMS_EVM;
    /// peak magnitude error
    double PK_MagErr;
    /// RMS magnitude error
    double RMS_MagErr;
    /// peak RMS magnitude error
    double RMS_MagErrPeak;
    /// peak phase error
    double PK_Pherr;
    /// RMS phase error
    double RMS_Pherr;
    /// peak RMS phase error
    double RMS_PherrPeak;
    /// original offset
    double orig_offset;
    /// frequency error
    double FErr;
    /// Amplitude droop
    double Amp_Droop;
    /// IQ imbalance
    double IQ_Imbalance;
    /// Timing Alignment (Agilent8960 need new application (application #?) CMU supported)
    double TA;
    /// AM/PM Alignment
    double AmPm;
} S_RCTLIB_GGE_NSFT_EMAC_RESULT_T;
/**
 * The structure for storing GGE NSFT TX measurement result (power/pvt part)
 */
typedef struct
{
    /// burst match or not
    bool b_burst_match;
    /// TX power value
    double tx_power;
} S_RCTLIB_GGE_NSFT_TXPOWER_RESULT_T;
/**
 * The structure for storing GGE NSFT GMSK measurement result
 */
typedef struct
{
    S_RCTLIB_GGE_NSFT_TXPOWER_RESULT_T txp_result;
    S_RCTLIB_GGE_NSFT_PFER_RESULT_T pfer_result;
    S_RCTLIB_GGE_NSFT_ORFS_RESULT_T orfs_result;
} S_RCTLIB_GGE_NSFT_GMSK_RESULT_T;
/**
 * The structure for storing GGE NSFT EPSK measurement result
 */
typedef struct
{
    S_RCTLIB_GGE_NSFT_TXPOWER_RESULT_T txp_result;
    S_RCTLIB_GGE_NSFT_EMAC_RESULT_T ema_result;
    S_RCTLIB_GGE_NSFT_ORFS_RESULT_T orfs_result;
} S_RCTLIB_GGE_NSFT_EPSK_RESULT_T;
/**
 * The structure for setting CAP ID calibration settings
 */
typedef struct
{
    /// band indicator (0: GSM450 / 1: GSM850 / 2: GSM900 / 3: DCS1800 / 4: PCS1900)
    unsigned int band;
    /// measurement ARFCN
    unsigned int arfcn;
    /// expected MS TX PCL
    unsigned int pcl;
    /// expected MS TX TSC
    unsigned int tsc;
    /// number of multiple measurement
    unsigned int measurementCount;
    /// measurement timeout setting (ms)
    double timeout;
} S_RCTLIB_GGE_CAPID_SETTINGS_T;
/**
 * The structure for setting AFC calibration settings
 */
typedef struct
{
    /// band indicator (0: GSM450 / 1: GSM850 / 2: GSM900 / 3: DCS1800 / 4: PCS1900)
    unsigned int band;
    /// BCH ARFCN
    unsigned int arfcn;
    /// downlink power for used timeslot (dBm)
    double d_used;
    /// downlink power for unused timeslot (dB)
    double d_unused;
    /// frequency offset
    double d_offset;
    /// Continuous wave mode indicator
    unsigned char CWmode;
    /// TSC
    unsigned int tsc;
} S_RCTLIB_GGE_AFC_SETTINGS_T;
/**
 * The structure for setting analyzer frequency offset
 */
typedef struct
{
    /// center frequency (Unit: MHz)
    double centerFrequency;
    /// frequency offset to center frequency (Unit: MHz)
    double frequencyOffset;
    /// manual control of the analyzer frequency offset (manual: 1, the center frequency/ frequency offset is used; auto: 0, both are not used)
    unsigned char manualControl;
} S_RCTLIB_GGE_FREQUENCY_OFFSET_SETTINGS_T;
/**
 * The structure for setting FB DAC calibration settings
 */
typedef struct
{
    /// band indicator (0: GSM450 / 1: GSM850 / 2: GSM900 / 3: DCS1800 / 4: PCS1900)
    unsigned int band;
    /// BCH & TCH ARFCN
    unsigned int arfcn;
    /// expected MS TX PCL
    unsigned int pcl;
    /// TSC
    unsigned int tsc;
    /// Measurement count
    unsigned int iMeasureCount;
    /// config power time out
    unsigned int iTimeout;
} S_RCTLIB_GGE_FBDAC_SETTINGS_T;

/**
 * The structure for setting TX Slope Skew calibration settings
 */
typedef struct
{
    /// band indicator (0: GSM450 / 1: GSM850 / 2: GSM900 / 3: DCS1800 / 4: PCS1900)
    unsigned int band;
    /// TCH & BCH ARFCN
    unsigned int arfcn;
    /// expected MS TX PCL
    unsigned int pcl;
    /// TSC
    unsigned int tsc;
    /// MCS
    unsigned int mcs;
    /// Measurement count
    unsigned int iMeasureCount;
    /// config power time out
    unsigned int iTimeout;
} S_RCTLIB_GGE_TXSLOPESKEW_SETTINGS_T;

/**
 * The structure for setting TRX Offset calibration settings
 */
typedef struct
{
    /// band indicator (0: GSM450 / 1: GSM850 / 2: GSM900 / 3: DCS1800 / 4: PCS1900)
    unsigned int band;
    /// TCH & BCH ARFCN
    unsigned int arfcn;
    /// expected MS TX PCL
    unsigned int pcl;
    /// cell power (dbm)
    double   d_used;
    /// TSC
    unsigned int tsc;
    /// time slot
    unsigned int iTimeslot;
    /// Measurement count
    unsigned int iMeasureCount;
    /// config power time out
    unsigned int iTimeout;
} S_RCTLIB_GGE_TRXOFFSET_SETTINGS_T;
/**
 * Description: GSM & EDGE intrument's spcial settings
 */
typedef struct
{
    /// TX IQ normal burst type
    int iTxIQ_BurstTypeNB;
    /// NSFT GSM time slot
    int iNSFT_GSM_TimeSlot;
    /// NSFT EDGE time slot
    int iNSFT_EDGE_TimeSlot;
    /// NSFT GSM tsc
    int iNSFT_GSM_tsc;
    /// NSFT EDGE tsc
    int iNSFT_EDGE_tsc;
    /// FHC fine sync SCB number
    int iFHC_fsSCB;
    /// FHC DTS Max Step Count
    int iFHC_DTS_MaxStepCount;
    /// FHC UTS Max Step Count
    int iFHC_UTS_MaxStepCount;
    /// FHC DTS Multiple Band Support
    int iFHC_DTS_MultiBand; // 0: single band, 1: high low band combine, 2: quad band combine
    /// FHC UTS Multiple Band Support
    int iFHC_UTS_MultiBand; // 0: single band, 1: high low band combine, 2: quad band combine
    /// Is cell power be overwrite
    bool bOverwriteNSFTCellPower;
    /// real cell power
    double dRealNSFTCellPower;
} S_RCTLIB_GGE_SPECIFIC_SETTINGS_T;



typedef struct
{
    unsigned char cmd_type;
} S_RCTLIB_GGE_NSFT_LIST_MODE_COMMON_T;
typedef struct
{
    /// Sync information
    S_RCTLIB_GGE_NSFT_LIST_MODE_COMMON_T common;
    /// band indicator (0: GSM450 / 1: GSM850 / 2: GSM900 / 3: DCS1800 / 4: PCS1900)
    unsigned int sync_band;
    /// BCH arfcn
    unsigned int sync_arfcn;
    /// sync power
    int sync_power;
    /// sync slot offset
    unsigned char sync_slot_offset;
} S_RCTLIB_GGE_NSFT_LIST_MODE_SYNC_T;

typedef struct
{
    /// Trigger information
    S_RCTLIB_GGE_NSFT_LIST_MODE_COMMON_T common;
    /// band indicator (0: GSM450 / 1: GSM850 / 2: GSM900 / 3: DCS1800 / 4: PCS1900)
    unsigned int trigger_band;
    /// TCH arfcn
    unsigned int trigger_arfcn;
    /// TSC
    unsigned int trigger_tsc;
    /// Modulation
    unsigned char trigger_rtx_types;
    /// TX pcl
    unsigned int trigger_pcl;
} S_RCTLIB_GGE_NSFT_LIST_MODE_TRIGGER_T;

typedef struct
{
#define MAX_MEASURE_NUM 8
    /// Trigger information
    S_RCTLIB_GGE_NSFT_LIST_MODE_COMMON_T common;
    /// band indicator (0: GSM450 / 1: GSM850 / 2: GSM900 / 3: DCS1800 / 4: PCS1900)
    unsigned int band;
    /// TCH arfcn
    unsigned int arfcn;
    /// TSC
    unsigned int tsc;
    /// Modulation (0: GMSK / 1: EPSK)
    unsigned char rtx_type;
    /// RX power
    int RX_power;
    /// Test pcl count
    int valid_test_count;
    /// TX pcl
    int tx_pcl[MAX_MEASURE_NUM];
    /// TX test count
    int repeat_count[MAX_MEASURE_NUM];
    /// Measurement slot offset
    unsigned char meas_slot_offset;
} S_RCTLIB_GGE_NSFT_LIST_MODE_MEASURE_T;

typedef union
{
    S_RCTLIB_GGE_NSFT_LIST_MODE_SYNC_T    sync;
    S_RCTLIB_GGE_NSFT_LIST_MODE_TRIGGER_T trigger;
    S_RCTLIB_GGE_NSFT_LIST_MODE_MEASURE_T test;
} S_RCTLIB_GGE_NSFT_LIST_MODE_COMMAND_T;

#define GGE_LIST_MODE_NSFT_MAX_SYNC_CMD_NUM    5
#define GGE_LIST_MODE_NSFT_MAX_TRIGGER_CMD_NUM 5
#define GGE_LIST_MODE_NSFT_MAX_MEAS_CMD_NUM    50

#define GGE_LIST_MODE_NSFT_MAX_MEAS_PCL_NUM    8

#define GGE_LIST_MODE_NSFT_MAX_CMD_NUM   \
    GGE_LIST_MODE_NSFT_MAX_MEAS_CMD_NUM + \
    GGE_LIST_MODE_NSFT_MAX_TRIGGER_CMD_NUM + \
    GGE_LIST_MODE_NSFT_MAX_SYNC_CMD_NUM // (Test + Sync + Trigger)
typedef struct
{
    unsigned int cmd_count;
    S_RCTLIB_GGE_NSFT_LIST_MODE_COMMAND_T nsft_cmd[GGE_LIST_MODE_NSFT_MAX_CMD_NUM];
} S_RCTLIB_GGE_NSFT_LIST_MODE_SETTINGS_T;

typedef union
{
    S_RCTLIB_GGE_NSFT_GMSK_RESULT_T gmsk;
    S_RCTLIB_GGE_NSFT_EPSK_RESULT_T epsk;
} S_RCTLIB_GGE_NSFT_LIST_MODE_RESULT_ELEMENT_T;

typedef struct
{
    S_RCTLIB_GGE_NSFT_LIST_MODE_RESULT_ELEMENT_T result[GGE_LIST_MODE_NSFT_MAX_CMD_NUM][GGE_LIST_MODE_NSFT_MAX_MEAS_PCL_NUM];
} S_RCTLIB_GGE_NSFT_LIST_MODE_RESULT_T;
/**********************************************
 * GGE function (shared library defined START)
 **********************************************/
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_Cableloss_Settings(S_RCTLIB_GGE_Cableloss_CONFIG_T cable_loss);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_ConfigCellPower(double power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_ConfigDefaultSettings(void);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_ConfigAnalyzerFrequencyOffset(const S_RCTLIB_GGE_FREQUENCY_OFFSET_SETTINGS_T* pSettings, unsigned int sz);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_CAPID_PreSettings(const S_RCTLIB_GGE_CAPID_SETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_CAPID_Iteration(double* frequency_error);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_AFC_PreSettings(const S_RCTLIB_GGE_AFC_SETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_AGC_PreSettings(double d_power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_AGC_ChangeCellBand(unsigned int band);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_AGC_ChangeChannel(unsigned int arfcn);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_APCDCOffset_PreSettings(unsigned int tsc);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_APCDCOffset_ChangeCellBand(unsigned int band);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_APCDCOffset_Iteration(unsigned int arfcn, double expected_power, int PCL, double* d_power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_Pedestal_DCOffset_Iteration(unsigned int arfcn, double expected_power, double* d_power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_EDGE_APCDCOffset_PreSettings(unsigned int tsc);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_EDGE_APCDCOffset_ChangeCellBand(unsigned int band);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_EDGE_APCDCOffset_Iteration(unsigned int arfcn, double expected_power, int PCL, double* d_power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_EDGE_APC_SetExceptedPower(double expected_power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_EDGE_APC_Iteration(unsigned int arfcn, double* d_power);

NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FHC_DTS_PreSettings();
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FHC_DTS_Iteration(S_RCTLIB_FHC_DL_List_T List, int ListLength);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FHC_DTS_START();
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FHC_DTS_STOP();

NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FHC_UTS_PreSettings();
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FHC_UTS_Iteration( S_RCTLIB_GGE_FHC_TX_UTS_T* uts);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FHC_UTS_FetchResult(const S_RCTLIB_GGE_FHC_TX_UTS_T* uts, S_RCTLIB_GGE_FHC_TX_UTS_RESULT_T* uts_result);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FHC_UTS_Iteration_Ex( S_RCTLIB_GGE_FHC_TX_UTS_BIG_T* uts);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FHC_UTS_FetchResult_Ex(const S_RCTLIB_GGE_FHC_TX_UTS_BIG_T* uts, S_RCTLIB_GGE_FHC_TX_UTS_BIG_RESULT_T* uts_result);

NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FBDAC_PreSettings(const S_RCTLIB_GGE_FBDAC_SETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_FBDAC_Iteration(double* d_power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_TXIQ_PreSettings(const S_RCTLIB_GGE_TXIQ_SETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_TXIQ_ChangeBand(const S_RCTLIB_GGE_TXIQ_SETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_TXIQ_Iteration(const S_RCTLIB_GGE_TXIQ_SETTINGS_T* pSettings, S_RCTLIB_GGE_TXIQ_RESULT_T* pTxIqResult);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_TXSlopeSkew_PreSettings(const S_RCTLIB_GGE_TXSLOPESKEW_SETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_TXSlopeSkew_Iteration(double* d_mod_depth);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_TRXOffset_PreSettings(const S_RCTLIB_GGE_TRXOFFSET_SETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_TRXOffset_InitAFC(const S_RCTLIB_GGE_TRXOFFSET_SETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_TRXOffset_Iteration(double* frequency_err);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_NSFT_PreSettings(unsigned int measurement_count, unsigned int ber_count);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_NSFT_GMSKInit(const S_RCTLIB_GGE_NSFT_TESTCONFIG_T* nsft_config);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_NSFT_EPSKInit(const S_RCTLIB_GGE_NSFT_TESTCONFIG_T* nsft_config);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_NSFT_BERInit(const S_RCTLIB_GGE_NSFT_TESTCONFIG_T* nsft_config);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_NSFT_ChangePCL(int b_EPSK, unsigned int pcl);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_NSFT_ReadGMSKPerformance(S_RCTLIB_GGE_NSFT_GMSK_RESULT_T* gmsk_result);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_NSFT_InitiateBER();
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_NSFT_FetchBER(S_RCTLIB_GGE_NSFT_BER_RESULT_T* ber_result);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_NSFT_ReadEPSKPerformance(S_RCTLIB_GGE_NSFT_EPSK_RESULT_T* epsk_result);
NON_REENTRANT_FUNC int __stdcall RCTLIB_GGE_GET_SpecificSettings(S_RCTLIB_GGE_SPECIFIC_SETTINGS_T* pSettings);

// reentrant functions
int __stdcall RCTLIB_GGE_Cableloss_Settings_r(const int meta_handle, S_RCTLIB_GGE_Cableloss_CONFIG_T cable_loss);
int __stdcall RCTLIB_GGE_ConfigCellPower_r(const int meta_handle, double power);
int __stdcall RCTLIB_GGE_ConfigDefaultSettings_r(const int meta_handle);
int __stdcall RCTLIB_GGE_ConfigAnalyzerFrequencyOffset_r(const int meta_handle, const S_RCTLIB_GGE_FREQUENCY_OFFSET_SETTINGS_T* pSettings, unsigned int sz);
int __stdcall RCTLIB_GGE_CAPID_PreSettings_r(const int meta_handle, const S_RCTLIB_GGE_CAPID_SETTINGS_T* pSettings);
int __stdcall RCTLIB_GGE_CAPID_Iteration_r(const int meta_handle, double* frequency_error);
int __stdcall RCTLIB_GGE_AFC_PreSettings_r(const int meta_handle, const S_RCTLIB_GGE_AFC_SETTINGS_T* pSettings);
int __stdcall RCTLIB_GGE_AGC_PreSettings_r(const int meta_handle, double d_power);
int __stdcall RCTLIB_GGE_AGC_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_GGE_AGC_ChangeChannel_r(const int meta_handle, unsigned int arfcn);
int __stdcall RCTLIB_GGE_APCDCOffset_PreSettings_r(const int meta_handle, unsigned int tsc);
int __stdcall RCTLIB_GGE_APCDCOffset_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_GGE_APCDCOffset_Iteration_r(const int meta_handle, unsigned int arfcn, double expected_power, int PCL, double* d_power);
int __stdcall RCTLIB_GGE_Pedestal_DCOffset_Iteration_r(const int meta_handle, unsigned int arfcn, double expected_power, double* d_power);
int __stdcall RCTLIB_GGE_EDGE_APCDCOffset_PreSettings_r(const int meta_handle, unsigned int tsc);
int __stdcall RCTLIB_GGE_EDGE_APCDCOffset_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_GGE_EDGE_APCDCOffset_Iteration_r(const int meta_handle, unsigned int arfcn, double expected_power, int PCL, double* d_power);
int __stdcall RCTLIB_GGE_EDGE_APC_SetExceptedPower_r(const int meta_handle, double expected_power);
int __stdcall RCTLIB_GGE_EDGE_APC_Iteration_r(const int meta_handle, unsigned int arfcn, double* d_power);

int __stdcall RCTLIB_GGE_FHC_DTS_PreSettings_r(const int meta_handle);
int __stdcall RCTLIB_GGE_FHC_DTS_Iteration_r(const int meta_handle, S_RCTLIB_FHC_DL_List_T List, int ListLength);
int __stdcall RCTLIB_GGE_FHC_DTS_START_r(const int meta_handle);
int __stdcall RCTLIB_GGE_FHC_DTS_STOP_r(const int meta_handle);

int __stdcall RCTLIB_GGE_FHC_UTS_PreSettings_r(const int meta_handle);
int __stdcall RCTLIB_GGE_FHC_UTS_Iteration_r(const int meta_handle, S_RCTLIB_GGE_FHC_TX_UTS_T* uts);
int __stdcall RCTLIB_GGE_FHC_UTS_FetchResult_r(const int meta_handle, const S_RCTLIB_GGE_FHC_TX_UTS_T* uts, S_RCTLIB_GGE_FHC_TX_UTS_RESULT_T* uts_result);
int __stdcall RCTLIB_GGE_FHC_UTS_Iteration_Ex_r(const int meta_handle, S_RCTLIB_GGE_FHC_TX_UTS_BIG_T* uts);
int __stdcall RCTLIB_GGE_FHC_UTS_FetchResult_Ex_r(const int meta_handle, const S_RCTLIB_GGE_FHC_TX_UTS_BIG_T* uts, S_RCTLIB_GGE_FHC_TX_UTS_BIG_RESULT_T* uts_result);

int __stdcall RCTLIB_GGE_FBDAC_PreSettings_r(const int meta_handle, const S_RCTLIB_GGE_FBDAC_SETTINGS_T* pSettings);
int __stdcall RCTLIB_GGE_FBDAC_Iteration_r(const int meta_handle, double* d_power);
int __stdcall RCTLIB_GGE_TXIQ_PreSettings_r(const int meta_handle, const S_RCTLIB_GGE_TXIQ_SETTINGS_T* pSettings);
int __stdcall RCTLIB_GGE_TXIQ_ChangeBand_r(const int meta_handle, const S_RCTLIB_GGE_TXIQ_SETTINGS_T* pSettings);
int __stdcall RCTLIB_GGE_TXIQ_Iteration_r(const int meta_handle, const S_RCTLIB_GGE_TXIQ_SETTINGS_T* pSettings, S_RCTLIB_GGE_TXIQ_RESULT_T* pTxIqResult);
int __stdcall RCTLIB_GGE_TXSlopeSkew_PreSettings_r(const int meta_handle, const S_RCTLIB_GGE_TXSLOPESKEW_SETTINGS_T* pSettings);
int __stdcall RCTLIB_GGE_TXSlopeSkew_Iteration_r(const int meta_handle, double* d_mod_depth);
int __stdcall RCTLIB_GGE_TRXOffset_PreSettings_r(const int meta_handle, const S_RCTLIB_GGE_TRXOFFSET_SETTINGS_T* pSettings);
int __stdcall RCTLIB_GGE_TRXOffset_InitAFC_r(const int meta_handle, const S_RCTLIB_GGE_TRXOFFSET_SETTINGS_T* pSettings);
int __stdcall RCTLIB_GGE_TRXOffset_Iteration_r(const int meta_handle, double* frequency_err);
int __stdcall RCTLIB_GGE_NSFT_PreSettings_r(const int meta_handle, unsigned int measurement_count, unsigned int ber_count);
int __stdcall RCTLIB_GGE_NSFT_GMSKInit_r(const int meta_handle, const S_RCTLIB_GGE_NSFT_TESTCONFIG_T* nsft_config);
int __stdcall RCTLIB_GGE_NSFT_EPSKInit_r(const int meta_handle, const S_RCTLIB_GGE_NSFT_TESTCONFIG_T* nsft_config);
int __stdcall RCTLIB_GGE_NSFT_BERInit_r(const int meta_handle, const S_RCTLIB_GGE_NSFT_TESTCONFIG_T* nsft_config);
int __stdcall RCTLIB_GGE_NSFT_ChangePCL_r(const int meta_handle, int b_EPSK, unsigned int pcl);
int __stdcall RCTLIB_GGE_NSFT_ReadGMSKPerformance_r(const int meta_handle, S_RCTLIB_GGE_NSFT_GMSK_RESULT_T* gmsk_result);
int __stdcall RCTLIB_GGE_NSFT_InitiateBER_r(const int meta_handle);
int __stdcall RCTLIB_GGE_NSFT_FetchBER_r(const int meta_handle, S_RCTLIB_GGE_NSFT_BER_RESULT_T* ber_result);
int __stdcall RCTLIB_GGE_NSFT_ReadEPSKPerformance_r(const int meta_handle, S_RCTLIB_GGE_NSFT_EPSK_RESULT_T* epsk_result);
int __stdcall RCTLIB_GGE_GET_SpecificSettings_r(const int meta_handle, S_RCTLIB_GGE_SPECIFIC_SETTINGS_T* pSettings);
int __stdcall RCTLIB_GGE_LIST_MODE_NSFT_PreSetting_r(const int meta_handle);
int __stdcall RCTLIB_GGE_LIST_MODE_NSFT_InitiateTestPlan_r(const int meta_handle, const S_RCTLIB_GGE_NSFT_LIST_MODE_SETTINGS_T* pSettings);
int __stdcall RCTLIB_GGE_LIST_MODE_NSFT_FetchTestPlanResult_r(const int meta_handle, const S_RCTLIB_GGE_NSFT_LIST_MODE_SETTINGS_T* pSettings, S_RCTLIB_GGE_NSFT_LIST_MODE_RESULT_T* pResult);

/**********************************************
 * GGE function (shared library defined END)
 **********************************************/
/*****************************
 * WCDMA
 *****************************/

/**********************************************
 * WCDMA structure (shared library defined START)
 **********************************************/
/**
 * Descriptions: WCDMA AGC PreSetting
 */
typedef struct
{
    /// cell power for AGC calibration
    double cellPower;
    /// CPICH power (dB)
    double cpichPower;
    /// PICH power (dB)
    double pichPower;
    /// PCCPCH power (dB)
    double pccpchPower;
    /// DPCH power (dB)
    double dpchPower;
} S_RCTLIB_WCDMA_AGC_PRESETTINGS_T;
/**
 * Descriptions: WCDMA APC PreSetting
 */
typedef struct
{
    /// measurement timeout setting (ms)
    double timeout;
    /// measurement interval (us)
    double measurementInterval;
    /// trigger delay (us)
    double triggerDelay;
} S_RCTLIB_WCDMA_APC_PRESETTINGS_T;
typedef struct
{
    /// measurement timeout setting (ms)
    double timeout;
    /// measurement interval (us)
    double measurementInterval;
    /// trigger delay (us)
    double triggerDelay;
    unsigned int triggerType; //trigger type 0:immediate 1:Rise
} S_RCTLIB_WCDMA_APC_PRESETTINGS_EX_T;
typedef struct
{
    /// step witch unit: ms
    double stepWidth;
    /// CPICH power (dB)
    double cpichPower;
    /// PICH power (dB)
    double pichPower;
    /// PCCPCH power (dB)
    double pccpchPower;
    /// DPCH power (dB)
    double dpchPower;
} S_RCTLIB_WCDMA_FHC_PRESETTINGS_T;
typedef struct
{
    /// UARFCN in MHz
    double mHz;
    /// UARFCN
    unsigned short uarfcn;
} S_RCTLIB_WCDMA_FHC_FREQ_STEP_U;
/**
 * The structure for storing WCDMA FHC request
 */
typedef struct
{
    /// band
    unsigned int e_band;
    /// measurement timeout setting
    double d_meas_timeout_sec;
    /// start index of UE TX power step
    int    txPowerStepStartIndex;
    /// start index of UE TX frequency step
    int    txFrequencyStepStartIndex;
    /// start index of UE RX power step
    int    rxPowerStepStartIndex;
    /// start index of UE RX frequency step
    int    rxFrequencyStepStartIndex;
    /// number of power step
    int    numberOfPowerSteps;
    /// number of frequency step
    int    numberOfFrequencySteps;
    /// expected TX power level (dBm)
    double txPowerSteps[20];
    /// downlink power level (dBm)
    double rxPowerSteps[20];
    /// UE TX frequency setting in each frequency step (UARFCN or MHz)
    S_RCTLIB_WCDMA_FHC_FREQ_STEP_U txFreqSteps[20];
    /// UE RX frequency setting in each frequency step (UARFCN or MHz)
    S_RCTLIB_WCDMA_FHC_FREQ_STEP_U rxFreqSteps[20];
} S_RCTLIB_WCDMA_FHC_MEASUREMENT_PARAM_T;
/**
 * The structure for storing WCDMA FHC TX power result
 */
typedef struct
{
    /// integrity of the measurement result
    int    integrity;
    /// frequency step
    int    numberOfFrequencySteps;
    /// power step
    int    numberOfPowerSteps;
    /// frequency step * power step count
    int    tx_pwr_cnt;
    /// [OUT] power measurement result array
    double d_tx_power[400];
    /// [OUT] power measurement result count
    int    real_cnt;
} S_RCTLIB_WCDMA_FHC_MEASUREMENT_RESULT_T;
/**
 * The structure for storing WCDMA NSFT TPC control used in TX performance
 */
typedef struct
{
    /// specify the test pattern (0: All up for UE max power, 1: All down for UE min power, 2: active for specified power
    int i_Pattern;
    /// TPC algorithm  (1: algo1 2: algo2)
    unsigned int u_Algorithm;
    /// TPC step size
    int i_Step;
    /// the target power if the i_Pattern is 2, expected power if the tpc pattern is 0 or 1 (all up or all down)
    double d_TargetPower;
} S_RCTLIB_WCDMA_NSFT_TPC_REQUEST_T;
/**
 * The structure for storing WCDMA NSFT BER result
 */
typedef struct
{
    /// BER
    double d_ber;
    /// bit error count
    int i_err_cnt;
    /// total test count
    int i_total_cnt;
} S_RCTLIB_WCDMA_NSFT_BER_RESULT_T;
/**
 * The structure for storing WCDMA NSFT PRACH result
 */
typedef struct
{
    /// TX on power
    double d_on_power;
    /// TX power before TX on
    double d_before_power;
    /// TX power after  TX on
    double d_after_power;
    /// error between the actual power and expected power
    double d_error;
} S_RCTLIB_WCDMA_NSFT_PRACH_RESULT_T;
/**
 * The structure for storing WCDMA NSFT SEM result
 */
typedef struct
{
    /// pass flag (overall)
    bool bPass;
    /// SEM level results
    double d_sem_level[8];
    /// frequency offset for each SEM level
    double d_sem_freq_offset[8];
    /// margin for each SEM result
    double d_sem_mask_margin[8];
    /// SEM pass flag
    int    i_sem_pass[8];
} S_RCTLIB_WCDMA_NSFT_SEM_RESULT_T;
/**
 * The structure for storing WCDMA NSFT WWQ result
 */
typedef struct
{
    /// EVM (average, dB)
    double d_evm_rms_average;
    /// max frequency error (max, Hz)
    double d_evm_max_freq_error;
    /// OOS (average, dB)
    double d_evm_origin_offset;
    /// PCDE (max, dB)
    double d_pcde;
} S_RCTLIB_WCDMA_NSFT_WWQ_RESULT_T;
/**
 * The structure for storing WCDMA NSFT ILPC result
 */
typedef struct
{
    /// integrity
    int     i_Integrity;
    /// pass flag (overall)
    bool    bPass;
    /// number of slots
    int     i_NumSlots;
    /// power (ABS)
    double  d_Absolute[100];
    /// delta value between each step
    double  d_Delta[100];
    bool    bCal_fail;
} S_RCTLIB_WCDMA_NSFT_ILPC_RESULT_T;
/**
 * the structure for storing WCDMA NSFT spectrum measurement result
 */
typedef struct
{
    /// ACLR at negative 10 MHz (dB)
    double m_dOffsetn10;
    /// ACLR at negative 5 MHz (dB)
    double m_dOffsetn5;
    /// ACLR at positive 5 MHz (dB)
    double m_dOffsetp5;
    /// ACLR at positive 10 MHz (dB)
    double m_dOffsetp10;
    /// Occupied bandwidth (MHz)
    double m_dOBW;
} S_RCTLIB_WCDMA_NSFT_SPECTRUM_RESULT_T;
/**
 * the structure for storing WCDMA NSFT TX performance (max power) measurement result
 */
typedef struct
{
    /// UE power
    double m_dUEPower;
    /// SEM test result (emission mask)
    S_RCTLIB_WCDMA_NSFT_SEM_RESULT_T semResult;
    /// WWQ test result
    S_RCTLIB_WCDMA_NSFT_WWQ_RESULT_T wwqResult;
    /// spectrum test result (ACLR, OBW)
    S_RCTLIB_WCDMA_NSFT_SPECTRUM_RESULT_T spectrumResult;
} S_RCTLIB_WCDMA_NSFT_TX_PERF_MAX_POWER_RESULT_T;
/**
 * the structure for storing WCDMA NSFT TX performance (min power) measurement result
 */
typedef struct
{
    /// UE power
    double m_dUEPower;
} S_RCTLIB_WCDMA_NSFT_TX_PERF_MIN_POWER_RESULT_T;
/**
 * Descriptions: WCDMA NSFT PreSetting
 */
typedef struct
{
    char seg;
    double start_power;
    double stop_power;
    // single step error
    double single_step_error_algo1_1dB_upper[2];// TPC cmd: +1, -1
    double single_step_error_algo1_1dB_lower[2];// TPC cmd: +1, -1
    double single_step_error_algo1_2dB_upper[2];// TPC cmd: +1, -1
    double single_step_error_algo1_2dB_lower[2];// TPC cmd: +1, -1
    double single_step_error_algo2_upper[3];// +1, 0, -1
    double single_step_error_algo2_lower[3];// +1, 0, -1
    // aggregate step error (10 steps)
    double aggregate_step_error_algo1_1dB_upper[2];// +1, -1
    double aggregate_step_error_algo1_1dB_lower[2];// +1, -1
    double aggregate_step_error_algo1_2dB_upper[2];// +1, -1
    double aggregate_step_error_algo1_2dB_lower[2];// +1, -1
    double aggregate_step_error_algo2_upper[3];// +1, 0, -1
    double aggregate_step_error_algo2_lower[3];// +1, 0, -1
} S_RCTLIB_WCDMA_NSFT_ILPC_CONFIG_T;
/**
 * Descriptions: WCDMA NSFT PreSetting
 */
typedef struct
{
    /// measurement timeout value (ms)
    double timeout;
    /// cell power for UE NSFT sync
    double cellPower;
    /// BER test count;
    unsigned int ber_bit_count;
    /// TFCI
    unsigned int tfci;
    /// SC code
    unsigned int sc_code;
    /// OVSF
    unsigned int ovsf;
    /// downlink data pattern
    unsigned int dtch_data_type;
    /// CPICH power (dB)
    double cpichPower;
    /// PICH power (dB)
    double pichPower;
    /// PCCPCH power (dB)
    double pccpchPower;
    /// DPCH power (dB)
    double dpchPower;
    /// ILPC config
    S_RCTLIB_WCDMA_NSFT_ILPC_CONFIG_T ilpcConfig;
} S_RCTLIB_WCDMA_NSFT_PRESETTINGS_T;
/**
 * WCDMA NSFT test case config
 */
typedef struct
{
    /// uplink UARFCN
    unsigned int uarfcn_ul;
    /// downlink UARFCN
    unsigned int uarfcn_dl;
    /// uplink cable loss
    double cableloss_ul;
    /// downlink cable loss
    double cableloss_dl;
    /// init cell power
    double cell_power;
    /// ILPC Test segment
    unsigned char testSegment;
} S_RCTLIB_WCDMA_NSFT_CONFIG_T;
/**
 * WCDMA NSFT PRACH pre setting
 */
typedef struct
{
    /// timeout (ms)
    double timeout;
    /// PRACH Test Uplink Interference (dBm)
    double uplinkInterference;
    /// PRACH Test Primary CPICH Power (dBm)
    double pcpichPower;
    /// PRACH Test Constant Value
    double constantValue;
    /// PRACH Test CPICH Level offset (dB)
    double cpichLevelOffset;
} S_RCTLIB_WCDMA_NSFT_PRACH_PRESETTING_T;
/**
 * WCDMA NSFT PRACH test case config
 */
typedef struct
{
    /// uplink UARFCN
    unsigned int uarfcn_ul;
    /// downlink UARFCN
    unsigned int uarfcn_dl;
    /// uplink cable loss
    double cableloss_ul;
    /// downlink cable loss
    double cableloss_dl;
} S_RCTLIB_WCDMA_NSFT_PRACH_CONFIG_T;
/**
 * Descriptions: WCDMA HSPA NSFT Presetting
 */
typedef struct
{
    /// HSDSCH UE category
    unsigned int ueCategory;
    /// measurement timeout value (ms)
    double timeout;
    /// delta ACK
    int deltaAck;
    /// delta NACK
    int deltaNack;
    /// delta CQI
    int deltaCqi;
    /// CQI feedback cycle
    int cqiFeedbackCycle;
    /// CQI repetition factor
    int cqiRepetitionFactor;
    int ovsf256;
    int ovsf128;
    int eagchChannelizationCode;
    int ehichChannelizationCode;
    int firstHspdschChannelizationCode;
    int hsscch1ChannelizationCode;
    double hspaFddTestCpichLevel;
    double hspaFddTestPccpchLevel;
    double hspaFddTestPichLevel;
    double hspaFddTestDpchLevel;
    double hspaFddTestEagchLevel;
    double hspaFddTestEhichLevel;
    double hspaFddTestHspdschsLevel;
    double hspaFddTestHsscch1Level;
    /// R99 parameters
    S_RCTLIB_WCDMA_NSFT_PRESETTINGS_T r99Param;
} S_RCTLIB_WCDMA_HSPA_NSFT_PRESETTINGS_T;

typedef void (__stdcall* DutWaitingCallback)(void);
/**
 * Descriptions: WCDMA HSPA NSFT test case configuration
 */
typedef struct
{
    /// uplink test channel
    unsigned int uplinkUarfcn;
    /// uplink test channel
    unsigned int downlinkUarfcn;
    /// input(DUT uplink) cable loss
    double inputCableLoss;
    /// output(DUT downlink) cable loss;
    double outputCableLoss;
    /// HSPA sub test number: (1 ~ 4)
    unsigned int subTest;
    /// betaC
    unsigned int betaC;
    /// betaD
    unsigned int betaD;
    /// closed-loop target power for TPC (dBm)
    int closedLoopTargetPower;
    /// expected power for RF analyzer (dBm)
    int expectedPower;
    /// callback function for DUT control loop (for adding delay)
    DutWaitingCallback delayCallback;
} S_RCTLIB_WCDMA_HSPA_NSFT_CONFIG_T;
/**
 * Descriptions: WCDMA HSPA NSFT Test result
 */
typedef struct
{
    /// max power
    double maxPower;
    /// SEM
    S_RCTLIB_WCDMA_NSFT_SEM_RESULT_T semResult;
    /// ACLR
    S_RCTLIB_WCDMA_NSFT_SPECTRUM_RESULT_T aclrResult;
} S_RCTLIB_WCDMA_HSPA_NSFT_RESULT_T;
/**
 * Descriptions: WCDMA AFC presetting
 */
typedef struct
{
    /// UARFCN for AFC calibration
    unsigned int uarfcn_dl;
    /// cell power for AFC calibration
    double d_cell_power;
} S_RCTLIB_WCDMA_AFC_PRESETTINGS_T;
/**
 * Descriptions: WCDMA List mode specific setting
 */
typedef struct
{
    unsigned char  dpcch_pwr;///<default 8, depends on testing requirement
    unsigned char  dpdch_pwr;///<default 15, depends on testing requirement
    unsigned short full_test_time;///<the total time of one freq.
    unsigned char  ready_time; ///< for first sync after TX transmit
    unsigned char  sync_time; ///< from cs_start to LBK is 26 frame
    unsigned char  retrial; ///<just for first sync
    unsigned short test_time; ///<the time of test for max&min TX power tests
    unsigned short rx_rssi_start_time[3]; ///<RSSI start time for 3 LNA mode
    unsigned char  rx_rssi_duration[3];
    unsigned short rx_ber_start_time; ///<BER start time, no used now.
    unsigned char  rx_ber_duration;
    unsigned short ILPC_ABC_time; ///<the time of ILPC ABC
    unsigned short ILPC_EF_time; ///<the time of ILPC EF
    unsigned short ILPC_GH_time; ///<the time of ILPC GH
    unsigned short transition_time; ///<the limitation of UE state machine is 4 frame at least
    double         expected_power[2];
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_SPECIFIC_SETTING_T;
/**
 * Description: WCDMA intrument's spcial settings
 */
typedef struct
{
    /// Tranditional calibration support
    bool bTCSupport;
    /// Tranditional calibration support
    bool bFHCSupport;
    /// WCDMA NSFT CTFC
    unsigned char ucNSFT_ctfc[4];
    /// WCDMA NSFT TFCI
    unsigned short usNSFT_tfci;
    /// WCDMA NSFT TX and BER test reverse
    bool usNSFT_TxBer_Reverse;
    /// WCDMA Selected port for two port Rxd
    E_RCTLIB_PORT_TYPE eRxdPathLossPort;
    /// WCDMA list mode setting
    S_RCTLIB_WCDMA_LIST_MODE_NSFT_SPECIFIC_SETTING_T sListModeSetting;
} S_RCTLIB_WCDMA_SPECIFIC_SETTINGS_T;

/** list mode*/
typedef struct
{
    /// R99 parameters
    S_RCTLIB_WCDMA_NSFT_PRESETTINGS_T r99Param;
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_PRESETTING_T;

typedef struct
{
#define WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM   50
    /// uplink UARFCN
    unsigned int uarfcn_ul[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    /// downlink UARFCN
    unsigned int uarfcn_dl[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    /// uplink cable loss
    double cableloss_ul[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    /// downlink cable loss
    double cableloss_dl[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    /// init cell power(unit: dBm)
    double cell_power;
    ///peak power (unit: dBm) , [0]: max peak power, [1]: min peak power
    //double dPeakpower[2];
    ///Expected power (unit: dBm) , [0]: Expected max power, [1]: Expected min power
    double dExpectedpower[2];
    ///Downlink power for Lna mode; 0: high mode, 1: middle mode, 2: low mode(unit: dBm)
    double   dWcdma_Lna_P_DL[3];
    ///BER power level(unit: dBm)
    double   dWcdma_BER_power[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    /// ILPC Test segment
    //unsigned char testSegment;

    unsigned char    ucBand[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    unsigned char valid_freq; //valid count of dl/ul freq.
    unsigned short test_item[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM]; //bit0:reserved. bit1:single end BER. bit2:RSSI measure. bit3:ILPC_ABC. bit4:ILPC_EF. bit5:ILPC_GH
    /* the time settings, unit = frame */
    unsigned short full_test_time;//the total time of one freq.
    unsigned char ready_time; // for first sync after TX transmit(the time of power up to max and ready to start test (10frames=100ms))
    unsigned char sync_time; //the time of sync, the limitation of UE state machine is 42 frame at least for 5 retrial
    unsigned char retrial; //retry times
    unsigned short test_time; //the time of test for max&min TX power tests
    unsigned short rx_rssi_start_time[3];  //RSSI start time for 3 LNA mode
    unsigned char rx_rssi_duration[3]; //the time of RSSI measurement
    unsigned short rx_ber_start_time;  //RSSI start time for 3 LNA mode
    unsigned char rx_ber_duration; //the time of BER measurement
    unsigned short ILPC_ABC_time; //the time of ILPC ABC
    unsigned short ILPC_EF_time; //the time of ILPC EF
    unsigned short ILPC_GH_time; //the time of ILPC GH
    unsigned short transition_time; //the limitation of UE state machine is 4 frame at least
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_INIT_SETTING_T;

/**
 * The structure for storing NSFT SEM result of list mode
 */
typedef struct
{
    /// pass flag (overall), pass(0)/fail(1)/not tested(-1)
    char cPass;
    /// Total power Ref.
    double dTotalPowerRef;
    /// Peak Ref Freq.
    double dPeakRefFreq;
    /// peak freq of lowers
    double dPeakFreqLower[6];
    /// peak freq of uppers
    double dPeakFreqUpper[6];
    /// Rel Int Power of lowers
    double dRelIntPowerLower[6];
    /// Rel Int Power of uppers
    double dRelIntPowerUpper[6];
    /// Abs Int Power of lowers
    double dAbsIntPowerLower[6];
    /// Abs Int Power of uppers
    double dAbsIntPowerUpper[6];
    /// Rel Peak Power of lowers
    double dRelPeakPowerLower[6];
    /// Rel Peak Power of uppers
    double dRelPeakPowerUpper[6];
    /// Abs Peak Power of lowers
    double dAbsPeakPowerLower[6];
    /// Abs Peak Power of uppers
    double dAbsPeakPowerUpper[6];
    /// Lower delta Limit
    double dDeltaLimitLower[6];
    /// Upper delta Limit
    double dDeltaLimitUpper[6];
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_SEM_RESULT_T;
/**
 * The structure for storing NSFT EVM result of list moe
 */
typedef struct
{
    /// EVM (%rms)
    double dRMS_EVM;
    /// EVM Pk (%)
    double dPeak_EVM;
    /// Frequency Error
    double dFreq_Error;
    /// IQ Offset (dB)
    double dIq_Offset_dB;
    /// PCDE (max, dB)
    double dpcde;
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_EVM_RESULT_T;

/**
 * the structure for storing ACP(ACLR) result of list mode
 */
typedef struct
{
    /// Total Carrier Power(unit: dBm)
    double dCarrierPower;
    /// ACLR at negative 10 MHz (dB)  10MHz Offs Rel Pwr
    double m_dOffsetn10;
    /// ACLR at negative 5 MHz (dB) -5MHz Offs Rel Pwr
    double m_dOffsetn5;
    /// ACLR at positive 5 MHz (dB) 5MHz Offs Rel Pwr
    double m_dOffsetp5;
    /// ACLR at positive 10 MHz (dB) -10MHz Offs Rel Pwr
    double m_dOffsetp10;
    /// Occupied bandwidth (MHz)
    double m_dOBW;
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_ACP_RESULT_T;
/**
 * The structure for storing WCDMA list mode NSFT ILPC config
 */
typedef struct
{
    char seg;
    double start_power;
    double stop_power;
    /// single step error
    double single_step_error_algo1_1dB_upper[2];// TPC cmd: +1, -1
    double single_step_error_algo1_1dB_lower[2];// TPC cmd: +1, -1
    double single_step_error_algo1_2dB_upper[2];// TPC cmd: +1, -1
    double single_step_error_algo1_2dB_lower[2];// TPC cmd: +1, -1
    double single_step_error_algo2_upper[3];// +1, 0, -1
    double single_step_error_algo2_lower[3];// +1, 0, -1
    /// aggregate step error (10 steps)
    double aggregate_step_error_algo1_1dB_upper[2];// +1, -1
    double aggregate_step_error_algo1_1dB_lower[2];// +1, -1
    double aggregate_step_error_algo1_2dB_upper[2];// +1, -1
    double aggregate_step_error_algo1_2dB_lower[2];// +1, -1
    double aggregate_step_error_algo2_upper[3];// +1, 0, -1
    double aggregate_step_error_algo2_lower[3];// +1, 0, -1
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_ILPC_CONFIG_T;
/**
 * The structure for storing WCDMA list mode NSFT ILPC result
 */
typedef struct
{
    /// integrity
    int     i_Integrity;
    /// pass flag (overall)
    bool    bPass;
    /// number of slots
    int     i_NumSlots;
    /// power (ABS)
    double  d_Absolute[100];
    /// delta value between each step
    double  d_Delta[100];
    bool    bCal_fail;
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_ILPC_RESULT_PER_SEGMENT_T;
typedef struct
{
    S_RCTLIB_WCDMA_LIST_MODE_NSFT_ILPC_RESULT_PER_SEGMENT_T sIlpc_Segment_result[8];
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_ILPC_RESULT_T;
/**
 * the structure for storing TX list mode step result
 */
typedef struct
{
#define WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM   50
    double  dMaxPower[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    double  dMinPower[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_WCDMA_LIST_MODE_NSFT_SEM_RESULT_T  sSEMResult[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_WCDMA_LIST_MODE_NSFT_ACP_RESULT_T  sACPResult[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_WCDMA_LIST_MODE_NSFT_EVM_RESULT_T  sEVMResult[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_WCDMA_LIST_MODE_NSFT_ILPC_RESULT_T sILPCResult[WCDMA_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_WCDMA_LIST_MODE_NSFT_ILPC_CONFIG_T sILPCConfig;
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_TEST_TX_STEP_RESULT_T;

typedef struct
{
    //int nValid_Freq;
    S_RCTLIB_WCDMA_LIST_MODE_NSFT_TEST_TX_STEP_RESULT_T txListModeResult;
} S_RCTLIB_WCDMA_LIST_MODE_NSFT_RESULT_T;

/**********************************************
 * WCDMA structure (shared library defined END)
 **********************************************/
/**********************************************
 * WCDMA function (shared library defined START)
 **********************************************/
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_ConfigCellPower(double power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_ConfigDefaultSettings(void);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_AFC_PreSetting(const S_RCTLIB_WCDMA_AFC_PRESETTINGS_T* pSettings, unsigned int size);
// Main path AGC calibration RCT controls
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_AGC_PreSetting(const S_RCTLIB_WCDMA_AGC_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_AGC_ChangeCellBand(unsigned int band);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_AGC_ChangeChannel(unsigned int uarfcn);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_AGC_ChangeCellPower(double cellPower);
// Diversity path AGC calibration RCT controls
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_AGC_RXD_PreSetting(const S_RCTLIB_WCDMA_AGC_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_AGC_RXD_ChangeCellBand(unsigned int band);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_AGC_RXD_ChangeChannel(unsigned int uarfcn);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_AGC_RXD_ChangeCellPower(double cellPower);

NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_APC_PreSetting(const S_RCTLIB_WCDMA_APC_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_APC_PreSetting_Ex(const S_RCTLIB_WCDMA_APC_PRESETTINGS_EX_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_APC_ChangeCellBand(unsigned int band);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_APC_ChangeChannel(unsigned int uarfcn);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_APC_ChangeExpectedPower(int expectedPower);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_APC_Initiate(void);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_APC_FetchResult(double* outputPower);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_FHC_PreSetting(const S_RCTLIB_WCDMA_FHC_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_FHC_StartIteration(const S_RCTLIB_WCDMA_FHC_MEASUREMENT_PARAM_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_FHC_FetchResult(const S_RCTLIB_WCDMA_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_WCDMA_FHC_MEASUREMENT_RESULT_T* pResult);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_PreSetting(const S_RCTLIB_WCDMA_NSFT_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_InitiateTestCase(const S_RCTLIB_WCDMA_NSFT_CONFIG_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_TPC(const S_RCTLIB_WCDMA_NSFT_TPC_REQUEST_T* tpc_request);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_FetchTXPerformanceMaxPower(S_RCTLIB_WCDMA_NSFT_TX_PERF_MAX_POWER_RESULT_T* tx_perf_result);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_FetchTXPerformanceMinPower(S_RCTLIB_WCDMA_NSFT_TX_PERF_MIN_POWER_RESULT_T* tx_perf_result);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_InitiateILPCTestCase(unsigned char testSegment);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_FetchILPCResult(S_RCTLIB_WCDMA_NSFT_ILPC_CONFIG_T* ilpcConfig, S_RCTLIB_WCDMA_NSFT_ILPC_RESULT_T* result);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_ChangeCellPower(double d_cell_power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_InitiateBER();
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_ReadBER(S_RCTLIB_WCDMA_NSFT_BER_RESULT_T* result);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_PRACH_PreSetting(const S_RCTLIB_WCDMA_NSFT_PRACH_PRESETTING_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_PRACH_CasePreSetting();
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_PRACH_InitiateTestCase(const S_RCTLIB_WCDMA_NSFT_PRACH_CONFIG_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_PRACH_FetchTestCase(S_RCTLIB_WCDMA_NSFT_PRACH_RESULT_T* result);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_NSFT_PRACH_ChangeCellPower(double d_cell_power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_HSDPA_NSFT_PreSetting(const S_RCTLIB_WCDMA_HSPA_NSFT_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_HSDPA_NSFT_InitiateTestCase(const S_RCTLIB_WCDMA_HSPA_NSFT_CONFIG_T* pConfig);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_HSDPA_NSFT_FetchResult(S_RCTLIB_WCDMA_HSPA_NSFT_RESULT_T* pResult);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_HSUPA_NSFT_PreSetting(const S_RCTLIB_WCDMA_HSPA_NSFT_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_HSUPA_NSFT_InitiateTestCase(const S_RCTLIB_WCDMA_HSPA_NSFT_CONFIG_T* pConfig);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_HSUPA_NSFT_FetchResult(S_RCTLIB_WCDMA_HSPA_NSFT_RESULT_T* pResult);
NON_REENTRANT_FUNC int __stdcall RCTLIB_WCDMA_GET_SpecificSettings(S_RCTLIB_WCDMA_SPECIFIC_SETTINGS_T* pSettings);

// reentrant funtions
int __stdcall RCTLIB_WCDMA_ConfigCellPower_r(const int meta_handle, double power);
int __stdcall RCTLIB_WCDMA_ConfigDefaultSettings_r(const int meta_handle);
int __stdcall RCTLIB_WCDMA_AFC_PreSetting_r(const int meta_handle, const S_RCTLIB_WCDMA_AFC_PRESETTINGS_T* pSettings, unsigned int size);
// Main path AGC calibration RCT controls
int __stdcall RCTLIB_WCDMA_AGC_PreSetting_r(const int meta_handle, const S_RCTLIB_WCDMA_AGC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_WCDMA_AGC_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_WCDMA_AGC_ChangeChannel_r(const int meta_handle, unsigned int uarfcn);
int __stdcall RCTLIB_WCDMA_AGC_ChangeCellPower_r(const int meta_handle, double cellPower);
// Diversity path AGC calibration RCT controls
int __stdcall RCTLIB_WCDMA_AGC_RXD_PreSetting_r(const int meta_handle, const S_RCTLIB_WCDMA_AGC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_WCDMA_AGC_RXD_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_WCDMA_AGC_RXD_ChangeChannel_r(const int meta_handle, unsigned int uarfcn);
int __stdcall RCTLIB_WCDMA_AGC_RXD_ChangeCellPower_r(const int meta_handle, double cellPower);

int __stdcall RCTLIB_WCDMA_APC_PreSetting_r(const int meta_handle, const S_RCTLIB_WCDMA_APC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_WCDMA_APC_PreSetting_Ex_r(const int meta_handle, const S_RCTLIB_WCDMA_APC_PRESETTINGS_EX_T* pSettings);
int __stdcall RCTLIB_WCDMA_APC_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_WCDMA_APC_ChangeChannel_r(const int meta_handle, unsigned int uarfcn);
int __stdcall RCTLIB_WCDMA_APC_ChangeExpectedPower_r(const int meta_handle, int expectedPower);
int __stdcall RCTLIB_WCDMA_APC_Initiate_r(const int meta_handle);
int __stdcall RCTLIB_WCDMA_APC_FetchResult_r(const int meta_handle, double* outputPower);
int __stdcall RCTLIB_WCDMA_FHC_PreSetting_r(const int meta_handle, const S_RCTLIB_WCDMA_FHC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_WCDMA_FHC_StartIteration_r(const int meta_handle, const S_RCTLIB_WCDMA_FHC_MEASUREMENT_PARAM_T* pSettings);
int __stdcall RCTLIB_WCDMA_FHC_FetchResult_r(const int meta_handle, const S_RCTLIB_WCDMA_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_WCDMA_FHC_MEASUREMENT_RESULT_T* pResult);
int __stdcall RCTLIB_WCDMA_NSFT_PreSetting_r(const int meta_handle, const S_RCTLIB_WCDMA_NSFT_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_WCDMA_NSFT_InitiateTestCase_r(const int meta_handle, const S_RCTLIB_WCDMA_NSFT_CONFIG_T* pSettings);
int __stdcall RCTLIB_WCDMA_NSFT_TPC_r(const int meta_handle, const S_RCTLIB_WCDMA_NSFT_TPC_REQUEST_T* tpc_request);
int __stdcall RCTLIB_WCDMA_NSFT_FetchTXPerformanceMaxPower_r(const int meta_handle, S_RCTLIB_WCDMA_NSFT_TX_PERF_MAX_POWER_RESULT_T* tx_perf_result);
int __stdcall RCTLIB_WCDMA_NSFT_FetchTXPerformanceMinPower_r(const int meta_handle, S_RCTLIB_WCDMA_NSFT_TX_PERF_MIN_POWER_RESULT_T* tx_perf_result);
int __stdcall RCTLIB_WCDMA_NSFT_InitiateILPCTestCase_r(const int meta_handle, unsigned char testSegment);
int __stdcall RCTLIB_WCDMA_NSFT_FetchILPCResult_r(const int meta_handle, S_RCTLIB_WCDMA_NSFT_ILPC_CONFIG_T* ilpcConfig, S_RCTLIB_WCDMA_NSFT_ILPC_RESULT_T* result);
int __stdcall RCTLIB_WCDMA_NSFT_ChangeCellPower_r(const int meta_handle, double d_cell_power);
int __stdcall RCTLIB_WCDMA_NSFT_InitiateBER_r(const int meta_handle);
int __stdcall RCTLIB_WCDMA_NSFT_ReadBER_r(const int meta_handle, S_RCTLIB_WCDMA_NSFT_BER_RESULT_T* result);
int __stdcall RCTLIB_WCDMA_NSFT_PRACH_PreSetting_r(const int meta_handle, const S_RCTLIB_WCDMA_NSFT_PRACH_PRESETTING_T* pSettings);
int __stdcall RCTLIB_WCDMA_NSFT_PRACH_CasePreSetting_r(const int meta_handle);
int __stdcall RCTLIB_WCDMA_NSFT_PRACH_InitiateTestCase_r(const int meta_handle, const S_RCTLIB_WCDMA_NSFT_PRACH_CONFIG_T* pSettings);
int __stdcall RCTLIB_WCDMA_NSFT_PRACH_FetchTestCase_r(const int meta_handle, S_RCTLIB_WCDMA_NSFT_PRACH_RESULT_T* result);
int __stdcall RCTLIB_WCDMA_NSFT_PRACH_ChangeCellPower_r(const int meta_handle, double d_cell_power);
int __stdcall RCTLIB_WCDMA_HSDPA_NSFT_PreSetting_r(const int meta_handle, const S_RCTLIB_WCDMA_HSPA_NSFT_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_WCDMA_HSDPA_NSFT_InitiateTestCase_r(const int meta_handle, const S_RCTLIB_WCDMA_HSPA_NSFT_CONFIG_T* pConfig);
int __stdcall RCTLIB_WCDMA_HSDPA_NSFT_FetchResult_r(const int meta_handle, S_RCTLIB_WCDMA_HSPA_NSFT_RESULT_T* pResult);
int __stdcall RCTLIB_WCDMA_HSUPA_NSFT_PreSetting_r(const int meta_handle, const S_RCTLIB_WCDMA_HSPA_NSFT_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_WCDMA_HSUPA_NSFT_InitiateTestCase_r(const int meta_handle, const S_RCTLIB_WCDMA_HSPA_NSFT_CONFIG_T* pConfig);
int __stdcall RCTLIB_WCDMA_HSUPA_NSFT_FetchResult_r(const int meta_handle, S_RCTLIB_WCDMA_HSPA_NSFT_RESULT_T* pResult);
int __stdcall RCTLIB_WCDMA_GET_SpecificSettings_r(const int meta_handle, S_RCTLIB_WCDMA_SPECIFIC_SETTINGS_T* pSettings);
int __stdcall RCTLIB_WCDMA_LIST_MODE_NSFT_PreSetting_r(const int meta_handle, const S_RCTLIB_WCDMA_LIST_MODE_NSFT_PRESETTING_T* pSetting, const unsigned int length);
int __stdcall RCTLIB_WCDMA_LIST_MODE_NSFT_InitiateTestPlan_r(const int meta_handle, const S_RCTLIB_WCDMA_LIST_MODE_NSFT_INIT_SETTING_T* pSetting, const unsigned int length);
int __stdcall RCTLIB_WCDMA_LIST_MODE_NSFT_FetchTestPlanResult_r(const int meta_handle, S_RCTLIB_WCDMA_LIST_MODE_NSFT_RESULT_T* pResult, const unsigned int length);
/**********************************************
 * WCDMA function (shared library defined END)
 **********************************************/
/**********************************************
 * TDSCDMA
 **********************************************/

/*****************************************************
 * AFC structure (START)
 *****************************************************/
typedef struct
{
    /// cell power seetings
    double         d_cell_power;
    /// expected power
    int            expected_power;
    /// Average Count
    unsigned int   ui_average_cnt;
    /// UARFCN
    unsigned short us_uarfcn;
} S_RCTLIB_TDSCDMA_AFC_TESTER_CONFIG_BEFORE_CAL_T;
/*****************************************************
 * AFC structure (END)
 *****************************************************/
/*****************************************************
 * AGC structure (START)
 *****************************************************/
typedef struct
{
    /// cell power for the calibration
    double d_cell_power;
} S_RCTLIB_TDSCDMA_AGC_TESTER_CONFIG_BEFORE_CAL_T;
/*****************************************************
 * AGC structure (END)
 *****************************************************/
/*****************************************************
 * APC structure (START)
 *****************************************************/
typedef struct
{
    /// timeout value (unit: ms)
    double timeout;
    /// meaurement count
    int measurement_count;
} S_RCTLIB_TDSCDMA_APC_TESTER_CONFIG_BEFORE_CAL_T;
typedef struct
{
    /// UARFCN
    unsigned int uarfcn;
    /// expected power (dBm)
    int expected_power;
    /// [IN/OUT] channel power (dBm)
    double output_power;
} S_RCTLIB_TDSCDMA_APC_MEASUREMENT_PARAM_T;
/*****************************************************
 * APC structure (END)
 *****************************************************/
/*****************************************************
 * FHC structure (START)
 *****************************************************/
typedef struct
{
    /// timeout value (unit: ms)
    double timeout;
} S_RCTLIB_TDSCDMA_FHC_TESTER_CONFIG_BEFORE_CAL_T;
typedef struct
{
    /// number of frequency steps (Max 20)
    unsigned int freq_num;
    /// frequnecy steps (used in both TX/RX since it's TDD) (MHz)
    double freq_steps[40];
    /// number of tx power steps
    unsigned int tx_power_steps;
    /// expected power level of tx power step (Max 40)
    double tx_expected_power[40];
    /// unmber of rx power steps
    unsigned int rx_power_steps;
    /// power level of rx power step (Max 40)
    double rx_power_level[40];
    /// RX retune step length (unit sub-frame)
    unsigned int rx_retune_step;
    /// TX retune step length (unit sub-frame)
    unsigned int tx_retune_step;
    /// power step length (sub-frame)
    unsigned int power_step_length;
} S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_PARAM_T;
typedef struct
{
    int integrity;
    /// number of frequencye steps
    int freq_steps;
    /// number of tx power steps
    int tx_power_steps;
    /// number of tx power samples
    int tx_power_samples;
    /// TX power measurement result
    double tx_power[400];
} S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_RESULT_T;
/*****************************************************
 * FHC structure (END)
 *****************************************************/
typedef struct
{
    unsigned char sc_code;
    int           m_iDtchType; // PRBS9 (0) | PRBS15 (1)| INCRement (2) | ZERos (3) | ONEs (4) |ALTernating (5)
} S_RCTLIB_TD_NSFT_TESTER_COMMON_CONFIG_T;

typedef struct
{
    unsigned short  m_usTD_NSFT_UARFCN;
    double          m_dTD_NSFT_CableLoss;
    double          m_dTD_NSFT_Cell_Power;
    //      double          m_dTD_NSFT_BER_LEVEL;
    double          m_dTD_NSFT_MAX_PWR_AVG_HIGH;
} S_RCTLIB_TD_NSFT_TESTER_CONFIG_T;


#define RCTLIB_TD_NSFT_SEM_MARGIN_NUM        3

typedef struct
{
    double m_dMinMsTargetPwr;
    double m_dMaxMsTargetPwr;
} S_RCTLIB_TD_NSFT_TPC_CONFIG_ENTRY_T;


//#define TD_NSFT_SEM_MARGIN_NUM 3

typedef struct
{
    bool   bPass;
    double d_sem_level[RCTLIB_TD_NSFT_SEM_MARGIN_NUM];
    double d_sem_freq_offset[RCTLIB_TD_NSFT_SEM_MARGIN_NUM];
    double d_sem_margin[RCTLIB_TD_NSFT_SEM_MARGIN_NUM];
    bool   b_sem_pass[RCTLIB_TD_NSFT_SEM_MARGIN_NUM];
    double d_in_channel_pwr[RCTLIB_TD_NSFT_SEM_MARGIN_NUM];
} S_RCTLIB_TDSCDMA_NSFT_SEM_RESULT_T;


typedef struct
{
    bool bPass;
    double d_aclr_result[4];  // -1.6/1.6/-3.2/3.2 MHz Offset
    bool   b_aclr_pass[4];    // -1.6/1.6/-3.2/3.2 MHz Offset
} S_TDSCDMA_NSFT_ACLR_RESULT_T;


typedef struct
{
    double d_evm_rms;
    double d_evm_max_freq_error;
    double d_evm_origin_offset;
    double d_max_pcde;
} S_TDSCDMA_NSFT_WQ_RESULT_T;

typedef struct
{
    bool bPass;
    double d_avg_on_pwr;
    bool   b_oop_pass[3];
    double d_avg_pwr[3];
} S_TDSCDMA_NSFT_OOP_RESULT_T;

/*
integrity indicator, overall pass/fail, maximum power, minimum power, worst REL1POW step index, worst REL1POW absolute power, worst REL1POW, worst REL10POW step index, worst REL10POW absolute power and worst REL10POW
*/


typedef struct
{
    bool bPass;
    double d_max_pwr;
    double d_min_pwr;
    int    i_worst_step_index[2];  // [0]: REL1POW, [1]:REL10POW
    double d_worst_abs_pwr[2]; // [0]: REL1POW, [1]:REL10POW
    double d_worst_pwr[2];  // [0]: REL1POW, [1]:REL10POW


} S_TDSCDMA_NSFT_CLP_RESULT_T;




typedef struct
{
    double d_min_avg_pwr;
    double d_max_avg_pwr;
    double d_obw_max;

    S_RCTLIB_TDSCDMA_NSFT_SEM_RESULT_T  r_sem_result;
    S_TDSCDMA_NSFT_ACLR_RESULT_T r_aclr_result;
    S_TDSCDMA_NSFT_WQ_RESULT_T   r_wq_result;
    S_TDSCDMA_NSFT_WQ_RESULT_T   r_wq_result_at_low_power;
    S_TDSCDMA_NSFT_OOP_RESULT_T  r_oop_result;
    S_TDSCDMA_NSFT_CLP_RESULT_T  r_clp_result;

    double d_ACLR_Low5;
    double d_ACLR_Up5;
    double d_ACLR_Low10;
    double d_ACLR_Up10;

    double d_ber_from_target;
    double d_ber_from_tester;   // the ber measured by tester

} S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T;

typedef struct
{
    double d_cell_pwr;
    bool   b_loopback_ber;  // loopback BER
    int    i_bit_cnt;   // valid when b_loopback_ber = true;

} S_RCTLIB_TD_NSFT_BER_CONFIG_ENTRY_T;
/**
 * Description: TDSCDMA intrument's spcial settings
 */
typedef struct
{
    /// Tranditional calibration support
    bool bTCSupport;
    /// Tranditional calibration support
    bool bFHCSupport;
    /// NSFT UL midamble config
    unsigned char  usNSFT_midamble;
    /// NSFT Single-End BER bit pattern, 0: all zero, 1: all one
    unsigned char  usNSFTSingleEndBitPattern;
    int iPCCPCH;
} S_RCTLIB_TDSCDMA_SPECIFIC_SETTINGS_T;

typedef struct
{
    unsigned int dummy;
} S_RCTLIB_TDSCDMA_LIST_MODE_NSFT_PRESETTING_T;

typedef struct
{
    unsigned int dummy;
} S_RCTLIB_TDSCDMA_LIST_MODE_NSFT_INIT_SETTING_T;

typedef struct
{
    unsigned int dummy;
} S_RCTLIB_TDSCDMA_LIST_MODE_NSFT_RESULT_T;
/*****************************************************
 * exported function (START)
 *****************************************************/
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterCommonBeforeCal(void);

NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterBeforeAFC(const S_RCTLIB_TDSCDMA_AFC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_MeasureAFC(double* p_dFreqOffset);

NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterBeforeAGC(const S_RCTLIB_TDSCDMA_AGC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_AGC_ChangeCellPower(double cell_power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_AGC_ChangeCellBand(unsigned int band);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_AGC_ChangeChannel(unsigned int uarfcn);

NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterBeforeAPC(const S_RCTLIB_TDSCDMA_APC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_APC_ChangeCellBand(unsigned int band);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_APC_MeasurePower(S_RCTLIB_TDSCDMA_APC_MEASUREMENT_PARAM_T* param);

NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterBeforeFHC(const S_RCTLIB_TDSCDMA_FHC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_FHC_StartIteration(const S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_PARAM_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_FHC_FetchResult(const S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_RESULT_T* pResult);

NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterCommonBeforeNSFT(S_RCTLIB_TD_NSFT_TESTER_COMMON_CONFIG_T* common_cfg);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterForNSFT(const S_RCTLIB_TD_NSFT_TESTER_CONFIG_T* cfg);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_MeasureTPCForNSFT(const S_RCTLIB_TD_NSFT_TPC_CONFIG_ENTRY_T* req,
        S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);

NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterForNSFTBer(const S_RCTLIB_TD_NSFT_BER_CONFIG_ENTRY_T* cfg);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_MeasureLBerForNSFT(S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);


NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterCommonBeforeFT(S_RCTLIB_TD_NSFT_TESTER_COMMON_CONFIG_T* common_cfg);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterForFT(const S_RCTLIB_TD_NSFT_TESTER_CONFIG_T* cfg);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_MeasureTPCForFT(const S_RCTLIB_TD_NSFT_TPC_CONFIG_ENTRY_T* req,
        S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);

NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_ConfigTesterForFTBer(const S_RCTLIB_TD_NSFT_BER_CONFIG_ENTRY_T* cfg);
NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_MeasureLBerForFT(S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);

NON_REENTRANT_FUNC int __stdcall RCTLIB_TDSCDMA_GET_SpecificSettings(S_RCTLIB_TDSCDMA_SPECIFIC_SETTINGS_T* pSettings);

// reentrant funtions
int __stdcall RCTLIB_TDSCDMA_ConfigTesterCommonBeforeCal_r(const int meta_handle);

int __stdcall RCTLIB_TDSCDMA_ConfigTesterBeforeAFC_r(const int meta_handle, const S_RCTLIB_TDSCDMA_AFC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
int __stdcall RCTLIB_TDSCDMA_MeasureAFC_r(const int meta_handle, double* p_dFreqOffset);

int __stdcall RCTLIB_TDSCDMA_ConfigTesterBeforeAGC_r(const int meta_handle, const S_RCTLIB_TDSCDMA_AGC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
int __stdcall RCTLIB_TDSCDMA_AGC_ChangeCellPower_r(const int meta_handle, double cell_power);
int __stdcall RCTLIB_TDSCDMA_AGC_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_TDSCDMA_AGC_ChangeChannel_r(const int meta_handle, unsigned int uarfcn);

int __stdcall RCTLIB_TDSCDMA_ConfigTesterBeforeAPC_r(const int meta_handle, const S_RCTLIB_TDSCDMA_APC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
int __stdcall RCTLIB_TDSCDMA_APC_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_TDSCDMA_APC_MeasurePower_r(const int meta_handle, S_RCTLIB_TDSCDMA_APC_MEASUREMENT_PARAM_T* param);

int __stdcall RCTLIB_TDSCDMA_ConfigTesterBeforeFHC_r(const int meta_handle, const S_RCTLIB_TDSCDMA_FHC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
int __stdcall RCTLIB_TDSCDMA_FHC_StartIteration_r(const int meta_handle, const S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_PARAM_T* pSettings);
int __stdcall RCTLIB_TDSCDMA_FHC_FetchResult_r(const int meta_handle, const S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_RESULT_T* pResult);

int __stdcall RCTLIB_TDSCDMA_ConfigTesterCommonBeforeNSFT_r(const int meta_handle, S_RCTLIB_TD_NSFT_TESTER_COMMON_CONFIG_T* common_cfg);
int __stdcall RCTLIB_TDSCDMA_ConfigTesterForNSFT_r(const int meta_handle, const S_RCTLIB_TD_NSFT_TESTER_CONFIG_T* cfg);
int __stdcall RCTLIB_TDSCDMA_MeasureTPCForNSFT_r(const int meta_handle, const S_RCTLIB_TD_NSFT_TPC_CONFIG_ENTRY_T* req,
        S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);

int __stdcall RCTLIB_TDSCDMA_ConfigTesterForNSFTBer_r(const int meta_handle, const S_RCTLIB_TD_NSFT_BER_CONFIG_ENTRY_T* cfg);
int __stdcall RCTLIB_TDSCDMA_MeasureLBerForNSFT_r(const int meta_handle, S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);


int __stdcall RCTLIB_TDSCDMA_ConfigTesterCommonBeforeFT_r(const int meta_handle, S_RCTLIB_TD_NSFT_TESTER_COMMON_CONFIG_T* common_cfg);
int __stdcall RCTLIB_TDSCDMA_ConfigTesterForFT_r(const int meta_handle, const S_RCTLIB_TD_NSFT_TESTER_CONFIG_T* cfg);
int __stdcall RCTLIB_TDSCDMA_MeasureTPCForFT_r(const int meta_handle, const S_RCTLIB_TD_NSFT_TPC_CONFIG_ENTRY_T* req,
        S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);

int __stdcall RCTLIB_TDSCDMA_ConfigTesterForFTBer_r(const int meta_handle, const S_RCTLIB_TD_NSFT_BER_CONFIG_ENTRY_T* cfg);
int __stdcall RCTLIB_TDSCDMA_MeasureLBerForFT_r(const int meta_handle, S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);

int __stdcall RCTLIB_TDSCDMA_GET_SpecificSettings_r(const int meta_handle, S_RCTLIB_TDSCDMA_SPECIFIC_SETTINGS_T* pSettings);
int __stdcall RCTLIB_TDSCDMA_LIST_MODE_NSFT_PreSetting_r(const int meta_handle, const S_RCTLIB_TDSCDMA_LIST_MODE_NSFT_PRESETTING_T* pSetting, const unsigned int length);
int __stdcall RCTLIB_TDSCDMA_LIST_MODE_NSFT_InitiateTestPlan_r(const int meta_handle, const S_RCTLIB_TDSCDMA_LIST_MODE_NSFT_INIT_SETTING_T* pSetting, const unsigned int length);
int __stdcall RCTLIB_TDSCDMA_LIST_MODE_NSFT_FetchTestPlanResult_r(const int meta_handle, S_RCTLIB_TDSCDMA_LIST_MODE_NSFT_RESULT_T* pResult, const unsigned int length);

#ifdef __META_LTE__
/*****************************
 * LTE
 *****************************/

/**********************************************
 * LTE structure (shared library defined START)
 **********************************************/
/**
 * Descriptions: LTE AGC Change Frequency
 */
typedef struct
{
    unsigned short usFrequency;  /* the frequency to siwtch. Unit: 100KHz */
    short sFreqOffset; /* the frequency to offset. Unit: KHz */
} S_RCTLIB_LTE_FREQUENCY_T;
/**
 * Descriptions: LTE APC PreSetting
 */
typedef struct
{
    char cMeasurementCount;  /* measurement count */
    char cTriggerMode;      /*0: rising trigger 1: free run */
    unsigned int uiTriggerDelay;      /* trigger delay (Unit: ms) */
} S_RCTLIB_LTE_APC_PRESETTINGS_T;

typedef struct
{
    char dummy;
} S_RCTLIB_LTE_FHC_PRESETTINGS_T;

typedef struct
{
    unsigned short   usFrequency; /* the frequency to siwtch. Unit: 100KHz */
    short            sFreqOffset; /* the frequency to offset. Unit: KHz */
    double           dPowerSteps[27];  /// TX expected power level (dBm) or RX downlink power (dBm)
    unsigned char    ucPwrStepNum;
} S_RCTLIB_LTE_FHC_FREQ_STEP_U;
/**
 * The structure for storing LTE FHC request by band
 */
typedef struct
{
    /// band
    unsigned int  uiBand; // index start from 0 ==> band1
    /// 0:TDD, 1:FDD
    unsigned char duplex_mode;
    /// number of frequency step
    int           iNumberOfFrequencySteps;
    /// UE TX frequency setting in each frequency step (KHz + offset)
    S_RCTLIB_LTE_FHC_FREQ_STEP_U sTxFreqSteps[22];
    /// UE RX frequency setting in each frequency step (KHz + offset)
    S_RCTLIB_LTE_FHC_FREQ_STEP_U sRxFreqSteps[22];
} S_RCTLIB_LTE_FHC_BAND_PARAM_T;

/**
 * The structure for storing LTE FHC request
 */
typedef struct
{
    unsigned char  fdd_tx_to_rx_time;//ms unit
    unsigned char  tdd_tx_to_rx_time;//ms unit
    unsigned char  freq_switch_time;//ms unit
    unsigned char  band_switch_time;//ms unit
    unsigned char  tx_step_width;//ms unit
    unsigned char  tdd_to_fdd_switch_time;//ms unit
    unsigned char  fdd_to_tdd_switch_time;//ms unit
    unsigned char  band_num;
    /// TX + RX Band parameter
    S_RCTLIB_LTE_FHC_BAND_PARAM_T sTRxBandParam[10];
} S_RCTLIB_LTE_FHC_MEASUREMENT_PARAM_T;

typedef struct
{
    double           dMeasuredPower[27];  /// TX measured power level (dBm)
    unsigned char    ucPwrStepNum;
} S_RCTLIB_LTE_FHC_FREQ_RESULT_U;

typedef struct
{
    /// integrity of the measurement result
    int              integrity;
    /// band
    unsigned int     uiBand; // index start from 0 ==> band1
    /// frequency step
    int              iNumberOfFrequencySteps;
    S_RCTLIB_LTE_FHC_FREQ_RESULT_U  sTxFreqResult[22];
} S_RCTLIB_LTE_FHC_BAND_RESULT_U;

/**
 * The structure for storing LTE FHC TX power result
 */
typedef struct
{
    /// TX Band Result
    S_RCTLIB_LTE_FHC_BAND_RESULT_U sTxBandResult[10];
} S_RCTLIB_LTE_FHC_MEASUREMENT_RESULT_T;
/**
 * The structure for storing LTE NSFT SEM result
 * Description: the sections are defined in 3GPP spec Table 6.6.2.1.5-1
 *              General E-UTRA spectrum emission mask
 */
typedef struct
{
    /// pass flag (overall), pass(0)/fail(1)/not tested(-1)
    char cPass;
    /// Abs Peak Power of lowers
    double dAbsPeakPowerLower[4];
    /// Abs Peak Power of uppers
    double dAbsPeakPowerUpper[4];
    /// Lower delta Limit
    double dDeltaLimitLower[4];
    /// Upper delta Limit
    double dDeltaLimitUpper[4];
} S_RCTLIB_LTE_NSFT_SEM_RESULT_T;

typedef struct
{
    unsigned short    usFrequency; /* the frequency to siwtch. Unit: 100KHz */
    short            sFreqOffset; /* the frequency to offset. Unit: KHz */
    unsigned char     ucPwrStepNum;
    double           dPowerSteps[7 * 3 + 72];  /// RX downlink power (dBm)
} S_RCTLIB_LTE_FHC_CA_FREQ_STEP_U;
/**
 * The structure for storing LTE FHC CA request by band
 */
typedef struct
{
    /// band
    unsigned int  uiBand; // index start from 0 ==> band1
    /// 0:TDD, 1:FDD
    unsigned char duplex_mode;
    /// number of frequency step
    int           iNumberOfFrequencySteps;
    /// UE TX frequency setting in each frequency step (KHz + offset)
    S_RCTLIB_LTE_FHC_FREQ_STEP_U    sTxFreqSteps[15];
    /// UE RX CA frequency setting in each frequency step (KHz + offset)
    S_RCTLIB_LTE_FHC_CA_FREQ_STEP_U sRxFreqSteps[15];
} S_RCTLIB_LTE_FHC_CA_BAND_PARAM_T;

/**
 * The structure for storing LTE FHC request
 */
typedef struct
{
    unsigned char  fdd_tx_to_rx_time;//ms unit
    unsigned char  tdd_tx_to_rx_time;//ms unit
    unsigned char  freq_switch_time;//ms unit
    unsigned char  band_switch_time;//ms unit
    unsigned char  tx_step_width;//ms unit
    unsigned char  fdd_to_tdd_switch_time;//ms unit
    unsigned char  band_num;
    unsigned char  tx_cal_enable;
    unsigned char  rx_cal_enable;
    /// TX + RX Band parameter
    S_RCTLIB_LTE_FHC_CA_BAND_PARAM_T sTRxBandParam[10];
} S_RCTLIB_LTE_FHC_CA_MEASUREMENT_PARAM_T;

typedef struct
{
    double           dMeasuredPower[11];  /// TX measured power level (dBm)
    unsigned char    ucPwrStepNum;
} S_RCTLIB_LTE_FHC_CA_FREQ_RESULT_U;

typedef struct
{
    /// integrity of the measurement result
    int              integrity;
    /// band
    unsigned int     uiBand; // index start from 0 ==> band1
    /// frequency step
    int              iNumberOfFrequencySteps;
    S_RCTLIB_LTE_FHC_FREQ_RESULT_U  sTxFreqResult[15];
} S_RCTLIB_LTE_FHC_CA_BAND_RESULT_U;
/**
 * The structure for storing LTE FHC TX power result
 */
typedef struct
{
    /// TX Band Result
    S_RCTLIB_LTE_FHC_CA_BAND_RESULT_U sTxBandResult[10];
} S_RCTLIB_LTE_FHC_CA_MEASUREMENT_RESULT_T;
/**
 * The enum for LTE CA categroy definition
 */
typedef enum
{
    RCTLIB_LTE_CA_BAND_USAGE_SINGLE_BAND = 0,
    RCTLIB_LTE_CA_BAND_USAGE_INTER_BAND_CA,
    RCTLIB_LTE_CA_BAND_USAGE_INTER_BAND_CA_ALT,
    RCTLIB_LTE_CA_BAND_USAGE_INTER_BAND_NCCA,
    RCTLIB_LTE_CA_BAND_USAGE_COUNT
} LteCaBandUsage;
/**
 * The structure for storing LTE NSFT EVM result
 */
typedef struct
{
    /// EVM (%rms)
    double dRMS_EVM;
    /// Frequency Error(ppm)
    double dFreq_Error_Ppm;
    /// Magnitude Error (%)
    double dMagnitude_Error;
    /// Phase Error (Degree)
    double dPhase_Error_Deg;
    /// IQ Offset (dB)
    double dIq_Offset_dB;
} S_RCTLIB_LTE_NSFT_EVM_RESULT_T;
/**
 * The structure for storing LTE NSFT Ripple flatnes result
 */
typedef struct
{
    /// RP 1 pass(0)/fail(1)/not tested(-1)
    char cRP1Pass;
    /// RP 2 pass/fail
    char cRP2Pass;
    /// RP 12 pass/fail
    char cRP12Pass;
    /// RP 21 pass/fail
    char cRP21Pass;
    /// maximum Ripple in Range 1
    double dRipple1;
    /// maximum Ripple in Range 2
    double dRipple2;
    /// RP 12 Value - the maximum ripple between the upper side of Range 1 and lower side of Range 2
    double dRipple12;
    /// RP 21 Value - the maximum ripple between the upper side of Range 2 and lower side of Range 1
    double dRipple21;
} S_RCTLIB_LTE_NSFT_RIPPLE_RESULT_T;

/**
 * the structure for storing ACP(ACLR) result
 */
typedef struct
{
    /// Total Carrier Power
    double dCarrierPower;
    /// Lower Offset EUTRA - relative power
    double dRel_Low_Power_Eutra;
    /// Upper Offset EUTRA - relative power
    double dRel_Upper_Power_Eutra;
    /// Lower Offset UTRA1 - relative power
    double dRel_Low_Power_Utra1;
    /// Upper Offset UTRA1 - relative power
    double dRel_Upper_Power_Utra1;
    /// Lower Offset UTRA2 - relative power
    double dRel_Low_Power_Utra2;
    /// Upper Offset UTRA2 - relative power
    double dRel_Upper_Power_Utra2;
} S_RCTLIB_LTE_NSFT_ACP_RESULT_T;
/**
 * the structure for storing TX list mode step result
 */
typedef struct
{
#define LTE_NSFT_MAX_TX_STEP_TEST_NUM               8
    double                            dPoutPower[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_LTE_NSFT_EVM_RESULT_T    sEVMResult[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_LTE_NSFT_RIPPLE_RESULT_T sRpResult[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_LTE_NSFT_ACP_RESULT_T    sACPResult[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_LTE_NSFT_SEM_RESULT_T    sSEMResult[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
} S_RCTLIB_LTE_NSFT_TEST_TX_STEP_RESULT_T;
/**
 * the structure for storing TX list mode sweep result
 */
typedef struct
{
#define LTE_NSFT_MAX_TX_SWEEP_TEST_NUM              63
    double                            dPoutPower[LTE_NSFT_MAX_TX_SWEEP_TEST_NUM];
} S_RCTLIB_LTE_NSFT_TEST_TX_SWEEP_RESULT_T;
/* TX NSFT test results */
typedef struct
{
    unsigned char                     ucMeasureStep;
    char                              cRequestOpetions;
    /* Inst. setting and RX test check items */
    union
    {
        S_RCTLIB_LTE_NSFT_TEST_TX_STEP_RESULT_T      txStepResult;
        S_RCTLIB_LTE_NSFT_TEST_TX_SWEEP_RESULT_T     txSweepResult;
    };
} S_RCTLIB_LTE_NSFT_TX_TEST_FREQ_RESULT_T;

typedef struct
{
    S_RCTLIB_LTE_NSFT_TX_TEST_FREQ_RESULT_T      txFreqResults[13];
} S_RCTLIB_LTE_NSFT_TX_TEST_BAND_RESULT_T;

typedef struct
{
    S_RCTLIB_LTE_NSFT_TX_TEST_BAND_RESULT_T      txBandResults[10];
} S_RCTLIB_LTE_NSFT_TX_RESULT_T;
/**
 * Descriptions: LTE NSFT PreSetting
 */
typedef struct
{
    unsigned char ucBandWidth; //0: 1.4MHz, 1: 3MHz, 2: 5MHz, 3: 10MHz, 4: 15MHz, 5: 20MHz
    bool bLteFddBandsInTestCases; // Indicate the LTE FDD bands are containing in the test cases for instrument presetting
    bool bLteTddBandsInTestCases; // Indicate the LTE TDD bands are containing in the test cases for instrument presetting
} S_RCTLIB_LTE_NSFT_PRESETTINGS_T;

/**
 * Descriptions: LTE NSFT RX BER
 */
typedef struct
{
    unsigned char       ucBandWidth; //0: 1.4MHz, 1: 3MHz, 2: 5MHz, 3: 10MHz, 4: 15MHz, 5: 20MHz
    unsigned char       ucDuplexMode; /* Refer to Tx duplexMode - tdd,fdd */
    unsigned char       ucBand;
    unsigned char       mcsMode; /* Refer to Tx mcsMode */
    unsigned short      usDlFrequency; // unit: 100KHz
} S_RCTLIB_LTE_NSFT_RX_BER_T;

/**
 * The structure for cable loss in frequency (Read from cfg)
 */
typedef struct
{
    unsigned short     usFrequencyIn100KHz;
    double             loss;
} S_RCTLIB_LTE_CABLE_LOSS_T;

// ======== TX NSFT test command start ============
typedef struct
{
    /* TX test check items */
    bool                          bTxPowerCheck;
    /* MS setting */
    unsigned char                 ucTxTestStep;
    char                          cRbOffset1;          //start VRB for the first period
    unsigned char                 ucRbLength1;
    char                          cRbOffset2;          //start VRB for the second period
    unsigned char                 ucRbLength2;
    unsigned char                 ucNoStep2ChangeVRB;  //0: Tx VRB will be changed to p2 at step 0
    float                         fStartTargetPower;
    float                         fStepPower;
    float                         fEndTargetPower;
} S_RCTLIB_LTE_NSFT_TEST_TX_SWEEP_REQ_T;

typedef struct
{
    /* TX test check items */
    bool                          bTxPowerCheck[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    bool                          bEvmCheck[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    bool                          bAclrCheck[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    bool                          bSemCheck[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    bool                          bFlatnessCheck[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    bool                          bGainErrCheck[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    bool                          bPhaseErrCheck[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    /* MS setting */
    unsigned char                 ucTxTestStep;
    char                          cRbOffset[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    unsigned char                 ucRbLength[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
    float                         fTargetPower[LTE_NSFT_MAX_TX_STEP_TEST_NUM];
} S_RCTLIB_LTE_NSFT_TEST_TX_STEP_REQ_T;

/* TX NSFT test command */
typedef struct
{
    /* Inst. setting and RX test check items */
    union
    {
        S_RCTLIB_LTE_NSFT_TEST_TX_STEP_REQ_T      txStepCmd;
        S_RCTLIB_LTE_NSFT_TEST_TX_SWEEP_REQ_T     txSweepCmd;
    };
    /* TX test command */
    unsigned short ulFrequency;
    char           cRequestOpetions; //0: follow power steps, 1: sweep powers with step (dBm)
    unsigned char  mcsMode; /* Refer to Tx mcsMode */
} S_RCTLIB_LTE_NSFT_TX_FREQ_CONFIG_T;

typedef struct
{
    unsigned char                 ucDuplexMode; /* Refer to Tx duplexMode - tdd,fdd */
    unsigned char                 ucBand;
    unsigned char                 ucFreqNum;
    unsigned short                usDlFrequency; // unit: 100KHz
    S_RCTLIB_LTE_NSFT_TX_FREQ_CONFIG_T  txFreqCmd[13];
} S_RCTLIB_LTE_NSFT_TX_BAND_CONFIG_T;

typedef struct
{
    unsigned char    ucFddTxStepWidth;//ms unit
    unsigned char    ucTddTxStepWidth;//ms unit
    unsigned char    ucFddToTddSwitchTime;//ms unit
    unsigned char    ucFddFreqSwitchTime;//ms unit
    unsigned char    ucTddFreqSwitchTime;//ms unit
    unsigned char    ucFddBandSwitchTime;//ms unit
    unsigned char    ucTddBandSwitchTime;//ms unit
    unsigned char    ucBandNum;
    unsigned short   usFddDlSyncTime;//ms unit
    unsigned short   usTddDlSyncTime;//ms unit
    double           dDownlinkSyncPowerDbm;
    unsigned char    ucBandwidth; /* Refer to Tx ulBandwidth - 6,15,25,50,75,100RB */
    S_RCTLIB_LTE_NSFT_TX_BAND_CONFIG_T  txBandCmd[10];
} S_RCTLIB_LTE_NSFT_TX_CONFIG_T;

// ======== TX NSFT test command end ============
/**
 * Descriptions: LTE AFC presetting
 */
typedef struct
{
    unsigned char band;
    unsigned short usFrequency;  /* the frequency to siwtch. Unit: 100KHz */
    short sFreqOffset;  /* the frequency to offset. Unit: KHz */
    double dExpectedPower;  /* the expected power, dBm */
    char cMeasurementCount;  /* measurement count */
} S_RCTLIB_LTE_AFC_PRESETTINGS_T;
/**
 * Description: LTE intrument's spcial settings
 */
typedef struct
{
    /// ========== FHC instrument parameters ==========
    /// FHC RX Max Step Count
    unsigned int uiFHC_RX_MaxStepCount;
    /// FHC TX Max Step Count
    unsigned int uiFHC_TX_MaxStepCount;
    /// FHC Multiple Band Support
    unsigned char ucFHC_MultiBand; // 0: single band, 1: multiple band support
    /// FHC FDD to TDD switch time (ms)
    unsigned char ucFHC_Fdd2TddSwitchTimeMS;
    /// FHC TDD to FDD switch time (ms)
    unsigned char ucFHC_Tdd2FddSwitchTimeMS;
    /// FHC FDD TX to RX switch time (ms)
    unsigned char ucFHC_FddTx2RxSwitchTimeMS;
    /// FHC TDD TX to RX switch time (ms)
    unsigned char ucFHC_TddTx2RxSwitchTimeMS;
    /// FHC frequency switch time (ms)
    unsigned char ucFHC_FreqSwitchTimeMS;
    /// FHC band switch time (ms)
    unsigned char ucFHC_BandSwitchTimeMS;
    /// FHC tx step width (ms)
    unsigned char ucFHC_TxStepWidthMS;
    /// FHC internal trigger delay time (us)
    unsigned int  uiFHC_InternalTriggerDelayTimeUs;
    /// FHC power adjust time (us)
    unsigned int  uiFHC_PowerAdjustTimeUs;
    /// ========== NSFT instrument parameters ==========
    /// NSFT RX Max Step Count
    unsigned int uiNSFT_RX_MaxStepCount;
    /// NSFT TX Max Step Count
    unsigned int uiNSFT_TX_MaxStepCount;
    /// NSFT Multiple Band Support
    unsigned char ucNSFT_MultiBand; // 0: single band, 1: multiple band support
    /// NSFT FDD TX step width (ms) bandwidth[1.4MB, 5MB, 10MB, 15MB, 20MB]
    unsigned char ucNSFT_FddTxSetpWidthMS[5];
    /// NSFT TDD TX step width (ms) bandwidth[1.4MB, 5MB, 10MB, 15MB, 20MB]
    unsigned char ucNSFT_TddTxSetpWidthMS[5];
    /// NSFT FDD to TDD switch time (ms)
    unsigned char ucNSFT_Fdd2TddSwitchTimeMS;
    /// NSFT FDD frequency switch time (ms)
    unsigned char ucNSFT_FddFreqSwitchTimeMS;
    /// NSFT TDD frequency switch time (ms)
    unsigned char ucNSFT_TddFreqSwitchTimeMS;
    /// NSFT FDD band switch time (ms)
    unsigned char ucNSFT_FddBandSwitchTimeMS;
    /// NSFT TDD band switch time (ms)
    unsigned char ucNSFT_TddBandSwitchTimeMS;
    /// NSFT FDD Downlink sync time (ms)
    unsigned short usNSFT_FddDownlinkSyncTimeMS;
    /// NSFT TDD Downlink sync time (ms)
    unsigned short usNSFT_TddDownlinkSyncTimeMS;
    /// NSFT list mode support
    bool bNSFT_ListModeSupported;
    /// NSFT MCS mode supported by frequency if false only by band
    bool bNSFT_McsModeByFrequencySupported;
} S_RCTLIB_LTE_SPECIFIC_SETTINGS_T;
/**
 * Descriptions: LTE traditional NSFT PreSetting
 */
typedef struct
{
    unsigned char ucBandWidth; //0: 1.4MHz, 1: 3MHz, 2: 5MHz, 3: 10MHz, 4: 15MHz, 5: 20MHz
} S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_PRESETTINGS_T;
/**
 * Descriptions: traditional TX NSFT test config (per step)
 */
typedef struct
{
    /* TX test check items */
    bool                          bTxPowerCheck;
    bool                          bEvmCheck;
    bool                          bAclrCheck;
    bool                          bSemCheck;
    bool                          bFlatnessCheck;
    bool                          bGainErrCheck;
    bool                          bPhaseErrCheck;
    /* MS setting */
    char                          cRbOffset;
    unsigned char                 ucRbLength;
    float                         fTargetPower;
    unsigned short usBand;
    unsigned short ulFrequency;
    unsigned short dlFrequency;
    unsigned char ucDuplexMode; // Indicate the duplex mode (0: TDD 1: FDD)

} S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_CONFIG_T;

/**
 * Descriptions: traditional TX NSFT test result (per step)
 */
typedef struct
{
    double                            dPoutPower;
    S_RCTLIB_LTE_NSFT_EVM_RESULT_T    sEVMResult;
    S_RCTLIB_LTE_NSFT_RIPPLE_RESULT_T sRpResult;
    S_RCTLIB_LTE_NSFT_ACP_RESULT_T    sACPResult;
    S_RCTLIB_LTE_NSFT_SEM_RESULT_T    sSEMResult;
} S_RCTLIB_LTE_NSFT_TX_TEST_FREQ_STEP_RESULT_T;

/**
 * Descriptions: Antenna port type definition.
 */
typedef enum
{
    TX,
    RX,
    RXD,
    ANTENNA_PORT_TYPE_NUM
} AntennaPortType;
/**********************************************
 * LTE structure (shared library defined END)
 **********************************************/
/**********************************************
 * LTE function (shared library defined START)
 **********************************************/
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_ConfigDefaultSettings(void);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_AFC_PreSetting(const S_RCTLIB_LTE_AFC_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_AFC_Initiate(void);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_AFC_FetchResult(double* freqerror);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_AGC_PreSetting();
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_AGC_ChangeCellBand(unsigned int band);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_AGC_ChangeFrequency(const S_RCTLIB_LTE_FREQUENCY_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_AGC_ChangeCellPower(double cellPower);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_APC_PreSetting(const S_RCTLIB_LTE_APC_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_APC_ChangeCellBand(unsigned int band);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_APC_ChangeUlFrequency(const S_RCTLIB_LTE_FREQUENCY_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_APC_ChangeExpectedPower(int expectedPower);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_APC_Initiate(void);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_APC_FetchResult(double* outputPower);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_FHC_PreSetting(const S_RCTLIB_LTE_FHC_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_FHC_StartIteration(const S_RCTLIB_LTE_FHC_MEASUREMENT_PARAM_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_FHC_FetchResult(const S_RCTLIB_LTE_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_LTE_FHC_MEASUREMENT_RESULT_T* pResult);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_FHC_CA_StartIteration(const S_RCTLIB_LTE_FHC_CA_MEASUREMENT_PARAM_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_FHC_CA_FetchResult(const S_RCTLIB_LTE_FHC_CA_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_LTE_FHC_CA_MEASUREMENT_RESULT_T* pResult);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_NSFT_PreSetting(const S_RCTLIB_LTE_NSFT_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_NSFT_TX_ListMode(const S_RCTLIB_LTE_NSFT_TX_CONFIG_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_NSFT_TX_FetchListMode(const S_RCTLIB_LTE_NSFT_TX_CONFIG_T* pSettings, S_RCTLIB_LTE_NSFT_TX_RESULT_T* pResult);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_NSFT_ChangeCellPower(double d_cell_power);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_NSFT_InitiateBER(const S_RCTLIB_LTE_NSFT_RX_BER_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_GET_SpecificSettings(S_RCTLIB_LTE_SPECIFIC_SETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_NSFT_TxFreqStepPreSetting(const S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_PRESETTINGS_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_NSFT_TxFreqStepInitiate(const S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_CONFIG_T* pSettings);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_NSFT_TxFreqStepFetch(const S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_CONFIG_T* pSettings, S_RCTLIB_LTE_NSFT_TX_TEST_FREQ_STEP_RESULT_T* pResult);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_GET_RxdLossOffset(unsigned char ucBand, unsigned short uiFreq100KHz, double* lossOffset);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_GET_GetCableLossMappingPort(unsigned char ucBand, AntennaPortType eAntennaPortType, unsigned char* port);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_GET_GetCableLossCalcByFrequency100KHz(unsigned char ucPort, unsigned short uiFreq100KHz, double* lossOffset);
NON_REENTRANT_FUNC int __stdcall RCTLIB_LTE_NSFT_GET_CableLossOffset(unsigned char ucBand, AntennaPortType eAntennaPortType, unsigned short uiFreq100KHz, double* lossoffset);
// reentrant
int __stdcall RCTLIB_LTE_ConfigDefaultSettings_r(const int meta_handle);
int __stdcall RCTLIB_LTE_AFC_PreSetting_r(const int meta_handle, const S_RCTLIB_LTE_AFC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_LTE_AFC_Initiate_r(const int meta_handle);
int __stdcall RCTLIB_LTE_AFC_FetchResult_r(const int meta_handle, double* freqerror);
int __stdcall RCTLIB_LTE_AGC_PreSetting_r(const int meta_handle);
int __stdcall RCTLIB_LTE_AGC_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_LTE_AGC_ChangeFrequency_r(const int meta_handle, const S_RCTLIB_LTE_FREQUENCY_T* pSettings);
int __stdcall RCTLIB_LTE_AGC_ChangeCellPower_r(const int meta_handle, double cellPower);
int __stdcall RCTLIB_LTE_APC_PreSetting_r(const int meta_handle, const S_RCTLIB_LTE_APC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_LTE_APC_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_LTE_APC_ChangeUlFrequency_r(const int meta_handle, const S_RCTLIB_LTE_FREQUENCY_T* pSettings);
int __stdcall RCTLIB_LTE_APC_ChangeExpectedPower_r(const int meta_handle, int expectedPower);
int __stdcall RCTLIB_LTE_APC_Initiate_r(const int meta_handle);
int __stdcall RCTLIB_LTE_APC_FetchResult_r(const int meta_handle, double* outputPower);
int __stdcall RCTLIB_LTE_FHC_PreSetting_r(const int meta_handle, const S_RCTLIB_LTE_FHC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_LTE_FHC_StartIteration_r(const int meta_handle, const S_RCTLIB_LTE_FHC_MEASUREMENT_PARAM_T* pSettings);
int __stdcall RCTLIB_LTE_FHC_FetchResult_r(const int meta_handle, const S_RCTLIB_LTE_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_LTE_FHC_MEASUREMENT_RESULT_T* pResult);
int __stdcall RCTLIB_LTE_FHC_CA_StartIteration_r(const int meta_handle, const S_RCTLIB_LTE_FHC_CA_MEASUREMENT_PARAM_T* pSettings);
int __stdcall RCTLIB_LTE_FHC_CA_FetchResult_r(const int meta_handle, const S_RCTLIB_LTE_FHC_CA_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_LTE_FHC_CA_MEASUREMENT_RESULT_T* pResult);
int __stdcall RCTLIB_LTE_NSFT_PreSetting_r(const int meta_handle, const S_RCTLIB_LTE_NSFT_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_LTE_NSFT_TX_ListMode_r(const int meta_handle, const S_RCTLIB_LTE_NSFT_TX_CONFIG_T* pSettings);
int __stdcall RCTLIB_LTE_NSFT_TX_FetchListMode_r(const int meta_handle, const S_RCTLIB_LTE_NSFT_TX_CONFIG_T* pSettings, S_RCTLIB_LTE_NSFT_TX_RESULT_T* pResult);
int __stdcall RCTLIB_LTE_NSFT_ChangeCellPower_r(const int meta_handle, double d_cell_power);
int __stdcall RCTLIB_LTE_NSFT_InitiateBER_r(const int meta_handle, const S_RCTLIB_LTE_NSFT_RX_BER_T* pSettings);
int __stdcall RCTLIB_LTE_GET_SpecificSettings_r(const int meta_handle, S_RCTLIB_LTE_SPECIFIC_SETTINGS_T* pSettings);
int __stdcall RCTLIB_LTE_NSFT_TxFreqStepPreSetting_r(const int meta_handle, const S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_LTE_NSFT_TxFreqStepInitiate_r(const int meta_handle, const S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_CONFIG_T* pSettings);
int __stdcall RCTLIB_LTE_NSFT_TxFreqStepFetch_r(const int meta_handle, const S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_CONFIG_T* pSettings, S_RCTLIB_LTE_NSFT_TX_TEST_FREQ_STEP_RESULT_T* pResult);
int __stdcall RCTLIB_LTE_GET_RxdLossOffset_r(const int meta_handle, unsigned char ucBand, unsigned short uiFreq100KHz, double* lossOffset);
int __stdcall RCTLIB_LTE_GET_GetCableLossMappingPort_r(const int meta_handle, unsigned char ucBand, AntennaPortType eAntennaPortType, unsigned char* port);
int __stdcall RCTLIB_LTE_GET_GetCableLossCalcByFrequency100KHz_r(const int meta_handle, unsigned char ucPort, unsigned short uiFreq100KHz, double* lossOffset);
int __stdcall RCTLIB_LTE_NSFT_GET_CableLossOffset_r(const int meta_handle, unsigned char ucBand, AntennaPortType eAntennaPortType, unsigned short uiFreq100KHz, double* lossoffset);
//=====================================================
//           LTE Callback defines
//=====================================================
typedef int (*RCTLIB_LTE_InstrumentInit_CALLBACK)(void);
typedef int (*RCTLIB_LTE_ConfigDefaultSettings_CALLBACK)();
typedef int (*RCTLIB_LTE_AFC_PreSetting_CALLBACK)(const S_RCTLIB_LTE_AFC_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_LTE_AFC_Initiate_CALLBACK)();
typedef int (*RCTLIB_LTE_AFC_FetchResult_CALLBACK)(double* freqerror);
typedef int (*RCTLIB_LTE_AGC_PreSetting_CALLBACK)();
typedef int (*RCTLIB_LTE_AGC_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_LTE_AGC_ChangeFrequency_CALLBACK)(const S_RCTLIB_LTE_FREQUENCY_T* pSettings);
typedef int (*RCTLIB_LTE_AGC_ChangeCellPower_CALLBACK)(double cellPower);
typedef int (*RCTLIB_LTE_APC_PreSetting_CALLBACK)(const S_RCTLIB_LTE_APC_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_LTE_APC_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_LTE_APC_ChangeUlFrequency_CALLBACK)(const S_RCTLIB_LTE_FREQUENCY_T* pSettings);
typedef int (*RCTLIB_LTE_APC_ChangeExpectedPower_CALLBACK)(int expectedPower);
typedef int (*RCTLIB_LTE_APC_Initiate_CALLBACK)();
typedef int (*RCTLIB_LTE_APC_FetchResult_CALLBACK)(double* outputPower);
typedef int (*RCTLIB_LTE_FHC_PreSetting_CALLBACK)(const S_RCTLIB_LTE_FHC_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_LTE_FHC_StartIteration_CALLBACK)(const S_RCTLIB_LTE_FHC_MEASUREMENT_PARAM_T* pSettings);
typedef int (*RCTLIB_LTE_FHC_FetchResult_CALLBACK)(const S_RCTLIB_LTE_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_LTE_FHC_MEASUREMENT_RESULT_T* pResult);
typedef int (*RCTLIB_LTE_FHC_CA_StartIteration_CALLBACK)(const S_RCTLIB_LTE_FHC_CA_MEASUREMENT_PARAM_T* pSettings);
typedef int (*RCTLIB_LTE_FHC_CA_FetchResult_CALLBACK)(const S_RCTLIB_LTE_FHC_CA_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_LTE_FHC_CA_MEASUREMENT_RESULT_T* pResult);
typedef int (*RCTLIB_LTE_NSFT_PreSetting_CALLBACK)(const S_RCTLIB_LTE_NSFT_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_LTE_NSFT_TX_ListMode_CALLBACK)(const S_RCTLIB_LTE_NSFT_TX_CONFIG_T* pSettings);
typedef int (*RCTLIB_LTE_NSFT_TX_FetchListMode_CALLBACK)(const S_RCTLIB_LTE_NSFT_TX_CONFIG_T* pSettings, S_RCTLIB_LTE_NSFT_TX_RESULT_T* pResult);
typedef int (*RCTLIB_LTE_NSFT_ChangeCellPower_CALLBACK)(double d_cell_power);
typedef int (*RCTLIB_LTE_NSFT_InitiateBER_CALLBACK)(const S_RCTLIB_LTE_NSFT_RX_BER_T* pSettings);
typedef int (*RCTLIB_LTE_GET_SpecificSettings_CALLBACK)(S_RCTLIB_LTE_SPECIFIC_SETTINGS_T* pSettings);
typedef int (*RCTLIB_LTE_NSFT_TxFreqStepPreSetting_CALLBACK)(const S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_LTE_NSFT_TxFreqStepInitiate_CALLBACK)(const S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_CONFIG_T* pSettings);
typedef int (*RCTLIB_LTE_NSFT_TxFreqStepFetch_CALLBACK)(const S_RCTLIB_LTE_NSFT_TX_FREQ_STEP_CONFIG_T* pSettings, S_RCTLIB_LTE_NSFT_TX_TEST_FREQ_STEP_RESULT_T* pResult);
typedef int (*RCTLIB_LTE_GET_RxdLossOffset_CALLBACK)(unsigned char ucBand, unsigned short uiFreq100KHz, double* lossOffset);
typedef int (*RCTLIB_LTE_GET_GetCableLossMappingPort_CALLBACK)(unsigned char ucBand, AntennaPortType eAntennaPortType, unsigned char* port);
typedef int (*RCTLIB_LTE_GET_GetCableLossCalcByFrequency100KHz_CALLBACK)(unsigned char ucPort, unsigned short uiFreq100KHz, double* lossOffset);
typedef int (*RCTLIB_LTE_NSFT_GET_CableLossOffset_CALLBACK)(unsigned char ucBand, AntennaPortType eAntennaPortType, unsigned short uiFreq100KHz, double* lossoffset);

typedef struct
{
    RCTLIB_LTE_InstrumentInit_CALLBACK InstrumentInit_CALLBACK;
    RCTLIB_LTE_ConfigDefaultSettings_CALLBACK ConfigDefaultSettings_CALLBACK;
    RCTLIB_LTE_AFC_PreSetting_CALLBACK AFC_PreSetting_CALLBACK;
    RCTLIB_LTE_AFC_Initiate_CALLBACK AFC_Initiate_CALLBACK;
    RCTLIB_LTE_AFC_FetchResult_CALLBACK AFC_FetchResult_CALLBACK;
    RCTLIB_LTE_AGC_PreSetting_CALLBACK AGC_PreSetting_CALLBACK;
    RCTLIB_LTE_AGC_ChangeCellBand_CALLBACK AGC_ChangeCellBand_CALLBACK;
    RCTLIB_LTE_AGC_ChangeFrequency_CALLBACK AGC_ChangeFrequency_CALLBACK;
    RCTLIB_LTE_AGC_ChangeCellPower_CALLBACK AGC_ChangeCellPower_CALLBACK;
    RCTLIB_LTE_APC_PreSetting_CALLBACK APC_PreSetting_CALLBACK;
    RCTLIB_LTE_APC_ChangeCellBand_CALLBACK APC_ChangeCellBand_CALLBACK;
    RCTLIB_LTE_APC_ChangeUlFrequency_CALLBACK APC_ChangeUlFrequency_CALLBACK;
    RCTLIB_LTE_APC_ChangeExpectedPower_CALLBACK APC_ChangeExpectedPower_CALLBACK;
    RCTLIB_LTE_APC_Initiate_CALLBACK APC_Initiate_CALLBACK;
    RCTLIB_LTE_APC_FetchResult_CALLBACK APC_FetchResult_CALLBACK;
    RCTLIB_LTE_FHC_PreSetting_CALLBACK FHC_PreSetting_CALLBACK;
    RCTLIB_LTE_FHC_StartIteration_CALLBACK FHC_StartIteration_CALLBACK;
    RCTLIB_LTE_FHC_FetchResult_CALLBACK FHC_FetchResult_CALLBACK;
    RCTLIB_LTE_FHC_CA_StartIteration_CALLBACK FHC_CA_StartIteration_CALLBACK;
    RCTLIB_LTE_FHC_CA_FetchResult_CALLBACK FHC_CA_FetchResult_CALLBACK;
    RCTLIB_LTE_NSFT_PreSetting_CALLBACK NSFT_PreSetting_CALLBACK;
    RCTLIB_LTE_NSFT_TX_ListMode_CALLBACK NSFT_TX_ListMode_CALLBACK;
    RCTLIB_LTE_NSFT_TX_FetchListMode_CALLBACK NSFT_TX_FetchListMode_CALLBACK;
    RCTLIB_LTE_NSFT_ChangeCellPower_CALLBACK NSFT_ChangeCellPower_CALLBACK;
    RCTLIB_LTE_NSFT_InitiateBER_CALLBACK NSFT_InitiateBER_CALLBACK;
    RCTLIB_LTE_GET_SpecificSettings_CALLBACK GET_SpecificSettings_CALLBACK;
    RCTLIB_LTE_NSFT_TxFreqStepPreSetting_CALLBACK NSFT_TxFreqStepPreSetting_CALLBACK;
    RCTLIB_LTE_NSFT_TxFreqStepInitiate_CALLBACK NSFT_TxFreqStepInitiate_CALLBACK;
    RCTLIB_LTE_NSFT_TxFreqStepFetch_CALLBACK NSFT_TxFreqStepFetch_CALLBACK;
    RCTLIB_LTE_GET_RxdLossOffset_CALLBACK RxdLossOffset_CALLBACK;
    RCTLIB_LTE_GET_GetCableLossMappingPort_CALLBACK GetCableLossMappingPort_CALLBACK;
    RCTLIB_LTE_GET_GetCableLossCalcByFrequency100KHz_CALLBACK GetCableLossCalcByFrequency100KHz_CALLBACK;
    RCTLIB_LTE_NSFT_GET_CableLossOffset_CALLBACK GetCableLossOffset_CALLBACK;
    // please add in the last
} RCTLIB_LTE_CALLBACKS_CFG_T;

/**
 * Register callbacks interface
 **/
NON_REENTRANT_FUNC int __stdcall RCTLIB_SetLTEInstrumentInstance(RCTLIB_LTE_CALLBACKS_CFG_T* instCallbacks);

// reentrant functions
int __stdcall RCTLIB_SetLTEInstrumentInstance_r(const int meta_handle, RCTLIB_LTE_CALLBACKS_CFG_T* instCallbacks);
/**********************************************
 * LTE function (shared library defined END)
 **********************************************/
#endif //#ifdef __META_LTE__
#ifdef __META_C2K__
/*****************************
 * C2K
 *****************************/
/**********************************************
 * C2K structure (shared library defined START)
 **********************************************/
/**
 * Descriptions: C2K AGC PreSetting
 */
typedef struct
{
    /// tester operating mode
    unsigned int mode;
    /// cell power for AGC calibration
    double cellPower;
    /// F-Pilot channel power (dB)
    double pilotPower;
    /// F-SYNC channel power (dB)
    double syncPower;
    /// F-PCH power (dB)
    double pchPower;
    /// F-FCH power (dB)
    double fchPower;
} S_RCTLIB_C2K_AGC_PRESETTINGS_T;
/**
 * Descriptions: C2K APC PreSetting
 */
typedef struct
{
    /// measurement timeout setting (ms)
    double timeout;
    /// measurement interval (us)
    double measurementInterval;
    /// trigger delay (us)
    double triggerDelay;
} S_RCTLIB_C2K_APC_PRESETTINGS_T;
typedef struct
{
    /// measurement timeout setting (ms)
    double timeout;
    /// measurement interval (us)
    double measurementInterval;
    /// trigger delay (us)
    double triggerDelay;
    unsigned int triggerType; //trigger type 0:immediate 1:Rise
} S_RCTLIB_C2K_APC_PRESETTINGS_EX_T;
typedef struct
{
    /// step width (ms)
    double stepWidth;
    /// F-Pilot channel power (dB)
    double pilotPower;
    /// F-SYNC channel power (dB)
    double syncPower;
    /// F-PCH power (dB)
    double pchPower;
    /// F-FCH power (dB)
    double fchPower;
} S_RCTLIB_C2K_FHC_PRESETTINGS_T;
typedef struct
{
    /// UARFCN in MHz
    double mHz;
    /// UARFCN
    unsigned short uarfcn;
} S_RCTLIB_C2K_FHC_FREQ_STEP_U;
/**
 * The structure for storing C2K FHC request
 */
typedef struct
{
    /// band class
    unsigned int e_band;
    /// measurement timeout setting
    double d_meas_timeout_sec;
    /// retune step width (ms)
    unsigned int retuneWidth;
    /// start index of UE TX power step
    int    txPowerStepStartIndex;
    /// start index of UE TX frequency step
    int    txFrequencyStepStartIndex;
    /// start index of UE RX power step
    int    rxPowerStepStartIndex;
    /// start index of UE RX frequency step
    int    rxFrequencyStepStartIndex;
    /// number of power step
    int    numberOfPowerSteps;
    /// number of frequency step
    int    numberOfFrequencySteps;
    /// expected TX power level (dBm)
    double txPowerSteps[20];
    /// down-link power level (dBm)
    double rxPowerSteps[20];
    /// UE TX frequency setting in each frequency step (UARFCN or MHz)
    S_RCTLIB_C2K_FHC_FREQ_STEP_U txFreqSteps[20];
    /// UE RX frequency setting in each frequency step (UARFCN or MHz)
    S_RCTLIB_C2K_FHC_FREQ_STEP_U rxFreqSteps[20];
} S_RCTLIB_C2K_FHC_MEASUREMENT_PARAM_T;
/**
 * The structure for storing C2K FHC TX power result
 */
typedef struct
{
    /// integrity of the measurement result
    int    integrity;
    /// frequency step
    int    numberOfFrequencySteps;
    /// power step
    int    numberOfPowerSteps;
    /// frequency step * power step count
    int    tx_pwr_cnt;
    /// [OUT] power measurement result array
    double d_tx_power[400];
    /// [OUT] power measurement result count
    int    real_cnt;
} S_RCTLIB_C2K_FHC_MEASUREMENT_RESULT_T;
/**
 * The structure for storing C2K NSFT TPC control used in TX performance
 */
typedef struct
{
    /// specify the test pattern (0: All up for UE max power, 1: All down for UE min power, 2: active for specified power
    int i_Pattern;
    /// TPC algorithm  (1: algo1 2: algo2)
    unsigned int u_Algorithm;
    /// TPC step size
    int i_Step;
    /// the target power if the i_Pattern is 2, expected power if the tpc pattern is 0 or 1 (all up or all down)
    double d_TargetPower;
} S_RCTLIB_C2K_NSFT_TPC_REQUEST_T;
/**
 * The structure for storing C2K NSFT FER result
 */
typedef struct
{
    /// FER
    double d_fer;
    /// frame error count
    int i_err_cnt;
    /// total test count
    int i_total_cnt;
} S_RCTLIB_C2K_NSFT_FER_RESULT_T;
/**
 * The structure for storing C2K NSFT APP result
 */
typedef struct
{
    /// access probe power
    double d_probe_power;
} S_RCTLIB_C2K_NSFT_APP_RESULT_T;
/**
 * The structure for storing C2K NSFT SPUR result
 */
typedef struct
{
    /// pass flag (overall)
    bool bPass;
    /// lower adjacent emission
    double d_spur_lower_adj;
    /// upper adjacent emission
    double d_spur_upper_adj;
    /// lower alternate emission
    double d_spur_lower_alt;
    /// upper alternate emission
    double d_spur_upper_alt;
} S_RCTLIB_C2K_NSFT_SPUR_RESULT_T;
/**
 * The structure for storing C2K NSFT WQ result
 */
typedef struct
{
    /// Rho
    double d_rho;
    /// Frequency Error
    double d_freq_error;
    /// Time Error
    double d_time_error;
    /// Carrier Feed through
    double d_carrier_feed;
    /// Phase Error
    double d_phase_error;
    /// Magnitude Error
    double d_mag_error;
    /// EVM (%)
    double d_evm;
} S_RCTLIB_C2K_NSFT_WQ_RESULT_T;
/**
 * The structure for storing C2K NSFT ILPC result
 */
typedef struct
{
    /// integrity
    int     i_Integrity;
    /// pass flag (overall)
    bool    bPass;
    /// number of slots
    int     i_NumSlots;
    /// power (ABS)
    double  d_Absolute[100];
    /// delta value between each step
    double  d_Delta[100];
    bool    bCal_fail;
} S_RCTLIB_C2K_NSFT_ILPC_RESULT_T;
/**
 * the structure for storing C2K NSFT TX performance (max power) measurement result
 */
typedef struct
{
    /// UE power
    double m_dUEPower;
    /// spurious emission test result (emission mask)
    S_RCTLIB_C2K_NSFT_SPUR_RESULT_T spurResult;
    /// WQ test result
    S_RCTLIB_C2K_NSFT_WQ_RESULT_T wqResult;
} S_RCTLIB_C2K_NSFT_TX_PERF_MAX_POWER_RESULT_T;
/**
 * the structure for storing C2K NSFT TX performance (min power) measurement result
 */
typedef struct
{
    /// UE power
    double m_dUEPower;
} S_RCTLIB_C2K_NSFT_TX_PERF_MIN_POWER_RESULT_T;
/**
 * Descriptions: C2K NSFT PreSetting
 */
typedef struct
{
    /// measurement timeout value (ms)
    double timeout;
    /// cell power for UE NSFT sync
    double cellPower;
    /// FER test count;
    unsigned int fer_frame_count;
    /// F-Pilot channel power (dB)
    double pilotPower;
    /// F-SYNC channel power (dB)
    double syncPower;
    /// F-PCH power (dB)
    double pchPower;
    /// F-FCH power (dB)
    double fchPower;
} S_RCTLIB_C2K_NSFT_PRESETTINGS_T;
/**
 * C2K NSFT test case config
 */
typedef struct
{
    /// Band Class
    unsigned int bandclass;
    /// UARFCN
    unsigned int uarfcn;
    /// up-link cable loss
    double cableloss_ul;
    /// down-link cable loss
    double cableloss_dl;
    /// init cell power
    double cell_power;
} S_RCTLIB_C2K_NSFT_CONFIG_T;
/**
 * C2K NSFT APP PreSetting
 */
typedef struct
{
    /// timeout (second)
    double timeout;
    /// F-Pilot channel power (dB)
    double pilotPower;
    /// F-SYNC channel power (dB)
    double syncPower;
    /// F-PCH power (dB)
    double pchPower;
    /// F-FCH power (dB)
    double fchPower;
    /// power increase between each access probe
    int probeSize;
    /// power step count
    int probeSteps;
} S_RCTLIB_C2K_NSFT_APP_PRESETTING_T;
/**
 * C2K NSFT APP test case config
 */
typedef struct
{
    /// Band Class
    unsigned int bandclass;
    /// UARFCN
    unsigned int uarfcn;
    /// up-link cable loss
    double cableloss_ul;
    /// down-link cable loss
    double cableloss_dl;
} S_RCTLIB_C2K_NSFT_APP_CONFIG_T;
/**
 * Descriptions: C2K AFC presetting
 */
typedef struct
{
    /// Band Class for AFC calibration
    unsigned int bandclass;
    /// UARFCN for AFC calibration
    unsigned int uarfcn;
    /// tx power for AFC calibration
    double d_tx_power;
    int freq_offset_hz;
} S_RCTLIB_C2K_AFC_PRESETTINGS_T;
/**
 * Descriptions: C2K instrument's special settings
 */
typedef struct
{
    /// Traditional calibration support
    bool bTCSupport;
    /// Fast calibration support
    bool bFHCSupport;
    /// C2K NSFT TX and FER test reverse
    bool usNSFT_TxFer_Reverse;
    /// C2K Selected port for two port Rxd
    E_RCTLIB_PORT_TYPE eRxdPathLossPort;
} S_RCTLIB_C2K_SPECIFIC_SETTINGS_T;

/* list mode */
typedef struct
{
    /// CS0011 parameters
    S_RCTLIB_C2K_NSFT_PRESETTINGS_T cs0011Param;
} S_RCTLIB_C2K_LIST_MODE_NSFT_PRESETTING_T;

typedef struct
{
#define C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM   50
    /// UARFCN
    unsigned int uarfcn[C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    /// uplink cable loss
    double cableloss_ul[C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    /// downlink cable loss
    double cableloss_dl[C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    /// init cell power(unit: dBm)
    double cell_power;
    ///peak power (unit: dBm) , [0]: max peak power, [1]: min peak power
    double dPeakpower[2];
    ///Expected power (unit: dBm) , [0]: Expected max power, [1]: Expected min power
    double dExpectedpower[2];
    ///FER power level(unit: dBm)
    double dC2k_FER_power[C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];

    unsigned char ucBand[C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    unsigned char valid_freq; //valid count of freq.
    /* the time settings, unit = frame */
    unsigned short test_time[C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM]; //the total time of each freq. for freq. array
} S_RCTLIB_C2K_LIST_MODE_NSFT_INIT_SETTING_T;

/**
 * The structure for storing NSFT EVM result of list moe
 */
typedef struct
{
    /// Rho
    double d_rho;
    /// Frequency Error
    double d_freq_error;
    /// Time Error
    double d_time_error;
    /// Carrier Feed Through
    double d_carrier_feed;
    /// Phase Error
    double d_phase_error;
    /// Magnitude Error
    double d_mag_error;
    /// EVM RMS (%)
    double dRMS_EVM;
    /// EVM Pk (%)
    double dPeak_EVM;
    /// IQ Offset (dB)
    //double dIq_Offset_dB;
    /// PCDE (max, dB)
    double dpcde;
} S_RCTLIB_C2K_LIST_MODE_NSFT_EVM_RESULT_T;

/**
 * the structure for storing ACP(Tx Spurious) result of list mode
 */
typedef struct
{
    /// pass flag (overall)
    bool bPass;
    /// lower adjacent emission
    double d_spur_lower_adj;
    /// upper adjacent emission
    double d_spur_upper_adj;
    /// lower alternate emission
    double d_spur_lower_alt;
    /// upper alternate emission
    double d_spur_upper_alt;
    /// Total Carrier Power(unit: dBm)
    double dCarrierPower;
    /// Occupied bandwidth (MHz)
    double dOBW;
} S_RCTLIB_C2K_LIST_MODE_NSFT_ACP_RESULT_T;

/**
 * the structure for storing TX list mode step result
 */
typedef struct
{
#define C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM   50
    double  dMaxPower[C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    double  dMinPower[C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_C2K_LIST_MODE_NSFT_ACP_RESULT_T  sACPResult[C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
    S_RCTLIB_C2K_LIST_MODE_NSFT_EVM_RESULT_T  sEVMResult[C2K_LIST_MODE_NSFT_MAX_TX_STEP_TEST_NUM];
} S_RCTLIB_C2K_LIST_MODE_NSFT_TEST_TX_STEP_RESULT_T;

typedef struct
{
    int nValid_Freq;
    S_RCTLIB_C2K_LIST_MODE_NSFT_TEST_TX_STEP_RESULT_T txListModeResult;
} S_RCTLIB_C2K_LIST_MODE_NSFT_RESULT_T;
/**********************************************
 * C2K structure (shared library defined END)
 **********************************************/
/**********************************************
 * C2K function (shared library defined START)
 **********************************************/
int __stdcall RCTLIB_C2K_ConfigCellPower(double power);
int __stdcall RCTLIB_C2K_ConfigDefaultSettings(void);
int __stdcall RCTLIB_C2K_AFC_PreSetting(const S_RCTLIB_C2K_AFC_PRESETTINGS_T* pSettings, unsigned int size);
int __stdcall RCTLIB_C2K_AFC_FetchResult(double* freqError);
// Main path AGC calibration RCT controls
int __stdcall RCTLIB_C2K_AGC_PreSetting(const S_RCTLIB_C2K_AGC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_AGC_ChangeCellBand(unsigned int band);
int __stdcall RCTLIB_C2K_AGC_ChangeChannel(unsigned int uarfcn);
int __stdcall RCTLIB_C2K_AGC_ChangeCellPower(double cellPower);
// Diversity path AGC calibration RCT controls
int __stdcall RCTLIB_C2K_AGC_RXD_PreSetting(const S_RCTLIB_C2K_AGC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_AGC_RXD_ChangeCellBand(unsigned int band);
int __stdcall RCTLIB_C2K_AGC_RXD_ChangeChannel(unsigned int uarfcn);
int __stdcall RCTLIB_C2K_AGC_RXD_ChangeCellPower(double cellPower);

int __stdcall RCTLIB_C2K_APC_PreSetting(const S_RCTLIB_C2K_APC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_APC_PreSetting_Ex(const S_RCTLIB_C2K_APC_PRESETTINGS_EX_T* pSettings);
int __stdcall RCTLIB_C2K_APC_ChangeCellBand(unsigned int band);
int __stdcall RCTLIB_C2K_APC_ChangeChannel(unsigned int uarfcn);
int __stdcall RCTLIB_C2K_APC_ChangeExpectedPower(int expectedPower);
int __stdcall RCTLIB_C2K_APC_Initiate(void);
int __stdcall RCTLIB_C2K_APC_FetchResult(double* outputPower);
int __stdcall RCTLIB_C2K_FHC_PreSetting(const S_RCTLIB_C2K_FHC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_FHC_StartIteration(const S_RCTLIB_C2K_FHC_MEASUREMENT_PARAM_T* pSettings);
int __stdcall RCTLIB_C2K_FHC_FetchResult(const S_RCTLIB_C2K_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_C2K_FHC_MEASUREMENT_RESULT_T* pResult);
int __stdcall RCTLIB_C2K_NSFT_PreSetting(const S_RCTLIB_C2K_NSFT_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_NSFT_InitiateTestCase(const S_RCTLIB_C2K_NSFT_CONFIG_T* pSettings);
int __stdcall RCTLIB_C2K_NSFT_ChangeCellPower(double d_cell_power);
int __stdcall RCTLIB_C2K_NSFT_TPC(const S_RCTLIB_C2K_NSFT_TPC_REQUEST_T* tpc_request);
int __stdcall RCTLIB_C2K_NSFT_FetchTXPerformanceMaxPower(S_RCTLIB_C2K_NSFT_TX_PERF_MAX_POWER_RESULT_T* tx_perf_result);
int __stdcall RCTLIB_C2K_NSFT_FetchTXPerformanceMinPower(S_RCTLIB_C2K_NSFT_TX_PERF_MIN_POWER_RESULT_T* tx_perf_result);
int __stdcall RCTLIB_C2K_NSFT_InitiateFER();
int __stdcall RCTLIB_C2K_NSFT_ReadFER(S_RCTLIB_C2K_NSFT_FER_RESULT_T* result);
int __stdcall RCTLIB_C2K_NSFT_APP_PreSetting(const S_RCTLIB_C2K_NSFT_APP_PRESETTING_T* pSettings);
int __stdcall RCTLIB_C2K_NSFT_APP_CasePreSetting();
int __stdcall RCTLIB_C2K_NSFT_APP_InitiateTestCase(const S_RCTLIB_C2K_NSFT_APP_CONFIG_T* pSettings);
int __stdcall RCTLIB_C2K_NSFT_APP_ChangeCellPower(double d_cell_power);
int __stdcall RCTLIB_C2K_NSFT_APP_FetchTestCase(S_RCTLIB_C2K_NSFT_APP_RESULT_T* result);
int __stdcall RCTLIB_C2K_EVDO_NSFT_PreSetting(const S_RCTLIB_C2K_NSFT_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_EVDO_NSFT_InitiateTestCase(const S_RCTLIB_C2K_NSFT_CONFIG_T* pSettings);
int __stdcall RCTLIB_C2K_EVDO_NSFT_TPC(const S_RCTLIB_C2K_NSFT_TPC_REQUEST_T* tpc_request);
int __stdcall RCTLIB_C2K_EVDO_NSFT_FetchTXPerformanceMaxPower(S_RCTLIB_C2K_NSFT_TX_PERF_MAX_POWER_RESULT_T* tx_perf_result);
int __stdcall RCTLIB_C2K_EVDO_NSFT_FetchTXPerformanceMinPower(S_RCTLIB_C2K_NSFT_TX_PERF_MIN_POWER_RESULT_T* tx_perf_result);
int __stdcall RCTLIB_C2K_EVDO_NSFT_InitiatePER();
int __stdcall RCTLIB_C2K_EVDO_NSFT_ReadPER(S_RCTLIB_C2K_NSFT_FER_RESULT_T* result);
int __stdcall RCTLIB_C2K_GET_SpecificSettings(S_RCTLIB_C2K_SPECIFIC_SETTINGS_T* pSettings);

// reentrant functions
int __stdcall RCTLIB_C2K_ConfigCellPower_r(const int meta_handle, double power);
int __stdcall RCTLIB_C2K_ConfigDefaultSettings_r(const int meta_handle);
int __stdcall RCTLIB_C2K_AFC_PreSetting_r(const int meta_handle, const S_RCTLIB_C2K_AFC_PRESETTINGS_T* pSettings, unsigned int size);
int __stdcall RCTLIB_C2K_AFC_FetchResult_r(const int meta_handle, double* freqError);
// Main path AGC calibration RCT controls
int __stdcall RCTLIB_C2K_AGC_PreSetting_r(const int meta_handle, const S_RCTLIB_C2K_AGC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_AGC_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_C2K_AGC_ChangeChannel_r(const int meta_handle, unsigned int uarfcn);
int __stdcall RCTLIB_C2K_AGC_ChangeCellPower_r(const int meta_handle, double cellPower);
// Diversity path AGC calibration RCT controls
int __stdcall RCTLIB_C2K_AGC_RXD_PreSetting_r(const int meta_handle, const S_RCTLIB_C2K_AGC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_AGC_RXD_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_C2K_AGC_RXD_ChangeChannel_r(const int meta_handle, unsigned int uarfcn);
int __stdcall RCTLIB_C2K_AGC_RXD_ChangeCellPower_r(const int meta_handle, double cellPower);

int __stdcall RCTLIB_C2K_APC_PreSetting_r(const int meta_handle, const S_RCTLIB_C2K_APC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_APC_PreSetting_Ex_r(const int meta_handle, const S_RCTLIB_C2K_APC_PRESETTINGS_EX_T* pSettings);
int __stdcall RCTLIB_C2K_APC_ChangeCellBand_r(const int meta_handle, unsigned int band);
int __stdcall RCTLIB_C2K_APC_ChangeChannel_r(const int meta_handle, unsigned int uarfcn);
int __stdcall RCTLIB_C2K_APC_ChangeExpectedPower_r(const int meta_handle, int expectedPower);
int __stdcall RCTLIB_C2K_APC_Initiate_r(const int meta_handle);
int __stdcall RCTLIB_C2K_APC_FetchResult_r(const int meta_handle, double* outputPower);
int __stdcall RCTLIB_C2K_FHC_PreSetting_r(const int meta_handle, const S_RCTLIB_C2K_FHC_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_FHC_StartIteration_r(const int meta_handle, const S_RCTLIB_C2K_FHC_MEASUREMENT_PARAM_T* pSettings);
int __stdcall RCTLIB_C2K_FHC_FetchResult_r(const int meta_handle, const S_RCTLIB_C2K_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_C2K_FHC_MEASUREMENT_RESULT_T* pResult);
int __stdcall RCTLIB_C2K_NSFT_PreSetting_r(const int meta_handle, const S_RCTLIB_C2K_NSFT_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_NSFT_InitiateTestCase_r(const int meta_handle, const S_RCTLIB_C2K_NSFT_CONFIG_T* pSettings);
int __stdcall RCTLIB_C2K_NSFT_ChangeCellPower_r(const int meta_handle, double d_cell_power);
int __stdcall RCTLIB_C2K_NSFT_TPC_r(const int meta_handle, const S_RCTLIB_C2K_NSFT_TPC_REQUEST_T* tpc_request);
int __stdcall RCTLIB_C2K_NSFT_FetchTXPerformanceMaxPower_r(const int meta_handle, S_RCTLIB_C2K_NSFT_TX_PERF_MAX_POWER_RESULT_T* tx_perf_result);
int __stdcall RCTLIB_C2K_NSFT_FetchTXPerformanceMinPower_r(const int meta_handle, S_RCTLIB_C2K_NSFT_TX_PERF_MIN_POWER_RESULT_T* tx_perf_result);
int __stdcall RCTLIB_C2K_NSFT_InitiateFER_r(const int meta_handle);
int __stdcall RCTLIB_C2K_NSFT_ReadFER_r(const int meta_handle, S_RCTLIB_C2K_NSFT_FER_RESULT_T* result);
int __stdcall RCTLIB_C2K_NSFT_APP_PreSetting_r(const int meta_handle, const S_RCTLIB_C2K_NSFT_APP_PRESETTING_T* pSettings);
int __stdcall RCTLIB_C2K_NSFT_APP_CasePreSetting_r(const int meta_handle);
int __stdcall RCTLIB_C2K_NSFT_APP_InitiateTestCase_r(const int meta_handle, const S_RCTLIB_C2K_NSFT_APP_CONFIG_T* pSettings);
int __stdcall RCTLIB_C2K_NSFT_APP_ChangeCellPower_r(const int meta_handle, double d_cell_power);
int __stdcall RCTLIB_C2K_NSFT_APP_FetchTestCase_r(const int meta_handle, S_RCTLIB_C2K_NSFT_APP_RESULT_T* result);
int __stdcall RCTLIB_C2K_EVDO_NSFT_PreSetting_r(const int meta_handle, const S_RCTLIB_C2K_NSFT_PRESETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_EVDO_NSFT_InitiateTestCase_r(const int meta_handle, const S_RCTLIB_C2K_NSFT_CONFIG_T* pSettings);
int __stdcall RCTLIB_C2K_EVDO_NSFT_TPC_r(const int meta_handle, const S_RCTLIB_C2K_NSFT_TPC_REQUEST_T* tpc_request);
int __stdcall RCTLIB_C2K_EVDO_NSFT_FetchTXPerformanceMaxPower_r(const int meta_handle, S_RCTLIB_C2K_NSFT_TX_PERF_MAX_POWER_RESULT_T* tx_perf_result);
int __stdcall RCTLIB_C2K_EVDO_NSFT_FetchTXPerformanceMinPower_r(const int meta_handle, S_RCTLIB_C2K_NSFT_TX_PERF_MIN_POWER_RESULT_T* tx_perf_result);
int __stdcall RCTLIB_C2K_EVDO_NSFT_InitiatePER_r(const int meta_handle);
int __stdcall RCTLIB_C2K_EVDO_NSFT_ReadPER_r(const int meta_handle, S_RCTLIB_C2K_NSFT_FER_RESULT_T* result);
int __stdcall RCTLIB_C2K_GET_SpecificSettings_r(const int meta_handle, S_RCTLIB_C2K_SPECIFIC_SETTINGS_T* pSettings);
int __stdcall RCTLIB_C2K_LIST_MODE_NSFT_PreSetting_r(const int meta_handle, const S_RCTLIB_C2K_LIST_MODE_NSFT_PRESETTING_T* pSetting, const unsigned int length);
int __stdcall RCTLIB_C2K_LIST_MODE_NSFT_InitiateTestPlan_r(const int meta_handle, const S_RCTLIB_C2K_LIST_MODE_NSFT_INIT_SETTING_T* pSetting, const unsigned int length);
int __stdcall RCTLIB_C2K_LIST_MODE_NSFT_FetchTestPlanResult_r(const int meta_handle, S_RCTLIB_C2K_LIST_MODE_NSFT_RESULT_T* pResult, const unsigned int length);
/**********************************************
 * C2K function (shared library defined END)
 **********************************************/
#endif //#ifdef __META_C2K__

/*****************************************************
 * exported function (END)
 *****************************************************/


/*****************************************************
 * Customized Instrument register interface
 *****************************************************/

//=====================================================
// Customzied common interface
//=====================================================
typedef int (*RCTLIB_InitializeConfiguration_CALLBACK)(const char* cfg_file_path);
typedef int (*RCTLIB_ConnectRCT_CALLBACK)(void);
typedef int (*RCTLIB_DisconnectRCT_CALLBACK)(void);
typedef int (*RCTLIB_QueryCurrentApplicationFormat_CALLBACK)(char* buf, int buf_len);
typedef int (*RCTLIB_ConfigApplicationFormat_CALLBACK)(unsigned int format);
typedef int (*RCTLIB_ConfigOperatingMode_CALLBACK)(unsigned int OperatingMode);
typedef int (*RCTLIB_Reset_CALLBACK)(void);


typedef struct
{
    RCTLIB_InitializeConfiguration_CALLBACK  InitializeConfiguration_CALLBACK;
    RCTLIB_ConnectRCT_CALLBACK  ConnectRCT_CALLBACK;
    RCTLIB_DisconnectRCT_CALLBACK  DisconnectRCT_CALLBACK;
    RCTLIB_QueryCurrentApplicationFormat_CALLBACK  QueryCurrentApplicationFormat_CALLBACK;
    RCTLIB_ConfigApplicationFormat_CALLBACK  ConfigApplicationFormat_CALLBACK;
    RCTLIB_ConfigOperatingMode_CALLBACK  ConfigOperatingMode_CALLBACK;
    RCTLIB_Reset_CALLBACK  Reset_CALLBACK;
    // please add in the last
} RCTLIB_COMMON_CALLBACKS_CFG_T;

//=====================================================
//           GGE Callback defines
//=====================================================

typedef int (*RCTLIB_GGE_InstrumentInit_CALLBACK)(void);
typedef int (*RCTLIB_GGE_Cableloss_Settings_CALLBACK)(S_RCTLIB_GGE_Cableloss_CONFIG_T cable_loss);
typedef int (*RCTLIB_GGE_ConfigCellPower_CALLBACK)(double power);
typedef int (*RCTLIB_GGE_ConfigDefaultSettings_CALLBACK)(void);
typedef int (*RCTLIB_GGE_ConfigAnalyzerFrequencyOffset_CALLBACK)(const S_RCTLIB_GGE_FREQUENCY_OFFSET_SETTINGS_T* pSettings, unsigned int sz);
typedef int (*RCTLIB_GGE_CAPID_PreSettings_CALLBACK)(const S_RCTLIB_GGE_CAPID_SETTINGS_T* pSettings);
typedef int (*RCTLIB_GGE_CAPID_Iteration_CALLBACK)(double* frequency_error);
typedef int (*RCTLIB_GGE_AFC_PreSettings_CALLBACK)(const S_RCTLIB_GGE_AFC_SETTINGS_T* pSettings);
typedef int (*RCTLIB_GGE_AGC_PreSettings_CALLBACK)(double d_power);
typedef int (*RCTLIB_GGE_AGC_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_GGE_AGC_ChangeChannel_CALLBACK)(unsigned int arfcn);
typedef int (*RCTLIB_GGE_APCDCOffset_PreSettings_CALLBACK)(unsigned int tsc);
typedef int (*RCTLIB_GGE_APCDCOffset_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_GGE_APCDCOffset_Iteration_CALLBACK)(unsigned int arfcn, double expected_power, int PCL, double* d_power);
typedef int (*RCTLIB_GGE_PedestalDCOffset_Iteration_CALLBACK)(unsigned int arfcn, double expected_power, double* d_power);
typedef int (*RCTLIB_GGE_EDGE_APCDCOffset_PreSettings_CALLBACK)(unsigned int tsc);
typedef int (*RCTLIB_GGE_EDGE_APCDCOffset_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_GGE_EDGE_APCDCOffset_Iteration_CALLBACK)(unsigned int arfcn, double expected_power, int PCL, double* d_power);
typedef int (*RCTLIB_GGE_EDGE_APC_SetExceptedPower_CALLBACK)(double expected_power);
typedef int (*RCTLIB_GGE_EDGE_APC_Iteration_CALLBACK)(unsigned int arfcn, double* d_power);

typedef int (*RCTLIB_GGE_FHC_DTS_PreSettings_CALLBACK)();
typedef int (*RCTLIB_GGE_FHC_DTS_Iteration_CALLBACK)(S_RCTLIB_FHC_DL_List_T List, int ListLength);
typedef int (*RCTLIB_GGE_FHC_DTS_START_CALLBACK)();
typedef int (*RCTLIB_GGE_FHC_DTS_STOP_CALLBACK)();

typedef int (*RCTLIB_GGE_FHC_UTS_PreSettings_CALLBACK)();
typedef int (*RCTLIB_GGE_FHC_UTS_Iteration_CALLBACK)( S_RCTLIB_GGE_FHC_TX_UTS_T* uts);
typedef int (*RCTLIB_GGE_FHC_UTS_FetchResult_CALLBACK)(const S_RCTLIB_GGE_FHC_TX_UTS_T* uts, S_RCTLIB_GGE_FHC_TX_UTS_RESULT_T* uts_result);
typedef int (*RCTLIB_GGE_FHC_UTS_Iteration_Ex_CALLBACK)( S_RCTLIB_GGE_FHC_TX_UTS_BIG_T* uts);
typedef int (*RCTLIB_GGE_FHC_UTS_FetchResult_Ex_CALLBACK)(const S_RCTLIB_GGE_FHC_TX_UTS_BIG_T* uts, S_RCTLIB_GGE_FHC_TX_UTS_BIG_RESULT_T* uts_result);

typedef int (*RCTLIB_GGE_FBDAC_PreSettings_CALLBACK)(const S_RCTLIB_GGE_FBDAC_SETTINGS_T* pSettings);
typedef int (*RCTLIB_GGE_FBDAC_Iteration_CALLBACK)(double* d_power);
typedef int (*RCTLIB_GGE_TXIQ_PreSettings_CALLBACK)(const S_RCTLIB_GGE_TXIQ_SETTINGS_T* pSettings);
typedef int (*RCTLIB_GGE_TXIQ_ChangeBand_CALLBACK)(const S_RCTLIB_GGE_TXIQ_SETTINGS_T* pSettings);
typedef int (*RCTLIB_GGE_TXIQ_Iteration_CALLBACK)(const S_RCTLIB_GGE_TXIQ_SETTINGS_T* pSettings, S_RCTLIB_GGE_TXIQ_RESULT_T* pTxIqResult);
typedef int (*RCTLIB_GGE_TXSlopeSkew_PreSettings_CALLBACK)(const S_RCTLIB_GGE_TXSLOPESKEW_SETTINGS_T* pSettings);
typedef int (*RCTLIB_GGE_TXSlopeSkew_Iteration_CALLBACK)(double* d_mod_depth);
typedef int (*RCTLIB_GGE_TRXOffset_PreSettings_CALLBACK)(const S_RCTLIB_GGE_TRXOFFSET_SETTINGS_T* pSettings);
typedef int (*RCTLIB_GGE_TRXOffset_InitAFC_CALLBACK)(const S_RCTLIB_GGE_TRXOFFSET_SETTINGS_T* pSettings);
typedef int (*RCTLIB_GGE_TRXOffset_Iteration_CALLBACK)(double* frequency_err);
typedef int (*RCTLIB_GGE_NSFT_PreSettings_CALLBACK)(unsigned int measurement_count, unsigned int ber_count);
typedef int (*RCTLIB_GGE_NSFT_GMSKInit_CALLBACK)(const S_RCTLIB_GGE_NSFT_TESTCONFIG_T* nsft_config);
typedef int (*RCTLIB_GGE_NSFT_EPSKInit_CALLBACK)(const S_RCTLIB_GGE_NSFT_TESTCONFIG_T* nsft_config);
typedef int (*RCTLIB_GGE_NSFT_BERInit_CALLBACK)(const S_RCTLIB_GGE_NSFT_TESTCONFIG_T* nsft_config);
typedef int (*RCTLIB_GGE_NSFT_ChangePCL_CALLBACK)(int b_EPSK, unsigned int pcl);
typedef int (*RCTLIB_GGE_NSFT_ReadGMSKPerformance_CALLBACK)(S_RCTLIB_GGE_NSFT_GMSK_RESULT_T* gmsk_result);
typedef int (*RCTLIB_GGE_NSFT_InitiateBER_CALLBACK)();
typedef int (*RCTLIB_GGE_NSFT_FetchBER_CALLBACK)(S_RCTLIB_GGE_NSFT_BER_RESULT_T* ber_result);
typedef int (*RCTLIB_GGE_NSFT_ReadEPSKPerformance_CALLBACK)(S_RCTLIB_GGE_NSFT_EPSK_RESULT_T* epsk_result);
typedef int (*RCTLIB_GGE_GET_SpecificSettings_CALLBACK)(S_RCTLIB_GGE_SPECIFIC_SETTINGS_T* pSettings);

typedef struct
{
    RCTLIB_GGE_InstrumentInit_CALLBACK  InstrumentInit_CALLBACK;
    RCTLIB_GGE_Cableloss_Settings_CALLBACK  Cableloss_Settings_CALLBACK;
    RCTLIB_GGE_ConfigCellPower_CALLBACK  ConfigCellPower_CALLBACK;
    RCTLIB_GGE_ConfigDefaultSettings_CALLBACK  ConfigDefaultSettings_CALLBACK;
    RCTLIB_GGE_ConfigAnalyzerFrequencyOffset_CALLBACK  ConfigAnalyzerFrequencyOffset_CALLBACK;
    RCTLIB_GGE_CAPID_PreSettings_CALLBACK  CAPID_PreSettings_CALLBACK;
    RCTLIB_GGE_CAPID_Iteration_CALLBACK  CAPID_Iteration_CALLBACK;
    RCTLIB_GGE_AFC_PreSettings_CALLBACK  AFC_PreSettings_CALLBACK;
    RCTLIB_GGE_AGC_PreSettings_CALLBACK  AGC_PreSettings_CALLBACK;
    RCTLIB_GGE_AGC_ChangeCellBand_CALLBACK  AGC_ChangeCellBand_CALLBACK;
    RCTLIB_GGE_AGC_ChangeChannel_CALLBACK  AGC_ChangeChannel_CALLBACK;
    RCTLIB_GGE_APCDCOffset_PreSettings_CALLBACK  APCDCOffset_PreSettings_CALLBACK;
    RCTLIB_GGE_APCDCOffset_ChangeCellBand_CALLBACK  APCDCOffset_ChangeCellBand_CALLBACK;
    RCTLIB_GGE_APCDCOffset_Iteration_CALLBACK  APCDCOffset_Iteration_CALLBACK;
    RCTLIB_GGE_PedestalDCOffset_Iteration_CALLBACK  Pedestal_DCOffset_Iteration_CALLBACK;
    RCTLIB_GGE_EDGE_APCDCOffset_PreSettings_CALLBACK  EDGE_APCDCOffset_PreSettings_CALLBACK;
    RCTLIB_GGE_EDGE_APCDCOffset_ChangeCellBand_CALLBACK  EDGE_APCDCOffset_ChangeCellBand_CALLBACK;
    RCTLIB_GGE_EDGE_APCDCOffset_Iteration_CALLBACK  EDGE_APCDCOffset_Iteration_CALLBACK;
    RCTLIB_GGE_FHC_DTS_PreSettings_CALLBACK  FHC_DTS_PreSettings_CALLBACK;
    RCTLIB_GGE_FHC_DTS_Iteration_CALLBACK  FHC_DTS_Iteration_CALLBACK;
    RCTLIB_GGE_FHC_DTS_START_CALLBACK  FHC_DTS_START_CALLBACK;
    RCTLIB_GGE_FHC_DTS_STOP_CALLBACK  FHC_DTS_STOP_CALLBACK;
    RCTLIB_GGE_FHC_UTS_PreSettings_CALLBACK  FHC_UTS_PreSettings_CALLBACK;
    RCTLIB_GGE_FHC_UTS_Iteration_CALLBACK  FHC_UTS_Iteration_CALLBACK;
    RCTLIB_GGE_FHC_UTS_FetchResult_CALLBACK  FHC_UTS_FetchResult_CALLBACK;
    RCTLIB_GGE_FBDAC_PreSettings_CALLBACK  FBDAC_PreSettings_CALLBACK;
    RCTLIB_GGE_FBDAC_Iteration_CALLBACK  FBDAC_Iteration_CALLBACK;
    RCTLIB_GGE_TXIQ_PreSettings_CALLBACK  TXIQ_PreSettings_CALLBACK;
    RCTLIB_GGE_TXIQ_ChangeBand_CALLBACK  TXIQ_ChangeBand_CALLBACK;
    RCTLIB_GGE_TXIQ_Iteration_CALLBACK  TXIQ_Iteration_CALLBACK;
    RCTLIB_GGE_TXSlopeSkew_PreSettings_CALLBACK  TXSlopeSkew_PreSettings_CALLBACK;
    RCTLIB_GGE_TXSlopeSkew_Iteration_CALLBACK  TXSlopeSkew_Iteration_CALLBACK;
    RCTLIB_GGE_TRXOffset_PreSettings_CALLBACK  TRXOffset_PreSettings_CALLBACK;
    RCTLIB_GGE_TRXOffset_InitAFC_CALLBACK  TRXOffset_InitAFC_CALLBACK;
    RCTLIB_GGE_TRXOffset_Iteration_CALLBACK  TRXOffset_Iteration_CALLBACK;
    RCTLIB_GGE_NSFT_PreSettings_CALLBACK  NSFT_PreSettings_CALLBACK;
    RCTLIB_GGE_NSFT_GMSKInit_CALLBACK  NSFT_GMSKInit_CALLBACK;
    RCTLIB_GGE_NSFT_EPSKInit_CALLBACK  NSFT_EPSKInit_CALLBACK;
    RCTLIB_GGE_NSFT_BERInit_CALLBACK  NSFT_BERInit_CALLBACK;
    RCTLIB_GGE_NSFT_ChangePCL_CALLBACK  NSFT_ChangePCL_CALLBACK;
    RCTLIB_GGE_NSFT_ReadGMSKPerformance_CALLBACK  NSFT_ReadGMSKPerformance_CALLBACK;
    RCTLIB_GGE_NSFT_InitiateBER_CALLBACK  NSFT_InitiateBER_CALLBACK;
    RCTLIB_GGE_NSFT_FetchBER_CALLBACK  NSFT_FetchBER_CALLBACK;
    RCTLIB_GGE_NSFT_ReadEPSKPerformance_CALLBACK  NSFT_ReadEPSKPerformance_CALLBACK;
    RCTLIB_GGE_GET_SpecificSettings_CALLBACK  GET_SpecificSettings_CALLBACK;
    RCTLIB_GGE_FHC_UTS_Iteration_Ex_CALLBACK  FHC_UTS_Iteration_Ex_CALLBACK;
    RCTLIB_GGE_FHC_UTS_FetchResult_Ex_CALLBACK  FHC_UTS_FetchResult_Ex_CALLBACK;
    RCTLIB_GGE_EDGE_APC_SetExceptedPower_CALLBACK  EDGE_APC_SetExceptedPower_CALLBACK;
    RCTLIB_GGE_EDGE_APC_Iteration_CALLBACK  EDGE_APC_Iteration_CALLBACK;
    // please add in the last
} RCTLIB_GGE_CALLBACKS_CFG_T;
//=====================================================
//           WCDMA Callback defines
//=====================================================
typedef int (*RCTLIB_WCDMA_InstrumentInit_CALLBACK)(void);
typedef int (*RCTLIB_WCDMA_ConfigCellPower_CALLBACK)(double power);
typedef int (*RCTLIB_WCDMA_ConfigDefaultSettings_CALLBACK)(void);
typedef int (*RCTLIB_WCDMA_AFC_PreSetting_CALLBACK)(const S_RCTLIB_WCDMA_AFC_PRESETTINGS_T* pSettings, unsigned int size);
typedef int (*RCTLIB_WCDMA_AGC_PreSetting_CALLBACK)(const S_RCTLIB_WCDMA_AGC_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_WCDMA_AGC_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_WCDMA_AGC_ChangeChannel_CALLBACK)(unsigned int uarfcn);
typedef int (*RCTLIB_WCDMA_AGC_ChangeCellPower_CALLBACK)(double cellPower);
typedef int (*RCTLIB_WCDMA_APC_PreSetting_CALLBACK)(const S_RCTLIB_WCDMA_APC_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_WCDMA_APC_PreSetting_Ex_CALLBACK)(const S_RCTLIB_WCDMA_APC_PRESETTINGS_EX_T* pSettings);
typedef int (*RCTLIB_WCDMA_APC_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_WCDMA_APC_ChangeChannel_CALLBACK)(unsigned int uarfcn);
typedef int (*RCTLIB_WCDMA_APC_ChangeExpectedPower_CALLBACK)(int expectedPower);
typedef int (*RCTLIB_WCDMA_APC_Initiate_CALLBACK)(void);
typedef int (*RCTLIB_WCDMA_APC_FetchResult_CALLBACK)(double* outputPower);
typedef int (*RCTLIB_WCDMA_FHC_PreSetting_CALLBACK)(const S_RCTLIB_WCDMA_FHC_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_WCDMA_FHC_StartIteration_CALLBACK)(const S_RCTLIB_WCDMA_FHC_MEASUREMENT_PARAM_T* pSettings);
typedef int (*RCTLIB_WCDMA_FHC_FetchResult_CALLBACK)(const S_RCTLIB_WCDMA_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_WCDMA_FHC_MEASUREMENT_RESULT_T* pResult);
typedef int (*RCTLIB_WCDMA_NSFT_PreSetting_CALLBACK)(const S_RCTLIB_WCDMA_NSFT_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_WCDMA_NSFT_InitiateTestCase_CALLBACK)(const S_RCTLIB_WCDMA_NSFT_CONFIG_T* pSettings);
typedef int (*RCTLIB_WCDMA_NSFT_TPC_CALLBACK)(const S_RCTLIB_WCDMA_NSFT_TPC_REQUEST_T* tpc_request);
typedef int (*RCTLIB_WCDMA_NSFT_FetchTXPerformanceMaxPower_CALLBACK)(S_RCTLIB_WCDMA_NSFT_TX_PERF_MAX_POWER_RESULT_T* tx_perf_result);
typedef int (*RCTLIB_WCDMA_NSFT_FetchTXPerformanceMinPower_CALLBACK)(S_RCTLIB_WCDMA_NSFT_TX_PERF_MIN_POWER_RESULT_T* tx_perf_result);
typedef int (*RCTLIB_WCDMA_NSFT_InitiateILPCTestCase_CALLBACK)(unsigned char testSegment);
typedef int (*RCTLIB_WCDMA_NSFT_FetchILPCResult_CALLBACK)(S_RCTLIB_WCDMA_NSFT_ILPC_CONFIG_T* ilpcConfig, S_RCTLIB_WCDMA_NSFT_ILPC_RESULT_T* result);
typedef int (*RCTLIB_WCDMA_NSFT_ChangeCellPower_CALLBACK)(double d_cell_power);
typedef int (*RCTLIB_WCDMA_NSFT_InitiateBER_CALLBACK)();
typedef int (*RCTLIB_WCDMA_NSFT_ReadBER_CALLBACK)(S_RCTLIB_WCDMA_NSFT_BER_RESULT_T* result);
typedef int (*RCTLIB_WCDMA_NSFT_PRACH_PreSetting_CALLBACK)(const S_RCTLIB_WCDMA_NSFT_PRACH_PRESETTING_T* pSettings);
typedef int (*RCTLIB_WCDMA_NSFT_PRACH_CasePreSetting_CALLBACK)();
typedef int (*RCTLIB_WCDMA_NSFT_PRACH_InitiateTestCase_CALLBACK)(const S_RCTLIB_WCDMA_NSFT_PRACH_CONFIG_T* pSettings);
typedef int (*RCTLIB_WCDMA_NSFT_PRACH_FetchTestCase_CALLBACK)(S_RCTLIB_WCDMA_NSFT_PRACH_RESULT_T* result);
typedef int (*RCTLIB_WCDMA_HSDPA_NSFT_PreSetting_CALLBACK)(const S_RCTLIB_WCDMA_HSPA_NSFT_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_WCDMA_HSDPA_NSFT_InitiateTestCase_CALLBACK)(const S_RCTLIB_WCDMA_HSPA_NSFT_CONFIG_T* pConfig);
typedef int (*RCTLIB_WCDMA_HSDPA_NSFT_FetchResult_CALLBACK)(S_RCTLIB_WCDMA_HSPA_NSFT_RESULT_T* pResult);
typedef int (*RCTLIB_WCDMA_HSUPA_NSFT_PreSetting_CALLBACK)(const S_RCTLIB_WCDMA_HSPA_NSFT_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_WCDMA_HSUPA_NSFT_InitiateTestCase_CALLBACK)(const S_RCTLIB_WCDMA_HSPA_NSFT_CONFIG_T* pConfig);
typedef int (*RCTLIB_WCDMA_HSUPA_NSFT_FetchResult_CALLBACK)(S_RCTLIB_WCDMA_HSPA_NSFT_RESULT_T* pResult);
typedef int (*RCTLIB_WCDMA_GET_SpecificSettings_CALLBACK)(S_RCTLIB_WCDMA_SPECIFIC_SETTINGS_T* pSettings);

typedef struct
{
    RCTLIB_WCDMA_InstrumentInit_CALLBACK  InstrumentInit_CALLBACK;
    RCTLIB_WCDMA_ConfigCellPower_CALLBACK  ConfigCellPower_CALLBACK;
    RCTLIB_WCDMA_ConfigDefaultSettings_CALLBACK  ConfigDefaultSettings_CALLBACK;
    RCTLIB_WCDMA_AFC_PreSetting_CALLBACK  AFC_PreSetting_CALLBACK;
    RCTLIB_WCDMA_AGC_PreSetting_CALLBACK  AGC_PreSetting_CALLBACK;
    RCTLIB_WCDMA_AGC_ChangeCellBand_CALLBACK  AGC_ChangeCellBand_CALLBACK;
    RCTLIB_WCDMA_AGC_ChangeChannel_CALLBACK  AGC_ChangeChannel_CALLBACK;
    RCTLIB_WCDMA_AGC_ChangeCellPower_CALLBACK  AGC_ChangeCellPower_CALLBACK;
    RCTLIB_WCDMA_AGC_PreSetting_CALLBACK  AGC_RXD_PreSetting_CALLBACK;
    RCTLIB_WCDMA_AGC_ChangeCellBand_CALLBACK  AGC_RXD_ChangeCellBand_CALLBACK;
    RCTLIB_WCDMA_AGC_ChangeChannel_CALLBACK  AGC_RXD_ChangeChannel_CALLBACK;
    RCTLIB_WCDMA_AGC_ChangeCellPower_CALLBACK  AGC_RXD_ChangeCellPower_CALLBACK;
    RCTLIB_WCDMA_APC_PreSetting_CALLBACK  APC_PreSetting_CALLBACK;
    RCTLIB_WCDMA_APC_ChangeCellBand_CALLBACK  APC_ChangeCellBand_CALLBACK;
    RCTLIB_WCDMA_APC_ChangeChannel_CALLBACK  APC_ChangeChannel_CALLBACK;
    RCTLIB_WCDMA_APC_ChangeExpectedPower_CALLBACK  APC_ChangeExpectedPower_CALLBACK;
    RCTLIB_WCDMA_APC_Initiate_CALLBACK  APC_Initiate_CALLBACK;
    RCTLIB_WCDMA_APC_FetchResult_CALLBACK  APC_FetchResult_CALLBACK;
    RCTLIB_WCDMA_FHC_PreSetting_CALLBACK  FHC_PreSetting_CALLBACK;
    RCTLIB_WCDMA_FHC_StartIteration_CALLBACK  FHC_StartIteration_CALLBACK;
    RCTLIB_WCDMA_FHC_FetchResult_CALLBACK  FHC_FetchResult_CALLBACK;
    RCTLIB_WCDMA_NSFT_PreSetting_CALLBACK  NSFT_PreSetting_CALLBACK;
    RCTLIB_WCDMA_NSFT_InitiateTestCase_CALLBACK  NSFT_InitiateTestCase_CALLBACK;
    RCTLIB_WCDMA_NSFT_TPC_CALLBACK  NSFT_TPC_CALLBACK;
    RCTLIB_WCDMA_NSFT_FetchTXPerformanceMaxPower_CALLBACK  NSFT_FetchTXPerformanceMaxPower_CALLBACK;
    RCTLIB_WCDMA_NSFT_FetchTXPerformanceMinPower_CALLBACK  NSFT_FetchTXPerformanceMinPower_CALLBACK;
    RCTLIB_WCDMA_NSFT_InitiateILPCTestCase_CALLBACK  NSFT_InitiateILPCTestCase_CALLBACK;
    RCTLIB_WCDMA_NSFT_FetchILPCResult_CALLBACK  NSFT_FetchILPCResult_CALLBACK;
    RCTLIB_WCDMA_NSFT_ChangeCellPower_CALLBACK  NSFT_ChangeCellPower_CALLBACK;
    RCTLIB_WCDMA_NSFT_InitiateBER_CALLBACK  NSFT_InitiateBER_CALLBACK;
    RCTLIB_WCDMA_NSFT_ReadBER_CALLBACK  NSFT_ReadBER_CALLBACK;
    RCTLIB_WCDMA_NSFT_PRACH_PreSetting_CALLBACK  NSFT_PRACH_PreSetting_CALLBACK;
    RCTLIB_WCDMA_NSFT_PRACH_CasePreSetting_CALLBACK  NSFT_PRACH_CasePreSetting_CALLBACK;
    RCTLIB_WCDMA_NSFT_PRACH_InitiateTestCase_CALLBACK  NSFT_PRACH_InitiateTestCase_CALLBACK;
    RCTLIB_WCDMA_NSFT_PRACH_FetchTestCase_CALLBACK  NSFT_PRACH_FetchTestCase_CALLBACK;
    RCTLIB_WCDMA_HSDPA_NSFT_PreSetting_CALLBACK  HSDPA_NSFT_PreSetting_CALLBACK;
    RCTLIB_WCDMA_HSDPA_NSFT_InitiateTestCase_CALLBACK  HSDPA_NSFT_InitiateTestCase_CALLBACK;
    RCTLIB_WCDMA_HSDPA_NSFT_FetchResult_CALLBACK  HSDPA_NSFT_FetchResult_CALLBACK;
    RCTLIB_WCDMA_HSUPA_NSFT_PreSetting_CALLBACK  HSUPA_NSFT_PreSetting_CALLBACK;
    RCTLIB_WCDMA_HSUPA_NSFT_InitiateTestCase_CALLBACK  HSUPA_NSFT_InitiateTestCase_CALLBACK;
    RCTLIB_WCDMA_HSUPA_NSFT_FetchResult_CALLBACK  HSUPA_NSFT_FetchResult_CALLBACK;
    RCTLIB_WCDMA_GET_SpecificSettings_CALLBACK  GET_SpecificSettings_CALLBACK;
    RCTLIB_WCDMA_NSFT_ChangeCellPower_CALLBACK  NSFT_ChangePrachCellPower_CALLBACK;
    RCTLIB_WCDMA_APC_PreSetting_Ex_CALLBACK  APC_PreSetting_Ex_CALLBACK;
    // please add in the last
} RCTLIB_WCDMA_CALLBACKS_CFG_T;
//=====================================================
//           TDSCDMA Callback defines
//=====================================================
typedef int (*RCTLIB_TDSCDMA_InstrumentInit_CALLBACK)(void);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterCommonBeforeCal_CALLBACK)(void);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterBeforeAFC_CALLBACK)(const S_RCTLIB_TDSCDMA_AFC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
typedef int (*RCTLIB_TDSCDMA_MeasureAFC_CALLBACK)(double* p_dFreqOffset);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterBeforeAGC_CALLBACK)(const S_RCTLIB_TDSCDMA_AGC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
typedef int (*RCTLIB_TDSCDMA_AGC_ChangeCellPower_CALLBACK)(double cell_power);
typedef int (*RCTLIB_TDSCDMA_AGC_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_TDSCDMA_AGC_ChangeChannel_CALLBACK)(unsigned int uarfcn);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterBeforeAPC_CALLBACK)(const S_RCTLIB_TDSCDMA_APC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
typedef int (*RCTLIB_TDSCDMA_APC_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_TDSCDMA_APC_MeasurePower_CALLBACK)(S_RCTLIB_TDSCDMA_APC_MEASUREMENT_PARAM_T* param);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterBeforeFHC_CALLBACK)(const S_RCTLIB_TDSCDMA_FHC_TESTER_CONFIG_BEFORE_CAL_T* p_rConfig);
typedef int (*RCTLIB_TDSCDMA_FHC_StartIteration_CALLBACK)(const S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_PARAM_T* pSettings);
typedef int (*RCTLIB_TDSCDMA_FHC_FetchResult_CALLBACK)(const S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_TDSCDMA_FHC_MEASUREMENT_RESULT_T* pResult);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterCommonBeforeNSFT_CALLBACK)(S_RCTLIB_TD_NSFT_TESTER_COMMON_CONFIG_T* common_cfg);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterForNSFT_CALLBACK)(const S_RCTLIB_TD_NSFT_TESTER_CONFIG_T* cfg);
typedef int (*RCTLIB_TDSCDMA_MeasureTPCForNSFT_CALLBACK)(const S_RCTLIB_TD_NSFT_TPC_CONFIG_ENTRY_T* req, S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterForNSFTBer_CALLBACK)(const S_RCTLIB_TD_NSFT_BER_CONFIG_ENTRY_T* cfg);
typedef int (*RCTLIB_TDSCDMA_MeasureLBerForNSFT_CALLBACK)(S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterCommonBeforeFT_CALLBACK)(S_RCTLIB_TD_NSFT_TESTER_COMMON_CONFIG_T* common_cfg);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterForFT_CALLBACK)(const S_RCTLIB_TD_NSFT_TESTER_CONFIG_T* cfg);
typedef int (*RCTLIB_TDSCDMA_MeasureTPCForFT_CALLBACK)(const S_RCTLIB_TD_NSFT_TPC_CONFIG_ENTRY_T* req, S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);
typedef int (*RCTLIB_TDSCDMA_ConfigTesterForFTBer_CALLBACK)(const S_RCTLIB_TD_NSFT_BER_CONFIG_ENTRY_T* cfg);
typedef int (*RCTLIB_TDSCDMA_MeasureLBerForFT_CALLBACK)(S_RCTLIB_TDA_NSFT_MEASURE_RESULT_ENTRY_T* res);
typedef int (*RCTLIB_TDSCDMA_GET_SpecificSettings_CALLBACK)(S_RCTLIB_TDSCDMA_SPECIFIC_SETTINGS_T* pSettings);

typedef struct
{
    RCTLIB_TDSCDMA_InstrumentInit_CALLBACK  InstrumentInit_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterCommonBeforeCal_CALLBACK  ConfigTesterCommonBeforeCal_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterBeforeAFC_CALLBACK  ConfigTesterBeforeAFC_CALLBACK;
    RCTLIB_TDSCDMA_MeasureAFC_CALLBACK  MeasureAFC_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterBeforeAGC_CALLBACK  ConfigTesterBeforeAGC_CALLBACK;
    RCTLIB_TDSCDMA_AGC_ChangeCellPower_CALLBACK  AGC_ChangeCellPower_CALLBACK;
    RCTLIB_TDSCDMA_AGC_ChangeCellBand_CALLBACK  AGC_ChangeCellBand_CALLBACK;
    RCTLIB_TDSCDMA_AGC_ChangeChannel_CALLBACK  AGC_ChangeChannel_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterBeforeAPC_CALLBACK  ConfigTesterBeforeAPC_CALLBACK;
    RCTLIB_TDSCDMA_APC_ChangeCellBand_CALLBACK  APC_ChangeCellBand_CALLBACK;
    RCTLIB_TDSCDMA_APC_MeasurePower_CALLBACK  APC_MeasurePower_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterBeforeFHC_CALLBACK  ConfigTesterBeforeFHC_CALLBACK;
    RCTLIB_TDSCDMA_FHC_StartIteration_CALLBACK  FHC_StartIteration_CALLBACK;
    RCTLIB_TDSCDMA_FHC_FetchResult_CALLBACK  FHC_FetchResult_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterCommonBeforeNSFT_CALLBACK  ConfigTesterCommonBeforeNSFT_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterForNSFT_CALLBACK  ConfigTesterForNSFT_CALLBACK;
    RCTLIB_TDSCDMA_MeasureTPCForNSFT_CALLBACK  MeasureTPCForNSFT_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterForNSFTBer_CALLBACK  ConfigTesterForNSFTBer_CALLBACK;
    RCTLIB_TDSCDMA_MeasureLBerForNSFT_CALLBACK  MeasureLBerForNSFT_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterCommonBeforeFT_CALLBACK  ConfigTesterCommonBeforeFT_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterForFT_CALLBACK  ConfigTesterForFT_CALLBACK;
    RCTLIB_TDSCDMA_MeasureTPCForFT_CALLBACK  MeasureTPCForFT_CALLBACK;
    RCTLIB_TDSCDMA_ConfigTesterForFTBer_CALLBACK  ConfigTesterForFTBer_CALLBACK;
    RCTLIB_TDSCDMA_MeasureLBerForFT_CALLBACK  MeasureLBerForFT_CALLBACK;
    RCTLIB_TDSCDMA_GET_SpecificSettings_CALLBACK  GET_SpecificSettings_CALLBACK;
    // please add in the last
} RCTLIB_TDSCDMA_CALLBACKS_CFG_T;
#ifdef __META_C2K__
//=====================================================
//           C2K Callback defines
//=====================================================
typedef int (*RCTLIB_C2K_InstrumentInit_CALLBACK)(void);
typedef int (*RCTLIB_C2K_ConfigCellPower_CALLBACK)(double power);
typedef int (*RCTLIB_C2K_ConfigDefaultSettings_CALLBACK)(void);
typedef int (*RCTLIB_C2K_AFC_PreSetting_CALLBACK)(const S_RCTLIB_C2K_AFC_PRESETTINGS_T* pSettings, unsigned int size);
typedef int (*RCTLIB_C2K_AFC_FetchResult_CALLBACK)(double* freqError);
typedef int (*RCTLIB_C2K_AGC_PreSetting_CALLBACK)(const S_RCTLIB_C2K_AGC_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_C2K_AGC_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_C2K_AGC_ChangeChannel_CALLBACK)(unsigned int uarfcn);
typedef int (*RCTLIB_C2K_AGC_ChangeCellPower_CALLBACK)(double cellPower);
typedef int (*RCTLIB_C2K_APC_PreSetting_CALLBACK)(const S_RCTLIB_C2K_APC_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_C2K_APC_PreSetting_Ex_CALLBACK)(const S_RCTLIB_C2K_APC_PRESETTINGS_EX_T* pSettings);
typedef int (*RCTLIB_C2K_APC_ChangeCellBand_CALLBACK)(unsigned int band);
typedef int (*RCTLIB_C2K_APC_ChangeChannel_CALLBACK)(unsigned int uarfcn);
typedef int (*RCTLIB_C2K_APC_ChangeExpectedPower_CALLBACK)(int expectedPower);
typedef int (*RCTLIB_C2K_APC_Initiate_CALLBACK)(void);
typedef int (*RCTLIB_C2K_APC_FetchResult_CALLBACK)(double* outputPower);
typedef int (*RCTLIB_C2K_FHC_PreSetting_CALLBACK)(const S_RCTLIB_C2K_FHC_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_C2K_FHC_StartIteration_CALLBACK)(const S_RCTLIB_C2K_FHC_MEASUREMENT_PARAM_T* pSettings);
typedef int (*RCTLIB_C2K_FHC_FetchResult_CALLBACK)(const S_RCTLIB_C2K_FHC_MEASUREMENT_PARAM_T* pSettings, S_RCTLIB_C2K_FHC_MEASUREMENT_RESULT_T* pResult);
typedef int (*RCTLIB_C2K_NSFT_PreSetting_CALLBACK)(const S_RCTLIB_C2K_NSFT_PRESETTINGS_T* pSettings);
typedef int (*RCTLIB_C2K_NSFT_InitiateTestCase_CALLBACK)(const S_RCTLIB_C2K_NSFT_CONFIG_T* pSettings);
typedef int (*RCTLIB_C2K_NSFT_ChangeCellPower_CALLBACK)(double d_cell_power);
typedef int (*RCTLIB_C2K_NSFT_TPC_CALLBACK)(const S_RCTLIB_C2K_NSFT_TPC_REQUEST_T* tpc_request);
typedef int (*RCTLIB_C2K_NSFT_FetchTXPerformanceMaxPower_CALLBACK)(S_RCTLIB_C2K_NSFT_TX_PERF_MAX_POWER_RESULT_T* tx_perf_result);
typedef int (*RCTLIB_C2K_NSFT_FetchTXPerformanceMinPower_CALLBACK)(S_RCTLIB_C2K_NSFT_TX_PERF_MIN_POWER_RESULT_T* tx_perf_result);
typedef int (*RCTLIB_C2K_NSFT_InitiateFER_CALLBACK)();
typedef int (*RCTLIB_C2K_NSFT_ReadFER_CALLBACK)(S_RCTLIB_C2K_NSFT_FER_RESULT_T* result);
typedef int (*RCTLIB_C2K_NSFT_APP_PreSetting_CALLBACK)(const S_RCTLIB_C2K_NSFT_APP_PRESETTING_T* pSettings);
typedef int (*RCTLIB_C2K_NSFT_APP_CasePreSetting_CALLBACK)();
typedef int (*RCTLIB_C2K_NSFT_APP_InitiateTestCase_CALLBACK)(const S_RCTLIB_C2K_NSFT_APP_CONFIG_T* pSettings);
typedef int (*RCTLIB_C2K_NSFT_APP_ChangeCellPower_CALLBACK)(double d_cell_power);
typedef int (*RCTLIB_C2K_NSFT_APP_FetchTestCase_CALLBACK)(S_RCTLIB_C2K_NSFT_APP_RESULT_T* result);
typedef int (*RCTLIB_C2K_GET_SpecificSettings_CALLBACK)(S_RCTLIB_C2K_SPECIFIC_SETTINGS_T* pSettings);

typedef struct
{
    RCTLIB_C2K_InstrumentInit_CALLBACK  InstrumentInit_CALLBACK;
    RCTLIB_C2K_ConfigCellPower_CALLBACK  ConfigCellPower_CALLBACK;
    RCTLIB_C2K_ConfigDefaultSettings_CALLBACK  ConfigDefaultSettings_CALLBACK;
    RCTLIB_C2K_AFC_PreSetting_CALLBACK  AFC_PreSetting_CALLBACK;
    RCTLIB_C2K_AFC_FetchResult_CALLBACK  AFC_FetchResult_CALLBACK;
    RCTLIB_C2K_AGC_PreSetting_CALLBACK  AGC_PreSetting_CALLBACK;
    RCTLIB_C2K_AGC_ChangeCellBand_CALLBACK  AGC_ChangeCellBand_CALLBACK;
    RCTLIB_C2K_AGC_ChangeChannel_CALLBACK  AGC_ChangeChannel_CALLBACK;
    RCTLIB_C2K_AGC_ChangeCellPower_CALLBACK  AGC_ChangeCellPower_CALLBACK;
    RCTLIB_C2K_AGC_PreSetting_CALLBACK  AGC_RXD_PreSetting_CALLBACK;
    RCTLIB_C2K_AGC_ChangeCellBand_CALLBACK  AGC_RXD_ChangeCellBand_CALLBACK;
    RCTLIB_C2K_AGC_ChangeChannel_CALLBACK  AGC_RXD_ChangeChannel_CALLBACK;
    RCTLIB_C2K_AGC_ChangeCellPower_CALLBACK  AGC_RXD_ChangeCellPower_CALLBACK;
    RCTLIB_C2K_APC_PreSetting_CALLBACK  APC_PreSetting_CALLBACK;
    RCTLIB_C2K_APC_ChangeCellBand_CALLBACK  APC_ChangeCellBand_CALLBACK;
    RCTLIB_C2K_APC_ChangeChannel_CALLBACK  APC_ChangeChannel_CALLBACK;
    RCTLIB_C2K_APC_ChangeExpectedPower_CALLBACK  APC_ChangeExpectedPower_CALLBACK;
    RCTLIB_C2K_APC_Initiate_CALLBACK  APC_Initiate_CALLBACK;
    RCTLIB_C2K_APC_FetchResult_CALLBACK  APC_FetchResult_CALLBACK;
    RCTLIB_C2K_FHC_PreSetting_CALLBACK  FHC_PreSetting_CALLBACK;
    RCTLIB_C2K_FHC_StartIteration_CALLBACK  FHC_StartIteration_CALLBACK;
    RCTLIB_C2K_FHC_FetchResult_CALLBACK  FHC_FetchResult_CALLBACK;
    RCTLIB_C2K_NSFT_PreSetting_CALLBACK  NSFT_PreSetting_CALLBACK;
    RCTLIB_C2K_NSFT_InitiateTestCase_CALLBACK  NSFT_InitiateTestCase_CALLBACK;
    RCTLIB_C2K_NSFT_ChangeCellPower_CALLBACK  NSFT_ChangeCellPower_CALLBACK;
    RCTLIB_C2K_NSFT_TPC_CALLBACK  NSFT_TPC_CALLBACK;
    RCTLIB_C2K_NSFT_FetchTXPerformanceMaxPower_CALLBACK  NSFT_FetchTXPerformanceMaxPower_CALLBACK;
    RCTLIB_C2K_NSFT_FetchTXPerformanceMinPower_CALLBACK  NSFT_FetchTXPerformanceMinPower_CALLBACK;
    RCTLIB_C2K_NSFT_InitiateFER_CALLBACK  NSFT_InitiateFER_CALLBACK;
    RCTLIB_C2K_NSFT_ReadFER_CALLBACK  NSFT_ReadFER_CALLBACK;
    RCTLIB_C2K_NSFT_APP_PreSetting_CALLBACK  NSFT_APP_PreSetting_CALLBACK;
    RCTLIB_C2K_NSFT_APP_CasePreSetting_CALLBACK  NSFT_APP_CasePreSetting_CALLBACK;
    RCTLIB_C2K_NSFT_APP_InitiateTestCase_CALLBACK  NSFT_APP_InitiateTestCase_CALLBACK;
    RCTLIB_C2K_NSFT_APP_ChangeCellPower_CALLBACK  NSFT_APP_ChangeCellPower_CALLBACK;
    RCTLIB_C2K_NSFT_APP_FetchTestCase_CALLBACK  NSFT_APP_FetchTestCase_CALLBACK;
    RCTLIB_C2K_GET_SpecificSettings_CALLBACK  GET_SpecificSettings_CALLBACK;
    RCTLIB_C2K_APC_PreSetting_Ex_CALLBACK  APC_PreSetting_Ex_CALLBACK;
    // please add in the last
} RCTLIB_C2K_CALLBACKS_CFG_T;
#endif //#ifdef __META_C2K__
/**
 * Register callbacks interface
 **/
NON_REENTRANT_FUNC int __stdcall RCTLIB_SetCommonInstrumentInstance(RCTLIB_COMMON_CALLBACKS_CFG_T* instCallbacks);
NON_REENTRANT_FUNC int __stdcall RCTLIB_SetGGEInstrumentInstance(RCTLIB_GGE_CALLBACKS_CFG_T* instCallbacks);
NON_REENTRANT_FUNC int __stdcall RCTLIB_SetWCDMAInstrumentInstance(RCTLIB_WCDMA_CALLBACKS_CFG_T* instCallbacks);
NON_REENTRANT_FUNC int __stdcall RCTLIB_SetTDSCDMAInstrumentInstance(RCTLIB_TDSCDMA_CALLBACKS_CFG_T* instCallbacks);
#ifdef __META_C2K__
NON_REENTRANT_FUNC int __stdcall RCTLIB_SetC2KInstrumentInstance(RCTLIB_C2K_CALLBACKS_CFG_T* instCallbacks);
#endif //#ifdef __META_C2K__

// reentrant functions
int __stdcall RCTLIB_SetCommonInstrumentInstance_r(const int meta_handle, RCTLIB_COMMON_CALLBACKS_CFG_T* instCallbacks);
int __stdcall RCTLIB_SetGGEInstrumentInstance_r(const int meta_handle, RCTLIB_GGE_CALLBACKS_CFG_T* instCallbacks);
int __stdcall RCTLIB_SetWCDMAInstrumentInstance_r(const int meta_handle, RCTLIB_WCDMA_CALLBACKS_CFG_T* instCallbacks);
int __stdcall RCTLIB_SetTDSCDMAInstrumentInstance_r(const int meta_handle, RCTLIB_TDSCDMA_CALLBACKS_CFG_T* instCallbacks);
#ifdef __META_C2K__
int __stdcall RCTLIB_SetC2KInstrumentInstance_r(const int meta_handle, RCTLIB_C2K_CALLBACKS_CFG_T* instCallbacks);
#endif //#ifdef __META_C2K__
#ifdef __cplusplus
}
#endif
#endif
