//Testing...
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMTASKS 25000
#define NANOSECONDS_PER_SECOND 1E9
#define FIBNUM 26

int fib(int x) {
  if (x == 0) 
    return 0;
  else if (x == 1) 
    return 1;
  return fib(x - 1) + fib(x - 2);
}

void * workerthread(void * tid){
  fib(FIBNUM);
  return NULL;
}

int main(){
  pthread_t thr[NUMTASKS];
  struct timespec before, after;
  
  printf("running fib(%d) %d times\n",FIBNUM,NUMTASKS);
  clock_gettime(CLOCK_REALTIME, &before);
  for (int i = 0; i < NUMTASKS; i++) {
    int rcode;
    if ((rcode = pthread_create(&thr[i], NULL, workerthread, NULL))) {
      fprintf(stderr, "Error in pthread_create: %d\n", rcode);
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < NUMTASKS; i++) {
    pthread_join(thr[i], NULL);
  }
  clock_gettime(CLOCK_REALTIME, &after);
  return 0;
}
