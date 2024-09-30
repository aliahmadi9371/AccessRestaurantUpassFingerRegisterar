
#ifndef _UCSAPI_TYPE_H
#define _UCSAPI_TYPE_H

#include "UCSAPI_Basic.h"
#include "UCBioAPI_Export.h"

/* Basic type define */
#define UCSAPI_FINGER_NUMBER_MAX		10
#define UCSAPI_CARD_NUMBER_MAX			5
#define UCSAPI_ACCESS_TIMEZONE_MAX		128
#define UCSAPI_ACCESS_HOLIDAY_MAX		64
#define UCSAPI_ACCESS_TIME_MAX			128
#define UCSAPI_ACCESS_GROUP_MAX			128
#define UCSAPI_MESSAGE					128
#define UCSAPI_SMARTCARD_SECTOR_MAX		128
#define UCSAPI_MAX_FACE_NUMBER			10

typedef UCSAPI_UINT32 UCSAPI_DATA_SIZE;
	#define UCSAPI_DATA_SIZE_PASSWORD			8
#ifdef _ARMY_HEAD
	#define UCSAPI_DATA_SIZE_RFID				34
#elif _ARMY_HEAD2
	#define UCSAPI_DATA_SIZE_RFID				40
#else
	#define UCSAPI_DATA_SIZE_RFID				24
#endif

	#define UCSAPI_DATA_SIZE_USER_NAME			16
	#define UCSAPI_DATA_SIZE_UNIQUE_ID			20
	#define UCSAPI_DATA_SIZE_CODE4				4
	#define UCSAPI_DATA_SIZE_PICTURE			7168

// Define Authtype String(middle number is AuthType value)
#define AUTHTYPE_00_NONE				"None"		// Not use ==> make auth method value from user property
#define AUTHTYPE_01_FP					"FP"
#define AUTHTYPE_02_FP_CARD				"FP-Card"
#define AUTHTYPE_03_PW					"PW"
#define AUTHTYPE_04_CD					"Card"
#define AUTHTYPE_05_CD_OR_FP			"Card or FP"
#define AUTHTYPE_06_CD_AND_FP			"Card & FP"
#define AUTHTYPE_07_CD_OR_PW			"Card or PW"
#define AUTHTYPE_08_CD_AND_PW			"Card & PW"
#define AUTHTYPE_09_ID_OR_CD_AND_FP		"(ID or Card) & FP"
#define AUTHTYPE_10_ID_OR_CD_AND_PW		"(ID or Card) & PW"
#define AUTHTYPE_11_FP_AND_PW			"FP & PW"
#define AUTHTYPE_12_FP_OR_PW			"FP or PW"
#define AUTHTYPE_13_CD_AND_PW_AND_FP	"Card & PW & FP"
// Add by Face(AC7000)
#define AUTHTYPE_14_FA					"FA"
#define AUTHTYPE_15_FA_OR_PW			"FA or PW"
#define AUTHTYPE_16_CD_OR_FA			"Card or FA"
#define AUTHTYPE_17_FP_OR_FA			"FP or FA"
#define AUTHTYPE_18_CD_OR_FP_OR_FA		"Card or FP or FA"
#define AUTHTYPE_19_CD_AND_FA			"Card & FA"
#define AUTHTYPE_20_ID_FA_OR_CD_FA		"(ID or Card) and FA"
#define AUTHTYPE_21_FP_AND_FA			"FP & FA"
#define AUTHTYPE_22_FA_AND_PW			"FA & PW"
#define AUTHTYPE_23_CD_AND_FP_AND_FA	"Card & FP & FA"
#define AUTHTYPE_24_CD_AND_FA_AND_PW	"Card & FA & PW"
#define AUTHTYPE_25_FP_AND_FA_AND_PW	"FP & FA & PW"
#define AUTHTYPE_26_CD_AND_FP_AND_FA_AND_PW	"Card & FP & FA & PW"

/* Gerneral type define */
typedef struct ucsapi_data
{
	UCSAPI_UINT32	Length;				/* just length of Data (not sizeof structure) */
	UCSAPI_VOID_PTR	Data;
	
} UCSAPI_DATA, *UCSAPI_DATA_PTR;

typedef struct ucsapi_protocol_version
{
	UCSAPI_UINT32 Major;
	UCSAPI_UINT32 Minor;
} UCSAPI_PROTOCOL_VERSION, *UCSAPI_PROTOCOL_VERSION_PTR;

typedef struct ucsapi_code4 
{
	UCSAPI_CHAR			Code[UCSAPI_DATA_SIZE_CODE4];
} UCSAPI_CODE4, *UCSAPI_CODE4_PTR;

typedef struct ucsapi_date_time_info
{
	UCSAPI_UINT16		Year;
	UCSAPI_UINT8		Month;
	UCSAPI_UINT8		Day;
	UCSAPI_UINT8		Hour;
	UCSAPI_UINT8		Min;
	UCSAPI_UINT8		Sec;
	UCSAPI_UINT8		Reserved;
} UCSAPI_DATE_TIME_INFO, *UCSAPI_DATE_TIME_INFO_PTR;

typedef struct ucsapi_date_yyyy_mm_dd
{
	UCSAPI_UINT16	Year;
	UCSAPI_UINT8	Month;
	UCSAPI_UINT8	Day;
} UCSAPI_DATE_YYYY_MM_DD, *UCSAPI_DATE_YYYY_MM_DD_PTR;

typedef struct ucsapi_date_mm_dd
{
	UCSAPI_UINT16		Month;
	UCSAPI_UINT16		Day;
} UCSAPI_DATE_MM_DD, *UCSAPI_DATE_MM_DD_PTR;

typedef struct ucsapi_time_hh_mm
{
	UCSAPI_UINT8	Hour;
	UCSAPI_UINT8	Minute;
} UCSAPI_TIME_HH_MM, *UCSAPI_TIME_HH_MM_PTR;

typedef struct ucsapi_peripheral_device
{
	UCSAPI_SINT32	DeviceID;
	UCSAPI_SINT32	ControlCommand;
} UCSAPI_PERIPHERAL_DEVICE, *UCSAPI_PERIPHERAL_DEVICE_PTR;

/* User information related type define */
typedef UCSAPI_UINT32	UCSAPI_ACCESS_DATE_TYPE;
	#define UCSAPI_DATE_TYPE_NOT_USE						0
	#define UCSAPI_DATE_TYPE_ALLOWED						1
	#define UCSAPI_DATE_TYPE_RESTRICTION					2

typedef struct ucsapi_user_property
{
	UCSAPI_UINT8	Finger		:1;
	UCSAPI_UINT8	FPCard		:1;
	UCSAPI_UINT8	Password	:1;
	UCSAPI_UINT8	Card		:1;
	UCSAPI_UINT8	CardID      :1;
	UCSAPI_UINT8	Operation   :1;
	UCSAPI_UINT8	Identify	:1;
	UCSAPI_UINT8	Admin		:1;
} UCSAPI_USER_PROPERTY, *UCSAPI_USER_PROPERTY_PTR;

typedef struct access_flag
{
	BYTE	blacklist		:1; // Black List Flag
	BYTE    Face1toN		:1;	// Face 1:N ??(0=only 1:1, 1=1:1 or 1:N)
	BYTE	reserved		:5;
	BYTE	exceptpassback	:1; // Except Passback Flag
} ACCESS_FLAG;

typedef struct ucsapi_access_date
{
	UCSAPI_DATE_YYYY_MM_DD		StartDate;
	UCSAPI_DATE_YYYY_MM_DD		EndDate;
} UCSAPI_ACCESS_DATE, *UCSAPI_ACCESS_DATE_PTR, UCSAPI_DATE_PERIOD, *UCSAPI_DATE_PERIOD_PTR;

typedef struct ucsapi_access_authority
{
	UCSAPI_DATA_PTR				AccessGroup;
	UCSAPI_ACCESS_DATE_TYPE		AccessDateType;
	UCSAPI_ACCESS_DATE_PTR		AccessDate; 
} UCSAPI_ACCESS_AUTHORITY, *UCSAPI_ACCESS_AUTHORITY_PTR;

typedef struct ucsapi_card_data
{
	UCSAPI_UINT32				CardNum;
	UCSAPI_DATA_PTR				RFID[UCSAPI_CARD_NUMBER_MAX];
} UCSAPI_CARD_DATA, *UCSAPI_CARD_DATA_PTR;

// This structure changed at 8.March.2011 
typedef struct ucsapi_finger_data
{
	UCSAPI_UINT8				SecurityLevel;
	UCSAPI_UINT8				TemplateFormat; // Default : UCBioAPI_TEMPLATE_FORMAT_UNION400
//	UCSAPI_UINT8				DuressFingerIndex; // 0=N/A, 1 ~ 10:Dudess FingerID, ==> change to DuressFinger array
	UCSAPI_UINT8				DuressFinger[10];  // 0:Normal, 1:Duress Finger (index is finger ID - 1)
	UCSAPI_BOOL					IsCheckSimilarFinger;
	UCBioAPI_EXPORT_DATA_PTR	ExportData;
} UCSAPI_FINGER_DATA, *UCSAPI_FINGER_DATA_PTR;

typedef struct ucsapi_face_info
{
	long Length;
	BYTE* Data;
} UCSAPI_FACE_INFO, *UCSAPI_FACE_INFO_PTR;

typedef struct ucsapi_fp_minutiae
{
	BYTE minType;	// Def 0
	BYTE minCount;	// Def 2
	BYTE matching;	// Matching Result
	long lenData;	// Real Data Length(minData Size ==> Def:800) 
	BYTE* minData;	// Fingerprint Minutiae Data
} UCSAPI_FP_MINUTIAE, *UCSAPI_FP_MINUTIAE_PTR;

typedef struct ucsapi_face_data
{
	long FaceNumber;
	UCSAPI_FACE_INFO_PTR	FaceInfo[UCSAPI_MAX_FACE_NUMBER];
} UCSAPI_FACE_DATA, *UCSAPI_FACE_DATA_PTR;

typedef struct ucsapi_auth_data
{
	UCSAPI_DATA_PTR				Password;
	UCSAPI_CARD_DATA_PTR		Card;
	UCSAPI_FINGER_DATA_PTR		Finger;
	UCSAPI_FACE_DATA_PTR		Face;
} UCSAPI_AUTH_DATA, *UCSAPI_AUTH_DATA_PTR;

typedef struct ucsapi_picture_header
{
	UCSAPI_UINT8				Format[4];		/* must be "JPG" */
	UCSAPI_UINT32				Length;			/* max Length is 7 Kbytes */
} UCSAPI_PICTURE_HEADER, *UCSAPI_PICTURE_HEADER_PTR;

typedef struct ucsapi_picture_data
{
	UCSAPI_PICTURE_HEADER		Header;
	UCSAPI_UINT8*				Data;
} UCSAPI_PICTURE_DATA, *UCSAPI_PICTURE_DATA_PTR; 

typedef struct ucsapi_user_info
{
	UCSAPI_UINT32				UserID;
	UCSAPI_DATA_PTR				UserName;
	UCSAPI_DATA_PTR				UniqueID;
	UCSAPI_USER_PROPERTY		Property;
	UCSAPI_UINT8				AuthType;	// 1..26 : ref Upper AuthType Define(1:FP,..., 26: Card & FP & FA & PW)
	ACCESS_FLAG					AcessFlag;
	UCSAPI_ACCESS_AUTHORITY_PTR AccessAuthority;
} UCSAPI_USER_INFO, *UCSAPI_USER_INFO_PTR;

typedef struct ucsapi_user_data
{
	UCSAPI_USER_INFO			UserInfo;
	UCSAPI_AUTH_DATA_PTR		AuthData;
	UCSAPI_PICTURE_DATA_PTR		PictureData;
} UCSAPI_USER_DATA, *UCSAPI_USER_DATA_PTR;

typedef struct ucsapi_user_count
{
	UCSAPI_UINT32 AdminNumber;
	UCSAPI_UINT32 UserNumber;
} UCSAPI_USER_COUNT, *UCSAPI_USER_COUNT_PTR;

/* Log related type define */
typedef UCSAPI_UINT32 UCSAPI_AUTH_TYPE;
	#define UCSAPI_AUTH_TYPE_FINGER_1_TO_N				0
	#define UCSAPI_AUTH_TYPE_FINGER_1_TO_1				1
   	#define UCSAPI_AUTH_TYPE_FINGER_CARD				2
	#define UCSAPI_AUTH_TYPE_CARD						3
	#define UCSAPI_AUTH_TYPE_PASSWORD					4
	#define UCSAPI_AUTH_TYPE_FACE_1_TO_N				5
	#define UCSAPI_AUTH_TYPE_FACE_1_TO_1				6

typedef UCSAPI_UINT32 UCSAPI_AUTH_MODE;
	#define UCSAPI_AUTH_MODE_ATTENDANCE					1
	#define UCSAPI_AUTH_MODE_LEAVE						2
	#define UCSAPI_AUTH_MODE_NORMAL						3
	#define UCSAPI_AUTH_MODE_OUT						4
	#define UCSAPI_AUTH_MODE_RETURN						5

typedef UCSAPI_UINT32 UCSAPI_GET_LOG_TYPE;
	#define UCSAPI_GET_LOG_TYPE_NEW						0
	#define UCSAPI_GET_LOG_TYPE_OLD						1
	#define UCSAPI_GET_LOG_TYPE_ALL						2
	#define UCSAPI_GET_LOG_PERIOD						3

typedef UCSAPI_UINT32	UCSAPI_AUTH_ERROR;
	#define UCSAPI_AUTH_AUTHORIZED						0 // This value is success and other value is fail.
	#define UCSAPI_AUTH_INVALID_USER					1
	#define UCSAPI_AUTH_MATCHING						2
	#define UCSAPI_AUTH_PERMISSION						3
	#define UCSAPI_AUTH_CAPTURE							4
	#define UCSAPI_AUTH_DUPLICATED_AUTHENTICATION		5
	#define UCSAPI_AUTH_ANTIPASSBACK					6
	#define UCSAPI_AUTH_NETWORK							7
	#define UCSAPI_AUTH_SERVER_BUSY						8
	#define UCSAPI_AUTH_FACE_DETECTION					9
	#define UCSAPI_AUTH_BLACKLIST						10
	#define UCSAPI_AUTH_MEAL_PAY						11
	#define UCSAPI_AUTH_MEAL_TYPE						12
	#define UCSAPI_AUTH_MEAL_CODE						13
	#define UCSAPI_AUTH_PERIOD							14
	#define UCSAPI_AUTH_MEAL_LIMIT						15
	#define UCSAPI_AUTH_DAY_LIMIT						16
	#define UCSAPI_AUTH_MONTH_LIMIT						17
	#define UCSAPI_AUTH_SOFT_PASSBACK					32
	#define UCSAPI_AUTH_DURESS_FINGER					33

typedef struct ucsapi_access_log_data
{
	UCSAPI_UINT32			UserID;
	UCSAPI_DATE_TIME_INFO	DateTime;
	UCSAPI_UINT8			AuthMode;
	UCSAPI_UINT8			AuthType;
	UCSAPI_UINT8			DeviceID;			// Main = 0, Dummy = 1
	UCSAPI_UINT8			Reserved[1];
	UCSAPI_BOOL				IsAuthorized;
	UCSAPI_DATA_PTR			RFID;
	UCSAPI_AUTH_ERROR		AuthResult;
	UCSAPI_PICTURE_DATA_PTR PictureData;

#ifdef _CIPSYSTEM
	UCSAPI_UINT8			PayFlag;
	UCSAPI_UINT8			SafeFlag;

#endif

} UCSAPI_ACCESS_LOG_DATA, *UCSAPI_ACCESS_LOG_DATA_PTR;

// UCS API Return define
typedef UCSAPI_UINT32 UCSAPI_RETURN;
typedef UCSAPI_RETURN  (UCSAPI * UCSAPI_CALLBACK_EVENT_HANDLER) (UCSAPI_UINT32 TerminalID, UCSAPI_UINT32 EventType, UCSAPI_UINT32 wParam, UCSAPI_UINT32 lParam);

/* Callback related type define */
typedef UCSAPI_UINT32 UCSAPI_CALLBACK_EVENT_TYPE;
	#define UCSAPI_CALLBACK_EVENT								1600
	#define UCSAPI_CALLBACK_EVENT_CONNECTED						UCSAPI_CALLBACK_EVENT+1
	#define UCSAPI_CALLBACK_EVENT_DISCONNECTED					UCSAPI_CALLBACK_EVENT+2
	#define UCSAPI_CALLBACK_EVENT_REALTIME_ACCESS_LOG			UCSAPI_CALLBACK_EVENT+3
	#define UCSAPI_CALLBACK_EVENT_GET_ACCESS_LOG				UCSAPI_CALLBACK_EVENT+4
	#define UCSAPI_CALLBACK_EVENT_GET_ACCESS_LOG_COUNT			UCSAPI_CALLBACK_EVENT+5
	#define UCSAPI_CALLBACK_EVENT_GET_TERMINAL_TIME				UCSAPI_CALLBACK_EVENT+6

	#define UCSAPI_CALLBACK_EVENT_ADD_USER						UCSAPI_CALLBACK_EVENT+10
	#define UCSAPI_CALLBACK_EVENT_DELETE_USER					UCSAPI_CALLBACK_EVENT+11
	#define UCSAPI_CALLBACK_EVENT_DELETE_ALL_USER				UCSAPI_CALLBACK_EVENT+12
	#define UCSAPI_CALLBACK_EVENT_GET_USER_COUNT				UCSAPI_CALLBACK_EVENT+13
	#define UCSAPI_CALLBACK_EVENT_GET_USER_INFO_LIST			UCSAPI_CALLBACK_EVENT+14
	#define UCSAPI_CALLBACK_EVENT_GET_USER_DATA					UCSAPI_CALLBACK_EVENT+15

	#define UCSAPI_CALLBACK_EVENT_VERIFY_USER_AUTH_INFO			UCSAPI_CALLBACK_EVENT+20
	#define UCSAPI_CALLBACK_EVENT_VERIFY_FINGER_1_TO_N			UCSAPI_CALLBACK_EVENT+21
	#define UCSAPI_CALLBACK_EVENT_VERIFY_FINGER_1_TO_1			UCSAPI_CALLBACK_EVENT+22
	#define UCSAPI_CALLBACK_EVENT_VERIFY_CARD					UCSAPI_CALLBACK_EVENT+23
	#define UCSAPI_CALLBACK_EVENT_VERIFY_PASSWORD				UCSAPI_CALLBACK_EVENT+24

	#define UCSAPI_CALLBACK_EVENT_GET_TERMINAL_OPTION			UCSAPI_CALLBACK_EVENT+30
	#define UCSAPI_CALLBACK_EVENT_SET_TERMINAL_OPTION			UCSAPI_CALLBACK_EVENT+31
	#define UCSAPI_CALLBACK_EVENT_GET_ACU_OPTION				UCSAPI_CALLBACK_EVENT+32
	#define UCSAPI_CALLBACK_EVENT_SET_ACU_OPTION				UCSAPI_CALLBACK_EVENT+33
	#define UCSAPI_CALLBACK_EVENT_GET_ACU_LOCKSCHEDULE			UCSAPI_CALLBACK_EVENT+34
	#define UCSAPI_CALLBACK_EVENT_SET_ACU_LOCKSCHEDULE			UCSAPI_CALLBACK_EVENT+35
	#define UCSAPI_CALLBACK_EVENT_GET_SIREN						UCSAPI_CALLBACK_EVENT+36
	#define UCSAPI_CALLBACK_EVENT_SET_SIREN						UCSAPI_CALLBACK_EVENT+37

	#define UCSAPI_CALLBACK_EVENT_FW_UPGRADING					UCSAPI_CALLBACK_EVENT+80
	#define UCSAPI_CALLBACK_EVENT_FW_UPGRADED					UCSAPI_CALLBACK_EVENT+81
	#define UCSAPI_CALLBACK_EVENT_FW_VERSION					UCSAPI_CALLBACK_EVENT+82
	#define UCSAPI_CALLBACK_EVENT_USERFILE_UPGRADING			UCSAPI_CALLBACK_EVENT+85
	#define UCSAPI_CALLBACK_EVENT_USERFILE_UPGRADED				UCSAPI_CALLBACK_EVENT+86
	
	#define UCSAPI_CALLBACK_EVENT_OPEN_DOOR						UCSAPI_CALLBACK_EVENT+90
	#define UCSAPI_CALLBACK_EVENT_TERMINAL_STATUS				UCSAPI_CALLBACK_EVENT+91
	#define UCSAPI_CALLBACK_EVENT_TERMINAL_CONTROL				UCSAPI_CALLBACK_EVENT+92
	#define UCSAPI_CALLBACK_EVENT_ACU_STATUS					UCSAPI_CALLBACK_EVENT+93

	#define UCSAPI_CALLBACK_EVENT_PICTURE_LOG					UCSAPI_CALLBACK_EVENT+100
	#define UCSAPI_CALLBACK_EVENT_ANTIPASSBACK					UCSAPI_CALLBACK_EVENT+101
	#define UCSAPI_CALLBACK_EVENT_SET_ACCESS_CONTROL_DATA		UCSAPI_CALLBACK_EVENT+102

	#define UCSAPI_CALLBACK_EVENT_CONTROL_PERIPHERAL_DEVICE		UCSAPI_CALLBACK_EVENT+110
	#define UCSAPI_CALLBACK_EVENT_GET_TA_FUNCTION				UCSAPI_CALLBACK_EVENT+120
	#define UCSAPI_CALLBACK_EVENT_SET_TA_FUNCTION				UCSAPI_CALLBACK_EVENT+121
	#define UCSAPI_CALLBACK_EVENT_SET_TA_TIME					UCSAPI_CALLBACK_EVENT+122

	#define UCSAPI_CALLBACK_EVENT_GET_TERMINAL_MEAL_CONFIG		UCSAPI_CALLBACK_EVENT+130
	#define UCSAPI_CALLBACK_EVENT_SET_TERMINAL_MEAL_CONFIG		UCSAPI_CALLBACK_EVENT+131

	#define UCSAPI_CALLBACK_EVENT_FINGER_IMAGE					UCSAPI_CALLBACK_EVENT+140

	#define UCSAPI_CALLBACK_EVENT_PRIVATE_MESSAGE				UCSAPI_CALLBACK_EVENT+150
	#define UCSAPI_CALLBACK_EVENT_PUBLIC_MESSAGE				UCSAPI_CALLBACK_EVENT+151

	#define UCSAPI_CALLBACK_EVENT_SET_SMARTCARD_LAYOUT			UCSAPI_CALLBACK_EVENT+160
	#define UCSAPI_CALLBACK_EVENT_SET_WIEGAND_FORMAT			UCSAPI_CALLBACK_EVENT+165

	#define UCSAPI_CALLBACK_EVENT_EMERGENCY						UCSAPI_CALLBACK_EVENT+170
	#define UCSAPI_CALLBACK_EVENT_SET_EMERGENCY					UCSAPI_CALLBACK_EVENT+171
	#define UCSAPI_CALLBACK_EVENT_ACU_ALARM						UCSAPI_CALLBACK_EVENT+172

	#define UCSAPI_CALLBACK_EVENT_REGIST_FACE					UCSAPI_CALLBACK_EVENT+180
	#define UCSAPI_CALLBACK_EVENT_FP_MINUTIAE					UCSAPI_CALLBACK_EVENT+181


// Define UCSAPI_CALLBACK_RESULT ==> over 1000 is estimated for error (by kks)
typedef UCSAPI_UINT32 UCSAPI_CALLBACK_RESULT;
	#define UCSAPI_CALLBACK_RESULT_DEFAULT				0	// Default processing
	#define UCSAPI_CALLBACK_RESULT_PROCESS				1	// Follow application process
	#define UCSAPI_CALLBACK_RESULT_IGNORE				2	// Skip Callback process
	#define UCSAPI_CALLBACK_RESULT_ERROR				1000

typedef struct ucsapi_progress_info
{
	UCSAPI_UINT32		CurrentIndex;
	UCSAPI_UINT32		TotalNumber;
} UCSAPI_PROGRESS_INFO, *UCSAPI_PROGRESS_INFO_PTR;

typedef struct ucsapi_callback_param_0
{
	UCSAPI_UINT32				ClientID;
	UCSAPI_UINT32				ErrorCode;
	UCSAPI_PROGRESS_INFO		Progress;

} UCSAPI_CALLBACK_PARAM_0, *UCSAPI_CALLBACK_PARAM_0_PTR;

typedef UCSAPI_UINT32	UCSAPI_CALLBACK_DATA_TYPE;
	#define UCSAPI_CALLBACK_DATA_TYPE_USER_INFO				0
	#define UCSAPI_CALLBACK_DATA_TYPE_USER_DATA				1
	#define UCSAPI_CALLBACK_DATA_TYPE_ACCESS_LOG			2
	#define UCSAPI_CALLBACK_DATA_TYPE_FACE_INFO				3

typedef struct ucsapi_callback_param_1
{
	UCSAPI_CALLBACK_DATA_TYPE		DataType;
	union {
		UCSAPI_USER_INFO_PTR		UserInfo;
		UCSAPI_USER_DATA_PTR		UserData;
		UCSAPI_ACCESS_LOG_DATA_PTR	AccessLog;
		UCSAPI_FACE_INFO_PTR		FaceInfo;
	} Data;

} UCSAPI_CALLBACK_PARAM_1, *UCSAPI_CALLBACK_PARAM_1_PTR;

/* Access Control setting related type define */
typedef struct ucsapi_timezone
{
	UCSAPI_TIME_HH_MM			StartTime;
	UCSAPI_TIME_HH_MM			EndTime;
} UCSAPI_TIMEZONE, *UCSAPI_TIMEZONE_PTR;

typedef struct ucsapi_access_timezone
{
	UCSAPI_CHAR				Code[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_TIMEZONE			Zone[12];
	UCSAPI_UINT8			Reserved[4];
} UCSAPI_ACCESS_TIMEZONE;

typedef struct ucsapi_access_timezone_data
{
	UCSAPI_UINT32			TimezoneNum;
	UCSAPI_ACCESS_TIMEZONE	Timezone[UCSAPI_ACCESS_TIMEZONE_MAX];
} UCSAPI_ACCESS_TIMEZONE_DATA, *UCSAPI_ACCESS_TIMEZONE_DATA_PTR;

typedef struct ucsapi_access_holiday
{
	UCSAPI_CHAR				Code[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_DATE_MM_DD		Date[32];
} UCSAPI_ACCESS_HOLIDAY, *UCSAPI_ACCESS_HOLIDAY_PTR;

typedef struct ucsapi_access_holiday_data
{
	UCSAPI_UINT32			HolidayNum;
	UCSAPI_ACCESS_HOLIDAY	Holiday[UCSAPI_ACCESS_HOLIDAY_MAX];
} UCSAPI_ACCESS_HOLIDAY_DATA, *UCSAPI_ACCESS_HOLIDAY_DATA_PTR;

typedef struct ucsapi_access_timezone_code
{
	UCSAPI_CHAR			Sun[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			Mon[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			Tue[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			Wed[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			Thu[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			Fri[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			Sat[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			Hol[UCSAPI_DATA_SIZE_CODE4];
} UCSAPI_ACCESS_TIMEZONE_CODE;

typedef struct ucsapi_access_time
{
	UCSAPI_CHAR			Code[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_ACCESS_TIMEZONE_CODE Timezone;
	UCSAPI_CHAR			Holiday[UCSAPI_DATA_SIZE_CODE4];
} UCSAPI_ACCESS_TIME, *UCSAPI_ACCESS_TIME_PTR;

typedef struct ucsapi_access_time_data
{
	UCSAPI_UINT32		AccessTimeNum;
	UCSAPI_ACCESS_TIME	AccessTime[UCSAPI_ACCESS_TIME_MAX];
} UCSAPI_ACCESS_TIME_DATA, *UCSAPI_ACCESS_TIME_DATA_PTR;


typedef struct ucsapi_access_group
{
	UCSAPI_CHAR			Code[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			AccssTime1[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			AccssTime2[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			AccssTime3[UCSAPI_DATA_SIZE_CODE4];
	UCSAPI_CHAR			AccssTime4[UCSAPI_DATA_SIZE_CODE4];
} UCSAPI_ACCESS_GROUP, *UCSAPI_ACCESS_GROUP_PTR;

typedef struct ucsapi_access_group_data
{
	UCSAPI_UINT32		AccessGroupNum;
	UCSAPI_ACCESS_GROUP	AccessGroup[UCSAPI_ACCESS_GROUP_MAX];
} UCSAPI_ACCESS_GROUP_DATA, *UCSAPI_ACCESS_GROUP_DATA_PTR;


typedef UCSAPI_UINT32	UCSAPI_ACCESS_CONTROL_DATA_TYPE;
	#define UCSAPI_ACCESS_CONTROL_DATA_TYPE_TIMEZONE	0
	#define UCSAPI_ACCESS_CONTROL_DATA_TYPE_HOLIDAY		1
	#define UCSAPI_ACCESS_CONTROL_DATA_TYPE_TIME		2
	#define UCSAPI_ACCESS_CONTROL_DATA_TYPE_GROUP		3

typedef struct ucsapi_access_control_data 
{
	UCSAPI_ACCESS_CONTROL_DATA_TYPE DataType;
	union {
		UCSAPI_ACCESS_TIMEZONE_DATA_PTR Timezone;
		UCSAPI_ACCESS_HOLIDAY_DATA_PTR	Holiday;
		UCSAPI_ACCESS_TIME_DATA_PTR		AccessTime;
		UCSAPI_ACCESS_GROUP_DATA_PTR	AccessGroup;
	} Data;
} UCSAPI_ACCESS_CONTROL_DATA, *UCSAPI_ACCESS_CONTROL_DATA_PTR;

/* Authentication related type define */
typedef struct ucsapi_input_data_card 
{
	UCSAPI_UINT32		AuthMode;
	UCSAPI_DATA			RFID;
} UCSAPI_INPUT_DATA_CARD, *UCSAPI_INPUT_DATA_CARD_PTR;

typedef struct ucsapi_input_data_password 
{
	UCSAPI_UINT32		UserID;
	UCSAPI_UINT32		AuthMode;
	UCSAPI_DATA			Password;
} UCSAPI_INPUT_DATA_PASSWORD, *UCSAPI_INPUT_DATA_PASSWORD_PTR;

typedef struct ucsapi_input_data_finger_1_to_n
{
	UCSAPI_UINT32		AuthMode;
	UCSAPI_UINT32		SecurityLevel; 
	UCSAPI_UINT32		InputIDLength;
	UCSAPI_DATA			Finger;
} UCSAPI_INPUT_DATA_FINGER_1_TO_N, *UCSAPI_INPUT_DATA_FINGER_1_TO_N_PTR;

typedef struct ucsapi_input_data_finger_1_to_1
{
	UCSAPI_UINT32		UserID;
	UCSAPI_UINT32		AuthMode;
	UCSAPI_UINT32		SecurityLevel; 
	UCSAPI_DATA			Finger;
} UCSAPI_INPUT_DATA_FINGER_1_TO_1, *UCSAPI_INPUT_DATA_FINGER_1_TO_1_PTR;

typedef UCSAPI_UINT32	UCSAPI_INPUT_DATA_TYPE;
	#define UCSAPI_INPUT_DATA_TYPE_FINGER_1_TO_N		0
	#define UCSAPI_INPUT_DATA_TYPE_FINGER_1_TO_1		1
	#define UCSAPI_INPUT_DATA_TYPE_PASSWORD				2
	#define UCSAPI_INPUT_DATA_TYPE_CARD					3
	#define UCSAPI_INPUT_DATA_TYPE_FINGER_CARD			4

typedef UCSAPI_UINT32	UCSAPI_ANTIPASSBACK_LEVEL;
	#define UCSAPI_ANTIPASSBACK_LEVEL_NOT_USE						0
	#define UCSAPI_ANTIPASSBACK_LEVEL_WHEN_DISCONNECTION_ALLOW		1
	#define UCSAPI_ANTIPASSBACK_LEVEL_WHEN_DISCONNECTION_PROHIBIT	2

typedef struct ucsapi_input_data
{
	UCSAPI_ANTIPASSBACK_LEVEL	AntipassbackLevel;
	UCSAPI_UINT8				DeviceID;
	UCSAPI_INPUT_DATA_TYPE		DataType;
	union {
		UCSAPI_INPUT_DATA_FINGER_1_TO_1_PTR Finger1To1;
		UCSAPI_INPUT_DATA_FINGER_1_TO_N_PTR Finger1ToN;
		UCSAPI_INPUT_DATA_CARD_PTR Card;
		UCSAPI_INPUT_DATA_PASSWORD_PTR Password;
	} Data;

} UCSAPI_INPUT_DATA, *UCSAPI_INPUT_DATA_PTR;

typedef UCSAPI_UINT32	UCSAPI_INPUT_ID_TYPE;
	#define UCSAPI_INPUT_ID_TYPE_USER_ID			0
	#define UCSAPI_INPUT_ID_TYPE_UNIQUE_ID			1	
	#define UCSAPI_INPUT_ID_TYPE_RFID				2
	

typedef struct ucsapi_input_id_data
{
	UCSAPI_UINT8			DeviceID;
	UCSAPI_INPUT_ID_TYPE	DataType;
	union {
		UCSAPI_UINT32*		UserID;
		UCSAPI_DATA_PTR		UniqueID;
		UCSAPI_DATA_PTR		RFID;
	} Data;
} UCSAPI_INPUT_ID_DATA, *UCSAPI_INPUT_ID_DATA_PTR;

typedef struct ucsapi_auth_info
{
	UCSAPI_UINT32			UserID;
	UCSAPI_BOOL				IsAccessibility;
	UCSAPI_USER_PROPERTY	Property;
	UCSAPI_UINT32			ErrorCode;
} UCSAPI_AUTH_INFO, *UCSAPI_AUTH_INFO_PTR;

typedef struct ucsapi_auth_notify
{
	UCSAPI_UINT32			UserID;
	UCSAPI_USER_PROPERTY	Property;			// Inserted after v4.0.1.0
	UCSAPI_BOOL				IsAuthorized;
	UCSAPI_BOOL				IsVisitor;
	UCSAPI_DATE_TIME_INFO	AuthorizedTime;
	UCSAPI_UINT32			ErrorCode;
} UCSAPI_AUTH_NOTIFY, *UCSAPI_AUTH_NOTIFY_PTR;

/* Terminal option settings related type define */
#define UCSAPI_SOUND_VOLUME_MAX				20 

typedef struct ucsapi_terminal_timezone
{
	UCSAPI_UINT8 IsUsed;
	UCSAPI_UINT8 StartHour;
	UCSAPI_UINT8 StartMin;
	UCSAPI_UINT8 EndHour;
	UCSAPI_UINT8 EndMin;
} UCSAPI_TERMINAL_TIMEZONE, *UCSAPI_TERMINAL_TIMEZONE_PTR;

typedef struct ucsapi_terminal_day_schedule
{
	UCSAPI_TERMINAL_TIMEZONE Lock1;
	UCSAPI_TERMINAL_TIMEZONE Lock2;
	UCSAPI_TERMINAL_TIMEZONE Lock3;
	UCSAPI_TERMINAL_TIMEZONE Open1;
	UCSAPI_TERMINAL_TIMEZONE Open2;
	UCSAPI_TERMINAL_TIMEZONE Open3;

} UCSAPI_TERMINAL_DAY_SCHEDULE, *UCSAPI_TERMINAL_DAY_SCHEDULE_PTR;


typedef UCSAPI_UINT8	UCSAPI_HOLIDAY_TYPE;
	#define UCSAPI_HOLIDAY_TYPE_1			1
	#define UCSAPI_HOLIDAY_TYPE_2			2
	#define UCSAPI_HOLIDAY_TYPE_3			3

typedef struct ucsapi_terminal_holiday_info
{
	UCSAPI_UINT8			Month;
	UCSAPI_UINT8			Day;
	UCSAPI_HOLIDAY_TYPE		HolidayType; // 1 ~ 3 digit
} UCSAPI_TERMINAL_HOLIDAY_INFO, *UCSAPI_TERMINAL_HOLIDAY_INFO_PTR;

typedef struct ucsapi_terminal_schedule
{
	UCSAPI_TERMINAL_DAY_SCHEDULE Sun;
	UCSAPI_TERMINAL_DAY_SCHEDULE Mon;
	UCSAPI_TERMINAL_DAY_SCHEDULE Tue;
	UCSAPI_TERMINAL_DAY_SCHEDULE Wed;
	UCSAPI_TERMINAL_DAY_SCHEDULE Thu;
	UCSAPI_TERMINAL_DAY_SCHEDULE Fri;
	UCSAPI_TERMINAL_DAY_SCHEDULE Sat;
	UCSAPI_TERMINAL_DAY_SCHEDULE Holiday1;
	UCSAPI_TERMINAL_DAY_SCHEDULE Holiday2;
	UCSAPI_TERMINAL_DAY_SCHEDULE Holiday3;
	UCSAPI_TERMINAL_HOLIDAY_INFO Holidays[100];
} UCSAPI_TERMINAL_SCHEDULE, *UCSAPI_TERMINAL_SCHEDULE_PTR;

typedef struct ucsapi_security_level
{
	UCSAPI_UINT8	Verify		:4;
	UCSAPI_UINT8	Identify	:4;
} UCSAPI_SECURITY_LEVEL, *UCSAPI_SECURITY_LEVEL_PTR;

typedef struct ucsapi_network_info
{
	UCSAPI_UINT8	NetworkType;
	UCSAPI_UINT8	IP[4];
	UCSAPI_UINT8	Subnet[4];
	UCSAPI_UINT8	Gateway[4];
} UCSAPI_NETWORK_INFO, *UCSAPI_NETWORK_INFO_PTR;

typedef struct ucsapi_server_info
{
	UCSAPI_UINT8	IP[4];
	UCSAPI_UINT16	Port;
	UCSAPI_UINT8	Reserved[2];
} UCSAPI_SERVER_INFO, *UCSAPI_SERVER_INFO_PTR;

typedef struct ucsapi_terminal_option_flag
{
	UCSAPI_UINT32	SecurityLevel	:1;
	UCSAPI_UINT32	InputIDLength	:1;
	UCSAPI_UINT32	AutoEnterKey	:1;
	UCSAPI_UINT32	Sound			:1;
	UCSAPI_UINT32	Authentication	:1;
	UCSAPI_UINT32	Applicaction	:1;
	UCSAPI_UINT32	Antipassback	:1;
	UCSAPI_UINT32	Network			:1;
	UCSAPI_UINT32	Server			:1;
	UCSAPI_UINT32	InputIDType		:1;
	UCSAPI_UINT32	AccessLevel		:1;
	UCSAPI_UINT32	PrintText		:1;
	UCSAPI_UINT32	Schedule		:1;
} UCSAPI_TERMINAL_OPTION_FLAG, *UCSAPI_TERMINAL_OPTION_FLAG_PTR;

typedef struct ucsapi_terminal_option
{
	UCSAPI_TERMINAL_OPTION_FLAG Flsgs;

	UCSAPI_SECURITY_LEVEL		SecurityLevel;  
	UCSAPI_UINT8				InputIDLength;	// 4 - 8
	UCSAPI_UINT8				AutoEnterKey;	// 0/1
	UCSAPI_UINT8				Sound;			// 0/1
	UCSAPI_UINT8				Authentication;	// N/S, S/N, NO, SO
	UCSAPI_UINT8				Applicaction;	// Access Control, Time Attendance, Meal Management
	UCSAPI_UINT8				Antipassback;	
	UCSAPI_NETWORK_INFO			Network;  
	UCSAPI_SERVER_INFO			Server;	
	UCSAPI_UINT8				InputIDType;
	UCSAPI_UINT8				AccessLevel;
	UCSAPI_UINT8				PrintName[32];
	UCSAPI_TERMINAL_SCHEDULE	Schedule;
} UCSAPI_TERMINAL_OPTION, *UCSAPI_TERMINAL_OPTION_PTR;

// Define for ACU
typedef struct ucsapi_acu_lockschedule
{
	UCSAPI_UINT8				LockIndex; // 0 - 3
	UCSAPI_TERMINAL_SCHEDULE	Schedule;
} UCSAPI_ACU_LOCKSCHEDULE, *UCSAPI_ACU_LOCKSCHEDULE_PTR;

typedef UCSAPI_UINT32	UCSAPI_ACU_OPTION_FLAG_INDEX;
	#define UCSAPI_ACU_OPTION_FLAG_NETWORK		0
	#define UCSAPI_ACU_OPTION_FLAG_SYSTEM		1
	#define UCSAPI_ACU_OPTION_FLAG_DOOR			2
	#define UCSAPI_ACU_OPTION_FLAG_PGMIN		3
	#define UCSAPI_ACU_OPTION_FLAG_PGMOUT		4
	#define UCSAPI_ACU_OPTION_FLAG_ZONE			5
	#define UCSAPI_ACU_OPTION_FLAG_PARTITION	6
	#define UCSAPI_ACU_OPTION_FLAG_CONSOLE		7

typedef struct ucsapi_acu_option_flag
{
	UCSAPI_UINT32	Console		:1; 
	UCSAPI_UINT32	Partition	:1;
	UCSAPI_UINT32	Zone		:1;
	UCSAPI_UINT32	PgmOutput	:1;
	UCSAPI_UINT32	PgmInput	:1;
	UCSAPI_UINT32	Door		:1;
	UCSAPI_UINT32	System		:1;	
	UCSAPI_UINT32	Network		:1;
} UCSAPI_ACU_OPTION_FLAG, *UCSAPI_ACU_OPTION_FLAG_PTR;

typedef union tag_ip_address
{
	int			ul;
	BYTE		uc[4];
} IP_ADDRESS;

typedef struct
{
	BYTE  lock_flag;	// 0=UDP¸1=UDP
	BYTE  reserved[3];
	BYTE  sitekey[24];
	BYTE  password[16];
} ACU_UDP_SETTING; 

typedef UCSAPI_UINT32	UCSAPI_ACU_NETIP_ADDR_INDEX;
	#define UCSAPI_ACU_NETIP_ADDR_CIP		0
	#define UCSAPI_ACU_NETIP_ADDR_GATEWAY	1
	#define UCSAPI_ACU_NETIP_ADDR_SUBNET	2
	#define UCSAPI_ACU_NETIP_ADDR_SIP		3
	#define UCSAPI_ACU_NETIP_DHCP_CIP		4
	#define UCSAPI_ACU_NETIP_DHCP_GATEWAY	5
	#define UCSAPI_ACU_NETIP_DHCP_SUBNET	6

typedef struct
{
	int nettype;
	IP_ADDRESS addr_cip;
	IP_ADDRESS addr_gw;
	IP_ADDRESS addr_subnet;
	IP_ADDRESS addr_sip;
	IP_ADDRESS dhcp_addr_cip;
	IP_ADDRESS dhcp_addr_gw;
	IP_ADDRESS dhcp_addr_subnet;
	int sport;
} ACU_NET_SETTING;

typedef enum 
{
    cpmaster,
	vsr20DSC,
	vsr20DRF,
	acf100,
	ac1000,
	ac2100,
	ac4000,
	ac5000,
	ac6000,
	sr100,
	wiegand,
	unknown,	
	ENDTYPE  		
} ACU_READER_TYPE;

typedef struct mcp040_partlock
{
	BYTE	lock1		:1;
	BYTE	lock2		:1;
	BYTE	lock3		:1;	
	BYTE	lock4		:1;

	BYTE	part1		:1; 
	BYTE	part2		:1;
	BYTE	part3		:1;
	BYTE	part4		:1;
} MCP040_PARTLOCK;

typedef struct 
{
	BYTE  type;				// Smart-RD, ACF100, other..(ACU_READER_TYPE)
	BYTE  partlock[1];	    // partition bits upper/lock bits lower(MCP040_PARTLOCK)
	BYTE  openTime;         // door open period 0 = always locked, FF=always open ( 1~254 seconds)
	BYTE  mode;             // 0=access, 1=arm/disarm, 2=all
	struct 
	{
		char entry[4];		// antipass-back entry code ascii
		char exit[4];		// antipass-back exit code ascii
		BYTE  type;         // antipass-back type = 0 disabled, 1 hard, 2 soft, 3 timed
		struct 
		{
			BYTE hour;		// 0-23
			BYTE min;		// 0-59
			BYTE sec;		// 0-59
		} t;
	} pb;
	BYTE resv[16];          // reserved
} ACU_READER_OPTION;		// 32 bytes

typedef enum 
{
	chime = 0x01,
	unlockondisarm = 0x02
} partOptions; 

typedef struct 
{
	BYTE  	Enable;				//0 : Disable, 1 : Enable
	BYTE	resv[3];
	BYTE    name[16];			// partition name
	BYTE  	Account[4];			// not used
	BYTE    Part_EntryDelay1;	//0 ~ 255 Sec		
	BYTE 	Part_EntryDelay2;	//0 ~ 255 Sec		
	BYTE 	Part_ExitDelay1;	//0 ~ 255 Sec		
	BYTE 	Part_ExitDelay2;	//0 ~ 255 Sec		
	short 	sirenTime;          // 0-no action, 1~65535 seconds
	BYTE 	alarmCount;			// 0 ~ 255     
	BYTE    options;			// see 'partOptions' bit define
} ACU_PARTITION_INFO;

typedef enum 
{
  pgm_unused,
  pgm_auth,           // matching success
  pgm_noauth,         // matching failed
  pgm_sched,          // scheduled output
  pgm_alarm,          // alarm output  
  pgm_tbl,            // tbl (ac loss, battery, bell, comm)
  pgm_armStat,        // arm/disarm status
  pgm_fire,           // fire alarm
  pgm_silent,         // silent alarm
} PGM_TypeDef; 

typedef enum 
{
	pgmin_unused,
	pgmin_egressNC, 
	pgmin_egressNO,   
	pgmin_fireNC, 
	pgmin_fireNO,   
	pgmin_securityNC, 
	pgmin_securityNO, 
	pgmin_end,   
} PGM_TypeInDef;


typedef struct 
{
	BYTE		time;                  	// activation time - 255 = toggle, 0-254 seconds
	BYTE		param1;                 // door#, partition#, schedule# 0-255
	BYTE		param2; 
	BYTE        type;					// PGM_TypeDef
	BYTE		resv[4];
} ACU_PROGRAM_OPTION;						// 8 bytes

typedef struct 
{
	BYTE       zone;					// assign zone number 0-7, 0xff = N/A
	BYTE       option;					// 0x01 - door forced enabled/disabled
	BYTE	   otlwarn;					// delay before open too long warning 0-255
	BYTE       resv[5];
} ACU_DOOR_OPTION;						// 8 bytes

typedef struct 
{
	BYTE       type;					// see PGM_TypeInDef
	BYTE       time;
	BYTE       option;
	BYTE       resv[5];      
} ACU_INPUT_OPTION;						// 8 bytes

typedef struct 
{
    BYTE ForceArm;
	BYTE card_format[2];		// (0=Default, 1=Hexa, 2=Decimal, 3=3:5Decimal
    BYTE LineTestTime;
    int term_id;
    BYTE time_sync; 
	BYTE zoneEOL;				// 1 = zone require resistors, 0= no resistors
	BYTE insoplog;
	BYTE connectmode;			//new v2.0 firmware
	BYTE passbackmode;			//new v2.0 firmware
	BYTE resv[19];
} ACU_SYSTEM_OPTION;

typedef struct 
{
	BYTE num;
    BYTE name[10];    
	BYTE resp;         	// fast = 1, 0 = slow
    BYTE dble;			// 1= enable 0=disable (zone double)
    BYTE partition;		// 0-3
	BYTE type;
	BYTE resv[17];
} ACU_ZONE_CONFIG;

#define MAX_CP040_READER		12
#define MAX_CP040_PARTITION		4
#define MAX_CP040_ZONE			8
#define MAX_CP040_PGM			8
#define MAX_CP040_DOOR			4
#define MAX_CP040_INPUT			4

typedef struct ucsapi_acu_option
{
	ACU_NET_SETTING			netSettings;
    ACU_READER_OPTION		reader[MAX_CP040_READER];
    ACU_PARTITION_INFO		part[MAX_CP040_PARTITION];
    ACU_ZONE_CONFIG			zone[MAX_CP040_ZONE];
    ACU_PROGRAM_OPTION		pgm[MAX_CP040_PGM];
    ACU_DOOR_OPTION			door[MAX_CP040_DOOR];
    ACU_INPUT_OPTION		inputs[MAX_CP040_INPUT];
    ACU_SYSTEM_OPTION		sysOpt;
	ACU_UDP_SETTING			udpset;
	BYTE					resv[11];
} UCSAPI_ACU_OPTION, *UCSAPI_ACU_OPTION_PTR;

typedef UCSAPI_UINT32	UCSAPI_ACU_STATUS_INDEX;
	#define UCSAPI_ACU_STATUS_PARTITION	0
	#define UCSAPI_ACU_STATUS_ZONE		1
	#define UCSAPI_ACU_STATUS_LOCK		2
	#define UCSAPI_ACU_STATUS_READER	3

#define MAX_ACU_PARTITION   4
#define MAX_ACU_ZONE		8
#define MAX_ACU_LOCK	    4
#define MAX_ACU_READER		8

typedef struct acu_reader_ver
{
	BYTE hw;
	BYTE major;
	BYTE minor;
	BYTE custom1;
	BYTE custom2;
	BYTE order;
	BYTE reserved[2];
} ACU_READER_VER;

typedef struct acu_reader
{
	BYTE id;
	BYTE reader_type;
	ACU_READER_VER ver; // 8
} ACU_READER;

typedef struct acu_status
{
    BYTE   partition[MAX_ACU_PARTITION];		//4 : 00 = disarm, 01 = armed, 02 = alarm
    BYTE   zone[MAX_ACU_ZONE];			//8 : 00 = normal, 01=Opened, 02=Trouble    
    BYTE   lock[MAX_ACU_LOCK];			//4 : 00 = closed 01 = opened  
	BYTE   reader[MAX_ACU_READER];		//8 :
	ACU_READER reader_ver[MAX_ACU_READER]; //8: ACU_READER(10)
    BYTE   Reserved[8];	//8
} ACU_STATUS; // MCP-040 상태

typedef struct ucsapi_acu_status_info
{
	UCSAPI_UINT8	Notice;
	ACU_STATUS		Status;
} UCSAPI_ACU_STATUS_INFO, *UCSAPI_ACU_STATUS_INFO_PTR;

/* Monitoring related type define */
typedef struct ucsapi_terminal_status
{
	UCSAPI_UINT32	Terminal;	// 0 = Unlock, 1 = Lock, 2 = Global Lock
	UCSAPI_UINT32	Door;		// 0 = Close, 1 = Open, 2 = Not support monitoring pin, 4 = Bad Open, 5 = no open after authorized
	UCSAPI_UINT32	Cover;		// 0 = Close, 1 = Open
	UCSAPI_UINT32	Lock;		// 0 = Normal, 1 = Error
	UCSAPI_UINT32	Open; // 0 = Normal, 1 = Continuous Open
	UCSAPI_UINT32	Reserved1; 
	UCSAPI_UINT32	Reserved2; 
	UCSAPI_UINT32	Reserved3;
} UCSAPI_TERMINAL_STATUS, *UCSAPI_TERMINAL_STATUS_PTR;

typedef struct ucsapi_terminal_control
{
	UCSAPI_UINT8	lockStatus;	// 0 = Unlock, 1 = Lock
	UCSAPI_UINT8	lockType;	// 0 = Normal, 1:Global
} UCSAPI_TERMINAL_CONTROL, *UCSAPI_TERMINAL_CONTROL_PTR;

/* Time/attendance, meal related type define */
typedef struct ucsapi_meal_time
{
	UCSAPI_UINT8 StartHour;
	UCSAPI_UINT8 StartMin;
	UCSAPI_UINT8 EndHour;
	UCSAPI_UINT8 EndMin;
} UCSAPI_MEAL_TIME, *UCSAPI_MEAL_TIME_PTR;

typedef struct ucsapi_terminal_meal_config
{
	UCSAPI_MEAL_TIME	Breakfast;
	UCSAPI_MEAL_TIME	Lunch;
	UCSAPI_MEAL_TIME	Dinner;	
	UCSAPI_MEAL_TIME	Snack;
	UCSAPI_MEAL_TIME	Latesnack;
	UCSAPI_UINT16		LimitOfMonth;
	UCSAPI_UINT8		LimitOfDay;
	UCSAPI_UINT8		Reserved;
	UCSAPI_UINT8		MealName[32];
} UCSAPI_TERMINAL_MEAL_CONFIG, *UCSAPI_TERMINAL_MEAL_CONFIG_PTR;

typedef struct ucsapi_ta_time
{
	UCSAPI_UINT8		Start1[4];
	UCSAPI_UINT8		Start2[4];
	UCSAPI_UINT8		Start3[4];
	UCSAPI_UINT8		Start4[4];
	UCSAPI_UINT8		End1[4];
	UCSAPI_UINT8		End2[4];
	UCSAPI_UINT8		End3[4];
	UCSAPI_UINT8		End4[4];
} UCSAPI_TA_TIME, *UCSAPI_TA_TIME_PTR;


typedef struct ucsapi_finger_image
{
	UCSAPI_UINT8				Format[4];		/* must be "JPG" */
	UCSAPI_UINT32				Length;			/* just length of Data (not sizeof structure) */
	UCSAPI_UINT8*				Data;
} UCSAPI_FINGER_IMAGE, *UCSAPI_FINGER_IMAGE_PTR; 


typedef struct ucsapi_public_message
{
	UCSAPI_UINT16			Length;
	UCSAPI_UINT8			Reserved1[2];
	UCSAPI_DATE_YYYY_MM_DD  StartDate;
	UCSAPI_DATE_YYYY_MM_DD  EndDate;
	UCSAPI_TIME_HH_MM		StartTime;
	UCSAPI_TIME_HH_MM		EndTime;
	UCSAPI_CHAR				Message[UCSAPI_MESSAGE];
} UCSAPI_PUBLIC_MESSAGE, *UCSAPI_PUBLIC_MESSAGE_PTR;

typedef struct ucsapi_private_message
{
	UCSAPI_UINT16			messageSize;
	UCSAPI_UINT16			displayTime;
	UCSAPI_CHAR				messageData[UCSAPI_MESSAGE];
} UCSAPI_PRIVATE_MESSAGE, *UCSAPI_PRIVATE_MESSAGE_PTR;

typedef UCSAPI_UINT32	UCSAPI_USER_FILE_TYPE;
	#define UCSAPI_USER_FILE_TYPE_TEXT_CSV					1
	#define UCSAPI_USER_FILE_TYPE_BACKGROUND_JPG			2
	#define UCSAPI_USER_FILE_TYPE_SUCCESS_VOICE_WAV			3
	#define UCSAPI_USER_FILE_TYPE_FAIL_VOICE_WAV			4
    #define UCSAPI_USER_FILE_TYPE_MOVIE_MP4					5


typedef UCSAPI_UINT8 UCSAPI_SMARTCARD_KEYTYPE;
	#define UCSAPI_SMARTCARD_KEYTYPE_A				0x60
	#define UCSAPI_SMARTCARD_KEYTYPE_B				0x61

typedef struct ucsapi_smartcard_sector_layout
{
	UCSAPI_UINT8	SectorNumber;		// Sector Number(0..127)
	UCSAPI_UINT8	KeyType;			// Key A = 0x60, Key B = 0x61)        
	UCSAPI_UINT8	KeyData[6];			// Key Value
	UCSAPI_UINT8	BlockNumber;		// Block Number(0..3)        
	UCSAPI_UINT8	Start;              // Start Location in Block
	UCSAPI_UINT8	Length;				// Data Length
	UCSAPI_UINT8	AID[2];             // AID of MAD Card. If AID not use then set 0xff
	UCSAPI_UINT8	Reserved[3]; 
} UCSAPI_SMARTCARD_SECTOR_LAYOUT, *UCSAPI_SMARTCARD_SECTOR_LAYOUT_PTR;

typedef UCSAPI_UINT32 UCSAPI_SMARTCARD_TYPE;
	#define UCSAPI_SMARTCARD_TYPE_DATA				0
	#define UCSAPI_SMARTCARD_TYPE_FINGER			1

typedef UCSAPI_UINT32 UCSAPI_SMARTCARD_READTYPE;
	#define UCSAPI_SMARTCARD_READTYPE_SERIAL		0
	#define UCSAPI_SMARTCARD_READTYPE_DATA			1
	#define UCSAPI_SMARTCARD_READTYPE_MAD			2

typedef UCSAPI_UINT8 UCSAPI_SMARTCARD_SERIALFORMAT;
	#define UCSAPI_SMARTCARD_SERIALFORMAT_DEFAULT			0
	#define UCSAPI_SMARTCARD_SERIALFORMAT_HEXA				1
	#define UCSAPI_SMARTCARD_SERIALFORMAT_DECIMAL			2
	#define UCSAPI_SMARTCARD_SERIALFORMAT_35DECIMAL			3

typedef struct ucsapi_smartcard_layout
{
	UCSAPI_SMARTCARD_TYPE			CardType;
	UCSAPI_SMARTCARD_READTYPE		ReadType;
	UCSAPI_SMARTCARD_SERIALFORMAT	SerialFormat; // if ReadType is UCSAPI_SMARTCARD_READTYPE_SERIAL then this value is valid data.
	UCSAPI_UINT8					SectorNumber; // 0..127
	UCSAPI_UINT8					Reserved[6];
	UCSAPI_SMARTCARD_SECTOR_LAYOUT Layouts[UCSAPI_SMARTCARD_SECTOR_MAX]; // max card size is 8k

} UCSAPI_SMARTCARD_LAYOUT, *UCSAPI_SMARTCARD_LAYOUT_PTR;

typedef struct ucsapi_version
{
	UCSAPI_UINT8 Major;
	UCSAPI_UINT8 Minor;
} UCSAPI_VERSION, *UCSAPI_VERSION_PTR;

typedef struct ucsapi_terminal_info
{
	UCSAPI_UINT32	TerminalID;
	UCSAPI_UINT8	TerminalIP[4];
	UCSAPI_UINT8	TerminalStatus;
	UCSAPI_UINT8	DoorStatus;
	UCSAPI_UINT8	CoverStatus;
	UCSAPI_UINT8	LockStatus;
	UCSAPI_UINT8	ExtSignal[4]; // 접점신호 1, 2, 3, 4(Reserved)
	UCSAPI_VERSION	Firmware;
	UCSAPI_VERSION	Protocol;
	UCSAPI_VERSION	CardReader;
	UCSAPI_UINT16	ModelNo;
	UCSAPI_UINT8	TerminalType;
	UCSAPI_UINT8	MacAddr[6];
} UCSAPI_TERMINAL_INFO, *UCSAPI_TERMINAL_INFO_PTR;

typedef UCSAPI_UINT32 UCSAPI_ERROR_TYPE;
	#define UCSAPI_ERROR_TYPE_NONE							0
	#define UCSAPI_ERROR_TYPE_ACCESS_LOG					1


typedef UCSAPI_UINT32 UCSAPI_TERMINAL_TYPE;
	#define UCSAPI_TERMINAL_TYPE_NORMAL		0
	#define UCSAPI_TERMINAL_TYPE_CARD		1
	#define UCSAPI_TERMINAL_TYPE_ACU		2
	#define UCSAPI_TERMINAL_TYPE_DUMMY		3

// Wiegand IN / OUT


typedef struct ucsapi_bit_mask
{
	UCSAPI_UINT8	bit7		:1;
	UCSAPI_UINT8	bit6		:1;
	UCSAPI_UINT8	bit5		:1;
	UCSAPI_UINT8	bit4		:1;
	UCSAPI_UINT8	bit3		:1;
	UCSAPI_UINT8	bit2		:1;
	UCSAPI_UINT8	bit1		:1;
	UCSAPI_UINT8	bit0		:1;
} UCSAPI_BIT_MASK, *UCSAPI_BIT_MASK_PTR;

typedef UCSAPI_UINT8 UCSAPI_PARITY_TYPE;
	#define UCSAPI_PARITY_TYPE_NONE
	#define UCSAPI_PARITY_TYPE_ODD
	#define UCSAPI_PARITY_TYPE_EVEN

typedef struct	ucsapi_wiegand_parity
{
	UCSAPI_PARITY_TYPE	Type;		// 0:Unused, 1:Odd Parity, 2:Even Parity
	UCSAPI_UINT8	Position;		// Parity bit location (0 ~ 127)
	UCSAPI_UINT8	Reserved[2];
	UCSAPI_BIT_MASK	BitMask1[16];	// masked Data bit

} UCSAPI_WIEGAND_PARITY, *UCSAPI_WIEGAND_PARITY_PTR;

typedef UCSAPI_UINT8 UCSAPI_CARD_TYPE;
	#define UCSAPI_CARD_TYPE_NONE
	#define UCSAPI_CARD_TYPE_BINARY
	#define UCSAPI_CARD_TYPE_DECIMAL
	#define UCSAPI_CARD_TYPE_HEXA

typedef struct	ucsapi_wiegand_cardinfo
{
	UCSAPI_CARD_TYPE	Type;		// 0:Unused, 1:Binary, 2:Decimal String, 3:Hexa String
	UCSAPI_UINT8	Digit;
	UCSAPI_UINT8	Endian;			// 0:MSB, 1:LSB
	UCSAPI_UINT8	Reserved0;
	UCSAPI_UINT8	BitMask[16];
} UCSAPI_WIEGAND_CARDINFO, *UCSAPI_WIEGAND_CARDINFO_PTR;

typedef UCSAPI_UINT8 UCSAPI_PORT_STATE;
	#define UCSAPI_PORT_STATE_ACTIVE_LOW	0
	#define UCSAPI_PORT_STATE_ACTIVE_HIGH	1


typedef UCSAPI_UINT32 UCSAPI_WIEGAND_DATA_TYPE;
	#define UCSAPI_WIEGAND_DATA_TYPE_OUT	1
	#define UCSAPI_WIEGAND_DATA_TYPE_IN		2

typedef struct	ucsapi_wiegand_in
{
	UCSAPI_UINT8	BitLen;
	UCSAPI_PORT_STATE	PortState;
	UCSAPI_UINT8	ParityBitCnt;
	UCSAPI_UINT8	Reserved0;
	UCSAPI_UINT32	IntervalTime;	// micro sec
	UCSAPI_UINT32	PulseTime;		// micro sec
	UCSAPI_WIEGAND_CARDINFO		Card[5];
	UCSAPI_WIEGAND_PARITY		Parity[10];
} UCSAPI_WIEGAND_IN, *UCSAPI_WIEGAND_IN_PTR;

typedef struct	ucsapi_wiegand_out
{
	UCSAPI_UINT8	BitLen;
	UCSAPI_UINT8	PortState;
	UCSAPI_UINT8	ParityBitCnt;
	UCSAPI_UINT8	SendFail;
	UCSAPI_UINT8	Bypass; // 0 : No (UserID), 1: Yes (Card data)
	UCSAPI_UINT8	Reserved0;
	UCSAPI_UINT8	Reserved1;
	UCSAPI_UINT8	Reserved2;
	UCSAPI_UINT32	IntervalTime;
	UCSAPI_UINT32	PulseTime;
	UCSAPI_UINT32	SiteCode;		
	UCSAPI_UINT32	FailID;
	UCSAPI_UINT8	MaskValue0[16];
	UCSAPI_UINT8	MaskValue1[16];
	UCSAPI_UINT8	MaskSiteCode[16];
	UCSAPI_UINT8	MaskUserID[16];
	UCSAPI_WIEGAND_PARITY		Parity[10];
} UCSAPI_WIEGAND_OUT, *UCSAPI_WIEGAND_OUT_PTR;

typedef UCSAPI_UINT8 UCSAPI_EMERGENCY_TYPE;
	#define UCSAPI_EMERGENCY_TYPE_NONE		0
	#define UCSAPI_EMERGENCY_TYPE_FIRE		1
	#define UCSAPI_EMERGENCY_TYPE_PANIC		2
	#define UCSAPI_EMERGENCY_TYPE_UNKNOWN	3

typedef UCSAPI_UINT8 UCSAPI_EMERGENCY_VALUE;
	#define UCSAPI_EMERGENCY_VALUE_OFF		0
	#define UCSAPI_EMERGENCY_VALUE_ON		1

typedef struct	ucsapi_emergency_info
{
	UCSAPI_EMERGENCY_TYPE	SignalType;
	UCSAPI_EMERGENCY_VALUE	SignalValue;
	UCSAPI_UINT8			Reserved[30];
} UCSAPI_EMERGENCY_INFO, *UCSAPI_EMERGENCY_INFO_PTR;

typedef UCSAPI_UINT8 UCSAPI_EMERGENCY_DOOR_CONTROL;
	#define UCSAPI_EMERGENCY_DOOR_CONTROL_NONE		0
	#define UCSAPI_EMERGENCY_DOOR_CONTROL_OPEN		1

typedef UCSAPI_UINT8 UCSAPI_EMERGENCY_ALARM_CONTROL;
	#define UCSAPI_EMERGENCY_ALARM_CONTROL_NONE		0
	#define UCSAPI_EMERGENCY_ALARM_CONTROL_PLAY		1

typedef struct	ucsapi_set_emergency_info
{
	UCSAPI_EMERGENCY_TYPE			SignalType;
	UCSAPI_EMERGENCY_VALUE			SignalValue;
	UCSAPI_EMERGENCY_DOOR_CONTROL	Door;
	UCSAPI_EMERGENCY_ALARM_CONTROL	Alarm;
	UCSAPI_UINT8			Reserved[28];
} UCSAPI_SET_EMERGENCY_INFO, *UCSAPI_SET_EMERGENCY_INFO_PTR;

#define SIZE_ACU_ALARM_DATA		15
typedef struct ucsapi_acu_alarm
{
	// CCCC 18 Q EEE GG ZZZ
	long Account;		// CCCC : Accunt
	long reserved;		// 18 :  
	long Qualifier;		// Q : 1 = alarm, 3 = restore
	long Event;			// EEE :
	long Partition;		// GG :
	long TargetID;		// ZZZ : ZoneID or UserID
} UCSAPI_ACU_ALARM, *UCSAPI_ACU_ALARM_PTR;

// Define for siren
#define MAX_SIREN_CONFIG		100
struct WeekDay_Flag
{
	BYTE	Sunday		:1;
	BYTE	Monday		:1;
	BYTE	Tuesday  	:1;
	BYTE	Wednesday	:1;
	BYTE	Thursday    :1;
	BYTE	Friday      :1;
	BYTE	Saturday 	:1;
	BYTE	OffHoliday	:1;
};

typedef struct siren_config
{		
	BYTE			Hour;
	BYTE			Minute;
	WeekDay_Flag	wf;
	BYTE			Duration;	// Seconds
	BYTE			Reserved[4];
} UCSAPI_SIREN_CONFIG, *UCSAPI_SIREN_CONFIG_PTR;


#endif /*_UCSAPI_TYPE_H*/
