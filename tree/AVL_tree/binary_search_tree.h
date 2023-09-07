#pragma once

#include "binary_tree.h"

Node* Search(Tree tree, Key key, Node** ptr_parent); // 키에 해당하는 노드 탐색 후 반환

int InsertKey(Tree* ptr_tree, Key key); // 이진 탐색 트리에 키 삽입

int TransplantSubtree(Tree* ptr_tree, Node* ptr_target_parent, Tree subtr_target, Tree subtr_new); // 특정 서브트리를 새로운 서브트리로 교체한다

int DeleteKey(Tree* ptr_tree, Key key); // 이진 탐색 트리에서 키 삭제

void PrintBinarySearchTree(Tree tree); // 이진 탐색 트리를 출력