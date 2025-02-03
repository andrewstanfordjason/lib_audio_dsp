#include "dsp/td_block_fir.h"

int32_t __attribute__((aligned (8))) coefs_test_0[8] = {
    -4315132,	    19119947,	   161692205,	   360373891,	
   360373891,	   161692205,	    19119947,	    -4315132
};
//This is the count of int32_t words to allocate for one data channel.
//i.e. int32_t channel_data[test_0_DATA_BUFFER_ELEMENTS] = { 0 };
#define test_0_DATA_BUFFER_ELEMENTS (24)

#define test_0_TD_BLOCK_LENGTH (8)
#define test_0_BLOCK_COUNT (1)
#define test_0_FRAME_ADVANCE (8)
#define test_0_FRAME_OVERLAP (0)
