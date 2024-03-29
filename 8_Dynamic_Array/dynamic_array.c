#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*pDArrayVisit)(void *data, void *ctx);
typedef int  (*pDArrayCmp)  (void *data, void *ctx);
typedef void  (*pDArraySort) (void *data, void *ctx);

typedef struct _DArray
{
	void** data; //存取第一个元素的地址
	int nMaxLen;
	int nCurLen;
}DArray;


typedef struct _DArraySortPara
{
	pDArraySort sort;
	pDArrayCmp cmp;
	int left;
	int right;
}DArraySortPara;

//typedef void (*pDArraySort) (void *data, void *data, void *ctx);
void Bubsort(DArray *L, pDArrayCmp cmp);

//typedef void (*pDArraySort) (void *data, void *data, void *ctx);
void QSort_up(DArray * L,DArraySortPara * Sortdata);
void QSort_down(DArray *L, DArraySortPara *Sortdata);



void DArraySort(DArray *L, DArraySortPara *SortPara)
{
	if(SortPara->sort == Bubsort)
	{
		SortPara->sort(L,SortPara->cmp);
	}
	else
	{
		SortPara->sort(L,SortPara);
		printf("Gao Duan pai xu!!\n");
	}
	return;	
}

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
	/*if(0 == L->nCurLen)
	{
		printf("There is no need to destory\n");
		return;
	}*/

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
void QSort_up(DArray *L, DArraySortPara *Sortdata)
{
	void *key,*tmp;
	int i = Sortdata->left,j = Sortdata->right;
	int tmp_left = i,tmp_right = j;
	key= L->data[Sortdata->left];
	pDArrayCmp cmp = Sortdata->cmp;

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

	printf("The index is %d\n",i);
	DArrayForeach(L,pDArrayVisit_PrintInt, NULL);
	Sortdata->right = i-1;
	if((i-1) > Sortdata->left)  QSort_up(L,Sortdata);
	Sortdata->right = tmp_right;
	Sortdata->left = i+1;
	if(Sortdata->right > (i+1)) QSort_up(L,Sortdata);
}


//void QSort
void QSort_down(DArray *L, DArraySortPara *Sortdata)
{
	void *key,*tmp;
	int i = Sortdata->left,j = Sortdata->right;
	int tmp_left = i,tmp_right = j;
	key= L->data[Sortdata->left];
	pDArrayCmp cmp = Sortdata->cmp;


	while(i < j)
	{
		while((cmp(key,L->data[j]) >= 1) && (i<j))
		{
			--j;
		}
		L->data[i] = L->data[j];
		
		while((1 >= cmp(key, L->data[i])) && (i<j))
		{
			++i	;
		}

		L->data[j] = L->data[i];
	}
	L->data[i] = key;
	
	printf("The index is %d\n",i);
	DArrayForeach(L,pDArrayVisit_PrintInt, NULL);
	Sortdata->left = tmp_left;
	Sortdata->right = i-1;
	if((i-1) > Sortdata->left)  QSort_down(L,Sortdata);
	Sortdata->right = tmp_right;
	Sortdata->left = i+1;
	if(Sortdata->right > (i+1)) QSort_down(L,Sortdata);

}



void DArrayEachMergeSort(DArray *L, DArray *L_tmp, pDArrayCmp cmp, int start, int middle, int end)
{
	int i = start;
	int j = start;
	int k = middle;
	int new_mid = 0;;
	
	//process low part
	if((middle - start) >= 2 )
	{
		new_mid= start + ((middle-start) >> 1);
		DArrayEachMergeSort(L,L_tmp,cmp,start,new_mid,middle);
	}

	//process high part
	if((end - middle) >=2 )
	{
		new_mid = middle + ((end-middle) >> 1);
		DArrayEachMergeSort(L,L_tmp,cmp,middle,new_mid,end);
	}


	//sort two part
	while((i < middle) && (k <= end))
	{
		if(cmp(L->data[i], L->data[k]) >= 1)
		{
			L_tmp->data[j++] = L->data[k++];
		}
		else
		{
			L_tmp->data[j++] = L->data[i++];
		}
	}

	while(i < middle)
	{
		L_tmp->data[j++] = L->data[i++];
	}

	while(k <= end)
	{
		L_tmp->data[j++] = L->data[k++];
	}


	for(j = start; j <= end; j++)
	{
		L->data[j] = L_tmp->data[j];
	}
	return;
}


void DArrayQSearch(DArray *L, void* data, pDArrayCmp cmp)
{
	int low = 0;
	int high = L->nCurLen;
	int middle = 0;

	while(low < high)
	{
		middle = low + ((high - low) >> 1);

		if(1 == (cmp(L->data[middle],data)))
		{
			printf("*********Find it at %d\n",middle+1);
			return;
		}
		else if(1 < (cmp(L->data[middle],data)))
		{
			high = middle-1;
		}
		else
		{
			low = middle+1;
		}
	}

	printf("Sorry!!!!Not Found!!!!\n");
	return;
}



void DArrayMergeSort(DArray *L,DArraySortPara *SortPara)
{
	DArray L_tmp;
	int middle = (SortPara->right - SortPara->left)>>1;
	DArrayInit(&L_tmp,L->nCurLen);
	DArrayEachMergeSort(L, &L_tmp , SortPara->cmp, SortPara->left,middle,SortPara->right);
	DArrayDestory(&L_tmp);
	return;
}

void main()
{
	int i = 0;
	int nDArray_Length = 6;
	int num[10] = {0,1,2,3,4,5,6,7,8,9};
	DArray DA;
	pDArrayVisit print = pDArrayVisit_PrintInt;
	pDArrayCmp cmp = pDArrayCmp_int;
	DArraySortPara SortPara;
	SortPara.sort = DArrayMergeSort;
	SortPara.cmp = cmp;
	SortPara.left = 0;
	SortPara.right = 7;

	
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

	
	/*DArrayInsert(&DA, 3, strdup("bcd"));插入字符串
	DArrayInsert(&DA, 4, strdup("bbd"));
	DArrayInsert(&DA, 5, strdup("abc"));
	DArrayInsert(&DA, 3, strdup("dd"));
	DArrayInsert(&DA, 3, strdup("aaa"));*/

	printf("Displaying the Dynamic Array!\n");
	DArrayForeach(&DA,print, NULL);

	DArraySort(&DA,&SortPara);		
	printf("Displaying the Sorted Dynamic Array!\n");
	DArrayForeach(&DA,print, NULL);

	DArrayQSearch(&DA,&num[7],cmp);
	
	DArrayDestory(&DA);
	return;
}
