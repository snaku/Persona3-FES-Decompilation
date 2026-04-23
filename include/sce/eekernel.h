#ifndef EEKERNEL_H
#define EEKERNEL_H

#include "sce/eetypes.h"

#define ExitHandler() asm volatile("sync.l; ei")

#define INTC_GS       0
#define INTC_SBUS  	  1
#define INTC_VBON  	  2
#define	INTC_VBLANK_S 2
#define INTC_VBOF  	  3
#define	INTC_VBLANK_E 3
#define INTC_VIF0  	  4
#define INTC_VIF1  	  5
#define INTC_VU0  	  6
#define INTC_VU1  	  7
#define INTC_IPU  	  8
#define INTC_TIM0  	  9
#define INTC_TIM1  	  10

#endif