#ifndef RW_H
#define RW_H

#include "type.h"
#include "rw/rphanim.h"
#include "rw/rprandom.h"
#include "rw/rpusrdat.h"
#include "rw/rpworld.h"
#include "rw/rt2danim.h"
#include "rw/rtanim.h"
#include "rw/rtquat.h"
#include "rw/rwcore.h"
#include "rw/rwplcore.h"
#include "rw/rptank.h"

// TODO: move types into their appropriate files

typedef enum RpDMorphType {
    rpNADMORPHTYPE = 0,
    rpDMORPHTYPEGENERIC = 1,
    rpDMORPHTYPEFORCEENUMSIZEINT = 2147483647,
} RpDMorphType;
typedef enum RpGeometryFlag {
    rpGEOMETRYTRISTRIP = 1,
    rpGEOMETRYPOSITIONS = 2,
    rpGEOMETRYTEXTURED = 4,
    rpGEOMETRYPRELIT = 8,
    rpGEOMETRYNORMALS = 16,
    rpGEOMETRYLIGHT = 32,
    rpGEOMETRYMODULATEMATERIALCOLOR = 64,
    rpGEOMETRYTEXTURED2 = 128,
    rpGEOMETRYNATIVE = 16777216,
    rpGEOMETRYNATIVEINSTANCE = 33554432,
    rpGEOMETRYFLAGSMASK = 255,
    rpGEOMETRYNATIVEFLAGSMASK = 251658240,
    rpGEOMETRYFLAGFORCEENUMSIZEINT = 2147483647,
} RpGeometryFlag;
typedef enum RpHAnimHierarchyFlag {
    rpHANIMHIERARCHYSUBHIERARCHY = 1,
    rpHANIMHIERARCHYNOMATRICES = 2,
    rpHANIMHIERARCHYUPDATEMODELLINGMATRICES = 4096,
    rpHANIMHIERARCHYUPDATELTMS = 8192,
    rpHANIMHIERARCHYLOCALSPACEMATRICES = 16384,
    rpHANIMHIERARCHYFLAGFORCEENUMSIZEINT = 2147483647,
} RpHAnimHierarchyFlag;
typedef enum RpIntersectType {
    rpINTERSECTNONE = 0,
    rpINTERSECTLINE = 1,
    rpINTERSECTPOINT = 2,
    rpINTERSECTSPHERE = 3,
    rpINTERSECTBOX = 4,
    rpINTERSECTATOMIC = 5,
    rpINTERSECTTYPEFORCEENUMSIZEINT = 2147483647,
} RpIntersectType;
typedef enum RpLightType {
    rpNALIGHTTYPE = 0,
    rpLIGHTDIRECTIONAL = 1,
    rpLIGHTAMBIENT = 2,
    rpLIGHTPOINT = 128,
    rpLIGHTSPOT = 129,
    rpLIGHTSPOTSOFT = 130,
    rpLIGHTTYPEFORCEENUMSIZEINT = 2147483647,
} RpLightType;
typedef enum RpMatFXMaterialFlags {
    rpMATFXEFFECTNULL = 0,
    rpMATFXEFFECTBUMPMAP = 1,
    rpMATFXEFFECTENVMAP = 2,
    rpMATFXEFFECTBUMPENVMAP = 3,
    rpMATFXEFFECTDUAL = 4,
    rpMATFXEFFECTUVTRANSFORM = 5,
    rpMATFXEFFECTDUALUVTRANSFORM = 6,
    rpMATFXEFFECTMAX = 7,
    rpMATFXNUMEFFECTS = 6,
    rpMATFXFORCEENUMSIZEINT = 2147483647,
} RpMatFXMaterialFlags;
typedef enum RpMatFXSkyPipeline {
    rpNAMATFXSKYPIPELINE = 0,
    rpMATFXSKYATOMICPS2ALLPIPELINE = 1,
    rpMATFXSKYATOMICUV2PS2ALLPIPELINE = 2,
    rpMATFXSKYWORLDSECTORPS2ALLPIPELINE = 3,
    rpMATFXSKYWORLDSECTORUV2PS2ALLPIPELINE = 4,
    rpMATFXSKYPS2ALLMATPIPELINE = 5,
    rpMATFXSKYUV2PS2ALLMATPIPELINE = 6,
    rpMATFXSKYPIPELINEMAX = 7,
    rpMATFXSKYPIPELINEFORCEENUMSIZEINT = 2147483647,
} RpMatFXSkyPipeline;
typedef enum RpMeshHeaderFlags {
    rpMESHHEADERTRISTRIP = 1,
    rpMESHHEADERTRIFAN = 2,
    rpMESHHEADERLINELIST = 4,
    rpMESHHEADERPOLYLINE = 8,
    rpMESHHEADERPOINTLIST = 16,
    rpMESHHEADERPRIMMASK = 255,
    rpMESHHEADERUNINDEXED = 256,
    rpMESHHEADERFLAGSFORCEENUMSIZEINT = 2147483647,
} RpMeshHeaderFlags;
typedef enum RpPDSPipeID {
    rpNAPDSPIPEID = 0,
    rwPDS_G3_Generic_MatPipeID = 1,
    rwPDS_G3_Generic_AtmPipeID = 2,
    rwPDS_G3_Generic_SctPipeID = 3,
    rwPDS_G3_Im3D_TriPipeID = 4,
    rwPDS_G3_Im3D_SegPipeID = 5,
    rwPDS_G3_Im3D_TriObjPipeID = 6,
    rwPDS_G3_Im3D_SegObjPipeID = 7,
    rwPDS_G3_Generic_GrpMatPipeID = 4097,
    rwPDS_G3_Generic_GrpAtmPipeID = 4098,
    rwPDS_G3_Generic_GrpSctPipeID = 4099,
    rwPDS_G3_Skin_MatPipeID = 65537,
    rwPDS_G3_Skin_AtmPipeID = 65538,
    rwPDS_G3_Emb_MatPipeID = 65539,
    rwPDS_G3_Gem_MatPipeID = 65540,
    rwPDS_G3_Bem_MatPipeID = 65541,
    rwPDS_G3_Dup_MatPipeID = 65542,
    rwPDS_G3_Toon_MatPipeID = 65543,
    rwPDS_G3_SkinEmb_MatPipeID = 65544,
    rwPDS_G3_SkinGem_MatPipeID = 65545,
    rwPDS_G3_SkinBem_MatPipeID = 65546,
    rwPDS_G3_SkinDup_MatPipeID = 65547,
    rwPDS_G3_SkinToon_MatPipeID = 65548,
    rwPDS_G2_BPatch_AtmPipeID = 65549,
    rwPDS_G2_BPatch_MatPipeID = 65550,
    rwPDS_G2_SkinBPatch_AtmPipeID = 65551,
    rwPDS_G2_SkinBPatch_MatPipeID = 65552,
    rwPDS_G2_EmbBPatch_MatPipeID = 65553,
    rwPDS_G2_GemBPatch_MatPipeID = 65554,
    rwPDS_G2_BemBPatch_MatPipeID = 65555,
    rwPDS_G2_DupBPatch_MatPipeID = 65556,
    rwPDS_G2_SkinEmbBPatch_MatPipeID = 65557,
    rwPDS_G2_SkinGemBPatch_MatPipeID = 65558,
    rwPDS_G2_SkinBemBPatch_MatPipeID = 65559,
    rwPDS_G2_SkinDupBPatch_MatPipeID = 65560,
    rwPDS_G3_2DStroke_MatPipeID = 65561,
    rwPDS_G3_2DStroke_ObjPipeID = 65562,
    rwPDS_G3_2DFont_MatPipeID = 65563,
    rwPDS_G3_2DFont_ObjPipeID = 65564,
    rwPDS_G3_2DFill_MatPipeID = 65565,
    rwPDS_G3_2DFill_ObjPipeID = 65566,
    rwPDS_G3_SkSpt_AtmPipeID = 65567,
    rwPDS_G3_SkSpt_MatPipeID = 65568,
    rwPDS_G3_SkSptEmb_MatPipeID = 65569,
    rwPDS_G3_SkSptGem_MatPipeID = 65570,
    rwPDS_G3_SkSptBem_MatPipeID = 65571,
    rwPDS_G3_SkSptDup_MatPipeID = 65572,
    rwPDS_G3_SkSptToon_MatPipeID = 65573,
    rwPDS_G3_Uva_MatPipeID = 65574,
    rwPDS_G3_DupUva_MatPipeID = 65575,
    rwPDS_G3_SkinUva_MatPipeID = 65576,
    rwPDS_G3_SkinDupUva_MatPipeID = 65577,
    rwPDS_G3_SkSptUva_MatPipeID = 65578,
    rwPDS_G3_SkSptDupUva_MatPipeID = 65579,
    rwPDS_G3_Prj_MatPipeID = 65580,
    rwPDS_G3_SkinPrj_MatPipeID = 65581,
    rwPDS_G3_DMorph_MatPipeID = 65582,
    rwPDS_G3_Skin_GrpMatPipeID = 69633,
    rwPDS_G3_Skin_GrpAtmPipeID = 69634,
    rwPDS_G2_DarkMaps_GrpMatPipeID = 69635,
    rwPDS_G2_DarkMaps_GrpAtmPipeID = 69636,
    rwPDS_G2_DarkMaps_GrpSctPipeID = 69637,
    rwPDS_G3_Toon_GrpMatPipeID = 69638,
    rwPDS_G3_Toon_GrpAtmPipeID = 69639,
    rwPDS_G3_Toon_GrpSctPipeID = 69640,
    rwPDS_G3_SkinToon_GrpMatPipeID = 69641,
    rwPDS_G3_SkinToon_GrpAtmPipeID = 69642,
    rwPDS_G3_MatfxUV1_GrpMatPipeID = 69643,
    rwPDS_G3_MatfxUV2_GrpMatPipeID = 69644,
    rwPDS_G3_MatfxUV1_GrpAtmPipeID = 69645,
    rwPDS_G3_MatfxUV2_GrpAtmPipeID = 69646,
    rwPDS_G3_MatfxUV1_GrpSctPipeID = 69647,
    rwPDS_G3_MatfxUV2_GrpSctPipeID = 69648,
    rwPDS_G3_SkinfxUV1_GrpMatPipeID = 69649,
    rwPDS_G3_SkinfxUV2_GrpMatPipeID = 69650,
    rwPDS_G3_SkinfxUV1_GrpAtmPipeID = 69651,
    rwPDS_G3_SkinfxUV2_GrpAtmPipeID = 69652,
    rwPDS_G2_BPatch_GrpAtmPipeID = 69653,
    rwPDS_G2_BPatch_GrpMatPipeID = 69654,
    rwPDS_G2_SkinBPatch_GrpAtmPipeID = 69655,
    rwPDS_G2_SkinBPatch_GrpMatPipeID = 69656,
    rwPDS_G2_MatfxUV1BPatch_GrpMatPipeID = 69657,
    rwPDS_G2_MatfxUV2BPatch_GrpMatPipeID = 69658,
    rwPDS_G2_MatfxUV1BPatch_GrpAtmPipeID = 69659,
    rwPDS_G2_MatfxUV2BPatch_GrpAtmPipeID = 69660,
    rwPDS_G2_SkinfxUV1BPatch_GrpMatPipeID = 69661,
    rwPDS_G2_SkinfxUV2BPatch_GrpMatPipeID = 69662,
    rwPDS_G2_SkinfxUV1BPatch_GrpAtmPipeID = 69663,
    rwPDS_G2_SkinfxUV2BPatch_GrpAtmPipeID = 69664,
    rwPDS_VCL_Uva_MatPipeID = 73728,
    rwPDS_VCL_DupUva_MatPipeID = 73729,
    rwPDS_VCL_SkinUva_MatPipeID = 73730,
    rwPDS_VCL_SkinDupUva_MatPipeID = 73731,
    rwPDS_VCL_Prj_MatPipeID = 73732,
    rwPDS_VCL_SkinPrj_MatPipeID = 73733,
    rwPDS_G3x_Generic_AtmPipeID = 327681,
    rwPDS_G3x_APL_MatPipeID = 327682,
    rwPDS_G3x_ADL_MatPipeID = 327683,
    rwPDS_G3x_A4D_MatPipeID = 327684,
    rwPDS_G3x_APLDup_MatPipeID = 327685,
    rwPDS_G3x_ADLDup_MatPipeID = 327686,
    rwPDS_G3x_A4DDup_MatPipeID = 327687,
    rwPDS_G3x_APLGem_MatPipeID = 327688,
    rwPDS_G3x_ADLGem_MatPipeID = 327689,
    rwPDS_G3x_A4DGem_MatPipeID = 327690,
    rwPDS_G3x_Skin_AtmPipeID = 327691,
    rwPDS_G3x_APLSkin_MatPipeID = 327692,
    rwPDS_G3x_ADLSkin_MatPipeID = 327693,
    rwPDS_G3x_A4DSkin_MatPipeID = 327694,
    rwPDS_G3x_APLSkinDup_MatPipeID = 327695,
    rwPDS_G3x_ADLSkinDup_MatPipeID = 327696,
    rwPDS_G3x_A4DSkinDup_MatPipeID = 327697,
    rwPDS_G3x_APLSkinGem_MatPipeID = 327698,
    rwPDS_G3x_ADLSkinGem_MatPipeID = 327699,
    rwPDS_G3x_A4DSkinGem_MatPipeID = 327700,
    rwPDS_G3x_ADLClone_MatPipeID = 327701,
    rwPDS_G3x_ADLClone_AtmPipeID = 327702,
    rwPDS_G3x_OPLClone_MatPipeID = 327703,
    rwPDS_G3x_OPLClone_AtmPipeID = 327704,
    rwPDS_G3x_Team_MatPipeID = 327705,
    rwPDS_G3x_DupTeam_MatPipeID = 327706,
    rwPDS_G3x_GemTeam_MatPipeID = 327707,
    rwPDS_G3x_SkinTeam_MatPipeID = 327708,
    rwPDS_G3x_SkinDupTeam_MatPipeID = 327709,
    rwPDS_G3x_SkinGemTeam_MatPipeID = 327710,
    rwPDS_G3x_Team_AtmPipeID = 327711,
    rwPDS_G3x_SkinTeam_AtmPipeID = 327712,
    rwPDS_G3x_APLUva_MatPipeID = 327713,
    rwPDS_G3x_ADLUva_MatPipeID = 327714,
    rwPDS_G3x_A4DUva_MatPipeID = 327715,
    rwPDS_G3x_APLDupUva_MatPipeID = 327716,
    rwPDS_G3x_ADLDupUva_MatPipeID = 327717,
    rwPDS_G3x_A4DDupUva_MatPipeID = 327718,
    rwPDS_G3x_APLSkinUva_MatPipeID = 327719,
    rwPDS_G3x_ADLSkinUva_MatPipeID = 327720,
    rwPDS_G3x_A4DSkinUva_MatPipeID = 327721,
    rwPDS_G3x_APLSkDupUva_MatPipeID = 327722,
    rwPDS_G3x_ADLSkDupUva_MatPipeID = 327723,
    rwPDS_G3x_A4DSkDupUva_MatPipeID = 327724,
    rwPDS_G3xd_APL_MatPipeID = 327725,
    rwPDS_G3xd_ADL_MatPipeID = 327726,
    rwPDS_G3xd_A4D_MatPipeID = 327727,
    rwPDS_G3xd_APLDup_MatPipeID = 327728,
    rwPDS_G3xd_ADLDup_MatPipeID = 327729,
    rwPDS_G3xd_A4DDup_MatPipeID = 327730,
    rwPDS_G3xd_APLGem_MatPipeID = 327731,
    rwPDS_G3xd_ADLGem_MatPipeID = 327732,
    rwPDS_G3xd_A4DGem_MatPipeID = 327733,
    rwPDS_G3xd_APLUva_MatPipeID = 327734,
    rwPDS_G3xd_ADLUva_MatPipeID = 327735,
    rwPDS_G3xd_A4DUva_MatPipeID = 327736,
    rwPDS_G3xd_APLDupUva_MatPipeID = 327737,
    rwPDS_G3xd_ADLDupUva_MatPipeID = 327738,
    rwPDS_G3xd_A4DDupUva_MatPipeID = 327739,
    rwPDS_G3xd_APLSkin_MatPipeID = 327740,
    rwPDS_G3xd_ADLSkin_MatPipeID = 327741,
    rwPDS_G3xd_A4DSkin_MatPipeID = 327742,
    rwPDS_G3xd_APLSkinDup_MatPipeID = 327743,
    rwPDS_G3xd_ADLSkinDup_MatPipeID = 327744,
    rwPDS_G3xd_A4DSkinDup_MatPipeID = 327745,
    rwPDS_G3xd_APLSkinGem_MatPipeID = 327746,
    rwPDS_G3xd_ADLSkinGem_MatPipeID = 327747,
    rwPDS_G3xd_A4DSkinGem_MatPipeID = 327748,
    rwPDS_G3xd_APLSkinUva_MatPipeID = 327749,
    rwPDS_G3xd_ADLSkinUva_MatPipeID = 327750,
    rwPDS_G3xd_A4DSkinUva_MatPipeID = 327751,
    rwPDS_G3xd_APLSkDupUva_MatPipeID = 327752,
    rwPDS_G3xd_ADLSkDupUva_MatPipeID = 327753,
    rwPDS_G3xd_A4DSkDupUva_MatPipeID = 327754,
    rwPDS_G3x_SkinShd_AtmPipeID = 327755,
    rwPDS_G3x_SkinShd_MatPipeID = 327756,
    rwPDS_G3x_ADLDMorph_MatPipeID = 65613,
    rwPDS_G3x_APLDMorph_MatPipeID = 65614,
    rwPDS_G3x_A4DDMorph_MatPipeID = 65615,
    rwPDS_VCL_Generic_AtmPipeID = 331776,
    rwPDS_VCL_ADLDot3_MatPipeID = 331777,
    rwPDS_VCL_APLDot3_MatPipeID = 331778,
    rwPDS_VCL_ADLSpec_MatPipeID = 331779,
    rwPDS_VCL_APLSpec_MatPipeID = 331780,
    rwPDS_VCL_Skin_AtmPipeID = 331781,
    rwPDS_VCL_ADLSkinDot3_MatPipeID = 331782,
    rwPDS_VCL_APLSkinDot3_MatPipeID = 331783,
    rwPDS_VCL_ADLSkinSpec_MatPipeID = 331784,
    rwPDS_VCL_APLSkinSpec_MatPipeID = 331785,
    rpPDSMAXPIPEID = 331786,
    rpPDSPIPEIDFORCEENUMSIZEINT = 2147483647,
} RpPDSPipeID;
typedef enum RpPDSPipeType {
    rpNAPDSPIPETYPE = 0,
    rpPDSMATPIPE = 1,
    rpPDSOBJPIPE = 2,
    rpPDSPIPETYPEFORCEENUMSIZEINT = 2147483647,
} RpPDSPipeType;
typedef enum RpSkinType {
    rpNASKINTYPE = 0,
    rpSKINTYPEGENERIC = 1,
    rpSKINTYPEMATFX = 2,
    rpSKINTYPETOON = 3,
    rpSKINTYPEFORCEENUMSIZEINT = 2147483647,
} RpSkinType;
typedef enum RpTeamElementLOD {
    rpTEAMELEMENTLODFIRST = 0,
    rpTEAMELEMENTLODMAX = 5,
    rpTEAMELEMENTLODSHADOW1 = 5,
    rpTEAMELEMENTLODSHADOW4 = 6,
    rpTEAMELEMENTLODSUP = 7,
    rpTEAMELEMENTLODFORCEENUMSIZEINT = 2147483647,
} RpTeamElementLOD;
typedef enum RpTeamElementType {
    rpNATEAMELEMENTTYPE = 0,
    rpTEAMELEMENTSTATIC = 1,
    rpTEAMELEMENTSKINNED = 2,
    rpTEAMELEMENTPATCH = 4,
    rpTEAMELEMENTALL = 255,
    rpTEAMELEMENTFORCEENUMSIZEINT = 2147483647,
} RpTeamElementType;
typedef enum RpTeamLightType {
    rpTEAMAMBIENTDIRECTIONLIGHTING = 0,
    rpTEAMAMBIENT4DIRECTIONLIGHTING = 1,
    rpTEAMAMBIENTPOINTLIGHTING = 2,
    rpTEAMLIGHTTYPEFORCEENUMSIZEINT = 2147483647,
} RpTeamLightType;
typedef enum RpWorldRenderOrder {
    rpWORLDRENDERNARENDERORDER = 0,
    rpWORLDRENDERFRONT2BACK = 1,
    rpWORLDRENDERBACK2FRONT = 2,
    rpWORLDRENDERORDERFORCEENUMSIZEINT = 2147483647,
} RpWorldRenderOrder;
typedef enum Rt2dJustificationType {
    rt2dJUSTIFYLEFT = 0,
    rt2dJUSTIFYCENTER = 1,
    rt2dJUSTIFYRIGHT = 2,
    rt2DJUSTIFICATIONTYPEFORCEENUMSIZEINT = 2147483647,
} Rt2dJustificationType;
typedef enum RtFSFileOperation {
    RTFS_FILEOP_NONE = 1,
    RTFS_FILEOP_OPEN = 2,
    RTFS_FILEOP_CLOSE = 3,
    RTFS_FILEOP_SEEK = 4,
    RTFS_FILEOP_READ = 5,
    RTFS_FILEOP_TYPEFORCEENUMSIZEINT = 2147483647,
} RtFSFileOperation;
typedef enum RtFSManagerCallBackCode {
    RTFSM_CALLBACKCODE_ERROR = 1,
    RTFSM_CALLBACKCODE_ERROR_TYPEFORCEENUMSIZEINT = 2147483647,
} RtFSManagerCallBackCode;
typedef enum RtFSManagerError {
    RTFSM_ERROR_NOERROR = 1,
    RTFSM_ERROR_INSTALL = 2,
    RTFSM_ERROR_UNINSTALL = 3,
    RTFSM_ERROR_INVALIDFS = 4,
    RTFSM_ERROR_NOTREGISTRABLE = 5,
    RTFSM_ERROR_NOFS = 6,
    RTFSM_ERROR_FSNAMEINUSE = 7,
    RTFSM_ERROR_TOOMANYOPENFILES = 8,
    RTFSM_ERROR_TYPEFORCEENUMSIZEINT = 2147483647,
} RtFSManagerError;
typedef enum RtFileAccessFlag {
    RTFILE_ACCESS_OPEN_READ = 1,
    RTFILE_ACCESS_OPEN_WRITE = 2,
    RTFILE_ACCESS_OPEN_CREATE = 4,
    RTFILE_ACCESS_OPEN_APPEND = 8,
    RTFILE_ACCESS_OPEN_ASYNC = 16,
    RTFILE_ACCESS_NO_BUFFERING = 32,
    RTFILE_ACCESS_TYPEFORCEENUMSIZEINT = 2147483647,
} RtFileAccessFlag;
typedef enum RtFileError {
    RTFILE_ERROR_NOERROR = 1,
    RTFILE_ERROR_FILESYSTEM = 2,
    RTFILE_ERROR_FILE = 3,
    RTFILE_ERROR_DISKFULL = 4,
    RTFILE_ERROR_TYPEFORCEENUMSIZEINT = 2147483647,
} RtFileError;
typedef enum RtFileSeekMethod {
    RTFILE_POS_BEGIN = 1,
    RTFILE_POS_CURRENT = 2,
    RTFILE_POS_END = 3,
    RTFILE_POS_TYPEFORCEENUMSIZEINT = 2147483647,
} RtFileSeekMethod;
typedef enum RtFileStatus {
    RTFILE_STATUS_CLOSED = 1,
    RTFILE_STATUS_READY = 2,
    RTFILE_STATUS_BUSY = 3,
    RTFILE_STATUS_ERROR = 4,
    RTFILE_STATUS_OPENING = 5,
    RTFILE_STATUS_TYPEFORCEENUMSIZEINT = 2147483647,
} RtFileStatus;
typedef enum RtFileSystemError {
    RTFS_ERROR_NOERROR = 1,
    RTFS_ERROR_TOOMANYFILESYSTEMS = 2,
    RTFS_ERROR_FILENOTFOUND = 3,
    RTFS_ERROR_WRITEPROTECTED = 4,
    RTFS_ERROR_FILENAMETOOLONG = 5,
    RTFS_ERROR_FILESYSTEMNAMEINUSE = 6,
    RTFS_ERROR_FILESYSTEMDEVICENAMEREGISTERED = 7,
    RTFS_ERROR_TYPEFORCEENUMSIZEINT = 2147483647,
} RtFileSystemError;
typedef enum RtFileSystemStatus {
    RTFS_STATUS_NOTREADY = 1,
    RTFS_STATUS_READY = 2,
    RTFS_STATUS_DOOROPEN = 3,
    RTFS_STATUS_NOMEDIA = 4,
    RTFS_STATUS_WRONGMEDIA = 5,
    RTFS_STATUS_RETRYING = 6,
    RTFS_STATUS_FATAL = 7,
    RTFS_STATUS_TYPEFORCEENUMSIZEINT = 2147483647,
} RtFileSystemStatus;
typedef enum RwPlatformID {
    rwID_PCD3D7 = 1,
    rwID_PCOGL = 2,
    rwID_MAC = 3,
    rwID_PS2 = 4,
    rwID_XBOX = 5,
    rwID_GAMECUBE = 6,
    rwID_SOFTRAS = 7,
    rwID_PCD3D8 = 8,
    rwID_PCD3D9 = 9,
    rwPLATFROMIDFORCEENUMSIZEINT = 2147483647,
} RwPlatformID;
typedef enum RwStreamAccessType {
    rwNASTREAMACCESS = 0,
    rwSTREAMREAD = 1,
    rwSTREAMWRITE = 2,
    rwSTREAMAPPEND = 3,
    rwSTREAMACCESSTYPEFORCEENUMSIZEINT = 2147483647,
} RwStreamAccessType;
typedef enum RwStreamType {
    rwNASTREAM = 0,
    rwSTREAMFILE = 1,
    rwSTREAMFILENAME = 2,
    rwSTREAMMEMORY = 3,
    rwSTREAMCUSTOM = 4,
    rwSTREAMTYPEFORCEENUMSIZEINT = 2147483647,
} RwStreamType;
typedef enum RwTextureAddressMode {
    rwTEXTUREADDRESSNATEXTUREADDRESS = 0,
    rwTEXTUREADDRESSWRAP = 1,
    rwTEXTUREADDRESSMIRROR = 2,
    rwTEXTUREADDRESSCLAMP = 3,
    rwTEXTUREADDRESSBORDER = 4,
    rwTEXTUREADDRESSMODEFORCEENUMSIZEINT = 2147483647,
} RwTextureAddressMode;
typedef enum RwTextureStreamFlags {
    rwNATEXTURESTREAMFLAG = 0,
    rwTEXTURESTREAMFLAGSUSERMIPMAPS = 1,
    rwTEXTURESTREAMFLAGSFORCEENUMSIZEINT = 2147483647,
} RwTextureStreamFlags;
typedef enum RwVideoModeFlag {
    rwVIDEOMODEEXCLUSIVE = 1,
    rwVIDEOMODEINTERLACE = 2,
    rwVIDEOMODEFFINTERLACE = 4,
    rwVIDEOMODE_PS2_FSAASHRINKBLIT = 256,
    rwVIDEOMODE_PS2_FSAAREADCIRCUIT = 512,
    rwVIDEOMODE_XBOX_WIDESCREEN = 256,
    rwVIDEOMODE_XBOX_PROGRESSIVE = 512,
    rwVIDEOMODE_XBOX_FIELD = 1024,
    rwVIDEOMODE_XBOX_10X11PIXELASPECT = 2048,
    rwVIDEOMODEFLAGFORCEENUMSIZEINT = 2147483647,
} RwVideoModeFlag;
typedef enum RxClusterForcePresent {
    rxCLALLOWABSENT = 0,
    rxCLFORCEPRESENT = 1,
    rxCLUSTERFORCEPRESENTFORCEENUMSIZEINT = 2147483647,
} RxClusterForcePresent;
typedef enum RxClusterValid {
    rxCLVALID_NOCHANGE = 0,
    rxCLVALID_VALID = 1,
    rxCLVALID_INVALID = 2,
    rxCLUSTERVALIDFORCEENUMSIZEINT = 2147483647,
} RxClusterValid;
typedef enum RxClusterValidityReq {
    rxCLREQ_DONTWANT = 0,
    rxCLREQ_REQUIRED = 1,
    rxCLREQ_OPTIONAL = 2,
    rxCLUSTERVALIDITYREQFORCEENUMSIZEINT = 2147483647,
} RxClusterValidityReq;
typedef enum RxInstanceFlags {
    rxINSTANCENAINSTANCEFLAG = 0,
    rxINSTANCEDONTINSTANCE = 1,
    rxINSTANCEINPLACEINSTANCE = 2,
    rxINSTANCECONGRUENTINSTANCE = 4,
    rxINSTANCEFULLINSTANCE = 8,
    rxINSTANCETYPEMASK = 14,
    rxINSTANCEXYZ = 16,
    rxINSTANCENORMAL = 32,
    rxINSTANCERGBA = 64,
    rxINSTANCEUV = 128,
    rxINSTANCEUV1 = 128,
    rxINSTANCEUV2 = 256,
    rxINSTANCEUV3 = 512,
    rxINSTANCEUV4 = 1024,
    rxINSTANCEUV5 = 2048,
    rxINSTANCEUV6 = 4096,
    rxINSTANCEUV7 = 8192,
    rxINSTANCEUV8 = 16384,
    rxINSTANCEUSER1 = 32768,
    rxINSTANCEUSER2 = 65536,
    rxINSTANCEUSER3 = 131072,
    rxINSTANCEUSER4 = 262144,
    rxINSTANCEALL = 524272,
    rxINSTANCEMASK = 524287,
    rxINSTANCEFORCEENUMSIZEINT = 2147483647,
} RxInstanceFlags;
typedef enum RxNodeDefEditable {
    rxNODEDEFCONST = 0,
    rxNODEDEFEDITABLE = 1,
    rxNODEDEFEDITABLEFORCEENUMSIZEINT = 2147483647,
} RxNodeDefEditable;
typedef enum RxPipelineNodePS2AllCallBackType {
    rxPS2ALLCALLBACKNACALLBACK = 0,
    rxPS2ALLCALLBACKOBJECTSETUP = 1,
    rxPS2ALLCALLBACKOBJECTFINALIZE = 2,
    rxPS2ALLCALLBACKFORCEENUMSIZEINT = 2147483647,
} RxPipelineNodePS2AllCallBackType;
typedef enum RxPipelineNodePS2AllMatCallBackType {
    rxPS2ALLMATCALLBACKNACALLBACK = 0,
    rxPS2ALLMATCALLBACKMESHINSTANCETEST = 1,
    rxPS2ALLMATCALLBACKRESENTRYALLOC = 2,
    rxPS2ALLMATCALLBACKINSTANCE = 3,
    rxPS2ALLMATCALLBACKBRIDGE = 4,
    rxPS2ALLMATCALLBACKPOSTMESH = 5,
    rxPS2ALLMATCALLBACKFORCEENUMSIZEINT = 2147483647,
} RxPipelineNodePS2AllMatCallBackType;
typedef enum WorldProgress {
    eWorldProgress_Day1 = 0,
    eWorldProgress_Day2 = 1,
    eWorldProgress_Day3 = 2,
    eWorldProgress_Day4 = 3,
    eWorldProgress_Day5 = 4,
    eWorldProgress_Day6 = 5,
    eWorldProgress_Day7 = 6,
} WorldProgress;
typedef enum rt2dLinetype {
    rt2dMOVE = 0,
    rt2dLINE = 1,
    rt2dCURVE = 2,
    rt2DLINETYPEFORCEENUMSIZEINT = 2147483647,
} rt2dLinetype;
typedef enum rwImageAlphaType {
    rwIMAGEALPHA_OPAQUE = 1,
    rwIMAGEALPHA_MASKED = 2,
    rwIMAGEALPHA_SMOOTH = 3,
    rwIMAGEALPHATYPEFORCEENUMSIZEINT = 2147483647,
} rwImageAlphaType;
typedef enum rwResHeapBlockFlags {
    rwRESHEAP_BLOCKUSED = 1,
    rwRESHEAPFLAGFORCEENUMSIZEINT = 2147483647,
} rwResHeapBlockFlags;
typedef enum rxEmbeddedPacketState {
    rxPKST_PACKETLESS = 0,
    rxPKST_UNUSED = 1,
    rxPKST_INUSE = 2,
    rxPKST_PENDING = 3,
    rxEMBEDDEDPACKETSTATEFORCEENUMSIZEINT = 2147483647,
} rxEmbeddedPacketState;

// 76 bytes
typedef struct ClumpCallbackData
{
    s32 numClumps;         // 0x00
    s32 currentClump;      // 0x04
    s32 playerNumber;      // 0x08
    RpClump** ppClump[16]; // 0x0c
} ClumpCallbackData;

// 16 bytes
typedef struct DMorphTargetBinary
{
    u32 flags;           // 0x00
    u32 lockFlags;       // 0x04
    u32 numCodeElements; // 0x08
    u32 numDataElements; // 0x0c
} DMorphTargetBinary;

// 4 bytes
typedef struct MatFXAtomicData
{
    s32 enabled; // 0x00
} MatFXAtomicData;

typedef struct RwTexture RwTexture;
// 20 bytes
typedef struct MatFXBumpMapData
{
    RwFrame* frame;         // 0x00
    RwTexture* texture;     // 0x04
    RwTexture* bumpTexture; // 0x08
    f32 coef;               // 0x0c
    f32 invBumpWidth;       // 0x10
} MatFXBumpMapData;

// 16 bytes
typedef struct MatFXDualData
{
    RwTexture* texture;           // 0x00
    RwBlendFunction srcBlendMode; // 0x04
    RwBlendFunction dstBlendMode; // 0x08
    void* padAlign;               // 0x0c
} MatFXDualData;

// 16 bytes
typedef struct MatFXEnvMapData
{
    RwFrame* frame;          // 0x00
    RwTexture* texture;      // 0x04
    f32 coef;                // 0x08
    s32 useFrameBufferAlpha; // 0x0c
} MatFXEnvMapData;

typedef struct RwMatrixTag RwMatrixTag;
// 8 bytes
typedef struct MatFXUVAnimData
{
    RwMatrixTag* baseTransform; // 0x00
    RwMatrixTag* dualTransform; // 0x04
} MatFXUVAnimData;

// 32 bytes
typedef union MatFXEffectUnion
{
    MatFXBumpMapData bumpMap; // 0x00
    MatFXEnvMapData envMap;   // 0x00
    MatFXDualData dual;       // 0x00
    MatFXUVAnimData uvAnim;   // 0x00
} MatFXEffectUnion;

// 24 bytes
typedef struct MatFXSkyMaterial
{
    u64 alpha;  // 0x00
    u64 fogcol; // 0x08
    u64 test;   // 0x10
} MatFXSkyMaterial;

// 64 bytes
typedef struct MatFXEffectData
{
    MatFXEffectUnion data;     // 0x00
    RpMatFXMaterialFlags flag; // 0x20
    MatFXSkyMaterial skyMat;   // 0x28
} MatFXEffectData;

// 4 bytes
typedef struct MatFXWorldSectorData
{
    s32 enabled; // 0x00
} MatFXWorldSectorData;

// 12 bytes
typedef struct RpADCDataTag
{
    s32 adcFormatted; // 0x00
    s8* adcBits;      // 0x04
    s32 numBits;      // 0x08
} RpADCDataTag;

// 20 bytes
typedef struct RpInterpolator
{
    s32 flags;            // 0x00
    s16 startMorphTarget; // 0x04
    s16 endMorphTarget;   // 0x06
    f32 time;             // 0x08
    f32 recipTime;        // 0x0c
    f32 position;         // 0x10
} RpInterpolator;

// 16 bytes
struct RwSphere
{
    RwV3d center; // 0x00
    f32 radius;   // 0x0c
};

typedef struct RwResEntry RwResEntry;
typedef struct RpGeometry RpGeometry;
typedef struct RpAtomic RpAtomic;
typedef struct RxPipeline RxPipeline;
// 112 bytes
struct RpAtomic
{
    RwObjectHasFrame object;           // 0x00
    RwResEntry* repEntry;              // 0x14
    RpGeometry* geometry;              // 0x18
    RwSphere boundingSphere;           // 0x1c
    RwSphere worldBoundingSphere;      // 0x2c
    RpClump* clump;                    // 0x3c
    RwLLLink inClumpLink;              // 0x40
    RpAtomic** renderCallBack;         // 0x48
    RpInterpolator interpolator;       // 0x4c
    u16 renderFrame;                   // 0x60
    u16 pad;                           // 0x62
    RwLinkList llWorldSectorsInAtomic; // 0x64
    RxPipeline* pipeline;              // 0x6c
};

typedef struct RpBuildMeshTriangle RpBuildMeshTriangle;
// 12 bytes
typedef struct RpBuildMesh
{
    u32 triangleBufferSize;             // 0x00
    u32 numTriangles;                   // 0x04
    RpBuildMeshTriangle* meshTriangles; // 0x08
} RpBuildMesh;

// 20 bytes
struct RpBuildMeshTriangle
{
    u16 vertIndex[3];     // 0x00
    RpMaterial* material; // 0x08
    u16 matIndex;         // 0x0c
    u16 textureIndex;     // 0x0e
    u16 rasterIndex;      // 0x10
    u16 pipelineIndex;    // 0x12
};

// 12 bytes
typedef struct RpClumpCameraExt
{
    RpClump* clump;       // 0x00
    RwLLLink inClumpLink; // 0x04
} RpClumpCameraExt;

// 12 bytes
typedef struct RpClumpChunkInfo
{
    s32 numAtomics; // 0x00
    s32 numLights;  // 0x04
    s32 numCameras; // 0x08
} RpClumpChunkInfo;

// 12 bytes
typedef struct RpClumpCloneStatus
{
    RpClump* oldClump; // 0x00
    RpClump* newClump; // 0x04
    s32 success;       // 0x08
} RpClumpCloneStatus;

// 12 bytes
typedef struct RpClumpLightExt
{
    RpClump* clump;       // 0x00
    RwLLLink inClumpLink; // 0x04
} RpClumpLightExt;

// 8 bytes
typedef struct rpGeometryList
{
    RpGeometry** geometries; // 0x00
    s32 numGeoms;            // 0x04
} rpGeometryList;

// 8 bytes
typedef struct rwFrameList
{
    RwFrame** frames; // 0x00
    s32 numFrames;    // 0x04
} rwFrameList;

// 24 bytes
typedef struct RpClumpStreamWriteStatus
{
    RwStream* stream;  // 0x00
    rwFrameList fl;    // 0x04
    rpGeometryList gl; // 0x0c
    s32 success;       // 0x14
} RpClumpStreamWriteStatus;

typedef struct RpDMorphAnimation
{
} RpDMorphAnimation;

// 16 bytes
typedef struct rpDMorphRLE
{
    u8* code;            // 0x00
    u32 numCodeElements; // 0x04
    u32 numDataElements; // 0x08
    void* data;          // 0x0c
} rpDMorphRLE;

typedef struct RwTexCoords RwTexCoords;
// 64 bytes
typedef struct RpDMorphTarget
{
    RpGeometry* geometry;    // 0x00
    char* name;              // 0x04
    u32 flags;               // 0x08
    u32 lockFlags;           // 0x0c
    rpDMorphRLE rle;         // 0x10
    RwV3d* vertices;         // 0x20
    RwV3d* normals;          // 0x24
    RwRGBA* preLightColors;  // 0x28
    RwTexCoords* texCoords;  // 0x2c
    RwSphere boundingSphere; // 0x30
} RpDMorphTarget;

// 12 bytes
typedef struct RpMaterialList
{
    RpMaterial** materials; // 0x00
    s32 numMaterials;       // 0x04
    s32 space;              // 0x08
} RpMaterialList;

typedef struct RpTriangle RpTriangle;
typedef struct RpMeshHeader RpMeshHeader;
typedef struct RpMorphTarget RpMorphTarget;
// 96 bytes
struct RpGeometry
{
    RwObject object;            // 0x00
    u32 flags;                  // 0x08
    u16 lockedSinceLastInst;    // 0x0c
    s16 refCount;               // 0x0e
    s32 numTriangles;           // 0x10
    s32 numVertices;            // 0x14
    s32 numMorphTargets;        // 0x18
    s32 numTexCoordSets;        // 0x1c
    RpMaterialList matList;     // 0x20
    RpTriangle* triangles;      // 0x2c
    RwRGBA* preLitLum;          // 0x30
    RwTexCoords* texCoords[8];  // 0x34
    RpMeshHeader* mesh;         // 0x54
    RwResEntry* repEntry;       // 0x58
    RpMorphTarget* morphTarget; // 0x5c
};

// 16 bytes
typedef struct RpGeometryChunkInfo
{
    s32 format;          // 0x00
    s32 numTriangles;    // 0x04
    s32 numVertices;     // 0x08
    s32 numMorphTargets; // 0x0c
} RpGeometryChunkInfo;

typedef struct RwFreeList RwFreeList;
// 8 bytes
typedef struct RpHAnimAtomicGlobalVars
{
    s32 engineOffset;          // 0x00
    RwFreeList* HAnimFreeList; // 0x04
} RpHAnimAtomicGlobalVars;

// 8 bytes
typedef struct RpHAnimFrameExtension
{
    s32 id;                      // 0x00
    RpHAnimHierarchy* hierarchy; // 0x04
} RpHAnimFrameExtension;

typedef struct RpHAnimKeyFrame RpHAnimKeyFrame;
// 36 bytes
typedef struct RpHAnimInterpFrame
{
    RpHAnimKeyFrame* keyFrame1; // 0x00
    RpHAnimKeyFrame* keyFrame2; // 0x04
    RtQuat q;                   // 0x08
    RwV3d t;                    // 0x18
} RpHAnimInterpFrame;

// 36 bytes
struct RpHAnimKeyFrame
{
    RpHAnimKeyFrame* prevFrame; // 0x00
    f32 time;                   // 0x04
    RtQuat q;                   // 0x08
    RwV3d t;                    // 0x18
};

// 16 bytes
struct RpHAnimNodeInfo
{
    s32 nodeID;      // 0x00
    s32 nodeIndex;   // 0x04
    s32 flags;       // 0x08
    RwFrame* pFrame; // 0x0c
};

// 24 bytes
typedef struct RwLine
{
    RwV3d start; // 0x00
    RwV3d end;   // 0x0c
} RwLine;

// 24 bytes
typedef union RpIntersectData
{
    RwLine line;     // 0x00
    RwV3d point;     // 0x00
    RwSphere sphere; // 0x00
    RwBBox box;      // 0x00
    void* object;    // 0x00
} RpIntersectData;

// 28 bytes
typedef struct RpIntersection
{
    RpIntersectData t;    // 0x00
    RpIntersectType type; // 0x18
} RpIntersection;

// 24 bytes
typedef struct RpLightChunkInfo
{
    f32 radius;        // 0x00
    f32 red;           // 0x04
    f32 green;         // 0x08
    f32 blue;          // 0x0c
    f32 minusCosAngle; // 0x10
    u32 typeAndFlags;  // 0x14
} RpLightChunkInfo;

typedef struct RpWorldSector RpWorldSector;
// 24 bytes
typedef struct RpLightTie
{
    RwLLLink lightInWorldSector; // 0x00
    RpLight* light;              // 0x08
    RwLLLink WorldSectorInLight; // 0x0c
    RpWorldSector* sect;         // 0x14
} RpLightTie;

// 16 bytes
typedef struct RpListedWorld
{
    RpWorld* world;  // 0x00
    u32 memorySize;  // 0x04
    RwLLLink nextEl; // 0x08
} RpListedWorld;

// 12 bytes
typedef struct RwSurfaceProperties
{
    f32 ambient;  // 0x00
    f32 specular; // 0x04
    f32 diffuse;  // 0x08
} RwSurfaceProperties;

// 28 bytes
struct RpMaterial
{
    RwTexture* texture;               // 0x00
    RwRGBA color;                     // 0x04
    RxPipeline* pipeline;             // 0x08
    RwSurfaceProperties surfaceProps; // 0x0c
    s16 refCount;                     // 0x18
    s16 pad;                          // 0x1a
};

// 28 bytes
typedef struct RpMaterialChunkInfo
{
    s32 flags;                        // 0x00
    RwRGBA color;                     // 0x04
    s32 unused;                       // 0x08
    s32 textured;                     // 0x0c
    RwSurfaceProperties surfaceProps; // 0x10
} RpMaterialChunkInfo;

// 12 bytes
typedef struct RpMesh
{
    u16* indices;         // 0x00
    u32 numIndices;       // 0x04
    RpMaterial* material; // 0x08
} RpMesh;

// 16 bytes
struct RpMeshHeader
{
    u32 flags;              // 0x00
    u16 numMeshes;          // 0x04
    u16 serialNum;          // 0x06
    u32 totalIndicesInMesh; // 0x08
    u32 firstMeshOffset;    // 0x0c
};

// 4 bytes
typedef struct RpMeshStatic
{
    RwFreeList* BuildMeshFreeList; // 0x00
} RpMeshStatic;

// 24 bytes
typedef struct RpMeshopStatic
{
    RpMeshHeader nullMeshHeader;       // 0x00
    RpMeshHeader** meshTristripMethod; // 0x10
    void* data;                        // 0x14
} RpMeshopStatic;

typedef struct RpMorphInterpolator RpMorphInterpolator;
// 12 bytes
typedef struct RpMorphAtomicAnim
{
    RpMorphInterpolator* interp; // 0x00
    f32 position;                // 0x04
    RpGeometry* lastGeom;        // 0x08
} RpMorphAtomicAnim;

// 12 bytes
typedef struct RpMorphGeometryAnim
{
    s32 numInterpolators;            // 0x00
    f32* fpAnimCntrlCB;              // 0x04
    RpMorphInterpolator* allInterps; // 0x08
} RpMorphGeometryAnim;

// 20 bytes
struct RpMorphInterpolator
{
    s32 flags;                 // 0x00
    s16 startMorphTarget;      // 0x04
    s16 endMorphTarget;        // 0x06
    f32 time;                  // 0x08
    f32 recipTime;             // 0x0c
    RpMorphInterpolator* next; // 0x10
};

// 28 bytes
struct RpMorphTarget
{
    RpGeometry* parentGeom;  // 0x00
    RwSphere boundingSphere; // 0x04
    RwV3d* verts;            // 0x14
    RwV3d* normals;          // 0x18
};

typedef struct RpPDSSkyMatTemplate RpPDSSkyMatTemplate;
typedef struct RpPDSSkyObjTemplate RpPDSSkyObjTemplate;
// 4 bytes
typedef struct RpPDSPipeDefinition
{
    void* ptr;                // 0x00
    RpPDSSkyMatTemplate* mat; // 0x00
    RpPDSSkyObjTemplate* obj; // 0x00
} RpPDSPipeDefinition;

// 20 bytes
typedef struct RpPDSRegister
{
    RpPDSPipeDefinition def; // 0x00
    RpPDSPipeID attachId;    // 0x04
    RpPDSPipeID id;          // 0x08
    RpPDSPipeType type;      // 0x0c
    RxPipeline* pipe;        // 0x10
} RpPDSRegister;

typedef struct RxClusterDefinition RxClusterDefinition;
// 8 bytes
typedef struct RpPDSSkyMatCluster
{
    RxClusterDefinition* definition; // 0x00
    u32 type;                        // 0x04
} RpPDSSkyMatCluster;

// 20 bytes
typedef struct RpPDSSkyMatPrimitive
{
    RwPrimitiveType type; // 0x00
    s32 clusterStride;    // 0x04
    s32 vertexCount;      // 0x08
    s32 primCount;        // 0x0c
    s32 vifOffset;        // 0x10
} RpPDSSkyMatPrimitive;

typedef struct RpPDSSkyVU1CodeTemplate RpPDSSkyVU1CodeTemplate;
// 132 bytes
struct RpPDSSkyMatTemplate
{
    u32 pluginId;                       // 0x00
    u32 pluginData;                     // 0x04
    RpPDSSkyMatCluster clusters[10];    // 0x08
    RpPDSSkyMatPrimitive primitive;     // 0x58
    RpPDSSkyVU1CodeTemplate* vu1code;   // 0x6c
    s32* meshInstanceTestCallBack;      // 0x70
    RwResEntry** resEntryAllocCallBack; // 0x74
    s32* instanceCallBack;              // 0x78
    s32* bridgeCallBack;                // 0x7c
    s32* postMeshCallBack;              // 0x80
};

// 20 bytes
struct RpPDSSkyObjTemplate
{
    u32 pluginId;                // 0x00
    u32 pluginData;              // 0x04
    s32* objectSetupCallBack;    // 0x08
    s32* objectFinalizeCallBack; // 0x0c
    RxPipeline* matGroup;        // 0x10
};

// 8 bytes
struct RpPDSSkyVU1CodeTemplate
{
    void** array; // 0x00
    u32 slots;    // 0x04
};

// 16 bytes
typedef struct RpPatternTex
{
    RwTexture** Pattern; // 0x00
    s32 nPattern;        // 0x04
    s32 Num;             // 0x08
    s32 Dummy;           // 0x0c
} RpPatternTex;

typedef struct RpSector RpSector;
// 24 bytes
typedef struct RpPlaneSector
{
    s32 type;               // 0x00
    f32 value;              // 0x04
    RpSector* leftSubTree;  // 0x08
    RpSector* rightSubTree; // 0x0c
    f32 leftValue;          // 0x10
    f32 rightValue;         // 0x14
} RpPlaneSector;

// 24 bytes
typedef struct RpPlaneSectorChunkInfo
{
    s32 type;               // 0x00
    f32 value;              // 0x04
    s32 leftIsWorldSector;  // 0x08
    s32 rightIsWorldSector; // 0x0c
    f32 leftValue;          // 0x10
    f32 rightValue;         // 0x14
} RpPlaneSectorChunkInfo;

// 8 bytes
typedef struct RpPolygon
{
    u16 matIndex;     // 0x00
    u16 vertIndex[3]; // 0x02
} RpPolygon;

// 20 bytes
typedef struct RpPrjTexParam
{
    u32 numTexture;        // 0x00
    RwTexture* Texture[3]; // 0x04
    char* Name;            // 0x10
} RpPrjTexParam;

typedef struct RpPrtAdvEmtPrtTexCoordsItem RpPrtAdvEmtPrtTexCoordsItem;
// 28 bytes
typedef struct RpPrtAdvEmtPrtMultiTexCoords
{
    u32 numTex;                        // 0x00
    RpPrtAdvEmtPrtTexCoordsItem* list; // 0x04
    u32 offsetTime;                    // 0x08
    u32 offsetStartUV0;                // 0x0c
    u32 offsetDeltaUV0;                // 0x10
    u32 offsetStartUV1;                // 0x14
    u32 offsetDeltaUV1;                // 0x18
} RpPrtAdvEmtPrtMultiTexCoords;

// 8 bytes
struct RwTexCoords
{
    f32 u; // 0x00
    f32 v; // 0x04
};

// 40 bytes
struct RpPrtAdvEmtPrtTexCoordsItem
{
    f32 time;               // 0x00
    f32 timeBias;           // 0x04
    RwTexCoords midUV0;     // 0x08
    RwTexCoords midUV0Bias; // 0x10
    RwTexCoords midUV1;     // 0x18
    RwTexCoords midUV1Bias; // 0x20
};

typedef struct RpPrtStdEmitter RpPrtStdEmitter;
typedef struct RpPrtStdEmitterClass RpPrtStdEmitterClass;
typedef struct RpPrtStdParticleClass RpPrtStdParticleClass;
typedef struct RpPrtStdParticleBatch RpPrtStdParticleBatch;
// 40 bytes
struct RpPrtStdEmitter
{
    RpPrtStdEmitter* next;                // 0x00
    u32 flag;                             // 0x04
    RpAtomic* atomic;                     // 0x08
    RpPrtStdEmitterClass* emtClass;       // 0x0c
    s32 prtActive;                        // 0x10
    s32 prtBatchMaxPrt;                   // 0x14
    RpPrtStdParticleClass* prtClass;      // 0x18
    RpPrtStdParticleBatch* inactiveBatch; // 0x1c
    RpPrtStdParticleBatch* activeBatch;   // 0x20
    f32 boundingSphere;                   // 0x24
};

typedef struct RpPrtStdPropertyTable RpPrtStdPropertyTable;
// 28 bytes
struct RpPrtStdEmitterClass
{
    RpPrtStdEmitterClass* next;     // 0x00
    s32 id;                         // 0x04
    s32 refCount;                   // 0x08
    s32 objSize;                    // 0x0c
    RpPrtStdPropertyTable* propTab; // 0x10
    s32 numCallback;                // 0x14
    void* callback;                 // 0x18
};

// 52 bytes
typedef struct RpPrtStdEmitterPTank
{
    u32 dataFlags;      // 0x00
    u32 platFlags;      // 0x04
    u32 numPrt;         // 0x08
    u32 maxPrt;         // 0x0c
    u32 updateFlags;    // 0x10
    u32 emitFlags;      // 0x14
    RpAtomic* pTank;    // 0x18
    char** dataInPtrs;  // 0x1c
    char** dataOutPtrs; // 0x20
    s32* dataStride;    // 0x24
    u32 strSrcBlend;    // 0x28
    u32 strDstBlend;    // 0x2c
    s32 strVtxABlend;   // 0x30
} RpPrtStdEmitterPTank;

// 16 bytes
typedef struct RpPrtStdEmitterPrt2DRotate
{
    f32 prtStart2DRotate;     // 0x00
    f32 prtStart2DRotateBias; // 0x04
    f32 prtEnd2DRotate;       // 0x08
    f32 prtEnd2DRotateBias;   // 0x0c
} RpPrtStdEmitterPrt2DRotate;

// 172 bytes
typedef struct RpPrtStdEmitterStandard
{
    s32 seed;             // 0x00
    s32 maxPrt;           // 0x04
    f32 currTime;         // 0x08
    f32 prevTime;         // 0x0c
    RwV3d force;          // 0x10
    RwV3d emtPos;         // 0x1c
    RwV3d emtSize;        // 0x28
    f32 emtEmitGap;       // 0x34
    f32 emtEmitGapBias;   // 0x38
    f32 emtPrevEmitTime;  // 0x3c
    f32 emtEmitTime;      // 0x40
    s32 emtPrtEmit;       // 0x44
    s32 emtPrtEmitBias;   // 0x48
    f32 prtInitVel;       // 0x4c
    f32 prtInitVelBias;   // 0x50
    f32 prtLife;          // 0x54
    f32 prtLifeBias;      // 0x58
    RwV3d prtInitDir;     // 0x5c
    RwV3d prtInitDirBias; // 0x68
    RwV2d prtSize;        // 0x74
    RwRGBA prtColor;      // 0x7c
    f32 prtDelta2DRotate; // 0x80
    RwTexCoords prtUV[4]; // 0x84
    RwTexture* texture;   // 0xa4
    RwMatrixTag* ltm;     // 0xa8
} RpPrtStdEmitterStandard;

// 24 bytes
struct RpPrtStdParticleBatch
{
    RpPrtStdParticleBatch* next;     // 0x00
    RpPrtStdParticleClass* prtClass; // 0x04
    s32 numPrt;                      // 0x08
    s32 maxPrt;                      // 0x0c
    s32 newPrt;                      // 0x10
    s32 offset;                      // 0x14
};

// 28 bytes
struct RpPrtStdParticleClass
{
    RpPrtStdParticleClass* next;    // 0x00
    s32 id;                         // 0x04
    s32 refCount;                   // 0x08
    s32 objSize;                    // 0x0c
    RpPrtStdPropertyTable* propTab; // 0x10
    s32 numCallback;                // 0x14
    void* callback;                 // 0x18
};

// 40 bytes
struct RpPrtStdPropertyTable
{
    u32* propPtr;                // 0x00
    RpPrtStdPropertyTable* next; // 0x04
    s32 id;                      // 0x08
    s32 refCount;                // 0x0c
    s32 numProp;                 // 0x10
    s32 maxProp;                 // 0x14
    s32* propID;                 // 0x18
    s32* propOffset;             // 0x1c
    s32* propSize;               // 0x20
    s32* propSizeUA;             // 0x24
};

// 4 bytes
struct RpSector
{
    s32 type; // 0x00
};

// 28 bytes
typedef struct RpShadow
{
    RwCamera* Camera; // 0x00
    RpWorld* World;   // 0x04
    RpLight* Light;   // 0x08
    RwRGBA BgColor;   // 0x0c
    RwV3d Pos;        // 0x10
} RpShadow;

// 28 bytes
typedef struct RpShadowParam
{
    RwV3d CamPos;     // 0x00
    RwV2d ViewWindow; // 0x0c
    s32 Size;         // 0x14
    RwRGBA BgColor;   // 0x18
} RpShadowParam;

typedef struct RpSkin
{
} RpSkin;

// 68 bytes
typedef struct RpSpline
{
    RwObject tType;    // 0x00
    s32 numCtrlPoints; // 0x08
    s32 nSplineType;   // 0x0c
    void* pUser;       // 0x10
    RwV3d* ctrlPoints; // 0x14
    char caName[32];   // 0x18
    RwV3d vPts[1];     // 0x38
} RpSpline;

// 8 bytes
typedef struct RpTeamFrustumTest
{
    RwFrustumTestResult* callBack; // 0x00
    void* data;                    // 0x04
} RpTeamFrustumTest;

// 20 bytes
typedef struct RpTeamLOD
{
    RwCamera* camera; // 0x00
    f32 farRange;     // 0x04
    f32 invFarRange;  // 0x08
    u32* callBack;    // 0x0c
    void* data;       // 0x10
} RpTeamLOD;

// 4 bytes
typedef struct RpTeamOptPatch
{
    s32 optimized; // 0x00
} RpTeamOptPatch;

typedef struct RpTeamOptElement RpTeamOptElement;
// 16 bytes
typedef struct RpTeamOptSkin
{
    s32 optimized;          // 0x00
    u32 numElements;        // 0x04
    RpTeamOptElement* data; // 0x08
    RpSkin* firstSkin;      // 0x0c
} RpTeamOptSkin;

// 12 bytes
typedef struct RpTeamOptStatic
{
    s32 optimized;          // 0x00
    u32 numElements;        // 0x04
    RpTeamOptElement* data; // 0x08
} RpTeamOptStatic;

// 36 bytes
typedef struct RpTeamOptElements
{
    s32 optimized;        // 0x00
    RpTeamOptStatic stat; // 0x04
    RpTeamOptSkin skin;   // 0x10
    RpTeamOptPatch patch; // 0x20
} RpTeamOptElements;

// 12 bytes
typedef struct RpTeamPlayerData
{
    u32 numOfPlayerElements; // 0x00
    u32 numOfPlayers;        // 0x04
    s32 optimized;           // 0x08
} RpTeamPlayerData;

// 16 bytes
typedef struct SkinCyclicCache
{
    void* unaligned;          // 0x00
    RwMatrixTag* matrixCache; // 0x04
    u32 maxMatrices;          // 0x08
    u32 nextMatrices;         // 0x0c
} SkinCyclicCache;

typedef struct RpTeamDictionary RpTeamDictionary;
typedef struct RpTeamPlayer RpTeamPlayer;
typedef struct RpTeamShadows RpTeamShadows;
// 148 bytes
typedef struct RpTeam
{
    RwLLLink list;                 // 0x00
    u32 lockFlags;                 // 0x08
    RpTeamPlayerData data;         // 0x0c
    RpTeamOptElements opData;      // 0x18
    RpTeamLOD lod;                 // 0x3c
    RpTeamDictionary* dictionary;  // 0x50
    u32* selected;                 // 0x54
    RpTeamPlayer* players;         // 0x58
    RpTeamShadows* shadows;        // 0x5c
    SkinCyclicCache cyclicCache;   // 0x60
    RpTeamFrustumTest frustumTest; // 0x70
    RpLight* lights[6];            // 0x78
    RpTeamLightType lightType;     // 0x90
} RpTeam;

typedef struct RpTeamDictionaryElement RpTeamDictionaryElement;
// 12 bytes
struct RpTeamDictionary
{
    u32 numOfElements;                 // 0x00
    RpTeamDictionaryElement* elements; // 0x04
    u32* map;                          // 0x08
};

// 36 bytes
struct RpTeamDictionaryElement
{
    RpAtomic* element[7];   // 0x00
    RpTeamElementType type; // 0x1c
    u32 refCount;           // 0x20
};

typedef struct RpTeamRenderStatic RpTeamRenderStatic;
typedef struct RpTeamRenderSkin RpTeamRenderSkin;
// 16 bytes
struct RpTeamOptElement
{
    u32 numClones;                    // 0x00
    u32 stack;                        // 0x04
    void* lodAtomic;                  // 0x08
    RpTeamRenderStatic* staticRender; // 0x0c
    RpTeamRenderSkin* skinRender;     // 0x0c
};

// 8 bytes
typedef struct RpTeamPlayerLOD
{
    u32 currentLOD;      // 0x00
    s32 syncLODPerFrame; // 0x04
} RpTeamPlayerLOD;

// 8 bytes
struct RpTeamRenderSkin
{
    RpTeamPlayer* player; // 0x00
    u32 transType;        // 0x04
};

// 48 bytes
struct RpTeamShadows
{
    RwFrame* shadowFrames[4];   // 0x00
    f32 shadowValues[4];        // 0x10
    RwFrame* shadowPlane;       // 0x20
    u32 number;                 // 0x24
    RpTeamElementLOD shadowLOD; // 0x28
};

// 20 bytes
typedef struct RpTeamSkyGlobals
{
    u32 currentLOD;           // 0x00
    RpTeamOptElement* opData; // 0x04
    u32 numOfClones;          // 0x08
    s32 skinning;             // 0x0c
    RpTeam* currentTeam;      // 0x10
} RpTeamSkyGlobals;

// 24 bytes
typedef struct RpTie
{
    RwLLLink lAtomicInWorldSector; // 0x00
    RpAtomic* apAtom;              // 0x08
    RwLLLink lWorldSectorInAtomic; // 0x0c
    RpWorldSector* worldSector;    // 0x14
} RpTie;

typedef struct RpTriStripMesh RpTriStripMesh;
// 12 bytes
typedef struct RpTriStripData
{
    s32 ignoreWinding;        // 0x00
    RpTriStripMesh** stripCB; // 0x04
    void* data;               // 0x08
} RpTriStripData;

typedef struct RpTriStripPolygon RpTriStripPolygon;
// 32 bytes
typedef struct RpTriStripEdge
{
    RwLLLink inUsedLink;      // 0x00
    RwLLLink inFreeLink;      // 0x08
    RpTriStripPolygon* poly1; // 0x10
    RpTriStripPolygon* poly2; // 0x14
    u16 vert1;                // 0x18
    u16 vert2;                // 0x1a
    s32 strip;                // 0x1c
} RpTriStripEdge;

// 44 bytes
struct RpTriStripMesh
{
    u32 numPolygons;            // 0x00
    RwLinkList polygonEndList;  // 0x04
    RwLinkList polygonUsedList; // 0x0c
    RwLinkList polygonFreeList; // 0x14
    RwLinkList edgeUsedList;    // 0x1c
    RwLinkList edgeFreeList;    // 0x24
};

// 52 bytes
struct RpTriStripPolygon
{
    RwLLLink inEndLink;       // 0x00
    RwLLLink inUsedLink;      // 0x08
    RwLLLink inFreeLink;      // 0x10
    u32 numEdges;             // 0x18
    RpTriStripEdge* edges[3]; // 0x1c
    u16 vertIndex[3];         // 0x28
    u32 testFrame;            // 0x30
};

// 16 bytes
typedef struct RpTriStripTunnel
{
    u32 length;                   // 0x00
    u32 maxLength;                // 0x04
    RpTriStripEdge** edges;       // 0x08
    RpTriStripPolygon** polygons; // 0x0c
} RpTriStripTunnel;

// 16 bytes
typedef struct RpTriStripTunnelData
{
    f32 quality;     // 0x00
    u32 lengthLimit; // 0x04
    u32* costCB;     // 0x08
    void* data;      // 0x0c
} RpTriStripTunnelData;

// 8 bytes
struct RpTriangle
{
    u16 vertIndex[3]; // 0x00
    s16 matIndex;     // 0x06
};

// 12 bytes
typedef struct RpUVAnimAnimation
{
    RtAnimAnimation* pAnim;       // 0x00
    RtAnimInterpolator* instance; // 0x04
    s32 type;                     // 0x08
} RpUVAnimAnimation;

// 8 bytes
typedef struct RpUserDataList
{
    s32 numElements;           // 0x00
    RpUserDataArray* userData; // 0x04
} RpUserDataList;

// 4 bytes
typedef struct RpVertexNormal
{
    s8 x;   // 0x00
    s8 y;   // 0x01
    s8 z;   // 0x02
    u8 pad; // 0x03
} RpVertexNormal;

// 112 bytes
struct RpWorld
{
    RwObject object;                 // 0x00
    u32 flags;                       // 0x08
    RpWorldRenderOrder renderOrder;  // 0x0c
    RpMaterialList matList;          // 0x10
    RpSector* rootSector;            // 0x1c
    s32 numTexCoordSets;             // 0x20
    s32 numClumpsInWorld;            // 0x24
    RwLLLink* currentClumpLink;      // 0x28
    RwLinkList clumpList;            // 0x2c
    RwLinkList lightList;            // 0x34
    RwLinkList directionalLightList; // 0x3c
    RwV3d worldOrigin;               // 0x44
    RwBBox boundingBox;              // 0x50
    RpWorldSector** renderCallBack;  // 0x68
    RxPipeline* pipeline;            // 0x6c
};

// 8 bytes
typedef struct RpWorldAtomicExt
{
    RpWorld* world;             // 0x00
    RwObjectHasFrame** oldSync; // 0x04
} RpWorldAtomicExt;

// 28 bytes
typedef struct RpWorldCameraExt
{
    RpWorldSector** frustumSectors; // 0x00
    s32 space;                      // 0x04
    s32 position;                   // 0x08
    RpWorld* world;                 // 0x0c
    RwCamera** oldBeginUpdate;      // 0x10
    RwCamera** oldEndUpdate;        // 0x14
    RwObjectHasFrame** oldSync;     // 0x18
} RpWorldCameraExt;

// 64 bytes
typedef struct RpWorldChunkInfo
{
    s32 rootIsWorldSector; // 0x00
    RwV3d invWorldOrigin;  // 0x04
    s32 numTriangles;      // 0x10
    s32 numVertices;       // 0x14
    s32 numPlaneSectors;   // 0x18
    s32 numWorldSectors;   // 0x1c
    s32 colSectorSize;     // 0x20
    s32 format;            // 0x24
    RwBBox boundingBox;    // 0x28
} RpWorldChunkInfo;

// 44 bytes
typedef struct RpWorldChunkInfoSector
{
    s32 matListWindowBase; // 0x00
    s32 numTriangles;      // 0x04
    s32 numVertices;       // 0x08
    RwV3d inf;             // 0x0c
    RwV3d sup;             // 0x18
    s32 collSectorPresent; // 0x24
    s32 unused;            // 0x28
} RpWorldChunkInfoSector;

// 8 bytes
typedef struct RpWorldClumpExt
{
    RpWorld* world;        // 0x00
    u32 clumpsInFrustumID; // 0x04
} RpWorldClumpExt;

// 8 bytes
typedef struct RpWorldLightExt
{
    RpWorld* world;             // 0x00
    RwObjectHasFrame** oldSync; // 0x04
} RpWorldLightExt;

// 144 bytes
struct RpWorldSector
{
    s32 type;                              // 0x00
    RpPolygon* polygons;                   // 0x04
    RwV3d* vertices;                       // 0x08
    RpVertexNormal* normals;               // 0x0c
    RwTexCoords* texCoords[8];             // 0x10
    RwRGBA* preLitLum;                     // 0x30
    RwResEntry* repEntry;                  // 0x34
    RwLinkList collAtomicsInWorldSector;   // 0x38
    RwLinkList noCollAtomicsInWorldSector; // 0x40
    RwLinkList lightsInWorldSector;        // 0x48
    RwBBox boundingBox;                    // 0x50
    RwBBox tightBoundingBox;               // 0x68
    RpMeshHeader* mesh;                    // 0x80
    RxPipeline* pipeline;                  // 0x84
    u16 matListWindowBase;                 // 0x88
    u16 numVertices;                       // 0x8a
    u16 numPolygons;                       // 0x8c
    u16 pad;                               // 0x8e
};

// 16 bytes
typedef struct Rt2dBBox
{
    f32 x; // 0x00
    f32 y; // 0x04
    f32 w; // 0x08
    f32 h; // 0x0c
} Rt2dBBox;

// 24 bytes
typedef struct rt2dShadeParameters
{
    RwRGBAReal col; // 0x00
    RwV2d uv;       // 0x10
} rt2dShadeParameters;

// 120 bytes
typedef struct Rt2dBrush
{
    rt2dShadeParameters top;     // 0x00
    rt2dShadeParameters dtop;    // 0x18
    rt2dShadeParameters bottom;  // 0x30
    rt2dShadeParameters dbottom; // 0x48
    RwRGBA colorCache;           // 0x60
    s32 flag;                    // 0x64
    RwTexture* texture;          // 0x68
    RpMaterial* material;        // 0x6c
    f32 halfwidth;               // 0x70
    s32 refCount;                // 0x74
} Rt2dBrush;

typedef struct RwSList RwSList;
typedef struct Rt2dFont Rt2dFont;
// 324 bytes
struct Rt2dFont
{
    s32 isOutline;          // 0x00
    f32 height;             // 0x04
    f32 baseline;           // 0x08
    f32 intergap;           // 0x0c
    u32 flag;               // 0x10
    RwTexture* textures[4]; // 0x14
    s16 aCharIndex[128];    // 0x24
    s32 uCharOffset;        // 0x124
    s32 uCharIndexCount;    // 0x128
    s16* uCharIndex;        // 0x12c
    s32 charCount;          // 0x130
    RwSList* charMap;       // 0x134
    Rt2dFont** fontshowCB;  // 0x138
    Rt2dFont* nextBatch;    // 0x13c
    void* strCache;         // 0x140
};

// 1032 bytes
typedef struct Rt2dStrBuffer
{
    s32 space;       // 0x00
    u8* str;         // 0x04
    u8 buffer[1024]; // 0x08
} Rt2dStrBuffer;

// 16 bytes
struct RxClusterDefinition
{
    char* name;            // 0x00
    u32 defaultStride;     // 0x04
    u32 defaultAttributes; // 0x08
    char* attributeSet;    // 0x0c
};

// 8 bytes
typedef struct _rt2dTriIndex
{
    s32 currIdx; // 0x00
    s32* idx;    // 0x04
} _rt2dTriIndex;

typedef struct _rt2dFontDictionaryNode _rt2dFontDictionaryNode;
typedef struct RwTexDictionary RwTexDictionary;
typedef struct Rt2dPath Rt2dPath;
typedef struct rt2dPathNode rt2dPathNode;
// 4400 bytes
typedef struct Rt2dGlobalVars
{
    u16 topo[256];                           // 0x00
    u16 fonttopo[384];                       // 0x200
    RwFreeList* brushFreeList;               // 0x500
    RxObjSpace3DVertex* brushVertexCache;    // 0x504
    RwFreeList* fontFreeList;                // 0x508
    char* fontPath;                          // 0x50c
    u32 fontPathSize;                        // 0x510
    RwFreeList* fontDictNodeFreeList;        // 0x514
    _rt2dFontDictionaryNode* fontDictionary; // 0x518
    RwTexDictionary* fontTexDictionary;      // 0x51c
    RwTexDictionary* currFontTexDictionary;  // 0x520
    RwFreeList* pathFreeList;                // 0x524
    Rt2dPath* scratch;                       // 0x528
    RwFreeList* objectFreeList;              // 0x52c
    RwFreeList* fillFreeList;                // 0x530
    RwFreeList* triVertFreeList;             // 0x534
    RwFreeList* triPolyFreeList;             // 0x538
    _rt2dTriIndex triVertIndex;              // 0x53c
    RwMatrixTag metricMtx;                   // 0x550
    RwMatrixTag* ctm[32];                    // 0x590
    s32 mtos;                                // 0x610
    RwV2d vw;                                // 0x614
    RwV2d vp;                                // 0x61c
    RwMatrixTag CTM2d;                       // 0x630
    RwMatrixTag iCTM2d;                      // 0x670
    RwMatrixTag CTM;                         // 0x6b0
    s32 CTMValid;                            // 0x6f0
    u32 TransformFlags;                      // 0x6f4
    f32 layerDepth;                          // 0x6f8
    f32 tolerance;                           // 0x6fc
    f32 sqTolerance;                         // 0x700
    s32 sqToleranceValid;                    // 0x704
    s32 flatDepth;                           // 0x708
    s32 extensionOffset;                     // 0x70c
    f32 deviceX;                             // 0x710
    f32 deviceY;                             // 0x714
    f32 deviceW;                             // 0x718
    f32 deviceH;                             // 0x71c
    s32 pixelSpace;                          // 0x720
    RwCamera* viewCamera;                    // 0x724
    Rt2dBrush* brush;                        // 0x728
    Rt2dFont* font;                          // 0x72c
    Rt2dPath* path;                          // 0x730
    u8* str;                                 // 0x734
    rt2dPathNode* pnode0;                    // 0x738
    rt2dPathNode* pnode1;                    // 0x73c
    f32 pathInset;                           // 0x740
    f32 oobaseu;                             // 0x744
    f32 fontbaseu;                           // 0x748
    Rt2dBBox bbox;                           // 0x74c
    RwV2d delta;                             // 0x75c
    s32 numVerts;                            // 0x764
    s32 numBatches;                          // 0x768
    RwCamera** cameraBeginUpdate;            // 0x76c
    RwCamera** cameraEndUpdate;              // 0x770
    RxClusterDefinition RxClPS2FillPos;      // 0x774
    RxClusterDefinition RxClPS2FillNrm;      // 0x784
    RxClusterDefinition RxClPS2FontUV1;      // 0x794
    RxClusterDefinition RxClPS2FontUV2;      // 0x7a4
    RxClusterDefinition RxClPS2StrokePos;    // 0x7b4
    RxClusterDefinition RxClPS2StrokeNrm;    // 0x7c4
    RxPipeline* default_pipe;                // 0x7d4
    RxPipeline* use_pipe;                    // 0x7d8
    RxPipeline* default_stroke_pipe;         // 0x7dc
    RxPipeline* use_stroke_pipe;             // 0x7e0
    RxPipeline* default_font_pipe;           // 0x7e4
    RxPipeline* use_font_pipe;               // 0x7e8
    RxPipeline* default_fill_pipe;           // 0x7ec
    RxPipeline* use_fill_pipe;               // 0x7f0
    RxPipeline* default_sgfont_pipe;         // 0x7f4
    RxPipeline* use_sgfont_pipe;             // 0x7f8
    s32 fill_batch_sz;                       // 0x7fc
    s32 font_batch_sz;                       // 0x800
    s32 stroke_batch_sz;                     // 0x804
    s32 sgfont_batch_sz;                     // 0x808
    Rt2dStrBuffer strBuffer;                 // 0x80c
    Rt2dFont* fontBatch;                     // 0xc14
    Rt2dFont** fontReadFunc;                 // 0xc18
    RwRGBA colorCache[64];                   // 0xc1c
    u32* triIdxCache;                        // 0xd1c
    u32 triIdxCacheSize;                     // 0xd20
    char filename[1024];                     // 0xd24
    s32* uCharIndex;                         // 0x1124
    s32 uCharIndexSize;                      // 0x1128
} Rt2dGlobalVars;

// 20 bytes
typedef struct _rt2dObjectString
{
    char* textString;              // 0x00
    Rt2dBrush* brush;              // 0x04
    s32 maxLength;                 // 0x08
    f32 height;                    // 0x0c
    _rt2dFontDictionaryNode* font; // 0x10
} _rt2dObjectString;

// 96 bytes
typedef struct _rt2dPickRegion
{
    Rt2dPath* path;             // 0x00
    Rt2dBBox bbox;              // 0x04
    RwMatrixTag transformation; // 0x20
} _rt2dPickRegion;

// 16 bytes
typedef struct _rt2dScene
{
    RwSList* objects;  // 0x00
    s32 objectCount;   // 0x04
    RwSList* depths;   // 0x08
    s32 isDirtyDepths; // 0x0c
} _rt2dScene;

typedef struct _rt2dShapeRep _rt2dShapeRep;
// 12 bytes
typedef struct _rt2dShape
{
    _rt2dShapeRep* rep; // 0x00
    RwRGBA* colorCache; // 0x04
    RpAtomic* atomic;   // 0x08
} _rt2dShape;

// 96 bytes
typedef union _rt2dObjectdata
{
    _rt2dShape shape;               // 0x00
    _rt2dScene scene;               // 0x00
    _rt2dPickRegion pickRegion;     // 0x00
    _rt2dObjectString objectString; // 0x00
} _rt2dObjectdata;

// 272 bytes
struct Rt2dObject
{
    s32 type;             // 0x00
    s32 depth;            // 0x04
    s32 flag;             // 0x08
    RwMatrixTag MTM;      // 0x10
    RwMatrixTag LTM;      // 0x50
    RwRGBAReal colorMult; // 0x90
    RwRGBAReal colorOffs; // 0xa0
    _rt2dObjectdata data; // 0xb0
};

// 28 bytes
struct Rt2dPath
{
    void* segments; // 0x00
    s32 numSegment; // 0x04
    s32 closed;     // 0x08
    s32 flat;       // 0x0c
    f32 inset;      // 0x10
    Rt2dPath* next; // 0x14
    Rt2dPath* curr; // 0x18
};

typedef struct RtAnimKeyFrameHeader RtAnimKeyFrameHeader;
// 8 bytes
typedef struct RtAnimInterpFrameHeader
{
    RtAnimKeyFrameHeader* keyFrame1; // 0x00
    RtAnimKeyFrameHeader* keyFrame2; // 0x04
} RtAnimInterpFrameHeader;

// 48 bytes
struct RtAnimInterpolatorInfo
{
    s32 typeID;                             // 0x00
    s32 interpKeyFrameSize;                 // 0x04
    s32 animKeyFrameSize;                   // 0x08
    void* keyFrameApplyCB;                  // 0x0c
    void* keyFrameBlendCB;                  // 0x10
    void* keyFrameInterpolateCB;            // 0x14
    void* keyFrameAddCB;                    // 0x18
    void* keyFrameMulRecipCB;               // 0x1c
    RtAnimAnimation** keyFrameStreamReadCB; // 0x20
    s32* keyFrameStreamWriteCB;             // 0x24
    s32* keyFrameStreamGetSizeCB;           // 0x28
    s32 customDataSize;                     // 0x2c
};

// 8 bytes
struct RtAnimKeyFrameHeader
{
    void* prevFrame; // 0x00
    f32 time;        // 0x04
};

// 28 bytes
typedef struct RtCharsetDesc
{
    s32 width;           // 0x00
    s32 height;          // 0x04
    s32 width_internal;  // 0x08
    s32 height_internal; // 0x0c
    s32 count;           // 0x10
    s32 tilewidth;       // 0x14
    s32 tileheight;      // 0x18
} RtCharsetDesc;

// 8 bytes
typedef struct _rtInt64
{
    s32 low;  // 0x00
    s32 high; // 0x04
} _rtInt64;

// 16 bytes
typedef struct RtInt64
{
    s64 supportValue;        // 0x00
    _rtInt64 noSupportValue; // 0x00
} RtInt64;

typedef struct RtFileSystem RtFileSystem;
// 96 bytes
typedef struct RtFile
{
    RtInt64 length;                      // 0x00
    RtInt64 position;                    // 0x10
    RtInt64 initialPos;                  // 0x20
    s32 isAsync;                         // 0x30
    s32 priority;                        // 0x34
    RtFileStatus status;                 // 0x38
    RtFileError error;                   // 0x3c
    RtFSFileOperation outstandingFileOp; // 0x40
    u32 outstandingSize;                 // 0x44
    void* outstandingCB;                 // 0x48
    void* outstandingCBData;             // 0x4c
    RtFileSystem* fileSystem;            // 0x50
} RtFile;

// 40 bytes
typedef struct RtFileSystemFileFunctionTable
{
    RtFileSystemError* open; // 0x00
    void* close;             // 0x04
    u32* read;               // 0x08
    u32* write;              // 0x0c
    RtInt64* setPosition;    // 0x10
    RtFileStatus* sync;      // 0x14
    s32* abort;              // 0x18
    s32* isEOF;              // 0x1c
    RtFileStatus* getStatus; // 0x20
    s32* fExists;            // 0x24
} RtFileSystemFileFunctionTable;

// 8 bytes
typedef struct rtFileSystemCallBacks
{
    void* registerCallBack;   // 0x00
    void* unregisterCallBack; // 0x04
} rtFileSystemCallBacks;

typedef struct RwSLLink RwSLLink;
// 88 bytes
struct RtFileSystem
{
    RwSLLink* next;                           // 0x00
    s32 maxNbOpenFiles;                       // 0x04
    RtFileSystemStatus status;                // 0x08
    char* deviceName;                         // 0x0c
    s32 defaultToAsync;                       // 0x10
    RtFile** fsGetObject;                     // 0x14
    void* fsClose;                            // 0x18
    char** fsGetDeviceName;                   // 0x1c
    rtFileSystemCallBacks CallBacks;          // 0x20
    RtFileSystemFileFunctionTable fsFileFunc; // 0x28
    char name[5];                             // 0x50
};

typedef struct RtUVFrameKeyFrame RtUVFrameKeyFrame;
// 28 bytes
typedef struct RtUVFrameInterpFrame
{
    RtUVFrameKeyFrame* keyFrame1; // 0x00
    RtUVFrameKeyFrame* keyFrame2; // 0x04
    f32 rot;                      // 0x08
    RwV2d trans;                  // 0x0c
    RwV2d scale;                  // 0x14
} RtUVFrameInterpFrame;

// 28 bytes
struct RtUVFrameKeyFrame
{
    RtUVFrameKeyFrame* prevFrame; // 0x00
    f32 time;                     // 0x04
    f32 rot;                      // 0x08
    RwV2d trans;                  // 0x0c
    RwV2d scale;                  // 0x14
};

typedef struct RtUVScrollKeyFrame RtUVScrollKeyFrame;
// 28 bytes
typedef struct RtUVScrollInterpFrame
{
    RtUVScrollKeyFrame* keyFrame1; // 0x00
    RtUVScrollKeyFrame* keyFrame2; // 0x04
    f32 rot;                       // 0x08
    RwV2d trans;                   // 0x0c
    RwV2d scale;                   // 0x14
} RtUVScrollInterpFrame;

// 28 bytes
struct RtUVScrollKeyFrame
{
    RtUVScrollKeyFrame* prevFrame; // 0x00
    f32 time;                      // 0x04
    f32 rot;                       // 0x08
    RwV2d trans;                   // 0x0c
    RwV2d scale;                   // 0x14
};

// 33 bytes
typedef struct RwChunkGroup
{
    char name[33]; // 0x00
} RwChunkGroup;

// 20 bytes
typedef struct RwChunkHeaderInfo
{
    u32 type;      // 0x00
    u32 length;    // 0x04
    u32 version;   // 0x08
    u32 buildNum;  // 0x0c
    s32 isComplex; // 0x10
} RwChunkHeaderInfo;

// 4 bytes
typedef struct RwEngineOpenParams
{
    void* displayID; // 0x00
} RwEngineOpenParams;

// 8 bytes
typedef struct RwError
{
    s32 pluginID;  // 0x00
    s32 errorCode; // 0x04
} RwError;

// 44 bytes
typedef struct RwFileFunctions
{
    s32* rwfexist;  // 0x00
    void** rwfopen; // 0x04
    s32* rwfclose;  // 0x08
    u32* rwfread;   // 0x0c
    u32* rwfwrite;  // 0x10
    char** rwfgets; // 0x14
    s32* rwfputs;   // 0x18
    s32* rwfeof;    // 0x1c
    s32* rwfseek;   // 0x20
    s32* rwfflush;  // 0x24
    s32* rwftell;   // 0x28
} RwFileFunctions;

// 36 bytes
struct RwFreeList
{
    u32 entrySize;        // 0x00
    u32 entriesPerBlock;  // 0x04
    u32 heapSize;         // 0x08
    u32 alignment;        // 0x0c
    RwLinkList blockList; // 0x10
    u32 flags;            // 0x18
    RwLLLink link;        // 0x1c
};

// 8 bytes
typedef struct RwModuleInfo
{
    s32 globalsOffset; // 0x00
    s32 numInstances;  // 0x04
} RwModuleInfo;

// 12 bytes
typedef struct RwMatFXInfo
{
    RwModuleInfo Module;      // 0x00
    RwFreeList* MaterialData; // 0x08
} RwMatFXInfo;

// 16 bytes
typedef struct RwMatrixWeights
{
    f32 w0; // 0x00
    f32 w1; // 0x04
    f32 w2; // 0x08
    f32 w3; // 0x0c
} RwMatrixWeights;

// 8 bytes
typedef struct RwMemory
{
    u8* start;  // 0x00
    u32 length; // 0x04
} RwMemory;

// 8 bytes
typedef struct RwMeshCache
{
    u32 lengthOfMeshesArray; // 0x00
    RwResEntry* meshes[1];   // 0x04
} RwMeshCache;

// 28 bytes
typedef struct RwMetrics
{
    u32 numTriangles;         // 0x00
    u32 numProcTriangles;     // 0x04
    u32 numVertices;          // 0x08
    u32 numTextureUploads;    // 0x0c
    u32 sizeTextureUploads;   // 0x10
    u32 numResourceAllocs;    // 0x14
    void* devSpecificMetrics; // 0x18
} RwMetrics;

// 28 bytes
typedef struct _rwPalQuantLeafNode
{
    f32 weight;    // 0x00
    RwRGBAReal ac; // 0x04
    f32 var;       // 0x14
    u8 palIndex;   // 0x18
} _rwPalQuantLeafNode;

// 32 bytes
typedef struct _rwPalQuantRGBABox
{
    s32 col0[4]; // 0x00
    s32 col1[4]; // 0x10
} _rwPalQuantRGBABox;

typedef struct _rwPalQuantOctNode _rwPalQuantOctNode;
// 16392 bytes
typedef struct RwPalQuant
{
    _rwPalQuantRGBABox Mcube[256]; // 0x00
    f32 Mvv[256];                  // 0x2000
    _rwPalQuantLeafNode Mvol[256]; // 0x2400
    _rwPalQuantOctNode* root;      // 0x4000
    RwFreeList* cubefreelist;      // 0x4004
} RwPalQuant;

typedef struct RwPluginRegEntry RwPluginRegEntry;
typedef struct RwPluginRegistry RwPluginRegistry;
// 60 bytes
struct RwPluginRegEntry
{
    s32 offset;                       // 0x00
    s32 size;                         // 0x04
    u32 pluginID;                     // 0x08
    RwStream** readCB;                // 0x0c
    RwStream** writeCB;               // 0x10
    s32* getSizeCB;                   // 0x14
    s32* alwaysCB;                    // 0x18
    s32* rightsCB;                    // 0x1c
    void** constructCB;               // 0x20
    void** destructCB;                // 0x24
    void** copyCB;                    // 0x28
    void** errStrCB;                  // 0x2c
    RwPluginRegEntry* nextRegEntry;   // 0x30
    RwPluginRegEntry* prevRegEntry;   // 0x34
    RwPluginRegistry* parentRegistry; // 0x38
};

// 24 bytes
struct RwPluginRegistry
{
    s32 sizeOfStruct;                // 0x00
    s32 origSizeOfStruct;            // 0x04
    s32 maxSizeOfStruct;             // 0x08
    s32 staticAlloc;                 // 0x0c
    RwPluginRegEntry* firstRegEntry; // 0x10
    RwPluginRegEntry* lastRegEntry;  // 0x14
};

// 16 bytes
struct RwRect
{
    s32 x; // 0x00
    s32 y; // 0x04
    s32 w; // 0x08
    s32 h; // 0x0c
};

typedef struct RwScopeTrace RwScopeTrace;
typedef struct RwReqEntry RwReqEntry;
typedef struct rxReq rxReq;
typedef struct RxPipelineNode RxPipelineNode;
// 36 bytes
struct RwReqEntry
{
    RxClusterDefinition* clusterDef; // 0x00
    RxClusterValidityReq required;   // 0x04
    u32 inputs;                      // 0x08
    RwScopeTrace* st;                // 0x0c
    RwReqEntry* next;                // 0x10
    rxReq* req;                      // 0x14
    u32 outbf;                       // 0x18
    u32 assignedslot;                // 0x1c
    RxPipelineNode* originatingNode; // 0x20
};

// 24 bytes
struct RwResEntry
{
    RwLLLink link;         // 0x00
    s32 size;              // 0x08
    void* owner;           // 0x0c
    RwResEntry** ownerRef; // 0x10
    void* destroyNotify;   // 0x14
};

// 8 bytes
typedef struct RwRwDeviceGlobals
{
    RwCamera* curCamera;         // 0x00
    RwMemoryFunctions* memFuncs; // 0x04
} RwRwDeviceGlobals;

// 4 bytes
struct RwSLLink
{
    RwSLLink* next; // 0x00
};

// 16 bytes
struct RwSList
{
    u8* listElements;       // 0x00
    s32 numElementsFilled;  // 0x04
    s32 numElementsAlloced; // 0x08
    s32 entrySize;          // 0x0c
};

// 16 bytes
struct RwScopeTrace
{
    RwReqEntry* head;           // 0x00
    RwScopeTrace* continuation; // 0x04
    RwScopeTrace* next;         // 0x08
    RwScopeTrace* parent;       // 0x0c
};

// 4 bytes
typedef struct RwSingleList
{
    RwSLLink link; // 0x00
} RwSingleList;

// 64 bytes
typedef union RwSky2DVertexAlignmentOverlay
{
    RwSky2DVertexFields els; // 0x00
    s32 qWords[4];           // 0x00
} RwSky2DVertexAlignmentOverlay;

// 276 bytes
typedef struct RwSkyFSState
{
    s32 gdfsOpenFiles;           // 0x00
    char SubDir[256];            // 0x04
    RwModuleInfo gdfsModuleInfo; // 0x104
    s32 DirEntry;                // 0x10c
    s32 IsRoot;                  // 0x110
} RwSkyFSState;

// 24 bytes
typedef struct RwVideoMode
{
    s32 width;             // 0x00
    s32 height;            // 0x04
    s32 depth;             // 0x08
    RwVideoModeFlag flags; // 0x0c
    s32 refRate;           // 0x10
    s32 format;            // 0x14
} RwVideoMode;

// 52 bytes
typedef struct RwSkyVideoMode
{
    RwVideoMode draw;     // 0x00
    RwVideoMode display;  // 0x18
    u8 numDrawBuffers;    // 0x30
    u8 numDisplayBuffers; // 0x31
    u8 tvSystem;          // 0x32
    u8 inplace;           // 0x33
} RwSkyVideoMode;

// 4 bytes
typedef union RwSplitBits
{
    f32 nReal; // 0x00
    s32 nInt;  // 0x00
    u32 nUInt; // 0x00
} RwSplitBits;

// 8 bytes
typedef struct RwStandard
{
    s32 nStandard;   // 0x00
    s32* fpStandard; // 0x04
} RwStandard;

// 20 bytes
typedef struct RwStreamCustom
{
    s32* sfnclose; // 0x00
    u32* sfnread;  // 0x04
    s32* sfnwrite; // 0x08
    s32* sfnskip;  // 0x0c
    void* data;    // 0x10
} RwStreamCustom;

// 4 bytes
typedef struct RwStreamFile
{
    void* fpFile;      // 0x00
    void* constfpFile; // 0x00
} RwStreamFile;

// 12 bytes
typedef struct RwStreamMemory
{
    u32 position; // 0x00
    u32 nSize;    // 0x04
    u8* memBlock; // 0x08
} RwStreamMemory;

// 20 bytes
typedef struct RwStreamUnion
{
    RwStreamMemory memory; // 0x00
    RwStreamFile file;     // 0x00
    RwStreamCustom custom; // 0x00
} RwStreamUnion;

// 36 bytes
struct RwStream
{
    RwStreamType type;             // 0x00
    RwStreamAccessType accessType; // 0x04
    s32 position;                  // 0x08
    RwStreamUnion Type;            // 0x0c
    s32 rwOwned;                   // 0x20
};

// 80 bytes
typedef struct RwSubSystemInfo
{
    char name[80]; // 0x00
} RwSubSystemInfo;

// 24 bytes
struct RwTexDictionary
{
    RwObject object;           // 0x00
    RwLinkList texturesInDict; // 0x08
    RwLLLink lInInstance;      // 0x10
};

// 88 bytes
struct RwTexture
{
    RwRaster* raster;       // 0x00
    RwTexDictionary* dict;  // 0x04
    RwLLLink lInDictionary; // 0x08
    char name[32];          // 0x10
    char mask[32];          // 0x30
    u32 filterAddressing;   // 0x50
    s32 refCount;           // 0x54
};

// 4 bytes
typedef struct RwTmpMatrix
{
    RwMatrixTag* m_matrix; // 0x00
} RwTmpMatrix;

// 40 bytes
typedef struct RxCamSpace3DVertex
{
    RwV3d cameraVertex; // 0x00
    u8 clipFlags;       // 0x0c
    u8 pad[3];          // 0x0d
    RwRGBAReal col;     // 0x10
    f32 u;              // 0x20
    f32 v;              // 0x24
} RxCamSpace3DVertex;

typedef struct RxPipelineCluster RxPipelineCluster;
// 28 bytes
typedef struct RxCluster
{
    u16 flags;                     // 0x00
    u16 stride;                    // 0x02
    void* data;                    // 0x04
    void* currentData;             // 0x08
    u32 numAlloced;                // 0x0c
    u32 numUsed;                   // 0x10
    RxPipelineCluster* clusterRef; // 0x14
    u32 attributes;                // 0x18
} RxCluster;

// 12 bytes
typedef struct RxClusterRef
{
    RxClusterDefinition* clusterDef;    // 0x00
    RxClusterForcePresent forcePresent; // 0x04
    u32 reserved;                       // 0x08
} RxClusterRef;

// 4 bytes
struct RxColorUnion
{
    RwRGBA preLitColor; // 0x00
    RwRGBA color;       // 0x00
};

typedef struct RxHeap RxHeap;
// 8 bytes
typedef struct RxPipelineNodeParam
{
    void* dataParam; // 0x00
    RxHeap* heap;    // 0x04
} RxPipelineNodeParam;

// 24 bytes
typedef struct RxExecutionContext
{
    RxPipeline* pipeline;        // 0x00
    RxPipelineNode* currentNode; // 0x04
    s32 exitCode;                // 0x08
    u32 pad;                     // 0x0c
    RxPipelineNodeParam params;  // 0x10
} RxExecutionContext;

typedef struct rxHeapSuperBlockDescriptor rxHeapSuperBlockDescriptor;
typedef struct rxHeapBlockHeader rxHeapBlockHeader;
typedef struct rxHeapFreeBlock rxHeapFreeBlock;
// 28 bytes
struct RxHeap
{
    u32 superBlockSize;               // 0x00
    rxHeapSuperBlockDescriptor* head; // 0x04
    rxHeapBlockHeader* headBlock;     // 0x08
    rxHeapFreeBlock* freeBlocks;      // 0x0c
    u32 entriesAlloced;               // 0x10
    u32 entriesUsed;                  // 0x14
    s32 dirty;                        // 0x18
};

typedef struct RxOutputSpec RxOutputSpec;
// 20 bytes
typedef struct RxIoSpec
{
    u32 numClustersOfInterest;               // 0x00
    RxClusterRef* clustersOfInterest;        // 0x04
    RxClusterValidityReq* inputRequirements; // 0x08
    u32 numOutputs;                          // 0x0c
    RxOutputSpec* outputs;                   // 0x10
} RxIoSpec;

// 4 bytes
typedef struct RxMatIndexBounds
{
    u16 minIndex; // 0x00
    u16 maxIndex; // 0x02
} RxMatIndexBounds;

// 208 bytes
typedef struct RxMeshStateVector
{
    s32 Flags;                             // 0x00
    void* SourceObject;                    // 0x04
    RwMatrixTag Obj2World;                 // 0x10
    RwMatrixTag Obj2Cam;                   // 0x50
    RwSurfaceProperties SurfaceProperties; // 0x90
    RwTexture* Texture;                    // 0x9c
    RwRGBA MatCol;                         // 0xa0
    RxPipeline* Pipeline;                  // 0xa4
    RwPrimitiveType PrimType;              // 0xa8
    u32 NumElements;                       // 0xac
    u32 NumVertices;                       // 0xb0
    s32 ClipFlagsOr;                       // 0xb4
    s32 ClipFlagsAnd;                      // 0xb8
    void* SourceMesh;                      // 0xbc
    void* DataObject;                      // 0xc0
} RxMeshStateVector;

// 28 bytes
typedef struct RxNodeMethods
{
    s32* nodeBody;           // 0x00
    s32* nodeInit;           // 0x04
    void* nodeTerm;          // 0x08
    s32* pipelineNodeInit;   // 0x0c
    void* pipelineNodeTerm;  // 0x10
    s32* pipelineNodeConfig; // 0x14
    u32* configMsgHandler;   // 0x18
} RxNodeMethods;

// 64 bytes
typedef struct RxNodeDefinition
{
    char* name;                      // 0x00
    RxNodeMethods nodeMethods;       // 0x04
    RxIoSpec io;                     // 0x20
    u32 pipelineNodePrivateDataSize; // 0x34
    RxNodeDefEditable editable;      // 0x38
    s32 InputPipesCnt;               // 0x3c
} RxNodeDefinition;

// 12 bytes
struct RxOutputSpec
{
    char* name;                      // 0x00
    RxClusterValid* outputClusters;  // 0x04
    RxClusterValid allOtherClusters; // 0x08
};

typedef struct rxNodePS2AllPvtData rxNodePS2AllPvtData;
typedef struct rxNodePS2AllMatPvtData rxNodePS2AllMatPvtData;
// 72 bytes
typedef struct RxPS2AllPipeData
{
    rxNodePS2AllPvtData* objPvtData;    // 0x00
    rxNodePS2AllMatPvtData* matPvtData; // 0x04
    void* sourceObject;                 // 0x08
    RpMeshHeader* meshHeader;           // 0x0c
    RwMeshCache* meshCache;             // 0x10
    RxInstanceFlags objInstance;        // 0x14
    u32 objIdentifier;                  // 0x18
    f32 spExtra;                        // 0x1c
    s32 numMorphTargets;                // 0x20
    u32 fastMorphing;                   // 0x24
    u8 transType;                       // 0x28
    u8 primType;                        // 0x29
    u8 matModulate;                     // 0x2a
    u8 vu1CodeIndex;                    // 0x2b
    RpMesh* mesh;                       // 0x2c
    RwResEntry** cacheEntryRef;         // 0x30
    RxInstanceFlags meshInstance;       // 0x34
    u32 meshIdentifier;                 // 0x38
    RwSurfaceProperties* surfProps;     // 0x3c
    RwTexture* texture;                 // 0x40
    RwRGBA matCol;                      // 0x44
} RxPS2AllPipeData;

// 48 bytes
typedef struct RxPacket
{
    u16 flags;                           // 0x00
    u16 numClusters;                     // 0x02
    RxPipeline* pipeline;                // 0x04
    u32* inputToClusterSlot;             // 0x08
    u32* slotsContinue;                  // 0x0c
    RxPipelineCluster** slotClusterRefs; // 0x10
    RxCluster clusters[1];               // 0x14
} RxPacket;

typedef struct RxPipelineRequiresCluster RxPipelineRequiresCluster;
// 52 bytes
struct RxPipeline
{
    s32 locked;                                   // 0x00
    u32 numNodes;                                 // 0x04
    RxPipelineNode* nodes;                        // 0x08
    u32 packetNumClusterSlots;                    // 0x0c
    rxEmbeddedPacketState embeddedPacketState;    // 0x10
    RxPacket* embeddedPacket;                     // 0x14
    u32 numInputRequirements;                     // 0x18
    RxPipelineRequiresCluster* inputRequirements; // 0x1c
    void* superBlock;                             // 0x20
    u32 superBlockSize;                           // 0x24
    u32 entryPoint;                               // 0x28
    u32 pluginId;                                 // 0x2c
    u32 pluginData;                               // 0x30
};

// 8 bytes
struct RxPipelineCluster
{
    RxClusterDefinition* clusterRef; // 0x00
    u32 creationAttributes;          // 0x04
};

typedef struct RxPipelineNodeTopSortData RxPipelineNodeTopSortData;
// 40 bytes
struct RxPipelineNode
{
    RxNodeDefinition* nodeDef;              // 0x00
    u32 numOutputs;                         // 0x04
    u32* outputs;                           // 0x08
    RxPipelineCluster** slotClusterRefs;    // 0x0c
    u32* slotsContinue;                     // 0x10
    void* privateData;                      // 0x14
    u32* inputToClusterSlot;                // 0x18
    RxPipelineNodeTopSortData* topSortData; // 0x1c
    void* initializationData;               // 0x20
    u32 initializationDataSize;             // 0x24
};

// 12 bytes
struct RxPipelineNodeTopSortData
{
    u32 numIns;        // 0x00
    u32 numInsVisited; // 0x04
    rxReq* req;        // 0x08
};

// 12 bytes
struct RxPipelineRequiresCluster
{
    RxClusterDefinition* clusterDef; // 0x00
    RxClusterValidityReq rqdOrOpt;   // 0x04
    u32 slotIndex;                   // 0x08
};

// 44 bytes
typedef struct RxRenderStateVector
{
    u32 Flags;                         // 0x00
    RwShadeMode ShadeMode;             // 0x04
    RwBlendFunction SrcBlend;          // 0x08
    RwBlendFunction DestBlend;         // 0x0c
    RwRaster* TextureRaster;           // 0x10
    RwTextureAddressMode AddressModeU; // 0x14
    RwTextureAddressMode AddressModeV; // 0x18
    RwTextureFilterMode FilterMode;    // 0x1c
    RwRGBA BorderColor;                // 0x20
    RwFogType FogType;                 // 0x24
    RwRGBA FogColor;                   // 0x28
} RxRenderStateVector;

// 8 bytes
typedef struct RxUV
{
    f32 u; // 0x00
    f32 v; // 0x04
} RxUV;

// 4 bytes
typedef struct SkinAtomicData
{
    RpHAnimHierarchy* hierarchy; // 0x00
} SkinAtomicData;

// 16 bytes
typedef struct SkinBoneData
{
    u32 numBones;                  // 0x00
    u32 numUsedBones;              // 0x04
    u8* usedBoneList;              // 0x08
    RwMatrixTag* invBoneToSkinMat; // 0x0c
} SkinBoneData;

// 12 bytes
typedef struct SkinCache
{
    void* unaligned;          // 0x00
    RwMatrixTag* matrixCache; // 0x04
    u32 number;               // 0x08
} SkinCache;

// 4 bytes
typedef struct SkinGlobalPlatform
{
    void* lightingCallBack; // 0x00
} SkinGlobalPlatform;

// 8 bytes
typedef struct SkinMatrixCache
{
    RwMatrixTag* aligned; // 0x00
    void* unaligned;      // 0x04
} SkinMatrixCache;

typedef struct SkinSplitData SkinSplitData;
// 44 bytes
typedef struct SkinGlobals
{
    s32 engineOffset;             // 0x00
    s32 atomicOffset;             // 0x04
    s32 geometryOffset;           // 0x08
    SkinMatrixCache matrixCache;  // 0x0c
    u32 numMatrices;              // 0x14
    RwFreeList* freeList;         // 0x18
    RwModuleInfo module;          // 0x1c
    SkinGlobalPlatform platform;  // 0x24
    SkinSplitData* skinSplitData; // 0x28
} SkinGlobals;

// 16 bytes
typedef struct SkinPlatformData
{
    u32 numVerticesWithWeight[4]; // 0x00
} SkinPlatformData;

// 24 bytes
struct SkinSplitData
{
    u32 boneLimit;          // 0x00
    u32 numMeshes;          // 0x04
    u32 numRLE;             // 0x08
    u8* matrixRemapIndices; // 0x0c
    u8* meshRLECount;       // 0x10
    u8* meshRLE;            // 0x14
};

// 12 bytes
typedef struct SkinVertexMaps
{
    u32 maxWeights;                 // 0x00
    u32* matrixIndices;             // 0x04
    RwMatrixWeights* matrixWeights; // 0x08
} SkinVertexMaps;

// 1824 bytes
typedef struct WorldGameVariables
{
    char* m_pasHelpTexts[3];                   // 0x28
    s32 m_nOptionValue_CurrentQuestion[4];     // 0x34
    s32 m_nOptionValue_CurrentAnswer[4];       // 0x44
    s32 m_nOptionValue_CurrentPagerMessage[4]; // 0x54
    s16 m_CurrentItemPriceUni[128];            // 0x64
    s32 m_nOptionValue_MainMenuSelection;      // 0x164
    s32 m_nLevelTarget;                        // 0x168
    s32 m_nCurrentRadioStation;                // 0x16c
    s32 m_nPlayVersusGameFlag;                 // 0x170
    s32 m_bShouldShowRewards;                  // 0x174
    s32 m_CurrentPictureID;                    // 0x178
    s32 m_CurrentPicture;                      // 0x17c
    u16 m_MissionProgress[40];                 // 0x180
    s32 m_CurrentActiveTaskID;                 // 0x1d0
    u16 m_DiamondCount[16];                    // 0x1d4
    u16 m_WinsLosses[16];                      // 0x1f4
    u16 m_UnlockablePoints[16];                // 0x214
    u16 m_SkillPoints[16];                     // 0x234
    u16 m_PlayerName[10];                      // 0x254
    u16 m_PlayerCredits[9];                    // 0x268
    u16* m_LocationDetails[9];                 // 0x27c
    u16* m_StoreDetails[4];                    // 0x2a0
    u16 m_LocationDetails_Name[64];            // 0x2b0
    u16 m_LocationDetails_Location[32];        // 0x330
    u16 m_LocationDetails_Type[16];            // 0x370
    u16 m_LocationDetails_Require[32];         // 0x390
    u16 m_LocationDetails_Difficulty[16];      // 0x3d0
    u16 m_LocationDetails_Description[230];    // 0x3f0
    u16 m_LocationDetails_Reward[32];          // 0x5bc
    u16 m_LocationDetails_Points[32];          // 0x5fc
    u16 m_LocationDetails_Status[32];          // 0x63c
    u8 m_LocationColumns;                      // 0x67c
    u8 m_LocationRows;                         // 0x67d
    u8 m_currentNeighborhood;                  // 0x67e
    s8 m_nCurrentCAMCategory;                  // 0x67f
    s8 m_nCAMCategorySelections[12];           // 0x680
    u16 m_CAMCategoryName[64];                 // 0x68c
    s16 m_currentFlowID;                       // 0x70c
    s32 m_nFoodPosition[4];                    // 0x710
} WorldGameVariables;

// 216 bytes
typedef struct _SkyCameraExt
{
    RwV3d largeFrustumVerts[8];           // 0x00
    RwFrustumPlane largeFrustumPlanes[6]; // 0x60
} _SkyCameraExt;

// 12 bytes
typedef struct _SkyMemBlock
{
    RwRaster* raster; // 0x00
    u32 address;      // 0x04
    u32 size;         // 0x08
} _SkyMemBlock;

// 92 bytes
typedef struct _SkyRasterExt
{
    s32 dmaRefCount;            // 0x00
    s32 dmaClrCount;            // 0x04
    u32 lsb;                    // 0x08
    u32 msb;                    // 0x0c
    u32 palOffset;              // 0x10
    u16 mipmapKL;               // 0x14
    u8 maxMipLevel;             // 0x16
    u8 bLocked;                 // 0x17
    u32 miptbp1Lsb;             // 0x18
    u32 miptbp1Msb;             // 0x1c
    u32 miptbp2Lsb;             // 0x20
    u32 miptbp2Msb;             // 0x24
    u32 sysMemSize;             // 0x28
    u32 sysMemPalSize;          // 0x2c
    u32 nTexCacheSize;          // 0x30
    u8 cachePkts;               // 0x34
    u8 lockedMipLevel;          // 0x35
    u8 flags;                   // 0x36
    u8 pad[1];                  // 0x37
    void* palUploadPkt;         // 0x38
    void* mipUploadPkts[7];     // 0x3c
    _SkyMemBlock* mpCacheEntry; // 0x58
} _SkyRasterExt;

// 60 bytes
typedef struct _SkyTexCache
{
    s32 enabled;             // 0x00
    u32 ringStart;           // 0x04
    u32 ringEnd;             // 0x08
    u32 ringSize;            // 0x0c
    u32 lockedStart;         // 0x10
    _SkyMemBlock* ring;      // 0x14
    s32 startAddr;           // 0x18
    s32 totalSize;           // 0x1c
    void* uploadRaster;      // 0x20
    RwRaster* currentRaster; // 0x24
    s32 context;             // 0x28
    u32 context1Index;       // 0x2c
    u32 context2Index;       // 0x30
    s32 originalStart;       // 0x34
    void* releaseRaster;     // 0x38
} _SkyTexCache;

// 20 bytes
typedef struct _rpBinaryAnimInterpolator
{
    s32 flags;            // 0x00
    s32 startMorphTarget; // 0x04
    s32 endMorphTarget;   // 0x08
    f32 time;             // 0x0c
    s32 nextInterpIndex;  // 0x10
} _rpBinaryAnimInterpolator;

// 24 bytes
typedef struct _rpMorphTarget
{
    RwSphere boundingSphere; // 0x00
    s32 pointsPresent;       // 0x10
    s32 normalsPresent;      // 0x14
} _rpMorphTarget;

// 40 bytes
typedef struct _rpSpline
{
    char name[32];   // 0x00
    s32 numVertices; // 0x20
    s32 splineType;  // 0x24
} _rpSpline;

// 12 bytes
typedef struct _rpTriStripEdge
{
    RpTriStripEdge* edge;  // 0x00
    RwLLLink inVertexLink; // 0x04
} _rpTriStripEdge;

// 12 bytes
typedef struct _rpTriStripTunnelStack
{
    RpTriStripEdge* edge;       // 0x00
    RpTriStripPolygon* polygon; // 0x04
    u32 length;                 // 0x08
} _rpTriStripTunnelStack;

// 12 bytes
typedef struct _rpTriStripVertex
{
    u32 numEdges;            // 0x00
    RwLinkList triangleList; // 0x04
} _rpTriStripVertex;

// 8 bytes
typedef struct _rpTriangle
{
    u32 vertex01;   // 0x00
    u32 vertex2Mat; // 0x04
} _rpTriangle;

// 12 bytes
struct _rt2dFontDictionaryNode
{
    char* name;                    // 0x00
    Rt2dFont* font;                // 0x04
    _rt2dFontDictionaryNode* next; // 0x08
};

// 8 bytes
typedef struct _rt2dSceneResourcePool
{
    _rt2dShapeRep** shapeReps; // 0x00
    u32 numShapeReps;          // 0x04
} _rt2dSceneResourcePool;

// 12 bytes
struct _rt2dShapeRep
{
    RwSList* nodes;       // 0x00
    u32 refCount;         // 0x04
    RpGeometry* geometry; // 0x08
};

// 112 bytes
typedef struct _rt2dStreamBrush
{
    u32 version;                 // 0x00
    rt2dShadeParameters top;     // 0x04
    rt2dShadeParameters dtop;    // 0x1c
    rt2dShadeParameters bottom;  // 0x34
    rt2dShadeParameters dbottom; // 0x4c
    u32 flag;                    // 0x64
    f32 halfwidth;               // 0x68
    s32 gotTexture;              // 0x6c
} _rt2dStreamBrush;

// 44 bytes
typedef struct _rt2dStreamObject
{
    u32 version;          // 0x00
    s32 type;             // 0x04
    s32 depth;            // 0x08
    RwRGBAReal colorMult; // 0x0c
    RwRGBAReal colorOffs; // 0x1c
} _rt2dStreamObject;

typedef struct _rt2dTriPoly _rt2dTriPoly;
typedef struct _rt2dTriVert _rt2dTriVert;
// 20 bytes
struct _rt2dTriPoly
{
    _rt2dTriPoly* next;      // 0x00
    _rt2dTriVert* vert;      // 0x04
    _rt2dTriIndex* triIndex; // 0x08
    s32 vCount;              // 0x0c
    RwV2d* pos;              // 0x10
};

// 8 bytes
struct _rt2dTriVert
{
    _rt2dTriVert* next; // 0x00
    s32 idx;            // 0x04
};

// 16 bytes
typedef struct _rt2streamPath
{
    u32 version;    // 0x00
    s32 numSegment; // 0x04
    s32 flag;       // 0x08
    f32 inset;      // 0x0c
} _rt2streamPath;

// 4 bytes
typedef union _rwIEEEFloatShapeType
{
    f32 value; // 0x00
    u32 word;  // 0x00
} _rwIEEEFloatShapeType;

// 48 bytes
typedef struct _rwIm3DPoolStash
{
    u32 flags;                        // 0x00
    RwMatrixTag* ltm;                 // 0x04
    u32 numVerts;                     // 0x08
    RxObjSpace3DVertex* objVerts;     // 0x0c
    RxCamSpace3DVertex* camVerts;     // 0x10
    RwSky2DVertex* devVerts;          // 0x14
    RxMeshStateVector* meshState;     // 0x18
    RxRenderStateVector* renderState; // 0x1c
    RxPipeline* pipeline;             // 0x20
    RwPrimitiveType primType;         // 0x24
    u16* indices;                     // 0x28
    u32 numIndices;                   // 0x2c
} _rwIm3DPoolStash;

// 5 bytes
typedef struct _rwPS2AllNormalLUTs
{
    u8 counterGen;     // 0x00
    u8 startIndOffset; // 0x01
    u8 shiftMask[1];   // 0x02
    u8 shiftMask2[1];  // 0x03
    u8 vertInc[1];     // 0x04
} _rwPS2AllNormalLUTs;

// 11 bytes
typedef struct _rwPS2AllTriFanLUTs
{
    u8 counterGen;     // 0x00
    u8 startIndOffset; // 0x01
    u8 shiftMask[3];   // 0x02
    u8 shiftMask2[3];  // 0x05
    u8 vertInc[3];     // 0x08
} _rwPS2AllTriFanLUTs;

// 64 bytes
typedef struct _rwPalQuantBranchNode
{
    _rwPalQuantOctNode* dir[16]; // 0x00
} _rwPalQuantBranchNode;

// 92 bytes
struct _rwPalQuantOctNode
{
    _rwPalQuantLeafNode Leaf;     // 0x00
    _rwPalQuantBranchNode Branch; // 0x1c
};

// 56 bytes
typedef struct _rwStreamFrame
{
    RwV3d right;     // 0x00
    RwV3d up;        // 0x0c
    RwV3d at;        // 0x18
    RwV3d pos;       // 0x24
    s32 parentIndex; // 0x30
    u32 data;        // 0x34
} _rwStreamFrame;

// 4 bytes
typedef struct _rwStreamFrameList
{
    s32 numFrames; // 0x00
} _rwStreamFrameList;

// 4 bytes
typedef struct _rwStreamTexDictionary
{
    u16 numTextures; // 0x00
    u16 deviceId;    // 0x02
} _rwStreamTexDictionary;

// 4 bytes
typedef struct _rwStreamTexture
{
    u32 filterAndAddress; // 0x00
} _rwStreamTexture;

// 16 bytes
typedef struct rpADCDegenerateRemovalStructureTag
{
    u32 numVertices;     // 0x00
    u32 numOrigVertices; // 0x04
    s32 preserveWinding; // 0x08
    s8* adcBits;         // 0x0c
} rpADCDegenerateRemovalStructureTag;

// 16 bytes
typedef struct rpAtomicBinary
{
    s32 frameIndex; // 0x00
    s32 geomIndex;  // 0x04
    s32 flags;      // 0x08
    s32 unused;     // 0x0c
} rpAtomicBinary;

// 96 bytes
typedef struct rpAtomicPS2AllLightData
{
    RwSurfaceProperties* surface; // 0x00
    RwMatrixTag invMat;           // 0x10
    f32 invScale;                 // 0x50
    f32 recipInvScale;            // 0x54
} rpAtomicPS2AllLightData;

typedef struct rpDMorphInterpolator rpDMorphInterpolator;
// 12 bytes
typedef struct rpDMorphAtomicData
{
    f32* values;                        // 0x00
    rpDMorphInterpolator* interpolator; // 0x04
    RpAtomic** defRenderCallBack;       // 0x08
} rpDMorphAtomicData;

// 20 bytes
typedef struct rpDMorphFrame
{
    f32 startValue;    // 0x00
    f32 endValue;      // 0x04
    f32 duration;      // 0x08
    f32 recipDuration; // 0x0c
    u32 nextFrame;     // 0x10
} rpDMorphFrame;

// 8 bytes
typedef struct rpDMorphFrameSequence
{
    u32 numFrames;         // 0x00
    rpDMorphFrame* frames; // 0x04
} rpDMorphFrameSequence;

// 12 bytes
typedef struct rpDMorphGeometryData
{
    u32 numDMorphTargets;          // 0x00
    RpDMorphTarget* dMorphTargets; // 0x04
    f32* currValues;               // 0x08
} rpDMorphGeometryData;

// 24 bytes
struct rpDMorphInterpolator
{
    RpDMorphAnimation* animation; // 0x00
    f32 animTime;                 // 0x04
    rpDMorphFrame** currFrames;   // 0x08
    f32* currTimes;               // 0x0c
    RpAtomic** loopCallBack;      // 0x10
    void* loopCallBackData;       // 0x14
};

// 144 bytes
typedef struct rpMatFXMaterialData
{
    MatFXEffectData data[2];    // 0x00
    RpMatFXMaterialFlags flags; // 0x80
} rpMatFXMaterialData;

// 8 bytes
typedef struct rpPolygon
{
    u16 matIndex;     // 0x00
    u16 vertIndex[3]; // 0x02
} rpPolygon;

// 12 bytes
typedef struct rpTextureChunkInfo
{
    RwTextureFilterMode filtering;    // 0x00
    RwTextureAddressMode addressingU; // 0x04
    RwTextureAddressMode addressingV; // 0x08
} rpTextureChunkInfo;

// 8 bytes
typedef struct rpWorldFindSectorData
{
    RpWorldSector* sector; // 0x00
    s32 foundSector;       // 0x04
} rpWorldFindSectorData;

// 32 bytes
typedef struct rt2dCharRect
{
    f32 width;      // 0x00
    RwTexture* tex; // 0x04
    RwV2d uv[2];    // 0x08
    Rt2dPath* path; // 0x18
    s8 charpage;    // 0x1c
} rt2dCharRect;

// 24 bytes
struct rt2dPathNode
{
    rt2dLinetype type; // 0x00
    RwV2d pos;         // 0x04
    RwV2d normal;      // 0x0c
    f32 dist;          // 0x14
};

// 12 bytes
typedef struct rtPickData
{
    RpAtomic* closestAtomic; // 0x00
    f32 closestDistance;     // 0x04
    RpWorldSector* sector;   // 0x08
} rtPickData;

// 8 bytes
typedef struct rwDMA_pktTag
{
    u32 type;   // 0x00
    void* addr; // 0x04
} rwDMA_pktTag;

// 60 bytes
typedef struct rwIm3DPool
{
    u16 numElements;        // 0x00
    u16 pad;                // 0x02
    void* elements;         // 0x04
    s32 stride;             // 0x08
    _rwIm3DPoolStash stash; // 0x0c
} rwIm3DPool;

// 24 bytes
typedef struct rwIm3DRenderPipelines
{
    RxPipeline* triList;   // 0x00
    RxPipeline* triFan;    // 0x04
    RxPipeline* triStrip;  // 0x08
    RxPipeline* lineList;  // 0x0c
    RxPipeline* polyLine;  // 0x10
    RxPipeline* pointList; // 0x14
} rwIm3DRenderPipelines;

typedef struct rwImageFormat rwImageFormat;
// 52 bytes
struct rwImageFormat
{
    char lcExtension[20];      // 0x00
    char ucExtension[20];      // 0x14
    RwImage** readImage;       // 0x28
    RwImage** writeImage;      // 0x2c
    rwImageFormat* nextFormat; // 0x30
};

// 124 bytes
typedef struct rwImmediGlobals
{
    RxPipeline* im3DTransformPipeline;                 // 0x00
    rwIm3DRenderPipelines im3DRenderPipelines;         // 0x04
    RxPipeline* platformIm3DTransformPipeline;         // 0x1c
    rwIm3DRenderPipelines platformIm3DRenderPipelines; // 0x20
    RxPipeline* ps2AllMatIm3DTrianglePipeline;         // 0x38
    RxPipeline* ps2AllMatIm3DLinePipeline;             // 0x3c
    rwIm3DPool curPool;                                // 0x40
} rwImmediGlobals;

// 8 bytes
typedef struct rwPS2AllClusterInstanceInfo
{
    u32 attrib; // 0x00
    u32 stride; // 0x04
} rwPS2AllClusterInstanceInfo;

// 8 bytes
typedef struct rwPS2AllClusterQuickInfo
{
    void* data; // 0x00
    u32 stride; // 0x04
} rwPS2AllClusterQuickInfo;

// 24 bytes
typedef struct rwPS2AllFieldRec
{
    s32 numVerts;        // 0x00
    s32 morphNumVerts;   // 0x04
    s32 dataoffset;      // 0x08
    s32 morphDataoffset; // 0x0c
    s16 skip;            // 0x10
    s16 morphSkip;       // 0x12
    s16 reverse;         // 0x14
    u8 vuoffset;         // 0x16
    u8 pad[1];           // 0x17
} rwPS2AllFieldRec;

// 18 bytes
typedef struct rwPS2AllIndexLUTs
{
    u16 fakeIndices[1];         // 0x00
    _rwPS2AllNormalLUTs normal; // 0x02
    _rwPS2AllTriFanLUTs triFan; // 0x07
} rwPS2AllIndexLUTs;

// 14 bytes
typedef struct rwPS2AllPrimTypeLUT
{
    u8 vertToIndRatio[7];  // 0x00
    u8 vertToIndOffset[7]; // 0x07
} rwPS2AllPrimTypeLUT;

// 312 bytes
typedef struct rwPS2AllResEntryFormat
{
    u8 batchRound;                 // 0x00
    u8 stripReverse;               // 0x01
    u8 pad[2];                     // 0x02
    u32 maxInputSize;              // 0x04
    s32 batchSize;                 // 0x08
    s32 batchesPerTag;             // 0x0c
    s32 morphBatchSize;            // 0x10
    s32 morphBatchesPerTag;        // 0x14
    rwPS2AllFieldRec fieldRec[12]; // 0x18
} rwPS2AllResEntryFormat;

// 432 bytes
typedef struct rwPS2AllResEntryHeader
{
    s32 refCnt;                               // 0x00
    s32 clrCnt;                               // 0x04
    void* data;                               // 0x08
    u32 numVerts;                             // 0x0c
    u32 objIdentifier;                        // 0x10
    u32 meshIdentifier;                       // 0x14
    s32 batchSize;                            // 0x18
    s32 numBatches;                           // 0x1c
    s32 batchesPerTag;                        // 0x20
    s32 morphStart;                           // 0x24
    s32 morphFinish;                          // 0x28
    s32 morphNum;                             // 0x2c
    rwPS2AllClusterQuickInfo clquickinfo[12]; // 0x30
    rwPS2AllFieldRec fieldRec[12];            // 0x90
} rwPS2AllResEntryHeader;

typedef struct rwResHeapHeader rwResHeapHeader;
typedef struct rwResHeapBlockHeader rwResHeapBlockHeader;
// 32 bytes
struct rwResHeapBlockHeader
{
    rwResHeapHeader* heap;      // 0x00
    rwResHeapBlockHeader* next; // 0x04
    rwResHeapBlockHeader* prev; // 0x08
    u32 size;                   // 0x0c
    rwResHeapBlockFlags flags;  // 0x10
    u32 pad[3];                 // 0x14
};

// 8 bytes
struct rwResHeapHeader
{
    rwResHeapBlockHeader* firstBlock;     // 0x00
    rwResHeapBlockHeader* firstFreeBlock; // 0x04
};

// 40 bytes
typedef struct rwResources
{
    s32 maxSize;             // 0x00
    s32 currentSize;         // 0x04
    s32 reusageSize;         // 0x08
    void* memHeap;           // 0x0c
    RwLinkList entriesA;     // 0x10
    RwLinkList entriesB;     // 0x18
    RwLinkList* freeEntries; // 0x20
    RwLinkList* usedEntries; // 0x24
} rwResources;

// 32 bytes
typedef struct rwStreamCamera
{
    RwV2d viewWindow; // 0x00
    RwV2d viewOffset; // 0x08
    f32 nearPlane;    // 0x10
    f32 farPlane;     // 0x14
    f32 fogPlane;     // 0x18
    u32 projection;   // 0x1c
} rwStreamCamera;

// 32 bytes
struct rxHeapBlockHeader
{
    rxHeapBlockHeader* prev;    // 0x00
    rxHeapBlockHeader* next;    // 0x04
    u32 size;                   // 0x08
    rxHeapFreeBlock* freeEntry; // 0x0c
    u32 pad[4];                 // 0x10
};

// 8 bytes
struct rxHeapFreeBlock
{
    u32 size;               // 0x00
    rxHeapBlockHeader* ptr; // 0x04
};

// 12 bytes
struct rxHeapSuperBlockDescriptor
{
    void* start;                      // 0x00
    u32 size;                         // 0x04
    rxHeapSuperBlockDescriptor* next; // 0x08
};

// 64 bytes
typedef struct rxNodePS2AllMatInitData
{
    RxClusterDefinition* clusters[12]; // 0x00
    s32 vu1MaxStripInputSize;          // 0x30
    s32 vu1MaxListInputSize;           // 0x34
    s32 sizeOnVU;                      // 0x38
    RpMeshHeaderFlags pipeType;        // 0x3c
} rxNodePS2AllMatInitData;

// 812 bytes
struct rxNodePS2AllMatPvtData
{
    s32* meshInstanceTestCB;                // 0x00
    RwResEntry** resEntryAllocCB;           // 0x04
    s32* instanceCB;                        // 0x08
    s32* bridgeCB;                          // 0x0c
    s32* postMeshCB;                        // 0x10
    s32 vifOffset;                          // 0x14
    void** vu1CodeArray;                    // 0x18
    u32 codeArrayLength;                    // 0x1c
    rwPS2AllClusterInstanceInfo clinfo[12]; // 0x20
    u32 cliIndex[12];                       // 0x80
    RpMeshHeaderFlags pipeType;             // 0xb0
    u8 totallyOpaque;                       // 0xb4
    u8 numStripes;                          // 0xb5
    u8 sizeOnVU;                            // 0xb6
    u8 pad0;                                // 0xb7
    rwPS2AllResEntryFormat strip;           // 0xb8
    rwPS2AllResEntryFormat list;            // 0x1f0
    u32 magicValue;                         // 0x328
};

// 88 bytes
struct rxNodePS2AllPvtData
{
    rwPS2AllPrimTypeLUT primLUT; // 0x00
    u8 pad[2];                   // 0x0e
    s32* objectSetupCB;          // 0x10
    s32* objectFinalizeCB;       // 0x14
    RxPipeline* groupPipe;       // 0x18
    u32 lightOffset;             // 0x1c
    u32 lightBufferSize;         // 0x20
    void* nullLightBlock;        // 0x24
    f32 nullLightBuffer[12];     // 0x28
};

// 20 bytes
struct rxReq
{
    u32 numused;            // 0x00
    u32 numalloced;         // 0x04
    u32 unavailslots;       // 0x08
    RwReqEntry* reqentries; // 0x0c
    RxPipelineNode* node;   // 0x10
};

typedef struct AllCallBackType AllCallBackType;
typedef struct AllMatCallBackType AllMatCallBackType;
typedef struct AllMatPvtData AllMatPvtData;
typedef struct AllMatSetVU AllMatSetVU;
typedef struct AllPipeData AllPipeData;
typedef struct DPS DPS;
typedef struct DPool DPool;
typedef struct DPoolStash DPoolStash;
typedef struct OBJ_CUSTOMRENDER OBJ_CUSTOMRENDER;
typedef struct RpAtomicPS RpAtomicPS;
typedef struct RpMeshPS RpMeshPS;
typedef struct RpPrjTex RpPrjTex;
typedef struct RpWorldSectorPS RpWorldSectorPS;
typedef struct Rt Rt;
typedef struct RtFSManager RtFSManager;
typedef struct RwIm RwIm;
typedef struct RwV RwV;
typedef struct RxNodeDefinitionGetPS RxNodeDefinitionGetPS;
typedef struct RxPS RxPS;
typedef struct RxPipelineNodePS RxPipelineNodePS;
typedef struct _RespAct _RespAct;
typedef struct _RpcResponse _RpcResponse;
typedef struct _rpAtomicPS _rpAtomicPS;
typedef struct _rpWorldSectorPS _rpWorldSectorPS;
typedef struct _rt _rt;
typedef struct _rwIm _rwIm;
typedef struct _rwPS _rwPS;
typedef struct _rwV _rwV;
typedef struct _rwfastIm _rwfastIm;
typedef struct cluster cluster;
typedef struct d d;
typedef struct dBrush dBrush;
typedef struct dFont dFont;
typedef struct dPS dPS;
typedef struct dPath dPath;
typedef struct ps ps;
typedef struct rwIm rwIm;
typedef struct rxNodePS rxNodePS;
typedef struct vu vu;

s8* RpADCGeometryGetADCSupport(RpGeometry* pGeom);
s32 RpADCPluginAttach(void);
s8* RpADCWorldSectorGetADCSupport(RpWorldSector* sector);
RpAtomic* RpAtomicClone(RpAtomic* atomic);
RpAtomic* RpAtomicCreate(void);
s32 RpAtomicDestroy(RpAtomic* atomic);
s32 RpAtomicGetPluginOffset(u32 pluginID);
RpWorld* RpAtomicGetWorld(RpAtomic* atomic);
RwSphere* RpAtomicGetWorldBoundingSphere(RpAtomic* atomic);
s32 RpAtomicPS2AllInstance(RxPS2AllPipeData* ps2AllPipeData);
void RpAtomicPS2AllLightingSetupFunc(RxPS2AllPipeData* ps2AllPipeData);
void RpAtomicPS2AllObjInstanceTestFunc(RpAtomic* atomic, RxPS2AllPipeData* ps2AllPipeData);
s32 RpAtomicPS2AllObjectSetupCallBack(RxPS2AllPipeData* ps2AllPipeData, RwMatrixTag** transform);
void RpAtomicPS2AllPrimTypeTransTypeSetupFunc(RxPS2AllPipeData* ps2AllPipeData, RwFrustumTestResult inFrustum);
void RpAtomicPS2AllResEntryAllocFunc(RxPS2AllPipeData* ps2AllPipeData, RwResEntry** repEntry, u32 size, void* destroyCallBack);
s32 RpAtomicRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
s32 RpAtomicRegisterPluginStream(u32 pluginID, RwStream** readCB, RwStream** writeCB, s32* getSizeCB);
RxPipeline* RpAtomicSetDefaultPipeline(RxPipeline* pipeline);
RpAtomic* RpAtomicSetFrame(RpAtomic* atomic, RwFrame* frame);
RpAtomic* RpAtomicSetGeometry(RpAtomic* atomic, RpGeometry* geometry, u32 flags);
s32 RpAtomicSetStreamAlwaysCallBack(u32 pluginID, s32* alwaysCB);
s32 RpAtomicSetStreamRightsCallBack(u32 pluginID, s32* rightsCB);
RpMeshHeader* RpBuildMeshGenerateDefaultTriStrip(RpBuildMesh* buildMesh);
RpClump* RpClumpAddAtomic(RpClump* clump, RpAtomic* atomic);
RpClump* RpClumpClone(RpClump* clump);
RpClump* RpClumpCreate(void);
s32 RpClumpDestroy(RpClump* clump);
RpClump* RpClumpForAllAtomics(RpClump* clump, RpAtomic** callback, void* pData);
RpClump* RpClumpForAllCameras(RpClump* clump, RwCamera** callback, void* pData);
RpClump* RpClumpForAllLights(RpClump* clump, RpLight** callback, void* pData);
s32 RpClumpGetNumAtomics(RpClump* clump);
s32 RpClumpRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
RpClump* RpClumpRemoveCamera(RpClump* clump, RwCamera* camera);
RpClump* RpClumpRemoveLight(RpClump* clump, RpLight* light);
RpClump* RpClumpRender(RpClump* clump);
RpClump* RpClumpStreamRead(RwStream* stream);
RpDMorphAnimation* RpDMorphAnimationCreate(u32 numDMorphTargets);
RpDMorphAnimation* RpDMorphAnimationCreateFrames(RpDMorphAnimation* anim, u32 dMorphTargetIndex, u32 numFrames);
RpDMorphAnimation* RpDMorphAnimationDestroy(RpDMorphAnimation* anim);
f32 RpDMorphAnimationFrameGetDuration(RpDMorphAnimation* anim, u32 dMorphTargetIndex, u32 frameIndex);
u32 RpDMorphAnimationGetNumDMorphTargets(RpDMorphAnimation* animation);
u32 RpDMorphAnimationGetNumFrames(RpDMorphAnimation* animation, u32 dMorphTargetIndex);
RpDMorphAnimation* RpDMorphAnimationStreamRead(RwStream* stream);
RpAtomic* RpDMorphAtomicAddTime(RpAtomic* atomic, f32 deltaTime);
f32* RpDMorphAtomicGetDMorphValues(RpAtomic* atomic);
RpAtomic* RpDMorphAtomicInitialize(RpAtomic* atomic);
RpAtomic* RpDMorphAtomicSetAnimLoopCallBack(RpAtomic* atomic, RpAtomic** callBack, void* data);
RpAtomic* RpDMorphAtomicSetAnimation(RpAtomic* atomic, RpDMorphAnimation* animation);
RpAtomic* RpDMorphAtomicSetType(RpAtomic* atomic, RpDMorphType type);
RpGeometry* RpDMorphGeometryCreateDMorphTargets(RpGeometry* geometry, u32 number);
RpGeometry* RpDMorphGeometryDestroyDMorphTargets(RpGeometry* geometry);
RpDMorphTarget* RpDMorphGeometryGetDMorphTarget(RpGeometry* geometry, u32 index);
u32 RpDMorphGeometryGetNumDMorphTargets(RpGeometry* geometry);
RpGeometry* RpDMorphGeometryRemoveDMorphTarget(RpGeometry* geometry, u32 index);
s32 RpDMorphPluginAttach(void);
char* RpDMorphTargetGetName(RpDMorphTarget* dMorphTarget);
s32 RpGeometryAddMorphTargets(RpGeometry* geometry, s32 mtcount);
RpGeometry* RpGeometryAddRef(RpGeometry* geometry);
RpGeometry* RpGeometryCreate(s32 numVerts, s32 numTriangles, u32 format);
s32 RpGeometryDestroy(RpGeometry* geometry);
RpGeometry* RpGeometryForAllMaterials(RpGeometry* geometry, RpMaterial** fpCallBack, void* pData);
RpUserDataArray* RpGeometryGetUserDataArray(RpGeometry* geometry, s32 data);
s32 RpGeometryGetUserDataArrayCount(RpGeometry* geometry);
RpGeometry* RpGeometryLock(RpGeometry* geometry, s32 lockMode);
s32 RpGeometryRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
s32 RpGeometryRegisterPluginStream(u32 pluginID, RwStream** readCB, RwStream** writeCB, s32* getSizeCB);
RpGeometry* RpGeometryStreamRead(RwStream* stream);
RpGeometry* RpGeometryTriangleSetMaterial(RpGeometry* geometry, RpTriangle* triangle, RpMaterial* material);
RpGeometry* RpGeometryTriangleSetVertexIndices(RpGeometry* geometry, RpTriangle* triangle, u16 vert1, u16 vert2, u16 vert3);
RpGeometry* RpGeometryUnlock(RpGeometry* geometry);
RpHAnimHierarchy* RpHAnimFrameGetHierarchy(RwFrame* frame);
s32 RpHAnimFrameGetID(RwFrame* frame);
s32 RpHAnimFrameSetHierarchy(RwFrame* frame, RpHAnimHierarchy* hierarchy);
s32 RpHAnimFrameSetID(RwFrame* frame, s32 id);
RpHAnimHierarchy* RpHAnimHierarchyAttach(RpHAnimHierarchy* hierarchy);
RpHAnimHierarchy* RpHAnimHierarchyCreate(s32 numNodes, u32* nodeFlags, s32* nodeIDs, RpHAnimHierarchyFlag flags, s32 maxInterpKeyFrameSize);
RpHAnimHierarchy* RpHAnimHierarchyCreateFromHierarchy(RpHAnimHierarchy* hierarchy, RpHAnimHierarchyFlag flags, s32 maxInterpKeyFrameSize);
RpHAnimHierarchy* RpHAnimHierarchyDestroy(RpHAnimHierarchy* hierarchy);
RpHAnimHierarchy* RpHAnimHierarchyDetach(RpHAnimHierarchy* hierarchy);
RwMatrixTag* RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy* hierarchy);
s32 RpHAnimIDGetIndex(RpHAnimHierarchy* hierarchy, s32 ID);
void RpHAnimKeyFrameAdd(void* pVoidOut, void* pVoidIn1, void* pVoidIn2);
void RpHAnimKeyFrameApply(void* pMatrix, void* pVoidIFrame);
void RpHAnimKeyFrameBlend(void* pVoidOut, void* pVoidIn1, void* pVoidIn2, f32 fAlpha);
void RpHAnimKeyFrameInterpolate(void* pVoidOut, void* pVoidIn1, void* pVoidIn2, f32 time);
void RpHAnimKeyFrameMulRecip(void* pVoidFrame, void* pVoidStart);
s32 RpHAnimKeyFrameStreamGetSize(RtAnimAnimation* animation);
RtAnimAnimation* RpHAnimKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* pAnimation);
s32 RpHAnimKeyFrameStreamWrite(RtAnimAnimation* pAnimation, RwStream* stream);
s32 RpHAnimPluginAttach(void);
RpLight* RpLightCreate(s32 type);
s32 RpLightDestroy(RpLight* light);
s32 RpLightRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
s32 RpLightRegisterPluginStream(u32 pluginID, RwStream** readCB, RwStream** writeCB, s32* getSizeCB);
RpLight* RpLightSetColor(RpLight* light, RwRGBAReal* color);
RpLight* RpLightStreamRead(RwStream* stream);
RpAtomic* RpMatFXAtomicEnableEffects(RpAtomic* atomic);
s32 RpMatFXAtomicQueryEffects(RpAtomic* atomic);
f32 RpMatFXMaterialGetBumpMapCoefficient(RpMaterial* material);
RwFrame* RpMatFXMaterialGetBumpMapFrame(RpMaterial* material);
RwTexture* RpMatFXMaterialGetBumpMapTexture(RpMaterial* material);
RpMaterial* RpMatFXMaterialGetDualBlendModes(RpMaterial* material, RwBlendFunction* srcBlendMode, RwBlendFunction* dstBlendMode);
RwTexture* RpMatFXMaterialGetDualTexture(RpMaterial* material);
RpMatFXMaterialFlags RpMatFXMaterialGetEffects(RpMaterial* material);
f32 RpMatFXMaterialGetEnvMapCoefficient(RpMaterial* material);
RwFrame* RpMatFXMaterialGetEnvMapFrame(RpMaterial* material);
s32 RpMatFXMaterialGetEnvMapFrameBufferAlpha(RpMaterial* material);
RwTexture* RpMatFXMaterialGetEnvMapTexture(RpMaterial* material);
RpMaterial* RpMatFXMaterialGetUVTransformMatrices(RpMaterial* material, RwMatrixTag** baseTransform, RwMatrixTag** dualTransform);
RpMaterial* RpMatFXMaterialSetBumpMapCoefficient(RpMaterial* material, f32 coef);
RpMaterial* RpMatFXMaterialSetBumpMapFrame(RpMaterial* material, RwFrame* frame);
RpMaterial* RpMatFXMaterialSetBumpMapTexture(RpMaterial* material, RwTexture* bumpTexture);
RpMaterial* RpMatFXMaterialSetDualBlendModes(RpMaterial* material, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode);
RpMaterial* RpMatFXMaterialSetDualTexture(RpMaterial* material, RwTexture* texture);
RpMaterial* RpMatFXMaterialSetEffects(RpMaterial* material, RpMatFXMaterialFlags flags);
RpMaterial* RpMatFXMaterialSetEnvMapCoefficient(RpMaterial* material, f32 coef);
RpMaterial* RpMatFXMaterialSetEnvMapFrame(RpMaterial* material, RwFrame* frame);
RpMaterial* RpMatFXMaterialSetEnvMapFrameBufferAlpha(RpMaterial* material, s32 useFrameBufferAlpha);
RpMaterial* RpMatFXMaterialSetEnvMapTexture(RpMaterial* material, RwTexture* texture);
RpMaterial* RpMatFXMaterialSetUVTransformMatrices(RpMaterial* material, RwMatrixTag* baseTransform, RwMatrixTag* dualTransform);
RpMaterial* RpMatFXMaterialSetupDualTexture(RpMaterial* material, RwTexture* texture, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode);
RpMaterial* RpMatFXMaterialSetupEnvMap(RpMaterial* material, RwTexture* texture, RwFrame* frame, s32 useFrameBufferAlpha, f32 coef);
s32 RpMatFXPluginAttach(void);
RpWorldSector* RpMatFXWorldSectorEnableEffects(RpWorldSector* worldSector);
RpMaterial* RpMaterialCreate(void);
s32 RpMaterialDestroy(RpMaterial* material);
s32 RpMaterialRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
s32 RpMaterialRegisterPluginStream(u32 pluginID, RwStream** readCB, RwStream** writeCB, s32* getSizeCB);
RxPipeline* RpMaterialSetDefaultPipeline(RxPipeline* pipeline);
s32 RpMaterialSetStreamRightsCallBack(u32 pluginID, s32* rightsCB);
RpMaterial* RpMaterialSetTexture(RpMaterial* material, RwTexture* texture);
RpMaterial* RpMaterialStreamRead(RwStream* stream);
s32 RpMeshPS2AllBridgeCallBack(RxPS2AllPipeData* ps2AllPipeData);
s32 RpMeshPS2AllInstanceCallBack(RxPS2AllPipeData* ps2AllPipeData);
s32 RpMeshPS2AllMeshInstanceTestCallBack(RxPS2AllPipeData* ps2AllPipeData);
RwResEntry* RpMeshPS2AllResEntryAllocCallBack(RxPS2AllPipeData* ps2AllPipeData, RwResEntry** repEntry, u32 size, void* destroyCallBack);
RpAtomic* RpMorphAtomicAddTime(RpAtomic* atomic, f32 time);
s32 RpMorphAtomicGetCurrentInterpolator(RpAtomic* atomic);
RpAtomic* RpMorphAtomicSetCurrentInterpolator(RpAtomic* atomic, s32 interpNum);
RpAtomic* RpMorphAtomicSetTime(RpAtomic* atomic, f32 time);
RpGeometry* RpMorphGeometryCreateInterpolators(RpGeometry* geometry, s32 numInterps);
RpMorphInterpolator* RpMorphGeometryGetInterpolator(RpGeometry* geometry, s32 interpNum);
RpGeometry* RpMorphGeometrySetInterpolator(RpGeometry* geometry, s32 interpNum, s32 startKey, s32 endKey, f32 time);
s32 RpMorphPluginAttach(void);
RpMorphTarget* RpMorphTargetCalcBoundingSphere(RpMorphTarget* morphTarget, RwSphere* boundingSphere);
RpAtomic* RpSkinAtomicSetHAnimHierarchy(RpAtomic* atomic, RpHAnimHierarchy* hierarchy);
RpAtomic* RpSkinAtomicSetType(RpAtomic* atomic, RpSkinType type);
RpSkin* RpSkinDestroy(RpSkin* skin);
RpSkin* RpSkinGeometryGetSkin(RpGeometry* geometry);
RpGeometry* RpSkinGeometrySetSkin(RpGeometry* geometry, RpSkin* skin);
u32 RpSkinGetNumBones(RpSkin* skin);
RwMatrixTag* RpSkinGetSkinToBoneMatrices(RpSkin* skin);
s32 RpSkinPluginAttach(void);
RwRaster* RpSkyGetDrawBufferRaster(void);
s32 RpSkyGetTrueTLClipper(void);
s32 RpSkyGetTrueTSClipper(void);
s32 RpSkyResume(void);
s32 RpSkySelectDeepZBuffer(s32 val);
s32 RpSkySelectTrueTLClipper(s32 val);
s32 RpSkySelectTrueTSClipper(s32 val);
s32 RpSkySuspend(void);
s32 RpSkyTexCacheAccessRaster(RwRaster* raster, s32 useContext2);
void RpSkyTexCacheAccessSpeculate(RwRaster* raster);
void RpSkyTexCacheFlush(void);
s32 RpSkyTexCacheRasterLock(RwRaster* raster, s32 lock);
void RpSkyTexCacheReleaseRaster(RwRaster* raster);
void RpSkyTexCacheRestore(void);
RwRaster* RpSkyTexCalcTex1(RwRaster* raster, u64* tex1, RwTextureFilterMode filter);
RwRaster* RpSkyTexGetTex0(RwRaster* raster, u32* msb, u32* lsb);
RwRaster* RpSkyTexSetTex0(RwRaster* raster, u32 msb, u32 lsb);
f32 RpSkyTextureGetMipmapK(RwTexture* tex);
u32 RpSkyTextureGetMipmapL(RwTexture* tex);
RwTexture* RpSkyTextureSetMipmapK(RwTexture* tex, f32 val);
RwTexture* RpSkyTextureSetMipmapL(RwTexture* tex, u32 val);
RpSpline* RpSplineCreate(s32 numCtrlPoints, s32 type, RwV3d* ctrlPoints);
s32 RpSplineDestroy(RpSpline* spline);
RwV3d* RpSplineFindPosition(RpSpline* spline, s32 path, f32 where, RwV3d* pos, RwV3d* tangent);
s32 RpSplineGetNumControlPoints(RpSpline* spline);
s32 RpSplinePluginAttach(void);
RpTeam* RpTeamCreate(u32 numOfPlayers, u32 numOfPlayerElements);
s32 RpTeamDestroy(RpTeam* team);
RpTeamDictionary* RpTeamDictionaryCreate(u32 numOfDictionaryElements);
s32 RpTeamDictionaryDestroy(RpTeamDictionary* dictionary);
RpAtomic* RpTeamDictionaryGetLODElement(RpTeamDictionary* dictionary, u32 lodIndex, u32 dictionaryIndex);
u32 RpTeamDictionaryGetNumOfElements(RpTeamDictionary* dictionary);
RpTeamDictionary* RpTeamDictionarySetLODElement(RpTeamDictionary* dictionary, RpAtomic* atomic, RpTeamElementType type, u32 lodIndex, u32 index);
u32 RpTeamGetNumberOfElements(RpTeam* team);
RpTeamPlayer* RpTeamGetPlayer(RpTeam* team, u32 index);
RpTeam* RpTeamLock(RpTeam* team, u32 lockMode);
RwRGBA* RpTeamMaterialGetPlayerColor(RpMaterial* material, RpTeamPlayer* player);
RwTexture* RpTeamMaterialGetPlayerTexture(RpMaterial* material, RpTeamPlayer* player);
RpMaterial* RpTeamMaterialSetPlayerColor(RpMaterial* material, RpTeamPlayer* player, RwRGBA* color);
RpMaterial* RpTeamMaterialSetPlayerDualTexture(RpMaterial* material, RpTeamPlayer* player, RwTexture* texture);
RpMaterial* RpTeamMaterialSetPlayerTexture(RpMaterial* material, RpTeamPlayer* player, RwTexture* texture);
s32 RpTeamPlayerGetActivity(RpTeamPlayer* player);
RwSphere* RpTeamPlayerGetBoundingSphere(RpTeamPlayer* player);
RwFrame* RpTeamPlayerGetHierarchyFrame(RpTeamPlayer* player);
RpTeamPlayer* RpTeamPlayerSetActivity(RpTeamPlayer* player, s32 active);
RpTeamPlayer* RpTeamPlayerSetCurrentLOD(RpTeamPlayer* player, u32 lod);
RpTeamPlayer* RpTeamPlayerSetElement(RpTeamPlayer* player, u32 index, u32 dictionaryIndex);
RpTeamPlayer* RpTeamPlayerSetHierarchyFrame(RpTeamPlayer* player, RwFrame* frame);
RpTeamPlayer* RpTeamPlayerSetRenderCallBack(RpTeamPlayer* player, RpAtomic** preCallBack, RpAtomic** postCallBack, void* data);
RpTeamPlayer* RpTeamPlayerSetShadows(RpTeamPlayer* player, s32 active);
RpTeamPlayer* RpTeamPlayerSetSyncLODPerFrame(RpTeamPlayer* player, s32 syncLODPerFrame);
s32 RpTeamPluginAttach(void);
RpTeam* RpTeamRender(RpTeam* team, u32 flags);
RpTeam* RpTeamSetCameraTestSphereCallBack(RpTeam* team, RwFrustumTestResult* callBack, void* data);
RpTeam* RpTeamSetDictionary(RpTeam* team, RpTeamDictionary* dictionary);
RpTeam* RpTeamSetLODFarRange(RpTeam* team, f32 farRange);
RpTeam* RpTeamSetPersistentLights(RpTeam* team, RpLight* directional, RpLight* ambient);
RpTeam* RpTeamSetShadows(RpTeam* team, RpTeamShadows* shadows);
RpTeam* RpTeamUnlock(RpTeam* team);
s32 RpUserDataArrayGetNumElements(RpUserDataArray* userData);
char* RpUserDataArrayGetString(RpUserDataArray* userData, s32 index);
s32 RpUserDataGetFormatSize(RpUserDataFormat format);
s32 RpUserDataPluginAttach(void);
RpWorld* RpWorldAddAtomic(RpWorld* world, RpAtomic* atomic);
RpWorld* RpWorldAddCamera(RpWorld* world, RwCamera* camera);
RpWorld* RpWorldAddClump(RpWorld* world, RpClump* clump);
RpWorld* RpWorldAddLight(RpWorld* world, RpLight* light);
RpWorld* RpWorldCreate(RwBBox* boundingBox);
s32 RpWorldDestroy(RpWorld* world);
RpWorld* RpWorldForAllWorldSectors(RpWorld* world, RpWorldSector** fpCallBack, void* pData);
RpWorld* RpWorldLock(RpWorld* world);
s32 RpWorldPluginAttach(void);
s32 RpWorldRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
s32 RpWorldRegisterPluginStream(u32 pluginID, RwStream** readCB, RwStream** writeCB, s32* getSizeCB);
RpWorld* RpWorldRemoveCamera(RpWorld* world, RwCamera* camera);
RpWorld* RpWorldRemoveLight(RpWorld* world, RpLight* light);
RpWorld* RpWorldRender(RpWorld* world);
RpWorld* RpWorldSectorGetWorld(RpWorldSector* sector);
void RpWorldSectorPS2AllFrustumTestFunc(RpWorldSector* sector, RwFrustumTestResult* inFrustum);
s32 RpWorldSectorPS2AllInstance(RxPS2AllPipeData* ps2AllPipeData);
s32 RpWorldSectorPS2AllObjectSetupCallBack(RxPS2AllPipeData* ps2AllPipeData, RwMatrixTag** transform);
s32 RpWorldSectorRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
s32 RpWorldSectorRegisterPluginStream(u32 pluginID, RwStream** readCB, RwStream** writeCB, s32* getSizeCB);
RpWorldSector* RpWorldSectorRender(RpWorldSector* sector);
s32 RpWorldSectorSetStreamAlwaysCallBack(u32 pluginID, s32* alwaysCB);
s32 RpWorldSectorSetStreamRightsCallBack(u32 pluginID, s32* rightsCB);
RxPipeline* RpWorldSetDefaultSectorPipeline(RxPipeline* pipeline);
RpWorld* RpWorldUnlock(RpWorld* world);
s32 Rt2dCTMPop(void);
s32 Rt2dCTMPush(void);
s32 Rt2dCTMScale(f32 x, f32 y);
s32 Rt2dCTMTranslate(f32 x, f32 y);
void Rt2dClose(void);
s32 Rt2dDeviceGetStep(RwV2d* xstep, RwV2d* ystep, RwV2d* origin);
s32 Rt2dDeviceSetCamera(RwCamera* cam);
s32 Rt2dDeviceSetFlat(f32 r);
s32 Rt2dDeviceSetMetric(f32 x, f32 y, f32 w, f32 h);
s32 Rt2dFontDestroy(Rt2dFont* font);
f32 Rt2dFontGetStringWidth(Rt2dFont* font, char* string, f32 height);
char* Rt2dFontSetPath(char* path);
s32 Rt2dFontSetReadCallBack(Rt2dFont** fpCallBack);
void Rt2dOpen(RwCamera* cam);
Rt2dPath* Rt2dPathClose(Rt2dPath* path);
Rt2dPath* Rt2dPathCreate(void);
Rt2dPath* Rt2dPathCurveto(Rt2dPath* path, f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3);
s32 Rt2dPathDestroy(Rt2dPath* path);
Rt2dPath* Rt2dPathLineto(Rt2dPath* path, f32 x, f32 y);
Rt2dPath* Rt2dPathLock(Rt2dPath* path);
Rt2dPath* Rt2dPathMoveto(Rt2dPath* path, f32 x, f32 y);
Rt2dPath* Rt2dPathStroke(Rt2dPath* path, Rt2dBrush* brush);
Rt2dPath* Rt2dPathUnlock(Rt2dPath* path);
s32 RtAnimAnimationDestroy(RtAnimAnimation* animation);
RtAnimAnimation* RtAnimAnimationStreamRead(RwStream* stream);
RtAnimInterpolatorInfo* RtAnimGetInterpolatorInfo(s32 typeID);
s32 RtAnimInitialize(void);
s32 RtAnimInterpolatorAddAnimTime(RtAnimInterpolator* interp, f32 time);
RtAnimInterpolator* RtAnimInterpolatorCreate(s32 numNodes, s32 maxInterpKeyFrameSize);
void RtAnimInterpolatorDestroy(RtAnimInterpolator* anim);
void RtAnimInterpolatorSetAnimCallBack(RtAnimInterpolator* anim, RtAnimInterpolator** callBack, f32 time, void* data);
void RtAnimInterpolatorSetAnimLoopCallBack(RtAnimInterpolator* anim, RtAnimInterpolator** callBack, void* data);
s32 RtAnimInterpolatorSetCurrentAnim(RtAnimInterpolator* animI, RtAnimAnimation* anim);
s32 RtAnimInterpolatorSetCurrentTime(RtAnimInterpolator* anim, f32 time);
s32 RtAnimInterpolatorSetKeyFrameCallBacks(RtAnimInterpolator* anim, s32 keyFrameTypeID);
s32 RtAnimInterpolatorSubAnimTime(RtAnimInterpolator* interp, f32 time);
s32 RtAnimRegisterInterpolationScheme(RtAnimInterpolatorInfo* interpInfo);
RtFileSystem* RtFSManagerGetFileSystemFromFileName(char* fileName);
RtQuat* RtQuatRotate(RtQuat* quat, RwV3d* axis, f32 angle, RwOpCombineType combineOp);
RwBBox* RwBBoxCalculate(RwBBox* boundBox, RwV3d* verts, s32 numVerts);
RwCamera* RwCameraCalcPixelRay(RwCamera* camera, RwLine* line, RwV2d* pixel);
RwCamera* RwCameraCreate(void);
s32 RwCameraDestroy(RwCamera* camera);
RwCamera* RwCameraForAllSectorsInFrustum(RwCamera* camera, RpWorldSector** callback, void* data);
s32 RwCameraRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
s32 RwCameraRegisterPluginStream(u32 pluginID, RwStream** readCB, RwStream** writeCB, s32* getSizeCB);
RwCamera* RwCameraSetFarClipPlane(RwCamera* camera, f32 farClip);
RwCamera* RwCameraSetNearClipPlane(RwCamera* camera, f32 nearClip);
RwCamera* RwCameraSetViewOffset(RwCamera* camera, RwV2d* offset);
RwCamera* RwCameraShowRaster(RwCamera* camera, void* dev, u32 flags);
RwCamera* RwCameraStreamRead(RwStream* stream);
s32 RwEngineClose(void);
s32 RwEngineGetCurrentVideoMode(void);
s32 RwEngineGetNumVideoModes(void);
s32 RwEngineGetPluginOffset(u32 pluginID);
RwVideoMode* RwEngineGetVideoModeInfo(RwVideoMode* modeinfo, s32 modeIndex);
s32 RwEngineOpen(RwEngineOpenParams* initParams);
s32 RwEngineRegisterPlugin(s32 size, u32 pluginID, void** initCB, void** termCB);
s32 RwEngineSetMatrixTolerances(RwMatrixTolerance* tolerance);
s32 RwEngineSetVideoMode(s32 modeIndex);
s32 RwEngineStart(void);
s32 RwEngineStop(void);
s32 RwEngineTerm(void);
RwError* RwErrorGet(RwError* code);
RwError* RwErrorSet(RwError* code);
s32 RwFclose(void* fptr);
s32 RwFeof(void* fptr);
s32 RwFexist(char* name);
char* RwFgets(char* buffer, s32 maxLen, void* fptr);
void* RwFopen(char* name, char* access);
RwFrame* RwFrameAddChild(RwFrame* parent, RwFrame* child);
RwFrame* RwFrameAddChildNoUpdate(RwFrame* parent, RwFrame* child);
RwFrame* RwFrameCreate(void);
s32 RwFrameDestroy(RwFrame* frame);
s32 RwFrameDestroyHierarchy(RwFrame* frame);
s32 RwFrameDirty(RwFrame* frame);
RwFrame* RwFrameForAllChildren(RwFrame* frame, RwFrame** callBack, void* data);
RwFrame* RwFrameGetRoot(RwFrame* frame);
RwFrame* RwFrameOrthoNormalize(RwFrame* frame);
s32 RwFrameRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
s32 RwFrameRegisterPluginStream(u32 pluginID, RwStream** readCB, RwStream** writeCB, s32* getSizeCB);
RwFrame* RwFrameRemoveChild(RwFrame* child);
RwFrame* RwFrameRotate(RwFrame* frame, RwV3d* axis, f32 angle, RwOpCombineType combineOp);
RwFrame* RwFrameScale(RwFrame* frame, RwV3d* scale, RwOpCombineType combineOp);
RwFrame* RwFrameSetIdentity(RwFrame* frame);
RwFrame* RwFrameTranslate(RwFrame* frame, RwV3d* translation, RwOpCombineType combineOp);
RwFrame* RwFrameUpdateObjects(RwFrame* frame);
u32 RwFread(void* addr, u32 size, u32 count, void* fptr);
RwFreeList* RwFreeListCreate(s32 entrySize, s32 entriesPerBlock, s32 alignment, u32 hint);
RwFreeList* RwFreeListCreateAndPreallocateSpace(s32 entrySize, s32 entriesPerBlock, s32 alignment, s32 numBlocksToPreallocate, RwFreeList* inPlaceSpaceForFreeListStruct, u32 hint);
s32 RwFreeListDestroy(RwFreeList* freeList);
RwFreeList* RwFreeListForAllUsed(RwFreeList* freeList, void* fpCallBack, void* pData);
s32 RwFreeListPurge(RwFreeList* freeList);
s32 RwFreeListPurgeAllFreeLists(void);
s32 RwFseek(void* fptr, s64 offset, s32 origin);
s32 RwFtell(void* fptr);
u32 RwFwrite(void* addr, u32 size, u32 count, void* fptr);
s32 RwIm3DEnd(void);
s32 RwIm3DPS2AllBridgeCallBack(RxPS2AllPipeData* ps2AllPipeData);
void RwIm3DPS2AllGetMeshHeaderMeshCacheFunc(_rwIm3DPoolStash* stash, RxPS2AllPipeData* ps2AllPipeData);
s32 RwIm3DPS2AllInstance(RxPS2AllPipeData* ps2AllPipeData);
s32 RwIm3DPS2AllInstanceCallBack(RxPS2AllPipeData* ps2AllPipeData);
s32 RwIm3DPS2AllObjectSetupCallBack(RxPS2AllPipeData* ps2AllPipeData, RwMatrixTag** transform);
s32 RwIm3DPS2AllPostMeshCallBack(void);
RwResEntry* RwIm3DPS2AllResEntryAllocCallBack(RxPS2AllPipeData* ps2AllPipeData, RwResEntry** repEntry, u32 size, void* destroyCallBack);
s32 RwIm3DRenderIndexedPrimitive(RwPrimitiveType primType, u16* indices, s32 numIndices);
s32 RwIm3DRenderPrimitive(RwPrimitiveType primType);
RxPipeline* RwIm3DSetRenderPipeline(RxPipeline* pipeline, RwPrimitiveType primType);
RxPipeline* RwIm3DSetTransformPipeline(RxPipeline* pipeline);
RwImage* RwImageAllocatePixels(RwImage* image);
RwImage* RwImageApplyMask(RwImage* image, RwImage* mask);
RwImage* RwImageCopy(RwImage* destImage, RwImage* sourceImage);
RwImage* RwImageCreate(s32 width, s32 height, s32 depth);
RwImage* RwImageCreateResample(RwImage* srcImage, s32 width, s32 height);
char* RwImageFindFileType(char* imageName);
RwImage* RwImageFindRasterFormat(RwImage* ipImage, s32 nRasterType, s32* npWidth, s32* npHeight, s32* npDepth, s32* npFormat);
RwImage* RwImageFreePixels(RwImage* image);
RwImage* RwImageGammaCorrect(RwImage* image);
RwImage* RwImageMakeMask(RwImage* image);
RwImage* RwImageReadMaskedImage(char* imageName, char* maskName);
RwImage* RwImageResample(RwImage* dstImage, RwImage* srcImage);
RwImage* RwImageSetFromRaster(RwImage* image, RwRaster* raster);
s32 RwImageSetGamma(f32 gammaValue);
char* RwImageSetPath(char* path);
RwMatrixTag* RwMatrixCreate(void);
s32 RwMatrixDestroy(RwMatrixTag* matrix);
RwMatrixTag* RwMatrixInvert(RwMatrixTag* dst, RwMatrixTag* src);
RwMatrixTag* RwMatrixOrthoNormalize(RwMatrixTag* dst, RwMatrixTag* src);
RwMatrixTag* RwMatrixRotateOneMinusCosineSine(RwMatrixTag* matrix, RwV3d* unitAxis, f32 oneMinusCosine, f32 sine, RwOpCombineType combineOp);
RwMatrixTag* RwMatrixTransform(RwMatrixTag* matrix, RwMatrixTag* transform, RwOpCombineType combineOp);
void RwPalQuantAddImage(RwPalQuant* pq, RwImage* img, f32 weight);
s32 RwPalQuantInit(RwPalQuant* pq);
void RwPalQuantMatchImage(u8* dstpixels, s32 dststride, s32 dstdepth, s32 dstPacked, RwPalQuant* pq, RwImage* img);
s32 RwPalQuantResolvePalette(RwRGBA* palette, s32 maxcols, RwPalQuant* pq);
void RwPalQuantTerm(RwPalQuant* pq);
RwRGBA* RwRGBASetFromPixel(RwRGBA* rgbOut, u32 pixelValue, s32 rasterFormat);
u32 RwRGBAToPixel(RwRGBA* rgbIn, s32 rasterFormat);
s32 RwRasterDestroy(RwRaster* raster);
s32 RwRasterGetNumLevels(RwRaster* raster);
u8* RwRasterLock(RwRaster* raster, u8 level, s32 lockMode);
u8* RwRasterLockPalette(RwRaster* raster, s32 lockMode);
s32 RwRasterRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
RwRaster* RwRasterShowRaster(RwRaster* raster, void* dev, u32 flags);
RwRaster* RwRasterSubRaster(RwRaster* subRaster, RwRaster* raster, RwRect* rect);
RwRaster* RwRasterUnlock(RwRaster* raster);
RwRaster* RwRasterUnlockPalette(RwRaster* raster);
RwResEntry* RwResourcesAllocateResEntry(void* owner, RwResEntry** ownerRef, s32 size, void* destroyNotify);
s32 RwResourcesEmptyArena(void);
s32 RwResourcesFreeResEntry(RwResEntry* entry);
s32 RwResourcesGetArenaSize(void);
s32 RwResourcesGetArenaUsage(void);
s32 RwStreamClose(RwStream* stream, void* pData);
s32 RwStreamFindChunk(RwStream* stream, u32 type, u32* lengthOut, u32* versionOut);
RwStream* RwStreamOpen(RwStreamType type, RwStreamAccessType accessType, void* pData);
u32 RwStreamRead(RwStream* stream, void* buffer, u32 length);
RwStream* RwStreamReadInt32(RwStream* stream, s32* ints, u32 numBytes);
RwStream* RwStreamReadReal(RwStream* stream, f32* reals, u32 numBytes);
RwStream* RwStreamSkip(RwStream* stream, u32 offset);
RwStream* RwStreamWrite(RwStream* stream, void* buffer, u32 length);
RwStream* RwStreamWriteInt32(RwStream* stream, s32* ints, u32 numBytes);
RwStream* RwStreamWriteReal(RwStream* stream, f32* reals, u32 numBytes);
RwTexture* RwTexDictionaryAddTexture(RwTexDictionary* dict, RwTexture* texture);
RwTexDictionary* RwTexDictionaryCreate(void);
s32 RwTexDictionaryDestroy(RwTexDictionary* dict);
RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* dict, char* name);
s32 RwTexDictionaryForAllTexDictionaries(RwTexDictionary** fpCallBack, void* pData);
RwTexDictionary* RwTexDictionaryForAllTextures(RwTexDictionary* dict, RwTexture** fpCallBack, void* pData);
RwTexDictionary* RwTexDictionaryGetCurrent(void);
RwTexture* RwTexDictionaryRemoveTexture(RwTexture* texture);
RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* dict);
u32 RwTexDictionaryStreamGetSize(RwTexDictionary* texDict);
RwTexDictionary* RwTexDictionaryStreamRead(RwStream* stream);
RwTexDictionary* RwTexDictionaryStreamWrite(RwTexDictionary* texDict, RwStream* stream);
RwTexture* RwTextureCreate(RwRaster* raster);
s32 RwTextureDestroy(RwTexture* texture);
s32 RwTextureGenerateMipmapName(char* name, char* maskName, u8 mipLevel, s32 format);
s32 RwTextureGetAutoMipmapping(void);
RwTexture** RwTextureGetFindCallBack(void);
s32 RwTextureGetMipmapping(void);
RwTexture** RwTextureGetReadCallBack(void);
s32 RwTextureRasterGenerateMipmaps(RwRaster* raster, RwImage* image);
RwTexture* RwTextureRead(char* name, char* maskName);
s32 RwTextureRegisterPlugin(s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
s32 RwTextureRegisterPluginStream(u32 pluginID, RwStream** readCB, RwStream** writeCB, s32* getSizeCB);
s32 RwTextureSetAutoMipmapping(s32 enable);
s32 RwTextureSetFindCallBack(RwTexture** callBack);
RwTexture* RwTextureSetMaskName(RwTexture* texture, char* maskName);
s32 RwTextureSetMipmapping(s32 enable);
RwTexture* RwTextureSetName(RwTexture* texture, char* name);
s32 RwTextureSetReadCallBack(RwTexture** callBack);
u32 RwTextureStreamGetSize(RwTexture* texture);
RwTexture* RwTextureStreamRead(RwStream* stream);
RwTexture* RwTextureStreamWrite(RwTexture* texture, RwStream* stream);
void RwV3dSetZero(RwV3d* in);
RwV3d* RwV3dTransformPoints(RwV3d* pointsOut, RwV3d* pointsIn, s32 numPoints, RwMatrixTag* matrix);
RwV3d* RwV3dTransformVector(RwV3d* vectorOut, RwV3d* vectorIn, RwMatrixTag* matrix);
RwV3d* RwV3dTransformVectors(RwV3d* vectorsOut, RwV3d* vectorsIn, s32 numPoints, RwMatrixTag* matrix);
RxHeap* RxHeapCreate(u32 size);
void RxHeapDestroy(RxHeap* heap);
void RxHeapFree(RxHeap* heap, void* block);
RxHeap* RxHeapGetGlobalHeap(void);
RxPipeline* RxLockedPipeAddFragment(RxPipeline* pipeline, u32* firstIndex, RxNodeDefinition* nodeDef0);
RxPipeline* RxLockedPipeAddPath(RxPipeline* pipeline, u32* out, RxPipelineNode* in);
RxPipeline* RxLockedPipeUnlock(RxPipeline* pipeline);
RxNodeDefinition* RxNodeDefinitionGetPS2All(void);
RxNodeDefinition* RxNodeDefinitionGetPS2AllMat(void);
RxPipeline* RxPipelineCreate(void);
RxPipeline* RxPipelineExecute(RxPipeline* pipeline, void* data, s32 heapReset);
RxPipelineNode* RxPipelineFindNodeByName(RxPipeline* pipeline, char* name, RxPipelineNode* start, s32* nodeIndex);
RxPipeline* RxPipelineLock(RxPipeline* pipeline);
void* RxPipelineNodeCreateInitData(RxPipelineNode* node, u32 size);
void* RxPipelineNodeGetInitData(RxPipelineNode* node);
void RxPipelineNodePS2AllApplyLight(RpLight* light, RwMatrixTag* inverseMat, f32 invScale, f32 recipInvScale);
RxPipelineNode* RxPipelineNodePS2AllGroupMeshes(RxPipelineNode* self, RxPipeline* pipe);
RxPipelineNode* RxPipelineNodePS2AllMatGenerateCluster(RxPipelineNode* self, RxClusterDefinition* cluster2generate, u32 type);
RxPipelineNode* RxPipelineNodePS2AllMatSetCallBack(RxPipelineNode* self, RxPipelineNodePS2AllMatCallBackType type, void* func);
RxPipelineNode* RxPipelineNodePS2AllMatSetLineVUBufferSizes(RxPipelineNode* self, s32 strideOfInputVertex, s32 vuLSVertexMaxCount, s32 vuLLLineMaxCount);
RxPipelineNode* RxPipelineNodePS2AllMatSetPointListVUBufferSize(RxPipelineNode* self, s32 strideOfInputVertex, s32 vuPLVertexMaxCount);
RxPipelineNode* RxPipelineNodePS2AllMatSetTriangleVUBufferSizes(RxPipelineNode* self, s32 strideOfInputVertex, s32 vuTSVertexMaxCount, s32 vuTLTriMaxCount);
RxPipelineNode* RxPipelineNodePS2AllMatSetVIFOffset(RxPipelineNode* self, s32 vifOffset);
RxPipelineNode* RxPipelineNodePS2AllMatSetVU1CodeArray(RxPipelineNode* self, void** vu1CodeArray, u32 length);
RxPipelineNode* RxPipelineNodePS2AllSetCallBack(RxPipelineNode* self, RxPipelineNodePS2AllCallBackType type, void* func);
RxRenderStateVector* RxRenderStateVectorSetDefaultRenderStateVector(RxRenderStateVector* rsvp);
RpLight* _rpAtomicPS2AllDoApplyLight(RpLight* light, void* pData);
void _rpAtomicResyncInterpolatedSphere(RpAtomic* atomic);
void* _rpBinaryWorldClose(void* instance);
void* _rpBinaryWorldOpen(void* instance);
RpBuildMesh* _rpBuildMeshAddTriangle(RpBuildMesh* mesh, RpMaterial* material, s32 vert1, s32 vert2, s32 vert3, u16 matIndex, u16 textureIndex, u16 rasterIndex, u16 pipelineIndex);
RpBuildMesh* _rpBuildMeshCreate(u32 bufferSize);
s32 _rpBuildMeshDestroy(RpBuildMesh* mesh);
void* _rpClumpClose(void* instance);
void* _rpClumpOpen(void* instance, s32 offset);
s32 _rpClumpRegisterExtensions(void);
s32 _rpCreatePlatformAtomicPipelines(void);
s32 _rpCreatePlatformMaterialPipelines(void);
s32 _rpCreatePlatformWorldSectorPipelines(void);
s32 _rpDMorphAtomicPluginAttach(void);
s32 _rpDMorphGeometryPluginAttach(void);
RpAtomic* _rpDMorphPipelinesAttach(RpAtomic* atomic);
s32 _rpDMorphPipelinesCreate(void);
s32 _rpDMorphPipelinesDestroy(void);
void _rpDestroyPlatformAtomicPipelines(void);
void _rpDestroyPlatformMaterialPipelines(void);
void _rpDestroyPlatformWorldSectorPipelines(void);
void* _rpGeometryClose(void* instance);
RpGeometry* _rpGeometryNativeRead(RwStream* stream, RpGeometry* geometry);
s32 _rpGeometryNativeSize(RpGeometry* geometry);
RwStream* _rpGeometryNativeWrite(RwStream* stream, RpGeometry* geometry);
void* _rpGeometryOpen(void* instance, s32 offset);
void* _rpLightClose(void* instance);
void* _rpLightOpen(void* instance, s32 offset);
s32 _rpLightTieDestroy(RpLightTie* tie);
void _rpMatFXMaterialSkyDualSetBlend(RpMaterial* material);
void _rpMatFXMaterialSkyEnvMapSetBlend(RpMaterial* material);
void _rpMatFXMaterialSkyInitialize(RpMaterial* material);
RpAtomic* _rpMatFXPipelineAtomicSetup(RpAtomic* atomic);
RpWorldSector* _rpMatFXPipelineWorldSectorSetup(RpWorldSector* worldSector);
s32 _rpMatFXPipelinesCreate(void);
s32 _rpMatFXPipelinesDestroy(void);
RwTexture* _rpMatFXSetupBumpMapTexture(RwTexture* baseTexture, RwTexture* effectTexture);
s32 _rpMatFXSetupDualRenderState(void);
RwStream* _rpMatFXStreamReadTexture(RwStream* stream, RwTexture** texture);
RwTexture* _rpMatFXTextureMaskCreate(RwTexture* baseTexture, RwTexture* maskTexture);
void* _rpMaterialClose(void* instance);
s32 _rpMaterialListAppendMaterial(RpMaterialList* matList, RpMaterial* material);
RpMaterialList* _rpMaterialListDeinitialize(RpMaterialList* matList);
s32 _rpMaterialListFindMaterialIndex(RpMaterialList* matList, RpMaterial* material);
RpMaterial* _rpMaterialListGetMaterial(RpMaterialList* matList, s32 matIndex);
RpMaterialList* _rpMaterialListInitialize(RpMaterialList* matList);
RpMaterialList* _rpMaterialListStreamRead(RwStream* stream, RpMaterialList* matList);
void* _rpMaterialOpen(void* instance, s32 offset);
void* _rpMeshClose(void* instance);
s32 _rpMeshDestroy(RpMeshHeader* mesh);
RpMeshHeader* _rpMeshHeaderCreate(u32 size);
RpMeshHeader* _rpMeshHeaderForAllMeshes(RpMeshHeader* meshHeader, RpMesh** fpCallBack, void* pData);
void* _rpMeshOpen(void* instance, s32 offset);
RpMeshHeader* _rpMeshOptimise(RpBuildMesh* mesh, u32 flags);
RpMeshHeader* _rpMeshRead(RwStream* stream, void* object, RpMaterialList* matList);
s32 _rpMeshSize(RpMeshHeader* meshHeader, void* object);
RwStream* _rpMeshWrite(RpMeshHeader* meshHeader, void* object, RwStream* stream, RpMaterialList* matList);
RwStream* _rpReadAtomicRights(RwStream* s, s32 len);
RwStream* _rpReadMaterialRights(RwStream* s, s32 len);
RwStream* _rpReadSectRights(RwStream* s, s32 len);
RwStream* _rpReadWorldRights(RwStream* s, s32 len);
void* _rpSectorClose(void* instance);
RpWorldSector* _rpSectorDefaultRenderCallBack(RpWorldSector* sector);
void* _rpSectorOpen(void* instance);
s32 _rpSizeAtomicRights(void* obj);
s32 _rpSizeMaterialRights(void* obj);
s32 _rpSizeSectRights(void* obj);
s32 _rpSizeWorldRights(void* obj);
RpGeometry* _rpSkinDeinitialize(RpGeometry* geometry);
RwStream* _rpSkinGeometryNativeRead(RwStream* stream, RpGeometry* geometry);
s32 _rpSkinGeometryNativeSize(RpGeometry* geometry);
RwStream* _rpSkinGeometryNativeWrite(RwStream* stream, RpGeometry* geometry);
RpGeometry* _rpSkinInitialize(RpGeometry* geometry);
RpAtomic* _rpSkinPipelinesAttach(RpAtomic* atomic, RpSkinType type);
s32 _rpSkinPipelinesCreate(void);
s32 _rpSkinPipelinesDestroy(void);
s32 _rpSkinSplitDataDestroy(RpSkin* skin);
s32 _rpSkinSplitDataStreamGetSize(RpSkin* skin);
RwStream* _rpSkinSplitDataStreamRead(RwStream* stream, RpSkin* skin);
RwStream* _rpSkinSplitDataStreamWrite(RwStream* stream, RpSkin* skin);
s32 _rpSkyCreateFrameBufferRasters(void);
s32 _rpSkyDestroyFrameBufferRasters(void);
void _rpSkyFrameBufferRastersUpdate(void);
void _rpTeamAddTeamToList(RpTeam* team);
RwFrustumTestResult _rpTeamCameraCustomTestSphere(RwCamera* camera, RwSphere* sphere);
s32 _rpTeamDictionaryAtomicRights(void* object, u32 extraData);
RpTeamDictionaryElement* _rpTeamDictionaryDestroyLODElement(RpTeamDictionaryElement* element, u32 lodIndex);
RpTeamPlayer* _rpTeamDictionarySetElement(RpTeamPlayer* player, u32 playerIndex, u32 dictionaryIndex);
s32 _rpTeamMatFXPipelineCreate(void);
void _rpTeamMatFXPipelineDestroy(void);
void* _rpTeamMaterialConstructor(void* object);
void* _rpTeamMaterialCopy(void* dstObject, void* srcObject);
void* _rpTeamMaterialDestructor(void* object);
RpTeam* _rpTeamOptimizeCreate(RpTeam* team, u32 type);
RpTeam* _rpTeamOptimizeDestroy(RpTeam* team, u32 type, u32 locked);
RpTeamPlayer* _rpTeamPlayerDestroy(RpTeamPlayer* player);
u32 _rpTeamPlayerLODDefaultSelectLODCallBack(RpTeam* team, u32 playerIndex);
void _rpTeamRemoveTeamFromList(RpTeam* team);
RpTeam* _rpTeamRender(RpTeam* team);
RpTeam* _rpTeamSetElementTypeOptimized(RpTeam* team, u32 type, s32 optimized);
RwFrustumTestResult _rpTeamShadowCalcRenderData(RpTeamPlayer* player);
s32 _rpTeamShadowPipelineCreate(void);
void _rpTeamShadowPipelineDestroy(void);
RpAtomic* _rpTeamSkinAttachCustomPipeline(RpAtomic* atomic);
s32 _rpTeamSkinCustomPipelineCreate(void);
void _rpTeamSkinCustomPipelineDestroy(void);
RxPipeline* _rpTeamSkinGetCustomPipeline(void);
RwMatrixTag* _rpTeamSkinMatBlendUpdating(RpSkin* skin, RwFrame* frame, RpHAnimHierarchy* hierarchy, RwMatrixTag* pMBA);
RpAtomic* _rpTeamSkyAttachMaterialPipeline(RpAtomic* atomic, RpTeamElementType type);
RpAtomic* _rpTeamStaticAttachCustomPipeline(RpAtomic* atomic);
s32 _rpTeamStaticCustomPipelineCreate(void);
void _rpTeamStaticCustomPipelineDestroy(void);
RxPipeline* _rpTeamStaticGetCustomPipeline(void);
s32 _rpTieDestroy(RpTie* tie);
RpMeshHeader* _rpTriListMeshGenerate(RpBuildMesh* buildMesh);
s32 _rpWorldForAllGlobalLights(RpLight** callBack, void* pData);
s32 _rpWorldObjRegisterExtensions(void);
s32 _rpWorldPipeAttach(void);
void _rpWorldPipelineClose(void);
s32 _rpWorldPipelineOpen(void);
void _rpWorldSectorDeinstanceAll(RpSector* sector);
void _rpWorldSectorDestroyRecurse(RpSector* sector);
RpWorldSector* _rpWorldSectorForAllLocalLights(RpWorldSector* sector, RpLight** callBack, void* pData);
RpWorldSector* _rpWorldSectorNativeRead(RwStream* stream, RpWorldSector* sector);
s32 _rpWorldSectorNativeSize(RpWorldSector* sector);
RwStream* _rpWorldSectorNativeWrite(RwStream* stream, RpWorldSector* sector);
RpLight* _rpWorldSectorPS2AllDoApplyLight(RpLight* light);
void _rpWorldUnregisterWorld(RpWorld* world);
RwStream* _rpWriteAtomicRights(RwStream* s, void* obj);
RwStream* _rpWriteMaterialRights(RwStream* s, void* obj);
RwStream* _rpWriteSectRights(RwStream* s, void* obj);
RwStream* _rpWriteWorldRights(RwStream* s, void* obj);
void _rt2dBrushClose(void);
s32 _rt2dBrushOpen(void);
RwMatrixTag* _rt2dCTMGet(void);
void _rt2dFontClose(void);
s32 _rt2dFontOpen(void);
f32 _rt2dGetTolerance(void);
void _rt2dGstateClose(void);
s32 _rt2dGstateOpen(void);
void _rt2dObjectClose(void);
s32 _rt2dObjectOpen(void);
void _rt2dPS2PipeClose(void);
s32 _rt2dPS2PipeOpen(void);
void _rt2dPathClose(void);
s32 _rt2dPathOpen(void);
Rt2dPath* _rt2dPathOptimize(Rt2dPath* path);
Rt2dPath* _rt2dScratchPath(void);
Rt2dPath* _rt2dSubPathFlatten(Rt2dPath* flat, Rt2dPath* path);
void _rt2dTriangulateClose(void);
s32 _rt2dTriangulateOpen(void);
RtFile* _rtFSManagerFOpenOnFS(RtFileSystem* fs, char* fileName, RtFileAccessFlag access, void* CallBack, void* CallBackData);
RtFSManager* _rtGetFSManager(void);
void* _rwCameraClose(void* instance);
void* _rwCameraOpen(void* instance, s32 offset);
void* _rwChunkGroupClose(void* instance);
void* _rwChunkGroupOpen(void* instance, s32 offset);
void* _rwColorClose(void* instance);
void* _rwColorOpen(void* instance);
s32 _rwDMAAddImageUpload(s32 parallel, u32 size);
void _rwDMAAddPURef(s32* ptr);
void _rwDMAAddPkt(void* addr, u32 type);
void _rwDMAClosePkt(void);
void* _rwDMADMAPktAllocHigh(u32 size, s32 sprFlush);
void _rwDMADmaClose(void);
s32 _rwDMADmaOpen(void);
void _rwDMAForceBufferSwap(void);
s32 _rwDMAHook(void);
s32 _rwDMAOpenGIFPkt(u32 size);
s32 _rwDMAOpenVIFPkt(u32 type, u32 size);
s32 _rwDMAPreAlloc(u32 size, u16 puRefSize, void* optionalBuf);
void _rwDMAReqFlip(void* addr, u8 id);
void _rwDMAUnhook(void);
void _rwDMAUnhookPrimitive(void);
void _rwDMAWaitQueue(void);
RwDevice* _rwDeviceGetHandle(void);
s32 _rwDeviceRegisterPlugin(void);
s32 _rwDeviceSystemRequest(RwDevice* device, s32 requestID, void* pOut, void* pInOut, s32 numIn);
void* _rwErrorClose(void* object);
void* _rwErrorOpen(void* object, s32 offset);
RwFrame* _rwFrameCloneAndLinkClones(RwFrame* root);
void* _rwFrameClose(void* instance);
rwFrameList* _rwFrameListDeinitialize(rwFrameList* frameList);
rwFrameList* _rwFrameListStreamRead(RwStream* stream, rwFrameList* frameList);
void* _rwFrameOpen(void* instance, s32 offset);
RwFrame* _rwFramePurgeClone(RwFrame* root);
s32 _rwFrameSyncDirty(void);
void _rwFrameSyncHierarchyLTM(RwFrame* frame);
void* _rwFreeListAllocReal(RwFreeList* freeList, u32 hint);
void _rwFreeListEnable(s32 enabled);
RwFreeList* _rwFreeListFreeReal(RwFreeList* freeList, void* entry);
u32 _rwGetNumEngineInstances(void);
void* _rwIm3DClose(void* instance);
s32 _rwIm3DCreatePlatformRenderPipelines(void);
s32 _rwIm3DCreatePlatformTransformPipeline(void);
void _rwIm3DDestroyPlatformRenderPipelines(void);
void _rwIm3DDestroyPlatformTransformPipeline(void);
rwIm3DPool* _rwIm3DGetPool(void);
void* _rwIm3DOpen(void* instance, s32 offset);
void* _rwImageClose(void* instance);
rwImageAlphaType _rwImageFindAlphaType(RwImage* image);
void* _rwImageOpen(void* instance, s32 offset);
void* _rwMatrixClose(void* instance);
f32 _rwMatrixDeterminant(RwMatrixTag* matrix);
f32 _rwMatrixNormalError(RwMatrixTag* matrix);
void* _rwMatrixOpen(void* instance, s32 offset);
f32 _rwMatrixOrthogonalError(RwMatrixTag* matrix);
s32 _rwMatrixSetMultFn(void* multMat);
void _rwMemoryClose(void);
s32 _rwMemoryOpen(RwMemoryFunctions* memFuncs);
void _rwObjectHasFrameReleaseFrame(void* object);
void _rwObjectHasFrameSetFrame(void* object, RwFrame* frame);
s32 _rwPS2AllRabinsConstructionTimeCode(rxNodePS2AllMatPvtData* pvtData);
s32 _rwPipeAttach(void);
void _rwPipeInitForCamera(void);
s32 _rwPluginRegistryAddPlgnStrmRightsCB(RwPluginRegistry* reg, u32 pluginID, s32* rightsCB);
s32 _rwPluginRegistryAddPlgnStrmlwysCB(RwPluginRegistry* reg, u32 pluginID, s32* alwaysCB);
s32 _rwPluginRegistryAddPlugin(RwPluginRegistry* reg, s32 size, u32 pluginID, void** constructCB, void** destructCB, void** copyCB);
s32 _rwPluginRegistryAddPluginStream(RwPluginRegistry* reg, u32 pluginID, RwStream** readCB, RwStream** writeCB, s32* getSizeCB);
s32 _rwPluginRegistryClose(void);
RwPluginRegistry* _rwPluginRegistryCopyObject(RwPluginRegistry* reg, void* dstObject, void* srcObject);
RwPluginRegistry* _rwPluginRegistryDeInitObject(RwPluginRegistry* reg, void* object);
s32 _rwPluginRegistryGetPluginOffset(RwPluginRegistry* reg, u32 pluginID);
s32 _rwPluginRegistryGetSize(RwPluginRegistry* reg, void* object);
RwPluginRegistry* _rwPluginRegistryInitObject(RwPluginRegistry* reg, void* object);
RwPluginRegistry* _rwPluginRegistryInvokeRights(RwPluginRegistry* reg, u32 id, void* obj, u32 extraData);
s32 _rwPluginRegistryOpen(void);
RwPluginRegistry* _rwPluginRegistryReadDataChunks(RwPluginRegistry* reg, RwStream* stream, void* object);
RwPluginRegistry* _rwPluginRegistrySkipDataChunks(RwPluginRegistry* reg, RwStream* stream);
RwPluginRegistry* _rwPluginRegistryWriteDataChunks(RwPluginRegistry* reg, RwStream* stream, void* object);
void* _rwRasterClose(void* instance);
void* _rwRasterOpen(void* instance, s32 offset);
void* _rwRenderPipelineClose(void* instance);
void* _rwRenderPipelineOpen(void* instance, s32 offset);
void* _rwResHeapAlloc(void* resHeap, u32 size);
s32 _rwResHeapClose(void);
void _rwResHeapFree(void* memory);
s32 _rwResHeapInit(void* resHeap, u32 size);
void* _rwResourcesClose(void* instance);
void* _rwResourcesOpen(void* instance, s32 offset);
void _rwResourcesPurge(void);
RwSList* _rwSListCreate(s32 size, u32 hint);
s32 _rwSListDestroy(RwSList* sList);
void _rwSListEmpty(RwSList* sList);
void* _rwSListGetArray(RwSList* sList);
void* _rwSListGetEntry(RwSList* sList, s32 entry);
void* _rwSListGetNewEntries(RwSList* sList, s32 count, u32 hint);
void* _rwSListGetNewEntry(RwSList* sList, u32 hint);
s32 _rwSListGetNumEntries(RwSList* sList);
void* _rwSListToArray(RwSList* sList);
s32 _rwSkyFindMSB(u32 nInt);
s32 _rwSkyImageFindRasterFormat(void* pRaster, void* pImage, s32 flags);
s32 _rwSkyImageGetRaster(void* pImage, void* pRaster);
void _rwSkyInitConfigSystem(void);
void _rwSkyOverloadPipelines(void);
void _rwSkyPipeSetupForCamera(RwCamera* camera);
s32 _rwSkyPixelToRGB(void* pRGB, void* pPixel, s32 nFormat);
s32 _rwSkyRGBToPixel(void* pPixel, void* pCol, s32 nFormat);
s32 _rwSkyRasterClear(s32 nValue);
s32 _rwSkyRasterClearRect(void* pRect, s32 nValue);
s32 _rwSkyRasterFinaliseStart(void);
void _rwSkyRasterInitiateStop(void);
s32 _rwSkyRasterRender(void* pRas, void* pLoc);
s32 _rwSkyRasterRenderFast(void* pRas, void* pLoc);
s32 _rwSkyRasterRenderScaled(void* pRas, void* pRect);
s32 _rwSkyRasterSetContext(void* pRas);
s32 _rwSkyRasterSetImage(void* pRaster, void* pImage);
s32 _rwSkySetRenderState(RwRenderState nState, void* pParam);
void _rwSkyUnOverloadPipelines(void);
RwStream* _rwStreamInitialize(RwStream* stream, s32 rwOwned, RwStreamType type, RwStreamAccessType accessType, void* pData);
void* _rwStreamModuleClose(void* instance);
void* _rwStreamModuleOpen(void* instance, s32 offset);
s32 _rwStreamReadChunkHeader(RwStream* stream, u32* type, u32* length, u32* version, u32* buildNum);
RwStream* _rwStreamWriteVersionedChunkHeader(RwStream* stream, s32 type, s32 size, u32 version, u32 buildNum);
void _rwStringClose(void);
s32 _rwStringOpen(void);
char* _rwStringStreamFindAndRead(char* string, RwStream* stream);
u32 _rwStringStreamGetSize(char* string);
char* _rwStringStreamWrite(char* string, RwStream* stream);
void* _rwTextureClose(void* instance);
void* _rwTextureOpen(void* instance, s32 offset);
f32 _rwV3dNormalize(RwV3d* out, RwV3d* in);
void* _rwVectorClose(void* instance);
void* _rwVectorOpen(void* instance, s32 offset);
s32 _rwVectorSetMultFn(RwV3d** multPoint, RwV3d** multPoints, RwV3d** multVector, RwV3d** multVectors);
s32 _rwerror(s32 code);
void _rwfastIm3DPipesClose(void);
s32 _rwfastIm3DPipesOpen(void);
s32 _rwpathisabsolute(char* path);
void rpObjectDestroyMeshCache(RwMeshCache* meshCache);
RwMeshCache** rpObjectGetMeshCacheResize(RwMeshCache** meshCacheRef, u32 numMeshes);
u32* rpcCommandBegin(s32 n, _RespAct* f, void* user);
void rpcCommandEnd(void);
s32 rpcFlush(void);
_RespAct rpcGetAsync(_RpcResponse* resp);
_RespAct rpcGetCallback(_RpcResponse* resp);
_RespAct rpcGetL(_RpcResponse* resp);
_RespAct rpcGetSoundFree(_RpcResponse* resp);
_RespAct rpcGetSysInfo(_RpcResponse* resp);
s32 rpcInit(u32 idRpc);
s32 rpcReady(s32 retries, char* msg);
s32 rpcReset(s32 bWantCompletions);
s32 rpcWaitForResponse(char* caller);
void rpteam_render(void);
void* rw_calloc(u32 numObj, u32 sizeObj);
void rw_draw(void);
void rw_free(void* data);
void rw_gsImgXfer_LoadImg_Path2(void* pvSourceBmp, s32 eSrcGsPixelMode, s32 nSrcWidth, s32 nSrcHeight, s32 pGsMemDest64, s32 eDestGsPixelMode, s32 nDestWidth, s32 nDestX, s32 nDestY);
s32 rw_init2(void);
void* rw_malloc(u32 size);
void* rw_realloc(void* mem, u32 newSize);
RtAnimAnimation* rwutil_AnimLoadMem(void* pBuffer, u32 uSize);
void rwutil_AtomicRenderClippedToCamera(RpAtomic* pAtomic, RwCamera* pCamera);
RpAtomic* rwutil_AtomicSetAllMaterialColorAlpha(RpAtomic* poRpAtomic, void* pvData);
RpAtomic* rwutil_AtomicSetAllMaterialColors(RpAtomic* poRpAtomic, void* pvData);
RpAtomic* rwutil_CallBack_ClumpGetAtomic(RpAtomic* atomic, void* data);
RpAtomic* rwutil_CallBack_SetHierarchyForSkinAtomic(RpAtomic* atomic, void* data);
RpAtomic* rwutil_ClumpGetAtomic(RpClump* clump, u32 i);
RpHAnimHierarchy* rwutil_ClumpGetHierarchy(RpClump* clump);
RpClump* rwutil_ClumpLoad(char* filename);
RpClump* rwutil_ClumpLoadMem(void* buffer, u32 size);
void rwutil_ClumpRenderClippedToCamera(RpClump* pClump, u8 bFlash, RwCamera* pCamera);
RpDMorphAnimation* rwutil_DMorphAnimationLoadMem(void* buffer, u32 size);
void rwutil_Fast_RpHAnimUpdateHierarchyMatrices(RpHAnimHierarchy* pHierarchy);
void rwutil_Fast_RpHAnimUpdateHierarchyMatrices_Character(RpHAnimHierarchy* pHierarchy);
void rwutil_Fast_RpHAnimUpdateHierarchyMatrices_QuatKey(RpHAnimHierarchy* pHierarchy);
RwFrame* rwutil_GetHierarchyFrame_Recurse(RwFrame* frame, void* ptr);
RwTexDictionary* rwutil_LoadTextureDictionary(char* dictionaryName);
RwTexDictionary* rwutil_LoadTextureDictionaryMem(void* buffer, u32 size);
void rwutil_PrepClumpForExternalAnimation(RpClump* pClump);
void rwutil_PrepHierarchyForExternalAnimation(RpHAnimHierarchy* pHier);
RwTexture* rwutil_TextureCallBack(RwTexture* texture);
RwTexDictionary* rwutil_TextureDictionaryCallBack(RwTexDictionary* dict);
s32 RpShadowRasterDestroy(RwRaster* raster);
RwRaster* RpShadowRasterCreate(s32 size);
s32 RpShadowDestroy(RpShadow* shadow);
s32 RpShadowPluginAttach(void);
s32 RpPrjTexDestroy(RpPrjTex* prj);
RpPrjTex* RpPrjTexCreate(RpPrjTexParam* param);
s32 RpPrjTexPluginAttach(void);
s32 RpPatternTexDestroy(RpPatternTex* pat);
OBJ_CUSTOMRENDER* RpAtomicMCCGetCustomRenderCallBack(RpAtomic* pAtomic);
s32 RpAtomicMCCSetCustomRenderCallBack(RpAtomic* pAtomic, OBJ_CUSTOMRENDER* pOBJ);
s32* RpAtomicMCCGetUsrData(RpAtomic* pAtomic);
s32 RpAtomicMCCSetUsrData(RpAtomic* pAtomic, s32* pUserData, s32 size);
s32 RpAtomicMCCSetActive(RpAtomic* pAtomic, s32 active);
s32 RpAtomicMCCSetMaterialPointer(RpAtomic* pAtomic, RpMaterial* pMaterial);
s32 RpAtomicMCCSetColor(RpAtomic* pAtomic, RwRGBA* pColor);
RpMaterial* RpAtomicMCCGetMaterialPointer(RpAtomic* pAtomic);
RwRGBA* RpAtomicMCCGetColor(RpAtomic* pAtomic);
s32 RpAtomicMCCPluginAttach(void);
RpAtomic* RpMatFXAtomicDisableEffects(RpAtomic* atomic);
RpUVAnimAnimation* RpUVAnimStreamReadAnimation(RwStream* stream);
RpUVAnimAnimation* RpUVAnimReadAnimation(char* filename);
s32 RpUVAnimMatrixUpdate(RpUVAnimAnimation* anim, RwMatrixTag* matrix);
s32 RpUVAnimAnimationDestroy(RpUVAnimAnimation* anim);
s32 RpUVAnimAnimationSetTime(RpUVAnimAnimation* animation, f32 time);
s32 RpUVAnimAnimationAddTime(RpUVAnimAnimation* animation, f32 time);
s32 RtUVFrameKeyFrameRegister(void);
s32 RpUVFrameScrollKeyFrameStreamWrite(RtAnimAnimation* animation, RwStream* stream);
RtAnimAnimation* RpUVFrameScrollKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* animation);
s32 RpUVFrameScrollKeyFrameStreamGetSize(RtAnimAnimation* animation);
void RpUVFrameScrollKeyFrameMulRecip(void);
void RpUVFrameScrollKeyFrameAdd(void);
void RpUVFrameScrollKeyFrameInterpolate(void* voidOut, void* voidIn1);
void RpUVFrameScrollKeyFrameBlend(void* voidOut, void* voidIn1);
void RpUVFrameScrollKeyFrameToMatrix(void* matrix, void* voidFrame);
s32 RtUVScrollKeyFrameRegister(void);
s32 RpUVAnimScrollKeyFrameStreamWrite(RtAnimAnimation* animation, RwStream* stream);
RtAnimAnimation* RpUVAnimScrollKeyFrameStreamRead(RwStream* stream, RtAnimAnimation* animation);
s32 RpUVAnimScrollKeyFrameStreamGetSize(RtAnimAnimation* animation);
void RpUVAnimScrollKeyFrameMulRecip(void);
void RpUVAnimScrollKeyFrameAdd(void);
void RpUVAnimScrollKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, f32 time);
void RpUVAnimScrollKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, f32 alpha);
void RpUVAnimScrollKeyFrameToMatrix(void* matrix, void* voidFrame);
RpPrtStdEmitter* RpPrtAdvEmtTexStepCloneCBExtend(RpPrtStdEmitter* emt, void* data);

#endif // RW_H
