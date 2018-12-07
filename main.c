#include<stdio.h>
#include<stdlib.h>

typedef char DataType;

typedef struct Node
{
    DataType data;
    struct Node *leftChild;
    struct Node *rightChild;

}BT;//完成节点结构体定义

void Initiate(BT **root)
{
    *root = (BT*)malloc(sizeof(BT));
    (*root)->leftChild = NULL;
    (*root)->rightChild = NULL;

}//初始化二叉树头结点

void Destroy(BT **root)
{
    if((*root) != NULL && (*root)->leftChild != NULL)
    {
        Destroy(&(*root)->leftChild);
    }
    if((*root) != NULL && (*root)->rightChild != NULL)
    {
        Destroy(&(*root)->rightChild);
    }
    free(*root);
}//二叉树删除

BT *InsertLeft(BT *curr, DataType x)
{
    BT *s, *t;
    if(curr == NULL)
        return NULL;
    else
    {
        t = curr->leftChild;
        s = (BT *)malloc(sizeof(BT));
        s->data = x;
        s->leftChild = t;
        s->rightChild = NULL;
        curr->leftChild = s;
        return curr->leftChild;
    }//插入左孩子
}

BT *InsertRight(BT *curr, DataType x)
{
    BT *s, *t;
    if(curr == NULL)
        return NULL;
    else
    {
        t = curr->rightChild;
        s = (BT *)malloc(sizeof(BT));
        s->data = x;
        s->rightChild = t;
        s->leftChild = NULL;
        curr->rightChild = s;
        return curr->rightChild;
    }//插入右孩子
}

void PreOrder(BT *t, void visit(DataType item))
//使用visit（item）遍历二叉树
{
    if(t != NULL)
    {
        visit(t->data);
        PreOrder(t->leftChild, visit);
        PreOrder(t->rightChild, visit);
    }
}

void InOrder(BT *t, void visit(DataType item))
//使用中序遍历二叉树
{
    if(t != NULL)
    {
        InOrder(t->leftChild, visit);
        visit(t->data);
        InOrder(t->rightChild, visit);
    }
}

void PostOrder(BT *t, void visit(DataType item))
//使用后序遍历二叉树
{
    if(t != NULL)
    {
        PostOrder(t->leftChild, visit);
        PostOrder(t->rightChild, visit);
        visit(t->data);
    }
}

void Visit(DataType item)
{
    printf("%c", item);
}

BT *Search(BT *root, DataType x)
{
    BT *find = NULL;
    if(root != NULL)
    {
        if(root->data == x)
        {
            find = root;
        }
        else
        {
            find = Search(root->leftChild, x);
            if(find == NULL)
            {
                find = Search(root->rightChild, x);
            }
        }
    }
    return find;
}

void main()
{
    BT *root, *p, *pp, *find;
    char x = 'E';
    Initiate(&root);
    p = InsertLeft(root, 'A');
    p = InsertLeft(p, 'B');
    p = InsertLeft(p, 'D');
    p = InsertRight(p, 'G');
    p = InsertRight(root->leftChild, 'C');
    pp = p;
    InsertLeft(p, 'E');
    InsertRight(pp, 'F');
    printf("PreOrder:");
    PreOrder(root->leftChild, Visit);
    printf("\nInOrder:");
    InOrder(root->leftChild, Visit);
    printf("\nPostOrder:");
    PostOrder(root->leftChild, Visit);

    find = Search(root, x);
    if(find != NULL)
    {
        printf("\nData %c in the tree\n", x);
    }
    else
    {
        printf("\nData %c not in the tree\n", x);
    }

    Destroy(&root);
}