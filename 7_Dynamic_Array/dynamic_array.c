#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _DArray
{
	void** data; //存取第一个元素的地址
	int nMaxLen;
	int nCurLen;
}DArray;

typedef void (*pDArrayVisit)(void *data, void *ctx);
typedef int  (*pDArrayCmp)  (void *data, void *ctx);
//typedef void (*pDArraySort) (void *data, void *data, void *ctx);



void DArrayInit(DArray *L, int nMallocLen)
{
	L->data = (void **)malloc(nMallocLen * sizeof(void *));
	L->nMaxLen = nMallocLen;
	L->nCurLen = 0;
}

void DArrayExpand(DArray *L)
{
	int nResizeLen = L->nMaxLen + L->nMaxLen/2+1;
	L->data = (void **)realloc(L->data,nResizeLen*sizeof(void *));
	L->nMaxLen = nResizeLen;
	return;
}

void DArrayPushBack(DArray *L, void* data)
{
	if(L->nCurLen >= L->nMaxLen)
	{
		printf("Not Enough Space!\n");
		DArrayExpand(L);
		//return;
	}

	L->data[L->nCurLen] = data;
	L->nCurLen ++;
	return;
}

void DArrayInsertMiddle(DArray *L, int location, void* data)
{
	int i = L->nCurLen;

	while(i > location-1)
	{
		L->data[i] = L->data[i-1];
		i--;
	}

	L->data[location-1] = data;
	L->nCurLen++;
	return;
}

void DArrayInsert(DArray *L, int location, void* data)
{
	if(L->nCurLen >= L->nMaxLen)
	{
		printf("Not Enough Space!Expanding the Space!\n");
		DArrayExpand(L);
		//return;
	}

	if(location > (L->nCurLen))
	{
		L->data[L->nCurLen] = data;
	    L->nCurLen ++;
	}
	else
	{
		DArrayInsertMiddle(L, location, data);
	}

	return;
}

void DArrayForeach(DArray *L, pDArrayVisit visit, void *ctx)
{
	int i;
	if(NULL == L)
	{
		printf("DArray is not init.\n");
		return;
	}
	
	if(0 == L->nCurLen)
	{
		printf("No Element!\n");
		return;
	}


	for(i = 0; i<L->nCurLen; i++)
	{
		visit(L->data[i],NULL);
	}
	return;
}


void  pDArrayVisit_PrintStr(void *data,void *ctx)
{
	char* str = (char *)data;
	printf("%s\n",str);
	return;
}


void  pDArrayVisit_PrintInt(void *data,void *ctx)
{
	int* tmp = (int *)data;
	printf("%d\n",*tmp);
	return;
}

void DArrayDestory(DArray *L)
{
	if(0 == L->nCurLen)
	{
		printf("There is no need to destory\n");
		return;
	}

	free((void *)L->data);
	printf("Destory Success!\n");
	return;
}

void DArrayDeleteMiddle(DArray *L, int location)
{
	int i = location;

	while(i < L->nCurLen)
	{
		L->data[i-1] = L->data[i];
		i++;
	}

	L->data[L->nCurLen] = NULL;
	L->nCurLen--;
	return;
}


void DArrayDelElement(DArray *L, int location)
{
	if((location > (L->nCurLen)) || (0 == L->nCurLen))
	{
		printf("Error para or NULL Dynamic Array\n");
		return;
	}
	
	DArrayDeleteMiddle(L, location);
	return;

}
int DArrayGetLength(DArray *L)
{
	return L->nCurLen;
}

int pDArrayCmp_int(void *data, void *ctx)
{
	int *i = (int *)data;
	int *j = (int *)ctx;

	if(*i == *j)
	{
		return 1;
	}
	else if(*i > *j)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

int pDArrayCmp_str(void *data, void *ctx)
{
	char *str_i = (char *)data;
	char *str_j = (char *)ctx;

	if(0 == strcmp(str_i,str_j))
	{
		return 1;
	}
	else if(strcmp(str_i,str_j) > 0)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}


void DArrayFind(DArray *L, pDArrayCmp cmp, void *data)
{
	int i;
	if(NULL == L)
	{
		printf("DArray is not init.\n");
		return;
	}
	
	if(0 == L->nCurLen)
	{
		printf("No Element!\n");
		return;
	}


	for(i = 0; i<L->nCurLen; i++)
	{
		if(1 == cmp(L->data[i],data))
		{
			printf("Find it!!The index is %d\n",i+1);
			break;
		}
	}

	if(i == L->nCurLen)
	{
		printf("Can't Find it\n");	
	}
	
	return;
}

//Bubsort
void Bubsort(DArray *L, pDArrayCmp cmp)
{
	void *tmp;
	int i,j;
	int nLen = L->nCurLen;

	for(i=0;i<nLen-1;i++)
		for(j=0;j<nLen-i-1;j++)
		{
			if((cmp(L->data[j],L->data[j+1])) > 0)
			{
				tmp = L->data[j];
				L->data[j] = L->data[j+1];
				L->data[j+1] = tmp;
			}
		}
}
	

//void QSort
void QSort(DArray *L, pDArrayCmp cmp, int left, int right)
{
	void *key,*tmp;
	int i = left,j = right;
	key= L->data[left];

	while(i < j)
	{
		while((cmp(key,L->data[j]) <= 1) && (i<j))
		{
			--j;
		}
		L->data[i] = L->data[j];
		
		while((1 <= cmp(key, L->data[i])) && (i<j))
		{
			++i	;
		}

		L->data[j] = L->data[i];
	}
	L->data[i] = key;
	printf("***the middle index is %d\n",i);
	DArrayForeach(L,pDArrayVisit_PrintInt, NULL);
	
	if((i-1) > left)  QSort(L,cmp, left, i-1);
	if(right > (i+1)) QSort(L,cmp, i+1, right);
}


void main()
{
	int i = 0;
	int nDArray_Length = 6;
	int num[10] = {0,1,2,3,4,5,6,7,8,9};
	DArray DA;

	memset(&DA, 0 ,sizeof(DArray));
	
	DArrayInit(&DA, nDArray_Length);

	for(;i<nDArray_Length;i++)
	{
		DArrayPushBack(&DA,&num[i]);
		
		//DArrayPushBack(&DA,strdup("it"));
	}

	DArrayDelElement(&DA,1);

	DArrayInsert(&DA, 3, &num[1]);
	DArrayInsert(&DA, 4, &num[3]);
	DArrayInsert(&DA, 5, &num[7]);

	DArrayFind(&DA,pDArrayCmp_str,&num[6]);

	
	printf("Displaying the Dynamic Array!\n");
	DArrayForeach(&DA,pDArrayVisit_PrintInt, NULL);

	//Bubsort(&DA,pDArrayCmp_int);

	QSort(&DA,pDArrayCmp_int,0,7);
	
	printf("Displaying the Sorted Dynamic Array!\n");
	DArrayForeach(&DA,pDArrayVisit_PrintInt, NULL);
	
	DArrayDestory(&DA);
	return;
}
