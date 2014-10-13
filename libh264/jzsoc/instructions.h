/*
 * Copyright (C) 2006-2014 Ingenic Semiconductor CO.,LTD.
 *
 * This file is part of MPlayer.
 *
 * MPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * MPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MPlayer; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __JZASM_H__
#define __JZASM_H__

#define i_movz(_dst_, src0, src1)						\
  ({__asm__ __volatile__("movz\t%0,%1,%2\t#i_movz":"+d"(_dst_):"d"(src0),"d"(src1)); })
#define i_movn(_dst_, src0, src1)						\
  ({__asm__ __volatile__("movn\t%0,%1,%2\t#i_movn":"+d"(_dst_):"d"(src0),"d"(src1)); })

#define i_mtc0_2(src0,src1,src2)	\
({ __asm__ __volatile__ ("mtc0\t%0,$%1,%2"::"r"(src0),"i"(src1),"i"(src2));})

#define i_mfc0_2(src0,src1)								\
(	{unsigned long _dst_; 								\
 	__asm__ __volatile__ ("mfc0\t%0,$%1,%2":"=r"(_dst_):"i"(src0),"i"(src1));	\
	_dst_;})	

#define i_lw(src0,src1)  								\
({unsigned long _dst_;								\
	__asm__ __volatile__("lw\t %0,%2(%1)\t#i_lw":"=r"(_dst_):"r"(src0),"X"(src1)); 	\
	_dst_;})
#define i_sw(src0,src1,offset)	\
({ __asm__ __volatile__("sw\t %0,%2(%1)\t#i_sw"::"r"(src0),"r"(src1),"X"(offset):"memory");})

#define i_nop  ({__asm__ __volatile__("nop\t#i_nop":::"memory");})

#define i_wait()  ({__asm__ __volatile__("wait\t#i_wait":::"memory");})

#define i_eret()  ({__asm__ __volatile__("eret\t#i_eret":::"memory");})

#define i_la(src)                                               			\
({  	unsigned long _dst_;                           					\
	__asm__ __volatile__("la\t""%0,%1""\t#i_la macro":"=r"(_dst_) :"X" (src));      \
	_dst_;})

#define i_cache(opcode,base,offset)	\
({ __asm__ __volatile__("cache %0,%2(%1)"::"i"(opcode),"r"(base),"i"(offset):"memory");})

#define i_pref(hint,base,offset)        \
({ __asm__ __volatile__("pref %0,%2(%1)"::"i"(hint),"r"(base),"i"(offset):"memory");})

#define i_sync()							\
  ({ __asm__ __volatile__("sync":::"memory");})

#define write_reg(reg, val) \
({ i_sw((val), (reg), 0); \
})
#define read_reg(reg, off) \
  ({ i_lw(((unsigned int)(reg))+((unsigned int)(off)), 0);	\
})

#define i_icache_index_st_tag(va, offset)         i_cache(0x8, va, offset)
#define i_dcache_index_st_tag(va, offset)         i_cache(0x9, va, offset)
#define i_dcache_index_invalidate(va, offset)     i_cache(0x1, va, offset)

#define i_dcache_hit_wb(va, offset) i_cache(0x19, va, offset)

#define CACHE_FLUSH_BASE 0x80000000
#define p1_cache_init()                        \
{                                              \
  int i, va;                                   \
  va = CACHE_FLUSH_BASE;                       \
  for(i=0; i<512; i++) {                       \
   i_icache_index_st_tag(va, 0);               \
   i_dcache_index_st_tag(va, 0);               \
   va += 32;                                   \
  }                                            \
}
#define p1_dcache_flush()                      \
{                                              \
  int i, va;                                   \
  va = CACHE_FLUSH_BASE;                       \
  for(i=0; i<512; i++) {                       \
   i_dcache_index_invalidate(va, 0);           \
   va += 32;                                   \
  }                                            \
}

#define jz_dcache_wb()				\
{ \
  int i, va; \
  va = CACHE_FLUSH_BASE; \
  for(i=0; i<512; i++) { \
    i_cache(0x1,va,0); \
    va += 32; \
  }   \
  i_sync(); \
}

#define i_clz(rs)				\
  __extension__( {				\
	unsigned long __dst__ = 0;		\
	__asm__ __volatile ("clz %0,%1"		\
			    :"+d"(__dst__)	\
			    :"d" (rs)		\
			    :"memory");		\
	__dst__;				\
    } )
#endif /*__JZASM_H__*/
