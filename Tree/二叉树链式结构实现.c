#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#include "windows.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

int treeIndex = 1;
typedef char String[24];
String str;

Status StrAssign(String T, char *chars) {
    int i;
    if (strlen(chars) > MAXSIZE) {
        return ERROR;
    }
    else {
        T[0] = strlen(chars);
        for (i = 1; i <= T[0]; i++) {
            T[i] = *(chars + i - 1);
        }
        return OK;
    }
}


typedef char TElemType;
TElemType Nil = ' ';

Status visit (TElemType e) {
    printf("%c", e);
    return OK;
}

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

Status InitBiTree(BiTree *T) {
    *T = NULL;
    return OK;
}

void DestroyBiTree(BiTree *T) {
    if (*T) {
        if ((*T)->lchild) {
            DestroyBiTree(&(*T)->lchild);
        }
        if ((*T)->rchild) {
            DestroyBiTree(&(*T)->rchild);
        }
        free(*T);
        *T = NULL;
    }
}

/* 按前序输入二叉树中结点的值（一个字符） */
/* #表示空树，构造二叉链表表示二叉树T。 */
// 每个结点的指针变量和实际内存都是当场分配的，每次传过去的都是指向指针变量的指针
void CreateBiTree(BiTree *T) {
    TElemType ch;
    ch = str[treeIndex++];

    if (ch == '#')
        *T = NULL;
    else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T)
            exit(OVERFLOW);
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
Status BiTreeEmpty(BiTree T) {
    if (T)
        return FALSE;
    else
        return TRUE;
}

#define ClearBiTree DestroyBiTree

/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
int BiTreeDepth(BiTree T) {
    int i, j;
    if (!T)
        return 0;
    if (T->lchild)
        i = BiTreeDepth(T->lchild);
    else i = 0;
    if (T->rchild)
        j = BiTreeDepth(T->rchild);
    else j = 0;
    return i > j ? i + 1 : j + 1;
}

/* 初始条件: 二叉树T存在。操作结果: 返回T的根 */
TElemType Root(BiTree T) {
    if (BiTreeEmpty(T))
        return Nil;
    else
        return T->data;
}


/* 初始条件: 二叉树T存在，p指向T中某个结点 */
/* 操作结果: 返回p所指结点的值 */
TElemType Value(BiTree p) {
    return p->data;
}


/* 给p所指结点赋值为value */
void Assign(BiTree p, TElemType e) {
    p->data = e;
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 前序递归遍历T */
void PreOrderTraverse(BiTree T) {
    if (T == NULL)
        return;
    printf("%c", T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 中序递归遍历T */
void InOrderTraverse(BiTree T)
{
    if(T==NULL)
        return;
    InOrderTraverse(T->lchild); /* 中序遍历左子树 */
    printf("%c",T->data);/* 显示结点数据，可以更改为其它对结点操作 */
    InOrderTraverse(T->rchild); /* 最后中序遍历右子树 */
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 后序递归遍历T */
void PostOrderTraverse(BiTree T)
{
    if(T==NULL)
        return;
    PostOrderTraverse(T->lchild); /* 先后序遍历左子树  */
    PostOrderTraverse(T->rchild); /* 再后序遍历右子树  */
    printf("%c",T->data);/* 显示结点数据，可以更改为其它对结点操作 */
}

int main()
{
    SetConsoleOutputCP(65001);

    int i;
    BiTree T;
    TElemType e1;
    InitBiTree(&T);


    StrAssign(str,"ABDH#K###E##CFI###G#J##");

    CreateBiTree(&T);

    printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    e1=Root(T);
    printf("二叉树的根为: %c\n",e1);

    printf("\n前序遍历二叉树:");
    PreOrderTraverse(T);
    printf("\n中序遍历二叉树:");
    InOrderTraverse(T);
    printf("\n后序遍历二叉树:");
    PostOrderTraverse(T);
    ClearBiTree(&T);
    printf("\n清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    i=Root(T);
    if(!i)
        printf("树空，无根\n");

    return 0;
}
