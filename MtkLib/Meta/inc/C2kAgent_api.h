#ifndef _C2KAGENT_API_H_
#define _C2KAGENT_API_H_

#include "meta.h"
#include "C2kAgent_api_datatype.h"
#ifdef __cplusplus
extern "C" {
#endif

/*************************** Functions Declaration ****************************/
int __stdcall META_C2K_GetDLLVer(unsigned int* major_ver, unsigned int* minor_ver, unsigned int* build_num, unsigned int* patch_num);
const char* __stdcall META_C2K_GetErrorString(const int metaHandle);
META_RESULT __stdcall META_C2K_Init(const int metaHandle, C2K_LIBCONFIGPARMS* libConfig, PHONEATTRIBUTE_PARMS* phoneAttr);
META_RESULT __stdcall META_C2K_DeInit(const int metaHandle);
META_RESULT __stdcall META_C2K_ConnectWithTarget(unsigned int msTimeout, C2K_CONNECT_PARAMS* connectReq);
META_RESULT __stdcall META_C2K_ConnectWithTarget_r(const int metaHandle, unsigned int msTimeout, C2K_CONNECT_PARAMS* connectReq);
META_RESULT __stdcall META_C2K_DisconnectWithTarget(void);
META_RESULT __stdcall META_C2K_DisconnectWithTarget_r(const int metaHandle);
META_RESULT __stdcall META_C2K_LoadMessage(char* PathName);
META_RESULT __stdcall META_C2K_LoadMessage_r(const int metaHandle, char* PathName);
META_RESULT __stdcall META_C2K_LoadLogFilter(char* PathName);
META_RESULT __stdcall META_C2K_LoadLogFilter_r(const int metaHandle, char* PathName);

META_RESULT __stdcall META_C2K_SetSpi(unsigned int msTimeout, C2K_SPI_TYPE spiType, unsigned int spiAddress, unsigned int spiData);
META_RESULT __stdcall META_C2K_SetSpi_r(const int metaHandle, unsigned int msTimeout, C2K_SPI_TYPE spiType, unsigned int spiAddress, unsigned int spiData);
META_RESULT __stdcall META_C2K_GetSpi(unsigned int msTimeout, C2K_SPI_TYPE spiType, unsigned int spiAddress, unsigned int* spiData);
META_RESULT __stdcall META_C2K_GetSpi_r(const int metaHandle, unsigned int msTimeout, C2K_SPI_TYPE spiType, unsigned int spiAddress, unsigned int* spiData);
META_RESULT __stdcall META_C2K_LogIq(unsigned int msTimeout, LOG_IQ_REQ* req);
META_RESULT __stdcall META_C2K_LogIq_r(const int metaHandle, unsigned int msTimeout, LOG_IQ_REQ* req);
META_RESULT __stdcall META_C2K_GetTemperatureAdc(unsigned int msTimeout, unsigned short* adcValue);
META_RESULT __stdcall META_C2K_GetTemperatureAdc_r(const int metaHandle, unsigned int msTimeout, unsigned short* adcValue);
META_RESULT __stdcall META_C2K_TransmitterCtrl(unsigned int msTimeout, bool enable, C2K_RF_MODE rfMode, unsigned int band, unsigned short channel);
META_RESULT __stdcall META_C2K_TransmitterCtrl_r(const int metaHandle, unsigned int msTimeout, bool enable, C2K_RF_MODE rfMode, unsigned int band, unsigned short channel);
META_RESULT __stdcall META_C2K_ReceiverCtrl(unsigned int msTimeout, bool enable, C2K_RF_MODE rfMode, unsigned int rxPathBitmap, unsigned int band, unsigned short channel);
META_RESULT __stdcall META_C2K_ReceiverCtrl_r(const int metaHandle, unsigned int msTimeout, bool enable, C2K_RF_MODE rfMode, unsigned int rxPathBitmap, unsigned int band, unsigned short channel);
META_RESULT __stdcall META_C2K_AfcConfig(unsigned int msTimeout, C2K_RF_MODE rfMode, unsigned int ctrlMode, bool capIdValid, unsigned short capId, bool dacValid, unsigned short initDac);
META_RESULT __stdcall META_C2K_AfcConfig_r(const int metaHandle, unsigned int msTimeout, C2K_RF_MODE rfMode, unsigned int ctrlMode, bool capIdValid, unsigned short capId, bool dacValid, unsigned short initDac);
META_RESULT __stdcall META_C2K_AfcGetParam(unsigned int msTimeout, C2K_RF_MODE rfMode, unsigned short* capId, unsigned short* initDac);
META_RESULT __stdcall META_C2K_AfcGetParam_r(const int metaHandle, unsigned int msTimeout, C2K_RF_MODE rfMode, unsigned short* capId, unsigned short* initDac);
META_RESULT __stdcall META_C2K_TxTone(unsigned int msTimeout, bool enable, unsigned int* frequencyHz);
META_RESULT __stdcall META_C2K_TxTone_r(const int metaHandle, unsigned int msTimeout, bool enable, unsigned int* frequencyHz);
META_RESULT __stdcall META_C2K_TxCdma(unsigned int msTimeout, bool enable, C2K_RF_MODE rfMode);
META_RESULT __stdcall META_C2K_TxCdma_r(const int metaHandle, unsigned int  msTimeout, bool enable, C2K_RF_MODE rfMode);
META_RESULT __stdcall META_C2K_TxAgcConfig(unsigned int msTimeout, TXAGC_CONFIG_REQ* req);
META_RESULT __stdcall META_C2K_TxAgcConfig_r(const int metaHandle, unsigned int msTimeout, TXAGC_CONFIG_REQ* req);
META_RESULT __stdcall META_C2K_ReadCurrentTxPower(unsigned int msTimeout, short* pdPower);
META_RESULT __stdcall META_C2K_ReadCurrentTxPower_r(const int metaHandle, unsigned int msTimeout, double* pdPower);
META_RESULT __stdcall META_C2K_RxAgcSetGain(unsigned int msTimeout, unsigned int ctrlMode, C2K_RF_MODE rfMode, unsigned int rxPathBitmap, unsigned int lnaMode, double cellPower);
META_RESULT __stdcall META_C2K_RxAgcSetGain_r(const int metaHandle, unsigned int msTimeout, unsigned int ctrlMode, C2K_RF_MODE rfMode, unsigned int rxPathBitmap, unsigned int lnaMode, double cellPower);
META_RESULT __stdcall META_C2K_FhcStart(unsigned int msTimeout, C2K_FHC_REQ* fhcReq, C2K_FHC_CNF* fhcCnf);
META_RESULT __stdcall META_C2K_FhcStart_r(const int metaHandle, unsigned int msTimeout, C2K_FHC_REQ* fhcReq, C2K_FHC_CNF* fhcCnf);
META_RESULT __stdcall META_C2K_EnableRxTxSpy(unsigned int msTimeout, bool enable);
META_RESULT __stdcall META_C2K_EnableRxTxSpy_r(const int metaHandle, unsigned int msTimeout, bool enable);
META_RESULT __stdcall META_C2K_Rssi(unsigned int msTimeout, int rssiCount, C2K_RSSI_CNF* rssiCnf);
META_RESULT __stdcall META_C2K_Rssi_r(const int metaHandle, unsigned int msTimeout, int rssiCount, C2K_RSSI_CNF* rssiCnf);
META_RESULT __stdcall META_C2K_QueryTargetCapability(unsigned int msTimeout, C2K_MS_CAPABILITY* msCapability);
META_RESULT __stdcall META_C2K_QueryTargetCapability_r(const int metaHandle, unsigned int msTimeout, C2K_MS_CAPABILITY* msCapability);
META_RESULT __stdcall META_C2K_PsPower(unsigned int msTimeout, bool enable);
META_RESULT __stdcall META_C2K_PsPower_r(const int metaHandle, unsigned int msTimeout, bool enable);
META_RESULT __stdcall META_C2K_MPATestRelease(unsigned int msTimeout);
META_RESULT __stdcall META_C2K_MPATestRelease_r(const int metaHandle, unsigned int msTimeout);
META_RESULT __stdcall META_C2K_NsftSetTestMode(unsigned int msTimeout);
META_RESULT __stdcall META_C2K_NsftSetTestMode_r(const int metaHandle, unsigned int msTimeout);
META_RESULT __stdcall META_C2K_NsftPowerUp(unsigned int msTimeout, unsigned int band, unsigned short channel, unsigned int walshCode, unsigned int rc, unsigned int numFrames, bool afcEnable);
META_RESULT __stdcall META_C2K_NsftPowerUp_r(const int metaHandle, unsigned int msTimeout, unsigned int band, unsigned short channel, unsigned int walshCode, unsigned int rc, unsigned int numFrames, bool afcEnable);
META_RESULT __stdcall META_C2K_NsftTxTrafficChannel(unsigned int msTimeout, unsigned int rc, unsigned int powerCtrlMode, double txPower);
META_RESULT __stdcall META_C2K_NsftTxTrafficChannel_r(const int metaHandle, unsigned int msTimeout, unsigned int rc, unsigned int powerCtrlMode, double txPower);
META_RESULT __stdcall META_C2K_NsftGetFer(unsigned int msTimeout, unsigned int* badFrames, unsigned int* totalFrames);
META_RESULT __stdcall META_C2K_NsftGetFer_r(const int metaHandle, unsigned int msTimeout, unsigned int* badFrames, unsigned int* totalFrames);
META_RESULT __stdcall META_C2K_NsftExitTestMode(unsigned int msTimeout);
META_RESULT __stdcall META_C2K_NsftExitTestMode_r(const int metaHandle, unsigned int msTimeout);
META_RESULT __stdcall META_C2K_NsftListModeStart(unsigned int msTimeout, NSTLISTMODE_PARMS* listModeParam);
META_RESULT __stdcall META_C2K_NsftListModeStart_r(const int metaHandle, unsigned int msTimeout, NSTLISTMODE_PARMS* listModeParam);
META_RESULT __stdcall META_C2K_NsftListModeGetFer(unsigned int msTimeout, unsigned int* count, unsigned int badFrames[], unsigned int totalFrames[]);
META_RESULT __stdcall META_C2K_NsftListModeGetFer_r(const int metaHandle, unsigned int msTimeout, unsigned int* count, unsigned int badFrames[], unsigned int totalFrames[]);

META_RESULT __stdcall META_C2K_ReadNvram(unsigned int msTimeout, unsigned int band, C2K_DB_SEGMENT dbSeg, void* buf, unsigned int len);
META_RESULT __stdcall META_C2K_ReadNvram_r(const int metaHandle, unsigned int msTimeout, unsigned int band, C2K_DB_SEGMENT dbSeg, void* buf, unsigned int len);
META_RESULT __stdcall META_C2K_WriteNvram(unsigned int msTimeout, unsigned int band, C2K_DB_SEGMENT dbSeg, void* buf, unsigned int len);
META_RESULT __stdcall META_C2K_WriteNvram_r(const int metaHandle, unsigned int msTimeout, unsigned int band, C2K_DB_SEGMENT dbSeg, void* buf, unsigned int len);
META_RESULT __stdcall META_C2K_ClearRfNvram(unsigned int msTimeout);
META_RESULT __stdcall META_C2K_ClearRfNvram_r(const int metaHandle, unsigned int msTimeout);
META_RESULT __stdcall META_C2K_CalInitNvram(unsigned int msTimeout, unsigned int mode);
META_RESULT __stdcall META_C2K_CalInitNvram_r(const int metaHandle, unsigned int msTimeout, unsigned int mode);
META_RESULT __stdcall META_C2K_FlushNvram(unsigned int msTimeout);
META_RESULT __stdcall META_C2K_FlushNvram_r(const int metaHandle, unsigned int msTimeout);

META_RESULT __stdcall META_C2K_CheckSIM1Inserted(unsigned int msTimeout, unsigned char* inserted);
META_RESULT __stdcall META_C2K_CheckSIM1Inserted_r(const int metaHandle, unsigned int msTimeout, unsigned char* inserted);
META_RESULT __stdcall META_C2K_CheckSIM2Inserted(unsigned int msTimeout, unsigned char* inserted);
META_RESULT __stdcall META_C2K_CheckSIM2Inserted_r(const int metaHandle, unsigned int msTimeout, unsigned char* inserted);

META_RESULT __stdcall META_C2K_SendCommand_r(const int metaHandle, char* szCmd);
META_RESULT __stdcall META_C2K_WaitResponse_r(const int metaHandle, unsigned int msTimeout, char* szToken, char* buffer, int size);
META_RESULT __stdcall META_C2K_ChangeBaudrate_r(const int metaHandle, int baudrate);
META_RESULT __stdcall META_C2K_SetCalibrationFlag_r(const int metaHandle, unsigned int msTimeout, int flag);
META_RESULT __stdcall META_C2K_GetCalibrationFlag_r(const int metaHandle, unsigned int msTimeout, int* flag);
META_RESULT __stdcall META_C2K_LoopbackTest_r(const int metaHandle, unsigned int msTimeout, unsigned char value);
META_RESULT __stdcall META_C2K_ReadCurrentTemperature_r(const int metaHandle, unsigned int msTimeout, unsigned char txPath, short* temperature);

#ifdef __cplusplus
}
#endif

#endif
