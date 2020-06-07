#include <stdio.h>

int dispenseChange(double paid, double due, int *tl1, int *krs50, int *krs25, int *krs10, int *krs5, int *krs1 );

int main(void){
	double paid, due;
	int tl1, krs50, krs25, krs10, krs5, krs1;
	scanf("%lf", &paid);	
	scanf("%lf", &due);
	if( dispenseChange(paid,due,&tl1,&krs50, &krs25, &krs10, &krs5, &krs1) )
		printf("Change: 1TL:%d, Kurus-50:%d,25:%d,10:%d,5:%d,1:%d\n",tl1,krs50,krs25,krs10,krs5,krs1);
	else
		printf("Unable to dispense change.");
	return(0);
}

int dispenseChange(double paid, double due, int *tl1, int *krs50, int *krs25, int *krs10, int *krs5, int *krs1 ){
	double change;
	int status;
	
	change = paid - due;
	
	if(change > 0.0){
		*tl1 = (int)(change / 1);
		change -= *tl1 * 1.0 ; 
		*krs50 = (int)(change / 0.5);
		change -= *krs50 * 0.5 ;
		*krs25 = (int)(change / 0.25);
		change -= *krs25 * 0.25 ;
		*krs10 = (int)(change / 0.1);
		change -= *krs10 * 0.1 ;				
		*krs5 = (int)(change / 0.05);
		change -= *krs5 * 0.05 ;
		*krs1 = change;	
		status = 1;
	}
	else{
		status = 0;
	}
	return(status);
}
