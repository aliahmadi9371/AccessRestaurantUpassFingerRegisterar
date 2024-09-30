#ifndef _UCSAPI_BASIC_H
#define _UCSAPI_BASIC_H

#ifdef WIN32
   #define UCSAPI   __stdcall
#else /* (!WIN32) */
   #define UCSAPI
#endif

#ifdef WIN32
   typedef __int8    UCSAPI_SINT8;
   typedef __int16   UCSAPI_SINT16;
   typedef int       UCSAPI_SINT32;

   typedef BYTE      UCSAPI_UINT8;
   typedef WORD      UCSAPI_UINT16;
   typedef DWORD     UCSAPI_UINT32;
   typedef __int64   UCSAPI_UINT64;

   typedef INT_PTR   UCSAPI_SINT;  
   typedef UINT_PTR  UCSAPI_UINT;  

   typedef void*     UCSAPI_VOID_PTR;
   typedef BOOL      UCSAPI_BOOL;

   typedef CHAR      UCSAPI_CHAR;
   typedef LPSTR     UCSAPI_CHAR_PTR;

   #define UCSAPI_FALSE   (0)
   #define UCSAPI_TRUE    (1)
   
   #define UCSAPI_NULL    (NULL)

   typedef HWND            UCSAPI_HWND;
#else
   typedef char      UCSAPI_SINT8;
   typedef short     UCSAPI_SINT16;
   typedef int       UCSAPI_SINT32;

   typedef unsigned char      UCSAPI_UINT8;
   typedef unsigned short     UCSAPI_UINT16;
   typedef unsigned int       UCSAPI_UINT32;
   typedef unsigned long int  UCSAPI_UINT64;

   typedef int                UCSAPI_SINT;
   typedef unsigned int       UCSAPI_UINT;

   typedef void*     UCSAPI_VOID_PTR;
   typedef int       UCSAPI_BOOL;

   typedef char      UCSAPI_CHAR;
   typedef char*     UCSAPI_CHAR_PTR;

   #define UCSAPI_FALSE   (0)
   #define UCSAPI_TRUE    (1)
   
   #define UCSAPI_NULL    (0)
   #define MAX_PATH        (256)

   #define WINAPI
   typedef const UCSAPI_CHAR_PTR   LPCTSTR;
   typedef UCSAPI_CHAR_PTR         LPSTR;
   typedef UCSAPI_CHAR             CHAR;
   typedef UCSAPI_VOID_PTR         HINSTANCE;
   typedef UCSAPI_UINT32           UCSAPI_HWND;

   #define IDOK                1
   #define IDCANCEL            2
#endif/* WIN32 */

/* Macros for byte-order conversion */
#ifndef LITTLE_ENDIAN   
   #ifndef _UNIX
      #define LITTLE_ENDIAN
   #endif
#endif
   
#ifdef LITTLE_ENDIAN
#define EndianChange4(a)	(a)
#define EndianChange2(a)	(a)
#else
#define EndianChange4(val)\
	(\
      (((val) & 0xff000000) >> 24) | (((val) & 0x00ff0000) >> 8) |   \
	   (((val) & 0x0000ff00) << 8) | (((val) & 0x000000ff) << 24)     \
   )
#define EndianChange2(val)\
   ((((val) & 0xff00) >> 8) | (((val) & 0x00ff) << 8))
#endif

#endif/*_UCSAPI_BASIC_H */
