#include <stdio.h>
#include <string.h>

#define NAMELEN 50
#define MAXRECORD 500

typedef struct person_s {
	int id;
	char name[NAMELEN];
} Person;

typedef struct record_s {
	int id;
	char number[NAMELEN];
} Record;

typedef struct Records_s {
	Record data[MAXRECORD];
	int size;
} Records;

typedef struct people_s {
	Person data[MAXRECORD];
	int size;
} People;

/* ========== IMPLEMENT THE FUNCTIONS BELOW ========== */
/*
	Write Records.data array to the filename.
	Note that file should be binary.
*/
void writeRecords(Records records, char* filename) {
	int i;
	FILE * out;

	out = fopen(filename, "wb");

	
	for (i = 0; i < records.size; i++){
		fwrite(&records.data[i].id,sizeof(int),1,out);
		fwrite(&records.data[i].number,sizeof(char),NAMELEN,out);
	}

	fclose(out);
}


void readRecords(Records *records, char* filename) {
	FILE * out;
	int i;
	out = fopen(filename, "rb");

	/* Following for loop continues to read until there is nothing to read*/

	for (i = 0; fread(&records->data[i].id,sizeof(int),1,out); i++){	
		fread(&records->data[i].number,sizeof(char),NAMELEN,out);
	}

	/* ------------------------------ */

	records->size = i; 

	fclose(out);
}


void writePeople(People people, char* filename) {
	int i;
	FILE * out;

	out = fopen(filename, "wb");

	
	for (i = 0; i < people.size; i++){
		fwrite(&people.data[i].id,sizeof(int),1,out);
		fwrite(&people.data[i].name,sizeof(char),NAMELEN,out);
	}

	fclose(out);
}


void readPeople(People *people, char* filename) {
	int i;
	FILE * out;
	
	out = fopen(filename, "rb");

	/* Following for loop continues to read until there is nothing to read*/

	for (i = 0; fread(&people->data[i].id,sizeof(int),1,out); i++){
		fread(&people->data[i].name,sizeof(char),NAMELEN,out);
	}

	/* ------------------------------ */

	people->size = i;

	fclose(out);
}


void read(char* filename, People *people, Records *records) {
	FILE * inp;
	int i=0,j,k,l = 0;	/* loop control variables */
	char lastName[NAMELEN]; 

	inp = fopen(filename,"rt");

	people->size = 0;	/* Initialize in case of error */
	records->size = 0;  /* Initialize in case of error */

	/* Following for loop continues until EOF */

	for (k = 0; fscanf(inp,"%d ",&people->data[k].id) != EOF; ++k)
	{
		fscanf(inp,"%s %s %d ", people->data[k].name, lastName, &j);

		/* %s format reads until space character, in order to write full name  /
		/  i use another variable and combine them 					      	  */

		strcat(people->data[k].name," ");
		strcat(people->data[k].name,lastName);

		/* ------------------------------ */
		
		/* Following for loop loops j times */

		for (i = l; l < i + j; ++l)	/* to keep first value of data arrays index, stores it in i variable */
		{ 
			records->data[l].id = people->data[k].id;
			fscanf(inp,"%s ",records->data[l].number);
			records->size++;
		}

		/* ------------------------------ */
		
		people->size++;
	}

	/* ------------------------------ */

	fclose(inp);
}

/* ========== IMPLEMENT THE FUNCTIONS ABOVE ========== */

void print(People people, Records records) {
	int i,j,found = 0;
	/* header */
	printf("%-5s %-30s %-20s\n", "ID","NAME","NUMBER(s)");
	/* line */
	for (i = 0; i < 57; ++i)
		printf("-");
	printf("\n");

	for (i = 0; i < people.size; ++i) {
		found = 0;
		printf("%-5d %-30s", people.data[i].id, people.data[i].name);
		for (j = 0; j < records.size; ++j) {
			if(records.data[j].id == people.data[i].id) {
				if(found)
					printf("%36s", "");
				printf("%-20s\n", records.data[j].number);
				found = 1;
			}
		}
		printf("\n");
	}
}

int isPeopleEq(People ppl1, People ppl2) {
	int i;
	if(ppl1.size != ppl2.size)
		return 0;
	for (i = 0; i < ppl1.size; ++i)
		if(strcmp(ppl1.data[i].name,ppl2.data[i].name) ||
			ppl1.data[i].id != ppl2.data[i].id)
			return 0;
	return 1;
}

int isRecordsEq(Records rec1, Records rec2) {
	int i;
	if(rec1.size != rec2.size)
		return 0;
	for (i = 0; i < rec1.size; ++i)
		if(strcmp(rec1.data[i].number,rec2.data[i].number) ||
			rec1.data[i].id != rec2.data[i].id)
			return 0;
	return 1;
}

int main(int argc, char** argv) {
	People people1,people2;
	Records records1,records2;
	people1.size = 0;
	records1.size = 0;
	read(argv[1],&people1, &records1);
	print(people1, records1);
	writePeople(people1,"people.bin");
	writeRecords(records1,"records.bin");
	readRecords(&records2,"records.bin");
	readPeople(&people2,"people.bin");
	print(people2, records2);
	printf("%s\n", isRecordsEq(records1,records2) ? "RECORDS ARE SAME" : "RECORDS ARE DIFFERENT!");
	printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
	return 0;
}
