/**************************************************
*****************Mult Thread Example******************
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define DEBUG 1

int g_Flag=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread1(void *arg)
{
	int err = 0;
	printf("Enter thread 1\n");
	printf("This is thread 1, g_Flag:%d, thread id is %u\n",g_Flag,(unsigned int)pthread_self());
	pthread_mutex_lock(&mutex);

	if(2 == g_Flag)
	{
		pthread_cond_signal(&cond);
	}

	g_Flag = 1;
	
	printf("This is thread 1, g_Flag:%d, thread id is %u\n",g_Flag,(unsigned int)pthread_self());
	pthread_mutex_unlock(&mutex);
	err = pthread_join(*(pthread_t*)arg, NULL);
	if(0 != err)
	{
		printf("***********Join error**********\n");
	}else
	{
		printf("********Join_Success********\n");
	}
	printf("Leave thread 1\n");
	pthread_exit(0);
}

void* thread2(void *arg)
{
	printf("Enter thread 2\n");
	printf("This is thread 2, g_Flag:%d, thread id is %u\n",g_Flag,(unsigned int)pthread_self());
	pthread_mutex_lock(&mutex);

	if(1 == g_Flag)
	{
		pthread_cond_signal(&cond);
	}

	g_Flag = 2;
	
	printf("This is thread 2, g_Flag:%d, thread id is %u\n",g_Flag,(unsigned int)pthread_self());
	pthread_mutex_unlock(&mutex);
	printf("Leave thread 2\n");
	pthread_exit(0);
}


int main(int argc, char** argv)
{
	printf("Enter main\n");
	pthread_t tid1,tid2;
	int err=0;

	err = pthread_create(&tid2, NULL, thread2, NULL);
	if(0 != err)
	{
		printf("Thread 2 create failed\n");
	}
	
	err = pthread_create(&tid1, NULL, thread1, &tid2);
	if(0 != err)
	{
		printf("Thread 1 create failed\n");
	}

	pthread_cond_wait(&cond,&mutex);
	printf("Leaving main\n");

	return 0;
}
