#include <stdio.h>
#include <string.h>
#include <ctype.h>


int getAndFilterWord(char * w);
void addWord(char * w, char words[][50],
			int occur[], int *word_count);
void sortWords(char words[][50],
			int occur[],int word_count);
void myTest();
void swapInt(int *n1, int *n2);
void lowerCase(char string[]);
void swapStr(char *s1, char *s2);

void myTest()
{
	char word[50], words[500][50];
	int occurence[500],wordCount = 0,i,j ,kontrol = 1 ;
	
	for (i = 0; i < 500; ++i) /* Initializations of words array */
		for (j = 0; j < 50; ++j)
			words[i][j] = '\0';

	do
	{		
		for (i = 0; i < 50; ++i) /* Resetting temporary line array */
			word[i] = '\0';

		scanf("%s",word); /* Gets word */

		for (i = 0; i < 50; ++i) /* converts every space into NULL to seperate words in case of multiple words in one line*/
			if (word[i] == ' ')	word[i] = '\0';

		for (i = 0; i < 50; i += 1 + strlen(&word[i])) /*sends every word to addword and checks if its 'end' */
		{
			if (strcmp(&word[i],"end") == 0)  /* 'end' check */
				kontrol = 0; /* if the word is end, kontrol variable turns into 0 */

			if ((getAndFilterWord(&word[i])) && (kontrol))    /* filters the word; if it's a word and not an 'end', continues */
				addWord(&word[i],words,occurence,&wordCount); /* to addWord function */
		}
	} while (kontrol);

	sortWords(words,occurence,wordCount);
	/* Prints the first 5 words and its occurences */
	for (i = 0; i < 5; ++i)
	{
		printf("Word: %s",words[i] );
		printf(" - Occur: %d\n",occurence[i]);
	}
	printf("WordCount: %d\n",wordCount );
	/* ------------------------------ */
}


int main()
{
	myTest();

	return 0;
}

void sortWords(char words[][50],
			int occur[],int word_count)
{
	int i,maxIndex;
	for (i = 0, maxIndex = 0; i < word_count; ++i) 
		if (occur[maxIndex] < occur[i]) 
			maxIndex = i; /* Finds maximum numbers index in an array */
	/* Swaps words and number of occurences at the same time */
	swapInt(&occur[0], &occur[maxIndex]);	/* Even if its already maximum */
	swapStr(words[0],words[maxIndex]);
	/* ------------------------------ */

	if (word_count > 0 ) /* continues the sortion recursively until there is no words to sort */
		sortWords(&words[1],&occur[1],word_count-1);
}

void addWord(char * w, char words[][50],
			int occur[], int *word_count)
{
	int i,j = -1;
	for (i = 0; i < 500; ++i) /* checks if the word is already in the array or not */
		if ((strcmp(w,words[i]) == 0) && (words[i] != '\0' )) 
			j = i; /* if it is in the list, stores its index */

	printf("j = %d, %s\n",j,words[j] ); /* Test print */

	if (j == -1) /* if the word is new, adds it to the end of the current list */
	{
		for (i = 0; w[i] != '\0'; ++i) /* adding word letter by letter to our list */
			words[*word_count][i] = w[i];

		occur[*word_count] += 1; /* increases occurence of the same index */
		*word_count += 1; /* word_count is also our word array index. so we have to increase it if the word is new */
	}

	else /* if the word is already in the list, using j variable we obtain our words index */
	{
		for (i = 0; w[i] != '\0'; ++i) /* adding word letter by letter to our list */
			words[j][i] = w[i];
		occur[j] += 1; /* increases occurence of the same index */
	}
	

}

int getAndFilterWord(char * w)
{
	int i,j;
	lowerCase(w); /* makes all letters lowercase */

	for (i = 0; w[i] != '\0'; ++i) /* if a letter isn't between 'a' and 'z', delete it from the array */
		if ((w[i] < 'a') || (w[i] > 'z')) 
		{
			for (j = i; w[j] != '\0'; ++j)	w[j] = w[j+1]; /* if char w[i] isn't letter shift all array to left from there */ 
			w[j+1] = '\0'; /* makes last character NULL */
			i--; /* makes sure to check first shifted letter */
		}
	return (strlen(w) > 0) ? 1: 0; /* if there is any letter, returns 1; otherwise it returns 0 */
}

/* PREFERRED FUNCTIONS TO AVOID COMPLICATOION */

/* converts a string into lowercase */
void lowerCase(char string[])
{
	int i;
	for (i = 0; string[i] != '\0'; ++i)
		if ((string[i] <= 'Z') && (string[i] >= 'A'))	
			string[i] += 'a' - 'A';
}
/* --------------------------- */

/* Swaps integers */
void swapInt(int *n1, int *n2) 
{
	int tmp;
	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}
/* ------------------------------ */

/* Swaps strings */
void swapStr(char *s1, char *s2)
{
	char tmp[50];
	strcpy(tmp,s1);
	strcpy(s1,s2);
	strcpy(s2,tmp);
}
/* ------------------------------ */

/* ------------------------------------------------------------ */