#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h> 
#include <math.h>

#define SIZE 160
#define PI 3.14

int writeToFile(char * writeFD, char * complexLine, int slp);
int lineNumber(int fd);
int lineLength(int fd);
int isEmpty(int fd,int totL);
void fft(int fd, char * line);
int isAexit();

int main(int argc, char * argv[]){
	char * line;
	char c[2];
	int opt;
	int timeSleep;
	char * inputPathB;
	char * outputPathB;

	// Command Line Parsing START...
	while((opt = getopt(argc, argv, "i:o:t:")) != -1){
		switch(opt){
			case 'i':
				if(optarg[0] == '-'){
					fprintf(stderr, "%s\n", "Missing Input File Name");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					return -1;
				}
				inputPathB = malloc((strlen(optarg)+1) * sizeof(char));
				strcpy(inputPathB,optarg);
				break;
			case 'o':
				if(optarg[0] == '-'){
					fprintf(stderr, "%s\n", "Missing Output File Name");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					return -1;
				}
				outputPathB = malloc((strlen(optarg)+1) * sizeof(char));
				strcpy(outputPathB,optarg);
				break;
			case 't':
				if(optarg[0] == '-'){
					fprintf(stderr, "%s\n", "Missing Time");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					return -1;
				}
				else if(atoi(optarg) < 1 || atoi(optarg) > 50){
					fprintf(stderr, "%s\n", "Time has to be between 1 and 50");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					return -1;
				}
				timeSleep = atoi(optarg); 
				break;
			case '?':
				fprintf(stderr,"Unknown option : %c\n", optopt);
				fprintf(stderr, "%s\n", "Program EXIT !!");
				return -1;
		}
	}
	for( ; optind < argc ; optind++){
		fprintf(stderr,"Extra argument(s) : %s\n",argv[optind]);
		fprintf(stderr, "%s\n", "Program EXIT !!");
		return -1;
	}
	// Command Line Parsing END...

	// File Read START...
	int readFD = open(inputPathB,O_RDWR | O_NONBLOCK);
	if(readFD == -1){
		fprintf(stderr, "%s\n", "Input File Opening Failure !");
		return -1;
	}
	else{
		char del[SIZE];
		int totalLine = lineNumber(readFD); // number of line in inputFile
		char buf[1];
		struct flock lock;
		
		for(;;){
			if(isEmpty(readFD,totalLine) == 0 ){
				if(isAexit() == 2)
					break;
				sleep(timeSleep);
			}
			else{
				char * line;
				lseek(readFD,0,SEEK_SET);
				srand(time(0)); 
				int actualLine = rand() % totalLine ; // Take a random 0 to line number
				
				memset(&lock,0,sizeof(lock));
				lock.l_type = F_WRLCK;
				fcntl(readFD,F_SETLKW,&lock);
				
				for (int i = 0; i < totalLine; ++i){
					if(i == actualLine){
						int lengthLine = lineLength(readFD);
						lseek(readFD,(lengthLine- (2*lengthLine) - 1),SEEK_CUR);
						line = malloc(sizeof(char) * lengthLine);
						strcpy(line,"\0");
						do{
							memset(buf, 0, 1);
							read(readFD,buf,1);
							sprintf(c,"%c",buf[0]);
							strcat(line, c);
							memset(c,0,2);
						}while(buf[0] != '\n');
						lseek(readFD,(strlen(line)- (2*strlen(line))),SEEK_CUR);
						line[strlen(line)-1] = '\n';
						if(line[0] != '\''){ // Not empty and not '\n'
							printf("%s%d\n","The Line was Read by progB -> pid : ",getpid());
							if(writeToFile(outputPathB,line,timeSleep) == -1)
								return -1;
							else{
								strcpy(del,"\0");
								strcat(del,"\'");
								strcat(del,"\\");
								strcat(del,"n");
								strcat(del,"\'");
								while(strlen(del)<=SIZE){
									strcat(del," ");
								}
								del[strlen(del)-1] = '\n';
								
								write(readFD,del,SIZE);

								lock.l_type = F_UNLCK;
								fcntl(readFD,F_SETLKW,&lock);

								memset(del,0,SIZE);
							}
						}
						else{
							i = -1;
							actualLine--;
							lseek(readFD,0,SEEK_SET);
						}
						memset(buf,0,1);
						free(line);
					}
					else{
						read(readFD,buf,1);
						while(buf[0] != '\n'){
							memset(buf, 0, 1);
							read(readFD,buf,sizeof(buf));
						}	
					}
				}
			}
		}
		lock.l_type = F_UNLCK;
		fcntl(readFD,F_SETLKW,&lock);
	}
	close(readFD);
	// File Read END...
	printf("%s%d\n","Program B EXIT -> pid: ",getpid());
	return 0;
}

int writeToFile(char * writeName, char * complexLine, int slp){
	struct flock lock;
	int writeFD = open(writeName, O_RDWR | O_APPEND | O_CREAT | O_NONBLOCK, S_IWUSR | S_IRUSR);
	if(writeFD == -1){
		fprintf(stderr, "%s\n", "Output File Opening Failure !");
		return -1;
	}
	else{

		memset(&lock,0,sizeof(lock));
		lock.l_type = F_WRLCK;
		fcntl(writeFD,F_SETLKW,&lock);

		fft(writeFD,complexLine); // write to file with FFT

		lock.l_type = F_UNLCK;
		fcntl(writeFD,F_SETLKW,&lock);

		printf("%s%d\n","The Line was Writen by prog B -> pid: ",getpid());
		sleep(slp / 100);
	}
	close(writeFD);

	return 0;
}

void fft(int fd, char * line){
    float sr, si;
    int re[16];
    int im[16];
    float reFft[16];
    float imFft[16];
    char delim[6] = ", +i";
    int i = 0;
    int turn = 0;
    char *comp = strtok(line,delim);
	while (comp != NULL){
        if(i%2 == 0)
            re[turn] = atoi(comp);
        else{
            im[turn] = atoi(comp);
            ++turn;
        }
        comp = strtok(NULL, delim);
        i++;
	} 
    // Real and Imaginer created.

    for (int k = 0; k < 16; k++){
        reFft[k] = 0;
        imFft[k] = 0;
    }

    for (int k = 0; k < 16; k++){
        for (int n = 0; n < 16; n++){
            float val = 2*PI*k*n/16;
            sr = cos(val);
            si = -sin(val);
            reFft[k] += re[n]*sr - im[n]*si;
            imFft[k] += re[n]*si + im[n]*sr;
        }
    }

    char res[10000];
    strcpy(res,"\0");
    for (int i = 0; i < 16; ++i){
        char a[50];
        sprintf(a,"%.2f%s%.2f,",reFft[i]," +i", imFft[i] );
        strcat(res,a);
        memset(a,0,50);
    }
    res[strlen(res)-1]='\n';

    size_t length = strlen(res);
	write(fd, res, length);
}

int isAexit(){
	int w = open("temp.txt",O_RDONLY);
	while(w==-1){
		return 0;
	}
	lseek(w,0,SEEK_SET);
	char c[1];
	int ex = 0;

	read(w,c,1);
	if(strcmp(c,"1")==0)
		ex++;
	memset(c,0,1);
	read(w,c,1);
	if(strcmp(c,"1")==0)
		ex++;
	
	return ex;
}

int isEmpty(int fd,int totL){
	char buf[SIZE+1];

	lseek(fd,0,SEEK_SET);
	for (int i = 0; i < totL; ++i){
		read(fd,buf,sizeof(buf));
		if(buf[0] != '\'' || buf[1] != '\\' || 
				buf[2] != 'n' || buf[3] != '\'' ){
			return -1;
		}
		memset(buf,0,SIZE+1);
	}
	return 0;
}

int lineNumber(int fd){
	char buf[1];
	int numLine = 0;
	lseek(fd,0,SEEK_SET);
	read(fd,buf,1);
	while(buf[0] != '\0'){
		if(buf[0] == '\n')
			numLine++;
		memset(buf, 0, 1);
		read(fd,buf,sizeof(buf));
	}
	return numLine;
}

int lineLength(int fd){
	char buf[1];
	int lineLen = 0;
	read(fd,buf,1);
	while(buf[0] != '\n'){
		lineLen++;
		memset(buf, 0, 1);
		read(fd,buf,sizeof(buf));
	}
	return lineLen;
}