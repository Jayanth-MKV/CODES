#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
int buffer[5];
int size=-1;

void *produce(void *arg){
    int count = 0;
    while(count<3){
    int i = (int)arg;
    sem_wait(&mutex);
    if(size!=4){
        buffer[++size] = rand()%10;
        printf("Producer %d produced %d\n", i, buffer[size]);
        count++;
    }
    else{
        printf("Buffer is full\n");
    }
    sem_post(&mutex);
    }
}

void *consume(void *arg){
    int count = 0;
    while(count<3){
    int i = (int)arg;
    sem_wait(&mutex);
    if(size!=-1){
        printf("Consumer %d consumed %d\n", i, buffer[size--]);
        count++;
    }
    else{
        printf("Buffer is empty\n");
    }
    sem_post(&mutex);
    }
}

void main(){
    
    pthread_t producer[3] ,consumer[3];
    int i;
    sem_init(&mutex, 0, 1);
    printf("Starting\n");
    for(i=0; i<3; i++){
        pthread_create(&producer[i], NULL, produce, (void*)i);
        printf("1");
        pthread_create(&consumer[i], NULL, consume, (void*)i);
        printf("2");
    }
    for(i=0; i<3; i++){
        pthread_join(producer[i], NULL);
        pthread_join(consumer[i], NULL);
    }
}
