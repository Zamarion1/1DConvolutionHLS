#include "functions.h"
#include "ap_fixed.h"

#define EXP_WIDTH	16
#define INT_WIDTH	4


typedef ap_fixed<EXP_WIDTH, INT_WIDTH> float24_t;




void conv_layer(float24_t output[CONV1_CHANNELS][CONV1_FILTERS],volatile float24_t datain[DATA_CHANNELS][DATA_SIZE],const  float24_t weights[CONV1_KERNEL_SIZE][CONV1_DATA_SIZE][CONV1_FILTERS],const float24_t bias[CONV1_FILTERS]) {



    int  filter, row_offset,column_offset, channel_offset;
    float24_t sum;

	for (filter = 0; filter < CONV1_FILTERS; filter++){
        for (channel_offset = 0; channel_offset < CONV1_CHANNELS; channel_offset += CONV1_STRIDE ){
            sum = 0;
            for(row_offset = 0; row_offset < CONV1_KERNEL_SIZE; row_offset++){
                for(column_offset = 0; column_offset < DATA_SIZE; column_offset++){

                    static float24_t val1, val2;
                    if ((channel_offset + row_offset == 0) || ((channel_offset + row_offset)  == (CONV1_CHANNELS + CONV1_KERNEL_SIZE - 2))){
                        val1 = 0;
                    }
                    else{
                    	val1 = datain[channel_offset + row_offset][column_offset];
                    }

                    val2 = weights[row_offset][column_offset][filter];

                    sum += val1 * val2;

                    }

                }

            output[filter][channel_offset] = relu(sum + bias[filter]);

        }
    }



}



void pool_layer(float24_t output[P1_CHANNELS], float24_t input[CONV1_CHANNELS][CONV1_FILTERS]) {



	int i, j, k;
	float24_t average;

    for (i = 0; i < P1_KERNEL_SIZE; i += P1_STRIDE){
        for(j = 0; j < P1_CHANNELS ; j++){
            average = 0;
            for (k = 0; k < P1_KERNEL_SIZE; k++){
              average += (input[i][j + k]) /P1_KERNEL_SIZE;
            }
            output[j] = average;
        }
    }
}



void fc_layer(float24_t output[FC1_NEURONS], float24_t input[FC1_CHANNELS], const float24_t weights[FC1_CHANNELS][FC1_NEURONS], const float24_t bias[FC1_NEURONS]){



    float24_t rel;

	for (int i = 0; i < FC1_NEURONS; i++) {
		rel = 0;
		for (int j = 0; j < FC1_CHANNELS; j++) {
			rel += input[j]*weights[j][i] ;
		}
		output[i] = relu( rel  + bias[i]);
	}
}

void op_layer(float24_t output[OP_NEURONS], float24_t input[OP_CHANNELS], const float24_t weights[OP_CHANNELS][OP_NEURONS], const float24_t bias[OP_NEURONS]){



    float24_t rel;

	for (int i = 0; i < OP_NEURONS; i++) {
		rel = 0;
		for (int j = 0; j < OP_CHANNELS; j++) {
			rel += input[j]*weights[j][i];
		}
		output[i] = relu( rel  + bias[i]);
	}
}
