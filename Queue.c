#define _CRT_SECURE_NO_WARNINGS
#include "Queue.h"

void main() {
	char c, e;
	while (1) {
		printf("\nCommand> ");
		scanf("%c", &c);
		c = toupper(c); //c를 대문자로 변환
		switch (c) {
		case '+':
			scanf("%c", &e);
			rewind(stdin);
			addq(e);
			break;
		case '-':
			e = deleteq();
			if (is_empty != true)
				printf("\n %c ", e);
			rewind(stdin);
			break;
		case 'S':
			queue_show();
			rewind(stdin);
			break;
		case 'Q': printf("\n");
			exit(1);
		default: break;
		}
	}
}

//front가 맨 앞의 인덱스를 그대로 가리키면 큐가 비어있을 떄와 가득찼을 때를 구분할 수 없다.
//그래서 front가 큐의 맨 앞 인덱스 -1을 가지고 있어야되는데...
//이 문제는 크기가 10으로 고정된 상태에서 원소 10개를 넣어야되므로 일반적인 코드론 오류가 나고,
//그래서 나는 다른 방식으로 접근했다.

//삽입을 할 때마다 rear는 계속 상승하고, newrear = rear % 10을 해서 queue[newrear] = e를 한다.
//마찬가지로 front는 삭제를 할 때마다 계속 상승하고 newfront = front % 10 을 해서 return queue[newfront];를 한다.
//이럼 rear와 front가 같으면 무조건 큐가 비어있는거고 rear - front >= 10이면 큐가 가득찬 것이므로 코드가 꼬이지 않는다.

void addq(Element e) {
	int newrear;
	if (rear - front >= MAX_SIZE) {
		printf("Queue is full!\n");
	} else {
		newrear = rear % MAX_SIZE;
		queue[newrear] = e;
		rear++;
	}
}

Element deleteq() {
	int newfront;
	if (front == rear) {
		printf("Queue is empty!!!\n");
	} else {
		newfront = front % MAX_SIZE;
		front++;
		return queue[newfront];
	}
}

void queue_show() {
	int newfront, newrear;
	newfront = front % MAX_SIZE;
	newrear = rear % MAX_SIZE;
	if (front == rear) {
		printf("Queue is empty\n");
	}
	else {
		for (int i = 0; i < rear - front; i++) {
			printf("%c ", queue[(newfront + i) % MAX_SIZE]);
		}
	}
}