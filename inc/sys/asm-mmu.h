/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2005.2.23
\***************************************************************************/
	

/***************************************************************************\
    #说明: 
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------
	2005-2-23	创建

\***************************************************************************/

#ifndef __ASM_MMU_H__
#define __ASM_MMU_H__

//====================================
// MMU Cache/TLB/etc on/off functions
//====================================
#define R1_I			(1<<12)
#define R1_C			(1<<2)
#define R1_A			(1<<1)
#define R1_M			(1)
#define R1_iA		(1u<<31)
#define R1_nF		(1<<30)

__inline void MMU_EnableICache(void)
	{	int tmp;
		__asm{
			mrc	p15,0,tmp,c1,c0,0
			orr	tmp,tmp,#R1_I
			mcr	p15,0,tmp,c1,c0,0
		}
	}

__inline void MMU_DisableICache(void)
	{	int tmp;
		__asm{
			mrc	p15,0,tmp,c1,c0,0
			bic	tmp,tmp,#R1_I
			mcr	p15,0,tmp,c1,c0,0
		}
	}

__inline void MMU_EnableDCache(void)
	{	int tmp;
		__asm{
			mrc	p15,0,tmp,c1,c0,0
			orr	tmp,tmp,#R1_C
			mcr	p15,0,tmp,c1,c0,0
		}
	}

__inline void MMU_DisableDCache(void)
	{	int tmp;
		__asm{
			mrc	p15,0,tmp,c1,c0,0
			bic	tmp,tmp,#R1_C
			mcr	p15,0,tmp,c1,c0,0
		}
	}

__inline void MMU_EnableAlignFault(void)
	{	int tmp;
		__asm{
			mrc	p15,0,tmp,c1,c0,0
			orr	tmp,tmp,#R1_A
			mcr	p15,0,tmp,c1,c0,0
		}
	}

__inline void MMU_DisableAlignFault(void)
	{	int tmp;
		__asm{
			mrc	p15,0,tmp,c1,c0,0
			bic	tmp,tmp,#R1_A
			mcr	p15,0,tmp,c1,c0,0
		}
	}

__inline void MMU_EnableMMU(void)
	{	int tmp;
		__asm{
			mrc	p15,0,tmp,c1,c0,0
			orr	tmp,tmp,#R1_M
			mcr	p15,0,tmp,c1,c0,0
		}
	}

__inline void MMU_DisableMMU(void)
	{	int tmp;
		__asm{
			mrc	p15,0,tmp,c1,c0,0
			bic	tmp,tmp,#R1_M
			mcr	p15,0,tmp,c1,c0,0
		}
	}

__inline void MMU_SetTTBase(U32 base){__asm{mcr p15,0,base,c2,c0,0}}
__inline void MMU_SetDomain(U32 domain){__asm{mcr p15,0,domain,c3,c0,0}}

__inline void MMU_SetFastBusMode(void)          //GCLK=HCLK
	{	int tmp;
		__asm{
			mrc  p15,0,tmp,c1,c0,0
			bic  tmp,tmp,#R1_iA|R1_nF
			mcr  p15,0,tmp,c1,c0,0
		}
	}

__inline void MMU_SetAsyncBusMode(void)         //GCLK=FCLK @(FCLK>=HCLK)
	{	int tmp;
		__asm{
			mrc  p15,0,tmp,c1,c0,0
			orr  tmp,tmp,#R1_iA|R1_nF
			mcr  p15,0,tmp,c1,c0,0
		}
	}

__inline void MMU_InvalidateIDCache(void){__asm{mcr  p15,0,r0,c7,c7,0}}
__inline void MMU_InvalidateICache(void){__asm{mcr  p15,0,r0,c7,c5,0}}
__inline void MMU_InvalidateICacheMVA(U32 mva){__asm{mcr  p15,0,mva,c7,c5,1}}
__inline void MMU_PrefetchICacheMVA(U32 mva){__asm{mcr  p15,0,mva,c7,c13,1}}
__inline void MMU_InvalidateDCache(void){__asm{mcr  p15,0,r0,c7,c6,0}}
__inline void MMU_InvalidateDCacheMVA(U32 mva){__asm{mcr  p15,0,mva,c7,c6,1}}
__inline void MMU_CleanDCacheMVA(U32 mva){__asm{mcr  p15,0,mva,c7,c10,1}}
__inline void MMU_CleanInvalidateDCacheMVA(U32 mva){__asm{mcr  p15,0,mva,c7,c14,1}}
__inline void MMU_CleanDCacheIndex(U32 index){__asm{mcr  p15,0,index,c7,c10,2}}
__inline void MMU_CleanInvalidateDCacheIndex(U32 index){__asm{mcr  p15,0,index,c7,c14,2}}
__inline void MMU_WaitForInterrupt(void){__asm{mcr  p15,0,r0,c7,c0,4}}
        
__inline void MMU_InvalidateTLB(void){__asm{mcr  p15,0,r0,c8,c7,0}}
__inline void MMU_InvalidateITLB(void){__asm{mcr  p15,0,r0,c8,c5,0}}
__inline void MMU_InvalidateITLBMVA(U32 mva){__asm{mcr  p15,0,mva,c8,c5,1}}
__inline void MMU_InvalidateDTLB(void){__asm{mcr p15,0,r0,c8,c6,0}}
__inline void MMU_InvalidateDTLBMVA(U32 mva){__asm{mcr p15,0,mva,c8,c6,1}}

__inline void MMU_SetDCacheLockdownBase(U32 base){__asm{mcr  p15,0,base,c9,c0,0}}
__inline void MMU_SetICacheLockdownBase(U32 base){__asm{mcr  p15,0,base,c9,c0,1}}

__inline void MMU_SetDTLBLockdown(U32 baseVictim){__asm{mcr  p15,0,baseVictim,c10,c0,0}}
__inline void MMU_SetITLBLockdown(U32 baseVictim){__asm{mcr  p15,0,baseVictim,c10,c0,1}}

__inline void MMU_SetProcessId(U32 pid){__asm{mcr  p15,0,pid,c13,c0,0}}

#endif //#ifndef __ASM_MMU_H__