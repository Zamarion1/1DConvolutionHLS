#include <stdio.h>
#include <string.h>
#include "ap_fixed.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define EXP_WIDTH	20
#define INT_WIDTH	4

typedef ap_fixed<EXP_WIDTH, INT_WIDTH> float24_t;


void CNN(float24_t datain[16], float24_t op_out[2]);

int main(){
	setvbuf(stdout,NULL,_IONBF,0);
	float24_t vector[100][16]{};
	float24_t datain[16]{};
	float24_t op_out[2]{};
	float temp{};

	//read values from preprocessed data file and store it in Datain
	FILE *file = fopen("preprocessed.csv", "r");
	if(file == NULL) exit(1);
	char line[200];
	char *token;

	for(int i = 0; i < 100; i ++){ 			//perform the test 100 times
		fgets(line, sizeof(line), file);
		token = strtok(line, ",");
		for (int col = 0; col < 16; ++col){
			temp = strtod(token,NULL);
			datain[col] = (float24_t) temp; // cast temporary value to the fixed point implementation
			token = strtok(NULL,",");
		}
		printf("\n");
		CNN(datain, op_out);
		printf("iteration: %i \n", i);
		printf("out1: %f \t out2: %f \n", op_out[0].to_float(), op_out[1].to_float());
	}




	return 0;
}
