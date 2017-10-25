#include "StdAfx.h"
#include <shlwapi.h> 
#include "SPexc.h"
#include "SN Writer.h"
#include "SN WriterDlg.h"
#include "ScanData.h"
#include "HdcpEncryption.h"
#include "C2kAgent_api.h"
//#include "C2kAgent_api_datatype.h"
#include <windows.h>
#include <tchar.h>
#include <string.h>
#include "Encryption.h"



#define s_MAX_PATH 512

#define META_MODEM_SRV_ETS 3
#define META_MODEM_CH_TUNNELING 2

int C2K_Flag =1;


extern CSNWriterDlg *g_pMainDlg;

static const GUID  GUID_PORT_CLASS_USB2SER = {0x4D36E978L,0xE325,0x11CE,{0xBF,0xC1,0x08,0x00,0x2B,0xE1,0x03,0x18}};

void __stdcall CNF_SPReadFromNVRAM(const SPMETA_DLL::FT_NVRAM_READ_CNF *cnf, const short token, void *usrData)
{
    if (cnf->status == META_SUCCESS)
    {  
        SetEvent(*((HANDLE*)usrData));
    }
    
}

void __stdcall CNF_SPWriteToNVRAM ( const SPMETA_DLL::FT_NVRAM_WRITE_CNF *cnf, const short token, void *usrData)
{
    if (cnf->status == META_SUCCESS)
    {  
        SetEvent(*((HANDLE*)usrData));
    }   
}

SmartPhoneSN::SmartPhoneSN()
{
    memset(&m_stModeArg, 0, sizeof(SP_BOOT_ARG_S));
	memset(&m_sMdInfo, 0, sizeof(SP_MODEMInfo_s));
    m_iKernelComport = 0;
    m_eMetaMode = SP_NOTIN_META;
    m_hMauiMetaHandle = INVALID_META_HANDLE;
    m_hSPMetaHandle = INVALID_META_HANDLE;
	m_bWorldPhone = false;
    m_bWithoutMD = false;
    m_bDualModem = false;
    m_bUseNewConnectMauiMetaAPI = true; 
	HANDLE hdle_write_cmd = NULL;
	HANDLE hdle_read_out = NULL;
	r_bufsize = sizeof(read_buf);
	memset(&read_buf,0,r_bufsize);
}

SmartPhoneSN::~SmartPhoneSN()
{
    MetaHandle_DeInit();
	//dongck add for fastboot oem lock
	Adb_WR_Cmd("exit",strlen("exit"));
//	MTRACE(g_hEBOOT_DEBUG, "ATB_MR::Scan_Devices_FunProc(): close cmd.exe");
	memset(&read_buf,0,r_bufsize);
	CloseHandle(hdle_write_cmd);
//	MTRACE(g_hEBOOT_DEBUG, "Adb_Manager::~Adb_Manager(): close hdle_write_cmd");
	CloseHandle(hdle_read_out);
//	MTRACE(g_hEBOOT_DEBUG, "Adb_Manager::~Adb_Manager(): close hdle_read_out");
}

void SmartPhoneSN::SPInit()
{	
    memset(&m_stModeArg, 0, sizeof(SP_BOOT_ARG_S));
    memset(&m_sMdInfo, 0, sizeof(SP_MODEMInfo_s));
    m_iKernelComport = 0;
    m_eMetaMode = SP_NOTIN_META;
    m_bWorldPhone = false;
    m_bWithoutMD = false;
    m_bDualModem = false;
    m_bUseNewConnectMauiMetaAPI = true; 
    m_bWriteProdInfo = false;

    m_iCurMDChanelIndex = 0;
    m_bDSDAProject = false;
    m_bInitExtMDdb = false;
    memset(m_iMDChannelIndex, 0, (sizeof(UINT)*MAX_MD_CHANNEL_NUM));

	if(g_sMetaComm.eTargetType == C2K)
	{	
		if (!g_sMetaComm.sWriteOption.bWriteBarcode &&
        !g_sMetaComm.sWriteOption.bWriteIMEI &&
        !g_sMetaComm.sWriteOption.bWriteBT &&
        !g_sMetaComm.sWriteOption.bWriteWifi &&
        !g_sMetaComm.sWriteOption.bWriteEthernetMac &&
        !g_sMetaComm.sWriteOption.bWriteDrmkeyMCID &&
		(g_sMetaComm.sWriteOption.bWriteMeid ||
		g_sMetaComm.sWriteOption.bWriteEsn))

			m_bWriteProdInfo = false;
		else
			m_bWriteProdInfo = true;
	}
	else
	{
		if (m_bWriteModemNvram || g_sMetaComm.sWriteOption.bWriteBT || g_sMetaComm.sWriteOption.bWriteWifi)
		{
			m_bWriteProdInfo = true;
		} 
		else
		{
			m_bWriteProdInfo = false;
		}
	}
}

META_RESULT SmartPhoneSN::WriteNvramLoop()
{
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::WriteNvramLoop() start...");
    

    SMART_PHONE_STAGE_e spStage = SP_START_STAGE;
    SMART_PHONE_STAGE_e spNextStage = SP_END_STAGE;
    META_RESULT MetaResult = META_SUCCESS;
	MULTIIMEI_OPTION_e multiIMEIOption = SINGLE_MD_SINGLE_IMEI;
	
	int iRet = 0;
	int option = 0;
    double fBeginProcess = 0.25;
    double fStep = 0.04;
	m_bBackupNvramSuccess = false;

    bool bCheckCalFlag = g_sMetaComm.bCheckCalFlag;
    bool bCheckFtFlag = g_sMetaComm.bCheckFtFlag;

    int mdNums = 1; 
    int MDIndex = 0;
    int IMEI_index = 0; 
    bool bWriteModemFail = false;
    if (g_sMetaComm.eTargetType == SMART_PHONE_DUALMODEM || m_bDSDAProject)
    {        
        mdNums = 2;   
        g_sMetaComm.sIMEIOption.iImeiNums = 2;
    }
    else if (g_sMetaComm.eTargetType == TABLET_WIFI_ONLY)
    {
        //without modem project
        m_bWriteModemNvram = false;
        bCheckCalFlag = false;
        bCheckFtFlag = false;
        mdNums = 0;
    }
    else
    {
        mdNums = m_sMdInfo.number_of_md; 
    }
    

    while((spStage != SP_END_STAGE) && (*m_pMetaStopFlag != BOOT_STOP))
    {
      //g_pMainDlg->ShowTemperatureOnUI();  先disable
        switch(spStage)
        {
        case SP_START_STAGE:
            
            if ((m_bWriteModemNvram || (bCheckCalFlag || bCheckFtFlag)) && mdNums >= 1)
            {
                //Target in AP meta mode, need to switch Modem meta
                if (m_eMetaMode == SP_AP_META) 
                {
                    spNextStage = SP_AP2MD_STAGE;
                }
                else //Target already in modem meta mode
                {
                    spNextStage = SP_CHECK_CAL_FT_FLAG_STAGE;                  
                }
            }
            else
            {
				spNextStage = SP_PRODINFO_STAGE;
            }
            break;

        case SP_AP2MD_STAGE:
            fBeginProcess += fStep;
            //iRet = APSwithToModemMeta();
            iRet = APSwithToModemMeta_Ex();
            if (iRet == META_SUCCESS)
            {
                spNextStage = SP_CHECK_CAL_FT_FLAG_STAGE;
            }
            else
            {
                sprintf(m_strMsg, "ERROR!! APSwithToModemMeta_Ex() : MetaResult = %s", ResultToString(iRet));
                spNextStage = SP_END_STAGE;
            }
            break;

        case SP_CHECK_CAL_FT_FLAG_STAGE:
            if (g_sMetaComm.bCheckCalFlag || g_sMetaComm.bCheckFtFlag)
            {
                char tmpBuf[2048] = {0};
                iRet = REQ_ReadModem_NVRAM_Start(WRITE_BARCODE, tmpBuf, 1);
                if(iRet == META_SUCCESS)
                {
                    bool bCheckPass = true;
                    bCheckPass = CheckCalFinalTestStatus(tmpBuf);
                    if (bCheckPass == true)
                    {
                        spNextStage = SP_BARCODE_MD_STAGE;
                    }
                    else
                    {
                        iRet = META_FAILED;
                        spNextStage = SP_END_STAGE;                       
                    }
                } 
                else
                {
                    sprintf(m_strMsg, "ERROR!! Read Barcode: MetaResult = %s", ResultToString(iRet));
                    spNextStage = SP_END_STAGE;
                }
            }
            else
            {
                spNextStage = SP_BARCODE_MD_STAGE;
            }
            break;

		case SP_BARCODE_MD_STAGE:
						
			if(g_sMetaComm.sWriteOption.bWriteIMEI)
			{
				if(mdNums == 1 && g_sMetaComm.sIMEIOption.iImeiNums == 1)
				{
					multiIMEIOption = SINGLE_MD_SINGLE_IMEI;
				}
				else if(mdNums == 1 && g_sMetaComm.sIMEIOption.iImeiNums >= 2)
				{
					multiIMEIOption = SINGLE_MD_MULTI_IMEI;
				}
				else if(mdNums == 2)
				{
					if(g_sMetaComm.eTargetType == C2K && g_sMetaComm.sIMEIOption.iImeiNums == 1)
					{
						multiIMEIOption = SINGLE_MD_SINGLE_IMEI;
					}
					if(g_sMetaComm.eTargetType == C2K && g_sMetaComm.sIMEIOption.iImeiNums >= 2 )
					{
						multiIMEIOption = SINGLE_MD_MULTI_IMEI;
					}
					if(g_sMetaComm.eTargetType == SMART_PHONE_DUALMODEM && g_sMetaComm.sIMEIOption.iImeiNums == 2)
					{
						multiIMEIOption = DUAL_MD_DUAL_IMEI;
					}
				}
				else
				{
					multiIMEIOption = MULTIIMEI_RESERVE;
				}
			}			
			spNextStage = SP_IMEI_MD_STAGE;
			
			break;
			
		case SP_IMEI_MD_STAGE:
	        
            bWriteModemFail = false;
            for(MDIndex = 0; MDIndex < mdNums && bWriteModemFail == false; MDIndex++)
            {                   
                //When MDIndex = 0, database already init by EnterModemMetaToInitModemDB() function
                //So just need to load MDIndex >= 1 MD database
                if (mdNums >= 2 && MDIndex >= 1 && (g_sMetaComm.eTargetType != C2K))
                {          
                    fBeginProcess += fStep;
                    iRet = SwitchMDByIndex(MDIndex); 
                    if (iRet != META_SUCCESS)
                    {
                        sprintf(m_strMsg, "ERROR!!SwitchMDByIndex[%d] : MetaResult = %s", MDIndex, ResultToString(iRet));
                        bWriteModemFail = true;
                        break;
                    }
                    else
                    {          
                        fBeginProcess += fStep;
                        iRet = LoadModemDatabase(MDIndex);
                        if (iRet != META_SUCCESS)
                        {
                            sprintf(m_strMsg, "ERROR!!LoadModemDatabase[%d] : MetaResult = %s", MDIndex, ResultToString(iRet));
                            bWriteModemFail = true;
                            break;
                        }                                                     
                    }
                }

                if (g_sMetaComm.sWriteOption.bWriteBarcode && (MDIndex == 0 || (mdNums >= 2 && MDIndex >= 1 && (g_sMetaComm.eTargetType != C2K))))
                {      
                    fBeginProcess += fStep;
                    MTRACE(g_hEBOOT_DEBUG, "Barcode[%d] = \"%s\"", MDIndex, m_sScanData.strBarcode);
                    iRet = REQ_WriteModem_NVRAM_Start(WRITE_BARCODE, m_sScanData.strBarcode, 1);
                    if (iRet != META_SUCCESS)
                    {
                        sprintf(m_strMsg, "ERROR!! Barcode[%d] : MetaResult = %s", MDIndex, ResultToString(iRet));
                        bWriteModemFail = true;
                        break;
                    }
                }
                
                if(g_sMetaComm.sWriteOption.bWriteIMEI && (MDIndex == 0 || (mdNums >= 2 && MDIndex >= 1 && (g_sMetaComm.eTargetType != C2K))))
                {
                    if(multiIMEIOption == SINGLE_MD_SINGLE_IMEI || multiIMEIOption == SINGLE_MD_MULTI_IMEI)
                    {
                        for (int i = 0; i < g_sMetaComm.sIMEIOption.iImeiNums; i++)
                        {
                            fBeginProcess += fStep;
                            IMEI_index = i;
                            MTRACE(g_hEBOOT_DEBUG, "IMEI[%d] = \"%s\"", i, m_sScanData.strIMEI[i]);
						
                            iRet = REQ_WriteModem_NVRAM_Start(WRITE_IMEI, m_sScanData.strIMEI[i], i+1);                          
                            if (iRet != META_SUCCESS)
                            {
                                if (m_bNeedBackupIMEI)
                                {
                                    strncpy(g_AutoGenData.sIMEI.Next, m_strBackupIMEI, strlen(m_strBackupIMEI));
                                }

                                sprintf(m_strMsg, "ERROR!! IMEI[%d] : MetaResult = %s", i, ResultToString(iRet));
                                bWriteModemFail = true;
                                break;
                            }
                        }// end for (int i = 0; i < g_sMetaComm.sIMEIOption.iImeiNums; i++)
                    }//end if(multiIMEIOption == SINGLE_MD_SINGLE_IMEI || multiIMEIOption == SINGLE_MD_MULTI_IMEI)
                    else if(multiIMEIOption == DUAL_MD_DUAL_IMEI)
                    {
                        fBeginProcess += fStep;
                        int i = 0;
                        i = MDIndex;
                        IMEI_index = MDIndex;
                        if (m_bDSDAProject)
                        {
                            IMEI_index = 0;
                        }

                        MTRACE(g_hEBOOT_DEBUG, "IMEI[%d] = \"%s\"", i, m_sScanData.strIMEI[i]);
                        iRet = REQ_WriteModem_NVRAM_Start(WRITE_IMEI, m_sScanData.strIMEI[i], IMEI_index+1);                          
                        if (iRet != META_SUCCESS)
                        {
                            if (m_bNeedBackupIMEI)
                            {
                                strncpy(g_AutoGenData.sIMEI.Next, m_strBackupIMEI, strlen(m_strBackupIMEI));
                            }
                            
                            sprintf(m_strMsg, "ERROR!! IMEI[%d] : MetaResult = %s", i, ResultToString(iRet));
                            bWriteModemFail = true;
                            break;
                       }
                    }

                    if (iRet == META_SUCCESS)
                    {                                             							
						if ((IMEI_index + 1) == g_sMetaComm.sIMEIOption.iImeiNums)
                        {	
							if (g_sMetaComm.sIMEIOption.bLockIMEI)
                            {
                                iRet = META_NVRAM_LockDown_r(m_hMauiMetaHandle, 5000);
                                if (iRet != META_SUCCESS)
                                {
                                    bWriteModemFail = true;
                                    break;
                                } 
                            }                                            
                        }                                       
                    } 
                    else
                    {
                        bWriteModemFail = true;
                        break;
                    }
                }//end if(g_sMetaComm.sWriteOption.bWriteIMEI)                            
            }//end for(MDIndex = 0; MDIndex < mdNums; MDIndex++)
            //Backup imei to SDS
			if(!bWriteModemFail && m_bDSDAProject)
			{
				_BOOL BackupResult = DSDA_ExternalModemBackup();
				if(_TRUE != BackupResult)
				{
					sprintf(m_strMsg, "ERROR!! Backup external modem fail!");
					spNextStage = SP_C2K_STAGE;
					break;
				}
			}
				
            if (bWriteModemFail == true)
            {
                spNextStage = SP_END_STAGE;
            }
            else
            {
                spNextStage = SP_C2K_STAGE;
            }

            break;
		case SP_C2K_STAGE:
			fBeginProcess += fStep;
			if((g_sMetaComm.eTargetType == C2K)&&(m_eMetaMode == SP_MODEM_META ))
			{
				if(g_sMetaComm.sWriteOption.bWriteMeid || g_sMetaComm.sWriteOption.bWriteEsn)
				{
					EnterC2KModemMeta(&iRet, &m_hMauiMetaHandle, &C2K_Flag);

					if((iRet != META_SUCCESS) || (0 == C2K_Flag))
					{
						//bAnyOperationFail = true;
						//goto End;
						spNextStage = SP_END_STAGE;
					}
					else
					{
						spNextStage = SP_MD2AP_STAGE;
					}
				}
				else
				{
					spNextStage = SP_MD2AP_STAGE;
				}

			}
			else
			{
				spNextStage = SP_MD2AP_STAGE;
			}
			break;


        case SP_MD2AP_STAGE:
            fBeginProcess += fStep;
            iRet = ModemSwithToAPMeta();
            if (iRet == META_SUCCESS)
            {
                spNextStage = SP_PRODINFO_STAGE;
            }
            else
            {
                spNextStage = SP_END_STAGE;
            }
            break;

        case SP_PRODINFO_STAGE:

            if (m_bWriteProdInfo && g_sMetaComm.bSkipWriteProdInfo == false)
            {
                MTRACE(g_hEBOOT_DEBUG, "Prod_Info = \"...\"");
                fBeginProcess += fStep;
                iRet = REQ_WriteAP_PRODINFO_Start(m_sScanData.strBarcode, m_sScanData.strIMEI,m_sScanData.strBTAddr,m_sScanData.strWifiAddr,m_sScanData.strSerialNo);
                if (iRet == META_SUCCESS)
                {
                    spNextStage = SP_WRITE_TEMP_STAGE;
                }
                else
                {
                    sprintf(m_strMsg, "ERROR!! Prod_Info : MetaResult = %s", ResultToString_SP(iRet));
                    spNextStage = SP_END_STAGE;
                }               
            }
            else
            {
                spNextStage = SP_WRITE_TEMP_STAGE;
            }

            break;
	
        case SP_WRITE_TEMP_STAGE:         
            if(QuerySpeakerCalibrationSupport() == SPMETA_DLL::META_SUCCESS && g_sMetaComm.sIMEIOption.Temp_Option.bWriteTemperature) //Query support yes or no from target
            {
                fBeginProcess += fStep;
                float minTemp = 20.0;
                float maxTemp = 30.0;
                float curTemp = 0.0;
                curTemp = atof(g_sMetaComm.sIMEIOption.Temp_Option.strTemperatureData);

                MTRACE(g_hEBOOT_DEBUG, "CurTemperature = \"%s\"", g_sMetaComm.sIMEIOption.Temp_Option.strTemperatureData);
                if((minTemp <= curTemp) && (curTemp <= maxTemp))
                {
                    iRet = REQ_WriteAP_NVRAM_Start(WRITE_TEMPERATURE, g_sMetaComm.sIMEIOption.Temp_Option.strTemperatureData, 1);
                    if (iRet == META_SUCCESS)
                    {
                        spNextStage = SP_BT_ADDRESS_STAGE;
                    }
                    else
                    {
                        sprintf(m_strMsg, "ERROR!! Audio_Temperature : MetaResult = %s", ResultToString_SP(iRet));
                        spNextStage = SP_END_STAGE;
                    }  
                }
                else
                {
                    sprintf(m_strMsg, "Warning: Temperature must be between 20.0~30.0, please reset current temperature!!");
                    MTRACE(g_hEBOOT_DEBUG, "%s",m_strMsg);
                    iRet = META_FAILED;
                    spNextStage = SP_END_STAGE;
                }
            }
            else
            {
                spNextStage = SP_BT_ADDRESS_STAGE;
            }

            break;

				
        case SP_BT_ADDRESS_STAGE:
            if (g_sMetaComm.sWriteOption.bWriteBT)
            {
                fBeginProcess += fStep;
                MTRACE(g_hEBOOT_DEBUG, "BT = \"%s\"", m_sScanData.strBTAddr);
                iRet = REQ_WriteAP_NVRAM_Start(WRITE_BT, m_sScanData.strBTAddr, 1);
                if (iRet == META_SUCCESS)
                {
                    spNextStage = SP_WIFI_ADDRESS_STAGE;
                }
                else
                {
                    sprintf(m_strMsg, "ERROR!! BT : MetaResult = %s", ResultToString_SP(iRet));
                    spNextStage = SP_END_STAGE;
                }
            }
            else
            {
                spNextStage = SP_WIFI_ADDRESS_STAGE;
            }
            break;

        case SP_WIFI_ADDRESS_STAGE:
            if (g_sMetaComm.sWriteOption.bWriteWifi)
            {
                fBeginProcess += fStep;
                MTRACE(g_hEBOOT_DEBUG, "Wifi = \"%s\"", m_sScanData.strWifiAddr);
                iRet = REQ_WriteAP_NVRAM_Start(WRITE_WIFI, m_sScanData.strWifiAddr, 1);
                if (iRet == META_SUCCESS)
                {
                    spNextStage = SP_ETHERNET_MAC_STAGE;
                }
                else
                {
                    sprintf(m_strMsg, "ERROR!! Wifi : MetaResult = %s", ResultToString_SP(iRet));
                    spNextStage = SP_END_STAGE;
                }
            }
            else
            {
                spNextStage = SP_ETHERNET_MAC_STAGE;
            }
            break;

        case SP_ETHERNET_MAC_STAGE:
            if (g_sMetaComm.sWriteOption.bWriteEthernetMac)
            {
                fBeginProcess += fStep;
                MTRACE(g_hEBOOT_DEBUG, "Ethernet Mac = \"%s\"", m_sScanData.strEthernetMac);
                iRet = REQ_WriteAP_NVRAM_Start(WRITE_ETHERNET_MAC, m_sScanData.strEthernetMac, 1);
                if (iRet == META_SUCCESS)
                {
                    spNextStage = SP_HDCP_STAGE;
                }
                else
                {
                    sprintf(m_strMsg, "ERROR!! Ethernet Mac : MetaResult = %s", ResultToString_SP(iRet));
                    spNextStage = SP_END_STAGE;
                }
            } 
            else
            {
                spNextStage = SP_HDCP_STAGE;
            }
            break;

        case SP_HDCP_STAGE:
            //TO DO
            fBeginProcess += fStep;
            if (g_sMetaComm.sWriteOption.bWriteHdcp)
            {
                iRet = REQ_WriteHdcpBinToAPNvram_Start(g_sMetaComm.sLoadFile.strHdcpBinPath);
                if (iRet == META_SUCCESS)
                {
                    spNextStage = SP_DRMKEY_STAGE;
                } 
                else
                {
                    sprintf(m_strMsg, "ERROR!! Hdcp : MetaResult = %s", ResultToString_SP(iRet));
                    spNextStage = SP_END_STAGE;
                }
            } 
            else
            {
                spNextStage = SP_DRMKEY_STAGE;
            }           
            break;

        case SP_DRMKEY_STAGE:
            //TO DO
            fBeginProcess += fStep;
            if (g_sMetaComm.sWriteOption.bWriteDrm)
            {
                iRet = REQ_InstallDRMKey_Start(g_sMetaComm.sLoadFile.strDrmKeyPath);
                if (iRet == META_SUCCESS)
                {
                    spNextStage = SP_HDCPDATA_INSTALL_STAGE;
                } 
                else
                {
                    sprintf(m_strMsg, "ERROR!! DRMKey : MetaResult = %s", ResultToString_SP(iRet));
                    spNextStage = SP_END_STAGE;
                }
            } 
            else
            {
                spNextStage = SP_HDCPDATA_INSTALL_STAGE;
            }           
            break;

        case SP_HDCPDATA_INSTALL_STAGE:
            //TO DO
            fBeginProcess += fStep;
            if (g_sMetaComm.sWriteOption.bInstallHdcpData)
            {
                iRet = REQ_InstallHdcpData_Start(g_sMetaComm.sLoadFile.strHdcpDataPath, g_sMetaComm.sLoadFile.strHdcpCekPath);
                if (iRet == META_SUCCESS)
                {
                    spNextStage = SP_DRMKEY_MCID_STAGE;
                } 
                else
                {
                    sprintf(m_strMsg, "ERROR!! HdcpData : MetaResult = %s", ResultToString_SP(iRet));
                    spNextStage = SP_END_STAGE;
                }
            } 
            else
            {
                spNextStage = SP_DRMKEY_MCID_STAGE;
            }           
            break;

        case SP_DRMKEY_MCID_STAGE:
            //TO DO
            fBeginProcess += fStep;
            if (g_sMetaComm.sWriteOption.bWriteDrmkeyMCID)
            {
                iRet = REQ_WriteDRMKeyMCID_Start(m_sScanData.strDrmkeyMCID);
                if (iRet == META_SUCCESS)
                {
                    spNextStage = SP_BACKUPNV_TO_PC_STAGE;
                } 
                else
                {
                    sprintf(m_strMsg, "ERROR!! DRMKeyMCID : MetaResult = %s", ResultToString_SP(iRet));
                    spNextStage = SP_END_STAGE;
                }
            } 
            else
            {
                spNextStage = SP_BACKUPNV_TO_PC_STAGE;
            }           
            break;
			
		case SP_BACKUPNV_TO_PC_STAGE:
			if(g_sMetaComm.bCheckBackNVtoPC)
			{	
			   fBeginProcess += fStep;
			   char NumFile[100] = {0};
			   iRet = ReadNvToMakeFileName(NumFile);
			
			   if(iRet == META_SUCCESS)
			   	{
					iRet = REQ_BackupNvram2PC_Start(NumFile);
					if(iRet != META_SUCCESS)
					{
						 sprintf(m_strMsg, "ERROR!! REQ_BackupNvram2PC_Start : MetaResult = %s", ResultToString_SP(iRet));
                         spNextStage = SP_END_STAGE;
					}
					else
					{
					     spNextStage = SP_BACKUP_NVRAM_STAGE;
					}	
			    }
			   else
			    {
			        spNextStage = SP_END_STAGE;
			    }
			}
			else
			{
			    spNextStage = SP_BACKUP_NVRAM_STAGE;
			}
			break;

        case SP_BACKUP_NVRAM_STAGE:
            int option = 0;
            fBeginProcess += fStep;
            if (g_sMetaComm.sWriteOption.bWriteBarcode && !g_sMetaComm.sWriteOption.bWriteIMEI)
            {
                option = 1;
            } 
            else if(!g_sMetaComm.sWriteOption.bWriteBarcode && g_sMetaComm.sWriteOption.bWriteIMEI)
            {
                option = 2;
            }
            else if(g_sMetaComm.sWriteOption.bWriteBarcode && g_sMetaComm.sWriteOption.bWriteIMEI)
            {
                option = 3;
            }

            iRet = REQ_BackupNvram2BinRegion_Start(option);            
            if (iRet != META_SUCCESS)
            {
                m_bBackupNvramSuccess = false;
                sprintf(m_strMsg, "ERROR!! BackUP : MetaResult = %s", ResultToString_SP(iRet));
            }
			else
			{
			    m_bBackupNvramSuccess = true;
			}
            
            spNextStage = SP_END_STAGE;
            break;
            
        }

        UpdateProgress(fBeginProcess);
        spStage = spNextStage;
    }

    if (iRet!= META_SUCCESS)
    {
        UpdateMsgInfo(m_strMsg);
    }

    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::WriteNvramLoop() end...");
    return (META_RESULT)iRet;
}

int SmartPhoneSN::GetSPModemInfo_Ex()
{
    int iRet = 0;
    char *pFuncName = NULL;
//	bool bExternMDDownload = (g_sMetaComm.sWriteOption.bWriteBarcode)? g_sMetaComm.sBarcodeOption.bExtMdDl:false;
	
    //Init parameters for without world phone feature
    m_sMdInfo.number_of_md = 1;
    m_sMdInfo.active_md_idx = 1;
    m_sMdInfo.number_of_mdSwImg = 1;
    m_sMdInfo.activeMdTypeIdx = 0;
    m_bDSDAProject = false;

    
    SPMETA_DLL::MODEM_QUERY_INFO_REQ pReq;
    SPMETA_DLL::MODEM_QUERY_INFO_CNF pCnf;
    memset(&pReq, 0, sizeof(SPMETA_DLL::MODEM_QUERY_INFO_REQ));
    memset(&pCnf, 0, sizeof(SPMETA_DLL::MODEM_QUERY_INFO_CNF));

    if(SPMETA_DLL::SP_META_QueryIfFunctionSupportedByTarget_r(m_hSPMetaHandle, 5000, "SP_META_MODEM_Query_Info_r") == SPMETA_DLL::META_SUCCESS)
    {       
        iRet = SPMETA_DLL::SP_META_MODEM_Query_Info_r(m_hSPMetaHandle, 2000, &pReq, &pCnf); 
        if (iRet != META_SUCCESS)
        {
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_MODEM_Query_Info_r(): Get modem info from target Fail, MetaResult = %s!", ResultToString_SP(iRet));
            return iRet;
        }
        else
        {
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_MODEM_Query_Info_r(): Get modem info from target successfully! md_numb = %d, active_md_idx = %d!",
                pCnf.modem_number, pCnf.modem_id);
            m_sMdInfo.number_of_md = pCnf.modem_number;
            m_sMdInfo.active_md_idx = pCnf.modem_id;
            m_bWithoutMD = (m_sMdInfo.number_of_md == 0) ? true : false;
            m_bDualModem = (m_sMdInfo.number_of_md == 2) ? true : false;
        }
    }
    
    
    
    SPMETA_DLL::MODEM_CAPABILITY_LIST_REQ pCapabilitiesReq;
    SPMETA_DLL::MODEM_CAPABILITY_LIST_CNF pCapabilitiesCnf;
    memset(&pCapabilitiesReq, 0, sizeof(pCapabilitiesReq));
    memset(&pCapabilitiesCnf, 0, sizeof(pCapabilitiesCnf));
    
    if(SPMETA_DLL::SP_META_QueryIfFunctionSupportedByTarget_r(m_hSPMetaHandle, 5000, "SP_META_MODEM_Capability_r") == SPMETA_DLL::META_SUCCESS)
    {       
        iRet = SPMETA_DLL::SP_META_MODEM_Capability_r(m_hSPMetaHandle, 2000, &pCapabilitiesReq, &pCapabilitiesCnf); 
        if (iRet != META_SUCCESS)
        {
            m_sMdInfo.multi_md_capability_support = 0;
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_MODEM_Capability_r(): Get modem capability from target Fail!!");
            
            m_tMetaReq_Ex.protocol = 1;
            m_tMetaReq_Ex.channel_type = 1;
            iRet = META_SUCCESS;
        }
        else
        {                  
            m_sMdInfo.multi_md_capability_support = 1;
            memcpy(&m_SpMdCapList, &pCapabilitiesCnf, sizeof(pCapabilitiesCnf));
            m_tMetaReq_Ex.protocol = m_SpMdCapList.modem_cap[m_sMdInfo.active_md_idx-1].md_service;
            m_tMetaReq_Ex.channel_type =  m_SpMdCapList.modem_cap[m_sMdInfo.active_md_idx-1].ch_type;
            
                       
            //for MT6595 DSDA project
            if (m_sMdInfo.number_of_md >= 2)
            {
                m_bDSDAProject = true;
                int mdIndex = 0;
                for (int i = 0; i < MAX_MD_CHANNEL_NUM; i++)
                {
                    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Modem capability, protocol = %d, channel_type = %d!",
                        m_SpMdCapList.modem_cap[i].md_service, m_SpMdCapList.modem_cap[i].ch_type);
                    if (m_SpMdCapList.modem_cap[i].md_service > 0 )
                    {
                        m_iMDChannelIndex[mdIndex] = i;
                        mdIndex += 1;
                    }

					if (m_sMdInfo.number_of_md == 2 && m_SpMdCapList.modem_cap[i].md_service ==3)
					{
						m_bDSDAProject = false;
					}

                }
            }      
        }
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_MODEM_Capability_r(): Get modem capability, protocol = %d, channel_type = %d!",
            m_tMetaReq_Ex.protocol, m_tMetaReq_Ex.channel_type);
    }
    
       
    SPMETA_DLL::MODEM_GET_CURRENTMODEMTYPE_REQ pCurMDTypeReq;
    SPMETA_DLL::MODEM_GET_CURENTMODEMTYPE_CNF pCurMDTypeCnf;
    memset(&pCurMDTypeReq, 0, sizeof(pCurMDTypeReq));
    memset(&pCurMDTypeCnf, 0, sizeof(pCurMDTypeCnf));
    
    if(SPMETA_DLL::SP_META_QueryIfFunctionSupportedByTarget_r(m_hSPMetaHandle, 5000, "SP_META_MODEM_Get_CurrentModemType_r") == SPMETA_DLL::META_SUCCESS)
    {       
        iRet = SPMETA_DLL::SP_META_MODEM_Get_CurrentModemType_r(m_hSPMetaHandle, 2000, &pCurMDTypeReq, &pCurMDTypeCnf);
        if (iRet != META_SUCCESS)
        {
            iRet = META_SUCCESS;
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_MODEM_Get_CurrentModemType_r(): Get modem type from target Fail, mean that handset not support worldphone feature!!");
        }
        else
        {
            m_sMdInfo.current_mdtype = pCurMDTypeCnf.current_modem_type;
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_MODEM_Get_CurrentModemType_r(): Get MD Image info from target success, MdType = %d.", m_sMdInfo.current_mdtype);
        }
    }
    
    
    SPMETA_DLL::MODEM_QUERY_MDIMGTYPE_REQ pMDImgTypeReq;
    SPMETA_DLL::MODEM_QUERY_MDIMGTYPE_CNF pMDImgTypeCnf;
    memset(&pMDImgTypeReq, 0, sizeof(pMDImgTypeReq));
    memset(&pMDImgTypeCnf, 0, sizeof(pMDImgTypeCnf));
    
    if(SPMETA_DLL::SP_META_QueryIfFunctionSupportedByTarget_r(m_hSPMetaHandle, 5000, "SP_META_MODEM_Query_MDIMGType_r") == SPMETA_DLL::META_SUCCESS)
    {       
        iRet = SPMETA_DLL::SP_META_MODEM_Query_MDIMGType_r(m_hSPMetaHandle, 2000, &pMDImgTypeReq, &pMDImgTypeCnf);
        if (iRet != META_SUCCESS)
        {
            iRet = META_SUCCESS;
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_MODEM_Query_MDIMGType_r(): Get MD Image info from target fail, mean that handset not support worldphone feature!!");
        }
        else
        {
            memcpy(m_sMdInfo.mdimg_type, pMDImgTypeCnf.mdimg_type, 16);
            bool bAllZero = true;
            m_bWorldPhone = true;
            m_sMdInfo.number_of_mdSwImg = 0;
            //Get current active mdtype index
            for(int i = 0; i < 16; i++)
            {
                if(m_sMdInfo.mdimg_type[i] !=0 )
                {
                    m_sMdInfo.number_of_mdSwImg += 1;                                    
                    bAllZero = false;
                }
                
                if(m_sMdInfo.current_mdtype != 0 && m_sMdInfo.mdimg_type[i] == m_sMdInfo.current_mdtype)
                {
                    m_sMdInfo.activeMdTypeIdx = i;
                }
            }
            
            //For before MT6577(include MT6577)old chip project
            //Old chip project call this api will return success, but mdimg_type array data all zero
            if (bAllZero)
            {
                m_sMdInfo.number_of_mdSwImg = 1;
                m_sMdInfo.activeMdTypeIdx = 0;
                m_bWorldPhone = false;
                MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_MODEM_Query_MDIMGType_r(): Get MD Image info from target success but all zero, mean that handset not support worldphone feature!!");
            }
            else
            {
                MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_MODEM_Query_MDIMGType_r(): Get MD Image info from target success, activeMdTypeIdx = %d, mean that handset support worldphone feature!!", m_sMdInfo.activeMdTypeIdx);
            }
            
            if (m_sMdInfo.number_of_md >= 2)
            {
                //extern modem have one SwImg
                m_sMdInfo.number_of_mdSwImg += (m_sMdInfo.number_of_md - 1);
            }
        }
    }  
#if 0
    if(m_bDSDAProject)
	{ 
        if(bExternMDDownload)
        {
            sprintf(m_strMsg, "Extern modem native download processing...");
    		UpdateMsgInfo(m_strMsg);
				
			iRet = DSDA_StartNativeDownload();
			if(iRet != SPMETA_DLL::META_SUCCESS)
			{
				sprintf(m_strMsg, "Extern modem native download fail. MetaResult = %s", ResultToString_SP(iRet));
    		    UpdateMsgInfo(m_strMsg);
			}    
        }
		else
		{
		    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_QueryNativeDownload() : Start query extern modem for native download...");
            for(int i=0; i<200; i++)
    		{
                Sleep(50);
				iRet = DSDA_QueryNativeDownload();
				if(iRet == 0) break;
            }
			if(iRet != 0)
			{
			    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_QueryNativeDownload() : Query status != 110, Please download Extern modem !");    
			}
		}
    }
#endif
	SPMETA_DLL::MODEM_QUERY_DOWNLOAD_STATUS_REQ pDLReq;
	SPMETA_DLL::MODEM_QUERY_DOWNLOAD_STATUS_CNF pDLCnf;
	   
    memset(&pDLReq, 0, sizeof(SPMETA_DLL::MODEM_QUERY_DOWNLOAD_STATUS_REQ));
    memset(&pDLCnf, 0, sizeof(SPMETA_DLL::MODEM_QUERY_DOWNLOAD_STATUS_CNF));
	   
	   //if(SPMETA_DLL:P_META_QueryIfFunctionSupportedByTarget_r(m_hSPMetaHandle, 5000, "SP_META_MODEM_Query_Download_Status_r ") == SPMETA_DLL::META_SUCCESS)
    if(m_bDSDAProject)
    {	   
	   iRet = SPMETA_DLL::SP_META_MODEM_Query_Download_Status_r (m_hSPMetaHandle, 80000, &pDLReq, &pDLCnf);
	   if (iRet != META_SUCCESS)
	   {
		   MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_MODEM_Query_Download_Status_r(): Query extern modem download process fail, MetaResult = %s", ResultToString_SP(iRet));
		   iRet = 0;
	   }
    }

	return iRet;
}

int SmartPhoneSN::GetSPModemInfo()
{
    int iRet = 0;
    char *pFuncName = NULL;
    //Init parameters for without world phone feature
    m_sMdInfo.number_of_md = 1;
    m_sMdInfo.active_md_idx = 1;
    m_sMdInfo.number_of_mdSwImg = 1;
    m_sMdInfo.activeMdTypeIdx = 0;
    m_bDSDAProject = false;

    //Get MD numbers & active index info
    iRet = SP_META_Wrapper_GetModemInfo_r(m_hSPMetaHandle, 5000, &m_sMdInfo.number_of_md, &m_sMdInfo.active_md_idx);
    if (iRet != META_SUCCESS)
    {
        pFuncName = "SmartPhoneSN::SP_META_Wrapper_GetModemInfo_r()";
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_GetModemInfo_r(): Get modem info from target Fail!!");
        goto Err;
    }
    else
    {      
        m_bWithoutMD = (m_sMdInfo.number_of_md == 0) ? true : false;
        m_bDualModem = (m_sMdInfo.number_of_md == 2) ? true : false;
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_GetModemInfo_r(): Get modem info from target success, md_num = %d, active_md_index = %d.",
            m_sMdInfo.number_of_md, m_sMdInfo.active_md_idx);
        
        //for LTE
        iRet = SP_META_Wrapper_QueryModemCapability_r(m_hSPMetaHandle, 5000, &m_SpWrapperMdCapList);
        if(iRet == META_SUCCESS)
        {            
            m_sMdInfo.multi_md_capability_support = 1;
            m_tMetaReq_Ex.protocol = m_SpWrapperMdCapList.modem_cap[m_sMdInfo.active_md_idx-1].md_service;
            m_tMetaReq_Ex.channel_type =  m_SpWrapperMdCapList.modem_cap[m_sMdInfo.active_md_idx-1].ch_type;

            //for MT6595 DSDA project
            if (m_sMdInfo.number_of_md >= 2)
            {
                m_bDSDAProject = true;
                int mdIndex = 0;
                for (int i = 0; i < MAX_MD_CHANNEL_NUM; i++)
                {
                    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Modem capability, protocol = %d, channel_type = %d!",
                        m_SpMdCapList.modem_cap[i].md_service, m_SpMdCapList.modem_cap[i].ch_type);
                    if (m_SpMdCapList.modem_cap[i].md_service > 0)
                    {
                        m_iMDChannelIndex[mdIndex] = i;
                        mdIndex += 1;
                    }
                }
            }  
        }
        else
        {           
            m_sMdInfo.multi_md_capability_support = 0;
            iRet = META_SUCCESS;
            m_tMetaReq_Ex.protocol = 1;
            m_tMetaReq_Ex.channel_type = 1;
        }    
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_QueryModemCapability_r(): protocol = %d, channel_type = %d!", 
                m_tMetaReq_Ex.protocol, m_tMetaReq_Ex.channel_type);
            
        //Get current active mdtype
        iRet = SP_META_Wrapper_GetCurrentModemType_r(m_hSPMetaHandle, 5000, m_sMdInfo.active_md_idx, &m_sMdInfo.current_mdtype);
        if(iRet == META_SUCCESS)
        {
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_GetCurrentModemType_r(): Get MD Image info from target success, MdType = %d.", m_sMdInfo.current_mdtype);
        }
        else
        {
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_GetCurrentModemType_r(): Get MD Image info from target Fail!!");
        }
        /*
        //SP_META_Wrapper_SetModemType_r(const int meta_handle, unsigned int ms_timeout, unsigned int active_md_idx, unsigned int active_md_type);
        iRet = SP_META_Wrapper_SetModemType_r(m_hSPMetaHandle, 1000, m_sMdInfo.active_md_idx, 3);
        if(iRet == META_SUCCESS)
        {
        m_bWorldPhone = true;
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_SetModemType_r(): Set MD Image info to target success!");
        }
        else
        {
        m_bWorldPhone = false;
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_SetModemType_r(): Set MD Image info to target Fail!!");
        }
        
          //Get current active mdtype
          iRet = SP_META_Wrapper_GetCurrentModemType_r(m_hSPMetaHandle, 1000, m_sMdInfo.active_md_idx, &m_sMdInfo.current_mdtype);
          if(iRet == META_SUCCESS)
          {
          m_bWorldPhone = true;
          MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_GetCurrentModemType_r(): Get MD Image info from target success!!");
          }
          else
          {
          m_bWorldPhone = false;
          MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_GetCurrentModemType_r(): Get MD Image info from target Fail!!");
          }
        */
        
        //Get current active MD software type
        iRet = SP_META_Wrapper_QueryMdImgType_r(m_hSPMetaHandle, 5000, m_sMdInfo.active_md_idx, m_sMdInfo.mdimg_type);
        if (iRet == 0)                              
        {
            bool bAllZero = true;
            m_bWorldPhone = true;
            m_sMdInfo.number_of_mdSwImg = 0;
            //Get current active mdtype index
            for(int i = 0; i < 16; i++)
            {
                if(m_sMdInfo.mdimg_type[i] !=0 )
                {
                    m_sMdInfo.number_of_mdSwImg += 1;                                    
                    bAllZero = false;
                }
                
                if(m_sMdInfo.current_mdtype != 0 && m_sMdInfo.mdimg_type[i] == m_sMdInfo.current_mdtype)
                {
                    m_sMdInfo.activeMdTypeIdx = i;
                }
            }
            
            //For before MT6577(include MT6577)old chip project
            //Old chip project call this api will return success, but mdimg_type array data all zero
            if (bAllZero)
            {
                m_sMdInfo.number_of_mdSwImg = 1;
                m_sMdInfo.activeMdTypeIdx = 0;
                m_bWorldPhone = false;
                MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_QueryMdImgType_r(): Get MD Image info from target success but all zero, mean that handset not support worldphone feature!!");
            }
            else
            {
                MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_QueryMdImgType_r(): Get MD Image info from target success, activeMdTypeIdx = %d, mean that handset support worldphone feature!!", m_sMdInfo.activeMdTypeIdx);
            }

            if (m_sMdInfo.number_of_md >= 2 && m_bDSDAProject)
            {
                //extern modem have one SwImg
                m_sMdInfo.number_of_mdSwImg += 1;
            }
        }
        else
        {
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_QueryMdImgType_r(): Get MD Image info from target fail, mean that handset not support worldphone feature!!");
        } 
        
        iRet = META_SUCCESS;
    }

    return iRet; 
    
Err:
    MTRACE_ERR(g_hEBOOT_DEBUG, "%s: MetaResult = %s", pFuncName, ResultToString_SP(iRet));     
    return iRet;
}

//Fix connect with kernel comport probabilistic fail bug
int SmartPhoneSN::TryToOpenSPKernelComport(int KernelCom_Num)
{
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::TryToOpenSPKernelComport(): Try to open kernel comport until it ready, KernelCom_Num = %d...",KernelCom_Num);
    HANDLE Hcom;
    char tmp_com[30] = {0};
    sprintf(tmp_com, "\\\\.\\COM%d", KernelCom_Num);
    
    int retryTime = 0;
    //try to open kernel comport until it ready
    do
    {
        retryTime += 1;
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::TryToOpenSPKernelComport(): Try to open kernel comport until it ready, retryTime = %d...",retryTime);
        Hcom = CreateFile(tmp_com, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (INVALID_HANDLE_VALUE != Hcom)
        {
            int Ret = CloseHandle(Hcom);
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::TryToOpenSPKernelComport(): Open kernel comport success, retryTime = %d...",  retryTime);
            return OK;
        }
        Sleep(1000);
    }while(retryTime <= 50);
    
    MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::TryToOpenSPKernelComport(): Open kernel comport fail, retryTime = %d...", retryTime);
    return ERROR;
}

int SmartPhoneSN::ConnectWithKernelPort_Ex(SP_METAMODE_e spMetaMode)
{
    int iRet = 0;
    unsigned short kernelComport = 0; 
    char *pFuncName = NULL;
    
    SPMETA_DLL::META_ConnectByUSB_Req     spUSBConnReq;
    SPMETA_DLL::META_ConnectByUSB_Report  spUSBConnReport;   
    memset(&spUSBConnReq, 0, sizeof(spUSBConnReq));
    memset(&spUSBConnReport, 0, sizeof(spUSBConnReport));
    
    SP_COM_FILTER_LIST_S sCOMFilter;
    SP_COM_PROPERTY_S sCOMProperty;   
    memset(&sCOMFilter, 0, sizeof(SP_COM_FILTER_LIST_S));
    memset(&sCOMProperty, 0, sizeof(SP_COM_PROPERTY_S));
    
    const UINT filterNums = 2;
    char *ppFilter[filterNums];
    for (int i = 0; i < filterNums; i++)
    {
        ppFilter[i] = NULL;
    }
    
    // Black kernel comport filter list
    ppFilter[0] = g_sMetaComm.sPortFilter.strBromFilter;
    ppFilter[1] = g_sMetaComm.sPortFilter.strKernelFilter;
    
    sCOMFilter.m_uCount = filterNums;
    sCOMFilter.m_ppFilterID = ppFilter;
    sCOMFilter.m_eType = SP_BLACK_LIST;
    
    if (g_sMetaComm.bUsbEnable)
    {     
        //phase out SP_META_GetDynamicUSBComPort_r API, cause it have probabilistic can`t fetch kernel comport issue  
        int iTimeout = m_tMetaReq_Ex.ms_connect_timeout / 1000;  //timeout unit: s, but m_tMetaReq_Ex.ms_connect_timeout unit is ms
        iRet = SP_GetIncrementCOMPortWithFilter(&sCOMFilter, &sCOMProperty, &GUID_PORT_CLASS_USB2SER, _FALSE, m_pMetaStopFlag, iTimeout); 
        if(0 == iRet)
        { 
            kernelComport = sCOMProperty.m_uNumber;
            m_iKernelComport = kernelComport;
            if (spMetaMode == SP_AP_META)
            {  
                spUSBConnReq.com_port = kernelComport;
                spUSBConnReq.ms_connect_timeout = m_tMetaReq_Ex.ms_connect_timeout;
                iRet = TryToOpenSPKernelComport(kernelComport);
                if(iRet == OK)
                {
                    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaModeByUSB_r(): Start enter AP meta mode, KernelComPort = %d", kernelComport);
                    iRet = SPMETA_DLL::SP_META_ConnectInMetaModeByUSB_r (m_hSPMetaHandle, &spUSBConnReq, m_pMetaStopFlag, &spUSBConnReport);
					if(g_sMetaComm.IgnoreApdatabase)
					{

						if (iRet == META_SUCCESS || iRet == SPMETA_DLL::META_MAUI_DB_INCONSISTENT)
						{
							iRet = META_SUCCESS;                
							MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaModeByUSB_r(): Enter meta successfully!!");
	#if 0
							MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information start...");
							iRet = GetSPModemInfo_Ex();                        
							if (iRet == 0)
							{
								MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information successfully!!");
							} 
							else
							{
								pFuncName = "GetSPModemInfo_Ex()";
								MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information fail, MetaResult = %s", ResultToString_SP(iRet));
								goto Err;
							}
							MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information end...");
	#endif
						}//end if (iRet == META_SUCCESS || iRet == SPMETA_DLL::META_MAUI_DB_INCONSISTENT)
					}
					else
					{
						if (iRet == META_SUCCESS)
						{               
							MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaModeByUSB_r(): Enter meta successfully!!");
	#if 0
							MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information start...");
							iRet = GetSPModemInfo_Ex();                        
							if (iRet == 0)
							{
								MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information successfully!!");
							} 
							else
							{
								pFuncName = "GetSPModemInfo_Ex()";
								MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information fail, MetaResult = %s", ResultToString_SP(iRet));
								goto Err;
							}
							MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information end...");
	#endif
						}//end if (iRet == META_SUCCESS)
						else
						{
							pFuncName = "SP_META_ConnectInMetaModeByUSB_r()";
							MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaModeByUSB_r(): Enter meta fail, MetaResult = %s", ResultToString_SP(iRet));                       
							goto Err;
						}
					}
                }//if(iRet==OK)
                else
                {
                    iRet = 1;
                    pFuncName = "TryToOpenSPKernelComport()";
                    MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::TryToOpenSPKernelComport(): Try to open kernel comport fail!!");                       
                    goto Err;
                }
            }//end if (spMetaMode == SP_AP_META)
            else
            {
                //TO DO
                iRet = META_FAILED;
            }
        }
        else
        {
            pFuncName = "SP_GetIncrementCOMPortWithFilter()";
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::ConnectWithKernelPort_Ex(): SP_GetIncrementCOMPortWithFilter get kernel comport fail, iRet = %d", iRet);
            return iRet;
        }
    }//end if(g_sMetaComm.bUsbEnable)
    else
    {
        kernelComport = g_sMetaComm.iCOMPort;
        m_iKernelComport = kernelComport;

        SPMETA_DLL::WM_META_ConnectInMETA_Req uartMETA_Req;
        SPMETA_DLL::WM_META_ConnectInMETA_Report uartMETA_Report;
        memset(&uartMETA_Req, 0 ,sizeof(SPMETA_DLL::WM_META_ConnectInMETA_Req));
        memset(&uartMETA_Report, 0 ,sizeof(SPMETA_DLL::WM_META_ConnectInMETA_Report));

        uartMETA_Req.com_port = m_iKernelComport;
        uartMETA_Req.baudrate[0] = SPMETA_DLL::META_BAUD921600;
        uartMETA_Req.baudrate[1] = SPMETA_DLL::META_BAUD_END;
        uartMETA_Req.flowctrl    = SPMETA_DLL::META_NO_FLOWCTRL;//META_SW_FLOWCTRL;
        uartMETA_Req.ms_connect_timeout = m_tMetaReq_Ex.ms_connect_timeout;

        
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaMode_r(): Start enter AP meta mode, KernelComPort = %d", kernelComport);
        iRet = SPMETA_DLL::SP_META_ConnectInMetaMode_r(m_hSPMetaHandle, &uartMETA_Req, m_pMetaStopFlag, &uartMETA_Report);
        if (iRet == META_SUCCESS)
        {                          
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaMode_r(): Enter meta successfully!!");
#if 0  
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information start...");
            iRet = GetSPModemInfo_Ex(); 
            if (iRet == 0)
            {
                MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information successfully!!");
            } 
            else
            {
                MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information fail, MetaResult = %s", ResultToString_SP(iRet));
                goto Err;
            }
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information end...");
#endif
        }//end if (iRet == META_SUCCESS)
        else
        {
            pFuncName = "SmartPhoneSN::SP_META_ConnectInMetaMode_r()";
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaMode_r(): enter meta fail, MetaResult = %s", ResultToString_SP(iRet));
            goto Err;
        } 
    }
	
	return iRet;

Err:
    MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::%s: MetaResult = %s", pFuncName, ResultToString_SP(iRet));
    return iRet;
}

int SmartPhoneSN::ConnectWithKernelPort(SP_METAMODE_e spMetaMode)
{
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::ConnectWithKernelPort(): Start to get dynamic kernel comport...");
    
    int iRet = 0;  
    char *pFuncName = NULL;
    unsigned short kernelComport = 0;  
    META_RESULT MetaResult = META_SUCCESS;
	META_ConnectByUSB_Req     usbConnReq;
    META_ConnectByUSB_Report  usbConnReport;  
    memset(&usbConnReq, 0, sizeof(usbConnReq));
    memset(&usbConnReport, 0, sizeof(usbConnReport));
	
    SP_COM_FILTER_LIST_S sCOMFilter;
    SP_COM_PROPERTY_S sCOMProperty;   
    memset(&sCOMFilter, 0, sizeof(SP_COM_FILTER_LIST_S));
    memset(&sCOMProperty, 0, sizeof(SP_COM_PROPERTY_S));

	const UINT filterNums = 2;
	char *ppFilter[filterNums];
    for (int i = 0; i < filterNums; i++)
    {
        ppFilter[i] = NULL;
    }

    // Block kernel comport filter list
    ppFilter[0] = g_sMetaComm.sPortFilter.strPreloaderFilter;
    ppFilter[1] = g_sMetaComm.sPortFilter.strKernelFilter;
    
	sCOMFilter.m_uCount = filterNums;
    sCOMFilter.m_ppFilterID = ppFilter;
	sCOMFilter.m_eType = SP_BLACK_LIST;
	  
    if (g_sMetaComm.bUsbEnable)
    {
        //phase out SP_META_GetDynamicUSBComPort_r API, cause it have probabilistic can`t fetch kernel comport issue
        //iRet = SPMETA_DLL::SP_META_GetDynamicUSBComPort_r(m_hSPMetaHandle, 35000, &kernelComport, m_pMetaStopFlag);
		iRet = SP_GetIncrementCOMPortWithFilter(&sCOMFilter, &sCOMProperty, &GUID_PORT_CLASS_USB2SER, _FALSE, m_pMetaStopFlag, m_tMetaReq_Ex.ms_connect_timeout); 
        if(0 == iRet)
        { 
            kernelComport = sCOMProperty.m_uNumber;			
        }
     
        if (iRet == SPMETA_DLL::META_SUCCESS)
        {
            m_iKernelComport = kernelComport;
            if (spMetaMode == SP_AP_META)
            {                                      
                if (g_sMetaComm.eTargetType == RNDIG_DONGLE)       
                {
                    m_bWorldPhone = false;
                    SPMETA_DLL::META_ConnectByUSB_Req     spUSBConnReq;
                    SPMETA_DLL::META_ConnectByUSB_Report  spUSBConnReport;   
                    memset(&spUSBConnReport, 0, sizeof(spUSBConnReq));
                    memset(&spUSBConnReport, 0, sizeof(spUSBConnReport));
                    
                    spUSBConnReq.com_port = kernelComport;
                    spUSBConnReq.ms_connect_timeout = m_tMetaReq_Ex.ms_connect_timeout;
                    iRet = TryToOpenSPKernelComport(kernelComport);
                    if(iRet == OK)
                    {
                        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaModeByUSB_r(): Start enter AP meta mode, KernelComPort = %d", kernelComport);
                        iRet = SPMETA_DLL::SP_META_ConnectInMetaModeByUSB_r (m_hSPMetaHandle, &spUSBConnReq, m_pMetaStopFlag, &spUSBConnReport);
                        if (iRet == META_SUCCESS)
                        {
                            
                            m_sMdInfo.number_of_md = 1;
                            m_sMdInfo.active_md_idx = 1;
                            m_sMdInfo.number_of_mdSwImg = 1;
                            m_sMdInfo.activeMdTypeIdx = 0;
                            m_sMdInfo.number_of_md = 1;
                            
                            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaModeByUSB_r(): Enter meta successfully!!");
                        #if 0
                            SPMETA_DLL::MODEM_QUERY_INFO_REQ pReq;
                            SPMETA_DLL::MODEM_QUERY_INFO_CNF pCnf;
                            memset(&pReq, 0, sizeof(SPMETA_DLL::MODEM_QUERY_INFO_REQ));
                            memset(&pCnf, 0, sizeof(SPMETA_DLL::MODEM_QUERY_INFO_CNF));
                            
                            iRet = SPMETA_DLL::SP_META_MODEM_Query_Info_r(m_hSPMetaHandle, 1000, &pReq, &pCnf); 
                            if (iRet != META_SUCCESS)
                            {
                                pFuncName = "SmartPhoneSN::SP_META_MODEM_Query_Info_r()";
                                goto Err;
                            }
                            m_sMdInfo.number_of_md = pCnf.modem_number;
                            
                            
                            //Always fail, so pause phase out 
                            SPMETA_DLL::MODEM_CAPABILITY_LIST_REQ pCapabilitiesReq;
                            SPMETA_DLL::MODEM_CAPABILITY_LIST_CNF pCapabilitiesCnf;
                            memset(&pCapabilitiesReq, 0, sizeof(pCapabilitiesReq));
                            memset(&pCapabilitiesCnf, 0, sizeof(pCapabilitiesCnf));
                            
                            iRet = SPMETA_DLL::SP_META_MODEM_Capability_r(m_hSPMetaHandle, 1000, &pCapabilitiesReq, &pCapabilitiesCnf); 
                            if (iRet != META_SUCCESS)
                            {
                                pFuncName = "SmartPhoneSN::SP_META_MODEM_Capability_r()";
                                //iRet = META_SUCCESS;
                                //goto Err;
                            }
                            memcpy(&m_SpMdCapList, &pCapabilitiesCnf, sizeof(pCapabilitiesCnf));
                            
                            
                            SPMETA_DLL::MODEM_GET_CURRENTMODEMTYPE_REQ pCurMDTypeReq;
                            SPMETA_DLL::MODEM_GET_CURENTMODEMTYPE_CNF pCurMDTypeCnf;
                            memset(&pCurMDTypeReq, 0, sizeof(pCurMDTypeReq));
                            memset(&pCurMDTypeCnf, 0, sizeof(pCurMDTypeCnf));
                            
                            iRet = SPMETA_DLL::SP_META_MODEM_Get_CurrentModemType_r(m_hSPMetaHandle, 1000, &pCurMDTypeReq, &pCurMDTypeCnf);
                            if (iRet != META_SUCCESS)
                            {
                                pFuncName = "SmartPhoneSN::SP_META_MODEM_Get_CurrentModemType_r()";
                                //goto Err;
                            }
                            m_sMdInfo.current_mdtype = pCurMDTypeCnf.current_modem_type;
                            
                            SPMETA_DLL::MODEM_QUERY_MDIMGTYPE_REQ pMDImgTypeReq;
                            SPMETA_DLL::MODEM_QUERY_MDIMGTYPE_CNF pMDImgTypeCnf;
                            memset(&pMDImgTypeReq, 0, sizeof(pMDImgTypeReq));
                            memset(&pMDImgTypeCnf, 0, sizeof(pMDImgTypeCnf));
                            
                            iRet = SPMETA_DLL::SP_META_MODEM_Query_MDIMGType_r(m_hSPMetaHandle, 1000, &pMDImgTypeReq, &pMDImgTypeCnf);
                            if (iRet != META_SUCCESS)
                            {
                                pFuncName = "SmartPhoneSN::SP_META_MODEM_Query_MDIMGType_r()";
                                //goto Err;
                            }
                            memcpy(m_sMdInfo.mdimg_type, pMDImgTypeCnf.mdimg_type, 16);                    
                        #endif				
                        }   
                        else
                        {
                            pFuncName = "SmartPhoneSN::SP_META_ConnectInMetaModeByUSB_r()";
                            goto Err;
                        }
                    }//end if(TryToOpenSPKernelComport(kernelComport) == OK)
                }//end if (g_sMetaComm.eTargetType == RNDIG_DONGLE)
                else
                {     
                    iRet = TryToOpenSPKernelComport(kernelComport);
                    if(iRet == OK)
                    {
                        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_ConnectTargetByUsb_r(): Start enter AP meta mode, KernelComPort = %d", kernelComport);
                        iRet = SP_META_Wrapper_ConnectTargetByUsb_r(m_hSPMetaHandle, m_tMetaReq_Ex.ms_connect_timeout, kernelComport);
                        if (iRet == META_SUCCESS /*|| META_MAUI_DB_INCONSISTENT == iRet*/)
                        {                          
                            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_ConnectTargetByUsb_r(): Enter meta successfully!!");
                            
                            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo(): Query modem information start...");
                            iRet = GetSPModemInfo(); 
                            if (iRet == 0)
                            {
                                MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo(): Query modem information successfully!!");
                            } 
                            else
                            {
                                MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo(): Query modem information fail, MetaResult = %s", ResultToString_SP(iRet));
                            }
                            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo(): Query modem information end...");
                        }//end if (iRet == META_SUCCESS)
                        else
                        {
                            pFuncName = "SmartPhoneSN::SP_META_Wrapper_ConnectTargetByUsb_r()";
                            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_ConnectTargetByUsb_r(): enter meta fail, MetaResult = %s", ResultToString_SP(iRet));
                            goto Err;
                        }
                    }//end if(TryToOpenSPKernelComport(kernelComport) == OK)
                } //end else -->if (g_sMetaComm.eTargetType == RNDIG_DONGLE)  
             }//end if (spMetaMode == SP_AP_META)
             else if(spMetaMode == SP_MODEM_META)
             {           
                 usbConnReq.com_port = kernelComport;
                 usbConnReq.ms_connect_timeout = m_tMetaReq_Ex.ms_connect_timeout;
                 MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::META_ConnectInMetaModeByUSB_r(): Start enter modem meta mode, KernelComPort = %d", kernelComport);  
                 iRet = META_ConnectInMetaModeByUSB_r(m_hMauiMetaHandle, &usbConnReq, m_pMetaStopFlag, &usbConnReport);
                 if (iRet == META_SUCCESS /*|| iRet == META_MAUI_DB_INCONSISTENT*/)
                 {
                     MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::META_ConnectInMetaModeByUSB_r(): enter meta success!!");
                 }   
                 else
                 {
                     MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::META_ConnectInMetaModeByUSB_r(): enter meta fail, MetaResult = %s", ResultToString(iRet));
                 } 
             }       
       }
       else
       {
           //MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_GetDynamicUSBComPort_r() fail, MetaResult = %s", ResultToString_SP(iRet));
           MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_GetIncrementCOMPortWithFilter(): Get kernel comport fail, iRet = %d", iRet);
       }
    } //end if (g_sMetaComm.bUsbEnable)
    else
    {
        kernelComport = g_sMetaComm.iCOMPort;
		m_iKernelComport = kernelComport;
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_ConnectTargetByUart_r(): Start enter AP meta mode, KernelComPort = %d", kernelComport);
        iRet = SP_META_Wrapper_ConnectTargetByUart_r(m_hMauiMetaHandle, m_tMetaReq_Ex.ms_connect_timeout, kernelComport);
        if (iRet == META_SUCCESS)
        {                          
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_ConnectTargetByUart_r(): Enter meta successfully!!");
            
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo(): Query modem information start...");
            iRet = GetSPModemInfo(); 
            if (iRet == 0)
            {
                MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo(): Query modem information successfully!!");
            } 
            else
            {
                MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo(): Query modem information fail, MetaResult = %s", ResultToString_SP(iRet));
            }
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo(): Query modem information end...");
        }//end if (iRet == META_SUCCESS)
        else
        {
            pFuncName = "SmartPhoneSN::SP_META_Wrapper_ConnectTargetByUart_r()";
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Wrapper_ConnectTargetByUart_r(): enter meta fail, MetaResult = %s", ResultToString_SP(iRet));
            goto Err;
        } 
    }
        
    return iRet;
    
Err:
    MTRACE_ERR(g_hEBOOT_DEBUG, "%s: MetaResult = %s", pFuncName, ResultToString_SP(iRet));
    return iRet;
}

int SmartPhoneSN::ConnectWithPreloader()
{
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::ConnectWithPreloader(): Start to get dynamic preloader comport...");

    SP_COM_FILTER_LIST_S sCOMFilter;
    SP_COM_PROPERTY_S sCOMProperty;   
    memset(&sCOMFilter, 0, sizeof(SP_COM_FILTER_LIST_S));
    memset(&sCOMProperty, 0, sizeof(SP_COM_PROPERTY_S));

    int iRet = 0;
    unsigned int eType;   //0:BoorROMUSB,1:PreloaderUSB
    char *ppFilter[2];
    //char *asPreloaderPortFilter = "VID_0E8D&PID_2000";
    //char *asBROMPortFilter = "VID_0E8D&PID_0003";

    char *asPreloaderPortFilter = g_sMetaComm.sPortFilter.strPreloaderFilter;
    char *asBROMPortFilter = g_sMetaComm.sPortFilter.strBromFilter;

    ppFilter[0]=asPreloaderPortFilter;
	ppFilter[1]=asBROMPortFilter;
   
    sCOMFilter.m_uCount=2;
    sCOMFilter.m_ppFilterID=ppFilter;
	sCOMFilter.m_eType=SP_WHITE_LIST;

    if (g_sMetaComm.bUsbEnable == false)
    {
        m_stModeArg.m_uPortNumber = g_sMetaComm.iCOMPort;
        eType = PreloaderUSB;
    } 
    else
    {     
        int iTimeout = m_stModeArg.m_uTimeout / 1000;  //timeout unit: s, but m_stModeArg.m_uTimeout unit is ms
        iRet = SP_GetIncrementCOMPortWithFilter(&sCOMFilter, &sCOMProperty, NULL, _TRUE, m_pMetaStopFlag, iTimeout);              
        if(0 == iRet)
        {      
            m_bStopBeforeUSBInsert = false;
            switch(sCOMProperty.m_iFilterIndex)
            {
            case 0:
                eType = PreloaderUSB;
                break;

            case 1:
                eType = BootROMUSB;
                break;

            default:
                //MessageBox (NULL, "Filter index error!", "fail", MB_OK);
                return SPMETA_DLL::META_FAILED;
            }
            
            m_stModeArg.m_uPortNumber = sCOMProperty.m_uNumber;
        }
        else
        {
            if (iRet == SP_S_TIMEOUT)
            {
                sprintf(m_strMsg, "SmartPhoneSN::ConnectWithPreloader(): Get dynamic preloader comport timeout...");
                MTRACE(g_hEBOOT_DEBUG, "%s", m_strMsg);
                PopupMsgBox(m_strMsg, "Error");
            }

            return iRet;
        }
    }
   
    Sleep (0.01);
    if(BootROMUSB == eType)
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::ConnectWithPreloader(): Get preloader comport successfully, comport = %d", m_stModeArg.m_uPortNumber);
        iRet = SP_BootROM_BootMode(&m_stModeArg);       
        if (iRet == 0)
        {
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_BootROM_BootMode(): Preloader boot meta mode success!!");
        }   
        else
        {
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_BootROM_BootMode(): Preloader boot meta mode Fail, Err = %d", iRet);
        }

        m_bStopBeforeUSBInsert = false;
    }
    else if(PreloaderUSB == eType)
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::ConnectWithPreloader(): Get preloader comport successfully, comport = %d", m_stModeArg.m_uPortNumber);
        iRet = SP_Preloader_BootMode(&m_stModeArg);
        if (iRet == 0)
        {
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_Preloader_BootMode(): Preloader boot meta mode success!!");
        }   
        else
        {
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_Preloader_BootMode(): Preloader boot meta mode Fail, Err = %d", iRet);
        }

        m_bStopBeforeUSBInsert = false;
    }
    
   
    return iRet;
}

void SmartPhoneSN::ModemMetaHandle_DeInit()
{
    META_Deinit_r(&m_hMauiMetaHandle);
}

void SmartPhoneSN::APMetaHandle_DeInit()
{
    SPMETA_DLL::SP_META_Deinit_r(&m_hSPMetaHandle);
}

SPMETA_DLL::META_RESULT SmartPhoneSN::APMetaHandle_Init()
{
    SPMETA_DLL::META_RESULT spMetaResult = SPMETA_DLL::META_SUCCESS;
    spMetaResult = SPMETA_DLL::SP_META_GetAvailableHandle ( &m_hSPMetaHandle );
    if (spMetaResult != SPMETA_DLL::META_SUCCESS )
    {     
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_GetAvailableHandle(): Get available AP handle fail, MetaResult = %s",ResultToString_SP(spMetaResult));
        return spMetaResult;
    } 
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_GetAvailableHandle(): Get available AP handle success");
    
    spMetaResult = SPMETA_DLL::SP_META_Init_r (m_hSPMetaHandle , NULL);
    if ( spMetaResult != META_SUCCESS)
    {     
        MTRACE_ERR(g_hEBOOT_DEBUG, "SP_META_Init_r(): Init AP handle fail, MetaResult = %s", ResultToString_SP(spMetaResult));
        return spMetaResult;
    }
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Init_r(): Init AP handle success");
    
    return SPMETA_DLL::META_SUCCESS;
}

META_MD_Query_Result_T __stdcall MdQueryHandler(void* MdQuery_CB_Arg)
{
    SP_MODEMInfo_s *sMdInfo = (SP_MODEMInfo_s*)MdQuery_CB_Arg;
    META_MD_Query_Result_T result;  
      
    result.number_of_md = sMdInfo->number_of_md;
    result.active_md_idx = sMdInfo->active_md_idx - 1;
    result.number_of_mdSwImg = sMdInfo->number_of_mdSwImg;
    result.active_mdtype_idx = sMdInfo->activeMdTypeIdx;
    result.multi_talk = (result.active_md_idx != 0 || result.number_of_md >= 2)?TRUE:FALSE;
    result.multi_frame_type = 1;   
    
    //result.multi_mdtype = (sMdInfo->current_mdtype != 0 && result.number_of_mdSwImg >= 2)?TRUE:FALSE;
    result.multi_mdtype = (result.number_of_mdSwImg > result.number_of_md) ? true : false;//zishuo modify
    result.multi_md_capability_support = sMdInfo->multi_md_capability_support; 
    result.reserved = 5;
    
    return result;
}

int __stdcall MdTypeSwitchHandler(META_MDTYPE_Switch_Param_T mdtype_switch_param, void* MdTypeSwitch_CB_Arg)
{
    return 1;
}

void SmartPhoneSN::MetaHandle_DeInit()
{
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::MetaHandle_DeInit() : DeInit meta handle start...");
    if (m_hMauiMetaHandle != INVALID_META_HANDLE)
    {
        ModemMetaHandle_DeInit();
        m_hMauiMetaHandle = INVALID_META_HANDLE;
    }
    
    if (m_hSPMetaHandle != INVALID_META_HANDLE)
    {
        APMetaHandle_DeInit();
        m_hSPMetaHandle = INVALID_META_HANDLE;
    }
    
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::MetaHandle_DeInit() : DeInit meta handle end...");
}

META_RESULT SmartPhoneSN::ModemMetaHandle_Init()
{
    META_RESULT meta_result = META_SUCCESS;    
    meta_result = META_GetAvailableHandle( &m_hMauiMetaHandle );
    if(meta_result != META_SUCCESS)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::META_GetAvailableHandle(): Get available modem meta handle fail, MetaResult = %s", ResultToString(meta_result));
        return meta_result;
    }
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_GetAvailableHandle(): Get available modem meta handle success!");
   
    /*
    if (g_sMetaComm.eTargetType == SMART_PHONE_DUALMODEM)
    {
        meta_result =  META_Init_Ex_r( m_hMauiMetaHandle, NULL, MdQueryHandler, NULL, NULL, NULL);
    }
    else
    {
        meta_result = META_Init_Ex_2_r( m_hMauiMetaHandle, NULL, MdQueryHandler, NULL, NULL, NULL, MdTypeSwitchHandler, NULL);
    }
    */
    meta_result = META_Init_Ex_2_r( m_hMauiMetaHandle, NULL, MdQueryHandler, (void*)&m_sMdInfo, NULL, NULL, MdTypeSwitchHandler, NULL);
    if(meta_result != META_SUCCESS)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::META_Init_Ex_2_r(): Init modem meta handle fail, MetaResult = %s", ResultToString(meta_result));
        return meta_result;
    }
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::META_Init_Ex_2_r(): Init modem meta handle success!");
        
    return meta_result;
}

META_RESULT SmartPhoneSN::MetaHandle_Init()
{
    META_RESULT meta_result; 
    SPMETA_DLL::META_RESULT spMetaResult;
    
    if (m_hMauiMetaHandle == INVALID_META_HANDLE)
    {
        meta_result = ModemMetaHandle_Init();
        if (meta_result != META_SUCCESS)
        {
            return meta_result;
        }
    }
        
    if (m_hSPMetaHandle == INVALID_META_HANDLE)
    {
        spMetaResult = APMetaHandle_Init();
        if (spMetaResult != SPMETA_DLL::META_SUCCESS)
        {
            meta_result = (META_RESULT)spMetaResult;
            return meta_result;
        }
    }
     
    return META_SUCCESS;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_ReadFromAPNVRAM(SPMETA_DLL::FT_NVRAM_READ_REQ *psNVRAM_ReadReq, SPMETA_DLL::FT_NVRAM_READ_CNF *psNVRAM_ReadCnf)
{
    DWORD wait_result;
    short iNVRAM_OPID;
    SPMETA_DLL::META_RESULT MetaResult;
    
    m_hReadFromNVRAMEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    
    ResetEvent ( m_hReadFromNVRAMEvent );
    
    
    MetaResult = SPMETA_DLL::SP_META_NVRAM_Read_r ( m_hSPMetaHandle,
        psNVRAM_ReadReq,
        psNVRAM_ReadCnf,
        CNF_SPReadFromNVRAM,
        &iNVRAM_OPID,
        (void*)&m_hReadFromNVRAMEvent );
    
    
    wait_result = WaitForSingleObject ( m_hReadFromNVRAMEvent, 15000 );
    
    if ( WAIT_TIMEOUT == wait_result )
    {
        return SPMETA_DLL::META_TIMEOUT;
    }
    else if(WAIT_OBJECT_0)
    {
        CloseHandle (m_hReadFromNVRAMEvent);
    }
    
    if ( MetaResult != SPMETA_DLL::META_SUCCESS )
    {
        return MetaResult;
    }
    
    return SPMETA_DLL::META_SUCCESS;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_BackupNvram2BinRegion_Start(int BackUpOption)
{
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_BackupNvram2BinRegion_Start() : Backup nvram to BinRegion start, BackupOption = %d...", BackUpOption);
    sprintf(m_strMsg, "Start backup nvram to BinRegion...");
    UpdateMsgInfo(m_strMsg);

    SPMETA_DLL::META_RESULT spMetaResult = SPMETA_DLL::META_SUCCESS;
    SPMETA_DLL::SetCleanBootFlag_REQ req;
    SPMETA_DLL::SetCleanBootFlag_CNF cnf;   
    req.Notused = BackUpOption;

    spMetaResult =  SPMETA_DLL::SP_META_SetCleanBootFlag_r ( m_hSPMetaHandle, 15000, &req, &cnf );
    if (spMetaResult == SPMETA_DLL::META_SUCCESS)
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_SetCleanBootFlag_r() : Backup nvram successfully!!");
    } 
    else
    {
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_SetCleanBootFlag_r() : Backup nvram Fail!! MetaResult = %s", ResultToString_SP(spMetaResult));
    }

    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_BackupNvram2BinRegion_Start() : Backup nvram to BinRegion end...");
    return spMetaResult;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::ConductProdInfoData(unsigned char *pOutData, const char *pBarcodeData, const char (*pIMEIData)[IMEI_ARRAY_LEN], int iIMEINums, char *pBtAddr, char *pWiFiAddr, char *pReserved, int bufSize)
{
    if (g_sMetaComm.sWriteOption.bWriteBarcode)
    {
        if (pBarcodeData == NULL || strlen(pBarcodeData) == 0)
        {
            return SPMETA_DLL::META_INVALID_ARGUMENTS;
        }
        else
        {
            memcpy(pOutData, pBarcodeData, 64);
        }
    }
    
    int offset = 64;//64Bytes storage barcode string
    if (g_sMetaComm.sWriteOption.bWriteIMEI)
    {       
        int imeiIndex = 0;      
		char  tmpCh;	

        for (imeiIndex = 0; imeiIndex < iIMEINums; imeiIndex++)
        {
            if (pIMEIData[imeiIndex] == NULL || strlen(pIMEIData[imeiIndex]) == 0)
            {
                return SPMETA_DLL::META_INVALID_ARGUMENTS;
            }
            else
            {
                for (int index = 0; index < 7; index++)
                {
                    tmpCh = pIMEIData[imeiIndex][index*2 + 1] - '0';
                    tmpCh = ((tmpCh << 4) & 240); //240 -->11110000	
                                  
                    tmpCh += pIMEIData[imeiIndex][index*2] - '0';
                    pOutData[offset+index] = tmpCh;		  
                }
                
                tmpCh = 15; //15 --> 00001111
                tmpCh = tmpCh << 4; //15<<4  --> 11110000
                tmpCh += pIMEIData[imeiIndex][14] - '0'; //checkSum bit
                pOutData[offset+7] = tmpCh;
                
                offset += 10;  //next IMEI field
            }
        }   
    }

    //64: storage barcode string
    //4*10: storage four imei data
    //6 + 6: BT/Wifi Address
    
    offset = (64+ 4*10);
	//0x1234.... btaddress[0]=12, btaddress[1]=34...
	if(g_sMetaComm.sWriteOption.bWriteBT)
	{
	    char  tmpCh;
	    if (pBtAddr == NULL || strlen(pBtAddr) == 0)
        {
            return SPMETA_DLL::META_INVALID_ARGUMENTS;
        }
		else
		{
		    for (int i = 0; i < 6; i++)
            {
                if ('0'<= pBtAddr[i*2] && pBtAddr[i*2] <= '9')
                {
                    tmpCh = pBtAddr[i*2] - '0';
                    tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
                }
                else if('A'<= pBtAddr[i*2] && pBtAddr[i*2] <= 'F')
                {
                    tmpCh = pBtAddr[i*2] - 'A' + 10;
                    tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
                }
                
                if ('0'<= pBtAddr[(i*2 + 1)] && pBtAddr[(i*2 + 1)] <= '9')
                {
                    tmpCh += pBtAddr[(i*2 + 1)] - '0'; //get Low 4bits
                } 
                else if('A'<= pBtAddr[(i*2 + 1)] && pBtAddr[(i*2 + 1)] <= 'F')
                {
                    tmpCh += pBtAddr[(i*2 + 1)] - 'A' + 10; //get Low 4bits
                }
                
                pOutData[offset + i] = tmpCh;
		   }
	    }
     }
	
	offset = (64 + 4*10 + 6);
	//wifi 0x123456.... bwifiaddr[0]=12,bwifiaddr[1]=34...
	if (g_sMetaComm.sWriteOption.bWriteWifi)
    {
        char  tmpCh;
        if (pWiFiAddr == NULL || strlen(pWiFiAddr) == 0)
        {
            return SPMETA_DLL::META_INVALID_ARGUMENTS;
        }
        else
        {
			for (int i = 0; i < 6; i++)
			{
				  if ('0'<= pWiFiAddr[i*2] && pWiFiAddr[i*2] <= '9')
				  {
					  tmpCh = pWiFiAddr[i*2] - '0';
					  tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
				  }
				  else if('A'<= pWiFiAddr[i*2] && pWiFiAddr[i*2] <= 'F')
				  {
					  tmpCh = pWiFiAddr[i*2] - 'A' + 10;
					  tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
				  }
				  
				  if ('0'<= pWiFiAddr[(i*2 + 1)] && pWiFiAddr[(i*2 + 1)] <= '9')
				  {
					  tmpCh += pWiFiAddr[(i*2 + 1)] - '0'; //get Low 4bits
				  } 
				  else if('A'<= pWiFiAddr[(i*2 + 1)] && pWiFiAddr[(i*2 + 1)] <= 'F')
				  {
					  tmpCh += pWiFiAddr[(i*2 + 1)] - 'A' + 10; //get Low 4bits
				  }
				  
				  pOutData[offset + i] = tmpCh;
			}
			
        }
    }
    offset = (64 + 4*10 + 6 + 6);
    if (g_sMetaComm.sWriteOption.bWriteSerialNo)
    {
        if (pReserved == NULL || strlen(pReserved) == 0)
        {
            return SPMETA_DLL::META_INVALID_ARGUMENTS;
        }
        else
        {
            memcpy(pOutData+offset, pReserved, 15);
        }
    }
    
    return SPMETA_DLL::META_SUCCESS;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_WriteAP_PRODINFO_Start(char *pBarcode, char (*pIMEI)[IMEI_ARRAY_LEN], char *pBtAddr, char *pWifiAddr, char *pReserved)
{
    SPMETA_DLL::META_RESULT meta_result = SPMETA_DLL::META_SUCCESS;
	m_bWriteNvram = true;
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteAP_PRODINFO_Start(): Write Barcode/Imei/Bt/Wifi/Serial.No to prod_info start...");

    int iIMEINums = g_sMetaComm.sIMEIOption.iImeiNums;
    int iMetaTimeout = 5000;
    int iWriteBufSize = 0;
    char *pLID = "AP_CFG_REEB_PRODUCT_INFO_LID";
    char *pFuncName = NULL;
	unsigned char *pWriteData = NULL;
    
    SPMETA_DLL::FT_NVRAM_WRITE_REQ sNVRAM_WriteReq;
    SPMETA_DLL::FT_NVRAM_READ_REQ sNVRAM_ReadReq;
    SPMETA_DLL::FT_NVRAM_READ_CNF sNVRAM_ReadCnf;
    if (g_sMetaComm.sWriteOption.bWriteBarcode)
    {
        if (pBarcode == NULL || strlen(pBarcode) == 0)
        {
            return SPMETA_DLL::META_INVALID_ARGUMENTS;
        }
		else
		{
			MTRACE(g_hEBOOT_DEBUG, "Prod_Info->Barcode = [%s]", pBarcode);
		}
    }
    
    if (g_sMetaComm.sWriteOption.bWriteIMEI)
    {
        for (int i = 0; i < g_sMetaComm.sIMEIOption.iImeiNums; i++)
        {
            if (pIMEI[i] == NULL || strlen(pIMEI[i]) == 0)
            {
				MTRACE(g_hEBOOT_DEBUG, "i = %d", i);
                return SPMETA_DLL::META_INVALID_ARGUMENTS;
            }
            else
            {
                MTRACE(g_hEBOOT_DEBUG, "Prod_Info->IMEI[%d] = [%s]", i, pIMEI[i]);
            }
        }  
    }  
    if (g_sMetaComm.sWriteOption.bWriteBT)
    {
        if (pBtAddr == NULL || strlen(pBtAddr) == 0)
        {
            return SPMETA_DLL::META_INVALID_ARGUMENTS;
        }
		else
		{
			MTRACE(g_hEBOOT_DEBUG, "Prod_Info->BtAddress = [%s]", pBtAddr);
		}
    }
    if (g_sMetaComm.sWriteOption.bWriteWifi)
    {
        if (pWifiAddr == NULL || strlen(pWifiAddr) == 0)
        {
            return SPMETA_DLL::META_INVALID_ARGUMENTS;
        }
		else
		{
			MTRACE(g_hEBOOT_DEBUG, "Prod_Info->WiFiAddress = [%s]", pWifiAddr);
		}
    }


    if (g_sMetaComm.sWriteOption.bWriteSerialNo)
    {            
        if (pReserved == NULL || strlen(pReserved) == 0)
        {
            return SPMETA_DLL::META_INVALID_ARGUMENTS;
        }
        else
        {
            MTRACE(g_hEBOOT_DEBUG, "Prod_Info->pReserved = [%s]", pReserved);
		}       
    }  

    memset(&sNVRAM_WriteReq, 0, sizeof(SPMETA_DLL::FT_NVRAM_WRITE_REQ));
    memset(&sNVRAM_ReadReq, 0, sizeof(SPMETA_DLL::FT_NVRAM_READ_REQ));
    memset(&sNVRAM_ReadCnf, 0, sizeof(SPMETA_DLL::FT_NVRAM_READ_CNF));

    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Start to get nvram struct size via LID = \"%s\"...", pLID);
    meta_result = SPMETA_DLL::SP_META_NVRAM_GetRecLen(pLID, &iWriteBufSize);
    if (  SPMETA_DLL::META_SUCCESS != meta_result)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Get nvram struct size fail, MetaResult = %s", ResultToString_SP(meta_result));
        return meta_result;
    }
    else
    {
        MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Get nvram struct size = %d successfully!", iWriteBufSize);
        if ( NULL != sNVRAM_ReadCnf.buf )
        {
            free ( sNVRAM_ReadCnf.buf );	
            sNVRAM_ReadCnf.buf = NULL;
        }

		if(NULL != pWriteData)
		{
		    free ( pWriteData );	
            pWriteData = NULL;
		}		
        
        sNVRAM_ReadReq.LID = pLID;
        sNVRAM_ReadReq.RID = 1;
        sNVRAM_ReadCnf.len = iWriteBufSize;
        sNVRAM_ReadCnf.buf = (unsigned char*) malloc (iWriteBufSize*sizeof(unsigned char));
		pWriteData = (unsigned char*) malloc (iWriteBufSize*sizeof(unsigned char));
        if (NULL == sNVRAM_ReadCnf.buf || NULL == pWriteData)
        {
            MTRACE_ERR (g_hEBOOT_DEBUG, "Malloc heap memory cause fail!");
            return  SPMETA_DLL::META_FAILED;
        }
    }

    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromAPNVRAM(): Start to read nvram data...");        
    meta_result =  REQ_ReadFromAPNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
    if (meta_result != SPMETA_DLL::META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_ReadFromAPNVRAM()";
        goto Err;
    }

    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::ConductProdInfoData(): Conduct Prod_Info nvram data start...");
    meta_result = ConductProdInfoData(sNVRAM_ReadCnf.buf, pBarcode, pIMEI, iIMEINums, pBtAddr, pWifiAddr, pReserved, iWriteBufSize);
    if (meta_result != SPMETA_DLL::META_SUCCESS)
    {
        pFuncName = "SmartPhoneSN::ConductProdInfoData()";
        goto Err;
    }
	else
	{
	    memcpy(pWriteData, sNVRAM_ReadCnf.buf, iWriteBufSize);
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::ConductProdInfoData(): Conduct Prod_Info nvram data successfully!!");
	}

    sNVRAM_WriteReq.LID = pLID;
    sNVRAM_WriteReq.RID = 1;
    sNVRAM_WriteReq.len = iWriteBufSize;
    sNVRAM_WriteReq.buf = pWriteData;
    m_sNVRAM_OPID = 1;
    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Start to write nvram data...");
    meta_result =  REQ_WriteToAPNVRAM(sNVRAM_WriteReq);
    if (meta_result != SPMETA_DLL::META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_WriteToAPNVRAM()";
        goto Err;
    }
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Write nvram data successfully!");

	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Read nvram data for check start...");
    memset(sNVRAM_ReadCnf.buf, 0 , sNVRAM_ReadCnf.len);
	meta_result = REQ_ReadFromAPNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
	if (meta_result != SPMETA_DLL::META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_ReadFromAPNVRAM()";
        goto Err;
    }
	else
	{
		if(memcmp(sNVRAM_ReadCnf.buf, pWriteData, sNVRAM_ReadCnf.len) != 0)
		{		     		    
			MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN: Check prod_info data FAIL!!");
			meta_result = SPMETA_DLL::META_FAILED;
		}
		else
		{		    
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Check prod_info data PASS!!");
		}
	}
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Read nvram data for check end...");
    
    if (sNVRAM_ReadCnf.buf != NULL)
    {
        free (sNVRAM_ReadCnf.buf);
        sNVRAM_ReadCnf.buf = NULL;
    }

	if (pWriteData != NULL)
    {
        free (pWriteData);
        pWriteData = NULL;
    }

    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteAP_PRODINFO_Start(): Write Barcode/Imei/Bt/Wifi/Serial.No to prod_info end...");
    return meta_result;

Err:
    if (sNVRAM_ReadCnf.buf != NULL)
    {
        free (sNVRAM_ReadCnf.buf);
        sNVRAM_ReadCnf.buf = NULL;
    }

	if (pWriteData != NULL)
    {
        free (pWriteData);
        pWriteData = NULL;
    }
    
    MTRACE_ERR (g_hEBOOT_DEBUG, "%s: fail! MetaResult = %s", pFuncName, ResultToString_SP(meta_result));
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteAP_PRODINFO_Start(): Write Barcode/Imei/Bt/Wifi/Serial.No to prod_info end...");
    return meta_result;
}

int SmartPhoneSN::LoadHDCPBinFile(const char *strHdcpBinPath)
{
    int iRet = 0;
    int file_size = 0;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    FILE *fp = NULL;
    
    EN_HDCP_RET retHdcp = R_OK;
    LPWIN32_FIND_DATA file_data;
    
    char tempfile[1024] = {0}; 
    unsigned char bufNoEncrypt[HDCP_KEY_ARRAY_NUMBER_FILE] = {0};
	unsigned char bufEncrypt[HDCP_KEY_ARRAY_NUMBER] = {0};
       
	file_data = (WIN32_FIND_DATA*)malloc(sizeof(WIN32_FIND_DATA));
    sprintf(tempfile,"%s\\*.bin", strHdcpBinPath);
    hFile = FindFirstFile(tempfile,file_data);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        sprintf ( m_strMsg,	 "FAIL: Can`t found Hdcp Key File!!");
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::LoadHDCPBinFile(): Can`t found Hdcp Key File!!");
        iRet = -1;
        goto End;
	}

    sprintf(m_strHdcpFileFullName,"%s\\%s",strHdcpBinPath, file_data->cFileName);
    fp = fopen(m_strHdcpFileFullName,"rb");
    if(fp == NULL)
    {
        sprintf ( m_strMsg,	"FAIL: Can`t Open Hdcp Key File!!");
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::LoadHDCPBinFile(): Can`t Open Hdcp Key File!!");
        iRet = -1;
        goto End;
	}
    fseek(fp,0,SEEK_SET);
    fread(bufNoEncrypt, sizeof(char), 308, fp);
    fseek(fp,0,SEEK_END);
	file_size = ftell(fp);

    /*
    for( i = 0; i < HDCP_KEY_ARRAY_NUMBER_FILE; i++)
    {
        sprintf(strLog,"HDCP: HdcpProcess input bufNoEncrypt[%d]: 0x%2.2X.\n", i, bufNoEncrypt[i]&0xFF);
	}
    */

    retHdcp = HdcpProcess(bufNoEncrypt, bufEncrypt);

End:
    fclose(fp);  
    FindClose( hFile );		   
    memcpy((char*)&m_sHDCPNvramStruct, bufEncrypt, sizeof(bufEncrypt));
	free (file_data);
    return iRet;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_WriteHdcpBinToAPNvram_Start(const char *strHdcpBinPath)
{
    if (!strHdcpBinPath || !strlen(strHdcpBinPath))
    {
        return SPMETA_DLL::META_INVALID_ARGUMENTS;
    }

    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteHdcpBinToAPNvram_Start(): Write Hdcp Bin start...");
    int i = 0;
    int iWriteBufSize = 0;
	int iReadBufSize = 0;
    char *pLID = "AP_CFG_RDCL_FILE_HDCP_KEY_LID";
    char *pFuncName = NULL;
    char* m_pcHDCPBuf = NULL;

    SPMETA_DLL::META_RESULT MetaResult = SPMETA_DLL::META_SUCCESS;
    SPMETA_DLL::FT_NVRAM_WRITE_REQ sNVRAM_WriteReq;  	
    SPMETA_DLL::FT_NVRAM_READ_REQ sNVRAM_ReadReq;
	SPMETA_DLL::FT_NVRAM_READ_CNF sNVRAM_ReadCnf;
    memset(&sNVRAM_WriteReq, 0, sizeof(SPMETA_DLL::FT_NVRAM_WRITE_REQ)); 
    memset(&m_sHDCPNvramStruct, 0, sizeof(m_sHDCPNvramStruct));
    memset(&sNVRAM_ReadReq, 0, sizeof(SPMETA_DLL::FT_NVRAM_READ_REQ));
    memset(&sNVRAM_ReadCnf, 0, sizeof(SPMETA_DLL::FT_NVRAM_READ_CNF));

	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Start to get nvram struct size via LID = \"%s\"...", pLID);

    MetaResult = SPMETA_DLL::SP_META_NVRAM_GetRecLen ( pLID, &iWriteBufSize );
    if ( MetaResult != SPMETA_DLL::META_SUCCESS )
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Get nvram struct size fail, MetaResult = %s", ResultToString_SP(MetaResult));
        return MetaResult;
    }   
    else
    {
        m_pcHDCPBuf = (char*)malloc(iWriteBufSize * sizeof(char));
        if (!m_pcHDCPBuf)
        {
            MTRACE_ERR (g_hEBOOT_DEBUG, "Malloc heap memory cause fail!");
            return SPMETA_DLL::META_FAILED;
        }
    }
    

    //load hdcp file
    if(LoadHDCPBinFile(strHdcpBinPath) == -1)
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteHdcpBinToAPNvram_Start(): Write Hdcp Bin end...");
        goto End;
    }

    MetaResult = SPMETA_DLL::SP_META_NVRAM_Compose_HDCP(&m_sHDCPNvramStruct, m_pcHDCPBuf, iWriteBufSize);   
    if (MetaResult != SPMETA_DLL::META_SUCCESS)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_Compose_HDCP(): Compose hdcp data fail, MetaResult = %s", ResultToString_SP(MetaResult));
        goto End;
    }
  	   
    sNVRAM_WriteReq.LID = pLID;
    sNVRAM_WriteReq.RID = 1;
    sNVRAM_WriteReq.len = iWriteBufSize;
    sNVRAM_WriteReq.buf = (unsigned char *)m_pcHDCPBuf;
    
    MetaResult = REQ_WriteToAPNVRAM(sNVRAM_WriteReq);
    if (MetaResult != SPMETA_DLL::META_SUCCESS )
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Write hdcp key to nvram data Fail, MetaResult = %s", ResultToString_SP(MetaResult));
        goto End;
    }
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Write hdcp key to nvram data successfully!");
	
    //read hdcp 12.11 add by mtk71596
    iReadBufSize = iWriteBufSize;
    sNVRAM_ReadReq.LID = pLID;
    sNVRAM_ReadReq.RID = 1;
    sNVRAM_ReadCnf.len = iReadBufSize;
    sNVRAM_ReadCnf.buf = (unsigned char *)m_pcHDCPBuf;
    if (NULL == sNVRAM_ReadCnf.buf)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "Malloc heap memory cause fail!");
        goto End;
    }
    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromAPNVRAM(): Start to read nvram data...");        
    MetaResult =  REQ_ReadFromAPNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
    if (MetaResult != SPMETA_DLL::META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_ReadFromAPNVRAM()";
        goto End;
    }
    MetaResult = SPMETA_DLL::SP_META_NVRAM_Decompose_HDCP(&m_sReadBackHdcp, m_pcHDCPBuf, iReadBufSize);
    
    for(i=0; i<287; i++)
    {
        if(m_sHDCPNvramStruct.HdcpKeyArray[i]!=m_sReadBackHdcp.HdcpKeyArray[i])
        {
            MTRACE (g_hEBOOT_DEBUG, "Fail:The Key Read back is not the same as the write \n");		 
            goto End;			 
        }		 
    }
    
    remove(m_strHdcpFileFullName);	 
    MTRACE (g_hEBOOT_DEBUG, "OK: Write HDCP Key File\n"); 	 	 
    
End:
    if (m_pcHDCPBuf != NULL)
    {
        free (m_pcHDCPBuf);
        m_pcHDCPBuf = NULL;
    }
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteHdcpBinToAPNvram_Start(): Write Hdcp Bin end...");
    return MetaResult;
}


SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_WriteTemperatureToNvram_Start(float * Temperature)
{
   if (NULL == Temperature)
    {
        return SPMETA_DLL::META_INVALID_ARGUMENTS;
    }

    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteTemperatureToNvram_Start(): Write Temperature start...");
    char *pLID = "AP_CFG_RDCL_FILE_AUDIO_SPEAKER_MONITOR_LID";
    unsigned char* pTempBuf = NULL;
	int iWriteBufSize = 0;
	char *pFuncName = NULL;
    unsigned char Temp[5] = {0};

    SPMETA_DLL::META_RESULT MetaResult = SPMETA_DLL::META_SUCCESS;
    SPMETA_DLL::FT_NVRAM_WRITE_REQ sNVRAM_WriteReq;  	
    SPMETA_DLL::FT_NVRAM_READ_REQ sNVRAM_ReadReq;
	SPMETA_DLL::FT_NVRAM_READ_CNF sNVRAM_ReadCnf;
	
	AUDIO_SPREAKER_MONITOR_PARAM_STRUCT WriteTempStruct;
	
    memset(&sNVRAM_WriteReq, 0, sizeof(SPMETA_DLL::FT_NVRAM_WRITE_REQ)); 
    memset(&sNVRAM_ReadReq, 0, sizeof(SPMETA_DLL::FT_NVRAM_READ_REQ));
    memset(&sNVRAM_ReadCnf, 0, sizeof(SPMETA_DLL::FT_NVRAM_READ_CNF));

    MetaResult = SPMETA_DLL::SP_META_NVRAM_GetRecLen ( pLID, &iWriteBufSize );
    if ( MetaResult != SPMETA_DLL::META_SUCCESS )
    {
        goto End;
    }  

	pTempBuf = (unsigned char*) malloc (iWriteBufSize*sizeof(unsigned char));

    sNVRAM_ReadReq.LID = pLID;
    sNVRAM_ReadReq.RID = 1;
    sNVRAM_ReadCnf.len = iWriteBufSize;
    sNVRAM_ReadCnf.buf = pTempBuf;

    if (NULL == sNVRAM_ReadCnf.buf || NULL == pTempBuf)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "Malloc heap memory cause fail!");
        return  SPMETA_DLL::META_FAILED;
    }
    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromAPNVRAM(): Start to read nvram data...");        
    MetaResult =  REQ_ReadFromAPNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
    if (MetaResult != SPMETA_DLL::META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_ReadFromAPNVRAM()";
        goto End;
    }

	//add start
	memcpy(&WriteTempStruct,sNVRAM_ReadCnf.buf,iWriteBufSize);
	WriteTempStruct.temp_initial = *Temperature;
	memcpy(sNVRAM_ReadCnf.buf,&WriteTempStruct,iWriteBufSize);
	memcpy(pTempBuf, sNVRAM_ReadCnf.buf, iWriteBufSize);
	//add end
  	   
    sNVRAM_WriteReq.LID = pLID;
    sNVRAM_WriteReq.RID = 1;
    sNVRAM_WriteReq.len = iWriteBufSize;
    sNVRAM_WriteReq.buf = (unsigned char *)pTempBuf;
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromAPNVRAM(): Start to write nvram data...");
    MetaResult = REQ_WriteToAPNVRAM(sNVRAM_WriteReq);
    if (MetaResult != SPMETA_DLL::META_SUCCESS )
    {
        MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Write nvram data Fail!!");
        goto End;
    }
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Write nvram data successfully!");
	
  
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromAPNVRAM(): Start to read nvram data for check...");  

	memset(sNVRAM_ReadCnf.buf, 0 , sNVRAM_ReadCnf.len);
    MetaResult =  REQ_ReadFromAPNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
    if (MetaResult != SPMETA_DLL::META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_ReadFromAPNVRAM()";
        goto End;
    }
	else
	{
		if(memcmp(sNVRAM_ReadCnf.buf, pTempBuf, sNVRAM_ReadCnf.len) != 0)
		{		     		    
			MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN: Check Temperature data FAIL!!");
			MetaResult = SPMETA_DLL::META_FAILED;
			goto End;
		}
		else
		{		    
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Check Temperature data PASS!!");
		}
	}

	if (pTempBuf != NULL)
    {
        free (pTempBuf);
        pTempBuf = NULL;
    }	

End:
    if (pTempBuf != NULL)
    {
        free (pTempBuf);
        pTempBuf = NULL;
    }
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteTemperatureToNvram_Start(): Write Temperature end...");
    return MetaResult;
}

int SmartPhoneSN::LoadDRMKeyFile(const char *strDrmKeyFilePath)
{
    LPWIN32_FIND_DATA files_data;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    char tempfile[1024] = {0}; 
    int rRet = 0;
    bool bFirstTime = true;
    
    files_data = (WIN32_FIND_DATAA*)malloc(sizeof(WIN32_FIND_DATA));
    memset(files_data, 0, sizeof(LPWIN32_FIND_DATA));
   
    sprintf(tempfile,"%s\\*.*",strDrmKeyFilePath);
   
    hFile = FindFirstFile(tempfile,files_data);
    if (INVALID_HANDLE_VALUE == hFile) 
    {
        rRet = -1; 
        goto err;
    }

    
    while( hFile != INVALID_HANDLE_VALUE )
    {      
        if( !FindNextFile(hFile, files_data)) 
        {
            char strMsg[256] = {0};
            sprintf(strMsg, "Can`t find any key file in %s...", strDrmKeyFilePath);
            MTRACE_ERR(g_hEBOOT_DEBUG, strMsg);
            *m_pMetaStopFlag = BOOT_STOP;
            g_pMainDlg->PopupMsgBox(strMsg, "Error", MB_ICONWARNING);  
            rRet = -1;
            goto err;
        }
        else
        {
            if (bFirstTime != true)
            {
                if (strlen(files_data->cFileName))
                {
                    sprintf(m_strDRMFileFullName,"%s\\%s",strDrmKeyFilePath, files_data->cFileName);
                    break;
                }  
            } 
            else
            {
                bFirstTime = false;
            }                    
        }
    }
    
err:	
    free (files_data);
    FindClose( hFile );	
	return rRet;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_WriteDRMKeyMCID_Start(const char *strDrmKeyMCIDData)
{
    if (!strDrmKeyMCIDData || strlen(strDrmKeyMCIDData) != DRMKEY_MCID_LENGTH)
    {
        return SPMETA_DLL::META_INVALID_ARGUMENTS;
    }

    

    SPMETA_DLL::META_RESULT MetaResult = SPMETA_DLL::META_SUCCESS;
    SPMETA_DLL::DRMKEY_WRITE_MCID_REQ pWriteReq;
    SPMETA_DLL::DRMKEY_WRITE_MCID_CNF pWriteCnf;
    SPMETA_DLL::DRMKEY_READ_MCID_REQ pReadReq;
    SPMETA_DLL::DRMKEY_READ_MCID_CNF pReadCnf;

    memset(&pWriteReq, 0, sizeof(SPMETA_DLL::DRMKEY_WRITE_MCID_REQ));
    memset(&pWriteCnf, 0, sizeof(SPMETA_DLL::DRMKEY_WRITE_MCID_CNF));
    memset(&pReadReq, 0, sizeof(SPMETA_DLL::DRMKEY_READ_MCID_REQ));
    memset(&pReadCnf, 0, sizeof(SPMETA_DLL::DRMKEY_READ_MCID_CNF));

    pWriteReq.keylength = DRMKEY_MCID_LENGTH;
    memcpy(pWriteReq.content, strDrmKeyMCIDData, DRMKEY_MCID_LENGTH);
    pWriteReq.content[DRMKEY_MCID_LENGTH] = '\0';
    MTRACE(g_hEBOOT_DEBUG, "DRMKeyMCID = [%s]", pWriteReq.content);

    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_DRMKey_Write_MCID_r(): Write DRMKeyMCID = [%s] to target start...", pWriteReq.content);
    MetaResult = SPMETA_DLL::SP_META_DRMKey_Write_MCID_r(m_hSPMetaHandle, 5000, &pWriteReq, &pWriteCnf);
    if (MetaResult != SPMETA_DLL::META_SUCCESS)
    {
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_DRMKey_Write_MCID_r(): Write DRMKeyMCID Fail, MetaResult = %s", ResultToString_SP(MetaResult));
        return MetaResult;
    }
    else
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_DRMKey_Write_MCID_r(): Write DRMKeyMCID successfully!!");

        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_DRMKey_Read_MCID_r(): Read DRMKeyMCID from target for check start...");
        MetaResult = SPMETA_DLL::SP_META_DRMKey_Read_MCID_r(m_hSPMetaHandle, 5000, &pReadReq, &pReadCnf);
        if (MetaResult != SPMETA_DLL::META_SUCCESS)
        {
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_DRMKey_Read_MCID_r(): Read DRMKeyMCID Fail, MetaResult = %s", ResultToString_SP(MetaResult));
            return MetaResult;
        }
        else
        {
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Write_DRMKeyMCID[%s]", pWriteReq.content);
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Read_DRMKeyMCID[%s]", pReadCnf.content);
            
            if(memcmp(pReadCnf.content, pWriteReq.content, DRMKEY_MCID_LENGTH) != 0)
            {
                MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN: Check DRMKeyMCID fail!! ");
                return SPMETA_DLL::META_FAILED;
            }
            else
            {
                MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Check DRMKeyMCID Pass!!");
            }
        }
    }

    return SPMETA_DLL::META_SUCCESS;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_ReadDRMKeyMCID_Start(char *strDrmKeyMCIDData)
{
    return SPMETA_DLL::META_SUCCESS;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_InstallDRMKey_Start(const char *strDrmKeyFilePath)
{
    if (!strDrmKeyFilePath || !strlen(strDrmKeyFilePath))
    {
        return SPMETA_DLL::META_INVALID_ARGUMENTS;
    }

    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_InstallDRMKey_Start(): Install DRMKey start...");

    int iRet = 0;
    SPMETA_DLL::META_RESULT MetaResult = SPMETA_DLL::META_SUCCESS;
    SPMETA_DLL::DRMKEY_INSTALL_QUERY_REQ Req;
    SPMETA_DLL::DRMKEY_INSTALL_SET_CNF pCnf;
    SPMETA_DLL::DRMKEY_INSTALL_QUERY_CNF QueCnf;
    memset(&Req,0,sizeof(SPMETA_DLL::DRMKEY_INSTALL_QUERY_REQ));
    memset(&QueCnf,0,sizeof(SPMETA_DLL::DRMKEY_INSTALL_QUERY_CNF));
	memset(&pCnf,0,sizeof(SPMETA_DLL::DRMKEY_INSTALL_SET_CNF));

    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::LoadDRMKeyFile(): start to load DRMKey start...");
    iRet = LoadDRMKeyFile(strDrmKeyFilePath);
    if (iRet == -1)
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::LoadDRMKeyFile(): Load DRM key file fail!!");
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_InstallDRMKey_Start(): Install DRMKey end...");
        return SPMETA_DLL::META_FAILED;
    }
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::LoadDRMKeyFile(): Load DRMKey successfully!!");

    MetaResult =  SPMETA_DLL::SP_META_DRMKey_Install_Set_r(m_hSPMetaHandle, 10000, (const char *)&m_strDRMFileFullName, &pCnf);
    if (MetaResult != SPMETA_DLL::META_SUCCESS)
    {
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_DRMKey_Install_Set_r(): Install DRM key file fail, MetaResult = %s!!", ResultToString_SP(MetaResult));
        return MetaResult;
    }
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_DRMKey_Install_Set_r(): Install DRM key file success!!");
      
    MetaResult = SPMETA_DLL::SP_META_DRMKey_Install_Query_r(m_hSPMetaHandle, 5000, &Req, &QueCnf);
	if(MetaResult != SPMETA_DLL::META_SUCCESS || QueCnf.keycount == 0)
	{	 
        if (QueCnf.keycount == 0)
        {
            MTRACE(g_hEBOOT_DEBUG, "FAIL: QueCnf.keycount = 0,Install DRM key fail .\n");
        }
	   
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_DRMKey_Install_Query_r(): Query DRM key file for check fail, MetaResult = %s!!", ResultToString_SP(MetaResult));
        return MetaResult;
	}    
    else
    {       
        char strRecordFolder[100] = {0};
        GetCurrentDirectory( MAX_PATH, strRecordFolder );
        strcat(strRecordFolder, "\\Record\\");
        
        if (!PathFileExists(strRecordFolder))
        {
            if(!CreateDirectory(strRecordFolder, NULL))
            {
                MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::CreateDirectory(): Create record folder fail...");
                MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_InstallDRMKey_Start(): Install DRMKey end...");
                return SPMETA_DLL::META_FAILED;
            }
        }
        
        int pos = -1;
        CString strTmpFileName = m_strDRMFileFullName;
        strTmpFileName.MakeReverse();
        
        pos = strTmpFileName.FindOneOf("\\");
        if(pos != -1)
        {
            strTmpFileName = strTmpFileName.Left(pos);
        }
        strTmpFileName.MakeReverse();
        

        //Fetch key filename
        char pFileName[100]  = {0};
        strncpy(pFileName, (LPSTR)(LPCTSTR)strTmpFileName, strTmpFileName.GetLength());
        
        //Copy had been written key file to record folder
        strncat(strRecordFolder, pFileName, strlen(pFileName)+1);
        CopyFile(m_strDRMFileFullName, strRecordFolder, NULL);

        //Delete had been written key file from key folder
        remove(m_strDRMFileFullName);

        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_DRMKey_Install_Set_r(): Install DRM_Key[%s] successfully!!", pFileName);
    }
    
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_InstallDRMKey_Start(): Install DRMKey end...");
    return MetaResult;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_InstallHdcpData_Start(const char *strHdcpDataFilePath, const char *strHdcpCekFilePath)
{
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_InstallHdcpData_Start(): Install Hdcp data start...");
    SPMETA_DLL::META_RESULT MetaResult = SPMETA_DLL::META_SUCCESS;
    SPMETA_DLL::HDCP_INSTALL_CNF Cnf;
    memset(&Cnf,0,sizeof(SPMETA_DLL::HDCP_INSTALL_CNF));

    if(!strlen(strHdcpDataFilePath) || !strlen(strHdcpCekFilePath))
    {
        sprintf(m_strMsg, "Error: Invalid HDCP file path");
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_InstallHdcpData_Start(): Invalid HDCP file path");

        MetaResult = SPMETA_DLL::META_INVALID_ARGUMENTS;
        goto End;
    }
    Sleep(2000);
    MetaResult  =  SPMETA_DLL::SP_META_HDCP_Install_r(m_hSPMetaHandle, 5000, strHdcpDataFilePath, strHdcpCekFilePath, &Cnf);
    if((MetaResult == META_SUCCESS) &&  (Cnf.install_result == 0))
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_InstallHdcpData_Start(): Install HDCP data successfully!!");
    }
    else
    {
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_InstallHdcpData_Start(): Install HDCP data Fail, MetaResult = %s", ResultToString_SP(MetaResult));
	}
   Sleep(2000);
End:
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_InstallHdcpData_Start(): Install Hdcp data end...");
    return MetaResult;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_BackupNvram2PC_Start(char* NumFile)
{
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_BackupNvram2PC_Start() : Backup nvram to PC start....");
    sprintf(m_strMsg, "Start backup nvram to PC...");
    UpdateMsgInfo(m_strMsg);
    SPMETA_DLL::META_RESULT spMetaResult = SPMETA_DLL::META_SUCCESS;
	char FolderPath[MAX_PATH];
	char FileFullPath[MAX_PATH];

	char MapFile[MAX_PATH];
	char DatFile[MAX_PATH];
	
	memset(MapFile,0,sizeof(MapFile));
	memset(DatFile,0,sizeof(DatFile));
	
	GetModuleFileName(NULL,FolderPath,MAX_PATH);
   (_tcsrchr(FolderPath,_T('\\')))[1] = 0;
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_BackupNvram2PC_Start() : GetModuleFileName folder path = %s ....", FolderPath);

	sprintf(FileFullPath, "%s\%s", FolderPath, "BackupNvData");
	
    if (!PathFileExists(FileFullPath))
    {
        if(!CreateDirectory(FileFullPath,NULL))
        {
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_BackupNvram2PC_Start() : Can`t create  backup nvram files folder path = %s ....", FileFullPath);
            return SPMETA_DLL::META_FAILED;
        }
    }
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_BackupNvram2PC_Start() : The backup nvram files folder path = %s ....", FileFullPath);
	
    char temp1[10]=".map";
    char temp2[10]=".dat";


    sprintf(MapFile,"%s\\%s%s",FileFullPath,NumFile,temp1);
	MTRACE(g_hEBOOT_DEBUG, "debug!!!SmartPhoneSN::REQ_BackupNvram2PC_Start() : MapFile files folder path = %s ....", MapFile);
	

    sprintf(DatFile,"%s\\%s%s",FileFullPath,NumFile,temp2);
     MTRACE(g_hEBOOT_DEBUG, "debug!!!SmartPhoneSN::REQ_BackupNvram2PC_Start() : DatFile files folder path = %s ....", DatFile);                                           
    spMetaResult = SPMETA_DLL::SP_META_Nvram_Backup_r( m_hSPMetaHandle, 15000, MapFile, DatFile);
    if (spMetaResult == SPMETA_DLL::META_SUCCESS)
    {
         MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Nvram_Backup_r() : Backup nvram to PC successfully!!");
    } 
    else
    {
         MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_Nvram_Backup_r() : Backup nvram to PC Fail!! MetaResult = %s", ResultToString_SP(spMetaResult));
    }

    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_BackupNvram2PC_Start() : Backup nvram to PC end...");
  
    return spMetaResult;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_WriteToAPNVRAM(SPMETA_DLL::FT_NVRAM_WRITE_REQ sNVRAM_WriteReq)
{
    SPMETA_DLL::META_RESULT MetaResult;
    DWORD wait_result;
    short iNVRAM_OPID;
    
    m_hWriteToNVRAMEvent = CreateEvent(NULL, true, false, NULL);
    ResetEvent(m_hWriteToNVRAMEvent);
    
    MetaResult = SPMETA_DLL::SP_META_NVRAM_Write_r(m_hSPMetaHandle,
        &sNVRAM_WriteReq,
        CNF_SPWriteToNVRAM,
        &iNVRAM_OPID,
        (void*)&m_hWriteToNVRAMEvent);
    
    wait_result = WaitForSingleObject(m_hWriteToNVRAMEvent, 15000);
    
    if (WAIT_TIMEOUT == wait_result)
    {
        return SPMETA_DLL::META_TIMEOUT;
    }
    else if(WAIT_OBJECT_0)
    {
        CloseHandle (m_hWriteToNVRAMEvent);
    }
    
    if ( MetaResult != SPMETA_DLL::META_SUCCESS )
    {
        return MetaResult;
    }
    
    return SPMETA_DLL::META_SUCCESS;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::QuerySpeakerCalibrationSupport()
{
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::QuerySpeakerCalibrationSupport(): Query target speaker calibration support yes or no start...");
    SPMETA_DLL::META_RESULT MetaResult = SPMETA_DLL::META_SUCCESS;
       
    MetaResult = SPMETA_DLL::SP_META_QuerySpeakerCalibrationSupport_r(m_hSPMetaHandle, 5000);
    if (MetaResult == SPMETA_DLL::META_SUCCESS)
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_QuerySpeakerCalibrationSupport_r(): Target support speaker calibration, need to write current temperature to nvram!");
    }
    else
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_QuerySpeakerCalibrationSupport_r(): Target don`t support speaker calibration, MetaResult = %s!", ResultToString_SP(MetaResult));
    }
    
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::QuerySpeakerCalibrationSupport(): Query target speaker calibration support yes or no end...");
    return MetaResult;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_ReadAP_NVRAM_Start(WriteData_Type_e dataType, char *pOutData, unsigned short iRID)
{
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadAP_NVRAM_Start()...");
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Read DataType is = %d",dataType); 

    SPMETA_DLL::META_RESULT MetaResult = SPMETA_DLL::META_SUCCESS;   
    int iBufLen = 0;
    char *pLID = NULL;
         
    switch(dataType)
    {       
        case WRITE_BARCODE:
        case WRITE_IMEI:
            pLID = "AP_CFG_REEB_PRODUCT_INFO_LID";		
            break;  

        default:
            return SPMETA_DLL::META_INVALID_ARGUMENTS;
    }
    
    SPMETA_DLL::FT_NVRAM_READ_REQ sNVRAM_ReadReq;
    SPMETA_DLL::FT_NVRAM_READ_CNF sNVRAM_ReadCnf;
    SPMETA_DLL::META_RESULT meta_result;
    int iWriteBufSize = 0;
    memset(&sNVRAM_ReadReq, 0, sizeof(SPMETA_DLL::FT_NVRAM_READ_REQ));
    memset(&sNVRAM_ReadCnf, 0, sizeof(SPMETA_DLL::FT_NVRAM_READ_CNF));

    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Start to get nvram struct size via LID = \"%s\"...", pLID);
    meta_result = SPMETA_DLL::SP_META_NVRAM_GetRecLen(pLID, &iWriteBufSize);
    if (  SPMETA_DLL::META_SUCCESS != meta_result)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Get nvram struct size fail, MetaResult = %s", ResultToString_SP(meta_result));
        return meta_result;
    }
    else
    {
        MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Get nvram struct size = %d successfully!", iWriteBufSize);
        if ( NULL != sNVRAM_ReadCnf.buf )
        {
            free ( sNVRAM_ReadCnf.buf );	
            sNVRAM_ReadCnf.buf = NULL;
        }
        
        sNVRAM_ReadReq.LID = pLID;
        sNVRAM_ReadReq.RID = iRID;
        sNVRAM_ReadCnf.len = iWriteBufSize;
        sNVRAM_ReadCnf.buf = (unsigned char*) malloc (iWriteBufSize*sizeof(unsigned char));
        if (NULL == sNVRAM_ReadCnf.buf)
        {
            MTRACE_ERR (g_hEBOOT_DEBUG, "Malloc heap memory cause fail!");
            return	SPMETA_DLL::META_FAILED;
        }
    }
    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromAPNVRAM(): Start to read nvram data...");		
    meta_result =  REQ_ReadFromAPNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
    
    if (meta_result != SPMETA_DLL::META_SUCCESS )
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "REQ_ReadFromAPNVRAM: fail! MetaResult = %s", ResultToString_SP(meta_result));
        return MetaResult;
    }
    
    if(dataType == WRITE_BARCODE)
    {
        // if(!strcmp(sNVRAM_ReadCnf.buf,"000000000000"))
        {
            int i = 0;
            for(i=0; i<64; i++)
            {   
                if(!((sNVRAM_ReadCnf.buf[i] >= 'a' && sNVRAM_ReadCnf.buf[i] <= 'z')
                    ||(sNVRAM_ReadCnf.buf[i] > 'A' && sNVRAM_ReadCnf.buf[i] < 'Z')                   
                    ||(sNVRAM_ReadCnf.buf[i] >= '0' && sNVRAM_ReadCnf.buf[i] <= '9')))
                {                   
                    break;
                }
                else
                {
                    pOutData[i] = sNVRAM_ReadCnf.buf[i];
                }
            }

            pOutData[i]='\0';
        }   	
    }
    
    if(dataType == WRITE_IMEI)
    {
        for(int i=0; i<8; i++)
        {
            if(((sNVRAM_ReadCnf.buf[64+i] & 15 >='0' && sNVRAM_ReadCnf.buf[64+i] & 15 <='9')
                && ((sNVRAM_ReadCnf.buf[64+i] >> 4) & 15 >='0' 
                && (sNVRAM_ReadCnf.buf[64+i] >> 4) & 240 <='9')))
            {
                break;               
            }
            else
            {
                pOutData[2*i] = (sNVRAM_ReadCnf.buf[64+i] & 15 ) + '0';
            }

            pOutData[2*i+1] = (sNVRAM_ReadCnf.buf[64+i]>>4 & 15) + '0';		 
        }

        pOutData[2*i-1]='\0';
    }
    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadAP_NVRAM_Start() Success...");
    return MetaResult;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::REQ_WriteAP_NVRAM_Start(WriteData_Type_e dataType, char *pInData, unsigned short iRID)
{
     if(!pInData)
    {
        return SPMETA_DLL::META_INVALID_ARGUMENTS;
    }   
    m_bWriteNvram = true;
    
    int iBufLen = 0;
    char *pLID = NULL;
    pConductDataFunc pDataFunc = NULL;
       
    switch(dataType)
    {       
    case WRITE_BT:
        iBufLen = 6;
        pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID";
        pDataFunc = ConductBTAddrData;
        break;
        
    case WRITE_WIFI:
        iBufLen = 6;
        pLID = "AP_CFG_RDEB_FILE_WIFI_LID";
        pDataFunc = ConductWifiAddrData;
        break;

    case WRITE_ETHERNET_MAC:
        iBufLen = 6;
        pLID = "AP_CFG_RDEB_FILE_ETHERNET_LID";
        pDataFunc = ConductEthernetMacAddrData;
        break;

    case WRITE_TEMPERATURE:
        iBufLen = strlen(pInData);
        pLID = "AP_CFG_RDCL_FILE_AUDIO_SPEAKER_MONITOR_LID";
        pDataFunc = ConductAudioTemperatureData;
        break;

    default:
        return SPMETA_DLL::META_INVALID_ARGUMENTS;
    }   

	const int MAX_DATA_LENGTH = 6;
    int iMetaTimeout = 5000;

    SPMETA_DLL::FT_NVRAM_WRITE_REQ sNVRAM_WriteReq;
    SPMETA_DLL::FT_NVRAM_READ_REQ sNVRAM_ReadReq;
	SPMETA_DLL::FT_NVRAM_READ_CNF sNVRAM_ReadCnf;
    SPMETA_DLL::META_RESULT meta_result;
	char pWriteData[MAX_DATA_LENGTH] = {0};
	char pReadData[MAX_DATA_LENGTH] = {0};
    int iWriteBufSize = 0;
	unsigned long wifiChipVersion = 0;
	char *pFuncName = NULL;
    int rs = 0;

    memset(&sNVRAM_WriteReq, 0, sizeof(SPMETA_DLL::FT_NVRAM_WRITE_REQ));
    memset(&sNVRAM_ReadReq, 0, sizeof(SPMETA_DLL::FT_NVRAM_READ_REQ));
    memset(&sNVRAM_ReadCnf, 0, sizeof(SPMETA_DLL::FT_NVRAM_READ_CNF));

	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Start to get nvram struct size via LID = \"%s\"...", pLID);
    meta_result = SPMETA_DLL::SP_META_NVRAM_GetRecLen(pLID, &iWriteBufSize);
    if (  SPMETA_DLL::META_SUCCESS != meta_result)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Get nvram struct size fail, MetaResult = %s", ResultToString_SP(meta_result));
        return meta_result;
    }
    else
    {
        MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_NVRAM_GetRecLen(): Get nvram struct size = %d successfully!", iWriteBufSize);
        if ( NULL != sNVRAM_ReadCnf.buf )
        {
            free ( sNVRAM_ReadCnf.buf );	
            sNVRAM_ReadCnf.buf = NULL;
        }

        sNVRAM_ReadReq.LID = pLID;
        sNVRAM_ReadReq.RID = iRID;
        sNVRAM_ReadCnf.len = iWriteBufSize;
        sNVRAM_ReadCnf.buf = (unsigned char*) malloc (iWriteBufSize*sizeof(unsigned char));
        if (NULL == sNVRAM_ReadCnf.buf)
        {
            MTRACE_ERR (g_hEBOOT_DEBUG, "Malloc heap memory cause fail!");
            return  SPMETA_DLL::META_FAILED;
        }
    }


	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromAPNVRAM(): Start to read nvram data...");        
    meta_result =  REQ_ReadFromAPNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
    if (meta_result != SPMETA_DLL::META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_ReadFromAPNVRAM()";
        goto Err;
    }
 
    
    if (strcmp(pLID, "AP_CFG_RDEB_FILE_WIFI_LID") == 0)
    {   
        MTRACE (g_hEBOOT_DEBUG, "SNBase::ConductWifiAddrData(): Start Conduct wifi nvram data...!");
		pFuncName = "SNBase::ConductWifiAddrData()";
        rs = (this->*pDataFunc)((char*)sNVRAM_ReadCnf.buf+0x4, iRID, pInData, iBufLen);
		for(int i = 0; i < iBufLen; i++)
		{
		    pWriteData[i] = sNVRAM_ReadCnf.buf[0x4+i];
		}
    }
		
    /*
		unsigned int  offset = 0;
        unsigned long u4Value = 0;

		pFuncName = "SP_META_WiFi_readMCR32_r()";
		meta_result = SPMETA_DLL::SP_META_WiFi_readMCR32_r(m_hSPMetaHandle, 20000, offset, &u4Value);
		if(meta_result == SPMETA_DLL::META_SUCCESS && u4Value != 0)
		{		    
		    MTRACE (g_hEBOOT_DEBUG, "SNBase::ConductWifiAddrData(): Start Conduct wifi nvram data...!");
		    pFuncName = "SNBase::ConductWifiAddrData()";

			wifiChipVersion = u4Value & 0xFFFF;
			if(wifiChipVersion == MT5921)
	        {
	            //Wifi address offset is 0x26
                rs = (this->*pDataFunc)((char*)sNVRAM_ReadCnf.buf+0x26, iRID, pInData, iBufLen);
				for(int i = 0; i < iBufLen; i++)
				{
				    pWriteData[i] = sNVRAM_ReadCnf.buf[0x26+i];
				}
	        }
			else if(wifiChipVersion == MT5931 || 
			      wifiChipVersion == MT6620 || 
			      wifiChipVersion == MT6628 ||
			      wifiChipVersion == MT6571 ||
			      wifiChipVersion == MT6572 || 
			      wifiChipVersion == MT6582 || 			      
			      wifiChipVersion == MT6592 ||
                  wifiChipVersion == MT6595 ||
                  wifiChipVersion == MT6752 ||
                  wifiChipVersion == MT8127)
			{
			    //Wifi address offset is 0x4
                rs = (this->*pDataFunc)((char*)sNVRAM_ReadCnf.buf+0x4, iRID, pInData, iBufLen);
				for(int i = 0; i < iBufLen; i++)
				{
				    pWriteData[i] = sNVRAM_ReadCnf.buf[0x4+i];
				}
			}
			else
			{
			    pFuncName = "SP_META_WiFi_readMCR32_r()";
				meta_result = SPMETA_DLL::META_FAILED;
			    MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_WiFi_readMCR32_r(): Unsupport wifi chip version, %d!", wifiChipVersion);
				goto Err;
			}			
		}
		else
		{
			pFuncName = "SP_META_WiFi_readMCR32_r()";
			meta_result = SPMETA_DLL::META_FAILED;
			MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_WiFi_readMCR32_r(): Get wifi chip version fail!");
		    goto Err;
		}	
		
    }
    */
    else if(strcmp(pLID, "AP_CFG_RDEB_FILE_BT_ADDR_LID") == 0)
    {
        MTRACE (g_hEBOOT_DEBUG, "SNBase::ConductBTAddrData(): Start Conduct BT nvram data...!");
        pFuncName = "SNBase::ConductBTAddrData()";
        rs = (this->*pDataFunc)((char*)sNVRAM_ReadCnf.buf, iRID, pInData, iBufLen);
		for(int i = 0; i < iBufLen; i++)
		{
		    pWriteData[i] = sNVRAM_ReadCnf.buf[i];
		}
    }
    else if(strcmp(pLID, "AP_CFG_RDEB_FILE_ETHERNET_LID") == 0)
    {
        MTRACE (g_hEBOOT_DEBUG, "SNBase::ConductEthernetMacAddrData(): Start Conduct Ethernet Mac nvram data...!");
        pFuncName = "SNBase::ConductEthernetMacAddrData()";
        rs = (this->*pDataFunc)((char*)sNVRAM_ReadCnf.buf, iRID, pInData, iBufLen);
		for(int i = 0; i < iBufLen; i++)
		{
		    pWriteData[i] = sNVRAM_ReadCnf.buf[i];
		}
    }
    else if (strcmp(pLID, "AP_CFG_RDCL_FILE_AUDIO_SPEAKER_MONITOR_LID") == 0)
    {
        rs = 0;
		for(int i = 0; i < iBufLen; i++)
        {
            pWriteData[i] = pInData[i];
		}
		
        //MTRACE (g_hEBOOT_DEBUG, "SNBase::ConductAudioTemperatureData(): Start Conduct Audio temperature data...!");
        //pFuncName = "SNBase::ConductAudioTemperatureData()";
        //rs = (this->*pDataFunc)((char*)sNVRAM_ReadCnf.buf, iRID, pInData, iBufLen);

		pFuncName = "SmartPhoneSN::REQ_WriteAP_NVRAM_Start()";
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteAP_NVRAM_Start(): Start Conduct Audio temperature data...!");
        AUDIO_SPREAKER_MONITOR_PARAM_STRUCT sWriteTempStruct;
        memset(&sWriteTempStruct, 0, sizeof(AUDIO_SPREAKER_MONITOR_PARAM_STRUCT));

        memcpy(&sWriteTempStruct, sNVRAM_ReadCnf.buf, iWriteBufSize);
        sWriteTempStruct.temp_initial = atof(pInData);

        memcpy(sNVRAM_ReadCnf.buf,  &sWriteTempStruct,  iWriteBufSize);
        
    }
     
    meta_result = (SPMETA_DLL::META_RESULT)rs;
    if (meta_result !=  SPMETA_DLL::META_SUCCESS)
    {
        goto Err;
    }
	MTRACE (g_hEBOOT_DEBUG, "%s: Conduct nvram data successfully!", pFuncName);
 
    sNVRAM_WriteReq.LID = pLID;
    sNVRAM_WriteReq.RID = iRID;
    sNVRAM_WriteReq.len = iWriteBufSize;
    sNVRAM_WriteReq.buf = sNVRAM_ReadCnf.buf;
    m_sNVRAM_OPID = iRID;

    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Start to write nvram data...");
    meta_result =  REQ_WriteToAPNVRAM(sNVRAM_WriteReq);
    if (meta_result != SPMETA_DLL::META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_WriteToAPNVRAM()";
        goto Err;
    }
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Write nvram data successfully!");

    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Read nvram data for check start...");
    memset(sNVRAM_ReadCnf.buf, 0 , sNVRAM_ReadCnf.len);
	meta_result = REQ_ReadFromAPNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
	if (meta_result != SPMETA_DLL::META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_ReadFromAPNVRAM()";
        goto Err;
    }
	else
	{
	    char *pDataType = NULL;
		memset(pReadData, 0, sizeof(char)*MAX_DATA_LENGTH);
	    if (strcmp(pLID, "AP_CFG_RDEB_FILE_WIFI_LID") == 0)
        {
            pDataType = "Wifi";
			 //Wifi address offset is 0x4
		    for(int i = 0; i < iBufLen; i++)
			{
			    pReadData[i] = sNVRAM_ReadCnf.buf[0x4+i];
			}
	    }
			/*
            if(wifiChipVersion == MT5921)
	        {
	            //Wifi address offset is 0x26
	            for(int i = 0; i < iBufLen; i++)
				{
				    pReadData[i] = sNVRAM_ReadCnf.buf[0x26+i];
				}
	        }
			else if(wifiChipVersion == MT5931 || 
			      wifiChipVersion == MT6620 || 
			      wifiChipVersion == MT6628 ||
			      wifiChipVersion == MT6571 ||
			      wifiChipVersion == MT6572 || 
			      wifiChipVersion == MT6582 || 			      
			      wifiChipVersion == MT6592 ||
                  wifiChipVersion == MT6595 ||
                  wifiChipVersion == MT8127)
			{
			    //Wifi address offset is 0x4
			    for(int i = 0; i < iBufLen; i++)
				{
				    pReadData[i] = sNVRAM_ReadCnf.buf[0x4+i];
				}
			}
			else
			{
			    MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_WiFi_readMCR32_r(): Unsupport wifi chip version, %d!", wifiChipVersion);
			    goto Err;
			}
			
		}
		*/
		else if(strcmp(pLID, "AP_CFG_RDEB_FILE_BT_ADDR_LID") == 0)
		{
		    pDataType = "BT";
			for(int i = 0; i < iBufLen; i++)
			{
				pReadData[i] = sNVRAM_ReadCnf.buf[i];
			}
		}
        else if(strcmp(pLID, "AP_CFG_RDEB_FILE_ETHERNET_LID") == 0)
        {
            pDataType = "Ethernet_Mac";
            for(int i = 0; i < iBufLen; i++)
            {
                pReadData[i] = sNVRAM_ReadCnf.buf[i];
            }
		}
        else if(strcmp(pLID, "AP_CFG_RDCL_FILE_AUDIO_SPEAKER_MONITOR_LID") == 0)
        {
            pDataType = "Audio_Temperature";
            
            AUDIO_SPREAKER_MONITOR_PARAM_STRUCT sWriteTempStruct;
            memset(&sWriteTempStruct, 0, sizeof(AUDIO_SPREAKER_MONITOR_PARAM_STRUCT));
            
            memcpy(&sWriteTempStruct, sNVRAM_ReadCnf.buf, iWriteBufSize);
            float fTemp = sWriteTempStruct.temp_initial;            
            sprintf(pReadData, "%.1f", fTemp);
		}

        char tmpReadData[13] = {0};		
		if(dataType != WRITE_TEMPERATURE)
		{
			m_bWriteNvram = false;
			(this->*pDataFunc)(tmpReadData, iRID, pReadData, iBufLen);
		}
		else
		{
			strncpy(tmpReadData, pReadData, strlen(pReadData));
		}
		
		if(strncmp(pWriteData, pReadData, iBufLen) != 0)
		{		     		    
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Write_%s[%s]", pDataType, pInData);
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Read_%s[%s]", pDataType, tmpReadData);
			MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN: Check nvram data FAIL!!");
			meta_result = SPMETA_DLL::META_FAILED;
		}
		else
		{		    
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Write_%s[%s]", pDataType, pInData);
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Read_%s[%s]", pDataType, tmpReadData);
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Check nvram data PASS!!");
		}
	}
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToAPNVRAM(): Read nvram data for check end...");

    if (sNVRAM_ReadCnf.buf != NULL)
    {
        free (sNVRAM_ReadCnf.buf);
        sNVRAM_ReadCnf.buf = NULL;
    }
    
    return meta_result;

Err:
    if (sNVRAM_ReadCnf.buf != NULL)
    {
        free (sNVRAM_ReadCnf.buf);
        sNVRAM_ReadCnf.buf = NULL;
    }

	MTRACE_ERR (g_hEBOOT_DEBUG, "%s: fail! MetaResult = %s", pFuncName, ResultToString_SP(meta_result));
    return meta_result;
}

META_RESULT SmartPhoneSN::SwitchMDByIndex(UINT MDIndex)
{
    if (m_bDSDAProject)
    {
        m_bInitExtMDdb = true;
        MDIndex = m_iMDChannelIndex[MDIndex];
        m_iCurMDChanelIndex = MDIndex;
    }
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SwitchMDByIndex(): Switch to MD[%d] start...", MDIndex);
    
    META_RESULT MetaResult;
    char *pFuncName = NULL;
    
    if (m_bDSDAProject)
    {
        pFuncName = "META_SwitchCurrentModemEx_r()";
        MetaResult = META_SwitchCurrentModemEx_r(m_hMauiMetaHandle, 10000, MDIndex, m_SpMdCapList.modem_cap[MDIndex].md_service, m_SpMdCapList.modem_cap[MDIndex].ch_type, NULL);
    } 
    else
    {
        pFuncName = "META_SwitchCurrentModem_r()";             
        MetaResult = META_SwitchCurrentModem_r(m_hMauiMetaHandle, 5000, MDIndex);
    }
    
    if (MetaResult == META_SUCCESS)
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::%s: Switch to MD[%d] successfully!!", pFuncName, MDIndex);
        /*
        if(MDIndex >= 1)
        {
            MetaResult = LoadModemDatabase(MDIndex);
        }
        */
    }
    else
    {
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::%s: Switch to MD[%d] Fail, MetaResult = %s!!", 
            pFuncName, MDIndex, ResultToString(MetaResult));
    }
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SwitchMDByIndex(): Switch to MD[%d] end...", MDIndex);
    return MetaResult;
}

META_RESULT SmartPhoneSN::REQ_ReadModem_NVRAM_Start(WriteData_Type_e dataType, char *pOutData, unsigned short iRID)
{
    
    if(!pOutData)
    {
        return META_INVALID_ARGUMENTS;
    }   
    m_bWriteNvram = false;
    
    int iBufLen = 0;
    char *pLID = NULL;
    pConductDataFunc pDataFunc = NULL;
    char *pFuncName = NULL;
    char *pDataType = NULL;
    
    switch(dataType)
    {       
    case WRITE_BARCODE:
        iBufLen = 64;
        pDataType = "Barcode";
        pLID = "NVRAM_EF_BARCODE_NUM_LID";
        pDataFunc = ConductBarcodeData;
        pFuncName = "SmartPhoneSN::ConductBarcodeData()";
        break;
        
    case WRITE_IMEI:
        iBufLen = 10;
        pDataType = "IMEI";
        pLID = "NVRAM_EF_IMEI_IMEISV_LID";
        pDataFunc = ConductIMEIData;
        pFuncName = "SmartPhoneSN::ConductIMEIData()";
        break;      
        
    default:
        return META_INVALID_ARGUMENTS;
    }   

    META_RESULT MetaResult = META_SUCCESS;

    int iMetaTimeout  = 5000;
    int iReadBufSize = 0;
    FT_NVRAM_READ_REQ  sNVRAM_ReadReq;
    FT_NVRAM_READ_CNF  sNVRAM_ReadCnf;
    

    memset(&sNVRAM_ReadReq, 0, sizeof(FT_NVRAM_READ_REQ));
    memset(&sNVRAM_ReadCnf, 0, sizeof(FT_NVRAM_READ_CNF));
    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_GetRecLen(): Start to get nvram struct size via LID = \"%s\"...", pLID);
    MetaResult = META_NVRAM_GetRecLen(pLID,&iReadBufSize);
    if ( META_SUCCESS != MetaResult)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_GetRecLen(): Get nvram struct size fail, MetaResult = %s", ResultToString(MetaResult));
        return MetaResult;
    }
    else
    {
        MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_GetRecLen(): Get nvram struct size = %d successfully!", iReadBufSize);
        
        if ( NULL != sNVRAM_ReadCnf.buf )
        {
            free ( sNVRAM_ReadCnf.buf );	
            sNVRAM_ReadCnf.buf = NULL;
        }
        
        sNVRAM_ReadReq.LID = pLID;
        sNVRAM_ReadReq.RID = iRID;
        sNVRAM_ReadCnf.len = iReadBufSize;
        sNVRAM_ReadCnf.buf = (unsigned char*) malloc (iReadBufSize*sizeof(unsigned char));
        if (NULL == sNVRAM_ReadCnf.buf)
        {
            MTRACE_ERR (g_hEBOOT_DEBUG, "Malloc heap memory cause fail!");
            return  META_FAILED;
        }
    }
    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromModemNVRAM(): Start to read nvram data...");
    MetaResult =  REQ_ReadFromModemNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
    if (MetaResult != META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_ReadFromModemNVRAM()";
        goto Err;
    }
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromModemNVRAM(): Read nvram data successfully!");

    memcpy(pOutData, sNVRAM_ReadCnf.buf, iReadBufSize);

    if (sNVRAM_ReadCnf.buf != NULL)
    {
        free (sNVRAM_ReadCnf.buf);
        sNVRAM_ReadCnf.buf = NULL;
    }
    
    return MetaResult;
    
Err:
    if (sNVRAM_ReadCnf.buf != NULL)
    {
        free (sNVRAM_ReadCnf.buf);
        sNVRAM_ReadCnf.buf = NULL;
    }
    
    MTRACE_ERR (g_hEBOOT_DEBUG, "%s: fail! MetaResult = %s", pFuncName, ResultToString(MetaResult));
    
    return MetaResult;

}

META_RESULT SmartPhoneSN::REQ_WriteModem_NVRAM_Start(WriteData_Type_e dataType, char *pInData, unsigned short iRID)
{
    if(!pInData || strlen(pInData) == 0)
    {
        return META_INVALID_ARGUMENTS;
    }   
    m_bWriteNvram = true;
    
    int iBufLen = 0;
    char *pLID = NULL;
    pConductDataFunc pDataFunc = NULL;
	char *pFuncName = NULL;
	char pWriteData[64] = {0};
	char pReadData[64] = {0};
	char *pDataType = NULL;
      
    switch(dataType)
    {       
    case WRITE_BARCODE:
        iBufLen = 64;
		pDataType = "Barcode";
        pLID = "NVRAM_EF_BARCODE_NUM_LID";
        pDataFunc = ConductBarcodeData;
		pFuncName = "SmartPhoneSN::ConductBarcodeData()";
        break;
        
    case WRITE_IMEI:
        iBufLen = 10;
		pDataType = "IMEI";
        pLID = "NVRAM_EF_IMEI_IMEISV_LID";
        pDataFunc = ConductIMEIData;
		pFuncName = "SmartPhoneSN::ConductIMEIData()";
        break;      
        
    default:
        return META_INVALID_ARGUMENTS;
    }   

	
    int iMetaTimeout  = 5000;
    int iWriteBufSize = 0;
    FT_NVRAM_WRITE_REQ sNVRAM_WriteReq;
    FT_NVRAM_WRITE_CNF sNVRAM_WriteCnf;
    FT_NVRAM_READ_REQ  sNVRAM_ReadReq;
    FT_NVRAM_READ_CNF  sNVRAM_ReadCnf;
    META_RESULT meta_result = META_SUCCESS;

    memset(&sNVRAM_WriteReq, 0, sizeof(FT_NVRAM_WRITE_REQ));
    memset(&sNVRAM_WriteCnf, 0, sizeof(FT_NVRAM_WRITE_CNF));
    memset(&sNVRAM_ReadReq, 0, sizeof(FT_NVRAM_READ_REQ));
    memset(&sNVRAM_ReadCnf, 0, sizeof(FT_NVRAM_READ_CNF));

    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_GetRecLen(): Start to get nvram struct size via LID = \"%s\"...", pLID);
    meta_result = META_NVRAM_GetRecLen(pLID,&iWriteBufSize);
    if ( META_SUCCESS != meta_result)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_GetRecLen(): Get nvram struct size fail, MetaResult = %s", ResultToString(meta_result));
        return meta_result;
    }
    else
    {
        MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_GetRecLen(): Get nvram struct size = %d successfully!", iWriteBufSize);
		
        if ( NULL != sNVRAM_ReadCnf.buf )
        {
            free ( sNVRAM_ReadCnf.buf );	
            sNVRAM_ReadCnf.buf = NULL;
        }
        
        sNVRAM_ReadReq.LID = pLID;
        sNVRAM_ReadReq.RID = iRID;
        sNVRAM_ReadCnf.len = iWriteBufSize;
        sNVRAM_ReadCnf.buf = (unsigned char*) malloc (iWriteBufSize*sizeof(unsigned char));
        if (NULL == sNVRAM_ReadCnf.buf)
        {
            MTRACE_ERR (g_hEBOOT_DEBUG, "Malloc heap memory cause fail!");
            return  META_FAILED;
        }
    }

    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromModemNVRAM(): Start to read nvram data...");
    meta_result =  REQ_ReadFromModemNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
    if (meta_result != META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_ReadFromModemNVRAM()";
        goto Err;
    }
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_ReadFromModemNVRAM(): Read nvram data successfully!");

    
    meta_result = (this->*pDataFunc)((char*)sNVRAM_ReadCnf.buf, iRID, pInData, iBufLen);  
    if (meta_result !=  META_SUCCESS)
    {
        goto Err;
    }
    else
    {
        /*
        for(int i = 0; i < iBufLen; i++)
        {
            writeData[i] = sNVRAM_ReadCnf.buf[i];
        }
        */
		memcpy(pWriteData, sNVRAM_ReadCnf.buf, iBufLen);
	    MTRACE (g_hEBOOT_DEBUG, "%s: Conduct nvram data successfully!", pFuncName);
    }
    
    sNVRAM_WriteReq.LID = pLID;
    sNVRAM_WriteReq.RID = iRID;
    sNVRAM_WriteReq.len = iWriteBufSize;
    sNVRAM_WriteReq.buf = sNVRAM_ReadCnf.buf;
    m_sNVRAM_OPID = iRID;

    //sNVRAM_WriteCnf.status = 0;
    //sNVRAM_WriteCnf.LID = pLID;  
    sNVRAM_WriteCnf.RID = iRID;

    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToModemNVRAM(): Start to write nvram data...");
    meta_result =  REQ_WriteToModemNVRAM(&sNVRAM_WriteReq, &sNVRAM_WriteCnf);
    if (meta_result != META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_WriteToModemNVRAM()";
        goto Err;
    }
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToModemNVRAM(): Write nvram data successfully!");

	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToModemNVRAM(): Read nvram data for check start...");
    memset(sNVRAM_ReadCnf.buf, 0 , sNVRAM_ReadCnf.len);
	meta_result = REQ_ReadFromModemNVRAM (&sNVRAM_ReadReq, &sNVRAM_ReadCnf);
	if (meta_result != SPMETA_DLL::META_SUCCESS )
    {
        pFuncName = "SmartPhoneSN::REQ_WriteToModemNVRAM()";
        goto Err;
    }
	else
	{
        char tmpReadData[64] = {0};
		m_bWriteNvram = false;
		memcpy(pReadData, sNVRAM_ReadCnf.buf, iBufLen);
		(this->*pDataFunc)(tmpReadData, iRID, pReadData, iBufLen);
		if(strncmp(pWriteData, pReadData, iBufLen) != 0)
		{		     		    
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Write_%s[%s]", pDataType, pInData);
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Read_%s[%s]", pDataType, tmpReadData);
            MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN: Check nvram data FAIL!!");
			meta_result = META_FAILED;
		}
		else
		{
		    
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Write_%s[%s]", pDataType, pInData);
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Read_%s[%s]", pDataType, tmpReadData);
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN: Check nvram data PASS!!");
		}
	}
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_WriteToModemNVRAM(): Read nvram data for check end...");
    
    if (sNVRAM_ReadCnf.buf != NULL)
    {
        free (sNVRAM_ReadCnf.buf);
        sNVRAM_ReadCnf.buf = NULL;
    }

    return meta_result;

Err:
    if (sNVRAM_ReadCnf.buf != NULL)
    {
        free (sNVRAM_ReadCnf.buf);
        sNVRAM_ReadCnf.buf = NULL;
    }

	MTRACE_ERR (g_hEBOOT_DEBUG, "%s: fail! MetaResult = %s", pFuncName, ResultToString(meta_result));
    
    return meta_result;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::ReadNvToMakeFileName(char *p_NumFile)
{	
	char pOutData[100];;
	char BarcodeFile[100] = {0};
	char ImeiFile[100] = {0};
	char temp[100] = "_";
	SPMETA_DLL::META_RESULT MetaResult = SPMETA_DLL::META_SUCCESS;

   
	if(g_sMetaComm.sWriteOption.bWriteIMEI 
        || g_sMetaComm.sWriteOption.bWriteBarcode 
		|| g_sMetaComm.sWriteOption.bWriteWifi
		||g_sMetaComm.sWriteOption.bWriteBT)
	{
		for(int i=0; i<2; i++)
		{
		    memset(pOutData,0,sizeof(pOutData));
			MetaResult = REQ_ReadAP_NVRAM_Start((WriteData_Type_e)i, pOutData, 1);//read barcode_imei
			if(MetaResult != SPMETA_DLL::META_SUCCESS)
			{
				 sprintf(m_strMsg, "ERROR!! REQ_ReadAP_NVRAM_Start : MetaResult = %s", ResultToString_SP(MetaResult));
				 return MetaResult;
			}
			else
			{
				 if(i == 0)
				 {
					 strncpy(BarcodeFile,pOutData,sizeof(pOutData));
					 sprintf(m_strMsg, "BarcodeFile = %s:",BarcodeFile);
				 }
				 else
				 {
					 strncpy(ImeiFile,pOutData,sizeof(pOutData));
					 sprintf(m_strMsg, "ImeiFile = %s:",ImeiFile);
				 }
			}				   
		}

		if(!strcmp(BarcodeFile,"00000000"))
		{
			if(!strcmp(ImeiFile,"00000000"))
			{
				sprintf(p_NumFile,"%s",temp);
			}
			else
			{
				sprintf(p_NumFile,"%s%s",temp,ImeiFile);
			}
		}
		else
		{
			if(!strcmp(ImeiFile,"00000000"))
			{
				sprintf(p_NumFile,"%s%s",BarcodeFile,temp);
			}
			else
			{
				sprintf(p_NumFile,"%s%s%s",BarcodeFile,temp,ImeiFile);
			}
		}
    }

    return MetaResult;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::LoadAPDatabase()
{
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::LoadAPDatabase() start...");

    SPMETA_DLL::META_RESULT MetaResult = SPMETA_DLL::META_SUCCESS;
    unsigned long db;
    
    if (!g_sMetaComm.sDBFileOption.strAPDbpath)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::LoadAPDatabase(): Incorrect database file path!");
        return SPMETA_DLL::META_INVALID_ARGUMENTS;
    }
      
    if (!g_sMetaComm.sDBFileOption.bDBInitAP)
    {       
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::LoadAPDatabase(): Start to init AP database, DB path = %s", g_sMetaComm.sDBFileOption.strAPDbpath);
        MetaResult = SPMETA_DLL::SP_META_NVRAM_Init_r ( m_hSPMetaHandle, g_sMetaComm.sDBFileOption.strAPDbpath, &db);
        if ( MetaResult == SPMETA_DLL::META_SUCCESS)
        {
            g_sMetaComm.sDBFileOption.bDBInitAP = true;
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::LoadAPDatabase(): Init AP database successfully!");
        }
        else
        {
            g_sMetaComm.sDBFileOption.bDBInitAP = false;
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::LoadAPDatabase(): Init AP database Fail! MetaResult = %s", ResultToString_SP(MetaResult));
        }
    }
    else
    {
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::LoadAPDatabase(): Already init AP database done, DB path = %s", g_sMetaComm.sDBFileOption.strAPDbpath);
        MetaResult = SPMETA_DLL::META_SUCCESS;
    }
    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::LoadAPDatabase() end...");
    return MetaResult;
}

META_RESULT SmartPhoneSN::LoadModemDatabase(int MDindex)
{
    unsigned long db = 0;
    META_RESULT meta_result = META_SUCCESS;
    
    bool bInitMD1Done = true;
    
    bool *pbInitDBDone = NULL;
    char *pStrMDDbpath = NULL;
    switch (MDindex)
    {
    case 0:
        pbInitDBDone = &g_sMetaComm.sDBFileOption.bDBInitModem_1;
        pStrMDDbpath = g_sMetaComm.sDBFileOption.strMD1Dbpath;
        break;
        
    case 1:
        pbInitDBDone = &g_sMetaComm.sDBFileOption.bDBInitModem_2;
        pStrMDDbpath = g_sMetaComm.sDBFileOption.strMD2Dbpath;
        break;
        
    default:
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::LoadModemDatabase(): Incorrect MDIndex = %d!", MDindex);
        return META_INVALID_ARGUMENTS;
        break;
    }
    
    if (!pStrMDDbpath || strlen(pStrMDDbpath) == 0)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::LoadModemDatabase(): Incorrect database file path!");
        return META_INVALID_ARGUMENTS;
    }
    else
    {
        if((*pbInitDBDone) == false)
        {                             
            char *pFuncName = NULL;
            //if (g_sMetaComm.eTargetType == SMART_PHONE_DUALMODEM)
            if ((m_bDualModem == true && m_bWorldPhone == false) /*|| g_sMetaComm.eTargetType == SMART_PHONE_DUALMODEM*/)
            {
                meta_result = META_NVRAM_Init_Ex_r ( m_hMauiMetaHandle, MDindex, pStrMDDbpath, &db);
                pFuncName = "META_NVRAM_Init_Ex_r";
            } 
            else
            {
                MDindex = m_sMdInfo.active_md_idx - 1;                 
                //For MT6595 DSDA project
                if (m_bDSDAProject)
                {
                    MDindex = m_iCurMDChanelIndex;
                    if (m_bInitExtMDdb)
                    {
                        m_sMdInfo.activeMdTypeIdx = 0;
                    }
                }

                meta_result = META_NVRAM_Init_Ex_Mdtype_r(m_hMauiMetaHandle, MDindex, m_sMdInfo.activeMdTypeIdx, pStrMDDbpath, &db);
                pFuncName = "META_NVRAM_Init_Ex_Mdtype_r";
            }
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::%s(): start to init MD[%d] database, DB path = \"%s\"...", 
                pFuncName, MDindex, pStrMDDbpath);
           
        #ifdef _IGNORE_DB_INCONSISTENT_
            if (META_SUCCESS == meta_result || meta_result == META_MAUI_DB_INCONSISTENT)
            {
                *pbInitDBDone = true;				
                if (META_SUCCESS == meta_result)
                {
                    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::%s(): Init MD[%d] database successfully!", pFuncName, MDindex);
                } 
                else if(META_MAUI_DB_INCONSISTENT == meta_result)
                {
                    MTRACE (g_hEBOOT_DEBUG, "Warning: SmartPhoneSN::%s(): Current database not match handset, MetaResult = %s!", 
                        pFuncName, ResultToString(meta_result));
                }
                meta_result = META_SUCCESS;
            }
        #else
            if (META_SUCCESS == meta_result)
            {
                *pbInitDBDone = true;				
                MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::%s(): Init MD[%d] database successfully!", pFuncName, MDindex);             
            }
        #endif           
            else
            {
                *pbInitDBDone = false;
                MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::%s(): Init MD[%d] database Fail, MetaResult = %s",
                    pFuncName, MDindex, ResultToString(meta_result)); 
            }
            
        }
        else
        {
            //For MT6595 DSDA project
            if (m_bDSDAProject)
            {
                MDindex = m_iCurMDChanelIndex;
            }
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_Init_r(): MD[%d] database already init done!",  MDindex);
        }       
    }

    return meta_result;
}

META_RESULT SmartPhoneSN::LoadModemDatabase()
{
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::LoadModemDatabase(): start to init modem database...");

    unsigned long db = 0;
    META_RESULT meta_result = META_SUCCESS;
    int MDindex = 0;
    bool bInitMD1Done = true;
    
    if (!g_sMetaComm.sDBFileOption.strMD1Dbpath)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::LoadModemDatabase(): Incorrect database file path!");
        meta_result = META_INVALID_ARGUMENTS;
    }
    else
    {       
        MDindex = 0;
        if (false == g_sMetaComm.sDBFileOption.bDBInitModem_1)
        {             
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_Init_Ex_r(): start to init MD[%d] database, DB path = \"%s\"...", MDindex+1, g_sMetaComm.sDBFileOption.strMD1Dbpath);
            meta_result = META_NVRAM_Init_Ex_r ( m_hMauiMetaHandle, MDindex, g_sMetaComm.sDBFileOption.strMD1Dbpath, &db);
            if (META_SUCCESS == meta_result)
            {
                g_sMetaComm.sDBFileOption.bDBInitModem_1 = true;
                MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_Init_Ex_r: Init MD[%d] database successfully!",  MDindex+1);
            }
            else
            {
                bInitMD1Done = false;
                g_sMetaComm.sDBFileOption.bDBInitModem_1 = false;
                MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_Init_Ex_r: Init MD[%d] database Fail, MetaResult = %s", MDindex+1, ResultToString(meta_result)); 
            }
        } 
        else
        {
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_Init_r(): MD[%d] database already init done!",  MDindex+1);
        }
        
        if (g_sMetaComm.eTargetType == SMART_PHONE_DUALMODEM && bInitMD1Done)
        {       
            MDindex = 1;
            if (!g_sMetaComm.sDBFileOption.strMD2Dbpath)
            {
                MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::LoadModemDatabase(): Incorrect database file path!");
                meta_result = META_INVALID_ARGUMENTS;
            }
            else
            {
                
                if (false == g_sMetaComm.sDBFileOption.bDBInitModem_2)
                {          
                    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_Init_Ex_r(): start to init MD[%d] database, DB path = \"%s\"...",  MDindex+1, g_sMetaComm.sDBFileOption.strMD2Dbpath);
                    meta_result = META_NVRAM_Init_Ex_r ( m_hMauiMetaHandle, MDindex, g_sMetaComm.sDBFileOption.strMD2Dbpath, &db);
                    if (META_SUCCESS == meta_result)
                    {
                        g_sMetaComm.sDBFileOption.bDBInitModem_2 = true;
                        MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_Init_Ex_r: Init MD[%d] database successfully!", MDindex+1);              
                    }
                    else
                    {
                        g_sMetaComm.sDBFileOption.bDBInitModem_2 = false;
                        MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_Init_Ex_r: Init MD[%d] database Fail, MetaResult = %s", MDindex+1, ResultToString(meta_result)); 
                    }           
                }
                else
                {
                    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::META_NVRAM_Init_r(): MD[%d] database already init done!", MDindex+1);
                }
            }//if (!g_sMetaComm.sDBFileOption.strMD2Dbpath)
        }// if (g_sMetaComm.eTargetType == SMART_PHONE_DUALMODEM && bInitMD1Done)
    }//if (!g_sMetaComm.sDBFileOption.strMD1Dbpath)
       
    return meta_result;
}

SPMETA_DLL::META_RESULT SmartPhoneSN::ExitAPMetaMode()
{
    SPMETA_DLL::META_RESULT spMetaResult;  
    char *pFuncName = NULL;
    
    if (m_bTargetInMetaMode)
    {
        //Switch to modem meta fail from AP meta last time, so need to reconnect to AP meta mode
        if (m_eMetaMode == SP_AP2MD_FAIL)
        {
            int BootStop = 0;
            int usb_port = 0;
            SPMETA_DLL::WM_META_ConnectInMETA_Req BootRequest; 
            SPMETA_DLL::WM_META_ConnectInMETA_Report BootReport;
            
            BootRequest.com_port = m_iKernelComport;
            BootRequest.baudrate[0] = SPMETA_DLL::META_BAUD115200;
            BootRequest.baudrate[1] = SPMETA_DLL::META_BAUD230400;
            BootRequest.baudrate[2] = SPMETA_DLL::META_BAUD460800;
            BootRequest.baudrate[3] = SPMETA_DLL::META_BAUD921600;
            BootRequest.baudrate[4] = SPMETA_DLL::META_BAUD57600;
            BootRequest.baudrate[5] = SPMETA_DLL::META_BAUD_END;
            BootRequest.flowctrl    = SPMETA_DLL::META_NO_FLOWCTRL;//META_SW_FLOWCTRL;
            BootRequest.ms_connect_timeout = m_tMetaReq_Ex.ms_connect_timeout;
            
            spMetaResult = SPMETA_DLL::SP_META_ConnectInMetaMode_r(m_hSPMetaHandle, &BootRequest, &BootStop, &BootReport); 
            if (META_SUCCESS != spMetaResult)
            {
                MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaMode_r(): Connect to AP meta Fail!, BootRequest.com_port = %d, MetaResult = %s", 
                    BootRequest.com_port, ResultToString_SP(spMetaResult));
            }  
        }
        
        
        spMetaResult = SPMETA_DLL::SP_META_DisconnectWithTarget_r (m_hSPMetaHandle);
        pFuncName = "SP_META_DisconnectWithTarget_r()";
        if (spMetaResult == SPMETA_DLL::META_SUCCESS)
        {
            m_bTargetInMetaMode = false;
        } 
    }

    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::ExitAPMeta(): Exit meta mode by %s successfully! MetaResult = %s", pFuncName, ResultToString_SP(spMetaResult));
    return spMetaResult;
}

META_RESULT SmartPhoneSN::APSwithToModemMeta()
{
    

    char *pFuncName = NULL;
    META_RESULT MetaResult;
    SPMETA_DLL::META_RESULT spMetaResult;

    META_ConnectInMETA_Req BootRequest;
    META_ConnectInMETA_Report BootReport;
      
    META_ConnectByUSB_Req usbRequest;
    META_ConnectByUSB_Report usbReport;
    
    spMetaResult = SPMETA_DLL::SP_META_DisconnectInMetaMode_r(m_hSPMetaHandle);
    if(SPMETA_DLL::META_SUCCESS != spMetaResult)
    {
        return (META_RESULT)spMetaResult;
    }
    
    //---------------------Connect with target ----------------------------------
    BootRequest.com_port = m_iKernelComport;
    // [META] META stage baudrate polling array, it must end with META_BAUD_END.
    BootRequest.baudrate[0] = META_BAUD115200;
    BootRequest.baudrate[1] = META_BAUD230400;
    BootRequest.baudrate[2] = META_BAUD460800;
    BootRequest.baudrate[3] = META_BAUD921600;
    BootRequest.baudrate[4] = META_BAUD57600;
    BootRequest.baudrate[5] = META_BAUD_END;   
    BootRequest.flowctrl = META_SW_FLOWCTRL;
    BootRequest.ms_connect_timeout = m_tMetaReq_Ex.ms_connect_timeout; //30000;
    
    if(g_sMetaComm.bUsbEnable)
    {      
        usbRequest.com_port = m_iKernelComport;
        usbRequest.ms_connect_timeout = m_tMetaReq_Ex.ms_connect_timeout;
        pFuncName = "META_ConnectInMetaModeByUSB_r";      
        MetaResult = META_ConnectInMetaModeByUSB_r(m_hMauiMetaHandle, &usbRequest, m_pMetaStopFlag, &usbReport);      
    }
    else
    {
        pFuncName = "META_ConnectInMetaMode_r";
        MetaResult = META_ConnectInMetaMode_r(m_hMauiMetaHandle, &BootRequest, m_pMetaStopFlag, &BootReport);
    }
        
    if(META_SUCCESS != MetaResult && META_MAUI_DB_INCONSISTENT != MetaResult)
    {
        m_eMetaMode = SP_AP2MD_FAIL;
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::%s():  Switch to Modem meta from AP meta Fail, MetaResult = %s", pFuncName, ResultToString(MetaResult));
        return MetaResult;
    }
    else
    {
        m_eMetaMode = SP_MODEM_META;
        MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::%s():  Switch to Modem meta from AP meta successfully!", pFuncName);
    }
        
	return META_SUCCESS;
}

META_RESULT SmartPhoneSN::APSwithToModemMeta_Ex()
{
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::META_ConnectWithMultiModeTarget_r():  Switch to Modem meta from AP meta by META_ConnectWithMultiModeTarget_r start...!");
    int iRet = 0;
    //iRet = SP_META_Wrapper_DisconnectInMetaMode_r(m_hMauiMetaHandle);
    iRet = SPMETA_DLL::SP_META_DisconnectInMetaMode_r(m_hSPMetaHandle);
    if(iRet == META_SUCCESS)
    {	  
        m_tMetaReq_Ex.com_port = m_iKernelComport;
        iRet = META_ConnectWithMultiModeTarget_r(m_hMauiMetaHandle, &m_tMetaReq_Ex,sizeof(m_tMetaReq_Ex),m_pMetaStopFlag,&m_tMetaConnReport_Ex);
        if(iRet != META_SUCCESS)
        {        
            m_eMetaMode = SP_AP2MD_FAIL;
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::META_ConnectWithMultiModeTarget_r():  Switch to Modem meta from AP meta Fail, MetaResult = %s", ResultToString(iRet));
        }
		else
		{
            //iRet = META_QueryIfFunctionSupportedByTarget_r(m_hMauiMetaHandle, 5000, "META_ERf_GetRfCapability_r");
            m_eMetaMode = SP_MODEM_META;
		    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::META_ConnectWithMultiModeTarget_r():  Switch to Modem meta from AP meta successfully!");
		}
    }	
    
    return (META_RESULT)iRet;
}

META_RESULT SmartPhoneSN::EnterModemMetaToInitModemDB()
{  
    META_RESULT MetaResult = META_SUCCESS;
    switch(m_eMetaMode)
    {
    case SP_AP_META:  
        if (m_bUseNewConnectMauiMetaAPI == false)
        {
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::ApSwithToModemMeta(): Switch to modem meta from AP meta start...");
            MetaResult = APSwithToModemMeta(); 
        }
        else if(m_bUseNewConnectMauiMetaAPI == true)
        {
            MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::ApSwithToModemMeta_Ex(): Switch to modem meta from AP meta start...");
            MetaResult = APSwithToModemMeta_Ex();
        }       
        break;

    case SP_NOTIN_META:
        MetaResult = EnterSPModemMeta();
        break;

    case SP_MODEM_META:
        MetaResult = META_SUCCESS;
        break;

    default:
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::EnterModemMetaToInitModemDB(): Unkown meta mode status!");
        MetaResult = META_FAILED;
        break;
    }

    if (MetaResult == META_SUCCESS)
    {       
        m_eMetaMode = SP_MODEM_META;
        MetaResult = LoadModemDatabase(0);
    }
    else
    {
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::EnterModemMetaToInitModemDB(): AP meta switch to modem meta cause error, MetaResult = %s",
            ResultToString(MetaResult));
    }

    return MetaResult;
}

META_RESULT SmartPhoneSN::ModemSwithToAPMeta()
{
    MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::ModemSwithToAPMeta(): Start switch to AP meta from Modem meta...");

    META_RESULT MetaResult = META_SUCCESS;
	
       
    MetaResult = META_DisconnectInMetaMode_r (m_hMauiMetaHandle);        
    if (MetaResult != META_SUCCESS)
    {
        MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::META_DisconnectInMetaMode_r(): Disconnect Modem meta mode Fail!, MetaResult = %s",  ResultToString(MetaResult));
    }
    else
    {       
        int BootStop = 0;
        int usb_port = 0;
        SPMETA_DLL::WM_META_ConnectInMETA_Req BootRequest; 
        SPMETA_DLL::WM_META_ConnectInMETA_Report BootReport;
        
        BootRequest.com_port = m_iKernelComport;
        BootRequest.baudrate[0] = SPMETA_DLL::META_BAUD115200;
        BootRequest.baudrate[1] = SPMETA_DLL::META_BAUD230400;
        BootRequest.baudrate[2] = SPMETA_DLL::META_BAUD460800;
        BootRequest.baudrate[3] = SPMETA_DLL::META_BAUD921600;
        BootRequest.baudrate[4] = SPMETA_DLL::META_BAUD57600;
        BootRequest.baudrate[5] = SPMETA_DLL::META_BAUD_END;
        BootRequest.flowctrl    = SPMETA_DLL::META_NO_FLOWCTRL;//META_SW_FLOWCTRL;
        BootRequest.ms_connect_timeout = m_tMetaReq_Ex.ms_connect_timeout;
              
        MetaResult = (META_RESULT)SPMETA_DLL::SP_META_ConnectInMetaMode_r(m_hSPMetaHandle, &BootRequest, &BootStop, &BootReport); 
        if (META_SUCCESS != MetaResult)
        {
            m_eMetaMode = SP_MD2AP_FAIL;
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaMode_r(): Modem meta switch to AP meta Fail!, BootRequest.com_port = %d, MetaResult = %s", 
                BootRequest.com_port, ResultToString_SP(MetaResult));
        }  
		else
		{
			m_eMetaMode = SP_AP_META;
			MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::SP_META_ConnectInMetaMode_r(): switch to AP meta from Modem meta  successfully!");    		
		}
    }
    
    
    return MetaResult;
}

META_RESULT SmartPhoneSN::ExitSPModemMeta()
{
    META_RESULT MetaResult = META_SUCCESS;

    //Switch to AP meta fail from modem meta last time, so need to reconnect to modem meta mode
    if (m_eMetaMode == SP_MD2AP_FAIL)
    {
        m_tMetaReq_Ex.com_port = m_iKernelComport;
        MetaResult = META_ConnectWithMultiModeTarget_r(m_hMauiMetaHandle, &m_tMetaReq_Ex,sizeof(m_tMetaReq_Ex),m_pMetaStopFlag,&m_tMetaConnReport_Ex);
        if(MetaResult != META_SUCCESS)
        {        
            m_eMetaMode = SP_AP2MD_FAIL;
            MTRACE_ERR(g_hEBOOT_DEBUG, "SmartPhoneSN::META_ConnectWithMultiModeTarget_r():  Connect to Modem meta Fail, MetaResult = %s", ResultToString(MetaResult));
        }     
    }

    MetaResult = ModemSwithToAPMeta(); //Must switch to AP meta first, if not target can`t shutdown successfully
    if (MetaResult == META_SUCCESS)
    {
        ExitAPMetaMode();
    }
    
    return META_SUCCESS;
}

META_RESULT SmartPhoneSN::EnterSPModemMeta()
{
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::EnterSPModemMeta() : Enter modem meta start...");

    META_RESULT MetaResult = META_SUCCESS;  
    int bootResult = 0;
    UpdateProgress(0.05);
    bootResult = ConnectWithPreloader();
    if (bootResult != 0)
    {
        MetaResult = (META_RESULT)bootResult;
    }
    else
    {
        UpdateProgress(0.08);
        bootResult = ConnectWithKernelPort(SP_MODEM_META);
        UpdateProgress(0.12);
        if (bootResult == 0)
        {
            m_eMetaMode = SP_MODEM_META;
            m_bTargetInMetaMode = true;
        }  
        else
        {
            m_eMetaMode = SP_NOTIN_META;
            m_bTargetInMetaMode = false;
        }
    }  

    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::EnterSPModemMeta() : Enter modem meta end...");
    return MetaResult;
}

void SmartPhoneSN::SetupMetaModeParameters()
{
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SetupMetaModeParameters() start...");
	//For preloader handshake parameters
    memset (&m_stModeArg, 0x0, sizeof(SP_BOOT_ARG_S));
	//For new api parameters
	m_bUseNewConnectMauiMetaAPI = true;
    memset(&m_tMetaReq_Ex, 0, sizeof(m_tMetaReq_Ex));
    memset(&m_tMetaConnReport_Ex, 0, sizeof(m_tMetaConnReport_Ex));

    if (g_sMetaComm.iPre_Connect_Timeout < 10000)
    {
        g_sMetaComm.iPre_Connect_Timeout = 10000;
    }

    if (g_sMetaComm.iKernel_Connect_Timeout < 20000)
    {
        g_sMetaComm.iKernel_Connect_Timeout = 20000;
    }

    m_iKernelComport = g_sMetaComm.iCOMPort;
		
    //Old parameters
    m_stModeArg.m_bbchip_type=SP_AUTO_DETECT_BBCHIP;
    m_stModeArg.m_ext_clock=SP_AUTO_DETECT_EXT_CLOCK;
    m_stModeArg.m_ms_boot_timeout=SP_BOOT_INFINITE;
    //m_stModeArg.m_max_start_cmd_retry_count = SP_DEFAULT_BROM_START_CMD_RETRY_COUNT;
    m_stModeArg.m_max_start_cmd_retry_count = 0;   
    //New parameters
    m_stModeArg.m_uTimeout = g_sMetaComm.iPre_Connect_Timeout;
    m_stModeArg.m_uRetryTime = 2000;
    m_stModeArg.m_uInterval = 10;
    m_stModeArg.m_uBaudrate = CBR_115200;
    m_stModeArg.m_pStopFlag  = &g_iMetaStopFlag;
    
    if (g_sMetaComm.bSecurityUSB)
    {
        m_stModeArg.m_auth_handle = SPATE_Get_AuthHandle();
        m_stModeArg.m_scert_handle = SPATE_Get_ScertHandle();
        m_stModeArg.m_cb_sla_challenge = SLA_Challenge;
        m_stModeArg.m_cb_sla_challenge_arg = NULL;
        m_stModeArg.m_cb_sla_challenge_end = SLA_Challenge_END;
        m_stModeArg.m_cb_sla_challenge_end_arg = NULL; 
    }
    else
    {
        m_stModeArg.m_auth_handle = NULL;
        m_stModeArg.m_scert_handle = NULL;
        m_stModeArg.m_cb_sla_challenge = NULL;
        m_stModeArg.m_cb_sla_challenge_arg = NULL;
        m_stModeArg.m_cb_sla_challenge_end = NULL;
        m_stModeArg.m_cb_sla_challenge_end_arg = NULL;
    }      
    m_stModeArg.m_bIsUSBEnable = g_sMetaComm.bUsbEnable;   
    m_stModeArg.m_bIsSymbolicEnable = false;
    m_stModeArg.m_bIsCompositeDeviceEnable = g_sMetaComm.bCompositeDeviceEnable;
    m_stModeArg.m_euBootMode = SP_META_BOOT;
    m_stModeArg.m_uPortNumber = 0;
    m_stModeArg.m_uMDMode = 0;

    //Common
    m_tMetaReq_Ex.com_port = m_iKernelComport;
    m_tMetaReq_Ex.ms_connect_timeout = g_sMetaComm.iKernel_Connect_Timeout;
    m_tMetaReq_Ex.close_com_port = 1;
    m_tMetaReq_Ex.InMetaMode = 1;
    m_tMetaReq_Ex.protocol = 1;          // DHL
    m_tMetaReq_Ex.channel_type = 1;      // Native channel
    m_tMetaReq_Ex.boot_meta_arg.m_bbchip_type = AUTO_DETECT_BBCHIP; 
    m_tMetaReq_Ex.boot_meta_arg.m_ext_clock = AUTO_DETECT_EXT_CLOCK;
    //UART parameters
    //m_tMetaReq_Ex.baudrate[0] = META_BAUD115200;
    //m_tMetaReq_Ex.baudrate[1] = META_BAUD230400;
    //m_tMetaReq_Ex.baudrate[2] = META_BAUD460800;
    m_tMetaReq_Ex.baudrate[0] = META_BAUD921600;
    m_tMetaReq_Ex.baudrate[1] = META_BAUD_END;   
    m_tMetaReq_Ex.flowctrl = META_SW_FLOWCTRL;
    //USB
    if (g_sMetaComm.bUsbEnable)
    {
        MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SetupMetaModeParameters(): Target enter meta mode by [USB].");
        m_tMetaReq_Ex.usb_enable = 1;
        m_tMetaReq_Ex.boot_meta_arg.m_usb_enable = _TRUE;       
    } 
    else
    {
        MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SetupMetaModeParameters(): Target enter meta mode by [UART].");
        m_tMetaReq_Ex.usb_enable = 0;
        m_tMetaReq_Ex.boot_meta_arg.m_usb_enable = _FALSE;
        m_tMetaReq_Ex.escape = 1;
    }                    
    
    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::SetupMetaModeParameters() end...");
}

SPMETA_DLL::META_RESULT SmartPhoneSN::EnterAPMetaMode()
{
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::EnterAPMetaMode() : Enter ap meta start...");

    SPMETA_DLL::META_RESULT spMetaResult = SPMETA_DLL::META_SUCCESS;
    int bootResult = 0;
    UpdateProgress(0.08);
    sprintf(m_strMsg, "Start searching preloader com port and handshake...");
    UpdateMsgInfo(m_strMsg);
	
    bootResult = ConnectWithPreloader();
    if (bootResult != 0)
    {
        sprintf(m_strMsg, "Searching preloader com port and handshake Fail!!");
        UpdateMsgInfo(m_strMsg);
        spMetaResult = (SPMETA_DLL::META_RESULT)bootResult;
        return spMetaResult;
    }
    else
    {
        sprintf(m_strMsg, "Searching preloader com port and handshake OK!!");
        UpdateMsgInfo(m_strMsg);

        sprintf(m_strMsg, "Start searching kernel com port and handshake...");
        UpdateMsgInfo(m_strMsg);
        UpdateProgress(0.10);
        //bootResult = ConnectWithKernelPort(SP_AP_META);
        bootResult = ConnectWithKernelPort_Ex(SP_AP_META);
        UpdateProgress(0.12);
        if (bootResult == 0)
        {
            sprintf(m_strMsg, "Searching kernel com port and handshake OK!!");
            UpdateMsgInfo(m_strMsg);
            m_eMetaMode = SP_AP_META;
            m_bTargetInMetaMode = true;
        }  
        else
        {
            sprintf(m_strMsg, "Searching kernel com port and handshake Fail!!");
            UpdateMsgInfo(m_strMsg);
            if (bootResult == SPMETA_DLL::META_MAUI_DB_INCONSISTENT)
            {
                m_eMetaMode = SP_AP_META;
                m_bTargetInMetaMode = true;
            } 
            else
            {
                m_eMetaMode = SP_NOTIN_META;
                m_bTargetInMetaMode = false;
            }            
        }
    }
    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::EnterAPMetaMode() : Enter ap meta end...");
    spMetaResult = (SPMETA_DLL::META_RESULT)bootResult;
    return spMetaResult;
}

//Add for DSDA Extern Modem Native Download
#if 0
int SmartPhoneSN::DSDA_QueryNativeDownload()    //0:query fail   1:need to download   2:do not need to download
{
    int iRet = 0;
	SPMETA_DLL::META_RESULT spMetaResult = SPMETA_DLL::META_SUCCESS;		

	SPMETA_DLL::MODEM_QUERY_DOWNLOAD_STATUS_REQ qDownloadReq;
	SPMETA_DLL::MODEM_QUERY_DOWNLOAD_STATUS_CNF qDownloadCnf;

	memset(&qDownloadReq, 0, sizeof(SPMETA_DLL::MODEM_QUERY_DOWNLOAD_STATUS_REQ));
	memset(&qDownloadCnf, 0, sizeof(SPMETA_DLL::MODEM_QUERY_DOWNLOAD_STATUS_CNF));
	
    for(int i=0; i<50; i++)
    {
		spMetaResult = SPMETA_DLL::SP_META_MODEM_Query_Download_Status_r(m_hSPMetaHandle, 2000, &qDownloadReq, &qDownloadCnf);
		if(spMetaResult == SPMETA_DLL::META_SUCCESS) break;
    }

	if(spMetaResult != SPMETA_DLL::META_SUCCESS)
	{
	    MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_QueryNativeDownload() : Query extern modem download status fail! MetaResult = %s!", ResultToString_SP(spMetaResult));
        sprintf(m_strMsg, "Query download extern modem status fail!");
    	UpdateMsgInfo(m_strMsg);
		iRet = 1;
	}
	else
	{
        if(qDownloadCnf.percentage != m_iLastPercentage)
        {
		    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_QueryNativeDownload() : Download status = %d / %d", qDownloadCnf.percentage, qDownloadCnf.status_code); 
        }
		m_iLastPercentage = qDownloadCnf.percentage;
		
		if(qDownloadCnf.percentage == 110 && qDownloadCnf.status_code == 0000)
	    {
			//Have downloaded already
			iRet = 0;
	    }
		else
		{
			//Need to download
			iRet = 2;
	    }
	}
	return iRet;
}
SPMETA_DLL::META_RESULT SmartPhoneSN::DSDA_StartNativeDownload()
{
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_StartNativeDownload() : Extern modem native download start!");
	SPMETA_DLL::META_RESULT spMetaResult = SPMETA_DLL::META_SUCCESS;
	
	SPMETA_DLL::MODEM_TRIGGER_NATIVE_DOWNLOAD_REQ DownloadReq;
	SPMETA_DLL::MODEM_TRIGGER_NATIVE_DOWNLOAD_CNF DownloadCnf;

	memset(&DownloadReq, 0, sizeof(SPMETA_DLL::MODEM_TRIGGER_NATIVE_DOWNLOAD_REQ));
	memset(&DownloadCnf, 0, sizeof(SPMETA_DLL::MODEM_TRIGGER_NATIVE_DOWNLOAD_CNF));

	spMetaResult = SPMETA_DLL::SP_META_MODEM_TRIGGER_NATIVE_DOWNLOAD_r(m_hSPMetaHandle, 20000, &DownloadReq, &DownloadCnf);
	if(spMetaResult != SPMETA_DLL::META_SUCCESS)
	{
	    MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_StartNativeDownload() : Extern modem native download fail! MetaResult = %s!", ResultToString_SP(spMetaResult));
		return spMetaResult;    
	}
	else
	{
	    //Sleep(10000);
	    int QueryResult = -1;
		m_iLastPercentage= 0;
		do
		{
		    QueryResult = DSDA_QueryNativeDownload();
		}while(QueryResult == 2);

		if(QueryResult != 0)
		{
		    spMetaResult = SPMETA_DLL::META_FAILED;
		}
	}
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_StartNativeDownload() : Extern modem native download finish!");
	return spMetaResult;
}
#endif

//Add for DSDA Extern Modem Backup and Restore
_BOOL SmartPhoneSN::DSDA_ExternalModemBackup()
{
    META_RESULT MetaResult;
    // query if bakcup function support
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_ExternalModemBackup() : Start query if target support backup function...");
    MetaResult = META_QueryIfFunctionSupportedByTarget_r(m_hMauiMetaHandle, 5000, "META_MISC_EX_BackupCalibrationToStorage_r");
    if(META_SUCCESS != MetaResult)
    {
	    MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_ExternalModemBackup() : Query target backup function fail! MetaResult = %s", ResultToString(MetaResult));
		return _FALSE;
    }
    // trigger external MODEM backup
    unsigned int status = 0;
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_ExternalModemBackup() : Start backup data to SDS...");
    MetaResult = META_MISC_EX_BackupCalibrationToStorage_r(m_hMauiMetaHandle, 2000, 0, &status);
    if(META_SUCCESS != MetaResult || status != 0)
    {
		MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_ExternalModemBackup() : Backup fail! MetaResult = %s", ResultToString(MetaResult));
		return _FALSE;
    }
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::DSDA_ExternalModemBackup() : Backup finish!");
    return _TRUE;
}


void SmartPhoneSN::ThreadMainEntryPoint()
{   
    bool bNeedScanData = false;  
    bool bSkipScanData = false;
    bool bNeedLoadDB = true;
	int times = 0;
	int Ret = 0;

	//int C2K_Flag = 1;

    /*For dual talk(external modem) project
    * Due to dual talk project can`t switch back and forth between ap and external modem 
    * When target type select tablet  and enable external modem option, mean that will write ap nvram, so need disable write external modem nvram
    * so it is mean(ex md + tablet to write bt wifi; ex md + tablet to write barcode imei;)
    */   
    bool bWriteBarcode = g_sMetaComm.sWriteOption.bWriteBarcode;
    bool bWriteIMEI = g_sMetaComm.sWriteOption.bWriteIMEI;
	
    if (g_sMetaComm.bDualTalk)
    {
        g_sMetaComm.sWriteOption.bWriteBarcode = false;
        g_sMetaComm.sWriteOption.bWriteIMEI = false;
    }
	if (g_sMetaComm.eTargetType != C2K)
	{
		g_sMetaComm.sWriteOption.bWriteMeid = false;
		g_sMetaComm.sWriteOption.bWriteEsn = false;
	}

    bNeedScanData = NeedScanData();
    if (bNeedScanData == false)
    {
        if (g_sMetaComm.sWriteOption.bWifiEPPCopy == false
            && g_sMetaComm.sWriteOption.bWriteDrm == false 
            && g_sMetaComm.sWriteOption.bWriteHdcp == false
            && g_sMetaComm.sWriteOption.bInstallHdcpData == false)
        {
            PopupMsgBox("At least select one write option!!", "Warning", MB_ICONWARNING);
            return;
        } 
        else
        {
            //Don`t need to Popup scan data dialog
            bSkipScanData = true;
            if (g_sMetaComm.sWriteOption.bWriteHdcp == false)
            {
                //Write DRM Key & Install Hdcp data don`t need to load ap database
                bNeedLoadDB = false;
            }
        }
    }
	else
	{
		if (!g_sMetaComm.sWriteOption.bWriteBarcode &&
        !g_sMetaComm.sWriteOption.bWriteIMEI &&
        !g_sMetaComm.sWriteOption.bWriteBT &&
        !g_sMetaComm.sWriteOption.bWriteWifi &&
        !g_sMetaComm.sWriteOption.bWriteEthernetMac &&
        !g_sMetaComm.sWriteOption.bWriteDrmkeyMCID &&
		(g_sMetaComm.sWriteOption.bWriteMeid ||
		g_sMetaComm.sWriteOption.bWriteEsn))

		bNeedLoadDB = false;
	}

    bool bAnyOperationFail = false;
    META_RESULT MetaResult = META_SUCCESS;
    SPMETA_DLL::META_RESULT spMetaResult = SPMETA_DLL::META_SUCCESS;

    

    if (g_sMetaComm.bSwithTool)
    {        
        EnableUSBSwitch();
    }

	if(g_sMetaComm.bCheckFastbootLock)
	{
	    sprintf(m_strMsg, "Start Adb_Manager_Init() and Set_Fastboot_EnvironmentVariable()...");
	    UpdateMsgInfo(m_strMsg);
		if(!Set_Fastboot_EnvironmentVariable())
		{
		    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Set_Fastboot_EnvironmentVariable() FAIL...");
			sprintf(m_strMsg, "Set Fastboot Environment Variable Fail!!");
        	UpdateMsgInfo(m_strMsg);
        	return;
		}
		sprintf(m_strMsg, "Set Fastboot Environment Variable OK!!");
        UpdateMsgInfo(m_strMsg);
		if(!Adb_Manager_Init())
		{	
			MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Adb_Manager_Init() FAIL...");
			
			Adb_Manager_Deinit();
			sprintf(m_strMsg, "SmartPhoneSN::Adb_Manager_Init() FAIL...");
        	UpdateMsgInfo(m_strMsg);
			return;
		}
		sprintf(m_strMsg, "SmartPhoneSN::Adb_Manager_Init() OK...");
        UpdateMsgInfo(m_strMsg);
	}
    m_hMauiMetaHandle = INVALID_META_HANDLE;
    m_hSPMetaHandle = INVALID_META_HANDLE;
    //Init meta handle    
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::MetaHandle_Init() start...");
    MetaResult = MetaHandle_Init();
    if (MetaResult != META_SUCCESS)
    {       
        bAnyOperationFail = true;
        sprintf(m_strMsg, "MetaHandle_Init() : MetaResult = %s", ResultToString_SP(MetaResult));
        *m_pMetaStopFlag = BOOT_STOP;
    }
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::MetaHandle_Init() end...");
           
    CScanData scanDlg;
	

    while(((*m_pMetaStopFlag != BOOT_STOP) &&( bSkipScanData == true || IDOK == scanDlg.DoModal())))
    {     
        MTRACE(g_hEBOOT_DEBUG, "------------------------------------ START -------------------------------------");
        bAnyOperationFail = false;
        UpdateMainDlgUI(false, NORMAL);
		//	if(g_sMetaComm.sIMEIOption.Temp_Option.bWriteTemperature)
		{
			g_pMainDlg->ShowTemperatureOnUI();
		}

        EnableStartBTN(false);

        
        //SPInit() can`t call before SNThread_Init() function
        SNThread_Init();
		//MTRACE (g_hEBOOT_DEBUG, "m_bWriteModemNvram = %d,m_sMdInfo.number_of_md = %d", m_bWriteModemNvram, m_sMdInfo.number_of_md);
        SPInit();
                                                            
        SetupMetaModeParameters();
        
        sprintf(m_strMsg, "Start load and init AP database...");
        UpdateMsgInfo(m_strMsg);
        
        UpdateProgress(0.06);   
        if (bNeedLoadDB == true)
        {
            MetaResult = (META_RESULT)LoadAPDatabase();
            if (MetaResult != META_SUCCESS)
            {       
                bAnyOperationFail = true;
                sprintf(m_strMsg, "LoadAPDatabase() : MetaResult = %s",ResultToString_SP(MetaResult));
                PopupMsgBox(m_strMsg, "Warning", MB_ICONWARNING);
                goto End;
            }
        }
        
        EnableStartBTN(true);
        
        if (g_sMetaComm.bUsbEnable)
        {
            sprintf(m_strMsg, "Wait for usb insert...");
            UpdateMsgInfo(m_strMsg);
        }  
        MetaResult = (META_RESULT)EnterAPMetaMode();
        if (MetaResult != META_SUCCESS)
        {       
            bAnyOperationFail = true;
            sprintf(m_strMsg, "EnterAPMetaMode() : MetaResult = %s", ResultToString_SP(MetaResult));
            goto End;
        }
#if 1
	if(SPMETA_DLL::META_SUCCESS == SPMETA_DLL::SP_META_QueryIfFunctionSupportedByTarget_r(m_hSPMetaHandle, 500, "SP_META_ENCRYPTED_Support_r"))
	{
		if(QueryEncryptionSupport(&m_hSPMetaHandle))
		{
			Encryption Edlg;
			//Edlg.DoModal();
			while((IDOK == Edlg.DoModal() ) && times < 3)
			{
				if(!VeritifiEncryption(&m_hSPMetaHandle))
				{
					MTRACE(g_hEBOOT_DEBUG,"VeritifiEncryption() retry : %d", times+1);
					times = times + 1;
				}
				else 
					break;
			}
			if(3 == times)
			{
				 bAnyOperationFail = true;
				 MTRACE(g_hEBOOT_DEBUG, "VeritifiEncryption() retry times more than 3 times!");
				 goto End;
			}
		}
	}
#endif 
		// query modem info must after queryEncryption.
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information start...");
        Ret = GetSPModemInfo_Ex();                        
        if (Ret == 0)
        {
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information successfully!!");
        } 
        else
        {
			bAnyOperationFail = true;
            //pFuncName = "GetSPModemInfo_Ex()";
            MTRACE_ERR (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information fail, MetaResult = %s", ResultToString_SP(Ret));
            goto End;
        }
        MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::GetSPModemInfo_Ex(): Query modem information end...");

        
        //Special case: m_bWriteModemNvram = true && m_sMdInfo.number_of_md = 0
        //So skip to load modem database
		MTRACE (g_hEBOOT_DEBUG, "m_bWriteModemNvram = %d,m_sMdInfo.number_of_md = %d", m_bWriteModemNvram, m_sMdInfo.number_of_md);
        if((m_bWriteModemNvram == true || g_sMetaComm.bCheckCalFlag || g_sMetaComm.bCheckFtFlag) && m_sMdInfo.number_of_md >= 1)
        {
            sprintf(m_strMsg, "Start switch to MD meta and init Modem database...");
            UpdateMsgInfo(m_strMsg);
            
            UpdateProgress(0.14);
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::EnterModemMetaToInitModemDB() start...");
            MetaResult = EnterModemMetaToInitModemDB();
            MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::EnterModemMetaToInitModemDB() end...");
            if (MetaResult != META_SUCCESS)
            {       
                bAnyOperationFail = true;
                sprintf(m_strMsg, "EnterModemMetaToInitModemDB() : MetaResult = %s", ResultToString(MetaResult));
                goto End;
            }
            UpdateProgress(0.18); 

        }   
        UpdateProgress(0.22);
        
        EnableStartBTN(false);
        sprintf(m_strMsg, "Start loop write data to nvram...");
        UpdateMsgInfo(m_strMsg);
        MetaResult = WriteNvramLoop();
        if (MetaResult != META_SUCCESS)
        {       
            bAnyOperationFail = true;
            goto End;
        }

        
    End:       
        if (m_bStopBeforeUSBInsert == true)
        {
            UpdateProgress(0.0);
            UpdateMsgInfo("..."); 
        } 
        else
        {
            if (bAnyOperationFail == true)
            {
                m_Process->SendMessage(PBM_SETBARCOLOR, 0, RGB(255, 0, 0));
                UpdateUICountResult(FAIL);
            }
            else
            {
                sprintf(m_strMsg, "All Operate successfully!!");
				UpdateMsgInfo(m_strMsg);
                MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::All Operate successfully!!");

                #ifdef _AUTO_GEN_FEATURE_
                if (g_AutoGenData.bEnableAutoGen)
                {
                    UpdateAutoGenParaToSetupFile();
                }       
                #endif
            }
            
            if (m_eMetaMode == SP_AP_META || m_eMetaMode == SP_AP2MD_FAIL)
            {
                ExitAPMetaMode();
            }
            else if(m_eMetaMode == SP_MODEM_META || m_eMetaMode == SP_MD2AP_FAIL)
            {
                ExitSPModemMeta();
            }

            //The backup nvram api return success, but the operator pull up usb cable immediately before all operation successfully.
            //This case will cause nvram data lose when firmware upgrate, so that put indicator turn green after exit meta.
			if((m_bBackupNvramSuccess == true) && (bAnyOperationFail = false) )
			{
				if(g_sMetaComm.bCheckFastbootLock)
				{
					if(REQ_FastbootLockOem()==-1)
					{
						sprintf(m_strMsg, "ERROR!! REQ_FastbootLockOem()");
						UpdateMsgInfo(m_strMsg);
						UpdateUICountResult(FAIL); 
					}

					else
					{
						sprintf(m_strMsg, "REQ_FastbootLockOem() OK");
						UpdateMsgInfo(m_strMsg);
						UpdateUICountResult(PASS); 

					}
				}	
				else
			    UpdateUICountResult(PASS); 
			}
			if((C2K_Flag == 1) && (bAnyOperationFail == false))
			{
				UpdateUICountResult(PASS); 
			}

            
            UpdateProgress(1.0);

            if (bSkipScanData == true)
            {
                Sleep(2000);
            }
        }
         
        EnableStartBTN(true);
		if(g_sMetaComm.sWriteOption.bWriteDrm)
		{
			*m_pMetaStopFlag = BOOT_STOP;
		}
        MTRACE(g_hEBOOT_DEBUG, "------------------------------------ END --------------------------------------");
	
    }
	if(g_sMetaComm.bCheckFastbootLock)
	{
		Adb_Manager_Deinit();
	}
    g_sMetaComm.sWriteOption.bWriteBarcode = bWriteBarcode;
    g_sMetaComm.sWriteOption.bWriteIMEI = bWriteIMEI;
    if (g_sMetaComm.bSwithTool)
    {
        DisableUSBSwitch();
    }
    MetaHandle_DeInit();       
    UpdateMainDlgUI(true, CANCEL);
}

bool SmartPhoneSN::Adb_Manager_Init()
{
	HANDLE hread_cmd = NULL,hwrite_out = NULL;
	SECURITY_ATTRIBUTES sa;
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    if(!CreatePipe(&hread_cmd, &hdle_write_cmd, &sa, 0))
    {	
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Adb_Manager_Init() : CreatePipe() write fail...");
		return FALSE;
    }
//	MTRACE (g_hEBOOT_DEBUG, "Adb_Manager::Adb_Manager_Init(): createpipe1 success!");
    if(!CreatePipe(&hdle_read_out, &hwrite_out, &sa, 0))
    {
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Adb_Manager_Init() : CreatePipe() read fail...");
        return FALSE;
    }
//	MTRACE (g_hEBOOT_DEBUG, "Adb_Manager::Adb_Manager_Init(): createpipe2 success!");

   
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    GetStartupInfo(&si);
    si.hStdError = hwrite_out;
    si.hStdOutput = hwrite_out;
    si.hStdInput = hread_cmd;
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

    if(!CreateProcess("c:\\windows\\system32\\cmd.exe", NULL, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
    {	
//		MTRACE_ERR (g_hEBOOT_DEBUG, "Adb_Manager::Adb_Manager_Init(): create cmd.exe process fail!");
        return FALSE;
    }
//	MTRACE (g_hEBOOT_DEBUG, "Adb_Manager::Adb_Manager_Init(): create cmd.exe process success!");

    CloseHandle(hread_cmd);
    CloseHandle(hwrite_out);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
//	MTRACE (g_hEBOOT_DEBUG, "Adb_Manager::Adb_Manager_Init(): hdle_write_cmd = %08X, hdle_read_out = %08X",hdle_write_cmd,hdle_read_out);
	return TRUE;
}

int SmartPhoneSN::Adb_Manager_Write(char *cmd_line,int cmd_length)
{
	char cmd_buf[100];
	memset(cmd_buf,0,sizeof(cmd_buf));
	memcpy(cmd_buf,cmd_line,cmd_length);

	cmd_buf[cmd_length] = '\r';
	cmd_buf[cmd_length+1] = '\n';
	DWORD bytesWritten = 0;

	if(!WriteFile(hdle_write_cmd, cmd_buf, cmd_length+2, &bytesWritten, NULL))
	{ 
		return 0;
	}

	return (int)(bytesWritten);
}

int SmartPhoneSN::Adb_Manager_Read(ADB_READ_BUF *adb_read_buf,int buf_size)
{
	DWORD bytesRead = 0;

	if(!ReadFile(hdle_read_out,adb_read_buf->rd_buf,buf_size,&bytesRead,NULL))
	{
		return 0;
	}
	adb_read_buf->rd_buf[bytesRead] = '\0';

	return (int)bytesRead;
}



bool SmartPhoneSN::Adb_WR_Cmd(char *cmd_line,int cmd_length)
{	
	
	if(!(Adb_Manager_Write(cmd_line,cmd_length)))
	{
		return FALSE;
	}
	Sleep(800);
	memset(&read_buf,0,r_bufsize);
	if(!(Adb_Manager_Read(&read_buf,r_bufsize)))
	{
		return FALSE;
	}
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Adb_WR_Cmd(): read_buf is = %s", read_buf.rd_buf);
	return TRUE;
}

int SmartPhoneSN::Adb_Manager_Deinit()
{
	
	//Adb_WR_Cmd("exit",strlen("exit"));
	Adb_WR_Cmd("adb kill-server",strlen("adb kill-server"));
	//	MTRACE(g_hEBOOT_DEBUG, "ATB_MR::Scan_Devices_FunProc(): close cmd.exe");
	memset(&read_buf,0,r_bufsize);
	CloseHandle(hdle_write_cmd);
	//	MTRACE(g_hEBOOT_DEBUG, "Adb_Manager::~Adb_Manager(): close hdle_write_cmd");
	CloseHandle(hdle_read_out);
	//	MTRACE(g_hEBOOT_DEBUG, "Adb_Manager::~Adb_Manager(): close hdle_read_out");
	return 0;
}
int SmartPhoneSN::REQ_FastbootLockOem()
{
    int timer=0;
	MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : Fastboot Lock OEM start....");
    sprintf(m_strMsg, "Start Lock OEM...");
    UpdateMsgInfo(m_strMsg);

    int bootResult=0;
	SetupMetaModeParameters();
	m_stModeArg.m_euBootMode = SP_FAST_BOOT;
	sprintf(m_strMsg, "Start searching preloader com port and handshake...");
    UpdateMsgInfo(m_strMsg);
	
    bootResult = ConnectWithPreloader();
	if (bootResult != 0)
    {
        sprintf(m_strMsg, "Searching preloader com port and handshake Fail!!");
        UpdateMsgInfo(m_strMsg);
        return -1;
    }
    else
    {
        sprintf(m_strMsg, "Searching preloader com port and handshake OK!!");
        UpdateMsgInfo(m_strMsg);

        sprintf(m_strMsg, "Start searching fastboot devices...");
		UpdateMsgInfo(m_strMsg);
		
		//	MTRACE (g_hEBOOT_DEBUG, "ATB_MR::ATB_MR_Init(): Adb_Manager_Init success!");
		if(!Adb_WR_Cmd("adb start-server",strlen("adb start-server")))
		{
			MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : adb start-server FAIL...");
			Adb_Manager_Deinit();
			return -1;
		}
		
		if(Adb_Detect_Devact()>0)
		{
			MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : Adb_Detect_Devact() OK...");
			sprintf(m_strMsg, "Find a fastboot devices OK...");
			UpdateMsgInfo(m_strMsg);
		}	
		else
		{
			MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : Adb_Detect_Devact() timeout...");
			Adb_Manager_Deinit();
			return -1;
		}	
	
		//if(!Adb_WR_Cmd("fastboot oem lock",strlen("fastboot oem lock")))
		if(!Fastboot_Lock_Oem())
		{
			MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : fastboot oem lock fail...");
			Adb_Manager_Deinit();
			return -1;
		}
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : fastboot oem lock ok...");
		sprintf(m_strMsg, "fastboot oem lock OK...");
		UpdateMsgInfo(m_strMsg);
   		return 0;
    }
}

int SmartPhoneSN::REQ_FastbootUnLockOem()
{
    int timer=0;
	MTRACE(g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : Fastboot Lock OEM start....");
    sprintf(m_strMsg, "Start Lock OEM...");
    UpdateMsgInfo(m_strMsg);

    int bootResult=0;
	SetupMetaModeParameters();
	m_stModeArg.m_euBootMode = SP_FAST_BOOT;
	sprintf(m_strMsg, "Start searching preloader com port and handshake...");
    UpdateMsgInfo(m_strMsg);
    bootResult = ConnectWithPreloader();
	if (bootResult != 0)
    {
        sprintf(m_strMsg, "Searching preloader com port and handshake Fail!!");
        UpdateMsgInfo(m_strMsg);
        return -1;
    }
    else
    {
        sprintf(m_strMsg, "Searching preloader com port and handshake OK!!");
        UpdateMsgInfo(m_strMsg);

        sprintf(m_strMsg, "Start searching ADB devices...");
		UpdateMsgInfo(m_strMsg);
		if(!Adb_Manager_Init())
		{	
			MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : Adb_Manager_Init() OK...");
			Adb_Manager_Deinit();
			return -1;
		}
		//	MTRACE (g_hEBOOT_DEBUG, "ATB_MR::ATB_MR_Init(): Adb_Manager_Init success!");
		if(!Adb_WR_Cmd("adb start-server",strlen("adb start-server")))
		{
			MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : Adb_Manager_Init() OK...");
			Adb_Manager_Deinit();
			return -1;
		}
		while(1)
		{
			timer++;
			if(Adb_Detect_Devact()>0)
			{
				MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : Adb_Detect_Devact() OK...");
				break;
			}	
			else if(timer>60)
			{
				MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : Adb_Detect_Devact() timeout...");
				Adb_Manager_Deinit();
				return -1;
			}	
		}
		if(!Adb_WR_Cmd("fastboot oem unlock",strlen("fastboot oem unlock")))
		{
			MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : fastboot oem lock fail...");
			Adb_Manager_Deinit();
			return -1;
		}
		if(!Adb_WR_Cmd("fastboot reboot",strlen("fastboot reboot")))
		{
			MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::REQ_FastbootLockOem() : fastboot oem lock fail...");
			Adb_Manager_Deinit();
			return -1;
		}
		Adb_Manager_Deinit();
   		return 0;
    }   
}
#if 0
int SmartPhoneSN::Adb_Detect_Devact()
{
	if(!Adb_WR_Cmd("fastboot devices",strlen("fastboot devices")))
	{
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Adb_Detect_Devact(): Adb_WR_Cmd() fastboot devices fail!");
		return 0;
	}

//	MTRACE (g_hEBOOT_DEBUG, "Adb_Manager::Adb_Detect_Devact(): send adb devices success!");
//	MTRACE (g_hEBOOT_DEBUG, "Adb_Manager::Adb_Detect_Devact(): %s",read_buf.rd_buf);
	
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Adb_Detect_Devact(): read_buf is = %s", read_buf.rd_buf);
	int r_leg = strlen(read_buf.rd_buf);
	char *f_str2 = "fastboot";
	int str2_leg = strlen("fastboot");
	if(strstr(read_buf.rd_buf,f_str2)!=NULL)
	{
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Adb_Detect_Devact(): find device ok....");
		return 1;
	}
	return 0;
}

int SmartPhoneSN::Fastboot_Lock_Oem()
{
   if(!Adb_WR_Cmd("fastboot oem lock",strlen("fastboot oem lock")))
	{
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Adb_Detect_Devact(): Adb_WR_Cmd() fastboot devices fail!");
		return 0;
	}
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Fastboot_Lock_Oem(): read_buf is = %s", read_buf.rd_buf);
	int r_leg = strlen(read_buf.rd_buf);
	char *f_str2 = "OKAY";
	int str2_leg = strlen("OKAY");
	if(strstr(read_buf.rd_buf,f_str2)!=NULL)
	{
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Fastboot_Lock_Oem(): find OKAY");
		return 1;
	}	
	return 0;
}

#else
int SmartPhoneSN::Adb_Detect_Devact()
{
	for(int i=0;i<10;i++)
	{   
		if(!(Adb_Manager_Write("fastboot devices",strlen("fastboot devices"))))
		{
			return 0;
		}
		Sleep(800);
		memset(&read_buf,0,r_bufsize);
		if(!(Adb_Manager_Read(&read_buf,r_bufsize)))
		{
			return 0;
		}
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Adb_Detect_Devact(): read_buf is = %s", read_buf.rd_buf);
		int r_leg = strlen(read_buf.rd_buf);
		char *f_str1=strstr(read_buf.rd_buf,"devices");
		if(f_str1!=NULL)
		{ 
			if(strstr(f_str1,"fastboot")!=NULL)
			{
				MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Adb_Detect_Devact(): find device ok....");
				return 1;
			}
		}
	}
	return 0;

}
int SmartPhoneSN::Fastboot_Lock_Oem()
{
   //if(!Adb_WR_Cmd("fastboot oem lock",strlen("fastboot oem lock")))
	if(!(Adb_Manager_Write("fastboot oem lock",strlen("fastboot oem lock"))))
	{
		return 0;
	}
	for(int i=0;i<3;i++)
	{
		memset(&read_buf,0,r_bufsize);
		if(!(Adb_Manager_Read(&read_buf,r_bufsize)))
		{
			return 0;
		}
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Fastboot_Lock_Oem(): read_buf is = %s", read_buf.rd_buf);
		int r_leg = strlen(read_buf.rd_buf);
		char *f_str2 = "OKAY";
		int str2_leg = strlen("OKAY");
		if(strstr(read_buf.rd_buf,f_str2)!=NULL)
		{
			MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Fastboot_Lock_Oem(): fastboot oem lock ok....");
			return 1;
		}
		Sleep(1500);
	}
	return 0;
}


int SmartPhoneSN::Set_Fastboot_EnvironmentVariable(void)
{
    char chBuf[0x8000]={0};  
    DWORD dwSize = GetEnvironmentVariable("path",chBuf,0x10000);  
	if(dwSize==0)
	{
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Set_Fastboot_EnvironmentVariable(): GetEnvironmentVariable() fail....");
		return 0;
	}
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Set_Fastboot_EnvironmentVariable(): GetEnvironmentVariable() chBuf is: %s....",chBuf);

	CString strEnvPaths(chBuf);  
  
    // find current path 
    if(!GetModuleFileName(NULL,chBuf,MAX_PATH))  
    {
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Set_Fastboot_EnvironmentVariable(): GetModuleFileName() fail....");
		return 0;
	}
	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Set_Fastboot_EnvironmentVariable(): GetModuleFileName() chBuf is: %s...",chBuf);
	
    CString strAppPath(chBuf);  
    const int nPos = strAppPath.ReverseFind(_T('\\'));  
    if(nPos>0){  
        // 路径中包含最后的'\\'  
        strAppPath = strAppPath.Mid(0,nPos+1);  
    }  
    //add fastboot path
    strEnvPaths.TrimRight(";");  
    strEnvPaths += ";" + strAppPath +"Android;";  
    MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Set_Fastboot_EnvironmentVariable(): SetEnvironmentVariable() strEnvPaths is: %s....",strEnvPaths);
	
    dwSize = SetEnvironmentVariable("path",strEnvPaths);  
	if(dwSize==0)
	{
		MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Set_Fastboot_EnvironmentVariable(): SetEnvironmentVariable() fail....");
		return 0;
	}
  	MTRACE (g_hEBOOT_DEBUG, "SmartPhoneSN::Set_Fastboot_EnvironmentVariable(): SetEnvironmentVariable() strEnvPaths is: %s....",strEnvPaths);
    return 1; 
}

#endif

//C2K
void SmartPhoneSN::EnterC2KModemMeta(int * MetaResult, int * m_hSPMetaHandle, int *C2K_Flag)
{
			C2K_LIBCONFIGPARMS c2kConfig;
			PHONEATTRIBUTE_PARMS phoneAttr;
			char szPath[s_MAX_PATH] = {0};


			c2kConfig.bLog = true;
			c2kConfig.bScript = false;
			c2kConfig.szLogPath = "C:\\ETS_LOG.txt";
			c2kConfig.szScriptPath = "";
			memset(&phoneAttr, 0, sizeof(PHONEATTRIBUTE_PARMS));
			phoneAttr.eAfcControlMode = C2K_AFC_TCXO;
			phoneAttr.eRfMode = C2K_RF_MODE_EVDO;
			phoneAttr.eRxCalibrationType = C2K_RX_CAL_MAIN;
			phoneAttr.eSidbAccessMode = C2K_SIDB_FSI;
			phoneAttr.bWriteSIDBFlag = false;       //if write calibration flag?
			phoneAttr.uPllSettleTime = 100;
			phoneAttr.uRxAGCGainTableSelectSettleTime = 200;
			phoneAttr.uRxCtrlSettleTime = 200;
			phoneAttr.uRxGainStateSettleTime = 200;
			phoneAttr.uTxAGCConfigSettleTime = 50;
			phoneAttr.uTxCtrlSettleTime = 50;
			phoneAttr.uTxTestRateSettleTime = 100;
			phoneAttr.uEnableRxTxSpySettleTime = 0;
			phoneAttr.bAFCSlopeStepPerPpmWithQ6 = 0;
			
			sprintf(m_strMsg, "Start  init C2K Meta...");
			UpdateMsgInfo(m_strMsg);

			UpdateProgress(0.14);
			MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_Init() start...");
			*MetaResult = META_C2K_Init(*m_hSPMetaHandle, &c2kConfig, &phoneAttr);
			MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_Init() end...");
			if(*MetaResult != META_SUCCESS)
			{
				*C2K_Flag = 0;
				MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_Init() fail");
				MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_Init() end...");
				sprintf(m_strMsg, "META_C2K_Init() fail");
				UpdateMsgInfo(m_strMsg);
				DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
				return;
			}
			UpdateProgress(0.18);

			bool isHasC2KModem = false;
			int c2kMdChannelIdx = 0;
			unsigned int c2k_protocol = META_MODEM_SRV_ETS;
			unsigned int c2k_ch_type = META_MODEM_CH_TUNNELING;

			int preMdChannelIdx = m_sMdInfo.active_md_idx;

			for (int i=0; i<m_sMdInfo.number_of_md+2; i++)
			{
				sprintf(m_strMsg, "[C2K] i= %d, protocol = %d, channel_type=%d", i, m_SpMdCapList.modem_cap[i].md_service, m_SpMdCapList.modem_cap[i].ch_type);
				UpdateMsgInfo(m_strMsg);
				MTRACE(g_hEBOOT_DEBUG, "[C2K] i= %d, protocol = %d, channel_type=%d", i, m_SpMdCapList.modem_cap[i].md_service, m_SpMdCapList.modem_cap[i].ch_type);

				if(META_MODEM_SRV_ETS == m_SpMdCapList.modem_cap[i].md_service)
				{
					c2kMdChannelIdx = i;
					c2k_protocol = m_SpMdCapList.modem_cap[i].md_service;
					c2k_ch_type = m_SpMdCapList.modem_cap[i].ch_type;
					isHasC2KModem = true;
					break;
				}
			}
			if(isHasC2KModem)
			{
				//META_RESULT MetaResult = META_SUCCESS;
				unsigned short us_com_port = 0;

				MTRACE(g_hEBOOT_DEBUG, "[C2K] Connect C2K USB port.");

				C2K_CONNECT_PARAMS connectReq;
				if(c2k_ch_type == META_MODEM_CH_TUNNELING)
				{
					MTRACE(g_hEBOOT_DEBUG, "[C2K] switch to C2K modem start");
					
					if(c2kMdChannelIdx != preMdChannelIdx)
					{
						*MetaResult = META_SwitchCurrentModemEx_r(*m_hSPMetaHandle, 10000, c2kMdChannelIdx, c2k_protocol, c2k_ch_type, NULL);
						if(META_SUCCESS != *MetaResult)
						{
							MTRACE(g_hEBOOT_DEBUG, "[C2K] switch to C2K modem fail!");
							*C2K_Flag = 0;
							DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
							return;
						}
						else
						{
							MTRACE(g_hEBOOT_DEBUG, "[C2K] switch to C2K modem OK!");
						}

					}

					MTRACE(g_hEBOOT_DEBUG, "[C2K] switch to C2K modem end!");
					
					
					us_com_port = c2kMdChannelIdx;
					MTRACE(g_hEBOOT_DEBUG, "[C2K]  us_com_port = %d", us_com_port);
					connectReq.eComType = C2K_COM_VC;
					connectReq.uComNum = us_com_port;
				}
				else
				{
					connectReq.eComType = C2K_COM_USB;
					connectReq.uComNum = us_com_port;

					GetModuleFileName(NULL, szPath, s_MAX_PATH);
					(_tcsrchr(szPath,_T('\\')))[1] = 0;
					strcat(szPath,"EtsMsg.txt");

					MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_LoadMessage_r() start...");
					*MetaResult = META_C2K_LoadMessage_r(*m_hSPMetaHandle, szPath);

					if(*MetaResult != META_SUCCESS)
					{
						*C2K_Flag = 0;
						DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
						sprintf(m_strMsg, "META_C2K_LoadMessage_r() : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
						UpdateMsgInfo(m_strMsg);
						MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_LoadMessage_r() fail :MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
						MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_LoadMessage_r() end!");
						UpdateProgress(1.00);
						return;
					}
					else
					{
						sprintf(m_strMsg, "META_C2K_LoadMessage_r() successful!");
						UpdateMsgInfo(m_strMsg);
						MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_LoadMessage_r() successful!");
						MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_LoadMessage_r() end!");
					}
					UpdateProgress(0.28);
				}
				sprintf(m_strMsg, "Start connect with C2K Meta...");
				UpdateMsgInfo(m_strMsg);

				UpdateProgress(0.34);

				MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_ConnectWithTarget_r() start...");

				for(int j=0; j<20; j++)
				{
					*MetaResult = META_C2K_ConnectWithTarget_r(*m_hSPMetaHandle, 2000, &connectReq);
					if(*MetaResult == META_SUCCESS)
						break;
				}
				if(*MetaResult != META_SUCCESS)
				{
					*C2K_Flag = 0;
					DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
					sprintf(m_strMsg, "META_C2K_ConnectWithTarget_r() : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
					UpdateMsgInfo(m_strMsg);
					MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_ConnectWithTarget_r() fail:MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
					MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_ConnectWithTarget_r() end!");
					UpdateProgress(1.00);
					return;
				}
				else
				{
					MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_ConnectWithTarget_r() successful!");
					MTRACE (g_hEBOOT_DEBUG, "[C2K] META_C2K_ConnectWithTarget_r() end!");
					sprintf(m_strMsg,  "META_C2K_ConnectWithTarget_r() successful!");
					UpdateMsgInfo(m_strMsg);
				}
				UpdateProgress(0.48);

				for(int i=0; i<10; i++)
				{
					*MetaResult = META_C2K_LoopbackTest_r(*m_hSPMetaHandle, 2000, i+1);
					if(META_SUCCESS == *MetaResult)
						break;
				}
				if(META_SUCCESS != *MetaResult)
				{
					*C2K_Flag = 0;
					sprintf(m_strMsg,"META_C2K_LoopbackTest_r(): MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
					UpdateMsgInfo(m_strMsg);
					MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_LoopbackTest_r() fail: MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
					DisconnectC2KMeta(m_hSPMetaHandle, C2K_Flag);
					DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
					UpdateProgress(1.00);

					return;
				}
				UpdateProgress(0.60);


				MEID_TABLE meidTable;
				if(g_sMetaComm.sWriteOption.bWriteMeid)
				{

					meidTable.idType = 0;
					strcpy(meidTable.meid, g_sMetaComm.sScanData.strMeid);
					sprintf(m_strMsg, "Start to Write MEID...");
					UpdateMsgInfo(m_strMsg);

					UpdateProgress(0.64);
					//Sleep(10000);
					MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_WriteNvram_r() start...");
					for(int m=0; m<20; m++)
					{
						*MetaResult = META_C2K_WriteNvram_r(*m_hSPMetaHandle, 2000, 0,C2K_DB_MEID, &meidTable, sizeof(meidTable));
						if(*MetaResult == META_SUCCESS)
							break;
					}
					//MTRACE(g_hEBOOT_DEBUG, "META_C2K_WriteNvram_r() end...");
					if(*MetaResult != META_SUCCESS)
					{
						*C2K_Flag = 0;
						sprintf(m_strMsg,"META_C2K_WriteNvram_r() : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
						UpdateMsgInfo(m_strMsg);
						MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_WriteNvram_r():Write MEID fail: MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
						MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_WriteNvram_r() end");
						DisconnectC2KMeta(m_hSPMetaHandle, C2K_Flag);
						DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);

						UpdateProgress(1.00);

						return;

					}
					else
					{

						MTRACE(g_hEBOOT_DEBUG, "[C2K] Write MEID succesful!");
						MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_WriteNvram_r() end");
						UpdateProgress(0.70);
						sprintf(m_strMsg, "Read MEID for check start...");
						MTRACE(g_hEBOOT_DEBUG, "[C2K] Read MEID for check start...");
						MEID_TABLE meid_table;
						memset(meid_table.meid , 0x00, sizeof(meid_table));
						MTRACE(g_hEBOOT_DEBUG, "[C2K] Read MEID :%s",meid_table.meid);
						meid_table.idType = 0;
						*MetaResult = META_C2K_ReadNvram_r(*m_hSPMetaHandle, 3000, 0, C2K_DB_MEID, &meid_table, sizeof(meid_table));
						//MTRACE(g_hEBOOT_DEBUG, "Read MEID for check End!");
						if(*MetaResult != META_SUCCESS)
						{
							//bAnyOperationFail = true;
							*C2K_Flag = 0;
							sprintf(m_strMsg,"META_C2K_ReadNvram_r() : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
							UpdateMsgInfo(m_strMsg);
							MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_ReadNvram_r(): Read MEID fail: MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
							MTRACE(g_hEBOOT_DEBUG, "[C2K] Read MEID for check End!");
							DisconnectC2KMeta(m_hSPMetaHandle, C2K_Flag);
							DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
							UpdateProgress(1.00);
							//goto End;
						
							return;
						}
						UpdateProgress(0.75);
						MTRACE(g_hEBOOT_DEBUG, "[C2K] Write MEID :%s",g_sMetaComm.sScanData.strMeid);
						MTRACE(g_hEBOOT_DEBUG, "[C2K] Read MEID :%s",meid_table.meid);

						if(0==stricmp(meid_table.meid, g_sMetaComm.sScanData.strMeid))
						{
							MTRACE(g_hEBOOT_DEBUG, "[C2K] Checking MEID succesfully!");
							sprintf(m_strMsg, "Checking MEID succesfully!");
							UpdateMsgInfo(m_strMsg);
						}
						else
						{
							*C2K_Flag = 0;
							MTRACE(g_hEBOOT_DEBUG, "[C2K] Checking MEID fail!");
							//bAnyOperationFail = true;
							sprintf(m_strMsg,"[C2K] Checking MEID fail!");
							UpdateMsgInfo(m_strMsg);
							//MTRACE(g_hEBOOT_DEBUG, "Read MEID fail: MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
							DisconnectC2KMeta(m_hSPMetaHandle, C2K_Flag);
							DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
							UpdateProgress(1.00);
							return;
						}

						UpdateProgress(0.85);
					}
					if(g_sMetaComm.sWriteOption.bWriteEsn)
					{
						meidTable.idType = 1;
						strcpy(meidTable.esn, g_sMetaComm.sScanData.strEsn);
						sprintf(m_strMsg, "Start to Write ESN...");
						UpdateMsgInfo(m_strMsg);

						UpdateProgress(0.64);
						MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_WriteNvram_r() start...");
						for(int m=0; m<20; m++)
						{
							*MetaResult = META_C2K_WriteNvram_r(*m_hSPMetaHandle, 2000, 0,C2K_DB_MEID, &meidTable, sizeof(meidTable));
							if(*MetaResult == META_SUCCESS)
								break;
						}
						//MTRACE(g_hEBOOT_DEBUG, "META_C2K_WriteNvram_r() end...");
						if(*MetaResult != META_SUCCESS)
						{

							//bAnyOperationFail = true;
							*C2K_Flag = 0;
							sprintf(m_strMsg,"[C2K] META_C2K_WriteNvram_r():Write ESN fail : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
							UpdateMsgInfo(m_strMsg);
							MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_WriteNvram_r():Write ESN fail: MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
							MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_WriteNvram_r() end!");
							DisconnectC2KMeta(m_hSPMetaHandle, C2K_Flag);
							DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
							return;
						}
						else
						{
							MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_WriteNvram_r(): Write ESN succesful!");
							MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_WriteNvram_r() end!");
							UpdateProgress(0.70);
							sprintf(m_strMsg, "[C2K] META_C2K_WriteNvram_r():Write ESN succesful!");
							UpdateMsgInfo(m_strMsg);
							//MTRACE(g_hEBOOT_DEBUG, "Write ESN succesful!");
							MTRACE(g_hEBOOT_DEBUG, "[C2K] Read ESN for check start...");
							sprintf(m_strMsg, "Read ESN for check start...");
							UpdateMsgInfo(m_strMsg);
							MEID_TABLE meid_table;
							meid_table.idType = 1;
							*MetaResult = META_C2K_ReadNvram_r(*m_hSPMetaHandle, 3000, 0, C2K_DB_MEID, &meid_table, sizeof(meid_table));
							if(*MetaResult != META_SUCCESS)
							{
								//bAnyOperationFail = true;
								*C2K_Flag = 0;
								sprintf(m_strMsg,"META_C2K_ReadNvram_r():Read ESN fail : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
								UpdateMsgInfo(m_strMsg);
								MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_ReadNvram_r():Read ESN fail: MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
								MTRACE(g_hEBOOT_DEBUG, "Read ESN for check End!");

								DisconnectC2KMeta(m_hSPMetaHandle, C2K_Flag);
								DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
								UpdateProgress(1.00);
								//goto End;
								
								return;
							}
							MTRACE(g_hEBOOT_DEBUG, "[C2K] Write ESN :%s",g_sMetaComm.sScanData.strMeid);
							MTRACE(g_hEBOOT_DEBUG, "[C2K] Read ESN :%s",meid_table.esn);
							UpdateProgress(0.80);
							if(0==stricmp(meid_table.esn, g_sMetaComm.sScanData.strEsn))
							{
								MTRACE(g_hEBOOT_DEBUG, "Checking ESN successfully!");
								sprintf(m_strMsg,"Checking Esn Successfully!");
								UpdateMsgInfo(m_strMsg);
							}
							else
							{
								*C2K_Flag = 0;
								MTRACE(g_hEBOOT_DEBUG, "[C2K] Checking ESN Fail!");
								//bAnyOperationFail = true;
								sprintf(m_strMsg,"[C2K] Checking ESN Fail!");
								UpdateMsgInfo(m_strMsg);
								MTRACE(g_hEBOOT_DEBUG, "[C2K] Checking ESN Fail!");
								MTRACE(g_hEBOOT_DEBUG, "[C2K] Checking ESN End!");
								DisconnectC2KMeta(m_hSPMetaHandle, C2K_Flag);
								DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
								UpdateProgress(1.00);
								
								return;
								
								//goto End;
							}
						}
					}
#if 0
					MTRACE(g_hEBOOT_DEBUG, "[C2K] Flaush NVRAM to Flash FFS start");

					*MetaResult = META_C2K_FlushNvram_r(*m_hSPMetaHandle, 10000);
							if(*MetaResult != META_SUCCESS)
							{
								MTRACE(g_hEBOOT_DEBUG, "[C2K] Flaush NVRAM to Flash FFS fail");
								//bAnyOperationFail = true;
								*C2K_Flag = 0;
								sprintf(m_strMsg,"META_C2K_ReadNvram_r():Read ESN fail : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
								UpdateMsgInfo(m_strMsg);
								MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_ReadNvram_r():Read ESN fail: MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
								MTRACE(g_hEBOOT_DEBUG, "Read ESN for check End!");

								DisconnectC2KMeta(m_hSPMetaHandle, C2K_Flag);
								DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);
								UpdateProgress(1.00);
								//goto End;
								
								return;
							}
							else
							{
									MTRACE(g_hEBOOT_DEBUG, "[C2K] Flaush NVRAM to Flash FFS successful!");
									MTRACE(g_hEBOOT_DEBUG, "[C2K] Flaush NVRAM to Flash FFS end!");
							}
#endif
					UpdateProgress(0.85);
					
					
					DisconnectC2KMeta(m_hSPMetaHandle, C2K_Flag);
					MTRACE(g_hEBOOT_DEBUG, "[C2K] switch to 234G modem start!");

				

					DeinitC2KMeta(m_hSPMetaHandle, C2K_Flag);


						*MetaResult = META_SwitchCurrentModemEx_r(*m_hSPMetaHandle, 10000, 0, m_SpMdCapList.modem_cap[0].md_service, 
								m_SpMdCapList.modem_cap[0].ch_type, NULL);
					if(META_SUCCESS != *MetaResult)
					{
						MTRACE(g_hEBOOT_DEBUG, "[C2K] META_SwitchCurrentModemEx_r(): [C2K] switch to 234G modem fail!");
						sprintf(m_strMsg,"META_SwitchCurrentModemEx_r(): [C2K] switch to 234G modem fail!");
						UpdateMsgInfo(m_strMsg);
					}
					else
					{
						MTRACE(g_hEBOOT_DEBUG, "[C2K] META_SwitchCurrentModemEx_r(): [C2K] switch to 234G modem successful!");
						sprintf(m_strMsg,"META_SwitchCurrentModemEx_r(): [C2K] switch to 234G modem successful!");
						UpdateMsgInfo(m_strMsg);
					}
					MTRACE(g_hEBOOT_DEBUG, "[C2K] switch to 234G modem end!");


			}
		}

		

}


		


void SmartPhoneSN::DeinitC2KMeta(int *m_hSPMetaHandle, int *C2K_Flag)
{
	MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_DeInit start...");
	META_RESULT MetaResult;

	MetaResult = META_C2K_DeInit(*m_hSPMetaHandle);
	if(MetaResult != META_SUCCESS)
	{
		*C2K_Flag = 0;
		MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_DeInit : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle) );
		sprintf(m_strMsg,"META_C2K_DeInit : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
		UpdateMsgInfo(m_strMsg);
		return;
	}
	MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_DeInit end!");

}

void SmartPhoneSN::DisconnectC2KMeta(int *m_hSPMetaHandle, int *C2K_Flag)
{
	MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_DisconnectWithTarget_r start...");
	META_RESULT MetaResult;
	
	MetaResult = META_C2K_DisconnectWithTarget_r(*m_hSPMetaHandle);
	if(MetaResult != META_SUCCESS)
	{
		*C2K_Flag = 0;
		MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_DisconnectWithTarget_r : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle) );
		sprintf(m_strMsg,"META_C2K_DisconnectWithTarget_r : MetaResult = %s", META_C2K_GetErrorString(*m_hSPMetaHandle));
		UpdateMsgInfo(m_strMsg);
		return;
	}
	MTRACE(g_hEBOOT_DEBUG, "[C2K] META_C2K_DisconnectWithTarget_r end!");
	
}

bool SmartPhoneSN::QueryEncryptionSupport(int * MetaHandle )
{
	
	SPMETA_DLL::CRYPTFS_QUERYSUPPORT_CNF cryptfs_Support_cnf;
	SPMETA_DLL::META_RESULT MetaResult;
	MetaResult = SPMETA_DLL::SP_META_ENCRYPTED_Support_r(*MetaHandle,60000, &cryptfs_Support_cnf);

	if((MetaResult == META_SUCCESS) && (cryptfs_Support_cnf.support == 1))
	{
		MTRACE(g_hEBOOT_DEBUG," Do support Encryption!");
		return true;
	}
    else
    {
		MTRACE(g_hEBOOT_DEBUG," Do not support Encryption : MetaResult = %s!", ResultToString_SP(MetaResult));
        return false;
    }	
	//return true;
}

bool SmartPhoneSN::VeritifiEncryption(int *MetaHandle)
{
	
	SPMETA_DLL::CRYPTFS_VERITIF_REQ cryptfs_Veritif_Req;
    SPMETA_DLL::CRYPTFS_VERITIF_CNF cryptfs_Veritif_Cnf;
    memset(&cryptfs_Veritif_Req, 0,sizeof(SPMETA_DLL::CRYPTFS_VERITIF_REQ));
    memset(&cryptfs_Veritif_Cnf, 0,sizeof(SPMETA_DLL::CRYPTFS_VERITIF_CNF));
	char *str = g_cPwd;
    strcpy((char *)cryptfs_Veritif_Req.pwd, str);
	cryptfs_Veritif_Req.length = strlen(g_cPwd);
	char m_strMsg[1024] = {0};
	SPMETA_DLL::META_RESULT MetaResult;
	MetaResult = SPMETA_DLL::SP_META_ENCRYPTED_VertifyPwd_r(*MetaHandle, 60000, &cryptfs_Veritif_Req, &cryptfs_Veritif_Cnf);
	if((MetaResult == META_SUCCESS) && cryptfs_Veritif_Cnf.match_result == 1)
	{
		MTRACE(g_hEBOOT_DEBUG, "Do match the password!");
		return true;
	}
	else
	{
		sprintf(m_strMsg, "Do not match: MetaResult = %s!",ResultToString_SP(MetaResult));
		UpdateMsgInfo(m_strMsg);
		return false;
	}
	
	//return true;
}



