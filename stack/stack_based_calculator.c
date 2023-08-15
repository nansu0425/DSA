#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

int InfixToPostfix(char *infix) /// 중위 표기식을 후위 표기식으로 바꾼다
{
	// 후위 표기식 저장에 필요한 메모리 할당
	int exp_len = strlen(infix);
	char* postfix = calloc(exp_len + 1, sizeof * postfix);
	if (postfix == NULL) return FALSE;
	
	// 연산자 저장을 위한 변수와 스택 할당
	Data op;
	Stack *stack = CreateStack();
	if (stack == NULL) return FALSE;
	
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
				Push(stack, infix[i]);
				break;
			case ')': // 닫는 괄호면 
				// 열린 괄호를 pop하기 전까지 스택의 연산자를 후위 표기식에 넣는다
				while (1)
				{
					Pop(stack, &op);
					if (op == '(') break;
					postfix[j++] = (char)op;
				}
				break;
			case '*': case '/': case '+': case '-': // 연산자인 경우
				// top에 있는 연산자의 우선순위가 더 높으면 pop한 후 후위 표기식에 넣는다
				while (Peek(stack, &op) == TRUE && Precedence(infix[i]) <= Precedence((char)op))
				{
					Pop(stack, &op);
					postfix[j++] = (char)op;
				}
				Push(stack, infix[i]);
				break;
			default: // 이외는 문자는 계산 불가
				return FALSE;
			}
		}
	}

	while (IsEmpty(stack) == FALSE) // 스택에 남아있는 연산자를 후위 표기식에 넣는다
	{
		Pop(stack, &op);
		postfix[j++] = (char)op;
	}

	strcpy_s(infix, exp_len + 1, postfix); // 후위 표기식을 중위 표기식에 복사
	free(stack);
	free(postfix);

	return TRUE;
}

int EvaluatePostfix(char *postfix, int *result) // 후위 표기식을 계산한다
{
	// 피연산자를 위한 스택과 연산자를 위한 변수 
	Stack* stack = CreateStack();
	Data op1, op2;
	
	int i;
	for (i = 0; i < strlen(postfix); i++)
	{
		if (isdigit(postfix[i])) // 피연산자는 스택에 push
			Push(stack, postfix[i] - '0'); // 아스키 코드 값에서 사칙연산 가능한 수로 변환
		else // 연산자인 경우
		{
			// 앞의 두 피연산자를 pop
			Pop(stack, &op2);
			Pop(stack, &op1);
			switch (postfix[i]) // 연산 후 결과를 스택에 push
			{
			case '+':
				Push(stack, op1 + op2);
				break;
			case '-':
				Push(stack, op1 - op2);
				break;
			case '*':
				Push(stack, op1 * op2);
				break;
			case '/':
				Push(stack, op1 / op2);
				break;
			default:
				return FALSE;
			}
		}
	}

	Pop(stack, result); // 스택에 최종 계산 결과만 남는다
	free(stack);

	return TRUE;
}

int Calculate(char *exp, int *result) // 수식을 계산한다
{
	if (InfixToPostfix(exp) == FALSE) // 중위 표기식을 후위 표기식으로 변환
		return FALSE;

	if (EvaluatePostfix(exp, result) == FALSE) // 후위 표기식을 계산한다
		return FALSE;

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
	int result;

	for (int i = 0; i < 3; i++)
	{
		Calculate(exp[i], &result);
		printf("result of exp%d: %d\n", i, result);
	}
	
	return 0;
}