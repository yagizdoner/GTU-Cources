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
	FILE * wpeo;
	wpeo = fopen(filename,"wb");
	fwrite(&people.data,sizeof(People),1,wpeo);
	fclose(wpeo);
}

/*
 Reads Person structs from file and places them to People.data array.
 Note that the number of Person structs in the file is unkown.
*/
void readPeople(People *people, char* filename) {
//	int i;
	FILE * rpeo;
	rpeo = fopen(filename,"rb");
	fread(&people->data,sizeof(People),1,rpeo);
//	for(i=0;i<people->size;i++)
//		people->data[i].id = 1 ;
	fclose(rpeo);
}



/*
 Calculates the expected expenditure for the person with unknown expenditure.
 Persons' expenditure is -1 if their expenditure is unknown.
 You should calculate average bill amount for a phone number and multiply it by
 the phone number count for the person.
*/

void imputation(People *people) {
	int i;
	int total_phone=0;
	int total_exp_phone[MAXRECORD];
	double total_exp = 0.0;
	double impt;
	Record * current;
	for(i=0 ; i < (people->size) ; i++){
		if(people->data[i].expenditure != -1.0){
			total_exp += people->data[i].expenditure;
		}	
	}
	for(i=0;i < people->size ; i++){
		if(people->data[i].expenditure == -1.0){
			current = people->data[i].numbers ;
			while(current->next != NULL){
				total_exp_phone[i]++;
				current = current->next;
			}
		}
	}
	for(i=0;i < people->size ; i++){
		if(people->data[i].expenditure != -1.0){
			current = people->data[i].numbers ;
			while(current->next != NULL){
				total_phone++;
				current = current->next;
			}
		}
	}
	for(i=0;i < people->size ; i++){
		if(people->data[i].expenditure == -1.0){
			impt = ( total_exp * total_exp_phone[i] ) / total_phone ;
			people->data[i].expenditure = impt ;
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
	int i=0,j;
	char str[MAXRECORD];
	char surname[NAMELEN];
	char temp[MAXRECORD];
	char * part;
	Record * rec ;
	FILE *rd;
	rd = fopen(filename,"r");
	people->size = 0;
	while( (fgets(str,MAXRECORD,rd))!=NULL ){ 
		people->size += 1; 
		sscanf(str,"%d%s%s%lf",&people->data[i].id,people->data[i].name,surname,&people->data[i].expenditure);
		strcat(people->data[i].name," ");
		strcat(people->data[i].name,surname);	
		strcpy(temp,str);
		j=0;
		people->data[i].numbers = malloc(sizeof(Record));
		rec = people->data[i].numbers;
		part = strtok(temp," ");
		while(part != NULL){
			if(j>3){
				strcpy(rec->number,part) ;
				rec->id = people->data[i].id ;
				rec->next = malloc(sizeof(Record)) ;
				rec = rec->next ; 			
			}
			part = strtok(NULL," ");
			j += 1 ;
			rec->next = NULL;
		}
		i += 1; 
	}
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
    for (i = 0; i < ppl1.size; ++i){
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
    }
    return 1;
}

int main(void) {
    People people1,people2;
    people1.size = 0;
    read("input.txt",&people1);
 	print(people1);
    writePeople(people1,"people.bin");
    readPeople(&people2,"people.bin");
    print(people2);
    printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
    printf("Making imputation\n"); 
    imputation(&people1);
    print(people1); 
    return 0;
}
