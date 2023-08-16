#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define ERROR   -1

typedef int Data; // 트리의 데이터 타입

typedef struct _Node // 노드 구조체 정의
{
    Data data;
    struct _Node *left;
    struct _Node *right;
} Node;

typedef Node *Tree; // 트리는 루트 노드의 포인터

typedef enum {PREORDER, INORDER, POSTORDER} TraversalWay; // 탐색 방법을 정의

typedef int (*ProcessRoot)(Tree tree); // 탐색한 트리의 루트 처리

Tree CreateTree(Data data) // 트리 생성
{
    Node *root = malloc(sizeof *root);
    if (root == NULL) return NULL;

    root->data = data;
    root->left = root->right = NULL;

    return root;
}

int InsertLeftSubtree(Node *root, Tree subtree) // 루트 노드의 왼쪽 서브트리 삽입
{
    if (root == NULL || root->left != NULL || subtree == NULL) return FALSE;

    root->left = subtree;

    return TRUE;
}

int InsertRightSubtree(Node *root, Tree subtree) // 루트 노드의 오른쪽 서브트리 삽입
{
    if (root == NULL || root->right != NULL || subtree == NULL) return FALSE;

    root->right = subtree;

    return TRUE;
}

int Traverse(Tree tree, TraversalWay traversal_way, ProcessRoot process_root) // 트리를 순회
{
    if (tree == NULL || (traversal_way != 0 && traversal_way != 1 && traversal_way != 2) || process_root == NULL)
        return FALSE;
    
    switch (traversal_way)
    {
    case PREORDER: // 전위 순회
        process_root(tree);
        Traverse(tree->left, PREORDER, process_root);
        Traverse(tree->right, PREORDER, process_root);
        break;
    case INORDER: // 중위 순회
        Traverse(tree->left, INORDER, process_root);
        process_root(tree);
        Traverse(tree->right, INORDER, process_root);
        break;
    case POSTORDER: // 후위 순회
        Traverse(tree->left, POSTORDER, process_root);
        Traverse(tree->right, POSTORDER, process_root);
        process_root(tree);
        break;
    default:
        return ERROR;
    }

    return TRUE;
}

int DeleteRoot(Node *root) // 트리의 루트 노드 삭제
{
    if (root == NULL) return FALSE;

    free(root);

    return TRUE;
}

int DeleteLeftSubtree(Node *root) // 트리의 왼쪽 서브트리 삭제
{
    if (root == NULL) return FALSE;

    Traverse(root->left, POSTORDER, DeleteRoot);
    root->left = NULL;

    return TRUE;
}

int DeleteRightSubtree(Node *root) // 트리의 오른쪽 서브트리 삭제
{
    if (root == NULL) return FALSE;

    Traverse(root->right, POSTORDER, DeleteRoot);
    root->right = NULL;

    return TRUE;
}

int PrintRoot(Node *root) // 루트를 출력
{
    if (root == NULL) return FALSE;

    printf("%c ", root->data);

    return TRUE;
}

int PrintTree(Tree tree) // 트리를 출력
{
    if (tree == NULL)
    {
        printf("Tree is empty\n");
        return FALSE;
    }

    printf("Preorder traversal: ");
    Traverse(tree, PREORDER, PrintRoot);
    printf("\n");

    printf("Inorder traversal: ");
    Traverse(tree, INORDER, PrintRoot);
    printf("\n");

    printf("Postorder traversal: ");
    Traverse(tree, POSTORDER, PrintRoot);
    printf("\n");

    return TRUE;
}

int main()
{

    Tree a = CreateTree('a');
    Tree b = CreateTree('b');
    Tree c = CreateTree('c');
    Tree d = CreateTree('d');
    Tree e = CreateTree('e');
    Tree f = CreateTree('f');
    Tree g = CreateTree('g');

    InsertLeftSubtree(a, b);
    InsertRightSubtree(a, c);
    InsertLeftSubtree(b, d);
    InsertRightSubtree(b, e);
    InsertRightSubtree(c, f);
    InsertRightSubtree(e, g);
    PrintTree(a);
    /*
        a
       / \
      b   c
     / \   \
    d   e   f
         \
          g
    */
    printf("\n");

    DeleteLeftSubtree(a);
    PrintTree(a);
    /*
    a
     \
      c
       \   
        f
    */
    printf("\n");

    DeleteRightSubtree(a);
    PrintTree(a);
    /*
    a
    */
    printf("\n");

    DeleteRoot(a);
    a = NULL;
    PrintTree(a);

    return 0;
}

/*
OUTPUT

Preorder traversal: a b d e g c f 
Inorder traversal: d b e g a c f
Postorder traversal: d g e b f c a

Preorder traversal: a c f
Inorder traversal: a c f 
Postorder traversal: f c a

Preorder traversal: a
Inorder traversal: a
Postorder traversal: a

Tree is empty
*/