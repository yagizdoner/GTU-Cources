#include <stdio.h>

int charge(int cardType, int* monthlyUse, double* balance);

void main(void){
	int monthlyUse = 0;
	double balance = 20.0;
	if(charge(2,&monthlyUse, &balance) == 0)
		printf("Remaining monthly use: %d - Remaining Balance: %.2f\n",monthlyUse,balance);
	else
		printf("Insufficient balance.");
}

int charge(int cardType, int *monthlyUse, double *balance){
	
	int status;
	if(*monthlyUse > 1 || *balance > 0.0 ){
		switch(cardType){
			case 1 : if(*monthlyUse > 1){               /* Case 1 is for normal card. */
						*monthlyUse = *monthlyUse - 1 ;
					 }
					 else{
					 	*balance = *balance - 2.30 ;
					 }								
					 status = 0 ;
				     break;
			case 2 : if(*monthlyUse > 1){               /* Case 2 is for student card. */
						*monthlyUse = *monthlyUse - 1 ;
					 }
					 else{
					 	*balance = *balance - 1.15 ;
					 }								
					 status = 0 ;
					 break;
			case 3 : if(*monthlyUse > 1){                /* Case 3 is for teacher card. */
						*monthlyUse = *monthlyUse - 1 ;
					 }
					 else{
					 	*balance = *balance - 2.30 ;
					 }								
					 status = 0 ;
					 break;
			default  : status = -2;   
		}
	}
	else{
		status = -1 ;
	}
	return(status);
}
