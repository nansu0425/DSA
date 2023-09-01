#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

Tree CreateTree(Key key) // 트리 생성
{
    Node *root = malloc(sizeof *root);
    if (root == NULL) return NULL;

    root->key = key;
    root->left = root->right = NULL;

    return root;
}

int InsertLeftSubtree(Node *root, Tree subtree) // 트리에 왼쪽 서브트리 삽입
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

    printf("%d ", root->key);

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