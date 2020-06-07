#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

#define SIZE 160

int writeToFile(char * writeFD, char * complexLine, int slp);

int main(int argc, char * argv[]){
	char * line;
	char buffer[32];
	char complexNum[10];
	size_t numByte;
	int opt;
	int time;
	char * inputPathA;
	char * outputPathA;
	struct flock lock;

	// Command Line Parsing START...
	while((opt = getopt(argc, argv, "i:o:t:")) != -1){
		switch(opt){
			case 'i':
				if(optarg[0] == '-'){
					fprintf(stderr, "%s\n", "Missing Input File Name");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					return -1;
				}
				inputPathA = malloc((strlen(optarg)+1) * sizeof(char));
				strcpy(inputPathA,optarg);
				break;
			case 'o':
				if(optarg[0] == '-'){
					fprintf(stderr, "%s\n", "Missing Output File Name");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					return -1;
				}
				outputPathA = malloc((strlen(optarg)+1) * sizeof(char));
				strcpy(outputPathA,optarg);
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
				time = atoi(optarg); 
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
	int readFD = open(inputPathA,O_RDONLY | O_NONBLOCK);
	if(readFD == -1){
		fprintf(stderr, "%s\n", "Input File Opening Failure !");
		return -1;
	}
	else{
		memset(&lock,0,sizeof(lock));
		lock.l_type = F_RDLCK;
		fcntl(readFD,F_SETLKW,&lock);

		do{ numByte = read(readFD,buffer,sizeof(buffer));
			if(numByte == sizeof(buffer)){
				line = malloc(sizeof(char)*SIZE);
				strcpy(line,"\0");
				for (int i = 0; i < numByte; i += 2){
					sprintf(complexNum,"%d%s%d",buffer[i]," +i",buffer[i+1]);
					strcat(line, complexNum);
					strcat(line,",");
					memset(complexNum, 0, 10);
				}
				line[strlen(line)-1] = ' ';
				while(strlen(line)<=SIZE){
					sprintf(complexNum,"%s"," ");
					strcat(line, complexNum);
					memset(complexNum,0,10);
				}
				line[strlen(line)-1] = '\n';
				printf("%s%d\n","The Line was Read by prog A -> pid : ",getpid());
				
				lock.l_type = F_UNLCK;
				fcntl(readFD,F_SETLKW,&lock);

				if(writeToFile(outputPathA,line,time) == -1)
					return -1;
				free(line);

				memset(&lock,0,sizeof(lock));
				lock.l_type = F_RDLCK;
				fcntl(readFD,F_SETLKW,&lock);
			}
		}while(numByte == sizeof(buffer));
		

	}
	close(readFD);
	// File Read END...
	printf("%s%d\n","Program A EXIT -> pid: ",getpid());

	int f = open("temp.txt", O_RDWR |O_CREAT|O_APPEND ,S_IRUSR | S_IWUSR);
	char a[1];
	read(f,a,1);
	if(a == '1'){
		lseek(f,1,SEEK_CUR);
		write(f,"2",1);
	}
	else
		write(f,"1",1);
	close(f);

	return 0;
}

int writeToFile(char * writeName, char * complexLine, int slp){
	char buf[1];
	char buf2[3];
	struct flock lock;
	int writeFD = open(writeName, O_RDWR | O_CREAT | O_NONBLOCK, S_IWUSR | S_IRUSR);
	if(writeFD == -1){
		fprintf(stderr, "%s\n", "Output File Opening Failure !");
		return -1;
	}
	else{
		memset(&lock,0,sizeof(lock));
		lock.l_type = F_WRLCK;
		fcntl(writeFD,F_SETLKW,&lock);

		int i = 0;
		size_t length = strlen(complexLine);
		lseek(writeFD,0,SEEK_SET);
		read(writeFD,buf,1);
		while(buf[0] != '\0'){
			if(buf[0] == '\''){
				read(writeFD,buf2,sizeof(buf2));
				if(buf2[0] == '\\' && buf2[1] == 'n' && buf2[2] == '\''){
					lseek(writeFD,-4,SEEK_CUR);
					break;
				}
				else
					lseek(writeFD,-3,SEEK_CUR);
			}
			memset(buf, 0, 1);
			read(writeFD,buf,sizeof(buf));
		}
		write(writeFD, complexLine, length);
		
		lock.l_type = F_UNLCK;
		fcntl(writeFD,F_SETLKW,&lock);
		
		printf("%s%d\n","The Line was Writen by prog A -> pid : ",getpid());
		sleep(slp / 100);
	}
	close(writeFD);

	return 0;
}