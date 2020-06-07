#include <stdio.h>
#include <math.h>

void drawRectangle(int width,int height, int startingPoint, int printLastLine);
void drawDoubleCircle(int radius, int startingPoint, int whellDistance);
void drawCar();

int main(void){

		
	drawCar();

	
	return(0);
}

void drawCar(){
	
	int width, height, startingPoint, printLastLine;
	int width1, height1, startingPoint1, printLastLine1;
	int radius, startingPoint2, whellDistance;
	scanf("%d", &width);
	scanf("%d", &height);
	scanf("%d", &startingPoint);
	scanf("%d", &printLastLine);
	scanf("%d", &width1);
	scanf("%d", &height1);
	scanf("%d", &startingPoint1);
	scanf("%d", &printLastLine1);
	scanf("%d", &radius);
	scanf("%d", &startingPoint2);
	scanf("%d", &whellDistance);
	drawRectangle(width, height, startingPoint, printLastLine);	
	drawRectangle(width1, height1, startingPoint1, printLastLine1);
	drawDoubleCircle(radius, startingPoint2, whellDistance);
}

void drawRectangle(int width,int height, int startingPoint, int printLastLine){
	
	int h, s, w;
	
	for( h = 1 ; h <= height ; h++ ){
		for( s = 1 ; s <= startingPoint ; s++ ){
			printf(" ");
		}
		for( w = 1 ; w <= width ; w++ ){
			if(printLastLine == 1){
				if(h == 1 || h == height || w == 1 || w == width){
					printf("*");
				}
				else{
					printf(" ");
				}
			}
			if(printLastLine == 0){
				if(h == 1 || w == 1 || w == width){
					printf("*");
				}
				else{
					printf(" ");
				}
			}
		}
		printf("\n");
	}
}

void drawDoubleCircle(int radius, int startingPoint, int whellDistance){
	
	int i,j,a,d,x,y,z;
	
	y = radius + startingPoint;  /*horizonal*/
	x = radius;                  /*vertical*/
	z = radius + whellDistance;
		
	for(i = 0 ; i <= x+z ; i++){
		for(j = 0 ; j <= x+z ; j++){
			a = ((i-x)*(i-x))+((j-y)*(j-y));
			d = sqrt(a);
			if(radius >= d){
				printf("*");
			}
			else{
				printf(" ");
			}
		}
		for(j = 0 ; j <= x+z ; j++){
			a = ((i-x)*(i-x))+((j-z)*(j-z));
			d = sqrt(a);
			if(radius >= d){
				printf("*");
			}
			else{
				printf(" ");
			}	
		}
	printf("\n");
	}
}


