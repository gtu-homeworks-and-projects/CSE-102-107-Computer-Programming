#include <stdio.h>

#define GRIDSIZE 4


typedef enum {mined, empty, flaggedMined, flaggedEmpty, closedEmpty, closedMined}cell;

void printGrid (cell grid[][GRIDSIZE]);
int openCell(cell grid[][GRIDSIZE], int x, int y);
void flagCell(cell grid[][GRIDSIZE], int x, int y);
int isCellEmpty(cell grid[][GRIDSIZE], int x, int y);
int isLocationLegal(int x, int y);
void initGrid(cell grid[][GRIDSIZE]);
int asMain();

int main()
{
	asMain();
	return 0;
}

int asMain()
{
	int i,j,x,y,userInput,controlVar = 1,step = 0,emptyCounter;
	/* userInput for storing user decision */
	/* if controlVar is 2 you won, if it's 0 you lost, 1 means you keep playing */
	/* step is move count */
	/* emptyCounter checks the grid if there is any closed empty left */
	cell grid[GRIDSIZE][GRIDSIZE];
	initGrid(grid); /* Initialize the grid */
	do
	{
		emptyCounter = 0; /* resetting empty counter every iteration */
		
		for (i = 0; i < GRIDSIZE; ++i) /* For loop for rows */
			for (j = 0; j < GRIDSIZE; ++j) /* For loop for columns */
				
				/* Increase counter if there is still closedEmpty left */
				if (isCellEmpty(grid, i, j)) emptyCounter++; 
				/* ---------------------------------------- */

		if (emptyCounter == 0) controlVar = 2; /* Finish game if there isn't any closedEmpty cell left */
		else
		{

			printGrid(grid); /* Prints grid */

			/* obtainin which coordinate to operate and what to do */
			printf("Choose Location (x): ");
			scanf(" %d", &x);
			printf("Choose Location (y): ");
			scanf(" %d", &y);
			printf("Choose what to do (1 opens cell, 0 flags/unflags cell): ");
			scanf(" %d", &userInput);
			/* ---------------------------------------- */

			/* Calling functions according to users choice */
			switch (userInput)
			{
				case 0: 
					flagCell(grid, x, y);
					break;

				case 1: 
					controlVar = openCell(grid, x, y);
					break;
			}
			/* ---------------------------------------- */

			step++ ; /* Move counter */
		}
	}	while ((controlVar != 0) && (controlVar != 2));
	
	if (controlVar == 2)	
		printf("Congratulations! You win the game with %d moves\n",step);

	else if (controlVar == 0) 
		printf("Sorry, that was a bomb.\n");

	return controlVar;
}

void printGrid (cell grid[][GRIDSIZE])
{
	int i,j;
	for (i = 0; i < GRIDSIZE; ++i) /* For loop for rows */
	{
		for (j = 0; j < GRIDSIZE; ++j) /* For loop for columns */
		{	
			/* Printing grid according to its specifications */
			if ((grid[i][j] == closedEmpty) || (grid[i][j] == closedMined))	
				printf(". ");
			if ((grid[i][j] == flaggedEmpty) || (grid[i][j] == flaggedMined))	
				printf("f ");
			if (grid[i][j] == empty)	printf("e ");
			/* ---------------------------------------- */
		}
		printf("\n"); /* Finishing every row with \n */
	}

}

void initGrid(cell grid[][GRIDSIZE])
{
	int i,j;
	for (i = 0; i < GRIDSIZE; ++i) /* For loop for rows */
		for (j = 0; j < GRIDSIZE; ++j) /* For loop for columns */	
			grid[i][j] = closedEmpty; /* Filling grid with closed empty cells */

	for (i = 0; i < GRIDSIZE; i += 2) /* For loop for rows */
		for (j = 1; j < GRIDSIZE; j += 2) /* For loop for columns */
			grid[i][j] = closedMined; /* Placing bombs */
}

int isLocationLegal(int x, int y)
{
	int i = 0;
	/* Following code checks x and y is in grid or not */
	if ((y < GRIDSIZE) && (x < GRIDSIZE) && (x >= 0) && (y >= 0))	i = 1;
	return i;
}

int isCellEmpty(cell grid[][GRIDSIZE], int x, int y)
{
	int i = 0;
	/* Following code checks cell is empty or not */
	if (grid[x][y] == closedEmpty)	i = 1;
	else if (grid[x][y] == flaggedEmpty)	i = 1;
	return i;
}

void flagCell(cell grid[][GRIDSIZE], int x, int y)
{
	/* Followind code flags/unflags cells */
	if ((isLocationLegal(x, y)) && (grid[x][y] == closedEmpty))	
		grid[x][y] = flaggedEmpty;

	else if ((isLocationLegal(x, y)) && (grid[x][y] == closedMined))	
		grid[x][y] = flaggedMined;

	else if ((isLocationLegal(x, y)) && (grid[x][y] == flaggedMined))	
		grid[x][y] = closedMined;

	else if ((isLocationLegal(x, y)) && (grid[x][y] == flaggedEmpty))	
		grid[x][y] = closedEmpty;
	else
		printf("You can't flag opened cell\n");
	/* ---------------------------------------- */
}

int openCell(cell grid[][GRIDSIZE], int x, int y)
{
	int i,j,k = -2; /* k = -2 if location is illegal */
	if (isLocationLegal(x, y))
	{
		switch(grid[x][y])
		{
		
		case closedEmpty :
			grid[x+i][y+j] = empty;
			for (i = -1; i < 2; ++i) /* For loop for 3 rows */
				for (j = -1; j < 2; ++j) /* For loop for 3 columns */
					if ((grid[x+i][y+j] == 4) && (y+j < GRIDSIZE) &&  /* If conditions makes sure */
						(x+i < GRIDSIZE) && (x+i >= 0) && (y+j >= 0)) /* cell is empty and in boundaries */
							opencell(grid,x+i,y+j); /* Turns cell to empty if it's viable */
			k = 1;
			break;
		
		case empty :
			printf("Cell is already opened.\n");
			k = -2; /* Return value in case of illegalmove (empty cell) */
			break;

		case flaggedMined :
		case flaggedEmpty :
			printf("Cell is flagged.\n");
			k = -2; /* Return value in case of illegalmove (flagged cell) */
			break;
		
		case mined : /* Can't select "mined" cell but to avoid warnings */		 
		case closedMined :
			grid[x][y] = mined; /* sets selected cell "mined" */
			k = 0; /* Return value in case of hitting the bomb */
			break;


		}
	}
	return k;
}