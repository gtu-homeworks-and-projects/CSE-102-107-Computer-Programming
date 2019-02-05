#include <stdio.h>

char* reverse (char str[], char rev[]);
char* tostr(int num, char str[]);
char* combine (char str1[], char str2[], char str3[], char res[]);
char* convert(char str1[], int num, char res[]);

int main()
{
	char str[255] = "herhalde", str2[255] = "turta", str3[255] = "donmus", res[255];
	int dec = 65109;
	printf("reverse of %s:  '%s'\n",str,reverse(str,res) );
	printf("tostr(%d): '%s'\n",dec,tostr(dec,res));
	printf("combine(%s,%s,%s): '%s'\n",str,str2,str3,combine(str,str2,str3,res) );
	printf("convert(%s,%d): '%s'\n",str,dec,convert(str,dec,res) );
	return 0;
}

char* reverse (char str[], char rev[])
{
	int i,j;
	for(i = 0; str[i] != '\0'; i++); /* Last index of str*/
	for (j = 0; i > 0; --i ,j++)	rev[j] = str[i-1]; /* str[i] is '\0' */
	rev[j] = '\0'; /* placing null character */
	return rev;
}

char* tostr(int num, char str[])
{
	int i, n;

	for (n = 1; num > n; n = n*10); /* Gets highest power of 10 which is just above num */
	for (i = 0, n = n/10 ; n >= 1; n = n/10, ++i)	str[i] = (num/n)%10 + 48; /* 48 is '0' in ASCI */
	str[i] = '\0'; /* placing null character */
	return str;
}

char* combine (char str1[], char str2[], char str3[], char res[])
{
	int i,j,k,z,y;

	/* String lengths */
	for (i = 0; str1[i] != '\0'; ++i);
	for (j = 0; str2[j] != '\0'; ++j);	
	for (k = 0; str3[k] != '\0'; ++k);
	/* -------------------- */

	/* z represents index of final array */
	/* y is index of three arrays. We must get same index for three of them 
	   while combining. It increases by one each iteration. */
	for (z = 0, y = 0; z < (i + j + k) ; ++z, ++y)
	{
		if ((str3[y] != '\0') && (str2[y] != '\0') && (str1[y] != '\0'))
		{
			res[z] = str1[y];		/* z increases by 3 in total   		*/
			res[z+1] = str2[y];		/* because of placing 3 characters 	*/
			res[z+2] = str3[y];		/* in this condition				*/
			z += 2;
		}

		else if ((str2[y] != '\0') && (str1[y] != '\0'))
		{
			res[z] = str1[y];		/* z increases by 2 in total because */ 
			res[z+1] = str2[y];		/* of placing 2 characters in this   */
			z += 1;					/* condition 						 */
		}

		else if ((str3[y] != '\0') && (str1[y] != '\0'))
		{
			res[z] = str1[y];		/* z increases by 2 in total because */ 
			res[z+1] = str3[y];		/* of placing 2 characters in this   */
			z += 1;					/* condition 						 */
		}

		else if ((str3[y] != '\0') && (str2[y] != '\0'))
		{
			res[z] = str2[y];		/* z increases by 2 in total because */ 
			res[z+1] = str3[y];		/* of placing 2 characters in this   */
			z += 1;					/* condition 						 */	
		}

		else if (str1[y] != '\0')	res[z] = str1[y]; /* just by one */
		else if (str2[y] != '\0')	res[z] = str2[y]; /* just by one */
		else if (str3[y] != '\0')	res[z] = str3[y]; /* just by one */	
	}

	return res;
}

char* convert(char str1[], int num, char res[])
{
	char decstr[255], revstr[255];

	tostr(num,decstr); 		/* gets string type of integer */
	reverse(str1, revstr); 	/* reverses the string */

	combine(str1,decstr,revstr,res); /* combines three string */

	return res;
}