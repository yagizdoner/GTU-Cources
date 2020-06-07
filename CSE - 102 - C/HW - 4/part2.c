#include <stdio.h>

typedef enum {ZERO, SAME, HALF} PaddingType;
int convolution(double inputArr[], int inputArraySize, double kernelArr[], int kernelArraySize, double outputArr[], int *outputArraySize, int stride, PaddingType padding);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);

int main(void){
	double inputArr[] = {1, 3, 5, 7, 9, 11, 13};
	double kernelArr[] = {2, 4, 6};
	double outputArr[255];
	int outputArrSize = 0;
	convolution(inputArr, 7, kernelArr, 3, outputArr, &outputArrSize, 2, ZERO);
	return(0);
}

int convolution(double inputArr[], int inputArraySize, double kernelArr[], int kernelArraySize, double outputArr[], int *outputArraySize, int stride, PaddingType padding){
	int i,j,m,n,status,paddingWidth;
	if(kernelArraySize <= inputArraySize){
		paddingWidth = (kernelArraySize -1) / 2 ;
		switch(padding){
			case ZERO: zeroPadding(inputArr, inputArraySize, paddingWidth);
					   break;
			case SAME: samePadding(inputArr, inputArraySize, paddingWidth);
					   break;
			case HALF: halfPadding(inputArr, inputArraySize, paddingWidth);
					   break;
			default:   break;
		}
		/* This If block is for stride equal to 1. */ 
		if(stride == 1){	
			*outputArraySize = inputArraySize + 2*paddingWidth;															
			for( m=0 ; m < inputArraySize ; m++){												 
				outputArr[m] = 0;																 	
				i= m;																			 
				j= 0;																			 	
				while(i < *outputArraySize && j < kernelArraySize){	     	
					outputArr[m] += inputArr[i] * kernelArr[j] ;								 	
					i++;																		 
					j++;																		 
				}																				 
			}																				 	
			status = 0;																			 
		}	
		/* This Else block is for stride diffirent from 1. */																					 
		else{
			*outputArraySize = ((inputArraySize + 2*paddingWidth - kernelArraySize) / stride) + 1;
			n=0;
			for( m=0 ; m < *outputArraySize * stride ; m+=stride){
				outputArr[n] = 0;
				i= m; 																    
				j= 0;
				while(i < inputArraySize + 2*paddingWidth && j < kernelArraySize){
					outputArr[n] += inputArr[i] * kernelArr[j] ;
					i++;
					j++;
				}
				n++;
			}	
			status = 0;
		}
	}
	/* This block is for error condition. */
	else
		status = -1;
	return(status);
}

void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth){
	int i,j,k,n;
	double Arr[255];
	for( i = 0 ; i<outputArraySize ; i++ ){       
		Arr[paddingWidth+i] = outputArr[i];
	}
	for( j = 0 ; j<paddingWidth ; j++ ){
		Arr[j] = 0;
	}
	for( k = paddingWidth + outputArraySize  ; k < 2*paddingWidth + outputArraySize ; k++ ){
		Arr[k] = 0;
	}
	for( n=0 ; n < 2*paddingWidth + outputArraySize ; n++){  
		outputArr[n] = Arr[n];
	}
}

void samePadding(double outputArr[], int outputArraySize, int paddingWidth){
	int i,j,k,n;
	double Arr[255];
	for( i = 0 ; i<outputArraySize ; i++ ){
		Arr[paddingWidth+i] = outputArr[i];
	}
	for( j = 0 ; j<paddingWidth ; j++ ){
		Arr[j] = outputArr[0];
	}
	for( k = paddingWidth + outputArraySize  ; k < 2*paddingWidth + outputArraySize ; k++ ){
		Arr[k] = outputArr[outputArraySize-1];
	}
	for( n=0 ; n < 2*paddingWidth + outputArraySize ; n++){
		outputArr[n] = Arr[n];
	}
}

void halfPadding(double outputArr[], int outputArraySize, int paddingWidth){
	int i,j,k,n;
	double Arr[255];
	for( i = 0 ; i<outputArraySize ; i++ ){
		Arr[paddingWidth+i] = outputArr[i];
	}
	for( j = 0 ; j<paddingWidth ; j++ ){
		Arr[j] = outputArr[0] / 2;
	}
	for( k = paddingWidth + outputArraySize  ; k < 2*paddingWidth + outputArraySize ; k++ ){
		Arr[k] = outputArr[outputArraySize-1] / 2;
	}
	for( n=0 ; n < 2*paddingWidth + outputArraySize ; n++){
		outputArr[n] = Arr[n];
	}
}
