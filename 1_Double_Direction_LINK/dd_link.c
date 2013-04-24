#include <stdio.h>
#include <stdlib.h>

#define CreateNode(t,p) p = (t*)malloc(sizeof(t))
#define FreeNode(p) free((void *)p)

typedef struct dd_link_node
{
	int data;
	struct dd_link_node *pPre,*pNext;
}dd_link_node;

typedef struct dd_link
{
	struct dd_link_node* pHead;
}dd_link;


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
void InsertDDLink(dd_link *L,int nData)
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


//Print dd_link
void PrintDDLink(dd_link *L)
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
		printf("%d\n",p->data);
		p = p->pNext;
	}
	return;
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
		if(p->data == nData)
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

void main()
{
	dd_link L;
	int i = 0;
	memset(&L,0,sizeof(dd_link));
	
	InitDDLink(&L);

	for(i=0;i<1;i++)
	{
		InsertDDLink(&L,i);		
	}

	PrintDDLink(&L);

	printf("Try to delete NULL element...\n");
	DeleteNodeByData(&L,99);
	PrintDDLink(&L);

	printf("Try to delete last element...\n");
	DeleteNodeByData(&L,0);
	PrintDDLink(&L);
	
	printf("Try to delete normal element...\n");
	DeleteNodeByData(&L,4);
	PrintDDLink(&L);

	
	printf("Try to delete first element...\n");
	DeleteNodeByData(&L,9);
	PrintDDLink(&L);
	
	DestoryDDLink(&L);
	return;
}




