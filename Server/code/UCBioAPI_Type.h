#ifndef _UCBioAPI_TYPE_H
#define _UCBioAPI_TYPE_H

#include "UCBioAPI_Basic.h"

/* UCBioAPI_FIR_VERSION */
typedef UCBioAPI_UINT16  UCBioAPI_FIR_VERSION;

/* UCBioAPI_VERSION */
typedef struct ucbioapi_version // 4자리 버전으로 변경(2014-08-18 by kks)
{
	UCBioAPI_UINT16		Major1;
	UCBioAPI_UINT16		Major2;
	UCBioAPI_UINT16		Minor1;
	UCBioAPI_UINT16		Minor2;
} UCBioAPI_VERSION, *UCBioAPI_VERSION_PTR;

/* UCBioAPI_FIR_DATA_TYPE */
typedef UCBioAPI_UINT16   UCBioAPI_FIR_DATA_TYPE;
#define UCBioAPI_FIR_DATA_TYPE_RAW               (0x00)
#define UCBioAPI_FIR_DATA_TYPE_INTERMEDIATE      (0x01)
#define UCBioAPI_FIR_DATA_TYPE_PROCESSED         (0x02)
#define UCBioAPI_FIR_DATA_TYPE_ENCRYPTED         (0x10)

/* UCBioAPI_FIR_PURPOSE */
typedef UCBioAPI_UINT16   UCBioAPI_FIR_PURPOSE;
#define UCBioAPI_FIR_PURPOSE_VERIFY                          (0x01)
#define UCBioAPI_FIR_PURPOSE_IDENTIFY                        (0x02)
#define UCBioAPI_FIR_PURPOSE_ENROLL                          (0x03)
#define UCBioAPI_FIR_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY    (0x04)
#define UCBioAPI_FIR_PURPOSE_ENROLL_FOR_IDENTIFICATION_ONLY  (0x05)
#define UCBioAPI_FIR_PURPOSE_AUDIT                           (0x06)
#define UCBioAPI_FIR_PURPOSE_UPDATE                          (0x10)

/* UCBioAPI_FIR_QUALITY */
typedef UCBioAPI_UINT16   UCBioAPI_FIR_QUALITY;

/* UCBioAPI_FIR_PRIVILEGE */
typedef UCBioAPI_UINT16   UCBioAPI_FIR_PRIVILEGE;
#define UCBioAPI_FIR_PRIVILEGE_NOT_USED      (0)
#define UCBioAPI_FIR_PRIVILEGE_LOWEST        (1)
#define UCBioAPI_FIR_PRIVILEGE_LOWER         (2)
#define UCBioAPI_FIR_PRIVILEGE_LOW           (3)
#define UCBioAPI_FIR_PRIVILEGE_BELOW_NORMAL  (4)
#define UCBioAPI_FIR_PRIVILEGE_NORMAL        (5)
#define UCBioAPI_FIR_PRIVILEGE_ABOVE_NORMAL  (6)
#define UCBioAPI_FIR_PRIVILEGE_HIGH          (7)
#define UCBioAPI_FIR_PRIVILEGE_HIGHER        (8)
#define UCBioAPI_FIR_PRIVILEGE_HIGHEST       (9)

/* UCBioAPI_FIR_DATE */
typedef struct ucbioapi_fir_date {
   UCBioAPI_UINT16      Year;    // 0 = 2000 / 1 = 2001 / ...
   UCBioAPI_UINT8       Month;
   UCBioAPI_UINT8       Day;
} UCBioAPI_FIR_DATE;

/* UCBioAPI_FIR_UUID_INFO */
typedef struct ucbioapi_fir_ott_info {
   UCBioAPI_UINT32      Index;
   UCBioAPI_UINT8       UUID[16];
} UCBioAPI_FIR_UUID_INFO, *UCBioAPI_FIR_UUID_INFO_PTR;

/* UCBioAPI_OPTIONAL_DATA_TYPE */
typedef UCBioAPI_UINT32  UCBioAPI_OPTIONAL_DATA_TYPE;
#define UCBioAPI_OPTIONAL_DATA_TYPE_UUID            (0x00000001)
#define UCBioAPI_OPTIONAL_DATA_TYPE_PIN1            (0x00000002)
#define UCBioAPI_OPTIONAL_DATA_TYPE_PIN2            (0x00000004)
#define UCBioAPI_OPTIONAL_DATA_TYPE_PRIVILEGE       (0x00000008)
#define UCBioAPI_OPTIONAL_DATA_TYPE_SITEID          (0x00000010)
#define UCBioAPI_OPTIONAL_DATA_TYPE_ISSUEDATE       (0x00000020)
#define UCBioAPI_OPTIONAL_DATA_TYPE_EXPIREDATE      (0x00000040)
#define UCBioAPI_OPTIONAL_DATA_TYPE_ALL             (0xffffffff)

/* UCBioAPI_FIR_OPTIONAL_DATA */
typedef struct ucbioapi_fir_optional_data {
   UCBioAPI_UINT32          Length;
   UCBioAPI_FIR_UUID_INFO   UUIDInfo;
   UCBioAPI_UINT32          PIN1;
   UCBioAPI_UINT32          PIN2;
   UCBioAPI_UINT32          Privilege;     /* UCBioAPI_FIR_PRIVILEGE */
   UCBioAPI_UINT32          SiteID;
   UCBioAPI_FIR_DATE        IssueDate;
   UCBioAPI_FIR_DATE        ExpireDate;
   UCBioAPI_UINT32          Reserved;
} UCBioAPI_FIR_OPTIONAL_DATA, *UCBioAPI_FIR_OPTIONAL_DATA_PTR;

/* UCBioAPI_FIR_HEADER */
typedef struct ucbioapi_fir_header {
   UCBioAPI_UINT32             Length;     /* Header Length */
   UCBioAPI_UINT32             DataLength; /* Data Length */
   UCBioAPI_FIR_VERSION        Version;
   UCBioAPI_FIR_DATA_TYPE      DataType;
   UCBioAPI_FIR_PURPOSE        Purpose;
   UCBioAPI_FIR_QUALITY        Quality;
   UCBioAPI_FIR_OPTIONAL_DATA  OptionalData;
   UCBioAPI_UINT32             Reserved;
} UCBioAPI_FIR_HEADER, *UCBioAPI_FIR_HEADER_PTR;

/* UCBioAPI_FIR_DATA */
typedef UCBioAPI_UINT8   UCBioAPI_FIR_DATA;

/* UCBioAPI_FIR_FORMAT */
typedef UCBioAPI_UINT32  UCBioAPI_FIR_FORMAT;
#define UCBioAPI_FIR_FORMAT_STANDARD     (1)

/* UCBioAPI_FIR */
typedef struct ucbioapi_fir {
   UCBioAPI_FIR_FORMAT  Format;
   UCBioAPI_FIR_HEADER  Header;
   UCBioAPI_FIR_DATA*   Data;
} UCBioAPI_FIR, *UCBioAPI_FIR_PTR;


/* UCBioAPI_FIR_PAYLOAD */
typedef struct ucbioapi_fir_payload {
   UCBioAPI_UINT32      Length;
   UCBioAPI_UINT8*      Data;
} UCBioAPI_FIR_PAYLOAD, *UCBioAPI_FIR_PAYLOAD_PTR;

/* UCBioAPI_HANDLE */
typedef UCBioAPI_UINT  UCBioAPI_HANDLE;
typedef UCBioAPI_UINT* UCBioAPI_HANDLE_PTR;
#define UCBioAPI_INVALID_HANDLE      (0)

/* UCBioAPI_FIR_HANDLE */
typedef UCBioAPI_UINT  UCBioAPI_FIR_HANDLE;
typedef UCBioAPI_UINT* UCBioAPI_FIR_HANDLE_PTR;

/* UCBioAPI_FIR_SECURITY_LEVEL */
typedef UCBioAPI_UINT32   UCBioAPI_FIR_SECURITY_LEVEL;
#define UCBioAPI_FIR_SECURITY_LEVEL_LOWEST        (1)
#define UCBioAPI_FIR_SECURITY_LEVEL_LOWER         (2)
#define UCBioAPI_FIR_SECURITY_LEVEL_LOW           (3)
#define UCBioAPI_FIR_SECURITY_LEVEL_BELOW_NORMAL  (4)
#define UCBioAPI_FIR_SECURITY_LEVEL_NORMAL        (5)
#define UCBioAPI_FIR_SECURITY_LEVEL_ABOVE_NORMAL  (6)
#define UCBioAPI_FIR_SECURITY_LEVEL_HIGH          (7)
#define UCBioAPI_FIR_SECURITY_LEVEL_HIGHER        (8)
#define UCBioAPI_FIR_SECURITY_LEVEL_HIGHEST       (9)

/* UCBioAPI_TEMPLATE_FORMAT for SetDefaultTemplateFormat() */
typedef UCBioAPI_UINT32      UCBioAPI_TEMPLATE_FORMAT;
#define UCBioAPI_TEMPLATE_FORMAT_UNION400     (0)
#define UCBioAPI_TEMPLATE_FORMAT_ISO500       (1)
#define UCBioAPI_TEMPLATE_FORMAT_ISO600       (2)

typedef UCBioAPI_UINT32      UCBioAPI_LIVE_DETECT_LEVEL;
#define UCBioAPI_LIVE_DETECT_LEVEL_NONE			(0) // Default
#define UCBioAPI_LIVE_DETECT_LEVEL_TOUCH_ONLY   (1)	
#define UCBioAPI_LIVE_DETECT_LEVEL_LOW		    (2)
#define UCBioAPI_LIVE_DETECT_LEVEL_HIGH			(3)
#define UCBioAPI_LIVE_DETECT_LEVEL_HIGHEST		(4)

/* UCBioAPI_INIT_INFO_0 */
typedef struct ucbioapi_init_info_0 {
   UCBioAPI_UINT32                StructureType;            /* must be 0 */
   UCBioAPI_UINT32                MaxFingersForEnroll;      /* Default = 10 */
   UCBioAPI_UINT32                NecessaryEnrollNum;       /* Default = 0 : Depends on MaxFingersForEnroll */
   UCBioAPI_UINT32                SamplesPerFinger;         /* Default = 2 : not used */
   UCBioAPI_UINT32                DefaultTimeout;           /* Default = 10000ms = 10sec */
   UCBioAPI_FIR_SECURITY_LEVEL    SecurityLevelForEnroll;   /* Default = UCBioAPI_FIR_SECURITY_LEVEL_NORMAL */
   UCBioAPI_FIR_SECURITY_LEVEL    SecurityLevelForVerify;   /* Default = UCBioAPI_FIR_SECURITY_LEVEL_NORMAL */
   UCBioAPI_FIR_SECURITY_LEVEL    SecurityLevelForIdentify; /* Default = UCBioAPI_FIR_SECURITY_LEVEL_ABOVE_NORMAL */
   UCBioAPI_TEMPLATE_FORMAT		  TemplateFormat;		    /* Default = UCBioAPI_TEMPLATE_FORMAT_UNION400 */
   UCBioAPI_UINT32                LiveDetectLevel;			/* Default = UCBioAPI_LIVE_DETECT_LEVEL_NONE */
   UCBioAPI_UINT32                Reserved1;                /* Reserved */
   UCBioAPI_UINT32                Reserved2;                /* Reserved */
} UCBioAPI_INIT_INFO_0, *UCBioAPI_INIT_INFO_PTR_0;

typedef UCBioAPI_VOID_PTR    UCBioAPI_INIT_INFO_PTR;

/* UCBioAPI_DEVICE_ID - high one byte : device instance, low one byte : device name */
typedef UCBioAPI_UINT16   UCBioAPI_DEVICE_ID; 
#define UCBioAPI_DEVICE_ID_NONE            (0x0000)
#define UCBioAPI_DEVICE_ID_AUTO            (0x00ff)

/* UCBioAPI_DEVICE_NAME */
typedef UCBioAPI_UINT8    UCBioAPI_DEVICE_NAME; 

/* for Union Community Sensor */
#define UCBioAPI_DEVICE_NAME_FOH01			1
#define UCBioAPI_DEVICE_NAME_FOM01			2
#define UCBioAPI_DEVICE_NAME_FOH03			3
#define UCBioAPI_DEVICE_NAME_HAM500			4
#define UCBioAPI_DEVICE_NAME_FOH01A			5
#define UCBioAPI_DEVICE_NAME_FOM01A			6
#define UCBioAPI_DEVICE_NAME_FPR02			7
#define UCBioAPI_DEVICE_NAME_FSH01RF		8
#define UCBioAPI_DEVICE_NAME_FOH01RF		9
#define UCBioAPI_DEVICE_NAME_FR100			10
#define UCBioAPI_DEVICE_NAME_FPR02LFD		11
#define UCBioAPI_DEVICE_NAME_FOH01RFL		12
#define UCBioAPI_DEVICE_NAME_FSH01SC		13
#define UCBioAPI_DEVICE_NAME_FPR02V30_W		14
//2009.04.07 added by jwlee
#define UCBioAPI_DEVICE_NAME_FOH02SC		18
#define UCBioAPI_DEVICE_NAME_FOH02RF		19
#define UCBioAPI_DEVICE_NAME_FOH02SB		20
#define UCBioAPI_DEVICE_NAME_FPR02V30		21
#define UCBioAPI_DEVICE_NAME_FOH02			22
#define UCBioAPI_DEVICE_NAME_FOH02_W		23
#define UCBioAPI_DEVICE_NAME_FOH02SC_W		24
#define UCBioAPI_DEVICE_NAME_FOH02RF_W		25
#define UCBioAPI_DEVICE_NAME_FOH02SB_W		26
#define UCBioAPI_DEVICE_NAME_FOH02C			27
#define UCBioAPI_DEVICE_NAME_FAS02NL		28
#define UCBioAPI_DEVICE_NAME_FAS02NLC		29
#define UCBioAPI_DEVICE_NAME_FOH02CSC		30
#define UCBioAPI_DEVICE_NAME_FOH02CRF		31
#define UCBioAPI_DEVICE_NAME_FSCAND			32
#define UCBioAPI_DEVICE_NAME_FOH04			41
#define UCBioAPI_DEVICE_NAME_CS2000			42
#define UCBioAPI_DEVICE_NAME_CFS01			43	// by iddol
#define UCBioAPI_DEVICE_NAME_UHF01			44
#define UCBioAPI_DEVICE_NAME_FDU06			200	// by cbk

// 2013. 06.25 by kks
#define UCBioAPI_INPUT_1FINGER_2TIME		0	/* Default*/
#define UCBioAPI_INPUT_1FINGER_1TIME		1
#define UCBioAPI_INPUT_1FINGER_ROLLING		2
#define UCBioAPI_INPUT_2FINGER_1TIME		3


/* UCBioAPI_MAX_DEVICE */
#define UCBioAPI_MAX_DEVICE                (0xFE)

/* UCBioAPI_DEVICE_INFO_0 */
typedef struct ucbioapi_device_info_0 {
   UCBioAPI_UINT32      StructureType;  /* must be 0 */
   UCBioAPI_UINT32      ImageWidth;     /* Read Only */
   UCBioAPI_UINT32      ImageHeight;    /* Read Only */
   UCBioAPI_UINT32      Brightness;     /* Not Used  */
   UCBioAPI_UINT32      Contrast;       /* Not Used  */
   UCBioAPI_UINT32      Gain;
} UCBioAPI_DEVICE_INFO_0, *UCBioAPI_DEVICE_INFO_PTR_0;
typedef UCBioAPI_VOID_PTR    UCBioAPI_DEVICE_INFO_PTR;

/* UCBioAPI_DEVICE_INFO_EX */
typedef struct ucbioapi_deviceinfoex {
   UCBioAPI_DEVICE_ID NameID;
   UCBioAPI_UINT16    Instance;

   UCBioAPI_CHAR      Name[64];
   UCBioAPI_CHAR      Description[256];
   UCBioAPI_CHAR      Dll[64];
   UCBioAPI_CHAR      Sys[64];
   
   UCBioAPI_UINT32    Brightness;
   UCBioAPI_UINT32    Contrast;
   UCBioAPI_UINT32    Gain;

   UCBioAPI_UINT32    Reserved[8];
} UCBioAPI_DEVICE_INFO_EX, *UCBioAPI_DEVICE_INFO_EX_PTR;

/* UCBioAPI_RETURN */
typedef UCBioAPI_UINT32  UCBioAPI_RETURN;

/* UCBioAPI_FIR_TEXTENCODE */
typedef struct ucbioapi_fir_textencode {
   UCBioAPI_BOOL      IsWideChar;
   UCBioAPI_CHAR_PTR  TextFIR;
} UCBioAPI_FIR_TEXTENCODE, *UCBioAPI_FIR_TEXTENCODE_PTR;

/* UCBioAPI_INPUT_FIR_FORM */
typedef UCBioAPI_UINT8   UCBioAPI_INPUT_FIR_FORM;
#define UCBioAPI_FIR_FORM_HANDLE      (0x02)
#define UCBioAPI_FIR_FORM_FULLFIR     (0x03)
#define UCBioAPI_FIR_FORM_TEXTENCODE  (0x04)

/*UCBioAPI_INPUT_FIR */
typedef struct ucbioapi_input_fir {
   UCBioAPI_INPUT_FIR_FORM  Form;
   union {
      UCBioAPI_FIR_HANDLE_PTR     FIRinBSP;
      UCBioAPI_VOID_PTR           FIR;
      UCBioAPI_FIR_TEXTENCODE_PTR TextFIR;
   } InputFIR;
} UCBioAPI_INPUT_FIR, *UCBioAPI_INPUT_FIR_PTR;

#define UCBioAPI_NO_TIMEOUT              (0)
#define UCBioAPI_USE_DEFAULT_TIMEOUT     (-1)
#define UCBioAPI_CONTINUOUS_CAPTRUE      (-2)

/* UCBioAPI_WINDOW_CALLBACK_PARAM_0 */
typedef struct ucbioapi_window_callback_param_0 {
   UCBioAPI_UINT32    dwQuality;
   UCBioAPI_UINT8*    lpImageBuf;
   UCBioAPI_UINT32    dwDeviceError;

   UCBioAPI_UINT32    dwReserved[8];
   UCBioAPI_VOID_PTR  lpReserved;
} UCBioAPI_WINDOW_CALLBACK_PARAM_0, *UCBioAPI_WINDOW_CALLBACK_PARAM_PTR_0;

/* UCBioAPI_WINDOW_CALLBACK_PARAM_1 */
typedef struct ucbioapi_window_callback_param_1 {
   UCBioAPI_UINT32    dwResult;
   
   UCBioAPI_UINT32    dwStartTime;
   UCBioAPI_UINT32    dwCapTime;
   UCBioAPI_UINT32    dwEndTime;

   UCBioAPI_UINT32    Reserved[8];
   UCBioAPI_VOID_PTR  lpReserved;
} UCBioAPI_WINDOW_CALLBACK_PARAM_1, *UCBioAPI_WINDOW_CALLBACK_PARAM_PTR_1;

/* UCBioAPI_WINDOW_CALLBACK */
typedef UCBioAPI_RETURN (WINAPI* UCBioAPI_WINDOW_CALLBACK_0)(UCBioAPI_WINDOW_CALLBACK_PARAM_PTR_0, UCBioAPI_VOID_PTR);
typedef UCBioAPI_RETURN (WINAPI* UCBioAPI_WINDOW_CALLBACK_1)(UCBioAPI_WINDOW_CALLBACK_PARAM_PTR_1, UCBioAPI_VOID_PTR);

typedef struct ucbioapi_callback_info_0 {
   UCBioAPI_UINT32             CallBackType;
   UCBioAPI_WINDOW_CALLBACK_0  CallBackFunction; 
   UCBioAPI_VOID_PTR           UserCallBackParam;
} UCBioAPI_CALLBACK_INFO_0, *UCBioAPI_CALLBACK_INFO_PTR_0;

typedef struct ucbioapi_callback_info_1 {
   UCBioAPI_UINT32             CallBackType;
   UCBioAPI_WINDOW_CALLBACK_1  CallBackFunction; 
   UCBioAPI_VOID_PTR           UserCallBackParam;
} UCBioAPI_CALLBACK_INFO_1, *UCBioAPI_CALLBACK_INFO_PTR_1;

/* UCBioAPI_WINDOW_STYLE */
typedef UCBioAPI_UINT32  UCBioAPI_WINDOW_STYLE;
#define UCBioAPI_WINDOW_STYLE_POPUP        (0)
#define UCBioAPI_WINDOW_STYLE_INVISIBLE    (1)   /* only for UCBioAPI_Capture() */
/* OR flag used only in high 2 bytes. */
#define UCBioAPI_WINDOW_STYLE_NO_FPIMG     (0x00010000)   /* Or flag */
#define UCBioAPI_WINDOW_STYLE_NO_WELCOME   (0x00020000)   /* Or flag : only for enroll */
#define UCBioAPI_WINDOW_STYLE_NO_TOPMOST   (0x00040000)   /* Or flag */

/* UCBioAPI_WINDOW_OPTION_2 */
typedef struct ucbioapi_window_option_2 {
   UCBioAPI_UINT8           FPForeColor[3];   /* Fingerprint RGB color */
   UCBioAPI_UINT8           FPBackColor[3];   /* Background RGB color */
   UCBioAPI_UINT8           DisableFingerForEnroll[11];   /* 0 = Enable, 1 = Disable / [0] = Not used, [1] = Right Thumb, ... [6] = Left Thumb, ... [10] = Left little */
   UCBioAPI_UINT32          Reserved1[4];
   UCBioAPI_VOID_PTR        Reserved2;
} UCBioAPI_WINDOW_OPTION_2, *UCBioAPI_WINDOW_OPTION_PTR_2;

/* UCBioAPI_WINDOW_OPTION */
typedef struct ucbioapi_window_option {
   UCBioAPI_UINT32                Length;
   UCBioAPI_WINDOW_STYLE          WindowStyle;
   UCBioAPI_HWND                  ParentWnd;
   UCBioAPI_HWND                  FingerWnd;           /* only for .._STYLE_INVISIBLE */
   UCBioAPI_CALLBACK_INFO_0       CaptureCallBackInfo; /* CallBackType = 0 */
   UCBioAPI_CALLBACK_INFO_1       FinishCallBackInfo;  /* CallBackType = 1 */
   UCBioAPI_CHAR_PTR              CaptionMsg;
   UCBioAPI_CHAR_PTR              CancelMsg;
   UCBioAPI_WINDOW_OPTION_PTR_2   Option2;             /* Default : NULL */
} UCBioAPI_WINDOW_OPTION, *UCBioAPI_WINDOW_OPTION_PTR;

/* UCBioAPI_TEMPLATE_TYPE for ConvertMinDataToFIRHandle() */
typedef UCBioAPI_UINT32      UCBioAPI_TEMPLATE_TYPE;
#define UCBioAPI_TEMPLATE_TYPE_SIZE400        (400)
#define UCBioAPI_TEMPLATE_TYPE_SIZE500        (500)
#define UCBioAPI_TEMPLATE_TYPE_SIZE600        (600)
#define UCBioAPI_TEMPLATE_TYPE_SIZE800        (800)
#define UCBioAPI_TEMPLATE_TYPE_SIZE1000       (1000)
#define UCBioAPI_TEMPLATE_TYPE_SIZE1200       (1200)
#define UCBioAPI_TEMPLATE_TYPE_SIZE320        (320)
#define UCBioAPI_TEMPLATE_TYPE_SIZE256        (256)
#define UCBioAPI_TEMPLATE_TYPE_FMR            (1) 
#define UCBioAPI_TEMPLATE_TYPE_ANSI           (2)   
   

/* UCBioAPI_FINGER_ID */
typedef UCBioAPI_UINT8       UCBioAPI_FINGER_ID;
#define UCBioAPI_FINGER_ID_UNKNOWN           (0) /* for verify */
#define UCBioAPI_FINGER_ID_RIGHT_THUMB       (1)
#define UCBioAPI_FINGER_ID_RIGHT_INDEX       (2)
#define UCBioAPI_FINGER_ID_RIGHT_MIDDLE      (3)
#define UCBioAPI_FINGER_ID_RIGHT_RING        (4)
#define UCBioAPI_FINGER_ID_RIGHT_LITTLE      (5)
#define UCBioAPI_FINGER_ID_LEFT_THUMB        (6)
#define UCBioAPI_FINGER_ID_LEFT_INDEX        (7)
#define UCBioAPI_FINGER_ID_LEFT_MIDDLE       (8)
#define UCBioAPI_FINGER_ID_LEFT_RING         (9)
#define UCBioAPI_FINGER_ID_LEFT_LITTLE       (10)
#define UCBioAPI_FINGER_ID_MAX               (11)

/* Make device ID */
#define UCBioAPI_MAKEDEVICEID(deviceName, instanceNum) ( ((instanceNum & 0x00FF) << 8) + (deviceName & 0x00FF) )

/* UCBioAPI_MATCH_OPTION_0 */
typedef struct ucbioapi_match_option_0 {
   UCBioAPI_UINT8    StructureType;       /* must be 0 */
   UCBioAPI_UINT8    NoMatchFinger[UCBioAPI_FINGER_ID_MAX];  /* 0 = Match, 1 = Sample1 not match, 2 = Sample2 not match, 3 = Not match */
   UCBioAPI_UINT32   Reserved[8];
} UCBioAPI_MATCH_OPTION_0, *UCBioAPI_MATCH_OPTION_PTR_0;
typedef UCBioAPI_VOID_PTR    UCBioAPI_MATCH_OPTION_PTR;

#endif/*_UCBioAPI_TYPE_H */
