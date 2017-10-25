#ifndef _FATAGENT_API_H_
#define _FATAGENT_API_H_

#define __STDCALL __stdcall

#if defined DLL_EXPORT
	#define DECLDIR __declspec(dllexport)
#else
	#define DECLDIR __declspec(dllimport)
#endif

typedef enum {
	AST_CAL_SUCCESS,
	AST_CAL_FAIL
} T_AST_CAL_RESULT;

typedef enum {
	AST_CAL_PA_HIGH ,
	AST_CAL_PA_MID,
	AST_CAL_PA_LOW
} T_AST_CAL_PA_MODE;

typedef enum {
	AST_CAL_AGC_HIGH ,
	AST_CAL_AGC_MID,
	AST_CAL_AGC_LOW
} T_AST_CAL_AGC_MODE;

#define MS_BAND_SUPPORT_A	(1<<0)
#define MS_BAND_SUPPORT_B	(1<<1)
#define MS_BAND_SUPPORT_C	(1<<2)
#define MS_BAND_SUPPORT_D	(1<<3)
#define MS_BAND_SUPPORT_E	(1<<4)
#define MS_BAND_SUPPORT_F	(1<<5)

#define MS_CAPABILITY_FHC           (1<<0)    // fast handset calibration
#define MS_CAPABILITY_NSFT          (1<<1)    // non-signalling final test.capability
#define MS_CAPABILITY_COCRYSTAL     (1<<2)    // gsm/td use same crystal
#define MS_CAPABILITY_COTEMP_CAL	(1<<3)	  // gsm/ts use same temp adc calibration result
#define MS_CAPABILITY_QUERY_EXTENSION	(1<<4)	  // support new capability query interface
#define MS_CAPABILITY_LIST_MODE	    (1<<5)	  // support new capability query interface

#define  TL1D_RF_ID_MT6161    0x0001
#define  TL1D_RF_ID_MT6163    0x0002
#define  TL1D_RF_ID_MT6166    0x0003
#define  TL1D_RF_ID_MT6169    0x0004
#define  TL1D_RF_ID_MT6165    0x0005

#define  TL1D_BB_ID_AST1001    0x0001
#define  TL1D_BB_ID_AST2001    0x0002
#define  TL1D_BB_ID_AST3001_E1    0x0003
#define  TL1D_BB_ID_AST3001_E2    0x0004
#define  TL1D_BB_ID_AST3002_E1    0x0005
//list mode add
#define SEGMENT_NUM_MAX 1
#define CHANNEL_NUM_MAX 2
#define MEAS_RSCP_NUM_MAX 3
typedef struct _T_AST_FHC_START_PARA
{
	unsigned char 		freq_num; // frequency pointer num,1~30
	unsigned short*		freq_list;	// frequency pointer list 
	unsigned char 		agc_freq_retune_num; // AGC frequency retune subframe number
	unsigned char 		agc_step_num;  //  power step number(s) for AGC cal,1~3
	T_AST_CAL_AGC_MODE * agc_mode_list;  //AGC MODE
	unsigned char 		apc_freq_retune_num; // APC frequency retune subframe number
	unsigned char 		apc_step_num;  //power step number(s) for APC cal,1~12
	T_AST_CAL_PA_MODE*  pa_mode_list;	  //PA MODE
	unsigned short*		apc_data_list;   // APC dac
}T_AST_FHC_START_PARA;

typedef struct _T_AST_FHC_START_PARA_EX
{
	unsigned char 		freq_num; // frequency pointer num,1~40
	unsigned short*		freq_list;	// frequency pointer list 

	unsigned char 		agc_freq_retune_num; // AGC frequency retune subframe number,=1
	unsigned char 		agc_step_num;  //  power step number(s) for AGC cal,1~9
	T_AST_CAL_AGC_MODE * agc_mode_list;  //AGC MODE
	unsigned char*		rf_gain;

	unsigned char 		apc_freq_retune_num; // APC frequency retune subframe number,=2
	unsigned char 		pow_step_num;  //tx power step number(s) for APC cal,1~12
	signed char*		pow_list;   // tx power list
}T_AST_FHC_START_PARA_EX;

typedef struct _T_AST_FHC_RESULT_RES
{
	signed short* 		rssi_list; // RSSI result£¬the number of rssi value in the list = freq_num* agc_step_num
}T_AST_FHC_RESULT_RES;

typedef struct _T_AST_FHC_RESULT_EX2_RES
{
	unsigned char freq_num;
	unsigned char agc_step_num;
	unsigned char pow_step_num;
	signed short* 		rssi_list; // RSSI result£¬the number of rssi value in the list = freq_num* agc_step_num
	signed short* 		pd_value_list; // RSSI result£¬the number of rssi value in the list = freq_num* pow_step_num
}T_AST_FHC_RESULT_EX2_RES;

typedef struct _T_AST_RF_TEMP_RESULT
{
    unsigned char ok;
    unsigned int  sum;
} T_AST_RF_TEMP_RESULT;

typedef struct _T_AST_RF_CAPABILITY_ITEM_SET
{
    unsigned int reserved;
} T_AST_RF_CAPABILITY_ITEM_SET;

typedef struct _T_AST_RF_CALIBRATION_ITEM
{
    unsigned int is_capable:1;
    unsigned int is_mandatory:1;
    unsigned int parameter:30;
} T_AST_RF_CALIBRATION_ITEM;

typedef struct _T_AST_RF_CALIBRATION_ITEM_SET
{
    T_AST_RF_CALIBRATION_ITEM tadc_cal;
    T_AST_RF_CALIBRATION_ITEM multi_rat_tadc_bitmap;
    T_AST_RF_CALIBRATION_ITEM multi_rat_afc_bitmap;
    T_AST_RF_CALIBRATION_ITEM apc_cal;
    T_AST_RF_CALIBRATION_ITEM temperature_info;
    T_AST_RF_CALIBRATION_ITEM ex_temp_sensor_info;
	T_AST_RF_CALIBRATION_ITEM ubin_info;
} T_AST_RF_CALIBRATION_ITEM_SET;

typedef struct _T_AST_RF_CAPABILITY_RESULT
{
    unsigned int capability_item_offset;
    unsigned int calibration_item_offset;
    T_AST_RF_CAPABILITY_ITEM_SET capabilityItems;
    T_AST_RF_CALIBRATION_ITEM_SET calibrationItems;
} T_AST_RF_CAPABILITY_RESULT;

typedef struct _T_AST_RF_TEMP_INFO_T
{
	short status;
	short tadc_dac;
	short temperature;
	short temp_idx;
}T_AST_RF_TEMP_INFO_T;
//list mode add
typedef struct _T_AST_LIST_MODE_SYNC
{
	unsigned int        subfn_length;			                  // sync subfn number
    signed   int        ul_pwr;			                        // sync ul power  
	unsigned int        ul_code;			                      // bitmap
	unsigned char       timeslot;			                      // bitmap [bit6 bit5 bit4 bit3 bit2 bit1 bit0]-> [tsn6 tsn5 tsn4 tsn3 tsn2 tsn1 tsn0]
	unsigned short		sync_freq; 
	
}T_AST_LIST_MODE_SYNC;

typedef struct _T_AST_LIST_MODE_STAGE1
{
	unsigned int        subfn_length;			                 
	
    signed   int        dl_rscp;			                         
    unsigned int        dl_timeslot_stage1;	
    unsigned int        dl_code_stage1;	
  
    unsigned int        ul_timeslot_stage1;	
    unsigned int        ul_code_stage1;	
    signed   int        ul_pwr;		
  
	
		
}T_AST_LIST_MODE_STAGE1;

typedef struct _T_AST_LIST_MODE_STAGE2
{
	unsigned int        subfn_length;     			// maximum subfn number of -20dBm tx power(2 subframes) and rscp measurement(3 subframes), default is 3 subframes

	signed   int        dl_rscp[MEAS_RSCP_NUM_MAX]; // 3 dl power
	unsigned int        dl_timeslot_stage2;         // Bitmap, [bit6 bit5 bit4 bit3 bit2 bit1 bit0] -> [ts6 ts5 ts4 ts3 ts2 ts1 ts0]
    unsigned int        dl_code_stage2;             // Bitmap
	
    unsigned char       ul_timeslot_stage2;         // Bitmap, [bit6 bit5 bit4 bit3 bit2 bit1 bit0] -> [ts6 ts5 ts4 ts3 ts2 ts1 ts0]
    unsigned int        ul_code_stage2;             // Bitmap
	signed   int        ul_pwr;    
  
		
}T_AST_LIST_MODE_STAGE2;

typedef struct _T_AST_LIST_MODE_STAGE3
{
    unsigned int        subfn_length;               // CLPC subfn number, default is 32 subframes
    
    unsigned char       ul_timeslot_stage3;         // Bitmap, [bit6 bit5 bit4 bit3 bit2 bit1 bit0] -> [ts6 ts5 ts4 ts3 ts2 ts1 ts0]
    unsigned int        ul_code_stage3;             // Bitmap
}T_AST_LIST_MODE_STAGE3;


typedef struct _T_AST_LIST_MODE_SEGMENT_PARA
{
	unsigned int           freq_num;
    unsigned short         uarfcn[CHANNEL_NUM_MAX];    // UARFCN
    unsigned char          b_stage1_valid;             // 0 - invalid, 1 - valid
    unsigned char          b_stage2_valid;             // 0 - invalid, 1 - valid
	unsigned char          b_stage3_valid;             // 0 - invalid, 1 - valid
	 
	T_AST_LIST_MODE_SYNC    sync_info;
	T_AST_LIST_MODE_STAGE1  stage1_info;
	T_AST_LIST_MODE_STAGE2  stage2_info;
	T_AST_LIST_MODE_STAGE3  stage3_info;
	
}T_AST_LIST_MODE_SEGMENT_PARA;

typedef struct _T_AST_LSIT_MODE_PARA
{
	unsigned short		cp_id;  					// CPID for the midamble selection 
	unsigned char       dl_k;                       // DL midamble config, [8,16]
	unsigned char       ul_k;                       // UL midamble config, [8,16]
	unsigned int 		switch_band_timedelay;		// time delay while switching band, the default value is 0, need to confirm with tester
	unsigned char		b_afc_dac_valid;			// 0 - invalid, 1 - valid, the default value is invalid
	unsigned short    	afc_dac;					// Determined by b_afc_dac_valid, the default value is 0
	
	T_AST_LIST_MODE_SEGMENT_PARA segment[SEGMENT_NUM_MAX];
	       
}T_AST_LSIT_MODE_PARA;
typedef struct _T_AST_LIST_MODE_GETBER_RES
{
	unsigned int total_bits[SEGMENT_NUM_MAX][CHANNEL_NUM_MAX];
	unsigned int error_bits[SEGMENT_NUM_MAX][CHANNEL_NUM_MAX];
	signed   short  rscp[MEAS_RSCP_NUM_MAX];         // FXP - S7.8 or S13.3
}T_AST_LIST_MODE_GETBER_RES;
typedef struct _T_AST_RFCAL_UBIN_MODE
{
       
    unsigned short        ubin_tdd_mode_init;           // 1: init TDD   ,0 :  de-init TDD
}T_AST_RFCAL_UBIN_MODE;

//2.2	API
extern "C"{ 

	//1)	AFC
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_afc_start(
		int ms_timeout, 
		unsigned short freq, 
		unsigned short afc_dac,
		T_AST_CAL_PA_MODE  pa_mode, 
		unsigned short apc_data,
		unsigned short cap_id //for ast3001
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_afc_start_r(
		int meta_handle, 
		int ms_timeout, 
		unsigned short freq, 
		unsigned short afc_dac,
		T_AST_CAL_PA_MODE  pa_mode, 
		unsigned short apc_data,
		unsigned short cap_id //for ast3001
		);

	//2)	AGC
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_agc(
		int ms_timeout, 
		unsigned short freq, 
		unsigned short afc_dac, 
		T_AST_CAL_AGC_MODE agc_mode,
		unsigned char rf_gain, 
		bool bTracking,		
		signed char * rssi,
		unsigned short *power, 
		unsigned char *used_gain
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_agc_r(
		int meta_handle, 
		int ms_timeout, 
		unsigned short freq, 
		unsigned short afc_dac, 
		T_AST_CAL_AGC_MODE agc_mode,
		unsigned char rf_gain, 
		bool bTracking,		
		signed char * rssi,
		unsigned short *power, 
		unsigned char *used_gain
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_agc_ex(
		int ms_timeout, 
		unsigned short freq, 
		unsigned short afc_dac, 
		T_AST_CAL_AGC_MODE agc_mode,
		unsigned char rf_gain, 
		bool bTracking,		
		signed short * rssi,
		unsigned short *power, 
		unsigned char *used_gain
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_agc_ex_r(
		int meta_handle, 
		int ms_timeout, 
		unsigned short freq, 
		unsigned short afc_dac, 
		T_AST_CAL_AGC_MODE agc_mode,
		unsigned char rf_gain, 
		bool bTracking,		
		signed short * rssi,
		unsigned short *power, 
		unsigned char *used_gain
		);

	//3)	APC
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_apc_start(
		int ms_timeout, 
		unsigned short freq, 
		unsigned short afc_dac, 
		T_AST_CAL_PA_MODE pa_mode, 
		unsigned short apc_data,
		unsigned char ts_bmp,//UL Timeslot bitmap
		unsigned char mod_bmp//modulation(QPSK/16QAM) bitmap
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_apc_start_r(
		int meta_handle, 
		int ms_timeout, 
		unsigned short freq, 
		unsigned short afc_dac, 
		T_AST_CAL_PA_MODE pa_mode, 
		unsigned short apc_data,
		unsigned char ts_bmp,//UL Timeslot bitmap
		unsigned char mod_bmp//modulation(QPSK/16QAM) bitmap
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_apc_start_ex(
		int ms_timeout, 
		unsigned short freq, 
		unsigned short afc_dac, 
		T_AST_CAL_PA_MODE pa_mode, 
		unsigned short apc_data,
		unsigned char ts_bmp,//UL Timeslot bitmap
		unsigned char mod_bmp,//modulation(QPSK/16QAM) bitmap
		bool powerfix,//0:tx power not fixed(default=0),1:fix tx power
		signed char power//tx power value
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_apc_start_ex_r(
		int meta_handle, 
		int ms_timeout, 
		unsigned short freq, 
		unsigned short afc_dac, 
		T_AST_CAL_PA_MODE pa_mode, 
		unsigned short apc_data,
		unsigned char ts_bmp,//UL Timeslot bitmap
		unsigned char mod_bmp,//modulation(QPSK/16QAM) bitmap
		bool powerfix,//0:tx power not fixed(default=0),1:fix tx power
		signed char power//tx power value
		);



	//4)	Stop
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_stop(int ms_timeout);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_stop_r(int meta_handle,int ms_timeout);

	//5)	Reset
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_tl1_reset(int ms_timeout); // trigger TDL1 to read calibration  data from NVRAM
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_tl1_reset_r(int meta_handle,int ms_timeout);

	//6)	Get Version number of fta agent dll
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_get_verion(unsigned int *ver);

	//7)	Get ChipID
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_get_chipid(
		int ms_timeout, 
		unsigned short      *BB_chipID,
		unsigned short      *RF_chipID
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_get_chipid_r(
		int meta_handle, 
		int ms_timeout, 
		unsigned short      *BB_chipID,
		unsigned short      *RF_chipID
		);

	//8)	Get Ms Capability
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_get_capability(
		int ms_timeout, 
		unsigned short*      capability,
		unsigned short*      band_support
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_get_capability_r(
		int meta_handle,
		int ms_timeout,
		unsigned short*      capability,
		unsigned short*      band_support
		);
	//9)	Read ABB register
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_read_abb_reg(
		int ms_timeout,
		unsigned short addr,
		unsigned short *val
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_read_abb_reg_r(
		int meta_handle,
		int ms_timeout,
		unsigned short addr,
		unsigned short *val
		);

	//10)	Write ABB register
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_write_abb_reg(
		int ms_timeout,
		unsigned short addr,
		unsigned short val
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_write_abb_reg_r(
		int meta_handle,
		int ms_timeout,
		unsigned short addr,
		unsigned short val
		);

	//11)	query API
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_QueryAPISupported(
		int ms_timeout,
		const char *func_name
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_QueryAPISupported_r(
		int meta_handle,
		int ms_timeout,
		const char *func_name
		);

	//12)	Get PAStage
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_get_pastage(
		int ms_timeout, 
		unsigned short      *stage
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_get_pastage_r(
		int meta_handle, 
		int ms_timeout, 
		unsigned short      *stage
		);

	//13) Get PD measurement result
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_get_pdmeasurement(
		int ms_timeout, 
		signed short      *pd
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_CAL_get_pdmeasurement_r(
		int meta_handle, 
		int ms_timeout, 
		signed short      *pd
		);


//-----------------------------FOR NSFT---------------
	//1)	NSFT Start
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_NSFT_Start(
		int 				ms_timeout,

		unsigned short  	dpch_freq,  // UARFCN
		unsigned short  	cp_id,  // CPID for the midamble selection

		unsigned char  		dl_timeslot,  // 0-6,DL Timeslot, support 1 TS only(0 for TS0,1 for TS1¡­)
		unsigned int 		dl_code,  /* DL TS channel code bitmap
										bit0 is C16-1 
                                        bit1 is C16-2 
                                        ...
                                        bit 15 is C16-16 
                                        bit16 is C8-1 
                                        ...
                                        bit23 is C8-8 
                                        bit24 is C4-1
										...
                                        bit27 is C4-4 
                                        bit28 is C2-1 
                                        bit29 is C2-2 
                                        bit30 is C1-1
                                        bit31 is reserved.*/
		unsigned char     	ul_timeslot,// 0-6,UL Timeslot, support 1 TS only(0 for TS0,1 for TS1¡­)
		unsigned int    	ul_code, /* UL TS channel code bitmap
										bit0 is C16-1 
                                        bit1 is C16-2 
                                        ...
                                        bit 15 is C16-16 
                                        bit16 is C8-1 
                                        ...
                                        bit23 is C8-8 
                                        bit24 is C4-1
										...
                                        bit27 is C4-4 
                                        bit28 is C2-1 
                                        bit29 is C2-2 
                                        bit30 is C1-1
                                        bit31 is reserved.*/

		bool     			single_end_loop_enable, //switch for the single ended BER
		bool 				b_afc_dac_valid,//indicate if using the AFC DAC below
		unsigned short    	afc_dac,    // AFC DAC set by META
		unsigned char     	loopbackType,  // Loopback type  BER/BLER type, 0 for BER, 1 for BLER
		bool     			b_bit_pattern_allzero,  // all 1 or all zero
		signed char			ul_dpdch_pwr,  // UL target power for the output loop power control 
		unsigned char		ul_ma		//UL midamble config,[8,16]
		//,unsigned char     	ul_tpc_step//ul tpc step,[1,2,3]
		); 
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_NSFT_Start_r(
		int 				meta_handle,
		int 				ms_timeout,

		unsigned short  	dpch_freq,  // UARFCN
		unsigned short  	cp_id,  // CPID for the midamble selection

		unsigned char  		dl_timeslot,  // DL Timeslot, support 1 TS only(0 for TS0,1 for TS1¡­)
		unsigned int 		dl_code,  /* DL TS channel code bitmap
										bit0 is C16-1 
                                        bit1 is C16-2 
                                        ...
                                        bit 15 is C16-16 
                                        bit16 is C8-1 
                                        ...
                                        bit23 is C8-8 
                                        bit24 is C4-1
										...
                                        bit27 is C4-4 
                                        bit28 is C2-1 
                                        bit29 is C2-2 
                                        bit30 is C1-1
                                        bit31 is reserved.*/
		unsigned char     	ul_timeslot,// 0-6,UL Timeslot, support 1 TS only(0 for TS0,1 for TS1¡­)
		unsigned int    	ul_code, /* UL TS channel code bitmap
										bit0 is C16-1 
                                        bit1 is C16-2 
                                        ...
                                        bit 15 is C16-16 
                                        bit16 is C8-1 
                                        ...
                                        bit23 is C8-8 
                                        bit24 is C4-1
										...
                                        bit27 is C4-4 
                                        bit28 is C2-1 
                                        bit29 is C2-2 
                                        bit30 is C1-1
                                        bit31 is reserved.*/

		bool     			single_end_loop_enable, //switch for the single ended BER
		bool 			b_afc_dac_valid,//indicate if using the AFC DAC below
		unsigned short    	afc_dac,    // AFC DAC set by META
		unsigned char     	loopbackType,  // Loopback type  BER/BLER type, 0 for BER, 1 for BLER
		bool     			b_bit_pattern_allzero,  // all 1 or all zero
		signed char		ul_dpdch_pwr,  // UL target power for the output loop power control 
		unsigned char		ul_ma		//UL midamble config,[8,16]
		//,unsigned char     	ul_tpc_step//ul tpc step,[1,2,3]
		);

	//2)	NSFT Get BER
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_NSFT_GetBitCount(
		int 				ms_timeout,
		unsigned int *		total_bits,	//total bits received between 2 GetBER commands
		unsigned int *		error_bits //total error bits received between 2 GetBER commands
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_NSFT_GetBitCount_r(
		int 				meta_handle,
		int 				ms_timeout,
		unsigned int *		total_bits, //total bits received between 2 GetBER commands
		unsigned int *		error_bits //total error bits received between 2 GetBER commands
		);

	//3)	NSFT Stop
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_NSFT_Stop(
		int 				ms_timeout
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_NSFT_Stop_r(
		int 				meta_handle,
		int 				ms_timeout
		);

	//4)	NSFT modfy
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_NSFT_Modify(
		int 				ms_timeout,
		signed char			ul_dpdch_pwr,// UL target power for the output loop power control 
		unsigned char     	ul_tpc_step//ul tpc step,[1,2,3]
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_NSFT_Modify_r(
		int 				meta_handle,
		int 				ms_timeout,
		signed char			ul_dpdch_pwr,// UL target power for the output loop power control 
		unsigned char     	ul_tpc_step//ul tpc step,[1,2,3]
		);

	//5)	NSFT Get RSCP
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_NSFT_GetRscp(
		int 				ms_timeout,
		signed short *		rscp
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_NSFT_GetRscp_r(
		int 				meta_handle,
		int 				ms_timeout,
		signed short *		rscp
		);

//-----------------------------FOR RF TEST---------------
	//1)	RX ON/OFF
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_RFTEST_RXOn(
		int 				ms_timeout,
		unsigned short		freq, 
		bool				bOn //on/off
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_RFTEST_RXOn_r(
		int 				meta_handle,
		int 				ms_timeout,
		unsigned short		freq, 
		bool				bOn //on/off
		);

	//2)	TX ON/OFF
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_RFTEST_TXOn(
		int 				ms_timeout,
		unsigned short		freq, 
		bool				bOn //on/off
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_RFTEST_TXOn_r(
		int 				meta_handle,
		int 				ms_timeout,
		unsigned short		freq, 
		bool				bOn //on/off
		);

//-----------------------------FOR FHC---------------
	//1) FHC START
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_start(
		int 				ms_timeout,
		T_AST_FHC_START_PARA		*para
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_start_r(
		int 				meta_handle,
		int 				ms_timeout,
		T_AST_FHC_START_PARA		*para
		);

	//1) FHC START EX
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_start_ex(
		int 				ms_timeout,
		T_AST_FHC_START_PARA_EX		*para
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_start_ex_r(
		int 				meta_handle,
		int 				ms_timeout,
		T_AST_FHC_START_PARA_EX		*para
		);

	//) FHC START EX2
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_start_ex2(
		int 				ms_timeout,
		T_AST_FHC_START_PARA_EX		*para
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_start_ex2_r(
		int 				meta_handle,
		int 				ms_timeout,
		T_AST_FHC_START_PARA_EX		*para
		);

	//2) FHC CHECK STATUS
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_check(
		int 				ms_timeout,
		bool* 			is_finished  // true: FHC is finished; false: FHC is not finished
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_check_r(
		int 				meta_handle,
		int 				ms_timeout,
		bool* 			is_finished  // true: FHC is finished; false: FHC is not finished
		);

	//3) FHC GET RESULT
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_get_result(
		int 				ms_timeout,
		T_AST_FHC_RESULT_RES* res
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_get_result_r(
		int 				meta_handle,
		int 				ms_timeout,
		T_AST_FHC_RESULT_RES* res
		);
	//3) FHC GET RESULT EX
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_get_result_ex(
		int 				ms_timeout,
		T_AST_FHC_RESULT_RES* res
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_get_result_ex_r(
		int 				meta_handle,
		int 				ms_timeout,
		T_AST_FHC_RESULT_RES* res
		);

	//) FHC GET RESULT EX2
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_get_result_ex2(
		int 				ms_timeout,
		T_AST_FHC_RESULT_EX2_RES* res
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_FHC_get_result_ex2_r(
		int 				meta_handle,
		int 				ms_timeout,
		T_AST_FHC_RESULT_EX2_RES* res
		);

	DECLDIR T_AST_CAL_RESULT __STDCALL AST_GetRfTemperature(
		const unsigned int ms_timeout,
        const unsigned short measure_count, /* [IN] the number of measurement performed by L1 */
        T_AST_RF_TEMP_RESULT* res /* [OUT] the sum of the specified number of measurement */
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_GetRfTemperature_r(
		const int meta_handle,
		const unsigned int ms_timeout,
        const unsigned short measure_count, /* [IN] the number of measurement performed by L1 */
		T_AST_RF_TEMP_RESULT* res /* [OUT] the sum of the specified number of measurement */
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_GetRfCapability(
		const unsigned int ms_timeout,
        T_AST_RF_CAPABILITY_RESULT* res, /* [OUT] the RF capability provided by L1 */
        const unsigned int res_length /* [IN] length of the input buffer */
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_GetRfCapability_r(
		const int meta_handle,
		const unsigned int ms_timeout,
		T_AST_RF_CAPABILITY_RESULT* res, /* [OUT] the RF capability provided by L1 */
        const unsigned int res_length /* [IN] length of the input buffer */
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_GetTemperatureInfo(
		const unsigned int ms_timeout,
		T_AST_RF_TEMP_INFO_T* info
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_GetTemperatureInfo_r(
		const int meta_handle, 
		const unsigned int ms_timeout,
		T_AST_RF_TEMP_INFO_T* info
		);
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_LIST_MODE_start(
	    const unsigned int ms_timeout,
	    T_AST_LSIT_MODE_PARA* list_mode_para,
	    T_AST_LIST_MODE_GETBER_RES* list_mode_ber
	    );
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_LIST_MODE_start_r(
		const int meta_handle, 
	    const unsigned int ms_timeout,
	    T_AST_LSIT_MODE_PARA* list_mode_para,
	    T_AST_LIST_MODE_GETBER_RES* list_mode_ber
	    );
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_UBIN_MODE_SETUP(
	    const unsigned int ms_timeout,
	    T_AST_RFCAL_UBIN_MODE* ubin_tdd_mode_init
	    );
	DECLDIR T_AST_CAL_RESULT __STDCALL AST_UBIN_MODE_SETUP_r(
		const int meta_handle, 
	    const unsigned int ms_timeout,
	    T_AST_RFCAL_UBIN_MODE* ubin_tdd_mode_init
	    );
}
#endif //_FATAGENT_API_H_