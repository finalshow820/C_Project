#include <stdio.h>
#include <stdlib.h>

#define CreateNode(t,p) p = (t*)malloc(sizeof(t))
#define FreeNode(p) free((void *)p)

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


typedef struct _queue
{
	dd_link* Dlist;

}queue;

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

dd_link* DDlink_init()
{
	dd_link *thiz = (dd_link *)malloc(sizeof(dd_link));
	return thiz;
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


void DDLink_append(dd_link *L,void *nData)
{
	dd_link_node *p = NULL;
	dd_link_node *q = NULL;
	if(NULL == L)
	{
		printf("NULL Double Link;\n");
		return;
	}

	CreateNode(dd_link_node,p);
	p->data = nData;

	if(NULL == L->pHead)
	{
		p->pNext = NULL;
		p->pPre = NULL;
		L->pHead = p;
		
	}
	else
	{
		q = L->pHead;
		while(q->pNext)
		{
			q = q->pNext;
		}

		q->pNext = p;
		p->pPre = q;
		p->pNext = NULL;
	}
	
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

//DDLink Get Elements
int DDLinkGetLength(dd_link *L)
{
	dd_link_node *p = NULL;
	int count = 0;
	if(NULL == L->pHead)
	{
		printf("NULL Double Link;\n");
		return 0;
	}

	p = L->pHead;
	while(p)
	{
		count++;
		p = p->pNext;
	}
	return count;

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

/********************************************************************
*********************************************************************
********************************************************************/

queue* Queue_init()
{
	queue* thiz=(queue *)malloc(sizeof(queue));

	thiz->Dlist = DDlink_init();

	return thiz;
}

void Queue_Pushback(queue *L, void *data)
{
	DDLink_append(L->Dlist,data);
	return;
}

void Queue_Pop(queue *L)
{
	DeleteHeadDDLink(L->Dlist);
	return;
}

void Queue_List(queue* L)
{
	DDLinkForeach(L->Dlist, DDLinkForeachPrint,print_int);
}

void Queue_length(queue *L)
{
	int count = DDLinkGetLength(L->Dlist);
	printf("The length of Queue is %d\n",count);
	return;
}

void Queue_Destroy(queue* L)
{
	DestoryDDLink(L->Dlist);
}


void main()
{
	dd_link L;
	int num[10] = {0,1,2,3,4,5,6,7,8,9};
	char cstr[10] = {'a','b','c','d','e','f','g','h','i','j'};
	int i = 0;
	int sum = 0;
	int max = 0;
	//memset(&L,0,sizeof(dd_link));
	
	//InitDDLink(&L);

	queue *Q = Queue_init();

	for(i=0;i<10;i++)
	{
		//DDLink_append(&L,&num[i]);	
		Queue_Pushback(Q,&num[i]);
	}

	
	//DDLinkForeach(&L, DDLinkForeachPrint,print_int);
	
	Queue_length(Q);
	Queue_List(Q);
	printf("**********ЫЌНу*************\n");
	
	Queue_Pop(Q);
	Queue_length(Q);
	Queue_List(Q);
	printf("**********ЫЌНу*************\n");
		
	Queue_Pop(Q);
	Queue_length(Q);
	Queue_List(Q);
	printf("**********ЫЌНу*************\n");
	Queue_Destroy(Q);
	return;
}




