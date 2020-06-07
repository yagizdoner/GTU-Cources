/* Yaðýz Döner - 141044062 */

#include <stdio.h>

#define PI 3.14

float diameter(float circumference);

float ageOfTree(float diameter, float growth_factor);

int main(void)
{
	float circumference, growth_factor;
	
	float dia, age;
	
	printf("Enter Circumference of Tree : ");
	scanf("%f", &circumference);

	printf("Growth Factors of Some Species as following : \n");
	printf("American Elm  = 4 \nAustrian Pine = 4.5 \nBlack Cherry  = 5 \nScotch Pine   = 3.5\n");
	printf("Choose one of These : ");
	scanf("%f", &growth_factor);
	
	dia = diameter(circumference);
		
	age = ageOfTree(dia, growth_factor);
	
	printf("Diameter of The Tree is %.2f and Age of The Tree is %.2f", dia, age);
	
	return(0);
}

float diameter(float circumference)
{
	float radius, diameter;
	
	/*   Circumference = ( 2 * PI * radius )   */
	radius = circumference / (2.0 * PI);
	
	diameter = radius * 2.0 ;

	return(diameter);
}

float ageOfTree(float diameter, float growth_factor)
{
	float ageOfTree;
	
	ageOfTree = diameter * growth_factor ;
	
	return(ageOfTree);
}
