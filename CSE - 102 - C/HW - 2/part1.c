#include <stdio.h>
void drawFunction(int xAxis, int yAxis, int functionNumber);
int fTheFunction(int x, int functionNumber);

void main(void){
	
	int functionNumber, xAxis, yAxis;
	 
	scanf("%d", &functionNumber);
	scanf("%d", &xAxis);
	scanf("%d", &yAxis);
	
	drawFunction(xAxis, yAxis, functionNumber);

}


int fTheFunction(int x, int functionNumber){
	if(functionNumber == 1)
		return(2*x);
}

void drawFunction(int xAxis, int yAxis, int functionNumber){
	
	int k, result, m, x;
	for( ; 0 < yAxis ; yAxis--){ /* This loop is for row number. */
		printf("|");
		for( x = xAxis ; -100 < x ; x-- ){ /* The number of 100 is selected randomly. */ 
			result = fTheFunction(x, functionNumber);
			if(result == yAxis){
				for( k = 1 ; k <= x ; k++ ){
					if( k != x){
						printf(" ");
					}
					else{
						printf("*\n");
					}
					 
				}
				break;
			}
			else if(result < yAxis){
				printf("\n");
				break;
			}
		}
	}
	for( m = 0 ; m < xAxis ; m++){
		printf("-");
	}
}
