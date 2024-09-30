#ifndef _UCBioAPI_EXPORT_H
#define _UCBioAPI_EXPORT_H

#include "UCBioAPI.h"
#include "UCBioAPI_ExportType.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _UCBioAPI_LOAD_LIBRARY

   /* Export Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_FIRToTemplate(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             const UCBioAPI_INPUT_FIR_PTR     piFIR,
										               UCBioAPI_EXPORT_DATA_PTR         pExportData,
										               UCBioAPI_TEMPLATE_TYPE           nExportType);

   /* Import Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_TemplateToFIR(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_UINT8*                  pTemplateData, 
                                             UCBioAPI_UINT32                  nTemplateDataSize,
                                             UCBioAPI_UINT32                  nTemplateDataType,
                                             UCBioAPI_FIR_PURPOSE             nPurpose,
                                             UCBioAPI_FIR_HANDLE_PTR          phProcessedFIR);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_TemplateToFIREx(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_UINT8*                  pTemplateData, 
                                             UCBioAPI_UINT32                  nTemplateDataSize,
                                             UCBioAPI_UINT32                  nOneTemplateSize,
                                             UCBioAPI_UINT32                  nTemplateDataType,
                                             UCBioAPI_FIR_PURPOSE             nnPurpose,
                                             UCBioAPI_FIR_HANDLE_PTR          phProcessedFIR);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_ConvertTemplateData(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_UINT8*                  pTemplateData, 
                                             UCBioAPI_UINT32                  nTemplateDataSize,
                                             UCBioAPI_UINT32                  nOneTemplateSize,
                                             UCBioAPI_UINT32                  nTemplateDataType,
                                             UCBioAPI_UINT32                  nConvertType,
                                             UCBioAPI_UINT8**                 ppConvertedData, // ppConvertedData must be free by UCBioAPI_FreeData(..)
                                             UCBioAPI_UINT32**                ppConvertedDataLen); // ppConvertedDataLen must be free by UCBioAPI_FreeData(..)

   UCBioAPI_RETURN UCBioAPI UCBioAPI_FreeData(
                                             UCBioAPI_UINT8*                  pData);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_ImportDataToFIR(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_EXPORT_DATA_PTR         pExportData, 
                                             UCBioAPI_FIR_PURPOSE             nPurpose,
                                             UCBioAPI_FIR_HANDLE_PTR          phProcessedFIR);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_ImportDataToFIREx(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_EXPORT_DATA_PTR         pExportData, 
                                             UCBioAPI_FIR_PURPOSE             nPurpose,
                                             UCBioAPI_FIR_DATA_TYPE           nDataType,
                                             UCBioAPI_FIR_HANDLE_PTR          phProcessedFIR,
                                             UCBioAPI_VOID_PTR                pReserved);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_FreeExportData(
										               UCBioAPI_EXPORT_DATA_PTR         pExportData);

   /* BioAPI Opaque Data */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_ImportBioAPIOpaqueToFIRHandle(
                                             UCBioAPI_UINT8*                  pBioAPIOpaqueData,
                                             UCBioAPI_FIR_HANDLE_PTR          pFIRHandle,
                                             UCBioAPI_VOID_PTR                pReserved);
   /* Image Export Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_AuditFIRToImage(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             const UCBioAPI_INPUT_FIR_PTR     piAuditFIR,
										               UCBioAPI_EXPORT_AUDIT_DATA_PTR   pExportAuditData);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_ImageToAuditFIR(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_EXPORT_AUDIT_DATA_PTR   pExportAuditData,
                                             UCBioAPI_FIR_HANDLE_PTR          phAuditFIR);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_FreeExportAuditData(
										               UCBioAPI_EXPORT_AUDIT_DATA_PTR   pExportAuditData);

#endif/*_UCBioAPI_LOAD_LIBRARY */


   /* typedef for GetProcAddress() */

   /* Export Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_FIRToTemplate)(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             const UCBioAPI_INPUT_FIR_PTR     piFIR,
										               UCBioAPI_EXPORT_DATA_PTR         pExportData,
										               UCBioAPI_TEMPLATE_TYPE           nExportType);

   /* Import Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_TemplateToFIR)(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_UINT8*                  pTemplateData, 
                                             UCBioAPI_UINT32                  nTemplateDataSize,
                                             UCBioAPI_UINT32                  nTemplateDataType,
                                             UCBioAPI_FIR_PURPOSE             nPurpose,
                                             UCBioAPI_FIR_HANDLE_PTR          phProcessedFIR);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_TemplateToFIREx)(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_UINT8*                  pTemplateData, 
                                             UCBioAPI_UINT32                  nTemplateDataSize,
                                             UCBioAPI_UINT32                  nOneTemplateSize,
                                             UCBioAPI_UINT32                  nTemplateDataType,
                                             UCBioAPI_FIR_PURPOSE             nPurpose,
                                             UCBioAPI_FIR_HANDLE_PTR          phProcessedFIR);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_ConvertTemplateData)(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_UINT8*                  pTemplateData, 
                                             UCBioAPI_UINT32                  nTemplateDataSize,
                                             UCBioAPI_UINT32                  nOneTemplateSize,
                                             UCBioAPI_UINT32                  nTemplateDataType,
                                             UCBioAPI_UINT32                  nConvertType,
                                             UCBioAPI_UINT8**                 ppConvertedData,
                                             UCBioAPI_UINT32**                ppConvertedDataLen);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_FreeData)(
                                             UCBioAPI_UINT8*                  pData);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_ImportDataToFIR)(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_EXPORT_DATA_PTR         pExportData, 
                                             UCBioAPI_FIR_PURPOSE             nPurpose,
                                             UCBioAPI_FIR_HANDLE_PTR          phProcessedFIR);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_ImportDataToFIREx)(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_EXPORT_DATA_PTR         pExportData, 
                                             UCBioAPI_FIR_PURPOSE             nPurpose,
                                             UCBioAPI_FIR_DATA_TYPE           nDataType,
                                             UCBioAPI_FIR_HANDLE_PTR          phProcessedFIR,
                                             UCBioAPI_VOID_PTR                pReserved);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_FreeExportData)(
										               UCBioAPI_EXPORT_DATA_PTR         pExportData);

   /* BioAPI Opaque Data */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_ImportBioAPIOpaqueToFIRHandle)(
                                             UCBioAPI_UINT8*                  pBioAPIOpaqueData,
                                             UCBioAPI_FIR_HANDLE_PTR          pFIRHandle,
                                             UCBioAPI_VOID_PTR                pReserved);

   /* Image Export Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_AuditFIRToImage)(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             const UCBioAPI_INPUT_FIR_PTR     piAuditFIR,
										               UCBioAPI_EXPORT_AUDIT_DATA_PTR   pExportAuditData);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_ImageToAuditFIR)(
                                             UCBioAPI_HANDLE                  hHandle, 
                                             UCBioAPI_EXPORT_AUDIT_DATA_PTR   pExportAuditData,
                                             UCBioAPI_FIR_HANDLE_PTR          phAuditFIR);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_FreeExportAuditData)(
										               UCBioAPI_EXPORT_AUDIT_DATA_PTR   pExportAuditData);

#ifdef __cplusplus
}
#endif

#endif/*_UCBioAPI_EXPORT_H */
