#include <stdio.h>

int isPrime(int num);
int goldbach(int num, int *p1, int *p2);

void main(void){
	int num, p1, p2 ;
	scanf("%d", &num);
	if(goldbach(num,&p1,&p2))
		printf("%d = %d + %d",num,p1,p2); /* may print 824 = 821 + 3 */
	else
		printf("You should provide even number.");
}

int isPrime(int num){
	
	int i, status ;
	status = 1 ;
	
	if(num >= 2){
		for( i = 2 ; (i < num) && (status == 1) ; i++ ){
			if(num % i == 0)
				status = 0;
		}
	}
	else
		status = 0;
	return(status);	
}

int goldbach(int num, int *p1, int *p2){
	
	int status, i, k, temp;
	
	if( (num % 2 == 0) && (num > 2) ){	
		for( i = 2 ; i <= num - 2 ; i++ ){
			if(isPrime(i)){
				*p1 = i ;
				for( k = 2 ; k <= num ; k++ ){
					temp = num - *p1 ;  /* This temporary variable is for check p2 is a prime number or not. */
					if(isPrime(temp)){
						*p2 = temp ;
					}
				}
			}
		}	
		status = 1 ;
	}
	else
		status = 0 ;
		
	return(status);	
}
