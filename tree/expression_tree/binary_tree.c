#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

Tree CreateTree(TData data) // 트리 생성
{
    TNode *root = malloc(sizeof *root);
    if (root == NULL) return NULL;

    root->data = data;
    root->left = root->right = NULL;

    return root;
}

int InsertLeftSubtree(TNode *root, Tree subtree) // 루트 노드의 왼쪽 서브트리 삽입
{
    if (root == NULL || root->left != NULL || subtree == NULL) return FALSE;

    root->left = subtree;

    return TRUE;
}

int InsertRightSubtree(TNode *root, Tree subtree) // 루트 노드의 오른쪽 서브트리 삽입
{
    if (root == NULL || root->right != NULL || subtree == NULL) return FALSE;

    root->right = subtree;

    return TRUE;
}

int TraverseTree(Tree tree, TraversalWay traversal_way, ProcessRoot process_root) // 트리를 순회
{
    if (tree == NULL || (traversal_way != 0 && traversal_way != 1 && traversal_way != 2) || process_root == NULL)
        return FALSE;
    
    switch (traversal_way)
    {
    case PREORDER: // 전위 순회
        process_root(tree);
        TraverseTree(tree->left, PREORDER, process_root);
        TraverseTree(tree->right, PREORDER, process_root);
        break;
    case INORDER: // 중위 순회
        TraverseTree(tree->left, INORDER, process_root);
        process_root(tree);
        TraverseTree(tree->right, INORDER, process_root);
        break;
    case POSTORDER: // 후위 순회
        TraverseTree(tree->left, POSTORDER, process_root);
        TraverseTree(tree->right, POSTORDER, process_root);
        process_root(tree);
        break;
    default:
        return ERROR;
    }

    return TRUE;
}

int DeleteRoot(TNode *root) // 트리의 루트 노드 삭제
{
    if (root == NULL) return FALSE;

    free(root);

    return TRUE;
}

int DeleteLeftSubtree(TNode *root) // 트리의 왼쪽 서브트리 삭제
{
    if (root == NULL) return FALSE;

    TraverseTree(root->left, POSTORDER, DeleteRoot);
    root->left = NULL;

    return TRUE;
}

int DeleteRightSubtree(TNode *root) // 트리의 오른쪽 서브트리 삭제
{
    if (root == NULL) return FALSE;

    TraverseTree(root->right, POSTORDER, DeleteRoot);
    root->right = NULL;

    return TRUE;
}

int PrintRoot(TNode *root) // 루트를 출력
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
    TraverseTree(tree, PREORDER, PrintRoot);
    printf("\n");

    printf("Inorder traversal: ");
    TraverseTree(tree, INORDER, PrintRoot);
    printf("\n");

    printf("Postorder traversal: ");
    TraverseTree(tree, POSTORDER, PrintRoot);
    printf("\n");

    return TRUE;
}