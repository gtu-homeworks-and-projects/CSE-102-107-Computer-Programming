#include <stdio.h>

#define MAX_WEIGHT 99999
#define SHORTEST_DAMAGE 4
#define COMFORTABLE_DAMAGE 2
#define SAFEST_DAMAGE 6
#define TOTAL_LIFE 30 // can change for different tests 


typedef enum _tileType {BORDER, WALL, EMPTY, USED, START} TILE_TYPE;
typedef enum _pathType {DISTANCE, COMFORT, DANGER} PATH_TYPE;
typedef enum _printType {P_DISTANCE, P_COMFORT, P_DANGER, P_TRAP} PRINT_TYPE;



typedef struct _tiles{
	TILE_TYPE type;
	int distance;
	int dangerLevel;
	int comfortLevel;
	int trapDamage;
}TILES;


typedef struct _coord{
	int x;
	int y;
}Coord;


typedef struct _path{
	Coord coords[200];
	int size;
	int totalDistance;
	int totalDanger;
	int totalComfort;
	int totalDamage;
}Path;


/*starter functions*/
int testMaze(char * fileName, Coord startTile, PATH_TYPE pType);
void readMaze(TILES maze[100][100], char * fileName, int *w, int *h);
void printMaze(TILES maze[100][100], int a, int b);
void printMazeWithValues(TILES maze[100][100], int a, int b, PRINT_TYPE pType);
void printAll(TILES maze[100][100], int a, int b);
void markPath(TILES maze[100][100], Path path);
void clearBoard(TILES maze[100][100]);

/*Required*/
int isStuck(TILES maze[100][100], Coord currentTile);
int isExit(TILES maze[100][100], Coord currentTile);
Path shortestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight);
Path comfortableExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight);
Path safestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight);

/*Optional*/
void addCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType);
void removeLastCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType);


int testMaze(char * fileName, Coord startTile, PATH_TYPE pType){
	int w = 0, h = 0;
	Path path, resultPath;
	int result = 0;

	TILES maze[100][100];
	int minWeight = MAX_WEIGHT;
	
	printf("Board name: %s\n", fileName);

	readMaze(maze, fileName, &w, &h);

	/*addCoord(maze, &path, startTile, pType);*/
	resultPath = shortestExit(maze, startTile, path, &minWeight);
	removeLastCoord(maze, &path, startTile, pType);

	markPath(maze, resultPath);
	maze[startTile.x][startTile.y].type = START;

	switch(pType){
		case DISTANCE:
			printf("Shortest Path\n");
			result = resultPath.totalDistance;
			printMazeWithValues(maze, w, h, P_DISTANCE);
			break;
		case COMFORT:
			printf("Comfortable Path\n");
			result = resultPath.totalComfort;
			printMazeWithValues(maze, w, h, P_COMFORT);
			break;
		case DANGER:
			printf("Safest Path\n");
			result = resultPath.totalDanger;
			printMazeWithValues(maze, w, h, P_DANGER);
			break;
	}

	printMaze(maze, w, h);

	printf("Total weight: %d\n", result);
	printf("-------------------------------------\n");
	return result;
}

/*marks path tiles as USED for printing*/
void markPath(TILES maze[100][100], Path path){
	int i = 0;

	for (i = 0; i < path.size; ++i){
		maze[path.coords[i].x][path.coords[i].y].type = USED;
	}
}

void readMaze(TILES maze[100][100], char * fileName, int *w, int *h){
	int i = 0, j = 0, tile = 0, distance, comfort, danger, trap;
	FILE *fp = fopen (fileName, "r");

	clearBoard(maze);

	fscanf(fp, "%d", w);
	fscanf(fp, "%d", h);

	/* Tile type*/
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &tile);
			switch(tile){
				case 0:
					maze[i][j].type = EMPTY;
					break;
				case 1:
					maze[i][j].type = WALL;
					break;
				case 2:
					maze[i][j].type = USED;
					break;
				case 3:
					maze[i][j].type = BORDER;
					break;
			}
		}
	}

	fscanf(fp, "%d", &distance);/*useless seperator*/

	/* distance values */
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &distance);
			maze[i][j].distance = distance;
		}
	}
	
	fscanf(fp, "%d", &comfort);/*useless seperator*/

	/* comfort values */
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &comfort);
			maze[i][j].comfortLevel = comfort;
		}
	}
	fscanf(fp, "%d", &danger);/*useless seperator*/

	/* danger values */
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &danger);
			maze[i][j].dangerLevel = danger;
		}
	}

	/* trap values */
	fscanf(fp, "%d", &trap);/*useless seperator*/

	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &trap);
			maze[i][j].trapDamage = trap;
		}
	}
  
	fclose(fp);
}

void printMaze(TILES maze[100][100], int a, int b){
	int i = 0, j = 0;
	
	printf("  ");
	for (j = 0; j < b; ++j){
		printf("%d ", j%10);
	}
	printf("\n");

	for (i = 0; i < a; ++i){
		printf("%d ", i%10);
		for (j = 0; j < b; ++j){
			switch(maze[i][j].type){
				case EMPTY:
					printf("  ");
					break;
				case WALL:
					printf("W ");
					break;
				case USED:
					printf(". ");
					break;
				case BORDER:
					printf("B ");
					break;
				case START:
					printf("* ");
					break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void printMazeWithValues(TILES maze[100][100], int a, int b, PRINT_TYPE pType){
	int i = 0, j = 0;
	
	printf("  ");
	for (j = 0; j < b; ++j){
		printf("%d ", j%10);
	}
	printf("\n");

	for (i = 0; i < a; ++i){
		printf("%d ", i%10);
		for (j = 0; j < b; ++j){
			if(maze[i][j].type == EMPTY || maze[i][j].type == USED || maze[i][j].type == START){
				if(pType == P_DISTANCE)
					printf("%d ", maze[i][j].distance);
				else if(pType == P_COMFORT)
					printf("%d ", maze[i][j].comfortLevel);
				else if(pType == P_DANGER)
					printf("%d ", maze[i][j].dangerLevel);
				else 
					printf("%d ", maze[i][j].trapDamage);
			}else if(maze[i][j].type == BORDER){
				printf("B ");
			}else{
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void printAll(TILES maze[100][100], int a, int b){
	printf("Distance Map:\n");
	printMazeWithValues(maze, a, b, P_DISTANCE);
	printf("Comfort Map:\n");
	printMazeWithValues(maze, a, b, P_COMFORT);
	printf("Danger Map:\n");
	printMazeWithValues(maze, a, b, P_DANGER);
	printf("Trap Map:\n");
	printMazeWithValues(maze, a, b, P_TRAP);
	printf("Path:\n");
	printMaze(maze, a, b);
}

void clearBoard(TILES maze[100][100]){
	int i = 0, j = 0;
	
	for (i = 0; i < 100; ++i){
		for (j = 0; j < 100; ++j){
			maze[i][j].type = BORDER;
		}
	}
}

/***********************************************************/

int isStuck(TILES maze[100][100], Coord currentTile){
	int emptyCounter = 0;
	if (maze[currentTile.x - 1][currentTile.y].type == EMPTY) emptyCounter++;
	if (maze[currentTile.x][currentTile.y - 1].type == EMPTY) emptyCounter++;
	if (maze[currentTile.x + 1][currentTile.y].type == EMPTY) emptyCounter++;
	if (maze[currentTile.x][currentTile.y + 1].type == EMPTY) emptyCounter++;

	if (emptyCounter > 0) return 0;
	else	return 1;
}

int isExit(TILES maze[100][100], Coord currentTile){
	int exit = 0;
	if (maze[currentTile.x - 1][currentTile.y].type == BORDER) exit++;
	if (maze[currentTile.x][currentTile.y - 1].type == BORDER) exit++;
	if (maze[currentTile.x + 1][currentTile.y].type == BORDER) exit++;
	if (maze[currentTile.x][currentTile.y + 1].type == BORDER) exit++;

	if (exit > 0) return 1;
	else	return 0;
}

Path shortestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight){

	if (maze[currentTile.x][currentTile.y].type != WALL)
	{
		*minWeight -= maze[currentTile.x][currentTile.y].distance + maze[currentTile.x][currentTile.y].trapDamage;
		
		addCoord(maze, &path, currentTile, DISTANCE);
		markPath(maze,path);
		if(isExit(maze,currentTile)) return path;
		else
		{
			if (!(isStuck(maze, currentTile)) && (*minWeight > 0))
			{

				if ( (maze[currentTile.x - 1][currentTile.y].type == EMPTY)  && (*minWeight > 0) )
  				{
  					currentTile.x -= 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					currentTile.x += 1;
  					
  				}
  				else if ((maze[currentTile.x + 1][currentTile.y].type == EMPTY) && (*minWeight > 0) )
  				{
  					currentTile.x += 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					currentTile.x -= 1;
  					
  				}
  				else if ((maze[currentTile.x][currentTile.y - 1].type == EMPTY) && (*minWeight > 0) )
  				{
  					currentTile.y -= 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					currentTile.y += 1;
  					
  				}
  				else if ((maze[currentTile.x][currentTile.y + 1].type == EMPTY) && (*minWeight > 0) )
  				{
  					currentTile.y += 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					currentTile.y -= 1;
  					
  				}
			}
		}
		removeLastCoord(maze, &path, currentTile, DISTANCE);
	}
	return path;
/*
 	if (*minWeight > 0)
 	{
  		maze[currentTile.x][currentTile.y].type = USED;
  		*minWeight -= maze[currentTile.x][currentTile.y].distance + maze[currentTile.x][currentTile.y].trapDamage;
  		if (isStuck(maze,currentTile) == 0)
  		{
  			
  			if (maze[currentTile.x + 1][currentTile.y].type == EMPTY)
  			{
  				currentTile.x += 1;
  				maze[currentTile.x][currentTile.y].type = USED;
  				addCoord(maze, &path, currentTile, DISTANCE);
  				path = shortestExit(maze, currentTile, path, minWeight);
  				removeLastCoord(maze, &path, currentTile, DISTANCE);
  				currentTile.x -= 1;
  			}
  			if (maze[currentTile.x - 1][currentTile.y].type == EMPTY)
  			{
  				currentTile.x -= 1;
  				maze[currentTile.x][currentTile.y].type = USED;
  				addCoord(maze, &path, currentTile, DISTANCE);
  				path = shortestExit(maze, currentTile, path, minWeight);
  				removeLastCoord(maze, &path, currentTile, DISTANCE);
  				currentTile.x += 1;
  			}
  			if (maze[currentTile.x][currentTile.y - 1].type == EMPTY)
  			{
  				currentTile.y -= 1;
  				maze[currentTile.x][currentTile.y].type = USED;
  				addCoord(maze, &path, currentTile, DISTANCE);
  				path = shortestExit(maze, currentTile, path, minWeight);
  				removeLastCoord(maze, &path, currentTile, DISTANCE);
  				currentTile.y += 1;
  			}
  			if (maze[currentTile.x][currentTile.y + 1].type == EMPTY)
  			{
  				currentTile.y += 1;
  				maze[currentTile.x][currentTile.y].type = USED;
  				addCoord(maze, &path, currentTile, DISTANCE);
  				path = shortestExit(maze, currentTile, path, minWeight);
  				removeLastCoord(maze, &path, currentTile, DISTANCE);
  				currentTile.y -= 1;
  			}
  		}
  	}
  	
  	return path;
*/
}

Path comfortableExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight){
	if (maze[currentTile.x][currentTile.y].type != WALL)
	{
		*minWeight -= maze[currentTile.x][currentTile.y].comfortLevel + maze[currentTile.x][currentTile.y].trapDamage;
		
		addCoord(maze, &path, currentTile, COMFORT);
		markPath(maze,path);
	
		if(isExit(maze,currentTile)) return path;
		else
		{
			if ((isStuck(maze, currentTile) != 1) && (*minWeight > 0))
			{
				
				
				if ( (maze[currentTile.x - 1][currentTile.y].type == EMPTY)  && (*minWeight > 0) )
  				{
  					currentTile.x -= 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					if(isExit(maze,currentTile)) return path;
  					currentTile.x += 1;
  				}
  				if ((maze[currentTile.x + 1][currentTile.y].type == EMPTY) && (*minWeight > 0) )
  				{
  					currentTile.x += 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					if(isExit(maze,currentTile)) return path;
  					currentTile.x -= 1;
  				}
  				if ((maze[currentTile.x][currentTile.y - 1].type == EMPTY) && (*minWeight > 0) )
  				{
  					currentTile.y -= 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					if(isExit(maze,currentTile)) return path;
  					currentTile.y += 1;
  				}
  				if ((maze[currentTile.x][currentTile.y + 1].type == EMPTY) && (*minWeight > 0) )
  				{
  					currentTile.y += 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					if(isExit(maze,currentTile)) return path;
  					currentTile.y -= 1;
  				}
			}
		}
		removeLastCoord(maze, &path, currentTile, COMFORT);
	}
	return path;
}

Path safestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight){
	if (maze[currentTile.x][currentTile.y].type != WALL)
	{
		*minWeight -= maze[currentTile.x][currentTile.y].dangerLevel + maze[currentTile.x][currentTile.y].trapDamage;
		
		addCoord(maze, &path, currentTile, DANGER);
		markPath(maze,path);

		if(isExit(maze,currentTile)) return path;
		else
		{
			if ((isStuck(maze, currentTile) != 1) && (*minWeight > 0))
			{
				
				
				if ( (maze[currentTile.x - 1][currentTile.y].type == EMPTY)  && (*minWeight > 0) )
  				{
  					currentTile.x -= 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					if(isExit(maze,currentTile)) return path;
  					currentTile.x += 1;
  				}
  				if ((maze[currentTile.x + 1][currentTile.y].type == EMPTY) && (*minWeight > 0) )
  				{
  					currentTile.x += 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					if(isExit(maze,currentTile)) return path;
  					currentTile.x -= 1;
  				}
  				if ((maze[currentTile.x][currentTile.y - 1].type == EMPTY) && (*minWeight > 0) )
  				{
  					currentTile.y -= 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					if(isExit(maze,currentTile)) return path;
  					currentTile.y += 1;
  				}
  				if ((maze[currentTile.x][currentTile.y + 1].type == EMPTY) && (*minWeight > 0) )
  				{
  					currentTile.y += 1;
  					path = shortestExit(maze, currentTile, path, minWeight);
  					if(isExit(maze,currentTile)) return path;
  					currentTile.y -= 1;
  				}
			}
		}
		removeLastCoord(maze, &path, currentTile, DANGER);
	}
	return path;
}


/***********************************************************/


void addCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType){
	int i;

	for (i = 0; (path->coords[i].x !=0) && (path->coords[i].y !=0); ++i);
	
	if (pType == DISTANCE)
	{
		path->totalDistance += maze[coord.x][coord.y].distance;
		path->totalDamage += SHORTEST_DAMAGE;
	}
	else if (pType == COMFORT)
	{
		path->totalComfort += maze[coord.x][coord.y].comfortLevel;
		path->totalDamage += COMFORTABLE_DAMAGE;
	}
	else if (pType == DANGER)
	{
		path->totalDanger += maze[coord.x][coord.y].dangerLevel;
		path->totalDamage += SAFEST_DAMAGE;
	}
	
	path->size++;
	path->coords[i].x = coord.x;
	path->coords[i].y = coord.y;
	printf("%d-%d,%d-%d\n", path->coords[i].x, path->coords[i].y, path->totalDistance, path->size);
}

void removeLastCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType){
	int i;

	for (i = 0; (path->coords[i].x !=0) && (path->coords[i].y !=0); ++i);

	if (pType == DISTANCE)
	{
		path->totalDistance -= maze[coord.x][coord.y].distance;
		path->totalDamage -= SHORTEST_DAMAGE;
	}
	else if (pType == COMFORT)
	{
		path->totalComfort -= maze[coord.x][coord.y].comfortLevel;
		path->totalDamage -= COMFORTABLE_DAMAGE;
	}
	else if (pType == DANGER)
	{
		path->totalDanger -= maze[coord.x][coord.y].dangerLevel;
		path->totalDanger -= SAFEST_DAMAGE;
	}
	path->size--;
	path->coords[i].x = 0;
	path->coords[i].y = 0;
}



int main(){

	Coord startTile1;
	startTile1.x = 5;
	startTile1.y = 2;


	testMaze("maze1.txt", startTile1, DISTANCE);
	testMaze("maze1.txt", startTile1, COMFORT);
	testMaze("maze1.txt", startTile1, DANGER);
	
	return 0;
}

