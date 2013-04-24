/**************************************************
*****************Mult Thread Example******************
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define DEBUG 1

int num=0;
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;

void* thread_func(void *arg)
{
	int i = (int)arg;
	int ret;
	sleep(5-i);
	pthread_mutex_lock(&mylock);

	while(i != num)
	{
		printf("thread %d warting\n",i);

		ret = pthread_cond_wait(&qready, &mylock);
		if(0 == ret)
		{
			printf("thread %d wait success\n",i);
		}
		else
		{
			printf("thread %d wait fail\n",i);
		}
	}

	printf("thread %d is running\n",i);
	num++;

	pthread_mutex_unlock(&mylock);
	pthread_cond_broadcast(&qready);

	return (void *)0;
}
int main(int argc, char** argv)
{
	int i=0,err;
	pthread_t tid[4];

	void *tret;

	for(i=0;i<4;i++)
	{
		err = pthread_create(&tid[i], NULL, thread_func, (void *)i);

		if(0 != err)
		{
			printf("pthread_create error:%s\n",strerror(err));
			exit(-1);
		}
	}

	for(i=0;i<4;i++)
	{
		err = pthread_join(tid[i], &tret);

		if(0 != err)
		{
			printf("can not join with thread :%d\n",i,strerror(err));
			exit(-1);
		}
	}
	
	return 0;
}
