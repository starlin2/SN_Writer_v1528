#ifndef _SN_BASE_H_
#define _SN_BASE_H_

#include "Common.h"
#include "Mdebug.h"
#include "xboot_debug.h"
#include "SLA.h"

#include "Meta.h"
#include "Brom.h"

#include "Sp_Brom.h"
namespace SPMETA_DLL 
{
    #include "spmeta.h"
};


//write temperature to nvram
typedef struct
{
    float resistor[512];
    float temp_initial;
    float current_sensing_resistor;
    unsigned short reso_freq_center;
    unsigned short reso_freq_bw;
    unsigned short reso_freq_gain;
    unsigned short prefer_band_upper;
    unsigned short prefer_band_lower;
    unsigned short temp_limit_low;
    unsigned short temp_limit_high;
    unsigned short temp_control_time_slots;
    unsigned short monitor_timer;
}AUDIO_SPREAKER_MONITOR_PARAM_STRUCT;

class SNBase
{
public:
    SNBase();
    virtual ~SNBase();

protected:
    HANDLE        m_hThread;
    unsigned int  m_iThreadID;
    int           *m_pMetaStopFlag;
    int           m_hMauiMetaHandle;
    int           m_hSPMetaHandle;
    short         m_sNVRAM_OPID;

    bool   m_bWriteNvram;
    bool   m_bWriteModemNvram;
    bool   m_bTargetInMetaMode;
    bool   m_bStopBeforeUSBInsert;

    HANDLE  m_hReadFromNVRAMEvent;
    HANDLE  m_hWriteToNVRAMEvent;

    IMEISV_struct_T m_sIMEISV[MAX_IMEI_NUMS];
    char    m_strBackupIMEI[IMEI_ARRAY_LEN];
    bool    m_bNeedBackupIMEI;
    ScanData_struct  m_sScanData;

protected:
    static UINT ThreadStaticEntryPoint(LPVOID pThis);
    virtual void SetupMetaModeParameters() = 0;
    virtual void ThreadMainEntryPoint() = 0;
    virtual META_RESULT MetaHandle_Init() = 0;
    virtual void MetaHandle_DeInit() = 0;
    virtual META_RESULT WriteNvramLoop() = 0;
    

    virtual META_RESULT LoadModemDatabase() = 0;
    virtual void UpdateProgress(double dPercent);
    virtual void SetProgress();

    virtual META_RESULT ConductBarcodeData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize);
    virtual META_RESULT ConductIMEIData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize);
    virtual META_RESULT ConductBTAddrData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize);
    virtual META_RESULT ConductWifiAddrData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize); 
    virtual META_RESULT ConductEthernetMacAddrData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize); 
    virtual META_RESULT ConductAudioTemperatureData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize);
    
    virtual META_RESULT Decompose_IMEI(char *pOutData, unsigned short RID_para,  char *pInDatabuf, int bufSize);
    virtual META_RESULT Compose_IMEI(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize, bool bChecksum);
    
    virtual META_RESULT REQ_ReadFromModemNVRAM(FT_NVRAM_READ_REQ *psNVRAM_ReadReq, FT_NVRAM_READ_CNF *psNVRAM_ReadCnf);
    virtual META_RESULT REQ_WriteToModemNVRAM(FT_NVRAM_WRITE_REQ *psNVRAM_WriteReq, FT_NVRAM_WRITE_CNF *psNVRAM_WriteCnf);
    virtual void UpdateUICountResult(WriteNvram_Status_e eWriteStatus);
    virtual void UpdateMsgInfo(char *strMsg);
    virtual CheckCalFlag_Status_e CheckCalibrationStatus(const char* strBarcode);
    virtual CheckFinalTestFlag_Status_e CheckFinalTestStatus(const char* strBarcode);
    virtual bool CheckCalFinalTestStatus(const char* strBarcode);
    virtual void PopupMsgBox(const char* strMsg, const char* strTilte, UINT uType = MB_OK); 
    virtual bool NeedScanData();
	


public:
    void SNThread_Init();
    void SNThread_Start();
    void SNThread_Stop();
    void GetScanData(ScanData_struct &pScanData);
    void UpdateMainDlgUI(bool bEnable, WriteNvram_Status_e eWriteStatus);
	void EnableStartBTN(bool bEnable = true);
protected:
    CProgressCtrl *m_Process;
    UINT  m_iProcessRange;
    char  m_strMsg[256];
	bool  m_bBackupNvramSuccess;
    
};




typedef META_RESULT (SNBase::*pConductDataFunc)(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize);

#endif