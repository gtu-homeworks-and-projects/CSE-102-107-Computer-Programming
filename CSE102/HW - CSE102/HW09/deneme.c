void writePeople(People people, char* filename) {
    int i, j, N; /* i and j are loop variables; N is for number of phone numbers */
    FILE * out;
    Record * nums, * tmpNums; /* tnmpNums is used for counting number of numbers                                */
                              /* nums is used for writing numbers without losing head of people.data[i].numbers */

    out = fopen(filename, "wb");
    
    for (i = 0; i < people.size; i++){
        fwrite(&people.data[i].id,sizeof(int),1,out);             /* Stores id      */
        fwrite(&people.data[i].name,sizeof(char),NAMELEN,out);    /* name           */
        fwrite(&people.data[i].expenditure,sizeof(double),1,out); /* expenditure    */

        nums = people.data[i].numbers;  /* Storing the head of linked list */
        tmpNums = nums;                 /* Making another copy of it       */

        for (N = 0; tmpNums ; ++N)  tmpNums = tmpNums->next; /* Counts number of phone numbers for a person */
        

        fwrite(&N,sizeof(int),1,out); /* Stores number of phone numers */

        for (j = 0; j < N; ++j) /* Stores number(s) of person */
        {
            fwrite(&nums->number,sizeof(char),NAMELEN,out);
            nums = nums->next;
        }

    }

    fclose(out);
}


void readPeople(People *people, char* filename) {
    Record * nums;  /* nums is used for writing numbers without losing head of people.data[i].numbers */
    FILE * out;
    int i, k, N;    /* i and k are loop variables; N is for number of phone numbers */

    out = fopen(filename, "rb");

    if (out){   /* Continues if the file opened succesfully */

        /* Following for loop continues to read until there is nothing to read*/

        for (i = 0; fread(&people->data[i].id,sizeof(int),1,out); i++){    
            
            fread(&people->data[i].name,sizeof(char),NAMELEN,out);
            fread(&people->data[i].expenditure,sizeof(double),1,out);
    
            nums = malloc(sizeof(Record));  /* Memory allocation for first number */
            people->data[i].numbers = nums; /* Stores head of number in struct    */

            fread(&N,sizeof(int),1,out);    /* Reads number of phone numbers */
            for (k = 0; k < N; ++k)
            {
                nums->id = people->data[i].id; /* Sets id for Num Record */
                fread(&nums->number,sizeof(char),NAMELEN,out);

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