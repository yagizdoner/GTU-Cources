/***********************************
**	Yağız Döner - 141044062       **
**	CSE 344 - System Programming  **
**	Homework 4                    **
***********************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

static void *chefsFunction(void *chef);

char * inputPath;
sem_t chefSem; // For chef Sync.
sem_t sem; // For seller Sync.
int* M;
int* F;
int* S;
int* W;

int main(int argc, char * argv[]){

	// Command Line Parsing START...
	int opt;
	if(argc < 2){
		perror("There is no Argument.\nProgram EXIT !!");
		exit(0);
	}
	else{
		while((opt = getopt(argc, argv, "i:")) != -1){
			switch(opt){
				case 'i':
					if(optarg[0] == '-'){
						fprintf(stderr, "%s\n", "Missing Input File Name");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					inputPath = malloc((strlen(optarg)+1) * sizeof(char));
					strcpy(inputPath,optarg);
					break;
				case '?':
					fprintf(stderr,"Unknown option : %c\n", optopt);
					fprintf(stderr, "%s\n", "Program EXIT !!");
					exit(0);
			}
		}
		for( ; optind < argc ; optind++){
			fprintf(stderr,"Extra argument(s) : %s\n",argv[optind]);
			fprintf(stderr, "%s\n", "Program EXIT !!");
			exit(0);
		}
	}
	// Command Line Parsing END.

    // File Opening...
    FILE* file = fopen(inputPath, "r");
	if(file == NULL){
		perror("Input File Opening Failure !");
		exit(0);
	}
	free(inputPath);
	// File Opened.


	M =  malloc(2*sizeof(int));
	F =  malloc(2*sizeof(int));
	S =  malloc(2*sizeof(int));
	W =  malloc(2*sizeof(int));


	int ret1 = sem_init(&chefSem, 0, 1);
	int ret2 = sem_init(&sem, 0, 0);
	if(ret1 == -1 || ret2 == -1){
		fprintf(stderr, "%s\n", "semaphore error. Program Exit");
		exit(0);
	} 

	pthread_t t1, t2, t3, t4, t5, t6;
	int s1, s2, s3, s4, s5, s6;

	s1 = pthread_create(&t1, NULL, chefsFunction, (void *)"1");
	s2 = pthread_create(&t2, NULL, chefsFunction, (void *)"2");
	s3 = pthread_create(&t3, NULL, chefsFunction, (void *)"3");
	s4 = pthread_create(&t4, NULL, chefsFunction, (void *)"4");
	s5 = pthread_create(&t5, NULL, chefsFunction, (void *)"5");
	s6 = pthread_create(&t6, NULL, chefsFunction, (void *)"6");

	if( s1!=0 || s2!=0 || s3!=0 || s4!=0 || s5!=0 || s6!=0){
		fprintf(stderr, "%s\n", "pthread_create error! Program Exit...");
		exit(0);
	}

	char * line = 0;
	size_t size = 2;
	while (getline(&line, &size,file)>0){
		int s=0;
		int f=0;
		int m=0;
		int w=0;
		// line[0] and line[1] is ready.
		if(line[0] == 'S' || line[1] == 'S'){
			s=1;
		}
		if(line[0] == 'W' || line[1] == 'W'){
			w=1;
		}
		if(line[0] == 'M' || line[1] == 'M'){
			m=1;
		}
		if(line[0] == 'F' || line[1] == 'F'){
			f=1;
		}
		free(line);
		line=NULL;
		if(s==1 && w==1){
			printf("%s\n","the wholesaler delivers sugar and walnuts");
			S[0] = 1;
			W[0] = 1;
		}
		else if(s==1 && m==1){
			printf("%s\n","the wholesaler delivers sugar and milk");
			S[0] = 1;
			M[0] = 1;
		}
		else if(s==1 && f==1){
			printf("%s\n","the wholesaler delivers sugar and flour");
			S[0] = 1;
			F[0] = 1;
		}
		else if(f==1 && m==1){
			printf("%s\n","the wholesaler delivers flour and milk");
			F[0] = 1;
			M[0] = 1;
		}
		else if(f==1 && w==1){
			printf("%s\n","the wholesaler delivers flour and walnuts");
			F[0] = 1;
			W[0] = 1;
		}
		else if(m==1 && w==1){
			printf("%s\n","the wholesaler delivers walnuts and milk");
			M[0] = 1;
			W[0] = 1;
		}
		// ingradients delivered to street
		printf("%s\n","the wholesaler is waiting for the dessert");
		sem_wait(&sem); // Waiting for Chef.
		printf("%s\n","the wholesaler has obtained the dessert and left to sell it");
	}
	
	F[0] = -1; M[0] = -1; W[0] = -1; S[0] = -1;
	fclose(file);
	void * ret = (void *)1;
	pthread_exit(ret);
}

static void *chefsFunction(void *chef){
	char *c = (char*)chef;
	int mes = 1;	
	switch(c[0]){
		case '1': 
				while(1){
					if(mes==1){
						printf("%s\n","chef1 is waiting for walnuts and sugar");
					}
					sem_wait(&chefSem);
					if(W[0]==1 && S[0]==1){
						W[0]=0;
						printf("%s\n","chef1 has taken the walnuts");
						S[0]=0;
						printf("%s\n","chef1 has taken the sugar" );
						printf("%s\n","chef1 is preparing the dessert");
						int ran = 1 + (rand() % 5);
						sleep(ran);
						printf("%s\n","chef1 has delivered the dessert to the wholesaler");
						mes=1;
						sem_post(&sem);
					}
					else{
						mes=0;
					}
				    sem_post(&chefSem);
				    if(M[0] == -1) // M or W or F or S (one of them)
				    	break;
				}
				break;
		case '2':
				while(1){
					if(mes==1){
						printf("%s\n","chef2 is waiting for walnuts and flour");
					}
					sem_wait(&chefSem);
				    if(W[0]==1 && F[0]==1){
						W[0]=0;
						printf("%s\n","chef2 has taken the walnuts");
						F[0]=0;
						printf("%s\n","chef2 has taken the flour" );
						printf("%s\n","chef2 is preparing the dessert");
						int ran = 1 + (rand() % 5);
						sleep(ran);
						printf("%s\n","chef2 has delivered the dessert to the wholesaler");
						mes=1;
						sem_post(&sem);
					}
					else{
						mes=0;
					}
				    sem_post(&chefSem);
				    if(M[0] == -1) // M or W or F or S (one of them)
				    	break;
				}
				break;
		case '3':
				while(1){
					if(mes==1){
						printf("%s\n","chef3 is waiting for sugar and flour");
					}
					sem_wait(&chefSem);
				    if(S[0]==1 && F[0]==1){
						S[0]=0;
						printf("%s\n","chef3 has taken the sugar");
						F[0]=0;
						printf("%s\n","chef3 has taken the flour" );
						printf("%s\n","chef3 is preparing the dessert");
						int ran = 1 + (rand() % 5);
						sleep(ran);
						printf("%s\n","chef3 has delivered the dessert to the wholesaler");
						mes=1;
						sem_post(&sem);
					}
					else{
						mes=0;
					}
				    sem_post(&chefSem);
				    if(M[0] == -1) // M or W or F or S (one of them)
				    	break;
				}
				break;
		case '4':
				while(1){
					if(mes==1){
						printf("%s\n","chef4 is waiting for milk and sugar");
					}
					sem_wait(&chefSem);
				    if(M[0]==1 && S[0]==1){
						M[0]=0;
						printf("%s\n","chef4 has taken the milk");
						S[0]=0;
						printf("%s\n","chef4 has taken the sugar" );
						printf("%s\n","chef4 is preparing the dessert");
						int ran = 1 + (rand() % 5);
						sleep(ran);
						printf("%s\n","chef4 has delivered the dessert to the wholesaler");
						mes=1;
						sem_post(&sem);
					}
					else{
						mes=0;
					}
				    sem_post(&chefSem);
				    if(M[0] == -1) // M or W or F or S (one of them)
				    	break;
				}	
				break;		
		case '5':
				while(1){
					if(mes==1){
						printf("%s\n","chef5 is waiting for milk and walnuts");
					}
					sem_wait(&chefSem);
				    if(M[0]==1 && W[0]==1){
						M[0]=0;
						printf("%s\n","chef5 has taken the milk");
						W[0]=0;
						printf("%s\n","chef5 has taken the walnuts" );
						printf("%s\n","chef5 is preparing the dessert");
						int ran = 1 + (rand() % 5);
						sleep(ran);
						printf("%s\n","chef5 has delivered the dessert to the wholesaler");
						mes=1;
						sem_post(&sem);
					}
					else{
						mes=0;
					}
				    sem_post(&chefSem);
				    if(M[0] == -1) // M or W or F or S (one of them)
				    	break;
				}	
				break;		
		case '6':
				while(1){ 
					if(mes==1){
						printf("%s\n","chef6 is waiting for flour and milk");
					}
					sem_wait(&chefSem);
				    if(F[0]==1 && M[0]==1){
						F[0]=0;
						printf("%s\n","chef6 has taken the flour");
						M[0]=0;
						printf("%s\n","chef6 has taken the milk" );
						printf("%s\n","chef6 is preparing the dessert");
						int ran = 1 + (rand() % 5);
						sleep(ran);
						printf("%s\n","chef6 has delivered the dessert to the wholesaler");
						mes=1;
						sem_post(&sem);
					}
					else{
						mes=0;
					}
				    sem_post(&chefSem);
				    if(M[0] == -1) // M or W or F or S (one of them)
				    	break;
				}	
				break;	
		default: fprintf(stderr, "%s\n", "Switch Error ->  There are chefs.");				   
	}
	void * ret = (void *)1;
	pthread_exit(ret);
}

