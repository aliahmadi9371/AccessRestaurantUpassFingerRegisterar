#ifndef _UCBioAPI_DEVICEEX_H
#define _UCBioAPI_DEVICEEX_H

#include "UCBioAPI.h"
#include "UCBioAPI_ExportType.h"

#ifdef __cplusplus
extern "C" {
#endif

/* UCBioAPI_DEVICE_INFO_1 */
typedef struct ucbioapi_device_info_1 {
   UCBioAPI_UINT32      StructureType;  /* must be 1 */
   UCBioAPI_UINT32      MajorVer, MinorVer;  /* Read Only */
   
   UCBioAPI_UINT32      Reserved1;
   UCBioAPI_UINT32      Reserved2;
   UCBioAPI_UINT32      Reserved3;
   UCBioAPI_UINT32      Reserved4;
} UCBioAPI_DEVICE_INFO_1, *UCBioAPI_DEVICE_INFO_PTR_1;

#ifndef _UCBioAPI_LOAD_LIBRARY

   /* Extension Functions */
   UCBioAPI_RETURN UCBioAPI UCBioAPI_EnumerateDeviceEx(UCBioAPI_HANDLE  hHandle, 
                                                       UCBioAPI_UINT32* pNumDevice, 
                                                       UCBioAPI_DEVICE_ID** ppDeviceID, 
                                                       UCBioAPI_DEVICE_INFO_EX** ppDeviceInfoEx,
                                                       UCBioAPI_UINT32  dwReserved,
                                                       UCBioAPI_VOID_PTR pReserved);

   UCBioAPI_RETURN UCBioAPI UCBioAPI_OpenDeviceEx(UCBioAPI_HANDLE hHandle, 
                                                  UCBioAPI_DEVICE_ID nDeviceID,
                                                  UCBioAPI_UINT32    dwReserved,
                                                  UCBioAPI_VOID_PTR  pReserved);

#endif/*_UCBioAPI_LOAD_LIBRARY */


   /* typedef for GetProcAddress() */

   /* Extension Functions */
   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_EnumerateDeviceEx)(UCBioAPI_HANDLE  hHandle, 
                                                                     UCBioAPI_UINT32* pNumDevice, 
                                                                     UCBioAPI_DEVICE_ID** ppDeviceID, 
                                                                     UCBioAPI_DEVICE_INFO_EX** ppDeviceInfoEx,
                                                                     UCBioAPI_UINT32  dwReserved,
                                                                     UCBioAPI_VOID_PTR pReserved);

   typedef UCBioAPI_RETURN (UCBioAPI *FP_UCBioAPI_OpenDeviceEx)(UCBioAPI_HANDLE hHandle, 
                                                  UCBioAPI_DEVICE_ID nDeviceID,
                                                  UCBioAPI_UINT32    dwReserved,
                                                  UCBioAPI_VOID_PTR  pReserved);

#ifdef __cplusplus
}
#endif

#endif/*_UCBioAPI_DEVICEEX_H */
