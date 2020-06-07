/* Yaðýz Döner - 141044062 */

#include <stdio.h>

#define A_Year 360
#define A_month 30

int theAge(int day,int month, int year, int today, int this_month, int this_year);

int daysLeft(int day, int month, int today, int this_month);

int main(void)

{
	int day, month, year, today, this_month, this_year;
	
	int age, days;
	
	/* Take information from the User */
	
	printf("Enter Your Birth Day   : ");
	scanf("%d", &day);
	printf("Enter Your Birth Month : ");
	scanf("%d", &month);
	printf("Enter Your Birth Year  : ");
	scanf("%d", &year);
	printf("Enter This Day   : ");
	scanf("%d", &today);	
	printf("Enter This Month : ");
	scanf("%d", &this_month);
	printf("Enter This Year  : ");
	scanf("%d", &this_year);
	
	age = theAge(day, month, year, today, this_month, this_year);
	
	days = daysLeft(day, month, today, this_month);
	
	printf("Age of the user is %d and %d Days Left to Birthday.", age, days);
	
	return(0);
		
}

int theAge(int day,int month, int year, int today, int this_month, int this_year)

{
	int age;
	
	
	age = ((12 - month) * A_month + A_month - day + (this_year - year - 1) * A_Year + (this_month - 1) * A_month + today) / A_Year ;
	
	return(age);
}

int daysLeft(int day, int month, int today, int this_month)

{
	int days;
	
	days = (month - this_month - 1) * A_month + A_month - today + day ;
	
	return(days);
}
