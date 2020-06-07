#include <stdio.h>
#include <string.h>
int is_there_word(char *w, char words[50][50]);
void main(){
	char w[]="aw";
	char arr[50][50] = {{"kfs"},{"aaa"}};
	int a = is_there_word(w,arr);
	printf("%d",a);
}

int is_there_word(char *w, char words[50][50]){
	int i, result=0;
	char *str;
	for(i=0;i<50;i++){
		str = strstr(words[i],w);
		if(str!=NULL){
			result = 1;
			break;
		}
	}
	return(result);
}
