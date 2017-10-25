/*****************************************************************************
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of MediaTek Inc. (C) 2001
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * Filename:
 * ---------
 *   SP_META_Wrapper.h
 *
 * Project:
 * --------
 *   Maui META APP
 *
 * Description:
 * ------------
 *   SP META DLL Wrapper APIs
 *
 * Author:
 * -------
 *  YH Sung (mtk02607)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 *
 * 04 09 2013 eason.lai
 * [STP100006899]  New feature of acquiring C0 & C1 from temperature-frequency values for CO-TSX
 * CoTSX file revisions
 *
 * 11 14 2012 bulin.huang
 * [STP100006026]  [META] Dual Talk META API
 * .
 *
 * 09 07 2012 bulin.huang
 * [STP100006128]  [META APP] Support encrypted partition access
 * .
 *
 * 06 04 2012 bulin.huang
 * [STP100005793]  [META APP][Backup Partition] META tool support to trigger backup partition
 * .
 *
 * 05 02 2012 bulin.huang
 * [STP100005695]  [META APP] Shut down target when META connects to smart phone
 * .
 *
 * 11 16 2011 yh.sung
 * [STP100005214]  [META_DLL] SP META API Wrapper library
 * Import the SP META DLL from 1144.2 and add the SP META DLL wrapper DLL into project space
 *
 * 11 11 2011 yh.sung
 * [STP100005214]  [META_DLL] SP META API Wrapper library
 * Add a DLL to implement the SP META DLL API wrapper to isolate the SP META header file
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef __SP_META_WRAPPER_H__
#define __SP_META_WRAPPER_H__
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

typedef enum
{
    SP_META_WRAPPER_SUCCESS = 0,
    SP_META_WRAPPER_TIMEOUT = 1,
    SP_META_WRAPPER_FAILED  = 2,
    SP_META_WRAPPER_EXT_MD_DOWNLOAD_FAILED = 3,
    SP_META_WRAPPER_INVALID_ARGUMENT = 4,
    SP_META_WRAPPER_INVALID_FILE = 5,
    SP_META_WRAPPER_CANCEL = 6,
    SP_META_WRAPPER_SP_META_FUNC_NOT_IMPLEMENT_YET = 7,
    SP_META_WRAPPER_SP_META_FUNC_LOAD_FAILED = 8,
    SP_META_WRAPPER_VERIFY_PASSWORD_FAILED = 9,
    SP_META_WRAPPER_LAST_ERROR
} SP_META_WRAPPER_RESULT;

SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MapToSPMetaWrapperResult (int spMetaResult);
const char* __stdcall SP_META_Wrapper_GetErrorString(SP_META_WRAPPER_RESULT ErrCode);
const char* __stdcall SP_META_Wrapper_GetLastExecuteSPMetaApiName();
const char* __stdcall SP_META_Wrapper_GetLastExecuteSPMetaApiName_r(const int meta_handle);

/**
 * Trace on /off API for SP META Wrapper
 */
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_TraceOn(void);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_TraceClear(void);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_TraceOff(void);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_TraceOn_With_FilePath(const char* filename);
/**
 * init Wrapper API for SP META DLL
 */
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_Init(void);
/**
 * Trace on /off Wrapper API for SP META DLL
 */
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_DebugOn(void);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_DebugOn_ex(const int meta_handle);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_DebugOff(void);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_DebugClear(void);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_DebugOnThePath(const char* path);
/**
 * non-reentrant version of SP_META_Wrapper_ConnectTargetByUart_r
 */
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_ConnectTargetByUart(unsigned int ms_timeout, int com_port);
/**
 * \brief connect AP with 921600 baud rate
 * \param metaHandle meta handle
 * \param connectionSetting connection setting to the UART interface
 */
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_ConnectTargetByUart_r(const int meta_handle, unsigned int ms_timeout, int com_port);
typedef enum _SP_META_WRAPPER_UART_BAUDRATE_E
{
    SP_META_WRAPPER_BAUDRATE_END = -1,
    SP_META_WRAPPER_BAUDRATE_57600 = 0,
    SP_META_WRAPPER_BAUDRATE_115200 = 1,
    SP_META_WRAPPER_BAUDRATE_230400 = 2,
    SP_META_WRAPPER_BAUDRATE_460800 = 3,
    SP_META_WRAPPER_BAUDRATE_921600 = 4,
    SP_META_WRAPPER_BAUDRATE_1500000 = 5,
    SP_META_WRAPPER_BAUDRATE_NUM = SP_META_WRAPPER_BAUDRATE_1500000+1
} SP_META_WRAPPER_UART_BAUDRATE_E;
typedef struct _SP_META_WRAPPER_CONN_UART_SETTING_T
{
    int comPort;
    SP_META_WRAPPER_UART_BAUDRATE_E baudrateSetting[SP_META_WRAPPER_BAUDRATE_NUM];
} SP_META_WRAPPER_CONN_UART_SETTING_T;
/**
 * non-reentrant version of SP_META_Wrapper_ConnectTargetByUartEx_r
 */
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_ConnectTargetByUartEx(unsigned int msTimeout, const SP_META_WRAPPER_CONN_UART_SETTING_T* connectionSetting, SP_META_WRAPPER_UART_BAUDRATE_E* currentBaudRate);
/**
 * \brief connect AP with configurable connection setting
 * \param metaHandle meta handle
 * \param connectionSetting connection setting to the UART interface
 */
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_ConnectTargetByUartEx_r(const int metaHandle, unsigned int msTimeout, const SP_META_WRAPPER_CONN_UART_SETTING_T* connectionSetting, SP_META_WRAPPER_UART_BAUDRATE_E* currentBaudRate);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_ConnectTargetByUsb(unsigned int ms_timeout, int com_port);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_ConnectTargetByUsb_r(const int meta_handle, unsigned int ms_timeout, int com_port);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_DisconnectInMetaMode(void);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_DisconnectInMetaMode_r(const int meta_handle);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_DisconnectWithTarget(void);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_DisconnectWithTarget_r(const int meta_handle);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_TriggerBackupByUart(unsigned int ms_timeout, int com_port, bool bShutDown);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_TriggerBackupByUart_r(const int meta_handle, unsigned int ms_timeout, int com_port, bool bShutDown);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_TriggerBackupByUsb(unsigned int ms_timeout, int com_port, bool bShutDown);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_TriggerBackupByUsb_r(const int meta_handle, unsigned int ms_timeout, int com_port, bool bShutDown);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_ShutdownTargetByUart(const int meta_handle, unsigned int ms_timeout, int com_port);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_ShutdownTargetByUart_r(const int meta_handle, unsigned int ms_timeout, int com_port);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_ShutdownTargetByUsb(const int meta_handle, unsigned int ms_timeout, int com_port);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_ShutdownTargetByUsb_r(const int meta_handle, unsigned int ms_timeout, int com_port);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_QueryEncryptedSupport(unsigned int ms_timeout, unsigned char* support);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_QueryEncryptedSupport_r(const int meta_handle, unsigned int ms_timeout, unsigned char* support);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_VerifyEncryptedPwd(const unsigned char* pwd, unsigned int ms_timeout, const int  length, unsigned char* result);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_VerifyEncryptedPwd_r(const int meta_handle, unsigned int ms_timeout, const unsigned char* pwd, const int  length, unsigned char* result);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_GetModemInfo(unsigned int ms_timeout, unsigned int* number_of_md, unsigned int* active_md_idx);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_GetModemInfo_r(const int meta_handle, unsigned int ms_timeout, unsigned int* number_of_md, unsigned int* active_md_idx);
typedef struct
{
    unsigned int md_service; /*!< logging_protocol type: 1: TST;2: DHL*/
    unsigned int ch_type; /*!< channel type: 0/1: Native Channel; 2: Tunneling without checksum; 3: Tunneling with checksum */
    unsigned char reserved;
} SP_MODEM_CAPABILITY;
typedef struct
{
    SP_MODEM_CAPABILITY modem_cap[8];
} SP_MODEM_CAPABILITY_LIST_CNF;
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_QueryModemCapability(unsigned int ms_timeout, SP_MODEM_CAPABILITY_LIST_CNF* md_cap_list);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_QueryModemCapability_r(const int meta_handle, unsigned int ms_timeout, SP_MODEM_CAPABILITY_LIST_CNF* md_cap_list);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_SetModemType(unsigned int ms_timeout, unsigned int active_md_idx, unsigned int active_md_type);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_SetModemType_r(const int meta_handle, unsigned int ms_timeout, unsigned int active_md_idx, unsigned int active_md_type);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_GetCurrentModemType(unsigned int ms_timeout, unsigned int current_md_idx, unsigned int* current_md_type);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_GetCurrentModemType_r(const int meta_handle, unsigned int ms_timeout, unsigned int current_md_idx, unsigned int* current_md_type);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_QueryMdImgType(unsigned int ms_timeout, unsigned int current_md_idx, unsigned int* current_mdimg_type_idx);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_QueryMdImgType_r(const int meta_handle, unsigned int ms_timeout, unsigned int current_md_idx, unsigned int* current_mdimg_type_idx);
//Modify naming
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MODEM_Set_ModemType(unsigned int ms_timeout, unsigned int active_md_idx, unsigned int active_md_type);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MODEM_Set_ModemType_r(const int meta_handle, unsigned int ms_timeout, unsigned int active_md_idx, unsigned int active_md_type);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MODEM_Get_CurrentModemType(unsigned int ms_timeout, unsigned int current_md_idx, unsigned int* current_md_type);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MODEM_Get_CurrentModemType_r(const int meta_handle, unsigned int ms_timeout, unsigned int current_md_idx, unsigned int* current_md_type);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MODEM_Query_MDIMGType(unsigned int ms_timeout, unsigned int current_md_idx, unsigned int* current_mdimg_type_idx);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MODEM_Query_MDIMGType_r(const int meta_handle, unsigned int ms_timeout, unsigned int current_md_idx, unsigned int* current_mdimg_type_idx);
typedef struct 
{
    unsigned char reserved; 
} SP_META_WRAPPER_MODEM_QUERY_DOWNLOAD_STATUS_REQ;

typedef struct 
{
    unsigned int percentage;
    unsigned int status_code;
} SP_META_WRAPPER_MODEM_QUERY_DOWNLOAD_STATUS_CNF;
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MODEM_Query_Download_Status(unsigned int ms_timeout, SP_META_WRAPPER_MODEM_QUERY_DOWNLOAD_STATUS_REQ* pReq, SP_META_WRAPPER_MODEM_QUERY_DOWNLOAD_STATUS_CNF* pCnf);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MODEM_Query_Download_Status_r(const int meta_handle, unsigned int ms_timeout, SP_META_WRAPPER_MODEM_QUERY_DOWNLOAD_STATUS_REQ* pReq, SP_META_WRAPPER_MODEM_QUERY_DOWNLOAD_STATUS_CNF* pCnf);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MODEM_Query_ExternalModemDownloadSupport(unsigned int ms_timeout);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_MODEM_Query_ExternalModemDownloadSupport_r(const int meta_handle, unsigned int ms_timeout);
/********************************************
 *      NVRAM access SP META DLL WRAPPER    *
 ********************************************/

// Read from NVRAM
typedef struct
{
    const char*          LID;       // The name of logical data item ID
    unsigned short      RID;        // Record ID (the first record is 1)
} SP_FT_NVRAM_READ_REQ;

typedef struct
{
    unsigned short      LID;        // Logical data item ID of a EF
    unsigned short      RID;        // Record ID (the first record is 1)
    unsigned char       status;     // 0: read ok; others: read failed.

    unsigned int        len;        // [IN] Length of Buffer, [OUT] Length of read data
    // The "len" field indicates the size of "buf" you
    // allocated. When the data is read back, "len" will
    // be replaced with the actual size of the data.

    unsigned char*       buf;       // Buffer that will contains the content of record
    unsigned char       read_status;
} SP_FT_NVRAM_READ_CNF;

//Write to NVRAM
typedef struct
{
    const char*          LID;       // The name of logical data item ID
    unsigned short      RID;        // Record ID (the first record is 1)
    unsigned int        len;        // Length of write data
    unsigned char*       buf;       // Buffer that contains the content of record
} SP_FT_NVRAM_WRITE_REQ;

typedef struct
{
    unsigned short      LID;        // Logical data item ID of a EF
    unsigned short      RID;        // Record ID (the first record is 1)
    unsigned char       write_status;
    unsigned char       status;     // 0: write ok; others: write failed.
} SP_FT_NVRAM_WRITE_CNF;

// NVRAM database initial function
SP_META_WRAPPER_RESULT  __stdcall SP_META_Wrapper_NVRAM_Init(const char* PathName, unsigned long* p_nvram_CatcherTranAddr);
SP_META_WRAPPER_RESULT  __stdcall SP_META_Wrapper_NVRAM_Init_r(const int meta_handle, const char* PathName, unsigned long* p_nvram_CatcherTranAddr);

// NVRAM read/write operations
SP_META_WRAPPER_RESULT  __stdcall SP_META_Wrapper_NVRAM_Read(unsigned int ms_timeout, const SP_FT_NVRAM_READ_REQ* req, SP_FT_NVRAM_READ_CNF* cnf);
SP_META_WRAPPER_RESULT  __stdcall SP_META_Wrapper_NVRAM_Read_r(const int meta_handle, unsigned int ms_timeout, const SP_FT_NVRAM_READ_REQ* req, SP_FT_NVRAM_READ_CNF* cnf);
SP_META_WRAPPER_RESULT  __stdcall SP_META_Wrapper_NVRAM_Write(unsigned int ms_timeout, const SP_FT_NVRAM_WRITE_REQ* req);
SP_META_WRAPPER_RESULT  __stdcall SP_META_Wrapper_NVRAM_Write_r(const int meta_handle, unsigned int ms_timeout, const SP_FT_NVRAM_WRITE_REQ* req);

// NVRAM query operations
SP_META_WRAPPER_RESULT  __stdcall SP_META_Wrapper_NVRAM_GetRecLen(const char* LID, int* len);
SP_META_WRAPPER_RESULT  __stdcall SP_META_Wrapper_NVRAM_SetRecFieldValue(const char* LID, const char* field, char* buf, const int buf_len, void* value, const int value_len);
SP_META_WRAPPER_RESULT  __stdcall SP_META_Wrapper_NVRAM_GetRecFieldValue(const char* LID, const char* field, const char* buf, const int buf_len, void* value, const int value_len);
SP_META_WRAPPER_RESULT  __stdcall SP_META_Wrapper_NVRAM_QueryIsLIDExist(const char* LID);

/********************************************
 *      Platform related flow API
 ********************************************/
#define SP_META_WRAPPER_STOP_CHECK_EXTERNAL_MODEM_DOWNLOAD_STATUS 0x5566
typedef void (__stdcall *SP_META_Wrapper_ExternalModemDownloadStatusCallback_T)(unsigned int progress, unsigned int statusCode, void* usrData);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_Flow_CheckExternalModemDownloadStatus(unsigned int ms_timeout, const int* pStop, int* pDownloadStatus, SP_META_Wrapper_ExternalModemDownloadStatusCallback_T reportCallback, void* usrData);
SP_META_WRAPPER_RESULT __stdcall SP_META_Wrapper_Flow_CheckExternalModemDownloadStatus_r(const int meta_handle, unsigned int ms_timeout, const int* pStop, int* pDownloadProgress, int* pDownloadStatus, SP_META_Wrapper_ExternalModemDownloadStatusCallback_T reportCallback, void* usrData);
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif // #ifndef __SP_META_WRAPPER_H__
