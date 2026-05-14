#ifndef EEREGS_H
#define EEREGS_H

#include "sce/eetypes.h"

#define T_MODE_CLKS_M (0x03<< 0)
#define T_MODE_GATE_M (0x01<< 2)
#define T_MODE_GATS_M (0x01<< 3)
#define T_MODE_GATM_M (0x03<< 4)
#define T_MODE_ZRET_M (0x01<< 6)
#define T_MODE_CUE_M  (0x01<< 7)
#define T_MODE_CMPE_M (0x01<< 8)
#define T_MODE_OVFE_M (0x01<< 9)
#define T_MODE_EQUF_M (0x01<<10)
#define T_MODE_OVFF_M (0x01<<11)

#define T_MODE_CLKS_O (0)
#define T_MODE_GATE_O (2)
#define T_MODE_GATS_O (3)
#define T_MODE_GATM_O (4)
#define T_MODE_ZRET_O (6)
#define T_MODE_CUE_O  (7)
#define T_MODE_CMPE_O (8)
#define T_MODE_OVFE_O (9)
#define T_MODE_EQUF_O (10)
#define T_MODE_OVFF_O (11)



#define T0_COUNT ((volatile u_int*)(0x10000000))
#define T0_MODE  ((volatile u_int*)(0x10000010))
#define T0_COMP  ((volatile u_int*)(0x10000020))
#define T0_HOLD  ((volatile u_int*)(0x10000030))

#define T1_COUNT ((volatile u_int *)(0x10000800))
#define T1_MODE  ((volatile u_int *)(0x10000810))
#define T1_COMP  ((volatile u_int *)(0x10000820))
#define T1_HOLD  ((volatile u_int *)(0x10000830))

#define DGET_T0_MODE()   (*T0_MODE)
#define DPUT_T0_MODE(x)  (*T0_MODE = x)
#define DGET_T0_COUNT()  (*T0_COUNT)
#define DPUT_T0_COUNT(x) (*T0_COUNT = x)
#define DGET_T0_COMP()   (*T0_COMP)
#define DPUT_T0_COMP(x)  (*T0_COMP = x)
#define DGET_T0_HOLD()   (*T0_HOLD)
#define DPUT_T0_HOLD(x)  (*T0_HOLD = x)

#define DGET_T1_MODE()   (*T1_MODE)
#define DPUT_T1_MODE(x)  (*T1_MODE = x)
#define DGET_T1_COUNT()  (*T1_COUNT)
#define DPUT_T1_COUNT(x) (*T1_COUNT = x)
#define DGET_T1_COMP()   (*T1_COMP)
#define DPUT_T1_COMP(x)  (*T1_COMP = x)
#define DGET_T1_HOLD()   (*T1_HOLD)
#define DPUT_T1_HOLD(x)  (*T1_HOLD = x)

#endif