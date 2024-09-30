#ifndef _UCBioAPI_FASTSEARCHTYPE_H
#define _UCBioAPI_FASTSEARCHTYPE_H

#include "UCBioAPI_Basic.h"

/* UCBioAPI_FASTSEARCH_INIT_INFO_0 */
typedef struct ucbioapi_fastsearch_init_info_0 {
   UCBioAPI_UINT32                StructureType;           /* must be 0 */
   UCBioAPI_UINT32                UseGroupMatch;           /* Default = 1 (GroupMatch) */  
   UCBioAPI_UINT32                MatchMethod;             /* 0 = Default / 1 = MaxScore Method */
   UCBioAPI_UINT32                Researved1;              /* Reserved */
   UCBioAPI_UINT32                Researved2;              /* Reserved */
   UCBioAPI_UINT32                Researved3;              /* Reserved */
   UCBioAPI_UINT32                Researved4;              /* Reserved */
   UCBioAPI_UINT32                Researved5;              /* Reserved */
   UCBioAPI_UINT32*               Researved6;              /* Reserved */
} UCBioAPI_FASTSEARCH_INIT_INFO_0, *UCBioAPI_FASTSEARCH_INIT_INFO_PTR_0;

/* UCBioAPI_FASTSEARCH_FP_INFO */
typedef struct ucbioapi_fastsearch_fp_info {
   UCBioAPI_UINT32	ID;	
   UCBioAPI_UINT8	   FingerID;  /* UCBioAPI_FINGER_ID */
   UCBioAPI_UINT8	   SampleNumber;
   UCBioAPI_UINT32   Reserved1;
   UCBioAPI_UINT32   Reserved2;
} UCBioAPI_FASTSEARCH_FP_INFO, *UCBioAPI_FASTSEARCH_FP_INFO_PTR;

/* UCBioAPI_FASTSEARCH_SAMPLE_INFO */
typedef struct ucbioapi_fastsearch_sample_info {
   UCBioAPI_UINT32	ID;	
   UCBioAPI_UINT8	   SampleCount[11];  /* Unknown = 0, Right Thumb = 1, ... , Left Little = 10 */
} UCBioAPI_FASTSEARCH_SAMPLE_INFO, *UCBioAPI_FASTSEARCH_SAMPLE_INFO_PTR;


/* UCBioAPI_FASTSEARCH_CALLBACK_PARAM_0 */
typedef struct ucbioapi_fastsearch_callback_param_0 {
   UCBioAPI_UINT32                TotalCount;
   UCBioAPI_UINT32                MatchedIndex;
   UCBioAPI_UINT32                MatchedScore;
   UCBioAPI_UINT32                Reserved1;
   UCBioAPI_UINT32                Reserved2;
   UCBioAPI_UINT32                Reserved3;
   UCBioAPI_VOID_PTR              Reserved4;
} UCBioAPI_FASTSEARCH_CALLBACK_PARAM_0, *UCBioAPI_FASTSEARCH_CALLBACK_PARAM_PTR_0;

/* UCBioAPI_FASTSEARCH_CALLBACK */
typedef UCBioAPI_RETURN (WINAPI* UCBioAPI_FASTSEARCH_CALLBACK_0)(UCBioAPI_FASTSEARCH_CALLBACK_PARAM_PTR_0, UCBioAPI_VOID_PTR);

typedef struct ucbioapi_fastsearch_callback_info_0 {
   UCBioAPI_UINT32                   CallBackType;
   UCBioAPI_FASTSEARCH_CALLBACK_0    CallBackFunction; 
   UCBioAPI_VOID_PTR                 UserCallBackParam;
} UCBioAPI_FASTSEARCH_CALLBACK_INFO_0, *UCBioAPI_FASTSEARCH_CALLBACK_INFO_PTR_0;

/* Callback return value */
#define UCBioAPI_FASTSEARCH_CALLBACK_OK      (0)
#define UCBioAPI_FASTSEARCH_CALLBACK_STOP    (1)

#endif/*_UCBioAPI_FASTSEARCHTYPE_H */
