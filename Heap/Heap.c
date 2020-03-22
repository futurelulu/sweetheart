#include "Heap.h"

void Swap(int* a, int* b)
{
	int x = *a;
	*a = *b;
	*b = x;
}

// 小堆 
// ->条件：左右子树都是堆
void AdjustDown(HpDataType* a, size_t n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		// 找出小的那个孩纸
		if (child + 1 < n && a[child+1] < a[child])
		{
			++child;
		}

		// 1、孩纸比父亲小，则交换，继续往下调
		// 2、孩纸比父亲大，则终止调整
		if (a[parent] > a[child])
		{
			Swap(&a[child], &a[parent]);

			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapCreate(Heap* hp, HpDataType* a, size_t n)
{
	hp->_a = (HpDataType*)malloc(sizeof(HpDataType)*n);
	memcpy(hp->_a, a, sizeof(HpDataType)*n);
	hp->_size = n;
	hp->_capacity = n;

	// 建小堆
	for (int i = (n-1-1)/2; i >= 0; --i)
	{
		AdjustDown(hp->_a, hp->_size, i);
	}
}

void AdjustUp(int* a, int child)
{
	int parent = (child - 1) / 2;
	//while (parent >= 0) // 没起作用，巧合借助break跳出的
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void HeapPush(Heap* hp, HpDataType x)
{
	// 空间不够-》增容
	if (hp->_size == hp->_capacity)
	{
		size_t newcapacity = hp->_capacity * 2;
		hp->_a = (HpDataType*)realloc(hp->_a, sizeof(HpDataType)*newcapacity);
		hp->_capacity = newcapacity;
	}

	hp->_a[hp->_size] = x;
	hp->_size++;

	// 向上调整，调成堆
	AdjustUp(hp->_a, hp->_size - 1);
}

void HeapPop(Heap* hp)
{
	Swap(&hp->_a[0], &hp->_a[hp->_size - 1]);
	hp->_size--;

	AdjustDown(hp->_a, hp->_size, 0);
}

HpDataType HeapTop(Heap* hp)
{
	return hp->_a[0];
}

int HeapEmpty(Heap* hp)
{
	return hp->_size == 0 ? 1 : 0;
}

void HeapPrint(Heap* hp)
{
	for (int i = 0; i < hp->_size; ++i)
	{ 
		printf("%d ", hp->_a[i]);
	}
	printf("\n");
}