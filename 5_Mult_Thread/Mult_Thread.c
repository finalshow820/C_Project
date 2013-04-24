/**************************************************
*****************Mult Thread Example******************
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


int num=0;
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
//Add 500 times
void *add(void *arg)
{
	int i = 0,tmp = 0;
	for(i=0;i<500;i++)
	{
		pthread_mutex_lock(&mylock);
		tmp = num+1;
		num = tmp;
		printf("add+1,result is :%d\n",num);
		pthread_mutex_unlock(&mylock);
	}
	return ((void *)0);
}



//Add 500 times
void *sub(void *arg)
{
	int i = 0,tmp = 0;
	for(i=0;i<500;i++)
	{
		pthread_mutex_lock(&mylock);
		tmp = num-1;
		num = tmp;
		printf("sub-1,result is :%d\n",num);
		pthread_mutex_unlock(&mylock);
	}
	return ((void *)0);
}

int main(int argc, char** argv)
{
	pthread_t tid1,tid2;
	int err;
	void *tret;

	//pthread_create tid1
	err = pthread_create(&tid1, NULL, add ,NULL);
	if(0 != err)
	{
		printf("pthread_create error:%s\n",strerror(err));
		exit(-1);
	}

	//pthread_create tid2
	err = pthread_create(&tid2, NULL, sub ,NULL);
	if(0 != err)
	{
		printf("pthread_create error:%s\n",strerror(err));
		exit(-1);
	}

	//pthread_join tid1
	err = pthread_join(tid1,&tret);
	if(0 != err)
	{
		printf("pthread_create error:%s\n",strerror(err));
		exit(-1);
	}

	//pthread_join tid2
	err = pthread_join(tid2,&tret);
	if(0 != err)
	{
		printf("pthread_create error:%s\n",strerror(err));
		exit(-1);
	}

	printf("thread 2 exit code %d\n",(int)tret);
	return 0;
}
