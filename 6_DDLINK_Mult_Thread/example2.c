#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t counter_lock;
pthread_cond_t counter_nonzero;
int counter = 0;
int estatus = -1;

void *decrement_counter(void *argv);
void *increment_counter(void *argv);

int main(int argc, char **argv)
{
    printf("counter: %d\n", counter);
    pthread_t thd1, thd2;
    int ret;

    ret = pthread_create(&thd1, NULL, decrement_counter, NULL);
    if(ret){
        perror("del:\n");
        return 1;
    }

    ret = pthread_create(&thd2, NULL, increment_counter, NULL);
    if(ret){
        perror("inc: \n");
        return 1;
    }

    int counter = 0;
    while(counter != 10){
        printf("counter(main): %d\n", counter);
        sleep(1);
        counter++;
    }

    return 0;
}

void *decrement_counter(void *argv)
{
    printf("counter(decrement): %d\n", counter);
    pthread_mutex_lock(&counter_lock);
    while(counter == 0)
        pthread_cond_wait(&counter_nonzero, &counter_lock); //½øÈ(wait)£¬µȴýsignal)
    
    printf("counter--(before): %d\n", counter);    
    counter--; //µȴýl¼¤»îÔִÐ
    printf("counter--(after): %d\n", counter);    
    pthread_mutex_unlock(&counter_lock); 

    return &estatus;
}

void *increment_counter(void *argv)
{
    printf("counter(increment): %d\n", counter);
    pthread_mutex_lock(&counter_lock);
    if(counter == 0)
        pthread_cond_signal(&counter_nonzero); //¼¤»îignal)×È(wait)µÄ߳ÌÏִÐÍsignalÏ³̣¬Ȼºó´ÐwaitÏ³Ì

    printf("counter++(before): %d\n", counter);    
    counter++; 
    printf("counter++(after): %d\n", counter);    
    pthread_mutex_unlock(&counter_lock);

    return &estatus;
}

