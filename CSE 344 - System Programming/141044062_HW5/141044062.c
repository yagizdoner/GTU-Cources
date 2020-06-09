/***********************************
**  Yağız Döner - 141044062       **
**  CSE 344 - System Programming  **
**  Homework  5                   **
***********************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE 1024
#define MAXFLOUR 20
#define MAXQUEUE 100

void getFloristAndClientsNumber(FILE * f, int * flo, int * cli);
int itContainsFlover(char ** flories, char * client);
int find_distance(int fX, int fY, int cX, int cY);
static void *doFlover(void *florist);
void signalHandler(int sig_num);

/* Client Request and releated florist */
typedef struct request{
    int valid;
    int distance; // Chebyshev Distance
    char * clientName; // The Name of the Client makes request
    char * flover; // Requested Flover
    char * florisName; // florist Name
    float speed; // florist speed
} request_t;

typedef struct ret{
    char * name; // flories name
    int sales; // how many sales
    int total; // total time
} return_t; // for thread return values

pthread_mutex_t mut;
pthread_cond_t con;
int ext = 0;

int main(int argc, char *argv[]){
    char * inputPath = NULL;
    // Command Line Parsing START...
    int opt;
    if(argc < 3){
        perror("There is no Argument.\nProgram EXIT !!");
        exit(-1);
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
                    exit(-1);
            }
        }
        for( ; optind < argc ; optind++){
            fprintf(stderr,"Extra argument(s) : %s\n",argv[optind]);
            fprintf(stderr, "%s\n", "Program EXIT !!");
            exit(-1);
        }
    }
    // Command Line Parsing END.

    // CTRL + C Handler
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    act.sa_handler = signalHandler;
    sigaction(SIGINT, &act, NULL);

    // Input File OPEN...
    FILE * fp = fopen(inputPath, "r");
    if(fp == NULL){
        fprintf(stderr, "%s\n", "Input File Openning Error !");
        exit(-1);
    }
    // Input File OPENED.

    // Find Number Of Florist in the File.
    int numberOfFlorist, numberOfClients;
    getFloristAndClientsNumber(fp, &numberOfFlorist, &numberOfClients);
    // Turn back to the first index of file.
    fseek(fp, 0, SEEK_SET);
    
    char line[MAXLINE];
    
    // Florist Parsing START...
    printf("Florist application initializing from file: %s\n", inputPath);
    free(inputPath);
    char * floriesName[numberOfFlorist]; // Florist Name
    int floriesXCoor[numberOfFlorist]; // Florist X Coordinat
    int floriesYCoor[numberOfFlorist]; // Florist Y Coordinat
    float floriesSpeed[numberOfFlorist]; // Florist Speed
    char * floriesFlovers[numberOfFlorist][MAXFLOUR]; //  // Florist -> Flovers 
    for (int i = 0; i < numberOfFlorist; ++i){
        char c;
        for(int j=0; j<MAXLINE ;++j){
            c = getc(fp);
            if(c == '\n'){
                line[j] = '\0';
                break;
            }
            line[j] = c;
        }

        int turn=0;
        int fl = 0;
        char * token = strtok(line, "(),;: ");
        while(token){
            if(turn == 0){
                floriesName[i] = malloc((strlen(token)+1) * sizeof(char));
                strcpy(floriesName[i],token);
            }
            else if(turn == 1){
                floriesXCoor[i] = atoi(token);                
            }
            else if(turn == 2){
                floriesYCoor[i] = atoi(token);
            }
            else if(turn == 3){
                floriesSpeed[i] = atof(token);
            }
            else if(turn>3){
                floriesFlovers[i][fl] = malloc((strlen(token)+1) * sizeof(char));
                strcpy(floriesFlovers[i][fl],token);
                ++fl;
            }
            ++turn;
            token = strtok(0, "(),;: ");
        }
        floriesFlovers[i][fl] = '\0';
        memset(line,0,MAXLINE);
    }
    // Florist Parsing END.

    printf("%d florists have been created\n", numberOfFlorist);
    getc(fp); // discard a newline between flories and clients.

    // Clients Parsing START...
    char * clientName[numberOfClients]; // Client Name
    int clientXCoor[numberOfClients]; // Client X Coordinat
    int clientYCoor[numberOfClients]; // Client Y Coordinat
    char * clientFlovers[numberOfClients]; //  // Client Flover
    for(int i=0; i<numberOfClients ;++i){
        char c;
        for(int j=0; j<MAXLINE ;++j){
            c = getc(fp);
            if(c == '\n'){
                line[j] = '\0';
                break;
            }
            line[j] = c;
        }
        int turn=0;
        char * token = strtok(line, "(),: ");
        while(token){
            if(turn == 0){
                clientName[i] = malloc((strlen(token)+1) * sizeof(char));
                strcpy(clientName[i],token);
            }
            else if(turn == 1){
                clientXCoor[i] = atoi(token);                
            }
            else if(turn == 2){
                clientYCoor[i] = atoi(token);
            }
            else if(turn == 3){
                clientFlovers[i] = malloc((strlen(token)+1) * sizeof(char));
                strcpy(clientFlovers[i],token);
            }
            ++turn;
            token = strtok(0, "(),: ");
        }
        memset(line,0,MAXLINE);        
    }
    // Client Parsing END

    fclose(fp); // File is no more important.

    pthread_mutex_init(&mut,NULL);
    pthread_cond_init(&con,NULL);
    request_t queues[numberOfFlorist][MAXQUEUE];

    // Threads Creat START...
    pthread_t threads[numberOfFlorist];
    for (int i = 0; i < numberOfFlorist; ++i){
      if (pthread_create(&threads[i], NULL, doFlover, (void *)queues[i]) != 0){
          fprintf(stderr, "Create Thread Error %d\n", i);
          exit(-1);
        }
    }
    // Threads Creat END

    // Find the Closest Flories
    printf("Processing requests\n");
    request_t request;
    for (int i = 0; i < numberOfClients; ++i){
        int dist = 9999;
        int closestFlory = -1; // There is no flory that contains clients flover
        // find the closest flories to the client flover.
        for(int j=0; j< numberOfFlorist ;++j){
            if(itContainsFlover(floriesFlovers[j],clientFlovers[i])){
                int tempDist = find_distance(floriesXCoor[j],floriesYCoor[j],
                                                 clientXCoor[i],clientYCoor[i]);
                if(tempDist < dist){
                    dist = tempDist;
                    closestFlory = j;
                }
            }            
        }
        // closest floriest index in closestFlory variable

        if(closestFlory != -1){
            // creat request
            request.distance = dist;
            request.florisName = floriesName[closestFlory];
            request.clientName = clientName[i];
            request.flover = clientFlovers[i];
            request.speed = floriesSpeed[closestFlory];
            request.valid = 1;
            // request created

            for(int j=0; j<MAXQUEUE ;++j){
                if(queues[closestFlory][j].valid == '\0'){
                    queues[closestFlory][j] = request;
                    pthread_cond_broadcast(&con); // Threads can check their queues.
                    break;
                }
                else if(j==MAXQUEUE-1){
                    fprintf(stderr, "%s\n", "Queue Overflow !!!");
                    exit(-1);
                }
            }
        }
        else{
            fprintf(stderr, "%s\n","There is no florist which sell flover you want...");
        }
    }
    ext = 1; // Now, threads can be exit, if their queues is empty.

    // Wait Florist CLOSE
    return_t * retvals[numberOfFlorist];
    for (int i = 0; i < numberOfFlorist; ++i)
    {
        if(pthread_join(threads[i], (void *)&retvals[i]) != 0){
            fprintf(stderr, "Join Thread Error %d\n", i);
            exit(-1);
        }
    }
    // All of The Flovers Finished.
    
    // Print Information
    printf("All requests processed.\n");
    for (int i = 0; i < numberOfFlorist; ++i){
        printf("%s closing shop.\n", retvals[i]->name);
    }
    printf("Sale statistics for today:\n");
    printf("-------------------------------------------------\n");
    printf("Florist       # of sales       Total time        \n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < numberOfFlorist; ++i)
    {
        printf("%-14s%-17d%dms\n",retvals[i]->name, retvals[i]->sales, retvals[i]->total );
        free(retvals[i]);
    }
    printf("-------------------------------------------------\n");

    return 0;
}

static void *doFlover(void *florist){
    request_t * r = (request_t *)florist;
    int tot = 0;
    int t=0;
    srand(time(NULL));
    while( (!(ext==1)) || r[0].valid != '\0' ){
        pthread_mutex_lock(&mut);
        // wait until, main thread writes to queue
        while(r[0].valid == '\0'){
            pthread_cond_wait(&con,&mut);
        }
        pthread_mutex_unlock(&mut);
        int preparationTime = rand()%((250+1)-1) + 1;
        int totalTime = r[0].speed * r[0].distance + preparationTime;
        sleep (totalTime / 1000); 
        /* 
        	According to HW instructions, I used sleep...
			"You can simulate it by letting the thread sleep
			for a random duration (equal to the time of 
			preparation + time of delivery)."
        */
        tot += totalTime;
        printf("Florist %s has delivered a %s to %s  in %dms\n",
            r[0].florisName, r[0].flover, r[0].clientName,totalTime);
        t++;
        if(r[1].valid == 1){
            for (int i = 1; r[i].valid != '\0'; ++i){
                r[i-1].valid = r[i].valid;
                r[i-1].distance = r[i].distance;
                r[i-1].speed = r[i].speed;
                r[i-1].clientName = r[i].clientName;
                r[i-1].flover = r[i].flover;
                r[i-1].florisName = r[i].florisName;
                r[i].valid = '\0';
            }
        }
        else{
            r[0].valid = '\0';
        }
    }
    return_t * ret = malloc(sizeof(ret));
    ret->name = r[0].florisName;
    ret->sales = t;
    ret->total = tot;
    pthread_exit(ret);
}


int find_distance(int fX, int fY, int cX, int cY){
    int a = abs(fX - cX);
    int b = abs(fY - cY);
    return fmax(a,b);
}

void getFloristAndClientsNumber(FILE * f, int * flo, int * cli){
    *flo = 0; // florist number
    *cli = 0; // client number
    while(getc(f) != '\n'){
        ++ *flo;
        while(getc(f) != '\n');
    }
    getc(f); // skip newline between clients and flories.
    while(getc(f) != '\n'){
        ++ *cli;
        while(getc(f) != '\n');
    }
}

int itContainsFlover(char ** flories, char * client){
    for (int i = 0; flories[i] != '\0'; ++i){
        if(strcmp(flories[i] , client) == 0)
            return 1; // found
    }
    return 0; // not found;
}

void signalHandler(int sig_num){
    signal(sig_num,SIG_DFL);
    raise(sig_num);
    switch(sig_num){
        case SIGINT:  puts("SIGINT CATCHING");
                      exit(0);
                      break;
    }
}