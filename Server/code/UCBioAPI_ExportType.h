#ifndef _UCBioAPI_EXPORT_TYPE_H
#define _UCBioAPI_EXPORT_TYPE_H

#include "UCBioAPI_Type.h"

/* UCBioAPI_TEMPLATE_BLOCK */
typedef struct ucbioapi_template_block {
   UCBioAPI_UINT32             Length;           /* just length of Data (not sizeof structure) */
   UCBioAPI_UINT8*             Data;             /* variable length of data */
} UCBioAPI_TEMPLATE_BLOCK, *UCBioAPI_TEMPLATE_BLOCK_PTR;

/* UCBioAPI_FINGER_BLOCK */
typedef struct ucbioapi_finger_block {
   UCBioAPI_UINT32                Length;        /* sizeof of structure */
   UCBioAPI_FINGER_ID             FingerID;      /* UCBioAPI_FINGER_ID */
   UCBioAPI_TEMPLATE_BLOCK_PTR    TemplateInfo;  /* TemplateInfo = UCBioAPI_TEMPLATE_INFO * SamplesPerFinger */
} UCBioAPI_FINGER_BLOCK, *UCBioAPI_FINGER_BLOCK_PTR;

/* UCBioAPI_EXPORT_DATA */
typedef struct ucbioapi_export_data {
   UCBioAPI_UINT32             Length;           /* sizeof of structure */
   UCBioAPI_TEMPLATE_TYPE      TemplateType;     /* Template type */
   UCBioAPI_UINT8              FingerNum;
   UCBioAPI_FINGER_ID          DefaultFingerID;  /* UCBioAPI_FINGER_ID */
   UCBioAPI_UINT8              SamplesPerFinger;
   UCBioAPI_UINT8              Reserved;
   UCBioAPI_FINGER_BLOCK_PTR   FingerInfo;       /* Finger information */
} UCBioAPI_EXPORT_DATA, *UCBioAPI_EXPORT_DATA_PTR;

/* UCBioAPI_IMAGE_DATA */
typedef struct ucbioapi_image_data {
   UCBioAPI_UINT32             Length;           /* sizeof of structure */
   UCBioAPI_UINT8*             Data;             /* Data Length = ImageWidth * ImageHeight */
} UCBioAPI_IMAGE_DATA, *UCBioAPI_IMAGE_DATA_PTR;

/* UCBioAPI_AUDIT_DATA */
typedef struct ucbioapi_audit_data {
   UCBioAPI_UINT32             Length;           /* sizeof of structure */
   UCBioAPI_UINT8              FingerID;         /* UCBioAPI_FINGER_ID */
   UCBioAPI_IMAGE_DATA_PTR     Image;            /* AuditData = UCBioAPI_IMAGE_DATA * SamplesPerFinger */
} UCBioAPI_AUDIT_DATA, *UCBioAPI_AUDIT_DATA_PTR;

/* UCBioAPI_EXPORT_AUDIT_DATA */
typedef struct ucbioapi_export_audit_data {
   UCBioAPI_UINT32             Length;           /* sizeof of structure */
   UCBioAPI_UINT8              FingerNum;
   UCBioAPI_UINT8              SamplesPerFinger;
   UCBioAPI_UINT32             ImageWidth;
   UCBioAPI_UINT32             ImageHeight;
   UCBioAPI_AUDIT_DATA_PTR     AuditData;        /* AuditData = UCBioAPI_AUDIT_DATA * FingerNum */
   UCBioAPI_UINT32             Reserved;
} UCBioAPI_EXPORT_AUDIT_DATA, *UCBioAPI_EXPORT_AUDIT_DATA_PTR;

#endif/*_UCBioAPI_EXPORT_TYPE_H */
