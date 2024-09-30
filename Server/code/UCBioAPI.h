#ifndef _UCBioAPI_H
#define _UCBioAPI_H

#include "UCBioAPI_Basic.h"
#include "UCBioAPI_Type.h"
#include "UCBioAPI_Error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _UCBioAPI_LOAD_LIBRARY

   /* Initializing Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_Init       (UCBioAPI_HANDLE_PTR  phHandle);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_Terminate  (UCBioAPI_HANDLE hHandle);

   /* Validity Check Function */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetValidityCode(UCBioAPI_HANDLE hHandle, UCBioAPI_UINT32 Code1, UCBioAPI_UINT32 Code2, UCBioAPI_UINT32 Code3, UCBioAPI_UINT32 Code4, UCBioAPI_UINT32* pResult1, UCBioAPI_UINT32* pResult2);

   /* Basic Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetVersion (UCBioAPI_HANDLE hHandle, UCBioAPI_VERSION_PTR  pVersion);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetInitInfo(UCBioAPI_HANDLE hHandle, UCBioAPI_UINT8 nStructureType, UCBioAPI_INIT_INFO_PTR pInitInfo);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_SetInitInfo(UCBioAPI_HANDLE hHandle, UCBioAPI_UINT8 nStructureType, UCBioAPI_INIT_INFO_PTR pInitInfo);
   
   /* Device Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_EnumerateDevice(UCBioAPI_HANDLE hHandle, 
                                                     UCBioAPI_UINT32* pNumDevice, 
                                                     UCBioAPI_DEVICE_ID** ppDeviceID,
                                                     UCBioAPI_DEVICE_INFO_EX** ppDeviceInfoEx);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_OpenDevice     (UCBioAPI_HANDLE hHandle, UCBioAPI_DEVICE_ID nDeviceID);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_CloseDevice    (UCBioAPI_HANDLE hHandle, UCBioAPI_DEVICE_ID nDeviceID);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetDeviceInfo  (UCBioAPI_HANDLE hHandle, UCBioAPI_DEVICE_ID nDeviceID, UCBioAPI_UINT8 nStructureType, UCBioAPI_DEVICE_INFO_PTR pDeviceInfo);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_SetDeviceInfo  (UCBioAPI_HANDLE hHandle, UCBioAPI_DEVICE_ID nDeviceID, UCBioAPI_UINT8 nStructureType, UCBioAPI_DEVICE_INFO_PTR pDeviceInfo);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_AdjustDevice   (UCBioAPI_HANDLE hHandle, const UCBioAPI_WINDOW_OPTION_PTR pWindowOption);
   UCBioAPI_DEVICE_ID UCBioAPI UCBioAPI_GetOpenedDeviceID(UCBioAPI_HANDLE hHandle);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_SetFingerInputType(UCBioAPI_HANDLE hHandle, UCBioAPI_UINT32 nInputType);
   UCBioAPI_UINT32 UCBioAPI UCBioAPI_GetFingerInputType(UCBioAPI_HANDLE hHandle);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_SetCaptureQuality(UCBioAPI_HANDLE hHandle, UCBioAPI_UINT32 nScanQuality, UCBioAPI_UINT32 nEnrollQuality, UCBioAPI_UINT32 nVerifyQuality, UCBioAPI_UINT32 nIdentifyQuality);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_CheckFinger    (UCBioAPI_HANDLE hHandle, UCBioAPI_BOOL* pbFingerExist);
   
   /* Memory Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_FreeFIRHandle       (UCBioAPI_FIR_HANDLE hFIR);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetFIRFromHandle    (UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_FIR_PTR pFIR);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetHeaderFromHandle (UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_FIR_HEADER_PTR pHeader);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetExtendedFIRFromHandle   (UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_VOID_PTR pFIR, UCBioAPI_FIR_FORMAT Format);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetExtendedHeaderFromHandle(UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_VOID_PTR pHeader, UCBioAPI_FIR_FORMAT Format);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_FreeFIR             (UCBioAPI_VOID_PTR pFIR);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_FreePayload         (UCBioAPI_FIR_PAYLOAD_PTR pPayload);
   
   /* TextEncode Funtions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetTextFIRFromHandle(UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_FIR_TEXTENCODE_PTR pTextFIR, UCBioAPI_BOOL bIsWide);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetExtendedTextFIRFromHandle(UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_FIR_TEXTENCODE_PTR pTextFIR, UCBioAPI_BOOL bIsWide, UCBioAPI_FIR_FORMAT Format);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_FreeTextFIR         (UCBioAPI_FIR_TEXTENCODE_PTR pTextFIR);

   /* BSP Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_Capture (
                                          UCBioAPI_HANDLE                  hHandle, 
                                          UCBioAPI_FIR_PURPOSE             nPurpose,
                                          UCBioAPI_FIR_HANDLE_PTR          phCapturedFIR,
                                          UCBioAPI_SINT32                  nTimeout,
                                          UCBioAPI_FIR_HANDLE_PTR          phAuditData,
                                          const UCBioAPI_WINDOW_OPTION_PTR pWindowOption);
   
   UCBioAPI_RETURN UCBioAPI UCBioAPI_Process (
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piCapturedFIR,
                                          UCBioAPI_FIR_HANDLE_PTR          phProcessedFIR);
   
   UCBioAPI_RETURN UCBioAPI UCBioAPI_CreateTemplate (
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piCapturedFIR,
                                          const UCBioAPI_INPUT_FIR_PTR     piStoredFIR,
                                          UCBioAPI_FIR_HANDLE_PTR          phNewFIR,
                                          const UCBioAPI_FIR_PAYLOAD_PTR   pPayload);
   
   UCBioAPI_RETURN UCBioAPI UCBioAPI_VerifyMatch (
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piProcessedFIR,
                                          const UCBioAPI_INPUT_FIR_PTR     piStoredFIR,
                                          UCBioAPI_BOOL*                   pbResult,
                                          UCBioAPI_FIR_PAYLOAD_PTR         pPayload);
   
   UCBioAPI_RETURN UCBioAPI UCBioAPI_VerifyMatchEx (
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piProcessedFIR,
                                          const UCBioAPI_INPUT_FIR_PTR     piStoredFIR,
                                          UCBioAPI_BOOL*                   pbResult,
                                          UCBioAPI_FIR_PAYLOAD_PTR         pPayload,
                                          UCBioAPI_MATCH_OPTION_PTR        pMatchOption);
   
   UCBioAPI_RETURN UCBioAPI UCBioAPI_Enroll (
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piStoredFIR,
                                          UCBioAPI_FIR_HANDLE_PTR          phEnrolledFIR,
                                          const UCBioAPI_FIR_PAYLOAD_PTR   pPayload,
                                          UCBioAPI_SINT32                  nTimeout,
                                          UCBioAPI_FIR_HANDLE_PTR          phAuditData,
                                          const UCBioAPI_WINDOW_OPTION_PTR pWindowOption);
   
   UCBioAPI_RETURN UCBioAPI UCBioAPI_Verify (
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piStoredFIR,
                                          UCBioAPI_BOOL*                   pbResult,
                                          UCBioAPI_FIR_PAYLOAD_PTR         pPayload,
                                          UCBioAPI_SINT32                  nTimeout,
                                          UCBioAPI_FIR_HANDLE_PTR          phAuditData,
                                          const UCBioAPI_WINDOW_OPTION_PTR pWindowOption);
   
   UCBioAPI_RETURN UCBioAPI UCBioAPI_SetTemplateFormat (
                                          UCBioAPI_HANDLE                  hHandle, 
                                          UCBioAPI_TEMPLATE_FORMAT		   TemplateFormat);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_SetLiveDetectLevel (
                                          UCBioAPI_HANDLE                  hHandle, 
                                          UCBioAPI_LIVE_DETECT_LEVEL	   LiveDetectLevel);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_SetAutoDetect(
                                          UCBioAPI_HANDLE                  hHandle, 
										  UCBioAPI_BOOL					   bFlag);
	UCBioAPI_RETURN UCBioAPI UCBioAPI_SetCaptureQuality(
                                          UCBioAPI_HANDLE					hHandle, 
                                          UCBioAPI_UINT32					nScanQuality,
                                          UCBioAPI_UINT32					nEnrollQuality,
                                          UCBioAPI_UINT32					nVerifyQuality,
                                          UCBioAPI_UINT32					nIdentifyQuality);
#ifndef _WIN32_WCE
   /* Skin Function */
   UCBioAPI_BOOL UCBioAPI UCBioAPI_SetSkinResource(LPCTSTR szResPath);
#endif
   
#endif/* _UCBioAPI_LOAD_LIBRARY */
   
   /* typedef for GetProcAddress() */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_Init)        (UCBioAPI_HANDLE_PTR  phHandle);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_Terminate)   (UCBioAPI_HANDLE hHandle);
   
   /* Validity Check Function */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetValidityCode)(UCBioAPI_HANDLE hHandle, UCBioAPI_UINT32 Code1, UCBioAPI_UINT32 Code2, UCBioAPI_UINT32 Code3, UCBioAPI_UINT32 Code4, UCBioAPI_UINT32* pResult1, UCBioAPI_UINT32* pResult2);

   /* Basic Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetVersion)  (UCBioAPI_HANDLE hHandle, UCBioAPI_VERSION_PTR  pVersion);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetInitInfo) (UCBioAPI_HANDLE hHandle, UCBioAPI_UINT8 nStructureType, UCBioAPI_INIT_INFO_PTR pInitInfo);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_SetInitInfo) (UCBioAPI_HANDLE hHandle, UCBioAPI_UINT8 nStructureType, UCBioAPI_INIT_INFO_PTR pInitInfo);
   
   /* Device Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_EnumerateDevice)(UCBioAPI_HANDLE hHandle, 
                                                                   UCBioAPI_UINT32* pNumDevice, 
                                                                   UCBioAPI_DEVICE_ID** ppDeviceID,
                                                                   UCBioAPI_DEVICE_INFO_EX** ppDeviceInfoEx);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_OpenDevice)     (UCBioAPI_HANDLE hHandle, UCBioAPI_DEVICE_ID nDeviceID);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_CloseDevice)    (UCBioAPI_HANDLE hHandle, UCBioAPI_DEVICE_ID nDeviceID);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetDeviceInfo)  (UCBioAPI_HANDLE hHandle, UCBioAPI_DEVICE_ID nDeviceID, UCBioAPI_UINT8 nStructureType, UCBioAPI_DEVICE_INFO_PTR pDeviceInfo);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_SetDeviceInfo)  (UCBioAPI_HANDLE hHandle, UCBioAPI_DEVICE_ID nDeviceID, UCBioAPI_UINT8 nStructureType, UCBioAPI_DEVICE_INFO_PTR pDeviceInfo);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_AdjustDevice)   (UCBioAPI_HANDLE hHandle, const UCBioAPI_WINDOW_OPTION_PTR pWindowOption);
   typedef UCBioAPI_DEVICE_ID (UCBioAPI *FP_UCBioAPI_GetOpenedDeviceID)(UCBioAPI_HANDLE hHandle);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_SetFingerInputType) (UCBioAPI_HANDLE hHandle, UCBioAPI_UINT32 nInputType);
   typedef UCBioAPI_UINT32 (UCBioAPI *FP_UCBioAPI_GetFingerInputType) (UCBioAPI_HANDLE hHandle);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_SetCaptureQuality) (UCBioAPI_HANDLE hHandle, UCBioAPI_UINT32 nScanQuality, UCBioAPI_UINT32 nEnrollQuality, UCBioAPI_UINT32 nVerifyQuality, UCBioAPI_UINT32 nIdentifyQuality);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_CheckFinger)    (UCBioAPI_HANDLE hHandle, UCBioAPI_BOOL* pbFingerExist);
   
   /* Memory Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_FreeFIRHandle)      (UCBioAPI_FIR_HANDLE hFIR);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetFIRFromHandle)   (UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_FIR_PTR pFIR);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetHeaderFromHandle)(UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_FIR_HEADER_PTR pHeader);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetExtendedFIRFromHandle)   (UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_VOID_PTR pFIR, UCBioAPI_FIR_FORMAT Format);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetExtendedHeaderFromHandle)(UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_VOID_PTR pHeader, UCBioAPI_FIR_FORMAT Format);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_FreeFIR)            (UCBioAPI_VOID_PTR pFIR);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_FreePayload)        (UCBioAPI_FIR_PAYLOAD_PTR pPayload);

   /* TextEncode Funtions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetTextFIRFromHandle)(UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_FIR_TEXTENCODE_PTR pTextFIR, UCBioAPI_BOOL bIsWide);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetExtendedTextFIRFromHandle)(UCBioAPI_FIR_HANDLE hFIR, UCBioAPI_FIR_TEXTENCODE_PTR pTextFIR, UCBioAPI_BOOL bIsWide, UCBioAPI_FIR_FORMAT Format);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_FreeTextFIR)         (UCBioAPI_FIR_TEXTENCODE_PTR pTextFIR);
   
   /* BSP Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_Capture)(
                                          UCBioAPI_HANDLE                  hHandle, 
                                          UCBioAPI_FIR_PURPOSE             nPurpose,
                                          UCBioAPI_FIR_HANDLE_PTR          phCapturedFIR,
                                          UCBioAPI_SINT32                  nTimeout,
                                          UCBioAPI_FIR_HANDLE_PTR          phAuditData,
                                          const UCBioAPI_WINDOW_OPTION_PTR pWindowOption);
   
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_Process)(
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piCapturedFIR,
                                          UCBioAPI_FIR_HANDLE_PTR          phProcessedFIR);
   
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_CreateTemplate)(
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piCapturedFIR,
                                          const UCBioAPI_INPUT_FIR_PTR     piStoredFIR,
                                          UCBioAPI_FIR_HANDLE_PTR          phNewFIR,
                                          const UCBioAPI_FIR_PAYLOAD_PTR   pPayload);
   
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_VerifyMatch)(
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piProcessedFIR,
                                          const UCBioAPI_INPUT_FIR_PTR     piStoredFIR,
                                          UCBioAPI_BOOL*                   pbResult,
                                          UCBioAPI_FIR_PAYLOAD_PTR         pPayload);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_VerifyMatchEx)(
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piProcessedFIR,
                                          const UCBioAPI_INPUT_FIR_PTR     piStoredFIR,
                                          UCBioAPI_BOOL*                   pbResult,
                                          UCBioAPI_FIR_PAYLOAD_PTR         pPayload,
                                          UCBioAPI_MATCH_OPTION_PTR        pMatchOption);
   
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_Enroll)(
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piStoredFIR,
                                          UCBioAPI_FIR_HANDLE_PTR          phEnrolledFIR,
                                          const UCBioAPI_FIR_PAYLOAD_PTR   pPayload,
                                          UCBioAPI_SINT32                  nTimeout,
                                          UCBioAPI_FIR_HANDLE_PTR          phAuditData,
                                          const UCBioAPI_WINDOW_OPTION_PTR WindowOption);
   
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_Verify)(
                                          UCBioAPI_HANDLE                  hHandle, 
                                          const UCBioAPI_INPUT_FIR_PTR     piStoredFIR,
                                          UCBioAPI_BOOL*                   pbResult,
                                          UCBioAPI_FIR_PAYLOAD_PTR         pPayload,
                                          UCBioAPI_SINT32                  nTimeout,
                                          UCBioAPI_FIR_HANDLE_PTR          phAuditData,
                                          const UCBioAPI_WINDOW_OPTION_PTR pWindowOption);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_SetTemplateFormat)(
                                          UCBioAPI_HANDLE                  hHandle, 
                                          UCBioAPI_TEMPLATE_TYPE		   TemplateType);
 
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_SetLiveDetectLevel)(
                                          UCBioAPI_HANDLE                  hHandle, 
                                          UCBioAPI_TEMPLATE_TYPE		   LiveDetectLevel);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_SetAutoDetect)(
                                          UCBioAPI_HANDLE                  hHandle, 
										  UCBioAPI_BOOL					   bFlag);
	
	typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_SetCaptureQuality)(
										UCBioAPI_HANDLE					hHandle, 
										UCBioAPI_UINT32					nScanQuality,
										UCBioAPI_UINT32					nEnrollQuality,
										UCBioAPI_UINT32					nVerifyQuality,
										UCBioAPI_UINT32					nIdentifyQuality);
#ifndef _WIN32_WCE
   /* Skin Function */
   typedef UCBioAPI_BOOL (UCBioAPI *FP_UCBioAPI_SetSkinResource)(
                                          LPCTSTR szResPath);
#endif

#ifdef __cplusplus
}
#endif

#endif/* _UCBioAPI_H */
