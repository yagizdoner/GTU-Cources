/***********************************
**	Yağız Döner - 141044062       **
**	CSE 344 - System Programming  **
**	Midterm Project               **
***********************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <signal.h>

void supplier(int file);
void cooks(int number);
void students(int number);
void signalHandler(int sig_num);
int N, M, T, S, K, L;
char * inputPath;
sem_t * mainSem; // One of each process will work at a time.
sem_t * supplierSize; // Total Plates of Supplier
sem_t * kitP; // Total Kitchen Soup 
sem_t * kitC; // Total Kitchen Main Course
sem_t * kitD; // Total Kitchen Desert
sem_t * atKitchen; // Total Number of Plates at the Kitchen
sem_t * kitchenSize; // Kitchen Size
sem_t * couP; // Total Counter Soup
sem_t * couC; // Total Counter Main Course
sem_t * couD; // Total Counter Desert
sem_t * atCounter; // Total Number of Plates at the Counter
sem_t * counterSize; // Counter Size
sem_t * queue; // Number of Students at the Counter
sem_t * tableSize; // Total Table Size
sem_t * barrier; // Parent - Children sync.

int main(int argc, char * argv[]){

	// Command Line Parsing START...
	int opt;
	if(argc < 2){
		perror("There is no Argument.\nProgram EXIT !!");
		exit(0);
	}
	else{
		while((opt = getopt(argc, argv, "N:M:T:S:L:F:")) != -1){
			switch(opt){
				case 'N':
					if(optarg[0] == '-'){
						fprintf(stderr, "%s\n", "Missing N");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					else if(atoi(optarg) < 3){
						fprintf(stderr, "%s\n", "Cooks(N) have to greater than 2");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					N = atoi(optarg); 
					break;
				case 'M':
					if(optarg[0] == '-'){
						fprintf(stderr, "%s\n", "Missing M");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					else if(atoi(optarg) <= N){
						fprintf(stderr, "%s\n", "Students(M) have to greater than Cooks(N)");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					M = atoi(optarg); 
					break;
				case 'T':
					if(optarg[0] == '-'){
						fprintf(stderr, "%s\n", "Missing T");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					else if(atoi(optarg) < 1 || atoi(optarg) >= M){
						fprintf(stderr, "%s\n", "Tables(T) have to between 1 and Students(M)");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					T = atoi(optarg); 
					break;
				case 'S':
					if(optarg[0] == '-'){
						fprintf(stderr, "%s\n", "Missing S");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					else if(atoi(optarg) < 4){
						fprintf(stderr, "%s\n", "Counter Size(S) has to grater than 3");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					S = atoi(optarg); 
					break;
				case 'L':
					if(optarg[0] == '-'){
						fprintf(stderr, "%s\n", "Missing L");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					else if(atoi(optarg) < 3){
						fprintf(stderr, "%s\n", "Total Times(L) have to grater than 2");
						fprintf(stderr, "%s\n", "Program EXIT !!");
						return -1;
					}
					L = atoi(optarg); 
					break;
				case 'F':
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
		K = 2 * L * M + 1;
	}
	// Command Line Parsing END...

	// Ctrl+C Signal Handler
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
    act.sa_handler = signalHandler;
    sigaction(SIGINT, &act, NULL);

    // File Opening
    int file = open(inputPath,O_RDONLY);
	if(file == -1){
		perror("Input File A Opening Failure !");
		exit(0);
	}
	free(inputPath);

	// initialize Semaphores and Shared Memories...
	int shm, atKit, kitSize, kittP, kittC, kittD, c, sub;
	int couuP, couuC, couuD, couSize, atCou, queu, tab; 
	if (
		((shm = shm_open("shm", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((atKit = shm_open("atKit", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((kitSize = shm_open("kitSize", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((kittP = shm_open("kittP", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((kittC = shm_open("kittC", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((kittD = shm_open("kittD", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((atCou = shm_open("atCou", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((couSize = shm_open("couSize", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((couuP = shm_open("couuP", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((couuC = shm_open("couuC", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((couuD = shm_open("couuD", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((queu = shm_open("queu", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((tab = shm_open("tab", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((c = shm_open("c", O_RDWR | O_CREAT, S_IRWXU)) < 0) ||
		((sub = shm_open("sub", O_RDWR | O_CREAT, S_IRWXU)) < 0)
	) {
		perror("shm_open Error");
		exit(0);
	}
	shm_unlink("shm");shm_unlink("atKit");shm_unlink("kitSize");shm_unlink("kittP");shm_unlink("kittD");
	shm_unlink("kittC");shm_unlink("atCou");shm_unlink("couSize");shm_unlink("couuP");shm_unlink("couuD");
	shm_unlink("couuC");shm_unlink("queu");shm_unlink("tab");shm_unlink("c");shm_unlink("sub");

	if ( 
		(ftruncate(shm, sizeof(sem_t)) < 0 ) ||
		(ftruncate(atKit, sizeof(sem_t)) < 0 ) ||
		(ftruncate(kitSize, sizeof(sem_t)) < 0 ) ||
		(ftruncate(kittP, sizeof(sem_t)) < 0 ) ||
		(ftruncate(kittC, sizeof(sem_t)) < 0 ) ||
		(ftruncate(kittD, sizeof(sem_t)) < 0 ) ||
		(ftruncate(atCou, sizeof(sem_t)) < 0 ) ||
		(ftruncate(couSize, sizeof(sem_t)) < 0 ) ||
		(ftruncate(couuP, sizeof(sem_t)) < 0 ) ||
		(ftruncate(couuC, sizeof(sem_t)) < 0 ) ||
		(ftruncate(couuD, sizeof(sem_t)) < 0 ) ||
		(ftruncate(queu, sizeof(sem_t)) < 0 ) ||
		(ftruncate(tab, sizeof(sem_t)) < 0 ) ||
		(ftruncate(c, sizeof(sem_t)) < 0 ) ||
		(ftruncate(sub, sizeof(sem_t)) < 0 )
	) {
		perror("ftruncate Error");
		exit(0);
	}

	if (
		((mainSem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0)) == MAP_FAILED) ||
		((atKitchen = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, atKit, 0)) == MAP_FAILED) ||
		((kitchenSize = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, kitSize, 0)) == MAP_FAILED) ||
		((kitP = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, kittP, 0)) == MAP_FAILED) ||
		((kitC = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, kittC, 0)) == MAP_FAILED) ||
		((kitD = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, kittD, 0)) == MAP_FAILED) ||
		((atCounter = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, atCou, 0)) == MAP_FAILED) ||
		((counterSize = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, couSize, 0)) == MAP_FAILED) ||
		((couP = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, couuP, 0)) == MAP_FAILED) ||
		((couC = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, couuC, 0)) == MAP_FAILED) ||
		((couD = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, couuD, 0)) == MAP_FAILED) ||
		((queue = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, queu, 0)) == MAP_FAILED) ||
		((tableSize = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, tab, 0)) == MAP_FAILED) ||
		((barrier = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, c, 0)) == MAP_FAILED) ||
		((supplierSize = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, sub, 0)) == MAP_FAILED)
	) {
		perror("mmap Error");
		exit(0);
	}
	close(shm);close(atKit);close(kitSize);close(couuD);close(tab);close(couuC);close(queu);close(sub);
	close(kittP);close(kittC);close(kittD);close(atCou);close(couSize);close(couuP);close(c);

	if (
		(sem_init(mainSem, 1, 1) < 0) ||
		(sem_init(atKitchen, 1, 0) < 0) ||
		(sem_init(kitchenSize, 1, K) < 0) ||
		(sem_init(kitP, 1, 0) < 0) ||
		(sem_init(kitC, 1, 0) < 0) ||
		(sem_init(kitD, 1, 0) < 0) ||
		(sem_init(atCounter, 1, 0) < 0) ||
		(sem_init(counterSize, 1, S) < 0) ||
		(sem_init(couP, 1, 0) < 0) ||
		(sem_init(couC, 1, 0) < 0) ||
		(sem_init(couD, 1, 0) < 0) ||
		(sem_init(queue, 1, 0) < 0) ||
		(sem_init(tableSize, 1, T) < 0) ||
		(sem_init(barrier, 1, 0) < 0) ||
		(sem_init(supplierSize, 1, 3*L*M) < 0)

	) {
		perror("sem_init Error");
		exit(0);
	}
	// Initialized

	// Fork...
	for (int i = 0; i < N+M+1; ++i){
    	pid_t child = fork();
    	if(child == -1){
    		perror("Fork Error");
    		exit(0);
    	}
    	else if(child==0){
    		if(i==0){
    			// Supplier
    			supplier(file);
    		}
    		else if(i<=N){
    			// Cooks
    			cooks(i);
    		}
    		else{
    			// Students
    			students(i-N);
    		}
    	}
	}
	// Forked.

	// Parent destroy all the semaphores.
	sem_destroy(mainSem);sem_destroy(kitP);sem_destroy(kitC);sem_destroy(kitD);sem_destroy(atKitchen);
	sem_destroy(kitchenSize);sem_destroy(couP);sem_destroy(couC);sem_destroy(couD);sem_destroy(atCounter);
	sem_destroy(counterSize);sem_destroy(queue);sem_destroy(tableSize);sem_destroy(supplierSize);

	//Wait For Children
	for (int i = 0; i < N+M+1; ++i){
		sem_wait(barrier);	
	}
	sem_destroy(barrier);
	printf("%s\n","PARENT GONE  ->  Program Finished Succesfully...");
	return 0;
}


void supplier(int file){
	// Unused semaphores in this process are closed.
	sem_destroy(couP);sem_destroy(couD);sem_destroy(couC);sem_destroy(atCounter);
	sem_destroy(counterSize);sem_destroy(queue);sem_destroy(tableSize);
	int p, c, d;
	char plate[1];
	int i = 0;
	while(i<3*L*M){
		sem_wait(kitchenSize);
		sem_wait(mainSem);
		// Supplier Critical Region Start
		sem_getvalue(kitP,&p);
		sem_getvalue(kitC,&c);
		sem_getvalue(kitD,&d);
		read(file,plate,sizeof(char));
		switch(plate[0]){
			case 'P':
				printf("%s%d%s%d%s%d%s%d\n", "The supplier is going to the kitchen to deliver soup: kitchen items P:",p,",C:",c,",D:",d,"=",p+c+d);
				sem_post(kitP);
				sem_wait(supplierSize);
				printf("%s%d%s%d%s%d%s%d\n", "The supplier delivers soup– after delivery: kitchen items P:",p+1,",C:",c,",D:",d,"=",p+c+d+1);
				break;
			case 'C':
				printf("%s%d%s%d%s%d%s%d\n", "The supplier is going to the kitchen to deliver main course: kitchen items P:",p,",C:",c,",D:",d,"=",p+c+d);
				sem_post(kitC);
				sem_wait(supplierSize);
				printf("%s%d%s%d%s%d%s%d\n", "The supplier delivers main course– after delivery: kitchen items P:",p,",C:",c+1,",D:",d,"=",p+c+d+1);
				break;
			case 'D':
				printf("%s%d%s%d%s%d%s%d\n", "The supplier is going to the kitchen to deliver desert: kitchen items P:",p,",C:",c,",D:",d,"=",p+c+d);
				sem_post(kitD);
				sem_wait(supplierSize);
				printf("%s%d%s%d%s%d%s%d\n", "The supplier delivers desert– after delivery: kitchen items P:",p,",C:",c,",D:",d+1,"=",p+c+d+1);
				break;
			default:
				perror("All Plates must be P, C or D !!!");
				perror("Program EXIT !!!");
				exit(0);
		}
		memset(plate,0,1);
		// Supplier Critical Region End
		sem_post(atKitchen);
		sem_post(mainSem);
		++i;
	}
	printf("%s\n","Supplier finished supplying – GOODBYE!");
	sem_post(atKitchen); // For cooks exit.
	// All of open semaphores are closed.
	sem_destroy(mainSem);sem_destroy(atKitchen);sem_destroy(kitchenSize);
	sem_destroy(kitP);sem_destroy(kitC);sem_destroy(kitD);sem_destroy(supplierSize);
	// For Parent Sync.
	sem_post(barrier);
	sem_destroy(barrier);
	close(file);
	exit(0);
}

void cooks(int number){
	// Unused semaphores in this process are closed.
	sem_destroy(queue);sem_destroy(tableSize);
	int valP, valC, valD, kp, kc, kd;
	int mes = 1;
	int con = 1;
	while(1){
		sem_wait(atKitchen); // Wait plates from supplier.
		sem_wait(counterSize); // Wait Counter Free.
		sem_wait(mainSem);
		// Cook Critical Region Start
		sem_getvalue(couP,&valP);
		sem_getvalue(couC,&valC);
		sem_getvalue(couD,&valD);
		sem_getvalue(kitP,&kp);
		sem_getvalue(kitC,&kc);
		sem_getvalue(kitD,&kd);
		if(mes)
			printf("%s%d%s%d%s%d%s%d%s%d\n", "Cook ", number, " is going to the kitchen to  wait for/get a plate - kitchen items P:",kp,",C:",kc,",D:",kd,"=",kp+kc+kd);
		if(kp!=0 && ((kc==0 && kd==0) || (valP<=valC && valP<=valD))){
			if( S-(valP+valC+valD) == 2 && valC==0 && valD==0 ){
				con = 1;
			}
			else if(S-(valP+valC+valD) == 1 && (valC==0 || valD==0) ){
				con = 1;
			}
			else{
				// Give Soup (P) to the Counter from Kitchen
				sem_wait(kitP);
				con = 0;
				printf("%s%d%s%d%s%d%s%d%s%d\n", "Cook ", number, " is going to the counter to deliver soup – counter items P:",valP,",C:",valC,",D:",valD,"=",valP+valC+valD);
				sem_post(kitchenSize); // open a new area
				sem_post(couP);
				sem_post(atCounter);
				printf("%s%d%s%d%s%d%s%d%s%d\n", "Cook ", number, " placed soup on the counter - counter items P:",valP+1,",C:",valC,",D:",valD,"=",valP+valC+valD+1);
			}
		}
		else if(kc!=0 && ((kp==0 && kd==0) || (valC<=valP && valC<=valD))){
			if( S-(valP+valC+valD) == 2 && valP==0 && valD==0 ){
				con = 1;
			}
			else if(S-(valP+valC+valD) == 1 && (valP==0 || valD==0) ){
				con = 1;
			}
			else{
				// Give Main Course (C) to the Counter from Kitchen
				sem_wait(kitC);
				con = 0;
				printf("%s%d%s%d%s%d%s%d%s%d\n", "Cook ", number, " is going to the counter to deliver main course – counter items P:",valP,",C:",valC,",D:",valD,"=",valP+valC+valD);
				sem_post(kitchenSize); // open a new area
				sem_post(couC);
				sem_post(atCounter);
				printf("%s%d%s%d%s%d%s%d%s%d\n", "Cook ", number, " placed main course on the counter - counter items P:",valP,",C:",valC+1,",D:",valD,"=",valP+valC+valD+1);
			}
		}
		else if(kd!=0){
			if( S-(valP+valC+valD) == 2 && valC==0 && valP==0 ){
				con = 1;
			}
			else if(S-(valP+valC+valD) == 1 && (valC==0 || valP==0) ){
				con = 1;
			}
			else{
				// Give Desert (D) to the Counter from Kitchen
				sem_wait(kitD);
				con = 0;
				printf("%s%d%s%d%s%d%s%d%s%d\n", "Cook ", number, " is going to the counter to deliver desert – counter items P:",valP,",C:",valC,",D:",valD,"=",valP+valC+valD);
				sem_post(kitchenSize); // open a new area
				sem_post(couD);
				sem_post(atCounter);
				printf("%s%d%s%d%s%d%s%d%s%d\n", "Cook ", number, " placed desert on the counter - counter items P:",valP,",C:",valC,",D:",valD+1,"=",valP+valC+valD+1);
			}
		}
		else{
			int exit;
			sem_getvalue(supplierSize,&exit);
			if(exit == 0){
				// Supplier Filenished and No more plates in the kitchen.
				printf("%s%d%s\n","Cook ", number ," finished serving - items at kitchen: 0 – going home – GOODBYE!!!");
				sem_post(counterSize);
				sem_post(atKitchen); // In Here, Supplier was finished. So, atKitchen no more important. I post it, so all of the cooks can exit.
				sem_post(mainSem);
				break;
			}
			else{
				con = 1;
			}
		}
		if(con){
			// There is a deadlock situation and cook wait supplier to get more plates.
			mes=0;
			sem_post(counterSize);
			sem_post(atKitchen);
			sem_post(mainSem);
			continue;
		}
		mes=1;
		// Cook Critical Region End
		sem_post(mainSem);
	}
	// All of open semaphores are closed.
	sem_destroy(mainSem);sem_destroy(kitP);sem_destroy(kitD);sem_destroy(kitC);sem_destroy(atKitchen);
	sem_destroy(kitchenSize);sem_destroy(couP);sem_destroy(couC);sem_destroy(couD);
	sem_destroy(atCounter);sem_destroy(counterSize);sem_destroy(supplierSize);
	// For Parent Sync.
	sem_post(barrier);
	sem_destroy(barrier);
	exit(0);
}

void students(int number){
	// Unused semaphores in this process are closed.
	sem_destroy(kitP);sem_destroy(kitC);sem_destroy(kitD);
	sem_destroy(atKitchen);sem_destroy(kitchenSize);sem_destroy(supplierSize);
	int q, p, c, d, t;
	int round = 1;
	int mes = 1;
	while(round <= L){
		sem_wait(mainSem);
		sem_getvalue(couP,&p);
		sem_getvalue(couD,&d);
		sem_getvalue(couC,&c);
		sem_getvalue(queue,&q);
		if(mes){
			sem_post(queue);
			printf("%s%d%s%d%s%d%s%d%s%d%s%d%s%d\n","Student ",number," is going to the counter (round ",round,") - # of students at counter: ",
				q+1," and counter items P:",p,",C:",c,",D:",d,"=",p+c+d);
		}
		if(p>0 && c>0 && d>0){
			sem_wait(couP); sem_wait(couC); sem_wait(couD);
			sem_wait(atCounter);sem_post(counterSize);sem_wait(atCounter);sem_post(counterSize);sem_wait(atCounter);sem_post(counterSize);
			mes = 1;
			sem_wait(queue);
			sem_post(mainSem);
		}
		else{
			mes = 0;
			sem_post(mainSem);
			continue;
		}
		// Going to Table
		sem_getvalue(tableSize,&t);
		printf("%s%d%s%d%s%d\n","Student ",number," got food and is going to get a table (round ",round,") - # of empty tables: ",t);
		sem_wait(tableSize); // Wait For a Empty Table
		printf("%s%d%s%d%s%d%s%d\n","Student ",number," sat at table ",t," to eat (round ",round,") - empty tables:",t-1);
		sem_post(tableSize);
		printf("%s%d%s%d%s%d%s%d\n","Student ",number," left table ",t," to eat again (round ",round,") - empty tables:",t);
		round++;
		// Leave from Table		
	}
	printf("%s%d%s%d%s\n","Student ",number," is done eating L=",L," times - going home – GOODBYE!!!" );
	// All of open semaphores are closed.
	sem_destroy(mainSem);sem_destroy(couP);sem_destroy(couD);sem_destroy(couC);sem_destroy(atCounter);
	sem_destroy(counterSize);sem_destroy(queue);sem_destroy(tableSize);
	// For Parent Sync.
	sem_post(barrier);
	sem_destroy(barrier);
	exit(0);
}

void signalHandler(int sig_num){
    signal(sig_num,SIG_DFL);
	raise(sig_num);
    switch(sig_num){
    	case SIGINT:  puts("Signal Handler Caught SIGINT.\nProgram EXIT Gracefully!");
    				  exit(0);
					  // exit is close all open files and free all allocated memory...
    }
}