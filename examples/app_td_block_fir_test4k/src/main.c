// Copyright 2024-2025 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <xcore/hwtimer.h>
#include <xcore/parallel.h>
#include <xcore/channel.h>
#include "dsp/td_block_fir.h"

#include "test_0.h"

int main(void){

    int32_t data[4096+TD_BLOCK_FIR_LENGTH];
    memset(data, 0, sizeof(data));    

    int32_t output[TD_BLOCK_FIR_LENGTH];
    memset(output, 0, sizeof(output));  

    for(int i=0;i<TD_BLOCK_FIR_LENGTH;i++)
        data[i] = INT32_MAX/4;

    td_block_fir_4k(output, data, coefs_test_0);
    
    for(int i=0;i<TD_BLOCK_FIR_LENGTH;i++){
        printf("%ld\n", output[i]);
    }
    exit(1);
}