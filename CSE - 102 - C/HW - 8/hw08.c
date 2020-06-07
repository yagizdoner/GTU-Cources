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
	Note that file should be binary.
*/
void writeRecords(Records records, char* filename) {
	FILE * wrec;
	wrec = fopen(filename,"wb");
	fwrite(&records.data,sizeof(Records),1,wrec);
	fclose(wrec);
}

/*
	Reads Record structs from the binary file and places them to Records.data array.
	Note that the number of Record structs in the file is unkown.
*/
void readRecords(Records *records, char* filename) {
	FILE * rrec;
	rrec = fopen(filename,"rb");
	fread(&records->data,sizeof(Records),1,rrec);
	fclose(rrec);
}

/*
	Write People.data array to the filename.
	Note that file should be binary.
*/
void writePeople(People people, char* filename) {
	FILE * wpeo;
	wpeo = fopen(filename,"wb");
	fwrite(&people.data,sizeof(People),1,wpeo);
	fclose(wpeo);
}

/*
	Reads Person structs from the binary file and places them to People.data array.
	Note that the number of Person structs in the file is unkown.
*/
void readPeople(People *people, char* filename) {
	FILE * rpeo;
	rpeo = fopen(filename,"rb");
	fread(&people->data,sizeof(People),1,rpeo);
	fclose(rpeo);
}

/**
  * Reads the input file and constructs People and Records structs.
  	Note that each Record in Records is unique (should not present multiple times).
  */
void read(char* filename, People *people, Records *records) {
	int i,j,k,rsize;
	char str[MAXRECORD];
	char surname[NAMELEN];
	FILE *rd;
	rd = fopen(filename,"r");
	people->size = 0;
	records->size = 0;
	while( (fgets(str,MAXRECORD,rd))!=NULL ){ /* Bu D�ng�de Sat�r Say�s�ndan*/
		people->size += 1;                	  /* people size �n� buldum.  */
	}
	rewind(rd);  							  /* Dosya Ba��na Geri D�nd�m */
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
