#include <stdio.h>
#include <math.h>


int fTheFunction(int x,int functionNumber);
void drawFunction(int xAxis, int yAxis, int functionNumber);

int main()
{
	drawFunction(20,15,1);
	return 0;
}

int fTheFunction(int x,int functionNumber){
	if (functionNumber==1)
	{
		x = 2*x-5;
	}
	else if (functionNumber==2)
	{
		x = 3*x;
	}
	return x ;
}

/*
This function draws function according to given X and Y axis numbers 
for the function specified by another function called "fTheFunction" 
*/
void drawFunction(int xAxis, int yAxis, int functionNumber){
	
	int i,j,k; /*Variables for for loops*/
	
	for (i = yAxis; i > 0; i--) /* Starting from top y value and decrementing until 0 */
	{
		printf("|"); /*Left Border*/
		
		for (j = 1; j <= xAxis; j++) /* xAxis starting from 1 */
		{
			
			/* if function result matches prints "*" else space */

			if ((fTheFunction(j,functionNumber))==i)
			{
				printf("*");
			}
			else {
				printf(" ");
			}
			
		}
		
		printf("\n"); /* Finishing a line */
		
	}
	
	/* Drawing bottom line starting with a space */

	printf(" ");
	for (k = 0; k < xAxis; k++)
		{
				printf("-");
		}
			printf("\n");

}

