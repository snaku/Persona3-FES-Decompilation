#ifndef EESTRUCT_H
#define EESTRUCT_H

#include "sce/eetypes.h"

#define GS_TEST_ATE_M  		(0x01<< 0)
#define GS_TEST_ATST_M  	(0x07<< 1)
#define GS_TEST_AREF_M  	(0xff<< 4)
#define GS_TEST_AFAIL_M  	(0x03<<12)
#define GS_TEST_DATE_M  	(0x01<<14)
#define GS_TEST_DATM_M  	(0x01<<15)
#define GS_TEST_ZTE_M 	 	(0x01<<16)
#define GS_TEST_ZTST_M  	(0x03<<17)

#define GS_TEST_ATE_O  		( 0)
#define GS_TEST_ATST_O  	( 1)
#define GS_TEST_AREF_O  	( 4)
#define GS_TEST_AFAIL_O  	(12)
#define GS_TEST_DATE_O  	(14)
#define GS_TEST_DATM_O  	(15)
#define GS_TEST_ZTE_O 	 	(16)
#define GS_TEST_ZTST_O  	(17)

#define SCE_GS_SET_TEST_1 SCE_GS_SET_TEST
#define SCE_GS_SET_TEST_2 SCE_GS_SET_TEST
#define SCE_GS_SET_TEST(ate, atst, aref, afail, date, datm, zte, ztst) \
	((u_long)(ate)         | ((u_long)(atst) << 1) | \
	((u_long)(aref) << 4)  | ((u_long)(afail) << 12) | \
	((u_long)(date) << 14) | ((u_long)(datm) << 15) | \
	((u_long)(zte) << 16)  | ((u_long)(ztst) << 17))

#define GS_ALPHA_A_M   (0x03<< 0)
#define GS_ALPHA_B_M   (0x03<< 2)
#define GS_ALPHA_C_M   (0x03<< 4)
#define GS_ALPHA_D_M   (0x03<< 6)
#define GS_ALPHA_FIX_M (0xffL<<32)

#define GS_ALPHA_A_O   (0)
#define GS_ALPHA_B_O   (2)
#define GS_ALPHA_C_O   (4)
#define GS_ALPHA_D_O   (6)
#define GS_ALPHA_FIX_O (32)

#define SCE_GS_SET_ALPHA_1	SCE_GS_SET_ALPHA
#define SCE_GS_SET_ALPHA_2	SCE_GS_SET_ALPHA
#define SCE_GS_SET_ALPHA(a, b, c, d, fix) \
	((u_long)(a)       | ((u_long)(b) << 2)     | ((u_long)(c) << 4) | \
	((u_long)(d) << 6) | ((u_long)(fix) << 32))

#endif