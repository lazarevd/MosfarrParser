#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_OF_TASKS 10

void * funcA(void * arg);
void * funcB(void * arg);

int main(void) {

while(1==1) {
sleep(5);
pthread_t thread;
pthread_create(&thread, NULL, &funcA, NULL);
}

printf("%s\n","done");
return 0;
}

void * funcA(void * arg){
int arr[3] ;
printf("%d\n", arr[64]);
}
void * funcB(void * arg) {
printf("%s\n", "B");
}
