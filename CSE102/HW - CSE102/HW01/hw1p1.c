#include <stdio.h>

int theAge(int day,int month, int year, int today,int this_month, int this_year );
int daysLeft(int day,int month, int today,int this_month);

float diameter(float circumference);
float ageOfTree(float diameter , float growth_factor);

int main(void)
{
	int day, month, year;
	printf("Day of Birth: ");
	scanf("%d", &day);
	printf("Month of Birth: ");
	scanf("%d", &month);
	printf("Year of Birth: ");
	scanf("%d", &year);
	printf("You are %d years old.\n",theAge(day, month, year, 3, 3, 2017));
	printf("%d days left to your birthday.\n", daysLeft(day, month, 3, 3));
	return 0;
}

int theAge(int day,int month, int year, int today,int this_month, int this_year )
{
	int days_of_birth;
	int days_of_today;
	int age;
	days_of_birth = day + (month-1)*30 + (year-1)*365;
	days_of_today = today + (this_month-1)*30 + (this_year-1)*365;
	age = days_of_today - days_of_birth;
	return age/365;


}

int daysLeft(int day,int month, int today,int this_month)
{
	int days_of_birth;
	int days_of_today;
	int days;
	days_of_birth = day + (month-1)*30;
	days_of_today = today + (this_month-1)*30;
	days = 365 - (days_of_today - days_of_birth);
	return days%365;
}

float diameter(float circumference)
{
	float pi = 3.14;
	float dia = circumference/pi;
	return dia;
}

float ageOfTree(float diameter , float growth_factor)
{
	float aot = diameter * growth_factor;
	return aot;
}