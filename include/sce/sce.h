#ifndef SCE_H
#define SCE_H

#include "type.h"
#include "sce/eekernel.h"
#include "sce/eeregs.h"
#include "sce/eestruct.h"
#include "sce/eetypes.h"
#include "sce/libcdvd.h"
#include "sce/libdbc.h"
#include "sce/libmc2.h"
#include "sce/libpad.h"
#include "sce/sifdev.h"
#include "sce/sifrpc.h"

typedef struct _sceDmaTag _sceDmaTag;
// 16 bytes
struct _sceDmaTag
{
    u16 qwc;          // 0x00
    u8 mark;          // 0x02
    u8 id;            // 0x03
    _sceDmaTag* next; // 0x04
    u32 p[2];         // 0x08
};

// 16 bytes
typedef struct _sif_rpc_data
{
    void* paddr; // 0x00
    u32 pid;     // 0x04
    s32 tid;     // 0x08
    u32 mode;    // 0x0c
} _sif_rpc_data;

typedef struct _sif_serve_data _sif_serve_data;
// 40 bytes
typedef struct _sif_client_data
{
    _sif_rpc_data rpcd;     // 0x00
    u32 command;            // 0x10
    void* buff;             // 0x14
    void* gp;               // 0x18
    void* func;             // 0x1c
    void* para;             // 0x20
    _sif_serve_data* serve; // 0x24
} _sif_client_data;

// 88 bytes
typedef struct _sif_module_t
{
    char filename[80]; // 0x00
    u32 arg_cnt;       // 0x50
    char* parg;        // 0x54
} _sif_module_t;

typedef struct _sif_queue_data _sif_queue_data;
// 24 bytes
struct _sif_queue_data
{
    s32 key;                // 0x00
    s32 active;             // 0x04
    _sif_serve_data* link;  // 0x08
    _sif_serve_data* start; // 0x0c
    _sif_serve_data* end;   // 0x10
    _sif_queue_data* next;  // 0x14
};

// 68 bytes
struct _sif_serve_data
{
    u32 command;              // 0x00
    void** func;              // 0x04
    void* buff;               // 0x08
    s32 size;                 // 0x0c
    void** cfunc;             // 0x10
    void* cbuff;              // 0x14
    s32 csize;                // 0x18
    _sif_client_data* client; // 0x1c
    void* paddr;              // 0x20
    u32 fno;                  // 0x24
    void* receive;            // 0x28
    s32 rsize;                // 0x2c
    s32 rmode;                // 0x30
    u32 rid;                  // 0x34
    _sif_serve_data* link;    // 0x38
    _sif_serve_data* next;    // 0x3c
    _sif_queue_data* base;    // 0x40
};

// 8 bytes
typedef struct sceDNAS2Data
{
    void* ptr; // 0x00
    s32 size;  // 0x04
} sceDNAS2Data;

// 16 bytes
typedef struct sceDNAS2Status
{
    s32 code;       // 0x00
    s32 sub_code;   // 0x04
    s32 progress;   // 0x08
    void* optional; // 0x0c
} sceDNAS2Status;

// 8 bytes
typedef struct sceDNAS2Timeout_info
{
    s32 timeout;  // 0x00
    s32 priority; // 0x04
} sceDNAS2Timeout_info;

// 20 bytes
typedef struct sceDNAS2TitleAuthInfo
{
    s32 line_type;            // 0x00
    sceDNAS2Data pass_phrase; // 0x04
    sceDNAS2Data auth_data;   // 0x0c
} sceDNAS2TitleAuthInfo;

// 16 bytes
typedef struct sceDNAS2UniqueID
{
    u32 category; // 0x00
    void* ptr;    // 0x04
    s32* sizep;   // 0x08
    s32 result;   // 0x0c
} sceDNAS2UniqueID;

// 20 bytes
typedef struct sceDmaEnv
{
    u8 sts;      // 0x00
    u8 std;      // 0x01
    u8 mfd;      // 0x02
    u8 rcycle;   // 0x03
    u16 express; // 0x04
    u16 notify;  // 0x06
    u16 sqwc;    // 0x08
    u16 tqwc;    // 0x0a
    void* rbadr; // 0x0c
    u32 rbmsk;   // 0x10
} sceDmaEnv;

// 4 bytes
typedef struct sceEENetInAddr
{
    u32 s_addr; // 0x00
} sceEENetInAddr;

// 12 bytes
typedef struct sceEENetCtlStatDhcp
{
    s32 phase;                  // 0x00
    s32 lease_duration;         // 0x04
    sceEENetInAddr server_addr; // 0x08
} sceEENetCtlStatDhcp;

// 508 bytes
typedef struct sceEENetCtlStatPpp
{
    s32 ppp_phase;          // 0x00
    s32 modem_phase;        // 0x04
    s32 redial_count;       // 0x08
    char phone_number[256]; // 0x0c
    char status_string[80]; // 0x10c
    char last_string[32];   // 0x15c
    char auth_message[128]; // 0x17c
} sceEENetCtlStatPpp;

// 136 bytes
typedef struct sceEENetCtlStatPppoe
{
    s32 ppp_phase;          // 0x00
    s32 pppoe_phase;        // 0x04
    char auth_message[128]; // 0x08
} sceEENetCtlStatPppoe;

// 32 bytes
typedef struct sceEENetFdSet
{
    s32 fds_bits[8]; // 0x00
} sceEENetFdSet;

// 20 bytes
typedef struct sceEENetHostent
{
    char* h_name;       // 0x00
    char** h_aliases;   // 0x04
    s32 h_addrtype;     // 0x08
    s32 h_length;       // 0x0c
    char** h_addr_list; // 0x10
} sceEENetHostent;

// 16 bytes
typedef struct sceEENetIfname
{
    char ifn_name[16]; // 0x00
} sceEENetIfname;

// 16 bytes
typedef struct sceEENetSockaddr
{
    u8 sa_len;        // 0x00
    u8 sa_family;     // 0x01
    char sa_data[14]; // 0x02
} sceEENetSockaddr;

// 16 bytes
typedef struct sceEENetSockaddrIn
{
    u8 sin_len;              // 0x00
    u8 sin_family;           // 0x01
    u16 sin_port;            // 0x02
    sceEENetInAddr sin_addr; // 0x04
    char sin_zero[8];        // 0x08
} sceEENetSockaddrIn;

// 16 bytes
typedef struct sceGifTag
{
    u64 NLOOP;  // 0x00
    u64 EOP;    // 0x00
    u64 pad16;  // 0x00
    u64 id;     // 0x00
    u64 PRE;    // 0x00
    u64 PRIM;   // 0x00
    u64 FLG;    // 0x00
    u64 NREG;   // 0x00
    u64 REGS0;  // 0x08
    u64 REGS1;  // 0x08
    u64 REGS2;  // 0x08
    u64 REGS3;  // 0x08
    u64 REGS4;  // 0x08
    u64 REGS5;  // 0x08
    u64 REGS6;  // 0x08
    u64 REGS7;  // 0x08
    u64 REGS8;  // 0x08
    u64 REGS9;  // 0x08
    u64 REGS10; // 0x08
    u64 REGS11; // 0x08
    u64 REGS12; // 0x08
    u64 REGS13; // 0x08
    u64 REGS14; // 0x08
    u64 REGS15; // 0x08
} sceGifTag;

// 8 bytes
typedef struct sceGsPrim
{
    u64 PRIM;  // 0x00
    u64 IIP;   // 0x00
    u64 TME;   // 0x00
    u64 FGE;   // 0x00
    u64 ABE;   // 0x00
    u64 AA1;   // 0x00
    u64 FST;   // 0x00
    u64 CTXT;  // 0x00
    u64 FIX;   // 0x00
    u64 pad11; // 0x00
} sceGsPrim;

// 8 bytes
typedef struct sceGsRgbaq
{
    u32 R; // 0x00
    u32 G; // 0x00
    u32 B; // 0x00
    u32 A; // 0x00
    f32 Q; // 0x04
} sceGsRgbaq;

// 8 bytes
typedef struct sceGsTest
{
    u64 ATE;   // 0x00
    u64 ATST;  // 0x00
    u64 AREF;  // 0x00
    u64 AFAIL; // 0x00
    u64 DATE;  // 0x00
    u64 DATM;  // 0x00
    u64 ZTE;   // 0x00
    u64 ZTST;  // 0x00
    u64 pad19; // 0x00
} sceGsTest;

// 8 bytes
typedef struct sceGsXyz
{
    u64 X; // 0x00
    u64 Y; // 0x00
    u64 Z; // 0x00
} sceGsXyz;

// 96 bytes
typedef struct sceGsClear
{
    sceGsTest testa;  // 0x00
    s64 testaaddr;    // 0x08
    sceGsPrim prim;   // 0x10
    s64 primaddr;     // 0x18
    sceGsRgbaq rgbaq; // 0x20
    s64 rgbaqaddr;    // 0x28
    sceGsXyz xyz2a;   // 0x30
    s64 xyz2aaddr;    // 0x38
    sceGsXyz xyz2b;   // 0x40
    s64 xyz2baddr;    // 0x48
    sceGsTest testb;  // 0x50
    s64 testbaddr;    // 0x58
} sceGsClear;

// 8 bytes
typedef struct sceGsColclamp
{
    u64 CLAMP; // 0x00
    u64 pad01; // 0x00
} sceGsColclamp;

// 8 bytes
typedef struct tGS_BGCOLOR
{
    u32 R;  // 0x00
    u32 G;  // 0x00
    u32 B;  // 0x00
    u32 p0; // 0x00
    u32 p1; // 0x04
} tGS_BGCOLOR;

// 8 bytes
typedef struct tGS_DISPFB2
{
    u32 FBP; // 0x00
    u32 FBW; // 0x00
    u32 PSM; // 0x00
    u32 p0;  // 0x00
    u32 DBX; // 0x04
    u32 DBY; // 0x04
    u32 p1;  // 0x04
} tGS_DISPFB2;

// 8 bytes
typedef struct tGS_DISPLAY2
{
    u32 DX;   // 0x00
    u32 DY;   // 0x00
    u32 MAGH; // 0x00
    u32 MAGV; // 0x00
    u32 p0;   // 0x00
    u32 DW;   // 0x04
    u32 DH;   // 0x04
    u32 p1;   // 0x04
} tGS_DISPLAY2;

// 8 bytes
typedef struct tGS_PMODE
{
    u32 EN1;   // 0x00
    u32 EN2;   // 0x00
    u32 CRTMD; // 0x00
    u32 MMOD;  // 0x00
    u32 AMOD;  // 0x00
    u32 SLBG;  // 0x00
    u32 ALP;   // 0x00
    u32 p0;    // 0x00
    u32 p1;    // 0x04
} tGS_PMODE;

// 8 bytes
typedef struct tGS_SMODE2
{
    u32 INT;  // 0x00
    u32 FFMD; // 0x00
    u32 DPMS; // 0x00
    u32 p0;   // 0x00
    u32 p1;   // 0x04
} tGS_SMODE2;

// 40 bytes
typedef struct sceGsDispEnv
{
    tGS_PMODE pmode;      // 0x00
    tGS_SMODE2 smode2;    // 0x08
    tGS_DISPFB2 dispfb;   // 0x10
    tGS_DISPLAY2 display; // 0x18
    tGS_BGCOLOR bgcolor;  // 0x20
} sceGsDispEnv;

// 8 bytes
typedef struct sceGsDthe
{
    u64 DTHE;  // 0x00
    u64 pad01; // 0x00
} sceGsDthe;

// 8 bytes
typedef struct sceGsFrame
{
    u64 FBP;   // 0x00
    u64 pad09; // 0x00
    u64 FBW;   // 0x00
    u64 pad22; // 0x00
    u64 PSM;   // 0x00
    u64 pad30; // 0x00
    u64 FBMSK; // 0x00
} sceGsFrame;

// 8 bytes
typedef struct sceGsPrmodecont
{
    u64 AC;    // 0x00
    u64 pad01; // 0x00
} sceGsPrmodecont;

// 8 bytes
typedef struct sceGsScissor
{
    u64 SCAX0; // 0x00
    u64 pad11; // 0x00
    u64 SCAX1; // 0x00
    u64 pad27; // 0x00
    u64 SCAY0; // 0x00
    u64 pad43; // 0x00
    u64 SCAY1; // 0x00
    u64 pad59; // 0x00
} sceGsScissor;

// 8 bytes
typedef struct sceGsXyoffset
{
    u64 OFX;   // 0x00
    u64 pad16; // 0x00
    u64 OFY;   // 0x00
    u64 pad48; // 0x00
} sceGsXyoffset;

// 8 bytes
typedef struct sceGsZbuf
{
    u64 ZBP;   // 0x00
    u64 pad09; // 0x00
    u64 PSM;   // 0x00
    u64 pad28; // 0x00
    u64 ZMSK;  // 0x00
    u64 pad33; // 0x00
} sceGsZbuf;

// 128 bytes
typedef struct sceGsDrawEnv1
{
    sceGsFrame frame1;          // 0x00
    u64 frame1addr;             // 0x08
    sceGsZbuf zbuf1;            // 0x10
    s64 zbuf1addr;              // 0x18
    sceGsXyoffset xyoffset1;    // 0x20
    s64 xyoffset1addr;          // 0x28
    sceGsScissor scissor1;      // 0x30
    s64 scissor1addr;           // 0x38
    sceGsPrmodecont prmodecont; // 0x40
    s64 prmodecontaddr;         // 0x48
    sceGsColclamp colclamp;     // 0x50
    s64 colclampaddr;           // 0x58
    sceGsDthe dthe;             // 0x60
    s64 dtheaddr;               // 0x68
    sceGsTest test1;            // 0x70
    s64 test1addr;              // 0x78
} sceGsDrawEnv1;

// 560 bytes
typedef struct sceGsDBuff
{
    sceGsDispEnv disp[2]; // 0x00
    sceGifTag giftag0;    // 0x50
    sceGsDrawEnv1 draw0;  // 0x60
    sceGsClear clear0;    // 0xe0
    sceGifTag giftag1;    // 0x140
    sceGsDrawEnv1 draw1;  // 0x150
    sceGsClear clear1;    // 0x1d0
} sceGsDBuff;

// 128 bytes
typedef struct sceGsDrawEnv2
{
    sceGsFrame frame2;          // 0x00
    u64 frame2addr;             // 0x08
    sceGsZbuf zbuf2;            // 0x10
    s64 zbuf2addr;              // 0x18
    sceGsXyoffset xyoffset2;    // 0x20
    s64 xyoffset2addr;          // 0x28
    sceGsScissor scissor2;      // 0x30
    s64 scissor2addr;           // 0x38
    sceGsPrmodecont prmodecont; // 0x40
    s64 prmodecontaddr;         // 0x48
    sceGsColclamp colclamp;     // 0x50
    s64 colclampaddr;           // 0x58
    sceGsDthe dthe;             // 0x60
    s64 dtheaddr;               // 0x68
    sceGsTest test2;            // 0x70
    s64 test2addr;              // 0x78
} sceGsDrawEnv2;

// 816 bytes
typedef struct sceGsDBuffDc
{
    sceGsDispEnv disp[2]; // 0x00
    sceGifTag giftag0;    // 0x50
    sceGsDrawEnv1 draw01; // 0x60
    sceGsDrawEnv2 draw02; // 0xe0
    sceGsClear clear0;    // 0x160
    sceGifTag giftag1;    // 0x1c0
    sceGsDrawEnv1 draw11; // 0x1d0
    sceGsDrawEnv2 draw12; // 0x250
    sceGsClear clear1;    // 0x2d0
} sceGsDBuffDc;

// 8 bytes
typedef struct sceMcStDateTime
{
    u8 Resv2; // 0x00
    u8 Sec;   // 0x01
    u8 Min;   // 0x02
    u8 Hour;  // 0x03
    u8 Day;   // 0x04
    u8 Month; // 0x05
    u16 Year; // 0x06
} sceMcStDateTime;

// 64 bytes
typedef struct sceMcTblGetDir
{
    sceMcStDateTime _Create; // 0x00
    sceMcStDateTime _Modify; // 0x08
    u32 FileSizeByte;        // 0x10
    u16 AttrFile;            // 0x14
    u16 Reserve1;            // 0x16
    u32 Reserve2;            // 0x18
    u32 PdaAplNo;            // 0x1c
    u8 EntryName[32];        // 0x20
} sceMcTblGetDir;

// 4928 bytes
typedef struct sceNetcnfifData
{
    char attach_ifc[256];      // 0x00
    char attach_dev[256];      // 0x100
    char dhcp_host_name[256];  // 0x200
    char address[256];         // 0x300
    char netmask[256];         // 0x400
    char gateway[256];         // 0x500
    char dns1_address[256];    // 0x600
    char dns2_address[256];    // 0x700
    char phone_numbers1[256];  // 0x800
    char phone_numbers2[256];  // 0x900
    char phone_numbers3[256];  // 0xa00
    char auth_name[256];       // 0xb00
    char auth_key[256];        // 0xc00
    char peer_name[256];       // 0xd00
    char vendor[256];          // 0xe00
    char product[256];         // 0xf00
    char chat_additional[256]; // 0x1000
    char outside_number[256];  // 0x1100
    char outside_delay[256];   // 0x1200
    s32 ifc_type;              // 0x1300
    s32 mtu;                   // 0x1304
    s32 ifc_idle_timeout;      // 0x1308
    s32 dev_type;              // 0x130c
    s32 phy_config;            // 0x1310
    s32 dialing_type;          // 0x1314
    s32 dev_idle_timeout;      // 0x1318
    s32 p0;                    // 0x131c
    u8 dhcp;                   // 0x1320
    u8 dns1_nego;              // 0x1321
    u8 dns2_nego;              // 0x1322
    u8 f_auth;                 // 0x1323
    u8 auth;                   // 0x1324
    u8 pppoe;                  // 0x1325
    u8 prc_nego;               // 0x1326
    u8 acc_nego;               // 0x1327
    u8 accm_nego;              // 0x1328
    u8 p1;                     // 0x1329
    u8 p2;                     // 0x132a
    u8 p3;                     // 0x132b
    s32 p4[5];                 // 0x132c
} sceNetcnfifData;

// 16 bytes
typedef struct sceSifDmaData
{
    u32 data; // 0x00
    u32 addr; // 0x04
    u32 size; // 0x08
    u32 mode; // 0x0c
} sceSifDmaData;

// 32 bytes
typedef struct sceVif1Packet
{
    u32* pCurrent; // 0x00
    void* pBase;   // 0x04
    void* pDmaTag; // 0x08
    u32* pVifCode; // 0x0c
    u32 numlen;    // 0x10
    u64* pGifTag;  // 0x14
    u32 pad12;     // 0x18
    u32 pad13;     // 0x1c
} sceVif1Packet;

// 8 bytes
typedef struct tGS_DISPFB1
{
    u32 FBP; // 0x00
    u32 FBW; // 0x00
    u32 PSM; // 0x00
    u32 p0;  // 0x00
    u32 DBX; // 0x04
    u32 DBY; // 0x04
    u32 p1;  // 0x04
} tGS_DISPFB1;

// 8 bytes
typedef struct tGS_DISPLAY1
{
    u32 DX;   // 0x00
    u32 DY;   // 0x00
    u32 MAGH; // 0x00
    u32 MAGV; // 0x00
    u32 p0;   // 0x00
    u32 DW;   // 0x04
    u32 DH;   // 0x04
    u32 p1;   // 0x04
} tGS_DISPLAY1;

#endif // SCE_H
