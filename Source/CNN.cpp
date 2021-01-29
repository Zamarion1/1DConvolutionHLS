#include "defines.h"
#include "weights.h"
#include "functions.h"
#include "Modules.h"
#include "ap_fixed.h"
#include <hls_stream.h>


typedef ap_fixed<EXP_WIDTH, INT_WIDTH> float24_t;



void CNN(float24_t op_out[OP_NEURONS],float24_t datain[DATA_SIZE]){
#pragma HLS INTERFACE ap_fifo port=datain
#pragma HLS INTERFACE ap_fifo port=op_out



    float24_t pool1_out[P1_CHANNELS] = {0};
#pragma HLS ARRAY_PARTITION variable=pool1_out dim=1 complete

    float24_t fc1_out[FC1_NEURONS]{0};
#pragma HLS ARRAY_PARTITION variable=fc1_out dim=1 complete

    float24_t conv1_out[CONV1_FILTERS][CONV1_CHANNELS] = {0};
#pragma HLS ARRAY_PARTITION variable=conv1_out dim=1 complete

	conv_layer(conv1_out, datain);
	pool_layer(pool1_out, conv1_out);
	fc_layer(fc1_out, pool1_out);
	op_layer(op_out,fc1_out);

	}


