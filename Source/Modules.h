#include "functions.h"
#include "ap_fixed.h"
#include <hls_stream.h>

typedef ap_fixed<EXP_WIDTH, INT_WIDTH> float24_t;




void conv_layer(float24_t out[CONV1_FILTERS][CONV1_CHANNELS],float24_t in[DATA_SIZE]) {


	static float24_t window[7*DATA_SIZE] = {0};
#pragma HLS ARRAY_PARTITION variable=window dim=1 complete
    int  filter, row_offset,column_offset, channel_offset;
    float24_t sum;

//shift register for storing the 16 values of datain in a window mode with the padding 'same': first and last rows are equal to 0
buffer:		for(int m = 1; m <= DATA_CHANNELS; m++){
       			for (int n = 0; n < DATA_SIZE; n++){
       				if(m == DATA_CHANNELS)
       					window[m*DATA_SIZE + n] = in[n];
       				else
       					window[(m)*DATA_SIZE + n] = window[(m+1)*DATA_SIZE + n];
       				}
       			}

//convolution layer with padding 'same'
convolution:	for (filter = 0; filter < CONV1_FILTERS; filter++){
					for (channel_offset = 0; channel_offset < CONV1_CHANNELS; channel_offset += CONV1_STRIDE ){
						sum = 0;
						for(row_offset = 0; row_offset < CONV1_KERNEL_SIZE; row_offset++){
							for(column_offset = 0; column_offset < DATA_SIZE; column_offset++){
								sum += window[(channel_offset + row_offset)*DATA_SIZE + column_offset]*conv_layer_weights[row_offset][column_offset][filter];
								}
							}
						out[filter][channel_offset] = relu(sum + conv_layer_bias[filter]);
					}
    			}
}



void pool_layer(float24_t out[CONV1_FILTERS],float24_t in[CONV1_FILTERS][CONV1_CHANNELS]) {


	int i, j;
	float24_t average;


pooling:        for(i = 0; i < CONV1_FILTERS ; i++){
            		average = 0;
           			for (j = 0; j < CONV1_CHANNELS; j++){
           				average += in[i][j]/CONV1_CHANNELS;
            		}
            		out[i] = average;
        		}

}



void fc_layer(float24_t output[FC1_NEURONS], float24_t input[FC1_CHANNELS]){

	float24_t rel;

	NN:	for (int i = 0; i < FC1_NEURONS; i++) {
			rel = 0;
				for (int j = 0; j < FC1_CHANNELS; j++) {
					rel += input[j]*fc1_layer_weights[j][i] ;
				}
			output[i] = relu( rel  + fc1_layer_bias[i]);
		}
	}

void op_layer(float24_t out[OP_NEURONS], float24_t input[OP_CHANNELS]){

    float24_t rel, buff;

	output:	for (int i = 0; i < OP_NEURONS; i++) {
				rel = 0;
					for (int j = 0; j < OP_CHANNELS; j++) {
						rel += input[j]*op_layer_weights[j][i] ;
					}
				out[i]= relu( rel  + op_layer_bias[i]);
			}
}
