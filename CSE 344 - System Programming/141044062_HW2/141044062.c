///////////////////////////////
//  Yağız Döner - 141044062  //
//  System Programming - HW2 //
///////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

#define SIZE 130

int leastSquareMethod(const int x[], const int y[], float* m, float* b);
int byteToInt(int * arr);
int writeToFile(char * writeFD, char * complexLine);
int lineNumber(int fd);
int lineLength(int fd);
float meanAbsoluteError(int arrX[], int arrY[], float xLSM, float yLSM);
float meanSquaredError(int arrX[], int arrY[], float xLSM, float yLSM);
float rootMeanSquaredError(int arrX[], int arrY[], float xLSM, float yLSM);
void calculation(int fd, char * line);
void childProcess(int input, char * output);
void criticalIgnoreParent(int sig_num);
void criticalIgnoreChild(int sig_num);
float standartDev(float arr[]);
float meanValue(float arr[]);
void fillTheMetric(float mae, float mse, float rmse);
void sigTermHandler(int sig_num);
void exitGracefully();
int signalsParent[20];
int ind = 0;
int in = 0;
pid_t child_pid;
char * fi;
char * fo;
char * ft; // file descriptors for exitGracefully 
float maeArr[100];
float mseArr[100];
float rmseArr[100];

int main(int argc, char * argv[]){
	char * line;
	char buffer[160];
	char coor[10];
	char leastSm[20];
	float xAxs;
	float yAxs;
	int lb, rb, fd;
	int lByte[8];
	int rByte[8];
	int coorX[10];
	int coorY[10];
	size_t numByte;
	int opt;
	char * inputPathA;
	char * outputPathA;
	int totalBytesread = 0;
	int unreadBytes;
	// Command Line Parsing START...
	while((opt = getopt(argc, argv, "i:o:")) != -1){
		switch(opt){
			case 'i':
				if(optarg[0] == '-'){
					fprintf(stderr, "%s\n", "Missing Input File Name");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					exit(-1);
				}
				inputPathA = malloc((strlen(optarg)+1) * sizeof(char));
				strcpy(inputPathA,optarg);
				break;
			case 'o':
				if(optarg[0] == '-'){
					fprintf(stderr, "%s\n", "Missing Output File Name");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					exit(-1);
				}
				outputPathA = malloc((strlen(optarg)+1) * sizeof(char));
				strcpy(outputPathA,optarg);
				break;
			case '?':
				fprintf(stderr,"Unknown option : %c\n", optopt);
				fprintf(stderr, "%s\n", "Program EXIT !!");
				exit(-1);
		}
	}
	for( ; optind < argc ; optind++){
		fprintf(stderr,"Extra argument(s) : %s\n",argv[optind]);
		fprintf(stderr, "%s\n", "Program EXIT !!");
		exit(-1);
	}
	// Command Line Parsing END...
	char name[] = "myFileXXXXXX";
	fd = mkstemp(name);
	if(fd == -1){
		fprintf(stderr, "%s\n", "mkstemp File Opening Failure !");
		exit(-1);
	}
	if(ft == NULL){
		ft = malloc(strlen(name)+1);
		strcpy(ft,name);
	}
	// temporary file created.
	remove(outputPathA);
	child_pid = fork();

	struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = sigTermHandler;
    sigaction(SIGTERM, &action, NULL);

	if(child_pid == -1)
		fprintf(stderr, "%s\n","Fork Error");
	else if(child_pid != 0){
		//Parent Process
		struct flock rlock;
		struct flock wlock;

		// File Read START...
		int readFD = open(inputPathA,O_RDONLY);
		if(readFD == -1){
			fprintf(stderr, "%s\n", "Input File Opening Failure !");
			kill(child_pid,SIGKILL);
			remove(ft);
			exit(-1);
		}
		else{
			if(fi == NULL){
				fi = malloc(strlen(inputPathA)+1);
				strcpy(fi,inputPathA);
			}
			memset(&rlock,0,sizeof(rlock));
			rlock.l_type = F_RDLCK;
			fcntl(readFD,F_SETLKW,&rlock);
			// locked.
			line = malloc(sizeof(char)*SIZE);
			do{ numByte = read(readFD,buffer,sizeof(buffer));
				if(numByte == sizeof(buffer)){
					totalBytesread += numByte;
					strcpy(line,"\0");
					for (int i = 0; i < numByte; i+=16){
						int c=0;
						while(c<8){
							lByte[c] = (buffer[i+c]-48);
							rByte[c] = (buffer[i+c+8]-48);
							c++;
						}
						lb = byteToInt(lByte);
						rb = byteToInt(rByte);
						sprintf(coor,"%s%d%s%d%s","(",lb,",",rb,")");
						coorX[i/15] = lb;
						coorY[i/15] = rb;
						strcat(line, coor);
						strcat(line,",");
						memset(lByte,0,8);
						memset(rByte,0,8);
						memset(coor, 0, 10);
					}

					if(leastSquareMethod(coorX,coorY, & xAxs, & yAxs) == 0){
						sprintf(leastSm,"%.3f%s%.3f\n", xAxs, "x+" ,yAxs);
						strcat(line,leastSm);
						memset(leastSm,0,20);
					}
					memset(&wlock,0,sizeof(wlock));
					wlock.l_type = F_WRLCK;
					fcntl(fd,F_SETLKW,&wlock);
					// locked.
					write(fd,line,strlen(line));

					kill(child_pid,SIGUSR2); // sent to child. Line written.

					wlock.l_type = F_UNLCK;
					fcntl(fd,F_SETLKW,&wlock);
					memset(&wlock,0,sizeof(wlock));
					// unlocked.
					memset(coorX,0,10);
					memset(coorY,0,10);
				}
				else{
					unreadBytes = numByte;
				}
			}while(numByte == sizeof(buffer));
			rlock.l_type = F_UNLCK;
			fcntl(readFD,F_SETLKW,&rlock);
			memset(&rlock,0,sizeof(rlock));
			// unlocked.
		}
		kill(child_pid,SIGUSR1); // sent to child. Parent finished.
		printf("%s %d\n","(Process 1) Total Bytes of Input File :",unreadBytes+totalBytesread);
		printf("%s %d\n","(Process 1) Total Executed Bytes :", totalBytesread);
		printf("%s %d\n","(Process 1) Total Line :", totalBytesread/160 );
		if(strlen(signalsParent) != NULL){
			printf("%s", "(Process 1) Signals in Critical Region : " );
			for(int k=0;k<strlen(signalsParent);++k){
				printf("%s ", strsignal(signalsParent[k]));
			}
			printf("\n");
		}
		else
			printf("%s\n","(Process 1) No Signal in Critical Region." );
		free(line);
		free(fi); free(fo); free(ft);
		free(inputPathA); free(outputPathA);
		close(readFD);
		close(fd);
		return 0;
		// File Read END...
	}
	else{
		//Child Process
		struct sigaction sact;
		sigset_t sigset2;
		sigfillset(&sigset2);
		sigdelset(&sigset2,SIGUSR2);
		sigset_t sigset1;
		sigfillset(&sigset1);
		sigdelset(&sigset1,SIGUSR1);
		sact.sa_flags = 0;
		sact.sa_handler = criticalIgnoreChild;

		if(fd == -1){
			fprintf(stderr, "%s\n", "mkstemp File Opening Failure !");
			return -1;
		}

		for(;;){
			sigaction(SIGUSR1, &sact, NULL);
			sigaction(SIGUSR2, &sact, NULL);
			if(sigsuspend(&sigset2) == -1) // while first line is written to temp file, wait.
				childProcess(fd,outputPathA);
			
			if(sigsuspend(&sigset1) == -1){
				break;
			}
			else{}
		}
		childProcess(fd,outputPathA);
		printf("%s\n", "(Process 2) Termination Results:");
		for(int y=0; y<in ;y++){
			printf("%s %d %s","Line",y,"Metrics : ");
			printf("%.3f %.3f %.3f\n", maeArr[y], mseArr[y], rmseArr[y]);
		}
		printf("%s %.3f %s %.3f\n", "MAE mean : ", meanValue(maeArr), " Standart Dev : ", standartDev(maeArr));
		printf("%s %.3f %s %.3f\n", "MSE mean : ", meanValue(mseArr), " Standart Dev : ", standartDev(mseArr));
		printf("%s %.3f %s %.3f\n", "RMSE mean : ", meanValue(rmseArr), " Standart Dev : ", standartDev(rmseArr));

		remove(name);
		exit(0);
	}
}

void childProcess(int input, char * output){
	char buf[1];
	char c[2];
	char * line;
	struct flock ilock;

	memset(&ilock,0,sizeof(ilock));
	ilock.l_type = F_WRLCK;
	fcntl(input,F_SETLKW,&ilock);
	// locked
	int totalLine = lineNumber(input); // number of line in inputFile

	lseek(input,0,SEEK_SET);
	for (int i = 0; i < totalLine; ++i){
		int ind = 0;
		int writable = 1;
		int lengthLine = lineLength(input);
		lseek(input,(lengthLine- (2*lengthLine) - 1),SEEK_CUR);
		line = malloc(sizeof(char) * lengthLine);
		strcpy(line,"\0");
		do{
			memset(buf, 0, 1);
			read(input,buf,1);
			if(ind < 5 & buf[0] == ' '){ // first index
				writable = 0;
			}
			ind++;
			sprintf(c,"%c",buf[0]);
			strcat(line, c);
			memset(c,0,2);
		}while(buf[0] != '\n');
		line[strlen(line)-1] = '\n';
		if(writable == 1){
			if(writeToFile(output,line) == -1)
				return -1;
			else{
				lseek(input,(lengthLine- (2*lengthLine) - 1),SEEK_CUR);
				for(int j=0; j<lengthLine ;++j){
					write(input," ",1);
				}
				lseek(input,1,SEEK_CUR);
			}
		}
		memset(buf,0,1);
		free(line);
	}
	ilock.l_type = F_UNLCK;
	fcntl(input,F_SETLKW,&ilock);
	memset(&ilock,0,sizeof(ilock));
	// unlocked
}

void exitGracefully(){
	printf("%s\n","ECIT WORKS" );
	close(fi); close(fo); close(ft);
	free(fi); free(fo); free(ft);
	remove(fi);	remove(ft);
	exit(0);
}

void criticalIgnoreParent(int sig_num){
    switch(sig_num){
    	case SIGINT:  puts("Critical Section Cannot Interrupt by SIGINT.");
    				  signalsParent[ind] = sig_num;
    				  ind++;
    				  break;
    	default:	  signalsParent[ind] = sig_num;
    				  ind++;
    }
} 

void criticalIgnoreChild(int sig_num){
    switch(sig_num){
    	case SIGINT:  puts("Critical Section Cannot Interrupt by SIGINT.");
    				  break;
		case SIGUSR1: puts("catcher caught SIGUSR1");
					  break;
		case SIGUSR2: puts("catcher caught SIGUSR2");
					  break;
    }
} 

void sigTermHandler(int sig_num){
	switch(sig_num){
    	case SIGTERM:   puts("SIGTERM SIGNAL HANDLED ! Exit Gracefully.");
    				    if(child_pid > 0){
	    				    kill(child_pid,SIGTERM); 
						}
						else{
						    kill(getppid(),SIGTERM); 
						}
						exitGracefully();
    }
}

int leastSquareMethod(const int x[], const int y[], float* m, float* b){
    int totalX = 0;
    int totalXsq = 0;
    int totalXY = 0;
    int totalY = 0;

    // Sigint(Ctrl+C) handled. SIGSTOP can't handle.
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_flags = 0;
    act.sa_handler = criticalIgnoreParent;


    if((sigemptyset(&act.sa_mask)==-1) || (sigaction(SIGINT,&act,NULL) ==-1))
    	fprintf(stderr, "%s\n","Signal Handler Failure !!!" );
    else{
    	 
    	// sleep(2); // You can use it in the DEMO to show how SIGINT works.

    	for (int i=0;i<10;i++){ 
	        totalX  += x[i];       
	        totalXsq += (x[i] * x[i]);  
	        totalXY += (x[i] * y[i]);
	        totalY  += y[i];      
	    } 

	    float t = ((10 * totalXsq) - (totalX * totalX));
	    if (t == 0) {
	        *m = 0.0;
	        *b = 0.0;
	        return -1;
	    }

	    *m = ((10 * totalXY)  -  (totalX * totalY)) / t;
	    *b = ((totalY * totalXsq)  -  (totalX * totalXY)) / t;
	    return 0;
	}
	return 0; 
}

int byteToInt(int * arr){
	int total = 0;
	for(int i = 0; i < 8 ;i++){
		total += arr[i] * pow(2,(7-i));
	}
	return total;
}

int writeToFile(char * writeName, char * complexLine){
	struct flock olock;

	memset(&olock,0,sizeof(olock));
	olock.l_type = F_WRLCK;
	fcntl(writeName,F_SETLKW,&olock);
	// locked.

	int writeFD = open(writeName, O_RDWR | O_APPEND | O_CREAT, S_IWUSR | S_IRUSR);
	if(writeFD == -1){
		fprintf(stderr, "%s\n", "Output File Opening Failure !");
		return -1;
	}
	else{
		if(fo == NULL){
			fo = malloc(strlen(writeName)+1);
			strcpy(fo,writeName);
		}
		calculation(writeFD,complexLine); // write to file with Calculations
	}
	olock.l_type = F_UNLCK;
	fcntl(writeName,F_SETLKW,&olock);
	memset(&olock,0,sizeof(olock));
	// unlocked.
	close(writeFD);
	return 0;
}

void calculation(int fd, char * line){
	char ret[200];
    int i = 0;
    int turn = 0;
    strcpy(ret, line);
    // line parsing start
    char delim[7] = "(,)x+ ";
    int xAxis[10];
    int yAxis[10];
    float xLSM, yLSM;
    char *comp = strtok(line,delim);
	while (comp != NULL){
        if(i%2 == 0)
        	if(turn == 10)
        		xLSM = strtof(comp,NULL);
        	else
            	xAxis[turn] = atoi(comp);
        else{
        	if(turn == 10)
        		yLSM = strtof(comp,NULL);
        	else{
	            yAxis[turn] = atoi(comp);
	            ++turn;
	        }
        }
        comp = strtok(NULL, delim);
        i++;
	}
	free(comp);
    // line parsing end
    
	// Sigint(Ctrl+C) handled. SIGSTOP can't handle.
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler = criticalIgnoreChild;
    act.sa_flags = 0;

    if((sigemptyset(&act.sa_mask)== -1) || (sigaction(SIGINT,&act,NULL) == -1))
    	fprintf(stderr, "%s\n","Signal Handler Failure !!!" );
    else{
    	//printf("%d\n",getppid() );
    	//printf("%d\n", getpid());
    	//sleep(5); // You can use it in the DEMO to show how SIGINT / SIGTERM works.

		float mae = meanAbsoluteError(xAxis,yAxis,xLSM,yLSM);
		float mse = meanSquaredError(xAxis,yAxis,xLSM,yLSM);
		float rmse = rootMeanSquaredError(xAxis,yAxis,xLSM,yLSM);
		fillTheMetric(mae,mse,rmse);
		char cal[50];
		sprintf(cal,"%s %.3f%s %.3f%s %.3f\n",",",mae,",",mse,",",rmse);
		ret[strlen(ret)-1] = '\0';
		strcat(ret,cal);
	    write(fd,ret,strlen(ret));
	}
}

float meanAbsoluteError(int arrX[], int arrY[], float xLSM, float yLSM){  
    float ret = 0; 
    for (int i = 0; i < 10; i++) 
        ret += abs((xLSM * arrX[i] + yLSM) - arrY[i]);   
    return ret / 10; 
}

float meanSquaredError(int arrX[], int arrY[], float xLSM, float yLSM){
	float ret = 0; 
    for (int i = 0; i < 10; i++) 
        ret += pow(((xLSM * arrX[i] + yLSM) - arrY[i]),2);   
    return ret / 10;	
}

float rootMeanSquaredError(int arrX[], int arrY[], float xLSM, float yLSM){
	return sqrt(meanSquaredError(arrX,arrY,xLSM,yLSM));
}

void fillTheMetric(float mae, float mse, float rmse){
	maeArr[in] = mae;
	mseArr[in] = mse;
	rmseArr[in] = rmse;
	in++;
}

float meanValue(float arr[]){
	float res = 0.0;
	if(strlen(arr) == 0)
		return 0.0;
	for(int i=0; i<in; ++i)
		res += arr[i];
	return res/in;
}

float standartDev(float arr[]){
	float mean = meanValue(arr);
	float res = 0.0;
	if(strlen(arr) == 0)
		return 0.0;
	for(int i=0; i<in ;++i){
		res += (pow((arr[i]-mean),2));
	}
	return sqrt(res/in);
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

