#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<conio.h>
#include "max_heap.h"

void main() {
	char c, data;
	int	key;
	Element	item;

	printf("************* Command ************ \n");
	printf("I: Insert data, D: Delete max data \n");
	printf("P: Print heap, Q: Quit             \n");
	printf("********************************** \n");

	while (1) {
		printf("\nCommand> ");
		c = _getch();
		_putch(c);
		c = toupper(c);
		switch (c) {
		case 'I':
			printf("\n key and data: ");
			scanf("%d %c", &key, &data);
			item.key = key;
			item.data = data;
			insert_max_heap(item);
			break;
		case 'D':
			if (is_heap_empty())
				printf("\nHeap is empty\n");
			else {
				item = delete_max_heap();
				printf("\n Max: key %d, data %c \n", item.key, item.data);
			}
			break;
		case 'P':
			printf("\n");
			max_heap_show();
			break;
		case 'Q':
			printf("\n");
			exit(1);
		default: break;
		}
	}
}

/*
// Global heap
Element heap[MAX_SIZE]; //구조체 배열
int heap_size = 0;
*/

// 히프에 item(key, data) 삽입
void insert_max_heap(Element item) {
	Element temp; //교환용 노드 temp
	int i = heap_size; //i는 heap_size

	if (is_heap_empty() == true) { //heap이 비어있으면 맨 앞에 삽입
		heap[++heap_size] = item;
	}
	else {
		heap[++heap_size] = item; //일단 삽입하기
		while (i != 1) {
			if (heap[i / 2].key < heap[i].key) { //부모의 키가 자식의 키보다 작으면
				temp = heap[i];
				heap[i] = heap[i / 2];
				heap[i / 2] = temp;
			} //부모와 자식 교환
			i = i / 2;
		}
	}
}

// 히프에서 max item (루트) 삭제 및 반환
Element delete_max_heap() {
	int i = 1; //루트로 옮겨진 노드의 주소
	Element ptr = heap[1];
	Element temp;
	heap[1] = heap[heap_size]; //가장 말단을 루트에 삽입
	while (1) {
		if (heap[i].key < heap[i * 2].key && i * 2 <= heap_size) { //왼쪽 자식의 key가 부모보다 크고 i*2가 size 이하면
			temp = heap[i];
			heap[i] = heap[i * 2];
			heap[i * 2] = temp; //서로 교환
			i *= 2;
		} 
		if (heap[i].key < heap[i * 2 + 1].key && i*2+1 <= heap_size) { //오른쪽 자식의 key가 부모보다 크고 i*2+1이 size 이하면
			temp = heap[i];
			heap[i] = heap[i * 2 + 1];
			heap[i * 2 + 1] = temp; //서로 교환
			i = 2 * i + 1;
		}
		else { //부모가 왼/오의 key보다 크다면 그대로 끝
			break;
		}
	}
	heap_size--; //한개 삭제했으니 크기 줄이기.
	return ptr;
}

// 히프의 자료들을 차례로 출력 
void max_heap_show() {
	for (int i = 1; i <= heap_size; i++) {
		printf("%d %c\n", heap[i].key, heap[i].data);
	}
}

boolean is_heap_empty() {
	if (heap_size == 0) return true; //만약 heap size가 0이면 비어있다.
	else return false;
}

//연결리스트가 아닌 배열로 문제를 품.
