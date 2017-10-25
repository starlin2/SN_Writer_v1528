#ifndef _C2KAGENT_API_DATATYPE_H_
#define _C2KAGENT_API_DATATYPE_H_

#define C2K_BAND_SUPPORT_BC0             (1<<0)
#define C2K_BAND_SUPPORT_BC1             (1<<1)
#define C2K_BAND_SUPPORT_BC2             (1<<2)
#define C2K_BAND_SUPPORT_BC3             (1<<3)
#define C2K_BAND_SUPPORT_BC4             (1<<4)
#define C2K_BAND_SUPPORT_BC5             (1<<5)
#define C2K_BAND_SUPPORT_BC6             (1<<6)
#define C2K_BAND_SUPPORT_BC7             (1<<7)
#define C2K_BAND_SUPPORT_BC8             (1<<8)
#define C2K_BAND_SUPPORT_BC9             (1<<9)
#define C2K_BAND_SUPPORT_BC10            (1<<10)
#define C2K_BAND_SUPPORT_BC11            (1<<11)
#define C2K_BAND_SUPPORT_BC12            (1<<12)
#define C2K_BAND_SUPPORT_BC13            (1<<13)
#define C2K_BAND_SUPPORT_BC14            (1<<14)
#define C2K_BAND_SUPPORT_BC15            (1<<15)

#define C2K_SUPPORT_BAND_COUNT           16

#define C2K_RF_ID_UNKNOWN                0x00000000
#define C2K_RF_ID_MT6158                 0x00000003

#define C2K_LNA_MODE_NUM                 8
#define C2K_NSFT_LIST_MODE_NUM           50

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    C2K_COM_SERIAL,
    C2K_COM_USB,
    C2K_COM_USBLTE,
    C2K_COM_VC
} C2K_COM_TYPE;

typedef enum
{
    C2K_RX_CAL_MAIN_DIV,
    C2K_RX_CAL_MAIN,
    C2K_RX_CAL_DIV
} C2K_RX_CALIBRATION_TYPE;

typedef enum
{
    C2K_AFC_TCXO,
    C2K_AFC_DCXO
} C2K_AFC_CONTROL_MODE;

typedef enum
{
    C2K_TX_SPI,
    C2K_RX_SPI
} C2K_SPI_TYPE;

typedef enum
{
    C2K_RF_MODE_1XRTT,
    C2K_RF_MODE_EVDO,
    C2K_RF_MODE_BOTH
} C2K_RF_MODE;

typedef enum
{
    C2K_CTRL_MODE_AUTO,
    C2K_CTRL_MODE_DISABLE,
    C2K_CTRL_MODE_MANUAL
} C2K_CTRL_MODE;

typedef enum
{
    C2K_LNA_MODE_HIGH,
    C2K_LNA_MODE_MIDDLE,
    C2K_LNA_MODE_LOW
} C2K_LNA_MODE;

// For SIDB access mode
typedef enum
{
    C2K_SIDB_FSI,
    C2K_SIDB_FFS
} C2K_SIDB_ACCESS_MODE;

typedef enum
{
    // OrionC DB segments
    C2K_DB_AFC,
    C2K_DB_TEMPERATURE,
    C2K_DB_TXAGC,
    C2K_DB_TXAGC_FREQ_ADJ,
    C2K_DB_TXAGC_TEMP_ADJ,
    C2K_DB_TX_COUPLE_LOSS,
    C2K_DB_TX_COUPLE_LOSS_FREQ_ADJ,
    C2K_DB_RXAGC_FREQ_ADJ,
    C2K_DB_RXAGC_TEMP_ADJ,
    C2K_DB_DIV_RXAGC_FREQ_ADJ,
    C2K_DB_DIV_RXAGC_TEMP_ADJ,
    C2K_DB_RF_VERSION,
    C2K_DB_MEID,
    C2K_DB_CUSTOM_DATA,
    C2K_DB_TAS_DATA
} C2K_DB_SEGMENT;


typedef struct
{
    BOOL bLog;
    char* szLogPath;
    BOOL bScript;
    char* szScriptPath;
} C2K_LIBCONFIGPARMS, *LPC2K_LIBCONFIGPARMS;

typedef struct
{
    C2K_AFC_CONTROL_MODE eAfcControlMode;
    C2K_RF_MODE eRfMode;
    C2K_RX_CALIBRATION_TYPE eRxCalibrationType;
    C2K_SIDB_ACCESS_MODE eSidbAccessMode;
    BOOL bWriteSIDBFlag;
    UINT uBarcodeLength;
    UINT uPllSettleTime;
    UINT uRxCtrlSettleTime;
    UINT uRxGainStateSettleTime;
    UINT uRxAGCGainTableSelectSettleTime;
    UINT uEnableRxTxSpySettleTime;
    UINT uTxCtrlSettleTime;
    UINT uTxTestRateSettleTime;
    UINT uTxAGCConfigSettleTime;
    BOOL bAFCSlopeStepPerPpmWithQ6;
} PHONEATTRIBUTE_PARMS, *LPPHONEATTRIBUTE_PARMS;

typedef struct
{
    C2K_COM_TYPE eComType;
    UINT uComNum;
} C2K_CONNECT_PARAMS, *LPC2K_CONNECT_PARMS;

typedef struct
{
    unsigned int bandSupport;
    unsigned int rxdBandSupport; //RX diversity band support
    unsigned int rxdEnabled;
    unsigned int paOctLevel; //PA 8 level control or not, 1: 8 levels, 0: 25 levels
    unsigned int rfId; //RF chip ID
    unsigned char cpMajor;
    unsigned char cpMinor;
    unsigned char cpRev;
} C2K_MS_CAPABILITY;

typedef struct
{
    unsigned char ucAction; //0: off, 1: on
    unsigned char ucRfMode; //0: 1xRTT, 1: EVDO, 2: SHDR
    unsigned char ucAntennaBitmap; //Bit0: Rx main, Bit1: Rx diversity, Bit2: Tx path; 0: invalid, 1: valid
    unsigned char ucSampleRate; //0: 8x, 1: 4x, 2: 2x, 3: 1x
    unsigned char ucLogMode; //0: assert mode, 1: period mode
    unsigned short usLogPeriod; //unit: half slot or half PCG
    unsigned short usLogOffset1; //unit: half slot or half PCG
    unsigned short usLogOffset2; //unit: chip
    unsigned short usLogLength1; //unit: half slot or half PCG
    unsigned short usLogLength2; //unit: chip
} LOG_IQ_REQ;

typedef struct
{
    C2K_RF_MODE rfMode;
    C2K_CTRL_MODE ctrlMode;
    unsigned char ucPaMode; //0: high, 1: middle, 2: low
    double prf;
    double paGain;
    double coupleLoss;
    unsigned char ucVm1;
    unsigned char ucVm2;
    unsigned short usVoltCtrl; //unit: mV
    unsigned short ddpcCtrl; //0: bypass DDPC, 6: enable DDPC loop, 7: enable DDPC measurement
} TXAGC_CONFIG_REQ;

typedef struct
{
    double dMainPower;
    double dMainDigiGain;
    int nMainBitSel;
    int nMainDigiGain;
    int nMainGainState;
    double dDivPower;
    double dDivDigiGain;
    int nDivBitSel;
    int nDivDigiGain;
    int nDivGainState;
} C2K_RSSI_CNF;

typedef struct
{
    unsigned short nTxRxDelay; //unit: us
    unsigned short nTxStepLength; //unit: us
    unsigned short nTxRetuneLength; //unit: us
    unsigned short nRxStepLength; //unit: us
    unsigned short nRxRetuneLength; //unit: us
    unsigned char caVm1[22][3];
    unsigned char caVm2[22][3];
    unsigned short naVoltCtrl[22][8]; //unit: mV
} FHC_COMMON_REQ;

typedef struct
{
    unsigned char cRetuneInd;
    unsigned char cBand;
    unsigned short nChannel;
    unsigned char cPaMode; //PA mode: 0:high, 1:middle, 2:low
    unsigned char cSectionIndex; //PA section index
    double prf;
    double paGain;
    double coupleLoss;
} FHC_TX_FREQ_STEP;

typedef struct
{
    unsigned char cTxStepNum;
    FHC_TX_FREQ_STEP txFreqSteps[256];
} FHC_TX_REQ;

typedef struct
{
    unsigned char cRetuneInd;
    unsigned char cBand;
    unsigned short nChannel;
    unsigned char cLnaMode; //0:high, 1:middle, 2:low
    double cellPower;
} FHC_RX_FREQ_STEP;

typedef struct
{
    unsigned char cRxStepNum;
    FHC_RX_FREQ_STEP rxFreqSteps[144];
} FHC_RX_REQ;

typedef struct
{
    unsigned char cReqType; //0: common req, 1: tx req, 2: rx req
    unsigned char cReqNum;
    unsigned char cReqIndex;
    FHC_COMMON_REQ commonReq;
    FHC_TX_REQ txReq;
    FHC_RX_REQ rxReq;
} C2K_FHC_REQ;

typedef struct
{
    unsigned char cCnfNum;
    double pdResult[240];
} FHC_TX_CNF;

typedef struct
{
    unsigned char cCnfNum;
    double mainDigiGain[144];
    double divDigiGain[144];
    char caTemperature[144]; //Centigrade
} FHC_RX_CNF;

typedef struct
{
    unsigned char cCnfId;
    unsigned char cCnfNum;
    unsigned char cCnfIndex;
    FHC_TX_CNF txCnf;
    FHC_RX_CNF rxCnf;
} C2K_FHC_CNF;

/*********** NVRAM Data Structure definition for OrionC Calibration ***********/
typedef struct
{
    unsigned int idType;
    char meid[17];
    char esn[9];
} MEID_TABLE, *LPMEID_TABLE;

typedef struct
{
    unsigned short initDacValue;
    short afcSlopeInv;
    unsigned int capId;
} AFC_TABLE_SEG, *LPAFC_TABLE_SEG;

typedef struct
{
    char tempCelsius;
    unsigned short adcValue;
} TEMPERATURE_PAIR;

typedef struct
{
    TEMPERATURE_PAIR tempPair[8];
} TEMPERATURE_TABLE_SEG, *LPTEMPERATURE_TABLE_SEG;

typedef struct
{
    unsigned short channel;
    double adjData[C2K_LNA_MODE_NUM];
} RXFREQADJ_PAIR;

typedef struct
{
    RXFREQADJ_PAIR freqAdj[16];
} RXFREQADJ_TABLE_SEG, *LPRXFREQADJ_TABLE_SEG;

typedef struct
{
    RXFREQADJ_TABLE_SEG mainTable;
    RXFREQADJ_TABLE_SEG divTable;
} RXFREQADJ_TABLE_SEG_ALL, *LPRXFREQADJ_TABLE_SEG_ALL;

typedef struct
{
    char tempCelsius;
    double adjData;
} RXTEMPADJ_PAIR;

typedef struct
{
    RXTEMPADJ_PAIR tempAdj[8];
} RXTEMPADJ_TABLE_SEG, *LPRXTEMPADJ_TABLE_SEG;

typedef struct  
{
    RXTEMPADJ_TABLE_SEG mainTable;
    RXTEMPADJ_TABLE_SEG divTable;
} RXTEMPADJ_TABLE_SEG_ALL, *LPRXTEMPADJ_TABLE_SEG_ALL;

typedef struct
{
    double paGain; //dBm
    double prf; //dBm
    unsigned short paMode; //0:high, 1:middle, 2:low
    unsigned short vm1;
    unsigned short vm2;
    unsigned short voltCtrl; //mV
} PA_SECTION;

typedef struct
{
    double start; //dBm
    double end; //dBm
} TX_HYSTERESIS;

typedef struct
{
    unsigned char paSectionNum;
    PA_SECTION paSection[8];
    TX_HYSTERESIS txHyst[2];
    short paPhaseComp[3];
} TXAGC_TABLE_SEG, *LPTXAGC_TABLE_SEG;

typedef struct
{
    unsigned short channel;
    double adjData[3];
} TXFREQADJ_PAIR;

typedef struct
{
    TXFREQADJ_PAIR freqAdj[16];
} TXFREQADJ_TABLE_SEG, *LPTXFREQADJ_TABLE_SEG;

typedef struct
{
    char tempCelsius;
    double adjData[3];
} TXTEMPADJ_PAIR;

typedef struct
{
    TXTEMPADJ_PAIR tempAdj[8];
} TXTEMPADJ_TABLE_SEG, *LPTXTEMPADJ_TABLE_SEG;

typedef struct
{
    double coupleLoss[3]; //dB
} TXCOUPLELOSS_TABLE_SEG, *LPTXCOUPLELOSS_TABLE_SEG;

typedef struct
{
    unsigned short channel;
    double adjData;
} TXCOUPLELOSSFREQADJ_PAIR;

typedef struct
{
    TXCOUPLELOSSFREQADJ_PAIR freqAdj[16];
} TXCOUPLELOSSFREQADJ_TABLE_SEG, *LPTXCOUPLELOSSFREQADJ_TABLE_SEG;

typedef struct
{
    unsigned char sysBandClass;
    unsigned char supported;
    unsigned int subClass;
} SUPPORTED_BAND_CLASS_T;

typedef struct
{
    /* BAND A BPI mask */ 
    unsigned int MASK_BAND_A_PR1;
    unsigned int MASK_BAND_A_PR2;
    unsigned int MASK_BAND_A_PR2B;
    unsigned int MASK_BAND_A_PR3;
    unsigned int MASK_BAND_A_PR3A;
    unsigned int MASK_BAND_A_PT1;
    unsigned int MASK_BAND_A_PT2;
    unsigned int MASK_BAND_A_PT2B;
    unsigned int MASK_BAND_A_PT3;
    unsigned int MASK_BAND_A_PT3A;
    unsigned int MASK_BAND_A_RXD_PR1;
    unsigned int MASK_BAND_A_RXD_PR2;
    unsigned int MASK_BAND_A_RXD_PR2B;
    unsigned int MASK_BAND_A_RXD_PR3;
    unsigned int MASK_BAND_A_RXD_PR3A;

    /* BAND B BPI mask */ 
    unsigned int MASK_BAND_B_PR1;
    unsigned int MASK_BAND_B_PR2;
    unsigned int MASK_BAND_B_PR2B;
    unsigned int MASK_BAND_B_PR3;
    unsigned int MASK_BAND_B_PR3A;
    unsigned int MASK_BAND_B_PT1;
    unsigned int MASK_BAND_B_PT2;
    unsigned int MASK_BAND_B_PT2B;
    unsigned int MASK_BAND_B_PT3;
    unsigned int MASK_BAND_B_PT3A;
    unsigned int MASK_BAND_B_RXD_PR1;
    unsigned int MASK_BAND_B_RXD_PR2;
    unsigned int MASK_BAND_B_RXD_PR2B;
    unsigned int MASK_BAND_B_RXD_PR3;
    unsigned int MASK_BAND_B_RXD_PR3A;

    /* BAND C BPI mask */ 
    unsigned int MASK_BAND_C_PR1;
    unsigned int MASK_BAND_C_PR2;
    unsigned int MASK_BAND_C_PR2B;
    unsigned int MASK_BAND_C_PR3;
    unsigned int MASK_BAND_C_PR3A;
    unsigned int MASK_BAND_C_PT1;
    unsigned int MASK_BAND_C_PT2;
    unsigned int MASK_BAND_C_PT2B;
    unsigned int MASK_BAND_C_PT3;
    unsigned int MASK_BAND_C_PT3A;
    unsigned int MASK_BAND_C_RXD_PR1;
    unsigned int MASK_BAND_C_RXD_PR2;
    unsigned int MASK_BAND_C_RXD_PR2B;
    unsigned int MASK_BAND_C_RXD_PR3;
    unsigned int MASK_BAND_C_RXD_PR3A;

    /* Band A Gate BPI mask */
    unsigned int MASK_BAND_A_PRG1;       /* Main Rx On */
    unsigned int MASK_BAND_A_PRG2;
    unsigned int MASK_BAND_A_PRG2B;
    unsigned int MASK_BAND_A_PRG3;       /* Main Rx Off */
    unsigned int MASK_BAND_A_PRG3A;
    unsigned int MASK_BAND_A_PTG1;       /* Tx On */
    unsigned int MASK_BAND_A_PTG2;
    unsigned int MASK_BAND_A_PTG2B;
    unsigned int MASK_BAND_A_PTG3;       /* Tx Off */
    unsigned int MASK_BAND_A_PTG3A;
    unsigned int MASK_BAND_A_RXD_PRG1;   /* Diversity Rx On */
    unsigned int MASK_BAND_A_RXD_PRG2;
    unsigned int MASK_BAND_A_RXD_PRG2B;
    unsigned int MASK_BAND_A_RXD_PRG3;   /* Diversity Rx Off */
    unsigned int MASK_BAND_A_RXD_PRG3A;
   
    /* Band B Gate BPI mask */
    unsigned int MASK_BAND_B_PRG1;       /* Main Rx On */
    unsigned int MASK_BAND_B_PRG2;
    unsigned int MASK_BAND_B_PRG2B;
    unsigned int MASK_BAND_B_PRG3;       /* Main Rx Off */
    unsigned int MASK_BAND_B_PRG3A;
    unsigned int MASK_BAND_B_PTG1;       /* Tx On */
    unsigned int MASK_BAND_B_PTG2;
    unsigned int MASK_BAND_B_PTG2B;
    unsigned int MASK_BAND_B_PTG3;       /* Tx Off */
    unsigned int MASK_BAND_B_PTG3A;
    unsigned int MASK_BAND_B_RXD_PRG1;   /* Diversity Rx On */
    unsigned int MASK_BAND_B_RXD_PRG2;
    unsigned int MASK_BAND_B_RXD_PRG2B;
    unsigned int MASK_BAND_B_RXD_PRG3;   /* Diversity Rx Off */
    unsigned int MASK_BAND_B_RXD_PRG3A;
    
    /* Band C Gate BPI mask */
    unsigned int MASK_BAND_C_PRG1;       /* Main Rx On */
    unsigned int MASK_BAND_C_PRG2;
    unsigned int MASK_BAND_C_PRG2B;
    unsigned int MASK_BAND_C_PRG3;       /* Main Rx Off */
    unsigned int MASK_BAND_C_PRG3A;
    unsigned int MASK_BAND_C_PTG1;       /* Tx On */
    unsigned int MASK_BAND_C_PTG2;
    unsigned int MASK_BAND_C_PTG2B;
    unsigned int MASK_BAND_C_PTG3;       /* Tx Off */
    unsigned int MASK_BAND_C_PTG3A;
    unsigned int MASK_BAND_C_RXD_PRG1;   /* Diversity Rx On */
    unsigned int MASK_BAND_C_RXD_PRG2;
    unsigned int MASK_BAND_C_RXD_PRG2B;
    unsigned int MASK_BAND_C_RXD_PRG3;   /* Diversity Rx Off */
    unsigned int MASK_BAND_C_RXD_PRG3A;

    /* Power Control mask */
    unsigned int MASK_PRPC1;       /* Main Rx On */
    unsigned int MASK_PRPC2;
    unsigned int MASK_PRPC2B;
    unsigned int MASK_PRPC3;       /* Main Rx Off */
    unsigned int MASK_PRPC3A;
    unsigned int MASK_PTPC1;       /* Tx On */
    unsigned int MASK_PTPC2;
    unsigned int MASK_PTPC2B;
    unsigned int MASK_PTPC3;       /* Tx Off */
    unsigned int MASK_PTPC3A;
    unsigned int MASK_RXD_PRPC1;   /* Diversity Rx On */
    unsigned int MASK_RXD_PRPC2;
    unsigned int MASK_RXD_PRPC2B;
    unsigned int MASK_RXD_PRPC3;   /* Diversity Rx Off */
    unsigned int MASK_RXD_PRPC3A;
} BPI_MASK_T;

typedef struct
{
    /* BAND A BPI data */ 
    unsigned int DATA_BAND_A_PR1;
    unsigned int DATA_BAND_A_PR2;
    unsigned int DATA_BAND_A_PR2B;
    unsigned int DATA_BAND_A_PR3;
    unsigned int DATA_BAND_A_PR3A;
    unsigned int DATA_BAND_A_PT1;
    unsigned int DATA_BAND_A_PT2;
    unsigned int DATA_BAND_A_PT2B;
    unsigned int DATA_BAND_A_PT3;
    unsigned int DATA_BAND_A_PT3A;
    unsigned int DATA_BAND_A_RXD_PR1;
    unsigned int DATA_BAND_A_RXD_PR2;
    unsigned int DATA_BAND_A_RXD_PR2B;
    unsigned int DATA_BAND_A_RXD_PR3;
    unsigned int DATA_BAND_A_RXD_PR3A;

    /* BAND B BPI data */ 
    unsigned int DATA_BAND_B_PR1;
    unsigned int DATA_BAND_B_PR2;
    unsigned int DATA_BAND_B_PR2B;
    unsigned int DATA_BAND_B_PR3;
    unsigned int DATA_BAND_B_PR3A;
    unsigned int DATA_BAND_B_PT1;
    unsigned int DATA_BAND_B_PT2;
    unsigned int DATA_BAND_B_PT2B;
    unsigned int DATA_BAND_B_PT3;
    unsigned int DATA_BAND_B_PT3A;
    unsigned int DATA_BAND_B_RXD_PR1;
    unsigned int DATA_BAND_B_RXD_PR2;
    unsigned int DATA_BAND_B_RXD_PR2B;
    unsigned int DATA_BAND_B_RXD_PR3;
    unsigned int DATA_BAND_B_RXD_PR3A;

    /* BAND C BPI data */ 
    unsigned int DATA_BAND_C_PR1;
    unsigned int DATA_BAND_C_PR2;
    unsigned int DATA_BAND_C_PR2B;
    unsigned int DATA_BAND_C_PR3;
    unsigned int DATA_BAND_C_PR3A;
    unsigned int DATA_BAND_C_PT1;
    unsigned int DATA_BAND_C_PT2;
    unsigned int DATA_BAND_C_PT2B;
    unsigned int DATA_BAND_C_PT3;
    unsigned int DATA_BAND_C_PT3A;
    unsigned int DATA_BAND_C_RXD_PR1;
    unsigned int DATA_BAND_C_RXD_PR2;
    unsigned int DATA_BAND_C_RXD_PR2B;
    unsigned int DATA_BAND_C_RXD_PR3;
    unsigned int DATA_BAND_C_RXD_PR3A;

    /* Band A TXGATE data */
    unsigned int DATA_BAND_A_PRG1;       /* Main Rx On */
    unsigned int DATA_BAND_A_PRG2;
    unsigned int DATA_BAND_A_PRG2B;
    unsigned int DATA_BAND_A_PRG3;       /* Main Rx Off */
    unsigned int DATA_BAND_A_PRG3A;
    unsigned int DATA_BAND_A_PTG1;       /* Tx On */
    unsigned int DATA_BAND_A_PTG2;
    unsigned int DATA_BAND_A_PTG2B;
    unsigned int DATA_BAND_A_PTG3;       /* Tx Off */
    unsigned int DATA_BAND_A_PTG3A;
    unsigned int DATA_BAND_A_RXD_PRG1;   /* Diversity Rx On */
    unsigned int DATA_BAND_A_RXD_PRG2;
    unsigned int DATA_BAND_A_RXD_PRG2B;
    unsigned int DATA_BAND_A_RXD_PRG3;   /* Diversity Rx Off */
    unsigned int DATA_BAND_A_RXD_PRG3A;

    /* Band B TXGATE data */
    unsigned int DATA_BAND_B_PRG1;       /* Main Rx On */
    unsigned int DATA_BAND_B_PRG2;
    unsigned int DATA_BAND_B_PRG2B;
    unsigned int DATA_BAND_B_PRG3;       /* Main Rx Off */
    unsigned int DATA_BAND_B_PRG3A;
    unsigned int DATA_BAND_B_PTG1;       /* Tx On */
    unsigned int DATA_BAND_B_PTG2;
    unsigned int DATA_BAND_B_PTG2B;
    unsigned int DATA_BAND_B_PTG3;       /* Tx Off */
    unsigned int DATA_BAND_B_PTG3A;
    unsigned int DATA_BAND_B_RXD_PRG1;   /* Diversity Rx On */
    unsigned int DATA_BAND_B_RXD_PRG2;
    unsigned int DATA_BAND_B_RXD_PRG2B;
    unsigned int DATA_BAND_B_RXD_PRG3;   /* Diversity Rx Off */
    unsigned int DATA_BAND_B_RXD_PRG3A;

    /* Band C TXGATE data */
    unsigned int DATA_BAND_C_PRG1;       /* Main Rx On */
    unsigned int DATA_BAND_C_PRG2;
    unsigned int DATA_BAND_C_PRG2B;
    unsigned int DATA_BAND_C_PRG3;       /* Main Rx Off */
    unsigned int DATA_BAND_C_PRG3A;
    unsigned int DATA_BAND_C_PTG1;       /* Tx On */
    unsigned int DATA_BAND_C_PTG2;
    unsigned int DATA_BAND_C_PTG2B;
    unsigned int DATA_BAND_C_PTG3;       /* Tx Off */
    unsigned int DATA_BAND_C_PTG3A;
    unsigned int DATA_BAND_C_RXD_PRG1;   /* Diversity Rx On */
    unsigned int DATA_BAND_C_RXD_PRG2;
    unsigned int DATA_BAND_C_RXD_PRG2B;
    unsigned int DATA_BAND_C_RXD_PRG3;   /* Diversity Rx Off */
    unsigned int DATA_BAND_C_RXD_PRG3A;

    /* TX Power Control data */
    unsigned int DATA_PRPC1;       /* Main Rx On */
    unsigned int DATA_PRPC2;
    unsigned int DATA_PRPC2B;
    unsigned int DATA_PRPC3;       /* Main Rx Off */
    unsigned int DATA_PRPC3A;
    unsigned int DATA_PTPC1;       /* Tx On */
    unsigned int DATA_PTPC2;
    unsigned int DATA_PTPC2B;
    unsigned int DATA_PTPC3;       /* Tx Off */
    unsigned int DATA_PTPC3A;
    unsigned int DATA_RXD_PRPC1;   /* Diversity Rx On */
    unsigned int DATA_RXD_PRPC2;
    unsigned int DATA_RXD_PRPC2B;
    unsigned int DATA_RXD_PRPC3;   /* Diversity Rx Off */
    unsigned int DATA_RXD_PRPC3A;
} BPI_DATA_T;

typedef struct
{
    // RF Window timing
    unsigned short TC_PR1;
    unsigned short TC_PR2;
    unsigned short TC_PR2B;

    unsigned short TC_PR3;
    unsigned short TC_PR3A;

    unsigned short TC_RXD_PR1;
    unsigned short TC_RXD_PR2;
    unsigned short TC_RXD_PR2B;

    unsigned short TC_RXD_PR3;
    unsigned short TC_RXD_PR3A;

    unsigned short TC_PT1;
    unsigned short TC_PT2;
    unsigned short TC_PT2B;

    unsigned short TC_PT3;
    unsigned short TC_PT3A;

    // RF Gate timing
    unsigned short TC_PRG1;
    unsigned short TC_PRG2;
    unsigned short TC_PRG2B;

    unsigned short TC_PRG3;
    unsigned short TC_PRG3A;

    unsigned short TC_RXD_PRG1;
    unsigned short TC_RXD_PRG2;
    unsigned short TC_RXD_PRG2B;

    unsigned short TC_RXD_PRG3;
    unsigned short TC_RXD_PRG3A;

    unsigned short TC_PTG1;
    unsigned short TC_PTG2;
    unsigned short TC_PTG2B;

    unsigned short TC_PTG3;
    unsigned short TC_PTG3A;

    // RF TX Power Control timing
    short TC_PRPC1;
    short TC_PRPC2;
    short TC_PRPC2B;

    short TC_PRPC3;
    short TC_PRPC3A;

    short TC_RXD_PRPC1;
    short TC_RXD_PRPC2;
    short TC_RXD_PRPC2B;

    short TC_RXD_PRPC3;
    short TC_RXD_PRPC3A;

    short TC_PTPC1;
    short TC_PTPC2;
    short TC_PTPC2B;

    short TC_PTPC3;
    short TC_PTPC3A;
} BPI_TIMING_T;

typedef struct
{
    short dc2DcSettlingTime;
} PA_TIMING_T;

typedef struct
{
    unsigned char BAND_A_CHANNEL_SEL;
    unsigned char BAND_B_CHANNEL_SEL;
    unsigned char BAND_C_CHANNEL_SEL;
} RX_LNA_PORT_SEL_T;

typedef struct
{
    unsigned char BAND_A_OUTPUT_SEL;
    unsigned char BAND_B_OUTPUT_SEL;
    unsigned char BAND_C_OUTPUT_SEL;
} TX_PATH_SEL_T;

typedef struct
{
    unsigned char structVersion; //reserved
    unsigned char isDataUpdate; //reserved
    SUPPORTED_BAND_CLASS_T supportedBand[3];
    BPI_MASK_T bpiMask;
    BPI_DATA_T bpiData;
    BPI_TIMING_T bpiTiming;
    PA_TIMING_T paTiming;
    RX_LNA_PORT_SEL_T rxLnaPortSel;
    RX_LNA_PORT_SEL_T rxDivLnaPortSel;
    TX_PATH_SEL_T txPathSel;
    unsigned char rxDiversityEnable;
    unsigned char rxDiversityTestEnable;
    unsigned char paVddPmuControlEnable;
    unsigned char paVddBattControlEnable;
    unsigned char paVddDc2DcControlEnable;
    unsigned char customTmEnable;
} CUSTOMDATA_TABLE, *LPCUSTOMDATA_TABLE;

typedef struct
{
    char rfOption[21];
    char rfDriverRev[11];
} RFVERSION_TABLE, *LPRFVERSION_TABLE;

typedef struct
{
    UINT uCount;
    bool bAFCEnable;
    UINT uIndex[C2K_NSFT_LIST_MODE_NUM];
    UINT uProtocol[C2K_NSFT_LIST_MODE_NUM];
    UINT uOffset[C2K_NSFT_LIST_MODE_NUM];
    UINT uBand[C2K_NSFT_LIST_MODE_NUM];
    UINT uChannel[C2K_NSFT_LIST_MODE_NUM];
    UINT uWashCode[C2K_NSFT_LIST_MODE_NUM];
    UINT uRadioConfig[C2K_NSFT_LIST_MODE_NUM];
    UINT uNumFrames[C2K_NSFT_LIST_MODE_NUM];
    UINT uPowerCtrlMode[C2K_NSFT_LIST_MODE_NUM];
    float fTxPower[C2K_NSFT_LIST_MODE_NUM];
} NSTLISTMODE_PARMS, *LPNSTLISTMODE_PARMS;

typedef struct
{
    unsigned char tasEnable;
    unsigned char tasInitAntIndex;
    unsigned char forceTxAntEnable;
    unsigned char forceTxAntIndex;
    unsigned int tasMask;
    unsigned int tasData[3][7];
} TASDATA_TABLE, *LPTASDATA_TABLE;

#ifdef __cplusplus
}
#endif

#endif
