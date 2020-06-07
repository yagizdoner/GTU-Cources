#include <stdio.h>
#include <stdlib.h>
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

void read(char* filename, People *people, Records *records) {
	int i,j,k,rsize;
	char str[MAXRECORD];
	char surname[NAMELEN];
	FILE *rd;
	rd = fopen(filename,"r");
	people->size = 0;
	records->size = 0;
	while( (fgets(str,MAXRECORD,rd))!=NULL ){ 
		people->size += 1;                
	}
	rewind(rd);
	for(i=0;i<people->size;i++){
		fscanf(rd,"%d%s%s%d",&people->data[i].id,people->data[i].name,surname,&rsize);
		strcat(people->data[i].name," ");
		strcat(people->data[i].name,surname);
		for(j=records->size ; j < (records->size) + rsize ; j++){
			fscanf(rd,"%s",records->data[j].number);
			records->data[j].id = people->data[i].id;
		}
		records->size += rsize;
	}
} 

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

int main(void) {
	People people;
	Records records;
	read("input.txt",&people, &records);
	print(people, records);
	return 0;
}
