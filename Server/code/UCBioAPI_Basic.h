#ifndef _UCBioAPI_BASIC_H
#define _UCBioAPI_BASIC_H

#ifdef WIN32
   #define UCBioAPI   __stdcall
#else /* (!WIN32) */
   #define UCBioAPI
#endif

#ifdef WIN32
   typedef __int8    UCBioAPI_SINT8;
   typedef __int16   UCBioAPI_SINT16;
   typedef int       UCBioAPI_SINT32;

   typedef BYTE      UCBioAPI_UINT8;
   typedef WORD      UCBioAPI_UINT16;
   typedef DWORD     UCBioAPI_UINT32;
   typedef __int64   UCBioAPI_UINT64;

   typedef INT_PTR   UCBioAPI_SINT;  
   typedef UINT_PTR  UCBioAPI_UINT;  

   typedef void*     UCBioAPI_VOID_PTR;
   typedef BOOL      UCBioAPI_BOOL;

   typedef CHAR      UCBioAPI_CHAR;
   typedef LPSTR     UCBioAPI_CHAR_PTR;

   #define UCBioAPI_FALSE   (0)
   #define UCBioAPI_TRUE    (1)
   
   #define UCBioAPI_NULL    (NULL)

   typedef HWND            UCBioAPI_HWND;
#else
   typedef char      UCBioAPI_SINT8;
   typedef short     UCBioAPI_SINT16;
   typedef int       UCBioAPI_SINT32;

   typedef unsigned char      UCBioAPI_UINT8;
   typedef unsigned short     UCBioAPI_UINT16;
   typedef unsigned int       UCBioAPI_UINT32;
   typedef unsigned long int  UCBioAPI_UINT64;

   typedef int                UCBioAPI_SINT;
   typedef unsigned int       UCBioAPI_UINT;

   typedef void*     UCBioAPI_VOID_PTR;
   typedef int       UCBioAPI_BOOL;

   typedef char      UCBioAPI_CHAR;
   typedef char*     UCBioAPI_CHAR_PTR;

   #define UCBioAPI_FALSE   (0)
   #define UCBioAPI_TRUE    (1)
   
   #define UCBioAPI_NULL    (0)
   #define MAX_PATH        (256)

   #define WINAPI
   typedef const UCBioAPI_CHAR_PTR   LPCTSTR;
   typedef UCBioAPI_CHAR_PTR         LPSTR;
   typedef UCBioAPI_CHAR             CHAR;
   typedef UCBioAPI_VOID_PTR         HINSTANCE;
   typedef UCBioAPI_UINT32           UCBioAPI_HWND;

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

#endif/*_UCBioAPI_BASIC_H */
