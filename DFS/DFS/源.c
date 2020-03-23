#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MaxVex        100            //��󶥵���
#define INFINITY    65535        //��ʾ��
#define TRUE        1
#define    FALSE        0
typedef char        VertexType;    //��������
typedef int            EdgeType;    //Ȩֵ����
typedef int            Bool;
Bool    visited[MaxVex];

typedef struct {
	VertexType    vexs[MaxVex];         //��������
	EdgeType    arc[MaxVex][MaxVex];    //�ڽӾ���
	int    numVertexes, numEdges;       //��ǰͼ�еĽ�����Լ�����
}MGraph;


//������ȱ�����Ҫ��ѭ������
typedef struct {
	int    data[MaxVex];
	int    front, rear;
}Queue;


/****************************************/
//���е���ز���

//��ʼ��
void InitQueue(Queue* Q)
{
	Q->front = Q->rear = 0;
}

//���
void EnQueue(Queue* Q, int e)
{
	if ((Q->rear + 1) % MaxVex == Q->front)
		return;

	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MaxVex;
}

//�п�
Bool QueueEmpty(Queue* Q)
{
	if (Q->front == Q->rear)
		return TRUE;
	else
		return FALSE;
}

//����
void DeQueue(Queue* Q, int* e)
{
	if (Q->front == Q->rear)
		return;

	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MaxVex;
}
/****************************************/


//����ͼ���ڽӾ���
void CreateMGraph(MGraph* G)
{
	int i, j, k, w;

	printf("���붥�����ͱ���: ");
	scanf("%d%d", &G->numVertexes, &G->numEdges);
	fflush(stdin);

	printf("==============================\n");
	printf("�����������:\n");
	for (i = 0; i < G->numVertexes; ++i)
	{
		printf("����%d: ", i + 1);
		scanf("%c", &G->vexs[i]);
		fflush(stdin);
	}

	for (i = 0; i < G->numVertexes; ++i)
	{
		for (j = 0; j < G->numVertexes; ++j)
			G->arc[i][j] = INFINITY;
	}

	printf("==============================\n");
	for (k = 0; k < G->numEdges; ++k)
	{
		printf("�����(vi, vj)�е��±�i��j��ȨW: ");
		scanf("%d%d%d", &i, &j, &w);
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
}


//���
void DisMGraph(MGraph* G)
{
	int i, j, k;
	k = G->numVertexes;
	for (i = 0; i < k; ++i)
	{
		for (j = 0; j < k; ++j)
		{
			printf("%5d ", G->arc[i][j]);
		}
		putchar('\n');
	}
}


/****************************************/
//ͼ��������ȱ���
void DFS(MGraph G, int i)
{
	int j;
	visited[i] = TRUE;
	printf("%c ", G.vexs[i]);

	for (j = 0; j < G.numVertexes; ++j)
	{
		if (G.arc[i][j] != INFINITY && !visited[j])
			DFS(G, j);
	}
}

void DFSTraverse(MGraph G)
{
	int i;
	for (i = 0; i < G.numVertexes; ++i)
		visited[i] = FALSE;         //���н�㶼û�б����ʹ�

	for (i = 0; i < G.numVertexes; ++i)
	{
		if (!visited[i])
			DFS(G, i);
	}

}


//ͼ�Ĺ�����ȱ���
void BFSTraverse(MGraph* G)
{
	int i, j;
	Queue Q;

	for (i = 0; i < G->numVertexes; ++i)//�������
		visited[i] = FALSE;

	InitQueue(&Q);

	for (i = 0; i < G->numVertexes; ++i)
	{
		if (!visited[i])
		{
			visited[i] = TRUE;
			printf("%c ", G->vexs[i]);
			EnQueue(&Q, i);

			while (!QueueEmpty(&Q))
			{
				DeQueue(&Q, &i);
				for (j = 0; j < G->numVertexes; ++j)
				{
					if (!visited[j] && G->arc[i][j] != INFINITY)
					{
						visited[j] = TRUE;
						printf("%c ", G->vexs[j]);
						EnQueue(&Q, j);
					}
				}
			}
		}
	}
}
/****************************************/

//�������
int main() {
	MGraph G;

	CreateMGraph(&G);

	printf("\nͼ��������ȱ���Ϊ: ");
	DFSTraverse(G);

	printf("\nͼ�Ĺ�����ȱ���Ϊ: ");
	BFSTraverse(&G);

	printf("\n");

	return 0;
}

