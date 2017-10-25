#include "StdAfx.h"
#include "Common.h"
#include "SNbase.h"
#include "SN Writer.h"
#include "SN WriterDlg.h"

CSNWriterDlg *g_pMainDlg;

SNBase::SNBase()
{
    m_hThread = NULL;
    m_iThreadID = 0;
    m_hMauiMetaHandle = 0;
    m_hSPMetaHandle = 0;
    m_sNVRAM_OPID = 0;
	g_iMetaStopFlag = 0;
    m_pMetaStopFlag = &g_iMetaStopFlag;
    m_bWriteNvram = false;
    m_bWriteModemNvram = false;
    m_bTargetInMetaMode = false;
    m_bNeedBackupIMEI = false;
    m_hReadFromNVRAMEvent = NULL;
    m_hWriteToNVRAMEvent = NULL;

    memset(m_sIMEISV, 0, sizeof(IMEISV_struct_T)*4);
    memset(&m_sScanData, 0, sizeof(ScanData_struct));
}

SNBase::~SNBase()
{
    if (g_sMetaComm.bSwithTool)
    {
        DisableUSBSwitch();
    }
}

UINT SNBase::ThreadStaticEntryPoint(LPVOID pThis)
{
    SNBase * pthX = (SNBase*)pThis;   // the tricky cast   
    pthX->ThreadMainEntryPoint();           // now call the true entry-point-function   
    return 1;
}

void SNBase::SetProgress()
{
    m_iProcessRange = 1000;
    m_Process->SetRange(0, m_iProcessRange);
    m_Process->SendMessage(PBM_SETBARCOLOR, 0, RGB(0, 0, 255));
    UpdateProgress(0.01);
}

void SNBase::UpdateMsgInfo(char *strMsg)
{
    g_pMainDlg->SetDlgItemText(IDC_OPERATE_INFO, strMsg);
}

void SNBase::UpdateUICountResult(WriteNvram_Status_e eWriteStatus)
{
    static UINT totalNums = 0;
    static UINT passNums = 0;
    static UINT failNums = 0;

    char strTotal[20] = {0};
    char strPass[20] = {0};
    char strFail[20] = {0};

    //For the user click 'STOP' button before USB still not insert
    if (m_bStopBeforeUSBInsert == true)
    {
        return;
    }

    totalNums += 1;
    if (eWriteStatus == PASS)
    {
        passNums += 1;
    }
    else
    {
        failNums += 1;
    }
    sprintf(strTotal, "%d", totalNums);
    sprintf(strPass, "%d", passNums);
    sprintf(strFail, "%d", failNums);      
    g_pMainDlg->SetDlgItemText(IDC_COUNT_TOTAL, strTotal);
    g_pMainDlg->SetDlgItemText(IDC_COUNT_PASS, strPass);
    g_pMainDlg->SetDlgItemText(IDC_COUNT_FAIL, strFail);

    UpdateMsgInfo(m_strMsg); 
    UpdateMainDlgUI(true, eWriteStatus);
}

void SNBase::EnableStartBTN(bool bEnable)
{
    g_pMainDlg->EnableStartBTN(bEnable);
}

void SNBase::UpdateMainDlgUI(bool bEnable, WriteNvram_Status_e eWriteStatus)
{    
    if (bEnable == false)
    {
        g_pMainDlg->DisableUIItem();
    }
    else
    {
        g_pMainDlg->EnableUIItem();
    }
    g_pMainDlg->UpdateOperateResult(eWriteStatus);

}

void SNBase::UpdateProgress(double dPercent)
{   
    if (dPercent >= 1)
    {
        dPercent = 1;
    }

    int curPos = (int)(dPercent * m_iProcessRange);
    m_Process->SetPos(curPos);
}

void SNBase::PopupMsgBox(const char* strMsg, const char* strTilte, UINT uType)
{
    g_pMainDlg->PopupMsgBox(strMsg, strTilte, uType);
}

bool SNBase::NeedScanData()
{
    if (g_sMetaComm.sWriteOption.bWriteBarcode ||
        g_sMetaComm.sWriteOption.bWriteIMEI ||
        g_sMetaComm.sWriteOption.bWriteBT ||
        g_sMetaComm.sWriteOption.bWriteWifi ||
        g_sMetaComm.sWriteOption.bWriteEthernetMac ||
        g_sMetaComm.sWriteOption.bWriteDrmkeyMCID ||
		g_sMetaComm.sWriteOption.bWriteMeid ||
		g_sMetaComm.sWriteOption.bWriteEsn)
    {
        return true;
    } 
    else
    {
        return false;
    }
}

CheckCalFlag_Status_e SNBase::CheckCalibrationStatus(const char* strBarcode)
{
    CheckCalFlag_Status_e eCheckCalFlag = CAL_FLAG_PASS;
    if (strBarcode[60] == '1' && strBarcode[61] == '0')  //Calibration Pass
    {
        eCheckCalFlag = CAL_FLAG_PASS;
    }
    else if (strBarcode[60] == '0' && strBarcode[61] == '1')//Calibration Fail
    {
        eCheckCalFlag = CAL_FLAG_FAILED;
    }
    else
    {
        eCheckCalFlag = CAL_FLAG_NOT_EXIST;
    }

    return eCheckCalFlag;

}

bool SNBase::CheckCalFinalTestStatus(const char* strBarcode)
{
    MTRACE(g_hEBOOT_DEBUG, "SNBase::CheckCalFinalTestStatus(): Check calibration & nsft flag start...");

    if (g_sMetaComm.bCheckCalFlag)
    {            
        CheckCalFlag_Status_e eCheckCalFlag = CAL_FLAG_PASS;
        eCheckCalFlag = CheckCalibrationStatus(strBarcode);
        if (eCheckCalFlag != CAL_FLAG_PASS)
        {
            if (eCheckCalFlag == CAL_FLAG_FAILED)
            {
                sprintf(m_strMsg, "Calibration Flag : Calibration Fail!");
            }
            else if (eCheckCalFlag == CAL_FLAG_NOT_EXIST)
            {
                sprintf(m_strMsg, "Calibration Flag : No exist calibration flag!!");
            }
            
            MTRACE_ERR(g_hEBOOT_DEBUG, "SNBase::CheckCalFinalTestStatus(): %s", m_strMsg);
            return false;
        }  
        
    }
    
    if (g_sMetaComm.bCheckFtFlag)
    {            
        CheckFinalTestFlag_Status_e eCheckFTFlag = FT_FLAG_PASS;
        eCheckFTFlag = CheckFinalTestStatus(strBarcode);
        if (eCheckFTFlag != FT_FLAG_PASS)
        {
            if (eCheckFTFlag == FT_FLAG_FAILED)
            {
                sprintf(m_strMsg, "FinalTest Flag : Final test Fail!");
            }
            else if (eCheckFTFlag == FT_FLAG_NOT_EXIST)
            {
                sprintf(m_strMsg, "FinalTest Flag : No exist final test flag!!");
            }
            
            MTRACE_ERR(g_hEBOOT_DEBUG, "SNBase::CheckCalFinalTestStatus(): %s", m_strMsg);
            return false;
        }    
    }

    MTRACE(g_hEBOOT_DEBUG, "SNBase::CheckCalFinalTestStatus(): Check calibration & nsft flag Pass!!");

    MTRACE(g_hEBOOT_DEBUG, "SNBase::CheckCalFinalTestStatus(): Check calibration & nsft flag end...");
    return true;
}

CheckFinalTestFlag_Status_e SNBase::CheckFinalTestStatus(const char* strBarcode)
{
    CheckFinalTestFlag_Status_e eCheckFTFlag = FT_FLAG_PASS;
    if (strBarcode[62] == 'P' )  //Final Test Pass
    {
        eCheckFTFlag = FT_FLAG_PASS;
    }
    else if (strBarcode[62] == 'F')//Final Test Fail
    {
        eCheckFTFlag = FT_FLAG_FAILED;
    }
    else
    {
        eCheckFTFlag = FT_FLAG_NOT_EXIST;
    }
    
    return eCheckFTFlag;
}

META_RESULT SNBase::ConductBarcodeData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize)
{    
    int dataLength = strlen(pInDatabuf);
    char calFlag[2] = {0};   
    calFlag[0] = pOutData[60];  //Backup calibration & FinalTest flag temporary
    calFlag[1] = pOutData[61];
    char ftFlag = pOutData[62];
    
    memset(pOutData, 0x20, 64);
    for (int i = 0; i < dataLength; i++)
    {
        pOutData[i] = pInDatabuf[i];
    }
    
    pOutData[60] = calFlag[0]; //Restore calibration & FinalTest flag
    pOutData[61] = calFlag[1];
    pOutData[62] = ftFlag;
    pOutData[63] = '\0';

    //Sync to AP Prod_Info
    strncpy(m_sScanData.strBarcode, pOutData, 64);
    
    return META_SUCCESS;
}

META_RESULT SNBase::ConductIMEIData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize)
{
    if (!pInDatabuf || !pOutData)
    {
        return META_INVALID_ARGUMENTS;
    }
    /*
    //UI input = "123459876543210" storage in nvram will be:
    //imei[0] = 0x21
    //imei[1] = 0x43
    //imei[2] = 0x95
    //imei[3] = 0x78
    //imei[4] = 0x56
    //imei[5] = 0x34
    //imei[6] = 0x12
    //imei[7] = 0xf0
    */
    META_RESULT MetaResult; 
	char *pFuncName;
    
    if (m_bWriteNvram == false)//read from nvram
    {
        MTRACE (g_hEBOOT_DEBUG, "SNBase::Decompose_IMEI(): Start to Decompose IMEI[%d]...", RID_para-1);
		pFuncName = "SNBase::Decompose_IMEI(): Decompose IMEI";
        MetaResult = Decompose_IMEI(pOutData, RID_para, pInDatabuf, bufSize);
    } 
    else //write to nvram
    {
        MTRACE (g_hEBOOT_DEBUG, "SNBase::Compose_IMEI(): Start to Compose IMEI[%d]...", RID_para-1);
		pFuncName = "SNBase::Compose_IMEI(): Compose IMEI";
        MetaResult = Compose_IMEI( pOutData, RID_para, pInDatabuf, bufSize, g_sMetaComm.sIMEIOption.bCheckSum);

    }
    
    if(MetaResult == META_SUCCESS)
    {
        MTRACE (g_hEBOOT_DEBUG, "%s successfully!", pFuncName);
    }
	else
	{
	    MTRACE_ERR (g_hEBOOT_DEBUG, "%s Fail! MetaResult = %s",  pFuncName, ResultToString(MetaResult));
	}
	return MetaResult;
}

META_RESULT SNBase::ConductBTAddrData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize)
{
    if (!pInDatabuf || !pOutData)
    {
        return META_INVALID_ARGUMENTS;
    }
        
    /* 
    *** Feature phone ***
    *  UI input = "1234567890AC" storage in Modem nvram will be:
    * btAddr[0] = 0xAC
    * btAddr[1] = 0x90
    * btAddr[2] = 0x78
    * btAddr[3] = 0x56
    * btAddr[4] = 0x34
    * btAddr[5] = 0x12
    ---------------------------------------------------------
    *** Smart Phone ***
    * UI input = "1234567890AC" storage in AP nvram will be:
    * btAddr[0] = 0x12
    * btAddr[1] = 0x34
    * btAddr[2] = 0x56
    * btAddr[3] = 0x78
    * btAddr[4] = 0x90
    * btAddr[5] = 0xAC
    */

       
    int tmpCh;
    if (g_sMetaComm.eTargetType == FEATURE_PHONE)
    {
        if (m_bWriteNvram == false)
        {
            for (int i = 0; i < bufSize; i++)
            {
                tmpCh = (pInDatabuf[i] & 15);  //15 -->0000 1111, get Low 4Bits
                if (0 <= tmpCh && tmpCh <= 9)  //0 - 9
                {
                    pOutData[(5-i)*2 + 1] = tmpCh + '0';
                }
                else if (10 <= tmpCh && tmpCh <= 15) //a - f
                {
                    pOutData[(5-i)*2 + 1] = (tmpCh - 10) + 'A';
                }
                
                tmpCh = ((pInDatabuf[i] & 240) >> 4); //240 -->1111 0000, get High 4Bits
                if (0 <= tmpCh && tmpCh <= 9)  //0 - 9
                {
                    pOutData[(5-i)*2] = tmpCh + '0';
                }
                else if (10 <= tmpCh && tmpCh <= 15) //a - f
                {
                    pOutData[(5-i)*2] = (tmpCh - 10) + 'A';
                }           
            }
        } 
        else if(m_bWriteNvram == true)
        {
            strupr(pInDatabuf);   //转换字符串中的小写字母为大写
            for (int i = 0; i < bufSize; i++)
            {
                if ('0'<= pInDatabuf[((5-i)*2)] && pInDatabuf[((5-i)*2)] <= '9')
                {
                    tmpCh = pInDatabuf[((5-i)*2)] - '0';
                    tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
                }
                else if('A'<= pInDatabuf[((5-i)*2)] && pInDatabuf[((5-i)*2)] <= 'F')
                {
                    tmpCh = pInDatabuf[((5-i)*2)] - 'A' + 10;
                    tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
                }
                
                if ('0'<= pInDatabuf[((5-i)*2 + 1)] && pInDatabuf[((5-i)*2 + 1)] <= '9')
                {
                    tmpCh += pInDatabuf[((5-i)*2 + 1)] - '0'; //get Low 4bits
                } 
                else if('A'<= pInDatabuf[((5-i)*2 + 1)] && pInDatabuf[((5-i)*2 + 1)] <= 'F')
                {
                    tmpCh += pInDatabuf[((5-i)*2 + 1)] - 'A' + 10; //get Low 4bits
                }
                
                pOutData[i] = tmpCh;
            }
        }     
    }//end if (g_sMetaComm.eTargetType == FEATURE_PHONE)
    else
    {
        if (m_bWriteNvram == false)
        {
            for (int i = 0; i < bufSize; i++)
            {
                tmpCh = (pInDatabuf[i] & 15);  //15 -->0000 1111, get Low 4Bits
                if (0 <= tmpCh && tmpCh <= 9)  //0 - 9
                {
                    pOutData[(i*2 + 1)] = tmpCh + '0';
                }
                else if (10 <= tmpCh && tmpCh <= 15) //A - F
                {
                    pOutData[(i*2 + 1)] = (tmpCh - 10) + 'A';
                }
                
                //tmpCh = ((pInDatabuf[i] >> 4)  & 15);
                tmpCh = ((pInDatabuf[i] & 240) >> 4); //240 -->1111 0000, get High 4Bits
                if (0 <= tmpCh && tmpCh <= 9)  //0 - 9
                {
                    pOutData[i*2] = tmpCh + '0';
                }
                else if (10 <= tmpCh && tmpCh <= 15) //A - F
                {
                    pOutData[i*2] = (tmpCh - 10) + 'A';
                }           
            }
        } 
        else if(m_bWriteNvram == true)
        {
            strupr(pInDatabuf);   //转换字符串中的小写字母为大写
            for (int i = 0; i < bufSize; i++)
            {
                if ('0'<= pInDatabuf[i*2] && pInDatabuf[i*2] <= '9')
                {
                    tmpCh = pInDatabuf[i*2] - '0';
                    tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
                }
                else if('A'<= pInDatabuf[i*2] && pInDatabuf[i*2] <= 'F')
                {
                    tmpCh = pInDatabuf[i*2] - 'A' + 10;
                    tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
                }
                
                if ('0'<= pInDatabuf[(i*2 + 1)] && pInDatabuf[(i*2 + 1)] <= '9')
                {
                    tmpCh += pInDatabuf[(i*2 + 1)] - '0'; //get Low 4bits
                } 
                else if('A'<= pInDatabuf[(i*2 + 1)] && pInDatabuf[(i*2 + 1)] <= 'F')
                {
                    tmpCh += pInDatabuf[(i*2 + 1)] - 'A' + 10; //get Low 4bits
                }
                
                pOutData[i] = tmpCh;
            }
        }
    }
    
    return META_SUCCESS;
}

/*
META_RESULT SNBase::ConductVendorIDData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize)
{
    if (!pInDatabuf || !pOutData)
    {
        return META_INVALID_ARGUMENTS;
    }
        
    *** Smart Phone ***
    * UI input = "1234567890AC" storage in AP nvram will be:
    * btAddr[0] = 0x12
    * btAddr[1] = 0x34
    * btAddr[2] = 0x56
    * btAddr[3] = 0x78
    * btAddr[4] = 0x90
    * btAddr[5] = 0xAC
    //   

       
	int tmpCh;
		if (m_bWriteNvram == false)
		{
			for (int i = 0; i < bufSize; i++)
			{
				tmpCh = (pInDatabuf[i] & 15);  //15 -->0000 1111, get Low 4Bits
				if (0 <= tmpCh && tmpCh <= 9)  //0 - 9
				{
					pOutData[(i*2 + 1)] = tmpCh + '0';
				}
				else if (10 <= tmpCh && tmpCh <= 15) //a - f
				{
					pOutData[(i*2 + 1)] = (tmpCh - 10) + 'A';
				}
				
				//tmpCh = ((pInDatabuf[i] >> 4)  & 15);
				tmpCh = ((pInDatabuf[i] & 240) >> 4); //240 -->1111 0000, get High 4Bits
				if (0 <= tmpCh && tmpCh <= 9)  //0 - 9
				{
					pOutData[i*2] = tmpCh + '0';
				}
				else if (10 <= tmpCh && tmpCh <= 15) //A - F
				{
					pOutData[i*2] = (tmpCh - 10) + 'A';
				}			
			}
		} 
		else if(m_bWriteNvram == true)
		{
			strupr(pInDatabuf); 	  //转换字符串中的小写字母为大写
			for (int i = 0; i < bufSize; i++)
			{
				if ('0'<= pInDatabuf[i*2] && pInDatabuf[i*2] <= '9')
				{
					tmpCh = pInDatabuf[i*2] - '0';
					tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
				}
				else if('A'<= pInDatabuf[i*2] && pInDatabuf[i*2] <= 'F')
				{
					tmpCh = pInDatabuf[i*2] - 'A' + 10;
					tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
				}
				
				if ('0'<= pInDatabuf[(i*2 + 1)] && pInDatabuf[(i*2 + 1)] <= '9')
				{
					tmpCh += pInDatabuf[(i*2 + 1)] - '0'; //get Low 4bits
				} 
				else if('A'<= pInDatabuf[(i*2 + 1)] && pInDatabuf[(i*2 + 1)] <= 'F')
				{
					tmpCh += pInDatabuf[(i*2 + 1)] - 'A' + 10; //get Low 4bits
				}
				
				pOutData[i] = tmpCh;
			}end for
		}

    
    return META_SUCCESS;
}


*/

META_RESULT SNBase::ConductWifiAddrData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize)
{
    if (!pInDatabuf || !pOutData)
    {
        return META_INVALID_ARGUMENTS;
    }
    
    //strupr(pInDatabuf);       //转换字符串中的小写字母为大写
    //strlwr(pInDatabuf);       //转换字符串的大写字母为小写
    /*
    * UI input = "1234567890AC" storage in AP nvram will be:
    * wifiAddr[0] = 0x12
    * wifiAddr[1] = 0x34
    * wifiAddr[2] = 0x56
    * wifiAddr[3] = 0x78
    * wifiAddr[4] = 0x90
    * wifiAddr[5] = 0xAC
    */
    
    int tmpCh;
    if (m_bWriteNvram == false)
    {
        for (int i = 0; i < bufSize; i++)
        {
            tmpCh = (pInDatabuf[i] & 15);  //15 -->0000 1111, get Low 4Bits
            if (0 <= tmpCh && tmpCh <= 9)  //0 - 9
            {
                pOutData[(i*2 + 1)] = tmpCh + '0';
            }
            else if (10 <= tmpCh && tmpCh <= 15) //a - f
            {
                pOutData[(i*2 + 1)] = (tmpCh - 10) + 'A';
            }
            
            //tmpCh = ((pInDatabuf[i] >> 4)  & 15);
            tmpCh = ((pInDatabuf[i] & 240) >> 4); //240 -->1111 0000, get High 4Bits
            if (0 <= tmpCh && tmpCh <= 9)  //0 - 9
            {
                pOutData[i*2] = tmpCh + '0';
            }
            else if (10 <= tmpCh && tmpCh <= 15) //A - F
            {
                pOutData[i*2] = (tmpCh - 10) + 'A';
            }           
        }
    } 
    else if(m_bWriteNvram == true)
    {
        strupr(pInDatabuf);       //转换字符串中的小写字母为大写
        for (int i = 0; i < bufSize; i++)
        {
            if ('0'<= pInDatabuf[i*2] && pInDatabuf[i*2] <= '9')
            {
                tmpCh = pInDatabuf[i*2] - '0';
                tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
            }
            else if('A'<= pInDatabuf[i*2] && pInDatabuf[i*2] <= 'F')
            {
                tmpCh = pInDatabuf[i*2] - 'A' + 10;
                tmpCh = ((tmpCh << 4) & 240);  //240 -->1111 0000, get High 4bits
            }
            
            if ('0'<= pInDatabuf[(i*2 + 1)] && pInDatabuf[(i*2 + 1)] <= '9')
            {
                tmpCh += pInDatabuf[(i*2 + 1)] - '0'; //get Low 4bits
            } 
            else if('A'<= pInDatabuf[(i*2 + 1)] && pInDatabuf[(i*2 + 1)] <= 'F')
            {
                tmpCh += pInDatabuf[(i*2 + 1)] - 'A' + 10; //get Low 4bits
            }
            
            pOutData[i] = tmpCh;
        }
    }
    
    return META_SUCCESS;
} 

META_RESULT SNBase::ConductEthernetMacAddrData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize)
{
    //strupr(pInDatabuf);       //转换字符串中的小写字母为大写
    //strlwr(pInDatabuf);       //转换字符串的大写字母为小写
    /*
    * UI input = "1234567890AC" storage in AP nvram will be:
    * ethMacAddr[0] = 0x12
    * ethMacAddr[1] = 0x34
    * ethMacAddr[2] = 0x56
    * ethMacAddr[3] = 0x78
    * ethMacAddr[4] = 0x90
    * ethMacAddr[5] = 0xAC
    *
    * The same as wifi address, so just need to call ConductWifiAddrData() function
    */
    return ConductWifiAddrData(pOutData, RID_para, pInDatabuf, bufSize);
}

META_RESULT SNBase::ConductAudioTemperatureData(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize)
{
    META_RESULT MetaResult = META_SUCCESS;

    AUDIO_SPREAKER_MONITOR_PARAM_STRUCT sWriteTempStruct;
    memset(&sWriteTempStruct, 0, sizeof(AUDIO_SPREAKER_MONITOR_PARAM_STRUCT));
    memcpy(&sWriteTempStruct, pInDatabuf, sizeof(AUDIO_SPREAKER_MONITOR_PARAM_STRUCT));

    if (m_bWriteNvram == true)
    {       
        sWriteTempStruct.temp_initial = atof(pInDatabuf);       
        memcpy(pOutData,  &sWriteTempStruct,  sizeof(AUDIO_SPREAKER_MONITOR_PARAM_STRUCT));
    } 
    else
    {
    	MetaResult = META_FAILED;
    }
	
    return MetaResult;
}

META_RESULT SNBase::Decompose_IMEI(char *pOutData, unsigned short RID_para,  char *pInDatabuf, int bufSize)
{
    META_RESULT MetaResult = META_NVRAM_Decompose_IMEISV(&m_sIMEISV[RID_para-1], pInDatabuf, bufSize);
    if (MetaResult == META_SUCCESS)
    {
        for (int i=0; i<IMEI_ARRAY_LEN; i++)
        {
            pOutData[i] = m_sIMEISV[RID_para-1].imei[i];
        }
    }
    
	return MetaResult;
}

META_RESULT SNBase::Compose_IMEI(char *pOutData, unsigned short RID_para, char *pInDatabuf, int bufSize, bool bChecksum)
{
    META_RESULT MetaResult = META_SUCCESS;
	if(bChecksum)
    {      
        MTRACE(g_hEBOOT_DEBUG, "SNBase::Compose_IMEI(): Calculate checksum bit start...");
        char tmpCh = '0';
		unsigned short checkSum = 0;
    	MetaResult = META_NVRAM_Calculate_IMEI_CD(pInDatabuf, &checkSum);
		if(MetaResult == META_SUCCESS)
		{
            tmpCh += checkSum;
		    pInDatabuf[IMEI_MAX_LENGTH - 1] = tmpCh;
		}
        else
        {
            MTRACE_ERR(g_hEBOOT_DEBUG, "SNBase::Compose_IMEI(): Calculate checksum bit fail, MetaResult = %s", ResultToString(MetaResult));
            return MetaResult;
        }
        MTRACE(g_hEBOOT_DEBUG, "SNBase::Compose_IMEI(): Calculate checksum bit end...");
	}
	
    for (int i=0; i<IMEI_ARRAY_LEN; i++)
    {
        m_sIMEISV[RID_para-1].imei[i] = pInDatabuf[i];
    }
    
    MetaResult = META_NVRAM_Compose_IMEISV_ex(&m_sIMEISV[RID_para-1], pOutData, bufSize, bChecksum);
    return MetaResult;
}

META_RESULT SNBase::REQ_ReadFromModemNVRAM(FT_NVRAM_READ_REQ *psNVRAM_ReadReq, FT_NVRAM_READ_CNF *psNVRAM_ReadCnf)
{
    META_RESULT meta_result;
    meta_result = META_NVRAM_Read_Ex_r(m_hMauiMetaHandle,
        15000,
        psNVRAM_ReadReq,
        psNVRAM_ReadCnf);
    
    if (meta_result != META_SUCCESS)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SNBase::META_NVRAM_Read_Ex_r(): Read nvram data fail! MetaResult = %s", 
            ResultToString(meta_result));
    }

    return meta_result;
}

META_RESULT SNBase::REQ_WriteToModemNVRAM(FT_NVRAM_WRITE_REQ *psNVRAM_WriteReq, FT_NVRAM_WRITE_CNF *psNVRAM_WriteCnf)
{
    META_RESULT meta_result;
    meta_result = META_NVRAM_Write_Ex_r(m_hMauiMetaHandle,
        15000,
        psNVRAM_WriteReq,
        psNVRAM_WriteCnf);
    
    if (meta_result != META_SUCCESS)
    {
        MTRACE_ERR (g_hEBOOT_DEBUG, "SNBase::META_NVRAM_Write_Ex_r(): Write nvram data fail! MetaResult = %s", ResultToString(meta_result));
        return meta_result;
    }

    return meta_result;
}

void SNBase::GetScanData(ScanData_struct &pScanData)
{
    memset(&m_sScanData, 0, sizeof(ScanData_struct));
    
    if (g_sMetaComm.sWriteOption.bWriteBarcode)
    {
        strncpy(m_sScanData.strBarcode, pScanData.strBarcode, strlen(pScanData.strBarcode));
    }
    
    if (g_sMetaComm.sWriteOption.bWriteBT)
    {
        strncpy(m_sScanData.strBTAddr, pScanData.strBTAddr, strlen(pScanData.strBTAddr));
    }
    
    if (g_sMetaComm.sWriteOption.bWriteWifi)
    {
        strncpy(m_sScanData.strWifiAddr, pScanData.strWifiAddr, strlen(pScanData.strWifiAddr));
    }

    if (g_sMetaComm.sWriteOption.bWriteEthernetMac)
    {
        strncpy(m_sScanData.strEthernetMac, pScanData.strEthernetMac, strlen(pScanData.strEthernetMac));
    }

    if (g_sMetaComm.sWriteOption.bWriteDrmkeyMCID)
    {
        strncpy(m_sScanData.strDrmkeyMCID, pScanData.strDrmkeyMCID, strlen(pScanData.strDrmkeyMCID));
    }
    
    if (g_sMetaComm.sWriteOption.bWriteIMEI)
    {
        for (int i = 0; i < g_sMetaComm.sIMEIOption.iImeiNums; i++)
        {
            strncpy(m_sScanData.strIMEI[i], pScanData.strIMEI[i], strlen(pScanData.strIMEI[i]));
        }
        
        if (g_AutoGenData.bAutoGenIMEI && g_sMetaComm.sIMEIOption.iImeiNums >= 2)
        {
            m_bNeedBackupIMEI = true;
            strncpy(m_strBackupIMEI, pScanData.strIMEI[0], strlen(pScanData.strIMEI[0]));
        }
    }

    if (g_sMetaComm.sWriteOption.bWriteSerialNo)
    {
        strncpy(m_sScanData.strSerialNo, pScanData.strSerialNo, strlen(pScanData.strSerialNo));
    }

    
    if (g_sMetaComm.sIMEIOption.bDualIMEISame)
    {
        strncpy(m_sScanData.strIMEI[1], pScanData.strIMEI[0], strlen(pScanData.strIMEI[0]));
    }

	if(g_sMetaComm.eTargetType == C2K)
	{
		if(g_sMetaComm.sWriteOption.bWriteMeid)
			strncpy(m_sScanData.strMeid, pScanData.strMeid, strlen(pScanData.strMeid));
		if(g_sMetaComm.sWriteOption.bWriteEsn)
			strncpy(m_sScanData.strEsn, pScanData.strEsn, strlen(pScanData.strEsn));
	}
    
}

void SNBase::SNThread_Init()
{
    //Get main dialog handle    
    //g_pMainDlg = (CSNWriterDlg*)g_MainDlgHandle;
    
    m_Process = &(g_pMainDlg->m_ProgressSN);
    SetProgress();

    m_bNeedBackupIMEI = false;
    memset(m_strBackupIMEI, 0, IMEI_ARRAY_LEN);
    memset(m_sIMEISV, 0, sizeof(IMEISV_struct_T)*MAX_IMEI_NUMS);
    memset(&m_sScanData, 0, sizeof(ScanData_struct));
    memset(m_strMsg, 0, sizeof(m_strMsg));
    GetScanData(g_sMetaComm.sScanData);

    g_iMetaStopFlag = 0;
    m_hThread = NULL;
    m_iThreadID = 0;
    m_sNVRAM_OPID = 0;
    m_pMetaStopFlag = &g_iMetaStopFlag;
    m_bWriteNvram = false;
    m_bTargetInMetaMode = false;
    m_bStopBeforeUSBInsert = true;
    m_hReadFromNVRAMEvent = NULL;
    m_hWriteToNVRAMEvent = NULL;
	m_bBackupNvramSuccess = false;

	

	if (g_sMetaComm.eTargetType == C2K)
	{
		
		if(g_sMetaComm.sWriteOption.bWriteMeid || g_sMetaComm.sWriteOption.bWriteEsn || g_sMetaComm.sWriteOption.bWriteIMEI || g_sMetaComm.sWriteOption.bWriteBarcode)
		{
			m_bWriteModemNvram = true;
		}
	}
	else
	{
		
		g_sMetaComm.sWriteOption.bWriteMeid = false;
		g_sMetaComm.sWriteOption.bWriteEsn = false;
		if (g_sMetaComm.sWriteOption.bWriteIMEI || g_sMetaComm.sWriteOption.bWriteBarcode)
		{
			m_bWriteModemNvram = true;
			
		}
		else
		{
			m_bWriteModemNvram = false;
		}
	}

    UpdateMsgInfo("");
}

void SNBase::SNThread_Start()
{
    g_iMetaStopFlag = 0;
    m_hThread =  AfxBeginThread(SNBase::ThreadStaticEntryPoint,
        (LPVOID)this,
        THREAD_PRIORITY_NORMAL,
        0,
        0,
        NULL);//用于创建工作线程
}

void SNBase::SNThread_Stop()
{
    g_iMetaStopFlag = BOOT_STOP;
}
