#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
int g=0;
pthread_mutex_t mutex;
void* my_thread(void *x){
int k=(int)(x);
pthread_mutex_lock(&mutex);
printf("%d ->",(int)k);
g++;
//(*k)++;
printf("%d ,",g);
pthread_mutex_unlock(&mutex);
return NULL;
}

int main(){
int i=0;
int parameter=100;
pthread_t thread[10];
pthread_mutex_t mutex;
pthread_mutex_init(&mutex,NULL);
for(i=0;i<10;i++){
pthread_create(&thread[i],NULL,my_thread,(void *)(parameter));
parameter=parameter+1;
//printf("%d\n",parameter);
}
for(i=0;i<10;i++){
pthread_join(thread[i],NULL);
}
return(1);}
