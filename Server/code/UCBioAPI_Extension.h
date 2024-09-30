#ifndef _UCBioAPI_EXTENSION_H
#define _UCBioAPI_EXTENSION_H

#include "UCBioAPI.h"
#include "UCBioAPI_ExportType.h"

#ifdef __cplusplus
extern "C" {
#endif


/* UCBioAPI_CAPTURE_OPTION */
typedef struct ucbioapi_capture_option {
   UCBioAPI_UINT32   Length;
   UCBioAPI_UINT32   Reserved1[8];
   UCBioAPI_VOID_PTR Reserved2;
} UCBioAPI_CAPTURE_OPTION, *UCBioAPI_CAPTURE_OPTION_PTR;

/* UCBioAPI_ENROLL_CALLBACK_PARAM_0 */
typedef struct ucbioapi_enroll_callback_param_0 {
   UCBioAPI_UINT8     FingerID;
   UCBioAPI_UINT8*    Image[2];
   UCBioAPI_UINT32    TemplateSize[2];
   UCBioAPI_UINT8*    Template[2];
   UCBioAPI_UINT32    Quality[2];

   UCBioAPI_UINT32    dwReserved[8];
   UCBioAPI_VOID_PTR  lpReserved;
} UCBioAPI_ENROLL_CALLBACK_PARAM_0, *UCBioAPI_ENROLL_CALLBACK_PARAM_PTR_0;

/* UCBioAPI_ENROLL_CALLBACK */
typedef UCBioAPI_RETURN (WINAPI* UCBioAPI_ENROLL_CALLBACK_0)(UCBioAPI_ENROLL_CALLBACK_PARAM_PTR_0, UCBioAPI_VOID_PTR);

/* UCBioAPI_INIT_INFO_1 */
typedef struct ucbioapi_init_info_1 {
   UCBioAPI_UINT32                StructureType;            /* must be 1 */

   UCBioAPI_UINT32                CallbackType;             /* Set only : 0 - EnrollCallback0 */
   UCBioAPI_VOID_PTR              CallbackFunction;
   UCBioAPI_VOID_PTR              CallbackUserParam;

   UCBioAPI_UINT32                Reserved1;                /* Reserved */
   UCBioAPI_UINT32                Reserved2;                /* Reserved */
   UCBioAPI_VOID_PTR              Reserved3;                /* Reserved */
} UCBioAPI_INIT_INFO_1, *UCBioAPI_INIT_INFO_PTR_1;

#ifndef _UCBioAPI_LOAD_LIBRARY

   /* Extension Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_CompareTwoFIR(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             const UCBioAPI_INPUT_FIR_PTR     pProcessedFIR,
                                             const UCBioAPI_INPUT_FIR_PTR     pStoredTemplate,
                                             UCBioAPI_SINT32*                 pMatchScore,
                                             const UCBioAPI_MATCH_OPTION_PTR  pMatchOption);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_CaptureEx(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_FIR_PURPOSE             nPurpose,
                                             UCBioAPI_FIR_HANDLE_PTR          phCapturedFIR,
                                             UCBioAPI_SINT32                  nTimeout,
                                             UCBioAPI_FIR_HANDLE_PTR          phAuditData,
                                             const UCBioAPI_WINDOW_OPTION_PTR pWindowOption,
                                             const UCBioAPI_CAPTURE_OPTION_PTR pCapOptionEx);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_VerifyEx(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             const UCBioAPI_INPUT_FIR_PTR     piStoredTemplate,
                                             UCBioAPI_BOOL*                   pbResult,
                                             UCBioAPI_FIR_PAYLOAD_PTR         pPayload,
                                             UCBioAPI_SINT32                  nTimeout,
                                             UCBioAPI_FIR_HANDLE_PTR          phAuditData,
                                             const UCBioAPI_WINDOW_OPTION_PTR pWindowOption,
                                             const UCBioAPI_CAPTURE_OPTION_PTR pCapOptionEx);


   /* Internal Communication */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetInitInfoFromMem(UCBioAPI_HANDLE hHandle);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_SetInitInfoToMem(UCBioAPI_HANDLE hHandle);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_InitEx(UCBioAPI_HANDLE_PTR  phHandle, UCBioAPI_UINT32 dwReserved, UCBioAPI_VOID_PTR pReserved);

#endif/*_UCBioAPI_LOAD_LIBRARY */


   /* typedef for GetProcAddress() */

   /* Extension Functions */
   typedef UCBioAPI_RETURN (UCBioAPI* FP_UCBioAPI_CompareTwoFIR)(
                                                UCBioAPI_HANDLE                  hHandle, 
                                                const UCBioAPI_INPUT_FIR_PTR     pProcessedFIR,
                                                const UCBioAPI_INPUT_FIR_PTR     pStoredTemplate,
                                                UCBioAPI_SINT32*                 pMatchScore,
                                                UCBioAPI_SINT32*                 pHitNumber,
                                                const UCBioAPI_MATCH_OPTION_PTR  pMatchOption);

   typedef UCBioAPI_RETURN (UCBioAPI* FP_UCBioAPI_CaptureEx)(
                                            UCBioAPI_HANDLE                  hHandle, 
                                            UCBioAPI_FIR_PURPOSE             nPurpose,
                                            UCBioAPI_FIR_HANDLE_PTR          phCapturedFIR,
                                            UCBioAPI_SINT32                  nTimeout,
                                            UCBioAPI_FIR_HANDLE_PTR          phAuditData,
                                            const UCBioAPI_WINDOW_OPTION_PTR pWindowOption,
                                            const UCBioAPI_CAPTURE_OPTION_PTR pCapOptionEx);

   typedef UCBioAPI_RETURN (UCBioAPI* FP_UCBioAPI_VerifyEx)(
                                           UCBioAPI_HANDLE                  hHandle, 
                                           const UCBioAPI_INPUT_FIR_PTR     piStoredTemplate,
                                           UCBioAPI_BOOL*                   pbResult,
                                           UCBioAPI_FIR_PAYLOAD_PTR         pPayload,
                                           UCBioAPI_SINT32                  nTimeout,
                                           UCBioAPI_FIR_HANDLE_PTR          phAuditData,
                                           const UCBioAPI_WINDOW_OPTION_PTR pWindowOption,
                                           const UCBioAPI_CAPTURE_OPTION_PTR pCapOptionEx);

   /* Internal Communication */
   typedef UCBioAPI_RETURN (UCBioAPI* FP_UCBioAPI_GetInitInfoFromMem)(UCBioAPI_HANDLE hHandle);
   typedef UCBioAPI_RETURN (UCBioAPI* FP_UCBioAPI_SetInitInfoToMem)(UCBioAPI_HANDLE hHandle);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_InitEx)(UCBioAPI_HANDLE_PTR  phHandle, UCBioAPI_UINT32 dwReserved, UCBioAPI_VOID_PTR pReserved);

#ifdef __cplusplus
}
#endif

#endif/*_UCBioAPI_EXTENSION_H */
