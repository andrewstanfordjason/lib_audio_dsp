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

    int32_t data0[test_0_DATA_BUFFER_ELEMENTS];
    td_block_fir_data_t d0;
    td_block_fir_data_init(&d0, data0, test_0_DATA_BUFFER_ELEMENTS);

    memset(data0, 0, test_0_DATA_BUFFER_ELEMENTS *sizeof(int32_t));    

    
    hwtimer_t SysTimer = hwtimer_alloc();
    uint32_t from, to;

    const uint32_t loops = 128;
    from = hwtimer_get_time(SysTimer);

    int32_t buffer0[TD_BLOCK_FIR_LENGTH];
    for(int i=0;i<TD_BLOCK_FIR_LENGTH;i++){
        buffer0[i] = INT32_MAX/4;
    }

    td_block_fir_add_data(buffer0, &d0);
    td_block_fir_compute(buffer0, &d0, &td_block_fir_filter_test_0);
    to = hwtimer_get_time(SysTimer);
    uint32_t elapsed = to - from;
    printf("elapsed: %lu\n", elapsed/loops);
    for(int i=0;i<TD_BLOCK_FIR_LENGTH;i++){
        printf("%ld\n", buffer0[i]);
    }
    exit(1);
}

// -3412
// -10239
// -13654
// -10237
// -3399
// 22
// -3401
// -10251