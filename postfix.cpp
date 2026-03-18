#include <stdio.h>
#pragma warning(disable : 4996)
#include "postfix.h"
#include<string.h>


void main()
{
	char exp[100];  // postfix expression
	int result;

	while (1) {
		printf("\nInput postfix expression: ");
		scanf("%s", exp);

		result = eval_postfix(exp);
		if (err_check == false)
			printf("Result = %d \n\n", result);
	}
}

void push(int e) {
	stack[++top] = e;
}

int pop() {
	return stack[top--];
}

int eval_postfix(char* exp) {
	int a, b, result;
	int len = strlen(exp);
	for (int i = 0; i < len; i++) {
		if (is_number(exp[i]) ==  true) { //만약 숫자면 push
			push(exp[i]-48);
		}
		else if (is_op(exp[i]) == true) { //만약 연산자면
			if (exp[i] == '+') {		//연산자가 +면 pop + pop
				result = pop() + pop(); 
				push(result);
			}
			else if (exp[i] == '-') {	//연산자가 -면 pop - pop
				a = pop();
				b = pop();
				result = b - a;
				push(result);
			}
			else if (exp[i] == '*') {	//연산자가 *면 pop * pop
				result = pop() * pop();
				push(result);
			}
			else if (exp[i] == '/') {	//연산자가 /면 pop / pop
				a = pop(), b = pop();
				if (a == 0) {
					printf("divided by 0 error\n");
					err_check = true;
					return 0;
				}
				else {
					result = b / a;
					push(result);
				}
			}
		}
		if (top > 0) err_check == true;
	}
	return result;
}

boolean is_number(char c)
{
	if (('0' <= c) && (c <= '9'))
		return true;
	else
		return false;
}

boolean is_op(char c) {
	if ((c < '0') || (c > '9'))
		return true;
	else
		return false;
}