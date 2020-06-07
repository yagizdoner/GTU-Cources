#include <stdio.h>

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int *outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);

int main(void){
	double inputArr[] = {5, 6, 7, 8, 9};
	double outputArr[255];
	int outputArrSize = 0;
	addPadding(inputArr, 5 , outputArr, &outputArrSize, 4, samePadding);
	return(0);
}

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int *outputArraySize, int paddingWidth, void paddingMethod(double[], int, int)){
	int i;
	*outputArraySize = 0 ;
	for( i = 0 ; i < inputArraySize ; i++ ){
		outputArr[i] = inputArr[i];
		*outputArraySize += 1;
	}
	paddingMethod(outputArr, *outputArraySize, paddingWidth);
	for( i = 0 ; i < 2*paddingWidth + inputArraySize ; i++ )
		printf("%.2f\n",outputArr[i]);
}


void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth){
	int i,j,k,n;
	double Arr[2*paddingWidth + outputArraySize];
	for( i = 0 ; i<outputArraySize ; i++ ){       
		Arr[paddingWidth+i] = outputArr[i];       /* This Arr array is to make calculations.  */
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
	double Arr[2*paddingWidth + outputArraySize];
	for( i = 0 ; i<outputArraySize ; i++ ){
		Arr[paddingWidth+i] = outputArr[i];			/* This Arr array is to make calculations.  */
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
	double Arr[2*paddingWidth + outputArraySize];
	for( i = 0 ; i<outputArraySize ; i++ ){
		Arr[paddingWidth+i] = outputArr[i];			/* This Arr array is to make calculations.  */
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
