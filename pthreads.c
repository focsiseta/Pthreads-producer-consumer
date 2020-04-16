#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define IS_FULL 1
#define IS_EMPTY 0
#define check_number(function,message) if(function != 0){perror(#message);exit(1);}


pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_buffer = PTHREAD_COND_INITIALIZER;
int buffer[1] = {0};
int state = 0;
int counter = 100;
void *producer(void *);
void *consumer(void *);




int main(int argc, char const *argv[])
{
    pthread_t tid,tidd;
    pthread_create(&tid,NULL,producer,NULL);
    pthread_create(&tidd,NULL,consumer,NULL);
    pthread_join(tid,NULL);
    pthread_join(tidd,NULL);

    
    return 0;
}


void * producer(void *arg){

    check_number(pthread_mutex_lock(&buffer_lock),Cant get mutex)
    while (counter){

        int rng = rand() % 100;
        buffer[0] = rng;
        state = IS_FULL;
        while(state){
            pthread_cond_wait(&condition_buffer,&buffer_lock);
        }
        pthread_cond_signal(&condition_buffer);
        
        counter--;

    }
    //pthread_cond_signal(&condition_buffer);
    pthread_mutex_unlock(&buffer_lock);
    pthread_exit(NULL);
}

void * consumer(void *arg){
    check_number(pthread_mutex_lock(&buffer_lock),cant get lock)
    while (counter){
        if(state){
            sleep(1);
            printf("Generated number %d\n",buffer[0]);
            state = IS_EMPTY;
            pthread_cond_signal(&condition_buffer);
        }else{
            pthread_cond_wait(&condition_buffer,&buffer_lock);
        }
    }
    //pthread_cond_signal(&condition_buffer);
    pthread_mutex_unlock(&buffer_lock);
    pthread_exit(NULL);
}
