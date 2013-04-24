/**************************************************
*****************Mult Thread Example******************
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM 6

int g_Flag=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread_function(void *arg)
{
	int mynum = (int)arg;
	int randnum;

	printf("thread_func is runnning, Argument was %d\n",mynum);

	randnum = 1+(int)(9.0 * rand()/(RAND_MAX+1.0));
	sleep(randnum);
	printf("Bye from %d, Randnum is %d\n",mynum, randnum);
	pthread_exit("****shuangjie*****");
	
}
int main(int argc, char** argv)
{
	pthread_t a_thread[NUM];
	void *thread_result;
	int index = 0;
	int err;
	
	for(;index < NUM;++index)
	{
		err = pthread_create(&a_thread[index], NULL, thread_function, (void *)index);
		sleep(1);
	}

	printf("Waitting for threads to finished...\n");

	for(index = NUM-1;index >= 0; --index)
	{
		err = pthread_join(a_thread[index], &thread_result);

		if(0 == err)
		{
			printf("Pikc up a thread:%d___%s\n",index+1,thread_result);
		}

	}
	
	printf("All done!\n");	
	return 0;
}
