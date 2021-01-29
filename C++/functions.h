

float relu(float a){
	if (a > 0)
		return a;
	return 0;
}


void readFile(float* data, int numCols, std::string csvfile  )
{

    int row{};
    int col{};
    int depth{};
    //float* data{new float[numCols*numRows*numDepth]};
	//static float* data[numCols*numRows*numDepth]{};
    static std::ifstream file(csvfile);
	std::string val;
	
	for ( col = 0; col < (numCols); ++col){    
		std::getline(file, val, ',');
		if ( !file.good() )
			break;
		std::stringstream convertor(val);
		convertor >> data[col];
		
	}
	std::getline(file, val, ',');
	std::cout<< "expected X: " << val  << '\t';
	std::getline(file, val, '\n');
	std::cout<< "expected Y: " << val  << '\n';
}
	


void printArray(std::string name, float* datain, int numRows, int numCols,int numDepth){
    std::cout<< name  << '\n';
	//std::cout<< "rows: " << numRows <<  " columns: " << numCols << '\n';

    for(int depth = 0; depth < numDepth; depth++){
		//std::cout<< "depth:" << depth  << '\n';
        for ( int row =  0 ; row < numRows; ++row){
            for (int col =  0 ; col < numCols; ++col){
				//std::cout << depth << row << col << '\t';
                std::cout << datain[depth*numRows*numCols + row*numCols + col] << '\t';
            }
            std::cout << '\n';
        }
    }  
	std::cout << '\n';  
}


