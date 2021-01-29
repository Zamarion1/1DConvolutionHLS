

void conv_layer(float* output, float* datain,  float* weights, float* bias,
                    int dataSize, int channels, int kernel, int filters, int stride) {
            
    int  filter, row_offset,column_offset, channel_offset;
    float sum;
	static int readIndex{};
    //float* output{ new float[filters*channels]};


//	}

	for (filter = 0; filter < filters; filter++){
        for (channel_offset = 0; channel_offset < channels; channel_offset += stride){
            sum = 0;
            for(row_offset = 0; row_offset < kernel; row_offset++){
                for(column_offset = 0; column_offset < dataSize; column_offset++){				
					//std::cout << column_offset << '\t';
					//std::cout << filter << '\t';
					//std::cout << '\n';
                    sum += datain[(channel_offset + row_offset)*dataSize + column_offset] * weights[row_offset*filters*dataSize + column_offset*filters + filter];
					//std::cout << sum << '\t';
					//std::cout << val1 << '\n';
					//std::cout << val2 << '\t';
					//std::cout << '\n';
                    }
					
                }                
                output[filter*channels + channel_offset] = relu(sum + bias[filter]);
				//std::cout << relu(sum + bias[filter]) << '\n';
				//std::cout << sum << '\t';
				//std::cout << bias[filter] << '\n';
        }           
    }

    

}



void pool_layer(float* output, float* input, int size, int channels, int kernel, int stride, int outsize) {
    


	int i, j, k;
	float average;
    //static float output[P_OUT][P_CHANNELS];
    //float* output{new float[outsize*channels]};
    
    for (i = 0; i < size; i += stride){
        for(j = 0; j < channels ; j++){
            average = 0;
            for (k = 0; k < kernel; k++){
              average += (input[i*channels*kernel + j*kernel + k]) / kernel;  
            }
            output[i*j + j] = average;
        }
    }



}


void fc_layer(float* output, float* input, float* weights, float* bias, int neurons, int channels){
	
	
    //float* output = new float[neurons];
    float rel;
    
	for (int i = 0; i < neurons; i++) {
		rel = 0;
		for (int j = 0; j < channels; j++) {
            rel += input[j]*weights[j*neurons + i] ;

				//std::cout << " Neuron: " << i << '\n';
				//std::cout << " Channel:  " << j << '\n';
				
				
				//std::cout << " weight: " << weights[j*neurons + i] << '\n';
				//std::cout << " index " << j*neurons + i << '\n';
				//std::cout << " input:  " << input[j] << '\n';
				//std::cout << " value:  " << rel << '\n';
				//std::cout << '\n';
				//std::cout << '\n';
		}
		output[i] = relu( rel  + bias[i]);
		//std::cout << output[i] << '\n';
	}



}

