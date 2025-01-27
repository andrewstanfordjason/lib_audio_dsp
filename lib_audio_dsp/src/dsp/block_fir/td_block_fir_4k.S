// Copyright 2020-2025 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#if defined(__XS3A__)

.section .cp.rodata, "ac", @progbits
.cc_top zero_shr.data
.p2align 2
zero_shr:
.long  0
.long  0
.long  0
.long  0
.long  0
.long  0
.long  0
.long  0
.cc_bottom zero_shr.data

.text
.align 16;
.issue_mode dual

/*  
void td_block_fir_4k(
    int32_t output_block[8],
    int32_t data[4096+8],
    int32_t filter[4096],
);
*/

#define FUNCTION_NAME   td_block_fir_4k
#define NSTACKWORDS     (2)

#define output_block_p      r0
#define data_p              r1
#define filter_p            r2

#define thirtytwo r3
#define step r4

#define t r11

.cc_top FUNCTION_NAME.function,FUNCTION_NAME
FUNCTION_NAME:
  dualentsp NSTACKWORDS
  std r3, r4, sp[0]
  {sub data_p, data_p, 4; ldc thirtytwo, 32}
  {add data_p, data_p, thirtytwo; ldc step, 64 - 4;}

#define ITT \
  {vldc filter_p[0]  ; add filter_p, filter_p, thirtytwo };\
  {vlmaccr data_p[0] ; sub data_p, data_p, 4 };\
  {vlmaccr data_p[0] ; sub data_p, data_p, 4 };\
  {vlmaccr data_p[0] ; sub data_p, data_p, 4 };\
  {vlmaccr data_p[0] ; sub data_p, data_p, 4 };\
  {vlmaccr data_p[0] ; sub data_p, data_p, 4 };\
  {vlmaccr data_p[0] ; sub data_p, data_p, 4 };\
  {vlmaccr data_p[0] ; sub data_p, data_p, 4 };\
  {vlmaccr data_p[0] ; add data_p, data_p, step };

#define ITT2 ITT;ITT
#define ITT4 ITT2;ITT2
#define ITT8 ITT4;ITT4
#define ITT16 ITT8;ITT8
#define ITT32 ITT16;ITT16
#define ITT64 ITT32;ITT32
#define ITT128 ITT64;ITT64

    ITT128
    ITT128
    ITT128
    ITT128

  {ldaw t, cp[zero_shr]}
  {vlsat t[0] ; nop}
  vstr output_block_p[0]

  ldd r3, r4, sp[0]
  { nop                ; retsp NSTACKWORDS           }

.L_func_end_unpack:
.cc_bottom FUNCTION_NAME.function

.global FUNCTION_NAME
.type FUNCTION_NAME,@function
.set FUNCTION_NAME.nstackwords,NSTACKWORDS;     .global FUNCTION_NAME.nstackwords
.set FUNCTION_NAME.maxcores,1;                  .global FUNCTION_NAME.maxcores
.set FUNCTION_NAME.maxtimers,0;                 .global FUNCTION_NAME.maxtimers
.set FUNCTION_NAME.maxchanends,0;               .global FUNCTION_NAME.maxchanends
.size FUNCTION_NAME,.L_func_end_unpack - FUNCTION_NAME

#undef NSTACKWORDS
#undef FUNCTION_NAME

#endif //defined(__XS3A__)
