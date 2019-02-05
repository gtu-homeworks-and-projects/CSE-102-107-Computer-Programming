#include <stdio.h>

void drawRectangle(int width,int height, int startingPoint, int printLastLine);
void drawDoubleCircle(int radius, int startingPoint , int whellDistance);
void drawCar();

int main()
{
	/*drawRectangle(40,10,11,0);
	drawDoubleCircle(4, 7, 12);*/
	drawCar();
	return 0;
}

/*Function for drawing a rectangle based on given height, width, point of start and
 option for not printing last line */
void drawRectangle(int width,int height, int startingPoint, int printLastLine){
	int i;
	int	j;
	
	/*Printing first line*/
	for (j = 0; j < startingPoint; j++)
		{
			printf(" ");
		}
	for (i = 0; i < width; i++)
	{
		printf("*");
	}
	printf("\n");
	/* ------------------------------------------------------------ */
	
	/*Printing middle lines*/
	
	for (i = 0; i < (height - 1); i++)
	{
		for (j = 0; j < startingPoint; j++)
		{
			printf(" ");
		}
		printf("*");
		
		for (j = 0; j < (width - 2); j++)
		{
			printf(" ");
		}

		printf("*\n");
	}
	/* ------------------------------------------------------------ */

	/*Printing last line in case of need*/
	if (printLastLine == 1)
	{
		for (j = 0; j < startingPoint; j++)
		{
			printf(" ");
		}
		for (i = 0; i < width; i++)
		{
			printf("*");
		}
		printf("\n");
	}
	/* ------------------------------------------------------------ */
}
/* ------------------------------------------------------------ */

/* This function draws two circle seperated between spaces in the same rows */
void drawDoubleCircle(int radius, int startingPoint , int whellDistance){
 	int i,j,k;

 	/*Outer for loop responsible of rows*/
 	for (j = -radius + 1 ; j < radius; j++)
 	{
 		
 		/* Following for loop print spaces for starting point */
 		for (k = 0; k < startingPoint; k++)
 		{
 			printf(" ");
 		}
 		/* ------------------------------------------------------------ */

 		/* This for loop checks x and y values to put "*" or not column by
 		column */
 		for (i = -radius + 1 ; i < radius; i++)
 		{
 			if ((i*i+j*j) < radius*radius)
 			{
 				printf("* ");
 			}
 			else 
 			{
 				printf("  ");
 			}
 		}
 		/* ------------------------------------------------------------ */
 		
 		/* Sets the distance between circles*/
 		for (k = 0; k < whellDistance; k++)
 			{
 				printf(" ");
 			}
 		/* ------------------------------------------------------------ */

 		/* Same loop which checks x and y values for printing circle */
 		for (i = -radius + 1 ; i < radius; i++)
 		{
 			if ((i*i+j*j) < radius*radius)
 			{
 				printf("* ");
 			}
 			else 
 			{
 				printf("  ");
 			}
 		}
 		/* ------------------------------------------------------------ */

 		printf("\n"); /* End of a row */
 	}
}
/* ------------------------------------------------------------ */

/* Following function draws a car using two functions and their variety of
   their parameters */
void drawCar(){
	drawRectangle(40,10,11,0);
	drawRectangle(62,10,1,1);
	drawDoubleCircle(5, 7, 14);
}
/* ------------------------------------------------------------ */
