#include <stdio.h>

void hist(char str[], int hist[27]);
int bin2dec(int bin[]);
int dec2bin(int dec, int bin[]);

void upperCase(char str[]);

int main()
{
	int a[8] = {1,0,1,0,1,0,1,0},b[8],i;
	/*char str[] = "The quick brown fox jumps over the lazy dog.";
	int histogram[27],i;
	hist(str,histogram);
	for (i = 0; i < 26; ++i)
		printf("%c    => %d\n",'A'+i,histogram[i] );
	printf("Others => %d\n",histogram[i] ); */
	bin2dec(a);
	dec2bin(142,b);
	for (i = 0; i < 8; ++i)
	{
		printf("%d\n",b[i] );
	}
	
	return 0;
}

void hist(char str[], int hist[27])
{
	int i;

	for (i = 0; i < 27; ++i)	hist[i] = 0;
	upperCase(str);

	for (i = 0; str[i] != '\0'; ++i)
		if ((str[i] >= 'A') && (str[i] <= 'Z')) 
			hist[str[i]-'A']++;
		else
			hist[26] ++;
}

void upperCase(char str[])
{
	int i;

	for (i = 0; str[i]!= '\0'; ++i) 
		if ((str[i] >= 'a')	&& (str[i] <= 'z')) str[i] -= 'a' - 'A';
}

int bin2dec(int bin[])
{
	int i,j,dec = 0,pow;
	for (i = 0; i < 8; ++i)
	{
		if (bin[i] == 1)
		{
			for (j = (7-i), pow = 1; j > 0; --j)	pow *= 2;				
			dec+=pow;
		}
	}
	return dec;
}

int dec2bin(int dec, int bin[])
{
	int i,pow,j,err = 0;
	for (i = 0; i < 8; ++i)	bin[i] = 0;
	if (dec >= 0)
	{
		for (i = 0; i < 8; ++i)
		{
			for (j = (7-i), pow = 1; j > 0; --j)	pow *= 2;
			if (dec >= pow) 
			{
				bin[i] = 1;
				dec -= pow;
			}
		}
	}
	else	err = -1;

	return err;
}