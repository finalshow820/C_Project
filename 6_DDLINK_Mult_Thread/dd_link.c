#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>


#define CreateNode(t,p) p = (t*)malloc(sizeof(t))
#define FreeNode(p) free((void *)p)


int num[10] = {0,1,2,3,4,5,6,7,8,9};
int global_count = 0;
int gddlink_update = 0;
int estatus = -1;
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


//Define Print Function Pointer
typedef void (*DDLinkPrintPointer)(void* data);
typedef void (*DDLinkVisitPointer)(void* ctx, void* data);


typedef struct dd_link_node
{
	void *data;
	struct dd_link_node *pPre,*pNext;
}dd_link_node;

typedef struct dd_link
{
	struct dd_link_node* pHead;
}dd_link;

dd_link L;


//Init dd_link
void InitDDLink(dd_link *L)
{
	if(NULL == L)
	{
		printf("NULL Double Link;\n");
		return;
	}

	L->pHead = NULL;
}


//Insert dd_link
void InsertDDLink(dd_link *L,void *nData)
{
	dd_link_node *p = NULL;
	if(NULL == L)
	{
		printf("NULL Double Link;\n");
		return;
	}

	CreateNode(dd_link_node,p);
	p->data = nData;
	p->pNext = L->pHead;

	if(NULL != L->pHead)
	{
		L->pHead->pPre = p;
	}

	p->pPre = NULL;
	L->pHead = p;
	return;
}


//Visit DD_link
void DDLinkForeach(dd_link *L, DDLinkVisitPointer visit,void *ctx)
{
	//printf("\nAttention!Print the DDLINK now!\n");
	dd_link_node *p = NULL;
	if(NULL == L->pHead)
	{
		printf("NULL Double Link;\n");
		return;
	}

	p = L->pHead;
	while(p)
	{
		visit(ctx,p->data);
		p = p->pNext;
	}
	return;
}

//DDLink Get Sum
void DDLinkGetSum(void *ctx, void *data)
{
	int *result = ctx;
	*result += *(int *)data;
}

//DDLink ForeachPrint
void DDLinkForeachPrint(void *ctx, void *data)
{
	((DDLinkPrintPointer)ctx)(data);
}

//DDLink Get Max
void DDLinkGetMax(void *ctx, void *data)
{
	int *result = ctx;
	*result = (*result) > (*(int *)data) ? (*result) : (*(int *)data);
}


//DDLinkVisitorPointer: Lower2Upper
void DDLinkVisitor_Lower2Upper(void *ctx, void *data)
{
	char *p = NULL;
	p = (char*)data;
	while(*p)
	{
		if(islower(*p))
		{
			*p = toupper(*p);
		}
		p++;
	}
}



//Print dd_link
void PrintDDLink(dd_link *L, DDLinkPrintPointer print)
{
	printf("\nAttention!Print the DDLINK now!\n");
	dd_link_node *p = NULL;
	if(NULL == L->pHead)
	{
		printf("NULL Double Link;\n");
		return;
	}

	p = L->pHead;
	while(p)
	{
		print(p->data);
		p = p->pNext;
	}
	return;
}

//Print Char
void print_char(void *data)
{
	printf("%c\n",*(char *)(data));
}


//Print Int
void print_int(void *data)
{
	printf("%d\n",*(int *)(data));
}


//Print String
void print_str(void *data)
{
	printf("%s\n",(char *)(data));
}



//Deatory dd_link
void DestoryDDLink(dd_link *L)
{
	dd_link_node *p = NULL;
	dd_link_node *tmp = NULL;
	if(NULL == L->pHead)
	{
		printf("NULL DDLINK, Failed!\n");
		return;
	}

	p = L->pHead;
	while(p)
	{
		tmp = p->pNext;
		FreeNode(p);
		p = tmp;
	}

	L->pHead = NULL;
	printf("Destory DDLink Successed!\n");
	return;
}


//Seach DDLink
dd_link_node* SearchDDLink(dd_link *L,int nData)
{
	dd_link_node *p;
	if(NULL == L->pHead)
	{
		printf("NULL DDLINK, Failed!\n");
		return;
	}

	p = L->pHead;

	while(p)
	{
		if(*(int *)(p->data) == nData)
		{
			printf("Search %d successed!\n",nData);
			return p;
		}
		p = p->pNext;
	}

	printf("Search %d failed!\n",nData);
	return NULL;
}



//DeleteNode By Data
void DeleteNodeByData(dd_link *L,int nData)
{
	dd_link_node *p;
	if(NULL == L->pHead)
	{
		printf("NULL DDLINK, Failed!\n");
		return;
	}

	if(NULL == (p=SearchDDLink(L,nData)))
	{
		printf("There are no this element.\n");
		return;
	}

	if(p == L->pHead)
	{
		DeleteHeadDDLink(L);
		printf("Delete First Element Successed!\n");
	}
	else if(NULL == p->pNext)
	{
		p->pPre->pNext = NULL;
		FreeNode(p);
		printf("Delete Last Element Successed!\n");
	}
	else
	{
		p->pPre->pNext = p->pNext;
		p->pNext->pPre = p->pPre;
		FreeNode(p);
		printf("Delete %d Successed!\n",nData);
	}

	return;
}


//DeleteHeadDDLink
void DeleteHeadDDLink(dd_link *L)
{
	dd_link_node *p=NULL;
	p = L->pHead;

	if(NULL == p->pNext)
	{
		L->pHead = NULL;
		FreeNode(p);
		return;
	}
	else
	{
		L->pHead = p->pNext;
		L->pHead->pPre = NULL;
		FreeNode(p);
		return;
	}
}

//MultThread Insert
void* thread_insert(void *arg)
{
	printf("thread_insert....\n");
	printf("thread_insert pid is %lu\n",(unsigned long)pthread_self());

	pthread_mutex_lock(&mylock);
	if(0 == gddlink_update)
	{
		pthread_cond_signal(&cond);
	}
	gddlink_update=1;
	InsertDDLink(&L,&num[global_count%10]);
	printf("Insert element %d\n",num[global_count%10]);
	pthread_mutex_unlock(&mylock);


	//return &estatus;
	pthread_exit(NULL);
}


//MultThread Display
void* thread_display(void *arg)
{
	printf("thread_dispaly....\n");
	printf("thread_dispaly pid is %lu\n",(unsigned long)pthread_self());
	pthread_mutex_lock(&mylock);
	while(0 == gddlink_update)
	{
		pthread_cond_wait(&cond, &mylock);
	}

	gddlink_update=0;
	//printf("Disply DDLink,Global is %d\n",global_count);
	DDLinkForeach(&L, DDLinkForeachPrint,print_int);
	pthread_mutex_unlock(&mylock);
	printf("\n");
	//return &estatus;
	pthread_exit(NULL);
}


void main()
{
	pthread_t tid1,tid2;
	int err;
	void *tret;

	memset(&L,0,sizeof(dd_link));

	
	InitDDLink(&L);

	printf("***********************Beginning!!!*************************\n");


	while(global_count<5)
	{
		gddlink_update = 0;
		printf("global_count is %d, gddlink_update is %d\n",global_count,gddlink_update);
		global_count++;
		
		err = pthread_create(&tid2, NULL, thread_display, NULL);
		if( 0 != err)
		{
			printf("*****error2*****\n");
		}


		err = pthread_create(&tid1, NULL, thread_insert, NULL);
		if( 0 != err)
		{
			printf("*****error1*****\n");
		}

		sleep(1);
		
	}
	

	printf("***************Final DDLink showing***********************\n");
	DDLinkForeach(&L, DDLinkForeachPrint,print_int);	
	printf("**********ЫЌНу*************\n");

	//DestoryDDLink(&L);
	return;
}




