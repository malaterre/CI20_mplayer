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

#ifndef __T_INTPID_H__
#define __T_INTPID_H__

typedef char I8;
typedef unsigned char U8;
typedef short I16;
typedef unsigned short U16;


typedef int I32;
typedef unsigned int U32;

enum IntpID {
  MPEG_HPEL = 0,
  MPEG_QPEL,
  H264_QPEL,
  H264_EPEL,
  RV8_TPEL,
  RV9_QPEL,
  RV9_CPEL,
  WMV2_QPEL,
  VC1_QPEL,
  AVS_QPEL,
  VP6_QPEL,
  VP8_QPEL,
};

enum TapTYP {
  TAP2 = 0,
  TAP4,
  TAP6,
  TAP8,
};

enum SPelSFT {
  HPEL = 1,
  QPEL,
  EPEL,
};

enum BlkTYP {
  BLK16X16 = 0,
  BLK16X8,
  BLK8X16,
  BLK8X8,
};
enum SBlkTYP {
  NOSUB = 0,
  SBLK8X4,
  SBLK4X8,
  SBLK4X4,
};

#define NO_RESET  0
#define DO_RESET  1

#define IS_FRAME  0
#define IS_FIELD  1

#define IS_SKIRT  0
#define IS_MIRROR 1

#define NOT_RGR   0
#define IS_RGR    1
#define NOT_ITS   0
#define IS_ITS    1    

#define IS_BIAVG  0
#define IS_WT1    1
#define IS_WT2    2
#define IS_FIXWT  3

#define IS_ILUT0  0
#define IS_ILUT1  2
#define IS_EC     1

#define IS_TCS     1
#define NOT_TCS    0
#define IS_SCS     1
#define NOT_SCS    0
#define IS_HLDGL   1
#define NOT_HLDGL  0
#define IS_AVSDGL  1
#define NOT_AVSDGL 0

#define INTP_HDIR  0
#define INTP_VDIR  1

typedef struct IntpFMT_t{
  U8 tap;
  U8 intp_pkg[2];
  U8 hldgl;
  U8 avsdgl;
  U8 intp[2];
  U8 intp_dir[2];
  I8 intp_coef[2][8];
  I8 intp_rnd[2];
  U8 intp_sft[2];
  U8 intp_sintp[2];
  U8 intp_srnd[2];
  U8 intp_sbias[2];
}IntpFMT_t;

typedef struct CompVector_t{
  /*MB information*/
  U8 mbx, mby;
  U8 mbtype;
  U8 rst;
  U8 automv;
  U8 mbpar, subpar[4];
  U8 field[4];
  U8 list[2][4], refn[2][4];
  I16 mvx[2][4][4][2], mvy[2][4][4][2];
  /*Ext. information*/
  U8 intpid;
  U8 cintpid;
  U8 rgr;
  U8 its;
  I8 its_scale;
  I16 its_rnd;
  U8 its_sft;
  U8 wt_mode;
  U8 wt_denom;
  I8 wt_lcoef, wt_rcoef;
  I8 wt_rnd;
  U8 wt_sft;
  /*Golden*/
  U8 std_y[256];
  U8 std_u[64];
  U8 std_v[64];
}CompVector_t;

typedef struct WTpara_t{
  I8 wcoef_y;
  I8 wofst_y;
  I8 wcoef_u;
  I8 wofst_u;
  I8 wcoef_v;
  I8 wofst_v;
}WTpara_t;

__place_k0_data__
static char AryFMT[] = {IS_SKIRT, IS_MIRROR, IS_SKIRT, IS_SKIRT,
			IS_SKIRT, IS_SKIRT, IS_SKIRT, IS_SKIRT, 
			IS_SKIRT, IS_SKIRT, IS_SKIRT, IS_SKIRT, 
			IS_SKIRT, IS_SKIRT, IS_SKIRT, IS_SKIRT};

__place_k0_data__
static char SubPel[] = {HPEL, QPEL, QPEL, EPEL, 
			QPEL, QPEL, QPEL, QPEL,
			QPEL, QPEL, QPEL, QPEL};

__place_k0_data__
static IntpFMT_t IntpFMT[][16] = {
  {
    /************* MPEG_HPEL ***************/
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {0},
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR}, 
      {{1, 1, 0, 0, 0, 0, 0, 0},{0},},
      {1, 0}, 
      {1, 0},
      {0},
      {0},
      {0},
    },
    {0},
    {0},
    {0},
    {0},
    {0},
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR}, 
      {{1, 1, 0, 0, 0, 0, 0, 0},{0},},
      {1, 0}, 
      {1, 0},
      {0},
      {0},
      {0},
    },
    {0},
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0} },
      {0, 2}, 
      {0, 2},
      {0},
      {0},
      {0},
    },
    {0},
    {0},
    {0},
    {0},
    {0},
  },
  
  {
    /************* MPEG_QPEL ***************/
    {
      TAP8, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1},{0},},
      {15, 0}, 
      {5, 0},
      {1, 0},
      {1, 0},
      {0, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1},{0},},
      {15, 0}, 
      {5, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1},{0},},
      {15, 0}, 
      {5, 0},
      {1, 0},
      {1, 0},
      {1, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1},{0},},
      {15, 0}, 
      {5, 0},
      {1, 0},
      {1, 0},
      {0, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1}, {-1, 3, -6, 20, 20, -6, 3, -1},},
      {15, 15}, 
      {5, 5},
      {1, 1},
      {1, 1},
      {0, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1}, {-1, 3, -6, 20, 20, -6, 3, -1},},
      {15, 15}, 
      {5, 5},
      {0, 1},
      {0, 1},
      {0, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1}, {-1, 3, -6, 20, 20, -6, 3, -1},},
      {15, 15}, 
      {5, 5},
      {1, 1},
      {1, 1},
      {1, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1},{0},},
      {15, 0}, 
      {5, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1}, {-1, 3, -6, 20, 20, -6, 3, -1},},
      {15, 15}, 
      {5, 5},
      {1, 0},
      {1, 0},
      {0, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1}, {-1, 3, -6, 20, 20, -6, 3, -1},},
      {15, 15}, 
      {5, 5},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1}, {-1, 3, -6, 20, 20, -6, 3, -1},},
      {15, 15}, 
      {5, 5},
      {1, 0},
      {1, 0},
      {1, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1},{0},},
      {15, 0}, 
      {5, 0},
      {1, 0},
      {1, 0},
      {1, 0},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1}, {-1, 3, -6, 20, 20, -6, 3, -1},},
      {15, 15}, 
      {5, 5},
      {1, 1},
      {1, 1},
      {0, 1},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1}, {-1, 3, -6, 20, 20, -6, 3, -1},},
      {15, 15}, 
      {5, 5},
      {0, 1},
      {0, 1},
      {0, 1},
    },
    {
      TAP8, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 3, -6, 20, 20, -6, 3, -1}, {-1, 3, -6, 20, 20, -6, 3, -1},},
      {15, 15}, 
      {5, 5},
      {1, 1},
      {1, 1},
      {1, 1},
    },
  },

  {
    /************* H264_QPEL ***************/
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{1, -5, 20, 20, -5, 1, 0, 0},{0},},
      {16, 0}, 
      {5, 0},
      {1, 0},
      {1, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{1, -5, 20, 20, -5, 1, 0, 0},{0},},
      {16, 0}, 
      {5, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{1, -5, 20, 20, -5, 1, 0, 0},{0},},
      {16, 0}, 
      {5, 0},
      {1, 0},
      {1, 0},
      {1, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{1, -5, 20, 20, -5, 1, 0, 0},{0},},
      {16, 0}, 
      {5, 0},
      {1, 0},
      {1, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, IS_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {16, 16}, 
      {5, 5},
      {0, 1},
      {0, 1},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {16, 0}, 
      {5, 10},
      {0, 1},
      {0, 1},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, IS_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {16, 16}, 
      {5, 5},
      {0, 1},
      {0, 1},
      {1, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{1, -5, 20, 20, -5, 1, 0, 0},{0},},
      {16, 0}, 
      {5, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_VDIR, INTP_HDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {16, 0}, 
      {5, 10},
      {0, 1},
      {0, 1},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {16, 0}, 
      {5, 10},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_VDIR, INTP_HDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {16, 0}, 
      {5, 10},
      {0, 1},
      {0, 1},
      {0, 1},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{1, -5, 20, 20, -5, 1, 0, 0},{0},},
      {16, 0}, 
      {5, 0},
      {1, 0},
      {1, 0},
      {1, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, IS_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {16, 16}, 
      {5, 5},
      {0, 1},
      {0, 1},
      {0, 1},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {16, 0}, 
      {5, 10},
      {0, 1},
      {0, 1},
      {0, 1},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, IS_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {16, 16}, 
      {5, 5},
      {0, 1},
      {0, 1},
      {1, 1},
    },
  },

  {
    /************* H264_EPEL ***************/
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {0},
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{0},{0},},
      {4, 0}, 
      {3, 0},
      {0},
      {0},
      {0},
    },
    {0},
    {0},
    {0},
    {0},
    {0},
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{0},{0},},
      {4, 0}, 
      {3, 0},
      {0},
      {0},
      {0},
    },
    {0},
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{0},{0},},
      {0, 32}, 
      {0, 6},
      {0},
      {0},
      {0},
    },
    {0},
    {0},
    {0},
    {0},
    {0},
  },

  {
    /************* RV8_TPEL ***************/
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 12, 6, -1, 0, 0, 0, 0},{0},},
      {8, 0}, 
      {4, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 6, 12, -1, 0, 0, 0, 0},{0},},
      {8, 0}, 
      {4, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {0},
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-1, 12, 6, -1, 0, 0, 0, 0},{0},},
      {8, 0}, 
      {4, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 12, 6, -1, 0, 0, 0, 0}, {-1, 12, 6, -1, 0, 0, 0, 0},},
      {8, 0}, //{0,128}
      {0, 8},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 6, 12, -1, 0, 0, 0, 0}, {-1, 12, 6, -1, 0, 0, 0, 0},},
      {8, 0}, //{0,128}
      {0, 8},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {0},
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-1, 6, 12, -1, 0, 0, 0, 0},{0},},
      {8, 0}, 
      {4, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 12, 6, -1, 0, 0, 0, 0}, {-1, 6, 12, -1, 0, 0, 0, 0},},
      {8, 0}, //{0,128}
      {0, 8},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 6, 12, -1, 0, 0, 0, 0}, {-1, 6, 12, -1, 0, 0, 0, 0},},
      {8, 0}, //{0,128}
      {0, 8},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {0},
    {0},
    {0},
    {0},
    {0},
  },

  {
    /************* RV9_QPEL ***************/
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{1, -5, 52, 20, -5, 1, 0, 0},{0},},
      {32, 0}, 
      {6, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{1, -5, 20, 20, -5, 1, 0, 0},{0},},
      {16, 0}, 
      {5, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{1, -5, 20, 52, -5, 1, 0, 0},{0},},
      {32, 0}, 
      {6, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{1, -5, 52, 20, -5, 1, 0, 0},{0},},
      {32, 0}, 
      {6, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 52, 20, -5, 1, 0, 0}, {1, -5, 52, 20, -5, 1, 0, 0},},
      {32, 32}, 
      {6, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 52, 20, -5, 1, 0, 0},},
      {16, 32}, 
      {5, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 52, -5, 1, 0, 0}, {1, -5, 52, 20, -5, 1, 0, 0},},
      {32, 32}, 
      {6, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{1, -5, 20, 20, -5, 1, 0, 0},{0},},
      {16, 0}, 
      {5, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 52, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {32, 16}, 
      {6, 5},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {16, 16}, 
      {5, 5},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 52, -5, 1, 0, 0}, {1, -5, 20, 20, -5, 1, 0, 0},},
      {32, 16}, 
      {6, 5},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{1, -5, 20, 52, -5, 1, 0, 0},{0},},
      {32, 0}, 
      {6, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 52, 20, -5, 1, 0, 0}, {1, -5, 20, 52, -5, 1, 0, 0},},
      {32, 32}, 
      {6, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -5, 20, 20, -5, 1, 0, 0}, {1, -5, 20, 52, -5, 1, 0, 0},},
      {16, 32}, 
      {5, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0},},
      {0, 2}, 
      {0, 2},
      {0, 0},
      {0, 0},
      {0, 0},
    },
  },

  {
    /************* RV9_CPEL ***************/
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{3, 1, 0, 0, 0, 0, 0, 0},{0},},
      {1, 0}, 
      {2, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{1, 1, 0, 0, 0, 0, 0, 0},{0},},
      {1, 0}, 
      {1, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{1, 3, 0, 0, 0, 0, 0, 0},{0},},
      {1, 0}, 
      {2, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{3, 1, 0, 0, 0, 0, 0, 0},{0},},
      {2, 0}, 
      {2, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{3, 1, 0, 0, 0, 0, 0, 0}, {3, 1, 0, 0, 0, 0, 0, 0},},
      {0, 7}, 
      {0, 4},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, 1, 0, 0, 0, 0, 0, 0}, {3, 1, 0, 0, 0, 0, 0, 0},},
      {0, 4}, 
      {0, 3},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, 3, 0, 0, 0, 0, 0, 0}, {3, 1, 0, 0, 0, 0, 0, 0},},
      {0, 7}, 
      {0, 4},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{1, 1, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {1, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{3, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0},},
      {0, 4}, 
      {0, 3},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0},},
      {0, 1}, 
      {0, 2},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, 3, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0},},
      {0, 4}, 
      {0, 3},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{1, 3, 0, 0, 0, 0, 0, 0},{0},},
      {2, 0}, 
      {2, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{3, 1, 0, 0, 0, 0, 0, 0}, {1, 3, 0, 0, 0, 0, 0, 0},},
      {0, 7}, 
      {0, 4},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, 1, 0, 0, 0, 0, 0, 0}, {1, 3, 0, 0, 0, 0, 0, 0},},
      {0, 4}, 
      {0, 3},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP2, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0},},
      {0, 1}, 
      {0, 2},
      {0, 0},
      {0, 0},
      {0, 0},
    },
  },

  {
    /************* WMV2_QPEL ***************/
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0},{0},},
      {8, 0}, 
      {4, 0},
      {1, 0},
      {1, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0},{0},},
      {8, 0}, 
      {4, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0},{0},},
      {8, 0}, 
      {4, 0},
      {1, 0},
      {1, 0},
      {1, 0},
    },
    {0},
    {0},
    {0},
    {0},
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0},{0},},
      {8, 0}, 
      {4, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_VDIR, INTP_HDIR}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0}, {-1, 9, 9, -1, 0, 0, 0, 0},},
      {8, 8}, 
      {4, 4},
      {0, 1},
      {0, 1},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_VDIR, INTP_HDIR}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0}, {-1, 9, 9, -1, 0, 0, 0, 0},},
      {8, 8}, 
      {4, 4},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_VDIR, INTP_HDIR}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0}, {-1, 9, 9, -1, 0, 0, 0, 0},},
      {8, 8}, 
      {4, 4},
      {0, 1},
      {0, 1},
      {0, 1},
    },
    {0},
    {0},
    {0},
    {0},
  },

  {
    /************* VC1_QPEL ***************/
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-4, 53, 18, -3, 0, 0, 0, 0},{0},},
      {31, 0}, 
      {6, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0},{0},},
      {7, 0}, 
      {4, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-3, 18, 53, -4, 0, 0, 0, 0},{0},},
      {31, 0}, 
      {6, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-4, 53, 18, -3, 0, 0, 0, 0},{0},},
      {31, 0}, 
      {6, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-4, 53, 18, -3, 0, 0, 0, 0}, {-4, 53, 18, -3, 0, 0, 0, 0},},
      {31, 31}, 
      {6, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0}, {-4, 53, 18, -3, 0, 0, 0, 0},},
      {7, 31}, 
      {4, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-3, 18, 53, -4, 0, 0, 0, 0}, {-4, 53, 18, -3, 0, 0, 0, 0},},
      {31, 31}, 
      {6, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0},{0},},
      {7, 0}, 
      {4, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-4, 53, 18, -3, 0, 0, 0, 0}, {-1, 9, 9, -1, 0, 0, 0, 0},},
      {31, 7}, 
      {6, 4},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0}, {-1, 9, 9, -1, 0, 0, 0, 0},},
      {7, 7}, 
      {4, 4},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-3, 18, 53, -4, 0, 0, 0, 0}, {-1, 9, 9, -1, 0, 0, 0, 0},},
      {31, 7}, 
      {6, 4},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-3, 18, 53, -4, 0, 0, 0, 0},{0},},
      {31, 0}, 
      {6, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-4, 53, 18, -3, 0, 0, 0, 0}, {-3, 18, 53, -4, 0, 0, 0, 0},},
      {31, 31}, 
      {6, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 9, 9, -1, 0, 0, 0, 0}, {-3, 18, 53, -4, 0, 0, 0, 0},},
      {7, 31}, 
      {4, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, IS_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-3, 18, 53, -4, 0, 0, 0, 0}, {-3, 18, 53, -4, 0, 0, 0, 0},},
      {31, 31}, 
      {6, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
  },

  {
    /************* AVS_QPEL ***************/
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, -2, 96, 42, -7, 0, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 5, 5, -1, 0, 0, 0, 0},{0},},
      {4, 0}, 
      {3, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{0, -7, 42, 96, -2, -1, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-1, -2, 96, 42, -7, 0, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, IS_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 5, 5, -1, 0, 0, 0, 0}, {-1, 5, -5, -1, 0, 0, 0, 0},},
      {0, 32}, 
      {0, 6},
      {0, 1},
      {0, 1},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{0, -1, 5, 5, -1, 0, 0, 0}, {-1, -2, 96, 42, -7, 0, 0, 0},},
      {64, 0}, //{0,512} 
      {0, 10},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, IS_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 5, 5, -1, 0, 0, 0, 0}, {-1, 5, -5, -1, 0, 0, 0, 0},},
      {0, 32}, 
      {0, 6},
      {0, 1},
      {0, 1},
      {1, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-1, 5, 5, -1, 0, 0, 0, 0},{0},},
      {4, 0}, 
      {3, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, -2, 96, 42, -7, 0, 0, 0}, {0, -1, 5, 5, -1, 0, 0, 0},},
      {64, 0}, //{0,512} 
      {0, 10},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 5, 5, -1, 0, 0, 0, 0}, {-1, 5, 5, -1, 0, 0, 0, 0},},
      {0, 32}, 
      {0, 6},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{0, -7, 42, 96, -2, -1, 0, 0}, {0, -1, 5, 5, -1, 0, 0, 0},},
      {64, 0}, //{0,512} 
      {0, 10},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{0, -7, 42, 96, -2, -1, 0, 0}, {0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, IS_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 5, 5, -1, 0, 0, 0, 0}, {-1, 5, -5, -1, 0, 0, 0, 0},},
      {0, 32}, 
      {0, 6},
      {0, 1},
      {0, 1},
      {0, 1},
    },
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{0, -1, 5, 5, -1, 0, 0, 0}, {0, -7, 42, 96, -2, -1, 0, 0},},
      {64, 0}, //{0,512} 
      {0, 10},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, IS_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 5, 5, -1, 0, 0, 0, 0}, {-1, 5, -5, -1, 0, 0, 0, 0},},
      {0, 32}, 
      {0, 6},
      {0, 1},
      {0, 1},
      {1, 1},
    },
  },

  {
    /************* VP6_QPEL ***************/
    { /*FIXME: only choose one group filter for test*/
      TAP4, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-4, 109, 24, -1, 0, 0, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-4, 68, 68, -4, 0, 0, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{-1, 24, 109, -4, 0, 0, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-4, 109, 24, -1, 0, 0, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-4, 109, 24, -1, 0, 0, 0, 0}, {-4, 109, 24, -1, 0, 0, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-4, 68, 68, -4, 0, 0, 0, 0}, {-4, 109, 24, -1, 0, 0, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 24, 109, -4, 0, 0, 0, 0}, {-4, 109, 24, -1, 0, 0, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-4, 68, 68, -4, 0, 0, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-4, 109, 24, -1, 0, 0, 0, 0}, {-4, 68, 68, -4, 0, 0, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-4, 68, 68, -4, 0, 0, 0, 0}, {-4, 68, 68, -4, 0, 0, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 24, 109, -4, 0, 0, 0, 0}, {-4, 68, 68, -4, 0, 0, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{-1, 24, 109, -4, 0, 0, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-4, 109, 24, -1, 0, 0, 0, 0}, {-1, 24, 109, -4, 0, 0, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-4, 68, 68, -4, 0, 0, 0, 0}, {-1, 24, 109, -4, 0, 0, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP4, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{-1, 24, 109, -4, 0, 0, 0, 0}, {-1, 24, 109, -4, 0, 0, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
  },

  { /*FIXME: only choose one group filter for test*/
    /************* VP8_QPEL ***************/
    {
      TAP6, {NOT_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {0, 0}, {0}, 
      {{1, 0, 0, 0, 0, 0, 0, 0},{0},},
      {0, 0}, 
      {0, 0},
      {0},
      {0},
      {0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{2, -11, 108, 36, -8, 1, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{3, -16, 77, 77, -16, 3, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_HDIR, 0}, 
      {{1, -8, 36, 108, -11, 2, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{2, -11, 108, 36, -8, 1, 0, 0}, {0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{2, -11, 108, 36, -8, 1, 0, 0}, {2, -11, 108, 36, -8, 1, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{3, -16, 77, 77, -16, 3, 0, 0}, {2, -11, 108, 36, -8, 1, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -8, 36, 108, -11, 2, 0, 0}, {2, -11, 108, 36, -8, 1, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{3, -16, 77, 77, -16, 3, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{2, -11, 108, 36, -8, 1, 0, 0}, {3, -16, 77, 77, -16, 3, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{3, -16, 77, 77, -16, 3, 0, 0}, {3, -16, 77, 77, -16, 3, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -8, 36, 108, -11, 2, 0, 0}, {3, -16, 77, 77, -16, 3, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 0}, {INTP_VDIR, 0}, 
      {{1, -8, 36, 108, -11, 2, 0, 0},{0},},
      {64, 0}, 
      {7, 0},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{2, -11, 108, 36, -8, 1, 0, 0}, {1, -8, 36, 108, -11, 2, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{3, -16, 77, 77, -16, 3, 0, 0}, {1, -8, 36, 108, -11, 2, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
    {
      TAP6, {IS_TCS, NOT_SCS}, NOT_HLDGL, NOT_AVSDGL,
      {1, 1}, {INTP_HDIR, INTP_VDIR}, 
      {{1, -8, 36, 108, -11, 2, 0, 0}, {1, -8, 36, 108, -11, 2, 0, 0},},
      {64, 64}, 
      {7, 7},
      {0, 0},
      {0, 0},
      {0, 0},
    },
  },

};


__place_k0_data__
static char ParNum[] = {1, 2, 2, 4};

__place_k0_data__
static char BlkOfst[4][4][2] = 
  { {0},
    {{0},{0,8}},
    {{0},{8,0}},
    {{0},{8,0},{0,8},{8,8}}
  };

__place_k0_data__
static char SblkOfst[4][4][2] = 
  { {0},
    {{0},{0,4}},
    {{0},{4,0}},
    {{0},{4,0},{0,4},{4,4}}
  };

__place_k0_data__
static char BlkWidth[] = {0x3, 0x3, 0x2, 0x2};

__place_k0_data__
static char BlkHeight[] = {0x3, 0x2, 0x3, 0x2};

__place_k0_data__
static char SblkWidth[] = {0x2, 0x2, 0x1, 0x1};

__place_k0_data__
static char SblkHeight[] = {0x2, 0x1, 0x2, 0x1};

#endif /*__T_INTPID_H__*/
