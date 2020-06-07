#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <math.h>


void exitGracefully(void);
void calculateQuarter (int ** m1, int ** m2, int ** m3, int ** m4, int ** c, int size);
void doChild(int size, int * fs, int * ft, int ** block);
void signalHandler(int sig_num);
static void Sort_by_Decreasing_Singular_Values(int nrows, int ncols,
                                double* singular_values, double* U, double* V);
static int Givens_Reduction_to_Diagonal_Form( int nrows, int ncols,
           double* U, double* V, double* diagonal, double* superdiagonal );
static void Householders_Reduction_to_Bidiagonal_Form(double* A, int nrows,
    int ncols, double* U, double* V, double* diagonal, double* superdiagonal );
int Singular_Value_Decomposition(double* A, int nrows, int ncols, double* U, 
                      double* singular_values, double* V, double* dummy_array);

int w1[2],  w2[2], w3[2], w4[2];


int main(int argc, char * argv[]){
	size_t numByteA;
	size_t numByteB;
	int opt;
	int n;
	char * inputPathA;
	char * inputPathB;
	// Command Line Parsing START...
	while((opt = getopt(argc, argv, "i:j:n:")) != -1){
		switch(opt){
			case 'i':
				if(optarg[0] == '-'){
					fprintf(stderr, "%s\n", "Missing InputA File Name");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					return -1;
				}
				inputPathA = malloc((strlen(optarg)+1) * sizeof(char));
				strcpy(inputPathA,optarg);
				break;
			case 'j':
				if(optarg[0] == '-'){
					fprintf(stderr, "%s\n", "Missing InputB File Name");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					return -1;
				}
				inputPathB = malloc((strlen(optarg)+1) * sizeof(char));
				strcpy(inputPathB,optarg);
				break;
			case 'n':
				if(optarg[0] == '-'){
					fprintf(stderr, "%s\n", "Missing N");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					return -1;
				}
				else if(atoi(optarg) < 1){
					fprintf(stderr, "%s\n", "N has to be Positive Integer");
					fprintf(stderr, "%s\n", "Program EXIT !!");
					return -1;
				}
				n = atoi(optarg); 
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


	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
    act.sa_handler = signalHandler;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGCHLD, &act, NULL);
    
    /*struct sigaction act2;
    act2.sa_handler = signalHandler;
    sigaction(SIGCHLD, &act, NULL);*/

	int size = (int)(pow(2,n) + 0.5 );
	char bufferA[size];
	char bufferB[size];
	int ** inputA = (int **)malloc(size * sizeof(int *)); 
	int ** inputB = (int **)malloc(size * sizeof(int *)); 

	// File Read START...
	int readA = open(inputPathA,O_RDONLY);
	int readB = open(inputPathB,O_RDONLY);
	if(readA == -1){
		fprintf(stderr, "%s\n", "Input File A Opening Failure !");
		return -1;
	}
	else if(readB == -1){
		fprintf(stderr, "%s\n", "Input File B Opening Failure !");
		return -1;
	}
	else{
		for(int i=0; i< size ;++i){
			inputA[i] = (int *)malloc(size * sizeof(int)); 
			inputB[i] = (int *)malloc(size * sizeof(int));

			numByteA = read(readA,bufferA,sizeof(bufferA));
			numByteB = read(readB,bufferB,sizeof(bufferB));
			if(numByteA == sizeof(bufferA) && numByteB == sizeof(bufferB)){
				for (int j=0; j < size; ++j){
					int a = bufferA[j];
					int b = bufferB[j];
					if(a>=33 && a<=126 && b>=33 && b<=126){ // If sufficient Character...
						// Demoda 33 ile oynayarak exitGraci gösterebilirsin...
						inputA[i][j] = a;
						inputB[i][j] = b;
					}
					else{
						fprintf(stderr,"%s\n","There is a Unsufficient Character in File.");
						exitGracefully();
					}
				}
			}
		}
		close(readA);
		close(readB);
		// File Read (finished)

		// Divede 4 part (inputA and inputB)
		int ** firstA = (int **)malloc((size/2) * sizeof(int *)); 
		int ** firstB = (int **)malloc((size/2) * sizeof(int *));
		int ** secondA = (int **)malloc((size/2) * sizeof(int *)); 
		int ** secondB = (int **)malloc((size/2) * sizeof(int *));
		int ** thirdA = (int **)malloc((size/2) * sizeof(int *)); 
		int ** thirdB = (int **)malloc((size/2) * sizeof(int *));
		int ** fourthA = (int **)malloc((size/2) * sizeof(int *)); 
		int ** fourthB = (int **)malloc((size/2) * sizeof(int *));
		
		for(int i=0; i<size; ++i){
			if(i < size/2){
				firstA[i] = (int *)malloc((size/2) * sizeof(int));
				firstB[i] = (int *)malloc((size/2) * sizeof(int));
				secondA[i] = (int *)malloc((size/2) * sizeof(int));
				secondB[i] = (int *)malloc((size/2) * sizeof(int));
			}
			else{
				thirdA[i-(size/2)] = (int *)malloc((size/2) * sizeof(int));
				thirdB[i-(size/2)] = (int *)malloc((size/2) * sizeof(int));
				fourthA[i-(size/2)] = (int *)malloc((size/2) * sizeof(int));
				fourthB[i-(size/2)] = (int *)malloc((size/2) * sizeof(int));
			}
			for(int j=0; j<size; ++j){
				if(i<size/2 && j<size/2){
					// First Area
					firstA[i][j] = inputA[i][j];
					firstB[i][j] = inputB[i][j];
				}
				else if(i<size/2 && j>=size/2){
					// Second Area
					secondA[i][j-(size/2)] = inputA[i][j];
					secondB[i][j-(size/2)] = inputB[i][j];
				}
				else if(i>=size/2 && j<size/2){
					// Third Area
					thirdA[i-(size/2)][j] = inputA[i][j];
					thirdB[i-(size/2)][j] = inputB[i][j];
				}
				else if(i>=size/2 && j>=size/2){
					// Fourth Area
					fourthA[i-(size/2)][j-(size/2)] = inputA[i][j];
					fourthB[i-(size/2)][j-(size/2)] = inputB[i][j];
				}
			}
		}
		free(inputA);
		free(inputB);
		// Now, the inputs parsed the quarters.

    	int p1s[2], p1t[2], p2s[2], p2t[2], p3s[2], p3t[2], p4s[2], p4t[2] ;

	    if(pipe(p1s) == -1 || pipe(p1t) == -1 || pipe(w1) == -1){
	    	perror("Child 1 Pipe Error");
	    }
	    if(pipe(p2s) == -1 || pipe(p2t) == -1 || pipe(w2) == -1){
	    	perror("Child 2 Pipe Error");
	    }
	    if(pipe(p3s) == -1 || pipe(p3t) == -1 || pipe(w3) == -1){
	    	perror("Child 3 Pipe Error");
	    }
	    if(pipe(p4s) == -1 || pipe(p4t) == -1 || pipe(w4) == -1){
	    	perror("Child 4 Pipe Error");
	    }

	    if(close(w1[1]) == -1 || close(w2[1]) == -1 || close(w3[1]) == -1 || close(w4[1]) == -1){
	    	perror("Parent Block Write Closing Error");
	    }
	    
	    for(int i=0; i<4 ;++i){
	    	pid_t child = fork();
	    	if(child == -1)
	    		perror("Fork Error");
	    	else if(child==0){
		    	if(i==0){
		    		// Child P2
			    	doChild(size, p1s, p1t, w1);
			        printf("Child P2 Done\n");
			        exit(0);
		    	}
		    	else if(i==1){
		    		// Child P3
			    	doChild(size, p2s, p2t, w2);
			        printf("Child P3 Done\n");
			    	exit(0);
		    	}
		    	else if(i==2){
		    		// Child P4
			    	doChild(size, p3s, p3t, w3);
			        printf("Child P4 Done\n");
			    	exit(0);
		    	}
		    	else if(i==3){
		    		// Child P5
			    	doChild(size, p4s, p4t, w4);
			        printf("Child P5 Done\n");
			    	exit(0);
		    	}
		    }
	    }

	    //printf("%d\n",getpid() );
	    //sleep(15); // you can use it in DEMO to show synchronization...

	    if(close(p1s[0]) == -1 || close(p2s[0]) == -1 || close(p3s[0]) == -1 || close(p4s[0]) == -1){
	    	perror("Parent Read Ends Closing Error");
	    }
	    if(close(p1t[1]) == -1 || close(p2t[1]) == -1 || close(p3t[1]) == -1 || close(p4t[1]) == -1){
	    	perror("Parent Write Ends Closing Error");
	    }
        // write to p_s[1] and read from p_t[0]

    	// 4 matrix are writing to pipe.
    	for(int i=0; i<4 ;++i){
	    	for(int k=0; k<size/2; ++k){
	        	if(i==0){
	        		write(p1s[1], firstA[k], (size/2) * sizeof(int));
	        		write(p2s[1], firstA[k], (size/2) * sizeof(int));
	        		write(p3s[1], thirdA[k], (size/2) * sizeof(int));
	        		write(p4s[1], thirdA[k], (size/2) * sizeof(int));
	        	}
	        	else if(i == 1){
	        		write(p1s[1], secondA[k], (size/2) * sizeof(int));
	        		write(p2s[1], secondA[k], (size/2) * sizeof(int));
	        		write(p3s[1], fourthA[k], (size/2) * sizeof(int));
	        		write(p4s[1], fourthA[k], (size/2) * sizeof(int));
	        	}
	        	else if(i==2){
	        		write(p1s[1], firstB[k], (size/2) * sizeof(int));
	        		write(p2s[1], secondB[k], (size/2) * sizeof(int));
	        		write(p3s[1], firstB[k], (size/2) * sizeof(int));
	        		write(p4s[1], secondB[k], (size/2) * sizeof(int));
	        	}
	        	else{
	        		write(p1s[1], thirdB[k], (size/2) * sizeof(int));
	        		write(p2s[1], fourthB[k], (size/2) * sizeof(int));
	        		write(p3s[1], thirdB[k], (size/2) * sizeof(int));
	        		write(p4s[1], fourthB[k], (size/2) * sizeof(int));
	        	}
	    	}
	    }	        
        close(p1s[1]); close(p2s[1]); close(p3s[1]); close(p4s[1]);
        free(firstA); free(secondA); free(thirdA); free(fourthA);
        free(firstB); free(secondB); free(thirdB); free(fourthB);
        // Matrix Writing End.


        int ** c1;
        int ** c2;
        int ** c3;
        int ** c4;
		c1 = (int **)malloc((size/2) * sizeof(int *));
		c2 = (int **)malloc((size/2) * sizeof(int *));
		c3 = (int **)malloc((size/2) * sizeof(int *));
		c4 = (int **)malloc((size/2) * sizeof(int *));
		for(int i=0;i<size/2;i++){    
    		c1[i] = (int *)malloc((size/2) * sizeof(int));
    		c2[i] = (int *)malloc((size/2) * sizeof(int));
    		c3[i] = (int *)malloc((size/2) * sizeof(int));
    		c4[i] = (int *)malloc((size/2) * sizeof(int));
    	}
    	// Result (coming from pipe) is collecting 
    	int buf1[size/2];
    	int buf2[size/2];
    	int buf3[size/2];
    	int buf4[size/2];
    	for(int k=0; k<size/2 ;++k){
        	read(p1t[0], buf1, sizeof(buf1));
        	read(p2t[0], buf2, sizeof(buf2));
        	read(p3t[0], buf3, sizeof(buf3));
        	read(p4t[0], buf4, sizeof(buf4));
			for(int i=0 ; i<size/2; ++i){
				c1[k][i] = buf1[i];
				c2[k][i] = buf2[i];
				c3[k][i] = buf3[i];
				c4[k][i] = buf4[i];
			}
		}	        
        close(p1t[0]); close(p2t[0]); close(p3t[0]); close(p4t[0]);
        // Result Collected

        // Sync. Wait... ( barrier )
        int dum;
        if(read(w1[0], &dum, 1) != 0)
        	perror("Parent didn't get EOF in P2");
		if(read(w2[0], &dum, 1) != 0)
        	perror("Parent didn't get EOF in P3");
        if(read(w3[0], &dum, 1) != 0)
        	perror("Parent didn't get EOF in P4");
		if(read(w4[0], &dum, 1) != 0)
        	perror("Parent didn't get EOF in P5");


        double res[size][size];

        for (int i = 0; i < size; ++i){
        	for (int j = 0; j < size; ++j){
        		if(i<size/2 && j<size/2){
        			res[i][j] = c1[i][j];
    			}
    			else if(i<size/2 && j>=size/2){
    				res[i][j] = c2[i][j-size/2];
    			}
    			else if(i>=size/2 && j<size/2){
    				res[i][j] = c3[i-size/2][j];
    			}
    			else if(i>=size/2 && j>=size/2){
    				res[i][j] = c4[i-size/2][j-size/2];
    			}
        	}
        }
        free(c1);free(c2);free(c3);free(c4);
        printf("%s\n", "RESULT MATRIX (returns from children) :" );
        for (int i = 0; i < size; ++i){
        	for(int j=0; j<size ;++j){
        		printf("%d ", (int)res[i][j] );
        	}
        	printf("\n");
        }

        double U[size][size];
		double V[size][size];
		double s[size];
		double * dummy;
		dummy = (double*) malloc(size * sizeof(double));   
		int err = Singular_Value_Decomposition((double*) res, size, size,(double*) U, s,(double*) V, dummy);
		free(dummy);                                                  
		if (err < 0) printf(" Failed to converge\n");                   
		else { 
			printf("\nSingular value decomposition of Result Matrix is :\n");		 
			for(int i=0; i<size; ++i){
				printf("%.3f ", s[i] );
			}
		}
		printf("\n");
	}
	return 0;
}

void doChild(int size, int * fs, int * ft, int ** block){
	close(block[0]); // syncr. pipe
	close(fs[1]); 
    close(ft[0]); 
    //  read from fs[0] and write to ft[1]
	int ** a1 = (int **)malloc((size/2) * sizeof(int *)); 
    int ** a2 = (int **)malloc((size/2) * sizeof(int *)); 
    int ** a3 = (int **)malloc((size/2) * sizeof(int *)); 
    int ** a4 = (int **)malloc((size/2) * sizeof(int *)); 
    
    for(int i=0; i<size/2 ;++i){
    	a1[i] = (int *)malloc((size/2) * sizeof(int));
    	a2[i] = (int *)malloc((size/2) * sizeof(int));
    	a3[i] = (int *)malloc((size/2) * sizeof(int));
    	a4[i] = (int *)malloc((size/2) * sizeof(int));
    }

    //printf("%d\n",getppid() );
    //sleep(8);  // you can use it in DEMO to show synchronization...

    // 4 matrix reading from pipe
    int buf[size/2];
    for(int j=0; j<4 ;++j){
        for(int k=0; k<size/2 ;++k){
        	read(fs[0], buf, sizeof(buf));
			for(int i=0 ; i<size/2; ++i){
				if(j==0)
					a1[k][i] = buf[i];
				else if(j==1)
					a2[k][i] = buf[i];
				else if(j==2)
					a3[k][i] = buf[i];
				else
					a4[k][i] = buf[i];
			}
		}
	}	        
	close(fs[0]);
	// 4 matrix readed from pipe and parsed

	int ** cal;
	cal = (int **)malloc((size/2) * sizeof(int *));
	for(int i=0;i<size/2;i++){    
		cal[i] = (int *)malloc((size/2) * sizeof(int));
	}
	calculateQuarter(a1,a2,a3,a4,cal,size/2);
	// operation has been calculated.
	free(a1); free(a2);	free(a3); free(a4);
	// Result is writing to pipe
	for(int k=0; k<size/2; ++k){
    		write(ft[1], cal[k], (size/2) * sizeof(int));
	}
    close(ft[1]);
    free(cal);
    // Result has been written to pipe.

    close(block[1]);
}

void signalHandler(int sig_num){
    signal(sig_num,SIG_DFL);
	raise(sig_num);
    switch(sig_num){
    	case SIGINT:  puts("catcher caught SIGINT");
    				  exitGracefully();
    				  break;
		case SIGCHLD: puts("catcher caught SIGCHLD");
					  signal(SIGCHLD, SIG_IGN);
					  /*for(int i=0; i<4 ;++i)
					  	wait(NULL);
					  exit(0);*/
					  break;
    }
}

void exitGracefully(void){
	printf("%s\n","Exiting Gracefully..." );
	exit(0);
	// exit is close all open files and free all allocated memory...
}

void calculateQuarter (int ** m1, int ** m2, int ** m3, int ** m4, int ** c, int size){
	int i,j,k;
    for(i=0;i<size;i++){    
    	for(j=0;j<size;j++){
	    	c[i][j]=0;    
	    	for(k=0;k<size;k++){   
	    		c[i][j]+=((m1[i][k]*m3[k][j])
	    				+(m1[i][k]*m4[k][j])
	    				+(m2[i][k]*m3[k][j])
	    				+(m2[i][k]*m4[k][j]));    
	    	}    
    	}   
    }  
}  

/*
BURADAN SONRASI SINGULAR VALUE DECOMPOSITION İÇİN GEREKLİ KODLARI İÇERİYOR
ÖDEVDE SÖYLENDİĞİ GİBİ İNTERNETTEN BULDUM. LİNKİ:
http://www.mymathlib.com/matrices/linearsystems/singular_value.html
*/
int Singular_Value_Decomposition(double* A, int nrows, int ncols, double* U, 
                      double* singular_values, double* V, double* dummy_array)
{
   Householders_Reduction_to_Bidiagonal_Form( A, nrows, ncols, U, V,
                                                singular_values, dummy_array);

   
   if (Givens_Reduction_to_Diagonal_Form( nrows, ncols, U, V,
                                singular_values, dummy_array ) < 0) return -1;

   Sort_by_Decreasing_Singular_Values(nrows, ncols, singular_values, U, V);
  
   return 0;
}

static void Householders_Reduction_to_Bidiagonal_Form(double* A, int nrows,
    int ncols, double* U, double* V, double* diagonal, double* superdiagonal )
{
   int i,j,k,ip1;
   double s, s2, si, scale;
   double dum;
   double *pu, *pui, *pv, *pvi;
   double half_norm_squared;

   memcpy(U,A, sizeof(double) * nrows * ncols);

   diagonal[0] = 0.0;
   s = 0.0;
   scale = 0.0;
   for ( i = 0, pui = U, ip1 = 1; i < ncols; pui += ncols, i++, ip1++ ) {
      superdiagonal[i] = scale * s;
      for (j = i, pu = pui, scale = 0.0; j < nrows; j++, pu += ncols)
         scale += fabs( *(pu + i) );
       
      if (scale > 0.0) {
         for (j = i, pu = pui, s2 = 0.0; j < nrows; j++, pu += ncols) {
            *(pu + i) /= scale;
            s2 += *(pu + i) * *(pu + i);
         }
         s = ( *(pui + i) < 0.0 ) ? sqrt(s2) : -sqrt(s2);
         half_norm_squared = *(pui + i) * s - s2;
         *(pui + i) -= s;
         
         for (j = ip1; j < ncols; j++) {
            for (k = i, si = 0.0, pu = pui; k < nrows; k++, pu += ncols)
               si += *(pu + i) * *(pu + j);
            si /= half_norm_squared;
            for (k = i, pu = pui; k < nrows; k++, pu += ncols) {
               *(pu + j) += si * *(pu + i);
            }
         }
      }
      for (j = i, pu = pui; j < nrows; j++, pu += ncols) *(pu + i) *= scale;
      diagonal[i] = s * scale;
      s = 0.0;
      scale = 0.0;
      if (i >= nrows || i == (ncols - 1) ) continue;
      for (j = ip1; j < ncols; j++) scale += fabs ( *(pui + j) );
      if ( scale > 0.0 ) {
         for (j = ip1, s2 = 0.0; j < ncols; j++) {
            *(pui + j) /= scale;
            s2 += *(pui + j) * *(pui + j);
         }
         s = ( *(pui + ip1) < 0.0 ) ? sqrt(s2) : -sqrt(s2);
         half_norm_squared = *(pui + ip1) * s - s2;
         *(pui + ip1) -= s;
         for (k = ip1; k < ncols; k++)
            superdiagonal[k] = *(pui + k) / half_norm_squared;
         if ( i < (nrows - 1) ) {
            for (j = ip1, pu = pui + ncols; j < nrows; j++, pu += ncols) {
               for (k = ip1, si = 0.0; k < ncols; k++) 
                  si += *(pui + k) * *(pu + k);
               for (k = ip1; k < ncols; k++) { 
                  *(pu + k) += si * superdiagonal[k];
               }
            }
         }
         for (k = ip1; k < ncols; k++) *(pui + k) *= scale;
      }
   }

   pui = U + ncols * (ncols - 2);
   pvi = V + ncols * (ncols - 1);
   *(pvi + ncols - 1) = 1.0;
   s = superdiagonal[ncols - 1];
   pvi -= ncols;
   for (i = ncols - 2, ip1 = ncols - 1; i >= 0; i--, pui -= ncols,
                                                      pvi -= ncols, ip1-- ) {
      if ( s != 0.0 ) {
         pv = pvi + ncols;
         for (j = ip1; j < ncols; j++, pv += ncols)
            *(pv + i) = ( *(pui + j) / *(pui + ip1) ) / s;
         for (j = ip1; j < ncols; j++) { 
            si = 0.0;
            for (k = ip1, pv = pvi + ncols; k < ncols; k++, pv += ncols)
               si += *(pui + k) * *(pv + j);
            for (k = ip1, pv = pvi + ncols; k < ncols; k++, pv += ncols)
               *(pv + j) += si * *(pv + i);                  
         }
      }
      pv = pvi + ncols;
      for ( j = ip1; j < ncols; j++, pv += ncols ) {
         *(pvi + j) = 0.0;
         *(pv + i) = 0.0;
      }
      *(pvi + i) = 1.0;
      s = superdiagonal[i];
   }

   pui = U + ncols * (ncols - 1);
   for (i = ncols - 1, ip1 = ncols; i >= 0; ip1 = i, i--, pui -= ncols ) {
      s = diagonal[i];
      for ( j = ip1; j < ncols; j++) *(pui + j) = 0.0;
      if ( s != 0.0 ) {
         for (j = ip1; j < ncols; j++) { 
            si = 0.0;
            pu = pui + ncols;
            for (k = ip1; k < nrows; k++, pu += ncols)
               si += *(pu + i) * *(pu + j);
            si = (si / *(pui + i) ) / s;
            for (k = i, pu = pui; k < nrows; k++, pu += ncols)
               *(pu + j) += si * *(pu + i);                  
         }
         for (j = i, pu = pui; j < nrows; j++, pu += ncols){
            *(pu + i) /= s;
         }
      }
      else 
         for (j = i, pu = pui; j < nrows; j++, pu += ncols) *(pu + i) = 0.0;
      *(pui + i) += 1.0;
   }
}

static int Givens_Reduction_to_Diagonal_Form( int nrows, int ncols,
           double* U, double* V, double* diagonal, double* superdiagonal )
{

   double epsilon;
   double c, s;
   double f,g,h;
   double x,y,z;
   double *pu, *pv;
   int i,j,k,m;
   int rotation_test;
   int iteration_count;
  
   for (i = 0, x = 0.0; i < ncols; i++) {
      y = fabs(diagonal[i]) + fabs(superdiagonal[i]);
      if ( x < y ) x = y;
   }
   epsilon = x * DBL_EPSILON;
   for (k = ncols - 1; k >= 0; k--) {
      iteration_count = 0;
      while(1) {
         rotation_test = 1;
         for (m = k; m >= 0; m--) { 
            if (fabs(superdiagonal[m]) <= epsilon) {rotation_test = 0; break;}
            if (fabs(diagonal[m-1]) <= epsilon) break;
         }
         if (rotation_test) {
            c = 0.0;
            s = 1.0;
            for (i = m; i <= k; i++) {  
               f = s * superdiagonal[i];
               superdiagonal[i] *= c;
               if (fabs(f) <= epsilon) break;
               g = diagonal[i];
               h = sqrt(f*f + g*g);
               diagonal[i] = h;
               c = g / h;
               s = -f / h; 
               for (j = 0, pu = U; j < nrows; j++, pu += ncols) { 
                  y = *(pu + m - 1);
                  z = *(pu + i);
                  *(pu + m - 1 ) = y * c + z * s;
                  *(pu + i) = -y * s + z * c;
               }
            }
         }
         z = diagonal[k];
         if (m == k ) {
            if ( z < 0.0 ) {
               diagonal[k] = -z;
               for ( j = 0, pv = V; j < ncols; j++, pv += ncols) 
                  *(pv + k) = - *(pv + k);
            }
            break;
         }
         else {
            if ( iteration_count >= 30 ) return -1;
            iteration_count++;
            x = diagonal[m];
            y = diagonal[k-1];
            g = superdiagonal[k-1];
            h = superdiagonal[k];
            f = ( (y - z) * ( y + z ) + (g - h) * (g + h) )/(2.0 * h * y);
            g = sqrt( f * f + 1.0 );
            if ( f < 0.0 ) g = -g;
            f = ( (x - z) * (x + z) + h * (y / (f + g) - h) ) / x;
// Next QR Transformtion
            c = 1.0;
            s = 1.0;
            for (i = m + 1; i <= k; i++) {
               g = superdiagonal[i];
               y = diagonal[i];
               h = s * g;
               g *= c;
               z = sqrt( f * f + h * h );
               superdiagonal[i-1] = z;
               c = f / z;
               s = h / z;
               f =  x * c + g * s;
               g = -x * s + g * c;
               h = y * s;
               y *= c;
               for (j = 0, pv = V; j < ncols; j++, pv += ncols) {
                  x = *(pv + i - 1);
                  z = *(pv + i);
                  *(pv + i - 1) = x * c + z * s;
                  *(pv + i) = -x * s + z * c;
               }
               z = sqrt( f * f + h * h );
               diagonal[i - 1] = z;
               if (z != 0.0) {
                  c = f / z;
                  s = h / z;
               } 
               f = c * g + s * y;
               x = -s * g + c * y;
               for (j = 0, pu = U; j < nrows; j++, pu += ncols) {
                  y = *(pu + i - 1);
                  z = *(pu + i);
                  *(pu + i - 1) = c * y + s * z;
                  *(pu + i) = -s * y + c * z;
               }
            }
            superdiagonal[m] = 0.0;
            superdiagonal[k] = f;
            diagonal[k] = x;
         }
      } 
   }
   return 0;
}

static void Sort_by_Decreasing_Singular_Values(int nrows, int ncols,
                                double* singular_values, double* U, double* V)
{
   int i,j,max_index;
   double temp;
   double *p1, *p2;

   for (i = 0; i < ncols - 1; i++) {
      max_index = i;
      for (j = i + 1; j < ncols; j++)
         if (singular_values[j] > singular_values[max_index] ) 
            max_index = j;
      if (max_index == i) continue;
      temp = singular_values[i];
      singular_values[i] = singular_values[max_index];
      singular_values[max_index] = temp;
      p1 = U + max_index;
      p2 = U + i;
      for (j = 0; j < nrows; j++, p1 += ncols, p2 += ncols) {
         temp = *p1;
         *p1 = *p2;
         *p2 = temp;
      } 
      p1 = V + max_index;
      p2 = V + i;
      for (j = 0; j < ncols; j++, p1 += ncols, p2 += ncols) {
         temp = *p1;
         *p1 = *p2;
         *p2 = temp;
      }
   } 
}