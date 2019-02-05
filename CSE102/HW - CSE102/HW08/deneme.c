#include <stdio.h>
#include <string.h>

int main(void)
{
	FILE * inp;
	int i[20], j[20], k, l;
	char phone[20][10][15];
	inp = fopen("input.txt","rt");
	char str[10][2][101];

	for (k = 0; fscanf(inp,"%d ",&i[k]) != EOF; ++k)
	{
		printf("%d in for\n",k );
		
		fscanf(inp,"%s %s %d ",str[k][0],str[k][1],&j[k]);
		for (l = 0; l < j[k]; ++l)
		{
			fscanf(inp,"%s ",phone[k][l]);
		}

	}
	printf("%d\n",k );
	printf("%-20s\n","-- " );
	for (k = 0; k < 5; ++k)
	{
		printf("%d %s %s %d",i[k],str[k][0],str[k][1],j[k]);
		for (l = 0; l < j[k]; ++l)
		{
			printf(" %s ",phone[k][l]);
		}
		printf("\n");
	}
	return 0;
}