#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 50
#define MAXRECORD 500

typedef struct record_s {
    int id;
    char number[NAMELEN];
    struct record_s *next;
} Record;

typedef struct person_s {
    int id;
    char name[NAMELEN];
    double expenditure;
    Record *numbers;
} Person;

typedef struct people_s {
    Person data[MAXRECORD];
    int size;
} People;


/*
 Write People.data array to the filename.
*/
void writePeople(People people, char* filename) {
    int i, j, N, L; /* i and j are loop variables; N is for number of phone numbers; L is for strlen*/
    FILE * out;
    Record * nums, * tmpNums; /* tnmpNums is used for counting number of numbers                                */
                              /* nums is used for writing numbers without losing head of people.data[i].numbers */

    out = fopen(filename, "wb");
    
    for (i = 0; i < people.size; i++){
        fwrite(&people.data[i].id,sizeof(int),1,out);             /* Stores id      */

    	L = strlen(people.data[i].name);	/* Stores length of name */
        fwrite(&L,sizeof(int),1,out);

        fwrite(&people.data[i].name,sizeof(char),strlen(people.data[i].name),out);    /* name           */
        fwrite(&people.data[i].expenditure,sizeof(double),1,out); /* expenditure    */

        nums = people.data[i].numbers;  /* Storing the head of linked list */
        tmpNums = nums;                 /* Making another copy of it       */

        for (N = 0; tmpNums ; ++N)  tmpNums = tmpNums->next; /* Counts number of phone numbers for a person */


        fwrite(&N,sizeof(int),1,out); /* Stores number of phone numers */

        for (j = 0; j < N; ++j) /* Stores number(s) of person */
        {
            L = strlen(nums->number);	/* Stores length of number */
            fwrite(&L,sizeof(int),1,out);

            fwrite(&nums->number,sizeof(char),strlen(nums->number),out);
            nums = nums->next;
        }

    }

    fclose(out);
}

/*
 Reads Person structs from file and places them to People.data array.
 Note that the number of Person structs in the file is unkown.
*/
void readPeople(People *people, char* filename) {
    Record * nums;  /* nums is used for writing numbers without losing head of people.data[i].numbers */
    FILE * out;
    int i, k, N, L;    /* i and k are loop variables; N is for number of phone numbers */

    out = fopen(filename, "rb");

    if (out){   /* Continues if the file opened succesfully */

        /* Following for loop continues to read until there is nothing to read*/

        for (i = 0; fread(&people->data[i].id,sizeof(int),1,out); i++){   
            
            fread(&L,sizeof(int),1,out); /* Length of name */
            fread(&people->data[i].name,sizeof(char),L,out);
            
            fread(&people->data[i].expenditure,sizeof(double),1,out);
    	
            nums = malloc(sizeof(Record));  /* Memory allocation for first number */
            people->data[i].numbers = nums; /* Stores head of number in struct    */
            fread(&N,sizeof(int),1,out);    /* Reads number of phone numbers */

            for (k = 0; k < N; ++k)
            {
                nums->id = people->data[i].id; /* Sets id for Num Record */
                
                fread(&L,sizeof(int),1,out);	/* Length of number */
                fread(&nums->number,sizeof(char),L,out);
                
                nums->next = malloc(sizeof(Record)); /* Allocates memory for next link */
                if (k < N-1) nums = nums->next; /* if it's not last number continues to allocated link */
                else    /* else frees memory and sets its next pointer to NULL */
                {
                    free(nums->next);
                    nums->next = NULL;
                }
            }
        }

        /* ------------------------------ */
        
    }

    people->size = i; /* Sets people size as loops final count */
    

    fclose(out);
}

/*
 Calculates the expected expenditure for the person with unknown expenditure.
 Persons' expenditure is -1 if their expenditure is unknown.
 You should calculate average bill amount for a phone number and multiply it by
 the phone number count for the person.
*/
void imputation(People *people) {
    int N = 0, i;   /* i is loop variables; N is for number of phone numbers */
    double totalExp = 0.0, singleExpected = 0.0;
    Record * num;   /* num is used for writing numbers without losing head of people.data[i].numbers */

    for (i = 0; i < people->size; ++i)
    {
        num = people->data[i].numbers; /* Sets the head */ 

        if (people->data[i].expenditure != -1)
        {
            totalExp += people->data[i].expenditure;
            for (; num ; ++N)   num = num->next; /* Counts total phone numbers which has expenditure */
 
        }
    }
    
    singleExpected = totalExp / N; /* expected expenditure for one phone number */

    for (i = 0; i < people->size; ++i)
    {   
        num = people->data[i].numbers; /* Sets the head */

        if (people->data[i].expenditure == -1)
        {
            for (N = 0; num ; ++N)  num = num->next; /* Counts total phone numbers which has not calculated expenditure */

            people->data[i].expenditure = singleExpected * N; /* Calculates estimated expenditure */
        }
    } 
}

/*
 Reads the input file and constructs People struct.
 Note that the number of phone numbers in file is unknown unlike your
 previous homework. You should keep phone numbers in the linked list
 (numbers field)
*/
void read(char* filename, People *people) {
    FILE * inp;
    int i=0,k, n, isItTheEnd = 0;  /* loop control variables */
    char lastName[NAMELEN];
    char number[NAMELEN]; /*temporary number variable */
    Record *num;    /* nums is used for writing numbers without losing head of people.data[i].numbers */

    inp = fopen(filename,"rt");
    people->size = 0; /* init of size variable */
    
    /* Following for loop continues until EOF */
    for (k = 0; fscanf(inp,"%d ",&people->data[k].id) != EOF; ++k)
    {
        
        fscanf(inp,"%s %s %lf ", people->data[k].name, lastName, &people->data[k].expenditure);
        
        /* %s format reads until space character, in order to write full name  /
        /  i use another variable and combine them                            */

        strcat(people->data[k].name," ");
        strcat(people->data[k].name,lastName);

        /* ------------------------------ */

        num = malloc(sizeof(Record));   /* Memory allocation for first number */
        people->data[k].numbers = num;  /* Stores head of number in struct    */

        fscanf(inp,"%s ", number);
        
        for (i = 0; strlen(number) >= 10 ; ++i) /* In order to ensure scanned value is phone number, it makes sure it's greater than or equal to 10 */
        {
            num->id = people->data[k].id; /* Sets id of num->id to data.id */
            strcpy(num->number,number); 
            

            n = fscanf(inp,"%s ", number); /* to determine if it has reached EOF, assigns fscanfs return value */
            if (n == EOF)
            {
                isItTheEnd = 1;
                break;
            }

            num->next = malloc(sizeof(Record)); /* Allocates memory for next link */
            if (strlen(number) >= 10) num = num->next; /* if it's not last number continues to allocated link */
            else    /* else frees memory and sets its next pointer to NULL */
            {
                free(num->next);
                num->next = NULL;
            }
        }

        if (!isItTheEnd) fseek(inp,-(strlen(number)+2),SEEK_CUR); /* if it's not the EOF moves position of file to the start of id */     

        people->size++;

    }

    /* ------------------------------ */

    fclose(inp);
}

void print(People people) {
    int i,found = 0;
    Record *rec;
    /* header */
    printf("%-5s %-30s %-20s %-20s\n", "ID","NAME","EXPENDITURE","NUMBER(s)");
    /* line */
    for (i = 0; i < 78; ++i)
        printf("-");
    printf("\n");

    for (i = 0; i < people.size; ++i) {
        found = 0;
        printf("%-5d %-30s %-20.4f", people.data[i].id, people.data[i].name, people.data[i].expenditure);
        rec = people.data[i].numbers;
        while(rec) {
            if(found)
                printf("%57s", "");
            else
                found = 1;
            printf("%-20s\n", rec->number);
            rec = rec->next;
        }
        printf("\n");
    }
}

int isPeopleEq(People ppl1, People ppl2) {
    Record *rec1,*rec2;
    int i,found = 0;
    int p1size = 0, p2size = 0;
    if(ppl1.size != ppl2.size)
        return 0;
    for (i = 0; i < ppl1.size; ++i)
        if(strcmp(ppl1.data[i].name,ppl2.data[i].name))
            return 0;
        if(ppl1.data[i].id != ppl2.data[i].id)
            return 0;

        p1size = p2size = 0;
        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            ++p1size;
            rec1 = rec1->next;
        }

        rec2 = ppl2.data[i].numbers;
        while(rec2) {
            ++p2size;
            rec2 = rec2->next;
        }

        if(p1size != p2size) {
            return 0;
        }

        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            rec2 = ppl2.data[i].numbers;
            found = 0;
            while(!found && rec2) {
                if(strcmp(rec1->number,rec2->number) == 0) {
                    found = 1;
                    break;
                }
                rec2 = rec2->next;
            }
            if(!found) {
                return 0;
            }
            rec1 = rec1->next;
        }
    return 1;
}

int main(int argc, char** argv) {
    People people1,people2;
    people1.size = 0;
    read(argv[1],&people1);
    print(people1);
    writePeople(people1,"people.bin");
    printf("aaa\n");
    readPeople(&people2,"people.bin");
    printf("sss\n");
    print(people2);
    printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
    printf("Making imputation\n");
    imputation(&people1);
    print(people1);
    
    return 0;
}
