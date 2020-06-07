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

/* ========== IMPLEMENT THE FUNCTIONS BELOW ========== */
/*
	Write Records.data array to the filename.
*/
void writeRecords(Records records, char* filename) {
	FILE *file = fopen(filename,"wb");
	if(!file)
		return;
	fwrite(records.data,sizeof(Record),records.size,file);
	fclose(file);
}

/*
	Reads Record structs from file and places them to Records.data array.
	Note that the number of Record structs in the file is unkown.
*/
void readRecords(Records *records, char* filename) {
	Record rec;
	FILE *file = fopen(filename,"rb");
	if(!file)
		return;
	records->size = 0;
	while(fread(&rec,sizeof(Record),1,file))
		memcpy(&records->data[records->size++], &rec, sizeof(Record));
	fclose(file);
}

/*
	Write People.data array to the filename.
*/
void writePeople(People people, char* filename) {
	FILE *file = fopen(filename,"wb");
	if(!file)
		return;
	fwrite(people.data,sizeof(Person),people.size,file);
	fclose(file);
}

/*
	Reads Person structs from file and places them to People.data array.
	Note that the number of Person structs in the file is unkown.
*/
void readPeople(People *people, char* filename) {
	Person p;
	FILE *file = fopen(filename,"rb");
	if(!file)
		return;
	people->size = 0;
	while(fread(&p,sizeof(Person),1,file))
		memcpy(&people->data[people->size++],&p,sizeof(Person));
	fclose(file);
}


int contains(Records records, Record record) {
	int i;
	for (i = 0; i < records.size; ++i)
		if(!strcmp(records.data[i].number,record.number) &&
			records.data[i].id == record.id)
			return 1;
	return 0;
}

/**
  * Reads the input file and constructs People and Records structs.
  	Note that each Record in Records is unique (should not present multiple times).
  */
void read(char* filename, People *people, Records *records) {
	Record record;
	char name[NAMELEN], surname[NAMELEN];
	int phoneCount = 0, i, status = 1;
	char tmp;
	FILE *file;
	file = fopen(filename,"r");
	if(!file)
		return;
	if(people->size >= MAXRECORD)
		return;
	while(1) {
		status = fscanf(file,"%d %s %s %d",&people->data[people->size].id, name, surname, &phoneCount);
		if(status == EOF)
			break;
		/* concatenate name and surname and copy the people struct */
		strcat(name," ");
		strcat(name,surname);
		strcpy(people->data[people->size].name, name);
		record.id = people->data[people->size].id;
		for (i = 0; i < phoneCount; ++i) {
			fscanf(file,"%s",record.number);
			/* avoid duplicate records */
			if(!contains(*records, record)) {
				memcpy(&records->data[records->size], &record, sizeof(Record));
				++records->size;
			}
		}
		fscanf(file,"%c",&tmp);
		++people->size;
	}
	fclose(file);
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
	read("input.txt",&people1, &records1);
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
