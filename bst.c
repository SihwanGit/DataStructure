#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
void main()
{
	char c, grade;
	int	id;

	printf("************* Command ************\n");
	printf("I: Insert data, S: Search data    \n");
	printf("P: Print inorder, Q: Quit         \n");
	printf("**********************************\n");

	while (1) {
		printf("\nCommand> ");
		c = getch();
		putch(c);
		c = toupper(c);
		switch (c) {
		case 'I':
			printf("\n id and grade: ");
			scanf("%d %c", &id, &grade);
			bst_insert(id, grade);
			break;
		case 'S':
			printf("\n id: ");
			scanf("%d", &id);
			grade = bst_search(id);
			if (grade) printf(" Grade of %d: %c \n", id, grade);
			else printf(" No such id ! \n");
			break;
		case 'P':
			printf("\n");
			bst_show_inorder(root);
			break;
		case 'Q':
			printf("\n");
			exit(1);
		default: break;
		}
	}
}

//여기 함수들은 재귀가 아니여서 p=p->link 형태의 반복문을 사용해야함.

// 트리에 (key, data) 자료 삽입
void bst_insert(int key, char data) {
	tree_pointer ptr = (tree_pointer)malloc(sizeof(tree_node));
	ptr->data = data;
	ptr->key = key;
	ptr->left = NULL;
	ptr->right = NULL;

	if (root == NULL) { //만약 트리가 비어있으면
		root = ptr; //root = ptr
		return;
	}

	tree_pointer p = root;
	while (1) {
		if (p->key == ptr->key) { //key가 같으면 리턴
			return;
		}
		else if (p->key > ptr->key) { //p의 key가 더 크면 왼쪽
			if (p->left == NULL) { //왼쪽이 비어있으면
				p->left = ptr; //그대로 삽입 후 종료
				return;
			}
			else  //비어있지 않다면 다시 반복
				p = p->left;
		}
		else { //p의 key가 더 작으면 오른쪽
			if (p->right == NULL) { //오른쪽이 비어있으면 삽입 후 종료
				p->right = ptr;
				return;
			}
			else //비어있지 않다면 반복
				p = p->right; 
		}
	}
}

// 트리에서 키값이 key인 자료를 검색, data를 반환
char bst_search(int key) {
	tree_pointer p = root;
	while (p) { //p가 NULL이 아닐 때까지
		if (p->key > key) { //p->key가 더 크면
			p = p->left;
		}
		else if (p->key < key) {
			p = p->right;
		}
		else if (p->key == key) {
			return p->data;
		}
	}
}

// 트리의 자료들을 inorder로 출력 
void bst_show_inorder(tree_pointer ptr) { //중위순회
	if (ptr->left == NULL && ptr->right == NULL) {
		printf("%d %c\n",ptr->key, ptr->data);
	}
	else {
		bst_show_inorder(ptr->left);
		printf("%d %c\n", ptr->key, ptr->data);
		bst_show_inorder(ptr->right);
	}
}