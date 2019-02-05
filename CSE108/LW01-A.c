#include <stdio.h>

int readInt();
double readDouble();
char readChar();
double calculateBMI(int height, int weight) ;
double getInfoAndCalculateBMI();
void printPersonalInfo(int id, char name, int height, double weight);
void getAndPrintPersonalInfo();	

int main()
{
	getAndPrintPersonalInfo();
	
	return 0;
}

int readInt()
{
	int a;
	printf("Enter an integer: ");
	scanf("%d", &a);
	return a;
}

double readDouble()
{
	double a;
	printf("Enter a float: ");
	scanf("%lf", &a);
	return a;
}

char readChar()
{
	char a;
	printf("Enter a character: ");
	scanf("%s", &a);
	return a;
}

double getInfoAndCalculateBMI()
{
	int h;
	int w;
	printf("**BMI Score Testing**\n\n");
	printf("Height (in cm)\n");
	h = readInt();
	printf("Weight (in kg)\n");
	w = readInt();
	printf("Your BMI Score: %.2f\n\n",calculateBMI(h,w) );
	return calculateBMI(h,w);
}

double calculateBMI(int height, int weight)
{
	double BMI;
	double cnv = 100;
	double height_meter = height/cnv;
	BMI = weight/height_meter/height_meter;
	return BMI;
}

void getAndPrintPersonalInfo()
{
	int id, height;
	char name;
	double weight;
	printf("Enter Your ID \n");
	id = readInt();
	printf("Enter Your Name's First Letter \n");
	name = readChar();
	printf("Height (in cm)\n");
	height = readInt();
	printf("Weight (in kg)\n");
	weight = readDouble();
	printPersonalInfo(id, name, height, weight);


}

void printPersonalInfo(int id, char name, int height, double weight)
{
	printf("ID:%d\n", id);
	printf("Name:%c\n", name );
	printf("Height:%d\n", height );
	printf("Weight:%.2f\n", weight);
	printf("BMI:%.2f\n", calculateBMI(height, weight) );
}