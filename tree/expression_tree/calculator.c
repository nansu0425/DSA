#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "binary_tree.h"
#include "stack_using_linked_list.h"

int Precedence(char op) // 연산자 우선순위 판단
{
	switch (op)
	{
	case '*': case '/':
		return 3;
	case '+': case '-':
		return 2;
	case '(':
		return 1;
	default:
		return FALSE;
	}
}

int InfixToPostfix(char* infix) /// 중위 표기식을 후위 표기식으로 바꾼다
{
	if (infix == NULL) return NULL;

	// 후위 표기식 저장에 필요한 메모리 할당
	size_t exp_len = strlen(infix);
	char* postfix = calloc(exp_len + 1, sizeof * postfix);
	if (postfix == NULL) return FALSE;

	// 연산자 저장을 위한 변수와 스택 생성
	char op;
	char* stack = malloc(exp_len);
	if (stack == NULL) return FALSE;
	int top = -1;

	int i, j;
	for (i = 0, j = 0; i < exp_len; i++)
	{
		if (isdigit(infix[i])) // 숫자인 경우
			postfix[j++] = infix[i]; // 후위 표기식에 넣는다
		else
		{
			switch (infix[i])
			{
			case '(': // 열린 괄호면 스택에 push
				stack[++top] = infix[i];
				break;
			case ')': // 닫는 괄호면 
				// 열린 괄호를 pop하기 전까지 스택의 연산자를 후위 표기식에 넣는다
				while (1)
				{
					op = stack[top--];
					if (op == '(') break;
					postfix[j++] = op;
				}
				break;
			case '*': case '/': case '+': case '-': // 연산자인 경우
				// top에 있는 연산자의 우선순위가 더 높으면 pop한 후 후위 표기식에 넣는다
				while (top > -1 && Precedence(infix[i]) <= Precedence(stack[top]))
				{
					op = stack[top--];
					postfix[j++] = op;
				}
				stack[++top] = infix[i];
				break;
			default: // 이외는 문자는 계산 불가
				return FALSE;
			}
		}
	}

	while (top > -1) // 스택에 남아있는 연산자를 후위 표기식에 넣는다
	{
		op = stack[top--];
		postfix[j++] = op;
	}

	strcpy_s(infix, exp_len + 1, postfix); // 후위 표기식을 중위 표기식에 복사
	free(stack);
	free(postfix);

	return TRUE;
}

Tree CreateExpressionTree(char* postfix) // 후위 표기식으로 수식 트리를 만든다
{
	if (postfix == NULL) return NULL;
	
	Stack* stack = CreateStack();
	Tree subtree1, subtree2;

	int i;
	size_t exp_len = strlen(postfix);
	
	for (i = 0; i < exp_len; i++)
	{
		if (isdigit(postfix[i])) // 숫자인 경우 스택에 넣는다
			Push(stack, CreateTree(postfix[i]));
		else // 연산자인 경우
		{
			// 스택에서 트리 두 개를 꺼낸 후
			Pop(stack, &subtree2);
			Pop(stack, &subtree1);

			// 연산자 트리 밑에 삽입
			Tree operator = CreateTree(postfix[i]);
			InsertLeftSubtree(operator, subtree1);
			InsertRightSubtree(operator, subtree2);

			// 트리에 삽입이 끝나면 스택에 넣는다
			Push(stack, operator);
		}
	}

	Pop(stack, &subtree1); // 최종 수식 트리의 루트를 subtree1에 저장
	free(stack);

	return subtree1;
}

int EvaluateExpressionTree(Tree exp_tree, int *result) // 수식 트리를 계산한다
{
	if (exp_tree == NULL || result == NULL)
		return FALSE;

	int left_result, right_result;

	if (isdigit(exp_tree->data)) // 트리의 루트가 숫자면
		*result = exp_tree->data - '0'; // 사칙 연산 가능한 형태로 루트의 값을 저장
	else // 트리의 루트가 연산자면
	{
		// 트리의 왼쪽 서브트리와 오른쪽 서브트리의 계산 결과를 구한다
		EvaluateExpressionTree(exp_tree->left, &left_result);
		EvaluateExpressionTree(exp_tree->right, &right_result);

		switch (exp_tree->data) // 연산자 종류에 따라 사칙 연산
		{
		case '+':
			*result = left_result + right_result;
			break;
		case '-':
			*result = left_result - right_result;
			break;
		case '*':
			*result = left_result * right_result;
			break;
		case '/':
			*result = left_result / right_result;
			break;
		default:
			return ERROR;
		}
	}

	return TRUE;
}

int main()
{
	char exp[3][30] =
	{
		"1+2*3+(8/4-(5+7))",
		"(5-8)*3-(6/2-7*2)",
		"((1-2)+8)/(9-7)-(8*6+(6-7/2))"
	};
	Tree exp_tree;
	int result;
	int i;

	for (i = 0; i < 3; i++)
	{
		// Infix To Postfix
		printf("Infix expression: %s\n", exp[i]);
		InfixToPostfix(exp[i]);
		printf("Postfix expression: %s\n", exp[i]);

		// Create Expression Tree
		exp_tree = CreateExpressionTree(exp[i]);
		PrintTree(exp_tree);

		// Evaluate Expression Tree
		EvaluateExpressionTree(exp_tree, &result);
		printf("Result: %d\n\n", result);
	}

	return 0;
}

/*
OUTPUT

Infix expression: 1+2*3+(8/4-(5+7))
Postfix expression: 123*+84/57+-+
Preorder traversal: + + 1 * 2 3 - / 8 4 + 5 7
Inorder traversal: 1 + 2 * 3 + 8 / 4 - 5 + 7
Postorder traversal: 1 2 3 * + 8 4 / 5 7 + - +
Result: -3

Infix expression: (5-8)*3-(6/2-7*2)
Postfix expression: 58-3*62/72*--
Preorder traversal: - * - 5 8 3 - / 6 2 * 7 2
Inorder traversal: 5 - 8 * 3 - 6 / 2 - 7 * 2
Postorder traversal: 5 8 - 3 * 6 2 / 7 2 * - -
Result: 2

Infix expression: ((1-2)+8)/(9-7)-(8*6+(6-7/2))
Postfix expression: 12-8+97-/86*672/-+-
Preorder traversal: - / + - 1 2 8 - 9 7 + * 8 6 - 6 / 7 2
Inorder traversal: 1 - 2 + 8 / 9 - 7 - 8 * 6 + 6 - 7 / 2
Postorder traversal: 1 2 - 8 + 9 7 - / 8 6 * 6 7 2 / - + -
Result: -48
*/