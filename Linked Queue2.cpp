#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "Linked Queue.h"

void main()
{
	char	c, e;
	front = rear = NULL;
	// … command 입력부분 작성
	while (1) {
		printf("\nCommand> ");
		c = _getch();
		_putch(c);
		c = toupper(c);
		switch (c) {
		case '+':
			e = _getch(); _putch(e);
			addq(e);
			break;
		case '-':
			if (is_queue_empty()) {
				printf("\n Queue is empty !!! \n");
			}
			else {
				e = deleteq();
				printf("\n %c ", e);
			}
			break;
		case 'S':
			queue_show();
			break;
		case 'Q': printf("\n"); exit(1);
		default: break;
		}
	}
}

void addq(Element e) {
	queue_pointer p = (queue_pointer)malloc(sizeof(queue));
	p->item = e;
	if (is_queue_empty()) { //만약 리스트가 비어있는 상태였다면
		p->link = NULL;
		front = p; //front와 rear를 모두 p로 초기화
		rear = p;
	}
	else { //비어있지 않은 상태라면
		p->link = NULL;
		rear->link = p; //rear를 p랑 연결한 다음에 rear = p;
		rear = p;
	}
}

Element deleteq() {
	if (is_queue_empty()) {
		printf("\nQueue is Empty!\n"); //만약 비어있으면 그대로 종료
		return '\0';
	}
	Element c;
	queue_pointer p = (queue_pointer)malloc(sizeof(queue));
	p = front;
	front = front->link; //front를 뒤로 한칸 이동시킴
	c = p->item;
	free(p);
	return c;
}

void queue_show() {
	if (is_queue_empty()) {
		printf("\nQueue is Empty!\n"); //비어있으면 비어있다고 출력 후 종료
		return;
	}
	printf("\n");
	queue_pointer p = front;
	do { //그렇지 않다면 front부터 NULL이 될 떄까지 계속 item 출력
		printf("%c ", p->item);
		p = p->link;
	} while (p != NULL);
	printf("\n");
}

boolean is_queue_empty() {
	if (front == NULL) { //front가 NULL이면 공백
		return true;
	}
	else return false;
}