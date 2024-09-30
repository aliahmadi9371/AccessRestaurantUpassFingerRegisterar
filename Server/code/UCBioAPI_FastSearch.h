#ifndef _UCBioAPI_FASTSEARCH_H
#define _UCBioAPI_FASTSEARCH_H

#include "UCBioAPI_Basic.h"
#include "UCBioAPI_Type.h"
#include "UCBioAPI_FastSearchType.h"
#include "UCBioAPI_Error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _UCBioAPI_LOAD_LIBRARY

   /* FastSearch Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_InitFastSearchEngine(UCBioAPI_HANDLE hHandle);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_TerminateFastSearchEngine(UCBioAPI_HANDLE hHandle);

   /* Parameter Funtions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_SetFastSearchInitInfo(
                 UCBioAPI_HANDLE                    hHandle,
                 UCBioAPI_UINT8                     nStructureType,
                 UCBioAPI_INIT_INFO_PTR             pInitInfo);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetFastSearchInitInfo(
                 UCBioAPI_HANDLE                    hHandle,
                 UCBioAPI_UINT8                     nStructureType,
                 UCBioAPI_INIT_INFO_PTR             pInitInfo);

   /* Add Funtion */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_AddFIRToFastSearchDB(
                 UCBioAPI_HANDLE                    hHandle, 
                 const UCBioAPI_INPUT_FIR_PTR       pInputFIR,
                 UCBioAPI_UINT32                    nUserID,
                 UCBioAPI_FASTSEARCH_SAMPLE_INFO_PTR pSampleInfo);

   /* Remove Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_RemoveFpFromFastSearchDB(
                 UCBioAPI_HANDLE                    hHandle,
                 UCBioAPI_FASTSEARCH_FP_INFO_PTR    pFpInfo);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_RemoveUserFromFastSearchDB(
                 UCBioAPI_HANDLE                    hHandle,
                 UCBioAPI_UINT32                    nUserID);
        
   /* Searching Funtions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_IdentifyFIRFromFastSearchDB(
                 UCBioAPI_HANDLE                    hHandle, 
                 const UCBioAPI_INPUT_FIR_PTR       pInputFIR,
                 UCBioAPI_FIR_SECURITY_LEVEL        nSecuLevel,
                 UCBioAPI_FASTSEARCH_FP_INFO_PTR    pFpInfo,
                 UCBioAPI_FASTSEARCH_CALLBACK_INFO_PTR_0  pCallbackInfo0);

   /* DB Funtions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_ClearFastSearchDB(UCBioAPI_HANDLE hHandle);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_SaveFastSearchDBToFile(
                 UCBioAPI_HANDLE                    hHandle, 
                 const UCBioAPI_CHAR*               szFilepath);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_LoadFastSearchDBFromFile(
                 UCBioAPI_HANDLE                    hHandle, 
                 const UCBioAPI_CHAR*               szFilepath);

   /* Check Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetFpCountFromFastSearchDB(
                 UCBioAPI_HANDLE                    hHandle, 
                 UCBioAPI_UINT32*                   pDataCount);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_GetFpInfoFromFastSearchDB(
                 UCBioAPI_HANDLE                   hHandle, 
                 UCBioAPI_UINT32                   nDataIndex,
                 UCBioAPI_FASTSEARCH_FP_INFO_PTR   pFpInfo);
   UCBioAPI_RETURN UCBioAPI UCBioAPI_CheckFpExistInFastSearchDB(
                 UCBioAPI_HANDLE                    hHandle, 
                 UCBioAPI_FASTSEARCH_FP_INFO_PTR    pFpInfo,
                 UCBioAPI_BOOL*                     pExist);
   
#endif/* _UCBioAPI_LOAD_LIBRARY */
   
   /* FastSearch Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_InitFastSearchEngine)(UCBioAPI_HANDLE hHandle);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_TerminateFastSearchEngine)(UCBioAPI_HANDLE hHandle);

   /* Parameter Funtions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_SetFastSearchInitInfo)(
                 UCBioAPI_HANDLE                    hHandle,
                 UCBioAPI_UINT8                     nStructureType,
                 UCBioAPI_INIT_INFO_PTR             pInitInfo);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetFastSearchInitInfo)(
                 UCBioAPI_HANDLE                    hHandle,
                 UCBioAPI_UINT8                     nStructureType,
                 UCBioAPI_INIT_INFO_PTR             pInitInfo);

   /* Add Funtion */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_AddFIRToFastSearchDB)(
                 UCBioAPI_HANDLE                    hHandle,
                 const UCBioAPI_INPUT_FIR_PTR       pInputFIR,
                 UCBioAPI_UINT32                    nUserID,
                 UCBioAPI_FASTSEARCH_SAMPLE_INFO_PTR pSampleInfo);
   
   /* Remove Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_RemoveFpFromFastSearchDB)(
                 UCBioAPI_HANDLE                    hHandle,
                 UCBioAPI_FASTSEARCH_FP_INFO_PTR    pFpInfo);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_RemoveUserFromFastSearchDB)(
                 UCBioAPI_HANDLE                    hHandle,
                 UCBioAPI_UINT32                    nUserID);
        
   /* Searching Funtions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_IdentifyFIRFromFastSearchDB)(
                 UCBioAPI_HANDLE                    hHandle,
                 const UCBioAPI_INPUT_FIR_PTR       pInputFIR,
                 UCBioAPI_FIR_SECURITY_LEVEL        nSecuLevel,
                 UCBioAPI_FASTSEARCH_FP_INFO_PTR    pFpInfo,
                 UCBioAPI_FASTSEARCH_CALLBACK_INFO_PTR_0 pCallbackInfo0);

   /* DB Funtions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_ClearFastSearchDB)(UCBioAPI_HANDLE hHandle);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_SaveFastSearchDBToFile)(
                 UCBioAPI_HANDLE                    hHandle,
                 const UCBioAPI_CHAR*               szFilepath);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_LoadFastSearchDBFromFile)(
                 UCBioAPI_HANDLE                    hHandle,
                 const UCBioAPI_CHAR*               szFilepath);

   /* Check Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetFpCountFromFastSearchDB)(
                 UCBioAPI_HANDLE                    hHandle, 
                 UCBioAPI_UINT32*                   pDataCount);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_GetFpInfoFromFastSearchDB)(
                 UCBioAPI_HANDLE                   hHandle, 
                 UCBioAPI_UINT32                   nDataIndex,
                 UCBioAPI_FASTSEARCH_FP_INFO_PTR   pFpInfo);
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_CheckFpExistInFastSearchDB)(
                 UCBioAPI_HANDLE                    hHandle, 
                 UCBioAPI_FASTSEARCH_FP_INFO_PTR    pFpInfo,
                 UCBioAPI_BOOL*                     pExist);

#ifdef __cplusplus
}
#endif

#endif/* _UCBioAPI_FASTSEARCH_H */
