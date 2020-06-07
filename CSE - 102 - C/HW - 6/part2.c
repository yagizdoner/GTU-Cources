#include <stdio.h>
#include <string.h>
#define MAX_NUM_WORDS 500
#define WORD_LENGTH 50

/*  YAÐIZ DÖNER  -  141044062  */

int getAndFilterWord(char * w); //  BU FONKSÝYON TAMAMDIR....
void addWord(char * w, char words[MAX_NUM_WORDS][WORD_LENGTH],int occur[MAX_NUM_WORDS], int * word_count);
void sortWords(char words[MAX_NUM_WORDS][WORD_LENGTH], int occur[MAX_NUM_WORDS],int word_count);
void lowercase_and_removes(char *arr); //  BU FONKSÝYON TAMAMDIR....
int is_there_end(char *arr); //  BU FONKSÝYON TAMAMDIR....
int is_there_word(char *w, char words[MAX_NUM_WORDS][WORD_LENGTH], int*i);
void myTest();

int main(void){
	myTest();
	return 0;
}

void myTest(){
	char line[WORD_LENGTH];
	getAndFilterWord(line);
}

int getAndFilterWord(char * w){
	int condition=1;
	char words[MAX_NUM_WORDS][WORD_LENGTH];
	int occur[MAX_NUM_WORDS];
	char line[WORD_LENGTH];
	int word_count=0, result=0; 
	do{
		gets(line);
		lowercase_and_removes(line);
		if(is_there_end(line)){
			condition = 0;
			break;
		}
		w = strtok(line," ");
		while(w != NULL){
			addWord( w , words , occur , &word_count);
			w = strtok(NULL," ");
			result = 1;
		}
	}while(condition);
	
	sortWords(words, occur, word_count);
	
	return result;
}

void addWord(char * w, char words[MAX_NUM_WORDS][WORD_LENGTH],int occur[MAX_NUM_WORDS], int * word_count){
	int i;
	if(is_there_word(w,words,&i)){
		occur[i] += 1;
	}
	else{
		for(i=0;i<MAX_NUM_WORDS;i++){
			if(words[i]==0){
				strcpy(words[i],w);
				occur[i] = 1;
				*word_count++;
				break;
			}
		}
	}
}

void sortWords(char words[MAX_NUM_WORDS][WORD_LENGTH], int occur[MAX_NUM_WORDS],int word_count){
	int i,m;
	int *temp;
	char *arr;
	for(i=0;i<word_count;i++)
		arr[i] = occur[i];
	for(i=1;i<word_count;i++){
		for(;i>0;i--){
			if(arr[i]>arr[i-1]){
				*temp = arr[i];
				arr[i] = arr[i-1];
				arr[i-1] = *temp;
			}
		}
	}
	for(m=0;m<word_count;m++){
		for(i=0;i<word_count;i++){
			if(arr[m] == occur[i]){
				printf("%s\n",words[i]);
				printf("%d\n",occur[i]);
			}
		}
	}
}

int is_there_word(char *w, char words[MAX_NUM_WORDS][WORD_LENGTH], int*i){
	int result=-1;
	char *str;
	for(*i=0;*i<MAX_NUM_WORDS;i++){
		str = strstr(words[*i],w);
		if(str!=NULL){
			result = 1;
			break;
		}
	}
	return(result);
}

int is_there_end(char *arr){
	int i,k,result=0;
	for(k=0 ; k<strlen(arr) ; k++){
		i=k;
		if(arr[i] == 'e' || arr[i] == 'E'){
			if(arr[i-1]==' ' || arr[0] == 'e' || arr[i] == '0' ){
				if(arr[i+1]== 'n' || arr[i] == 'N'){
					if(arr[i+2]== 'd' || arr[i] == 'D'){
						if(arr[i+3]==' ' || arr[i+3]=='\0')
							result = 1;
					}
				}
			}
		}
	}
	return result;
}

void lowercase_and_removes(char *arr){
	int i,k=0;
	char line[WORD_LENGTH];
	for(i=0;i<strlen(arr);i++){
		if(arr[i]<='Z' && arr[i]>='A')
			arr[i] -= ('A'-'a');
	}
	for(i=0;i<strlen(arr);i++){
		if( (arr[i]<='z' && arr[i]>='a') || arr[i] == ' ' ){
			line[k] = arr[i];
			k++;
		}
	}
	line[k] = '\0';
	arr[k] = '\0';
	for(i=0;i<strlen(line);i++){
		arr[i] = line[i];
	}
}
