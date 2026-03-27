#include"binary tree.h"

void main()
{
	char c;
	int n;
	tree_pointer t;

	t = build_simple_tree();

	printf("************* Command ************\n");
	printf("C: Count tree, A:  Sum tree data    \n");
	printf("H: Height of tree, S: Show preorder \n");
	printf("F: Free tree, Q: Quit              \n");
	printf("**********************************\n");

	while (1) {
		printf("\nCommand> ");
		c = _getch();
		_putch(c);
		c = toupper(c);
		switch (c) {
		case 'C': //전체 개수
			n = bt_count(t);
			printf("\n Total number of node = %d \n", n);
			break;
		case 'A': //데이터 합
			n = bt_sum(t);
			printf("\n Sum of tree data = %d \n", n);
			break;
		case 'H': //높이
			n = bt_height(t);
			printf("\n Height of tree = %d \n", n);
			break;
		case 'S': //전위순회
			printf("\n");							
			bt_show_preorder(t);
			printf("\n");
			break;
		case 'F': //노드 반환
			printf("\n");
			bt_free(t);
		case 'Q': //종료
			printf("\n");
			exit(1);
		default: break;
		}
	}
}

int bt_count(tree_pointer ptr) { // 트리의 노드수를 계산
	int count = 0;
	if (ptr->left == NULL && ptr->right == NULL) { //단말이면
		return 1;
	}
	else { //단말이 아니면
		count = 1 + bt_count(ptr->left) + bt_count(ptr->right);
		return count;
	}
}

int bt_sum(tree_pointer ptr) { // 트리의 데이터 합을 계산
	int add = 0;
	if (ptr->left == NULL && ptr->right == NULL) {
		return ptr->data;
	}
	else {
		add = ptr->data + bt_sum(ptr->left) + bt_sum(ptr->right);
		return add;
	}
}

int bt_height(tree_pointer ptr) { // 트리의 높이를 계산
	int height = 0;
	if (!(ptr->left == NULL && ptr->right == NULL)) { //단말이 아니면 return 1+max
		height = 1 + max(bt_height(ptr->left), bt_height(ptr->right));
		return height;
	}
	else return 1; //만약 단말이면 return 1
}

void bt_show_preorder(tree_pointer ptr) { // 트리의 내용을 preorder로 출력
	if (ptr->left == NULL && ptr->right == NULL) {
		printf("%d ", ptr->data);
	}
	else {
		printf("%d ", ptr->data);
		bt_show_preorder(ptr->left);
		bt_show_preorder(ptr->right);
	}
}

void bt_free(tree_pointer ptr) { // 트리의 모든 노드를 시스템에반환(free)
	if (ptr->left == NULL && ptr->right == NULL) {
		printf("free node with item %d\n", ptr->data);
		free(ptr);
		return;
	}
	else {
		bt_free(ptr->left); //해제를 하면 해제가 된거지 자식이 NULL이 된건 아님.
		ptr->left = NULL; //그래서 자식을 NULL로 바꿔줌.
		bt_free(ptr->right);
		ptr->right = NULL;
		bt_free(ptr); //자식을 전부 NULL로 바꾼 다음 또 재귀사용(본인이 해제 될 것.)
	}
}

tree_pointer build_simple_tree() {    // 앞에 정의된 7개의 노드를 갖는 binary tree를 생성
	tree_pointer root = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n2 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n3 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n4 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n5 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n6 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n7 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n8 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n9 = (tree_pointer)malloc(sizeof(tree_node));
	root->data = 10;
	root->left = n2; n2->data = 20; n2->left = n4; n2->right = n5;
	root->right = n3; n3->data = 30; n3->left = n6; n3->right = n7;
	n4->data = 40; n4->left = n8; n4->right = n9;
	n5->data = 50; n5->right = NULL; n5->left = NULL;
	n6->data = 60; n6->left = NULL; n6->right = NULL;
	n7->data = 70; n7->left = NULL; n7->right = NULL;
	n8->data = 80; n8->left = NULL; n8->right = NULL;
	n9->data = 90; n9->left = NULL; n9->right = NULL;
	return root;
}