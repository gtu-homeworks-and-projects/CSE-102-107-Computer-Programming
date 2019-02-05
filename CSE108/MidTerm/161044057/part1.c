#include <stdio.h>

void lowercase(char arr[]);
int ifind(char haystack[], char needle[]);
int count(char haystack[], char needle[]);

int main()
{
	char haystack[255] = "deHedeheDeHEDE", needle[255] = "hede";
	char haystack1[255] = "heHeheheheHEHE", needle1[255] = "hehe";
	printf("%d, %d\n",ifind(haystack,needle) , count(haystack,needle));
	printf("%d, %d\n",ifind(haystack1,needle1) , count(haystack1,needle1));

	return 0;
}

void lowercase(char arr[])
{
	int i,diff;
	diff = 'a' - 'A';
	for (i = 0; arr[i] != '\0'; i++)
		if ((arr[i] <= 'Z') && (arr[i] != ' '))
			arr[i] += diff;

}

int ifind(char haystack[], char needle[])
{
	int	i, j, k, needleLen, res = -1, count = 0;

	lowercase(haystack);
	lowercase(needle);

	for (needleLen = 0; needle[needleLen] != '\0'; needleLen++);

	for (i = 0; haystack[i] != '\0'; ++i)
	{
		for (j = 0, k = i; needle[j] != '\0'; ++j, ++k)
			if (haystack[k] == needle [j]) count++ ;
		if (count == needleLen)
		{
			res = k - needleLen;
			break;
		}
		else count = 0;

				
	}
	return res;
}

int count(char haystack[], char needle[])
{
	int	i, j, k, needleLen, count = 0, matchCount = 0;

	lowercase(haystack);
	lowercase(needle);

	for (needleLen = 0; needle[needleLen] != '\0'; needleLen++);

	for (i = 0; haystack[i] != '\0'; ++i)
	{
		for (j = 0, k = i; needle[j] != '\0'; ++j, ++k)
			if (haystack[k] == needle [j]) count++ ;
		if (count == needleLen)
		{
			matchCount++ ;
			count = 0;
			i += needleLen - 1;
		}
		else count = 0;

				
	}
	return matchCount;
}