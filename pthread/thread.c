#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THREAD_NUM 10
void *test(void *args) {
	while(1)
	{
 printf("tid %d: i say 'Hello'.\n", args);
	sleep(1);
	}
 return NULL;
}
int main() {
 int i, err;
 pthread_t child[THREAD_NUM];
 for(i = 0; i < THREAD_NUM; i++) {
  printf("Creating thread %d\n", i);
  err = pthread_create(&child[i], NULL, test, (void *) i);
  if(err) {
   printf("Can't create thread %d\n", i);
   exit(0);
  }
 }
 for(i = 0; i < THREAD_NUM; i++)
 pthread_join(child[i], NULL);
 printf("Thread initialize\n");
 return 0;
}
