#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code.

  Compile with:
    cc -o CrackAZ99-With-Data CrackAZ99-With-Data.c -lcrypt -pthread

  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:

    ./CrackAZ99-With-Data > results.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/
int n_passwords = 4;


void multiCore () {
pthread_t t1, t2;

void *kernel_function_1();
void *kernel_function_2();

pthread_create (&t1, NULL, kernel_function_1, NULL);
pthread_create (&t2, NULL, kernel_function_2, NULL);

pthread_join(t1, NULL);
pthread_join(t2, NULL);



}

void substr(char *dest, char *src, int start, int length) {
memcpy(dest, src + start, length);
*(dest + length) = '\0';
}


/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the
 start of the line. Note that one of the most time consuming operations that
 it performs is the output of intermediate results, so performance experiments
 for this kind of program should not include this. i.e. comment out the printfs.
*/

void *kernel_function_1(){
  int x, y, z, s;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

char *encrypted_passwords[] = {
  "$6$KB$yPvAP5BWyF7oqOITVloN9mCAVdel.65miUZrEel72LcJy2KQDuYE6xccHS2ycoxqXDzW.lvbtDU5HuZ733K0X0",
  "$6$KB$4dWyDaT7p8xMWfb6.1R4Q7hQMyezwOgLfAcZhdE4QkH3bylH4EmM.gOVhU7m7K9FHfL.kKhzK6bfHqfA.NDb/0",
  "$6$KB$xELPxo7gwBciT/5FN/.kBwgSPG5RZ8TiW8N0hEER1gyYrQ9ErvSfTbGuDl4w9/QyIP5Lu6W25.G.C8jk6VTYL0",
  "$6$KB$YsfzwjTmZTAEUfD/L/uEqVAmfKGAWSa0ZWg8tSPGT4DZnQNBzLT4vXg2nl7Yd2KZrs4dykykxVIZZLob5ijUb/"

/**
 Required by lack of standard function in C.  
*/
};

  substr(salt, encrypted_passwords[0], 0, 6);
	for(int i = 0; i<n_passwords;i++){
		for(x='A'; x<='M'; x++){
			for(y='A'; y<='Z'; y++){
				for(s='A'; s<='Z'; s++){
			  		for(z=0; z<=99; z++){
						sprintf(plain, "%c%c%c%02d", x, y, s, z);
						enc = (char *) crypt(plain, salt);
						count++;
						if(strcmp(encrypted_passwords[i], enc) == 0){
				  			printf("#%-8d%s %s\n", count, plain, enc);
						} else {
				  			//printf(" %-8d%s %s\n", count, plain, enc);
						}
			  		}
				}
		  	}	
		}
	}
	
  //printf("%d solutions explored\n", count);
}

void *kernel_function_2(){
  int x, y, z, s;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

char *encrypted_passwords[] = {
  "$6$KB$yPvAP5BWyF7oqOITVloN9mCAVdel.65miUZrEel72LcJy2KQDuYE6xccHS2ycoxqXDzW.lvbtDU5HuZ733K0X0",
  "$6$KB$4dWyDaT7p8xMWfb6.1R4Q7hQMyezwOgLfAcZhdE4QkH3bylH4EmM.gOVhU7m7K9FHfL.kKhzK6bfHqfA.NDb/0",
  "$6$KB$xELPxo7gwBciT/5FN/.kBwgSPG5RZ8TiW8N0hEER1gyYrQ9ErvSfTbGuDl4w9/QyIP5Lu6W25.G.C8jk6VTYL0",
  "$6$KB$YsfzwjTmZTAEUfD/L/uEqVAmfKGAWSa0ZWg8tSPGT4DZnQNBzLT4vXg2nl7Yd2KZrs4dykykxVIZZLob5ijUb/"

/**
 Required by lack of standard function in C.  
*/
};

  substr(salt, encrypted_passwords[0], 0, 6);

	for(int i = 0; i<n_passwords;i++){
		for(x='N'; x<='Z'; x++){
			for(y='A'; y<='Z'; y++){
				for(s='A'; s<='Z'; s++){
				  	for(z=0; z<=99; z++){
					    sprintf(plain, "%c%c%c%02d", x, y, s, z);
			    		enc = (char *) crypt(plain, salt);
			    		count++;
			    		if(strcmp(encrypted_passwords[i], enc) == 0){
			     			//printf("#%-8d%s %s\n", count, plain, enc);
			    		} else {
			      			//printf(" %-8d%s %s\n", count, plain, enc);
			    		}
			  		}
				}
	  		}
		}
	}
  //printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main(int argc, char *argv[]){
	struct timespec start, finish;   
  long long int time_elapsed;

  	clock_gettime(CLOCK_MONOTONIC, &start);

  int i;

 
  
    multiCore();
  

	clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 

  return 0;
}


