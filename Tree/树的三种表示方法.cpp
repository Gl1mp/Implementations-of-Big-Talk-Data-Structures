#include <stdio.h>
#define MAX_TREE_SIZE 100
typedef int TElemType;

// 法1：双亲表示法
typedef struct PTNode
{
	TElemType data;
	int parent;
}PTNode;

typedef struct
{
	PTNode nodes[MAX_TREE_SIZE];
	int n, r; // n为节点数，r为根节点位置
}PTree;

// 法2：孩子表示法
typedef struct CTNode
{
	int child;
	struct CTNode* next;
}*ChildPtr;

typedef struct
{
	TElemType data;
	ChildPtr firstchild;
}CTBox;

typedef struct
{
	CTBox nodes[MAX_TREE_SIZE];
	int n, r; // n为节点数，r为根节点位置
}CTree;

// 法2+法1的改进版本：双亲孩子表示法
typedef struct
{
	TElemType data;
	ChildPtr firstchild;
	int parent; // 多加一个父亲节点位置即可
}CPTBox;

typedef struct
{
	CPTBox nodes[MAX_TREE_SIZE];
	int n, r; // n为节点数，r为根节点位置
}CPTree;

// 法3：孩子兄弟表示法
typedef struct CSNode
{
	TElemType data;
	struct CSNode *firstchild, *rightsib;
}CSNode, *CSTree;
