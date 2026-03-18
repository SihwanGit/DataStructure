#include "arraystack.h"

int main() {

	char c, e;
	printf("********** Command **********\n");
	printf("+<c>: Push c, -: Pop, \n");
	printf("S: Show, Q: Quit\n");
	printf("*****************************\n");
	while (1) {
		printf("\nCommand> ");
		c = _getch();
		_putch(c);
		c = toupper(c);
		switch (c) {
		case '+':
			e = _getch();
			_putch(e);
			push(e);
			break;
		case '-':
			e = pop();
			if (e != NULL)
				printf("\n%c \n", e);
			break;
		case 'S':
			stack_show();
			break;
		case 'Q':
			printf("\n");
			exit(1);
		default: break;
		}
	}
}

// main 밑에 나머지 세 함수 구현
void push(Element e) {
	stack[++top] = e;
}

Element pop() {
	if (top == -1) {
		printf("\nStack is Empty");
	}
	else {
		return stack[top--];
	}
}

void stack_show() {
	printf("\n");
	if (top == -1) {
		printf("Stack is Empty\n");
	} else {
		for (int i = 0; i <= top; i++) {
			printf("%c ", stack[i]);
		}
	}
}