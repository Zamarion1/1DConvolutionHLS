#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "defines.h"
#include "functions.h"
#include "Modules.h"
#include "weights.h"

int main(){

    
    //float data_in  [DATA_SIZE] {};      
    //float conv_out [CONV_CHANNELS][CONV_FILTERS] {};
    
	float datain[DATA_SIZE]{};
	float window[DATA_SIZE*(DATA_CHANNELS+2)]{};
	float conv1_out[CONV1_CHANNELS*CONV1_FILTERS]{};
	float pool1_out[P1_OUT*P1_CHANNELS]{};
	float fc1_out[FC1_NEURONS]{};
	float op_out[OP_NEURONS]{};

	int i{};
	
	for(i = 0; i < 100; i++){
		std::cout << "iteration: " << i << '\n';
		readFile(datain, DATA_SIZE, "preprocessed.csv" );
		
		//printArray("datain", datain, 1, DATA_SIZE, 1);
		
		for(int m = 1; m <= DATA_CHANNELS; m++){
			for (int n = 0; n < DATA_SIZE; n++){
				if(m == DATA_CHANNELS) 
					window[(m)*DATA_SIZE + n] = datain[n];
				else 
					window[(m)*DATA_SIZE + n] = window[(m+1)*DATA_SIZE + n];
			}
		}
		
		
		
		

		
		
		if(i>=0){
			printArray("window", window, (DATA_CHANNELS+2), DATA_SIZE, 1);
			conv_layer(conv1_out, window, conv_layer_weights,conv_layer_bias, CONV1_DATA_SIZE,CONV1_CHANNELS, CONV1_KERNEL_SIZE, CONV1_FILTERS, CONV1_STRIDE );
			//printArray("convolution", conv1_out,32, 5, 1);


			pool_layer(pool1_out, conv1_out, P1_SIZE, P1_CHANNELS, P1_KERNEL_SIZE, P1_STRIDE, P1_OUT );
			//printArray("pooling",pool1_out, P1_CHANNELS, P1_OUT,  1);

			//flatten1_out = flatten(pool1_out, P1_OUT, P1_CHANNELS);

			fc_layer(fc1_out, pool1_out,fc1_layer_weights, fc1_layer_bias,FC1_NEURONS,FC1_CHANNELS);
			//printArray("fully connected", fc1_out, FC1_NEURONS, 1, 1);

			fc_layer(op_out,fc1_out, op_layer_weights, op_layer_bias,OP_NEURONS,OP_CHANNELS);
			
			
			printArray("output layer",op_out, OP_NEURONS, 1, 1);
			
		}
    
    }
}
