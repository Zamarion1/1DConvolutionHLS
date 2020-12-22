#include "defines.h"
#include "weights.h"
#include "functions.h"
#include "Modules.h"
#include "ap_fixed.h"

#define EXP_WIDTH	16
#define INT_WIDTH	4

typedef ap_fixed<EXP_WIDTH, INT_WIDTH> float24_t;

void CNN(volatile float24_t datain[DATA_CHANNELS][DATA_SIZE], float24_t op_out[OP_NEURONS]){

	#pragma HLS INTERFACE ap_fifo port=op_out
	#pragma HLS INTERFACE ap_fifo port=datain

    float24_t conv1_out[CONV1_CHANNELS][CONV1_FILTERS]{};
    float24_t pool1_out[P1_CHANNELS]{};
    float24_t fc1_out[FC1_NEURONS]{};



	conv_layer(conv1_out, datain, conv_layer_weights,conv_layer_bias);

	pool_layer(pool1_out, conv1_out);

	fc_layer(fc1_out, pool1_out,fc1_layer_weights, fc1_layer_bias);

	op_layer(op_out,fc1_out, op_layer_weights, op_layer_bias);


}
