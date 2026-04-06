#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>

typedef struct LinkNode {
	double data; //데이터 섹터
	int index; //이중연결리스트 노드들의 인덱스
	struct LinkNode* right; //오른쪽 링크
	struct LinkNode* left; //왼쪽 링크
} LinkNode;

void input(double n[], int* pc); //정수를 최대 20번 입력하는 함수
int natureError(double n[], int* pc); //자연수 판별 함수
LinkNode* insertFront(LinkNode* head, double n[], int* pc); //이중 연결리스트에 노드들을 삽입할 함수
void print(LinkNode* head); //이증 연결리스트의 노드들을 앞에서부터 출력해줄 함수
void init(LinkNode* head); //헤드를 초기화 함수
//LinkNode* change(LinkNode* head, int index1, int index2); //이중 연결리스트의 원소들을 교환할 함수
LinkNode* change(LinkNode* head, int index1, int index2, int* pc);

int main() {
	double n[20];
	int count = 0; //n은 입력할 자연수
	int* pc = &count; //count는 입력된 자연수의 개수
	do {
		input(n, pc);
		if (natureError(n, pc) == -1) printf("Error: 잘못된 입력이 있습니다. 자연수만 입력해 주세요.\n");
	} while (natureError(n, pc) == -1);

	printf("입력 결과: ");
	for (int i = count - 1; i > -1; i--) printf("%.0f ", n[i]);
	printf("\n");

	LinkNode* head = (LinkNode*)malloc(sizeof(LinkNode)); //head 포인터
	init(head);
	head = insertFront(head, n, pc); //이중연결리스트 삽입
	print(head);

	int c1, c2;
	while (1) {
		printf("위치 변경(형식: 인덱스1 인덱스 2, 종료: q): ");
		scanf("%d", &c1);
		scanf("%d", &c2);
		head = change(head, c1, c2, pc);
		rewind(stdin); //버퍼 비우기
	}

	return 0;
}

void input(double n[], int* pc) {
	*pc = 0;
	printf("자연수 리스트 입력(최대 20개, -1로 종료): ");
	for (int i = 0; i < 20; i++) {
		scanf("%lf", &n[i]);
		if (n[i] == -1) break;
		(*pc)++;
	}
}

int natureError(double n[], int* pc) {
	for (int i = 0; i < (*pc); i++) {
		if ((n[i] - (int)n[i]) != 0) return -1; //소수거나 0, 음수면 -1 리턴
		else if (n[i] <= 0) return -1;
	}
	return 0; //모든 원소가 자연수면 0리턴
}

LinkNode* insertFront(LinkNode* head, double n[], int* pc) { //맨 앞에 삽입하는 함수
	for (int i = 0; i < (*pc); i++) { //0부터 pc까지 반복
		LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
		p->data = n[i];
		p->index = *(pc)-(i + 1); //인덱스는 뒤에서부터
		p->right = head; //head와 p를 서로 연결
		head->left = p;
		head = p;
		printf("%.0f %d\n", head->data, head->index);
	}
	return head;
}

void print(LinkNode* head) {
	LinkNode* p = head;
	for (p; p->right != NULL; p = p->right) { //맨 마지막 노드는 아무런 data도 가지지 않으므로 p->right != NULL까지 반복
		printf("%.0lf ", p->data);
	}
	printf("\n");
}

void init(LinkNode* head) {
	head->right = NULL;
	head->left = NULL;
}

LinkNode* change(LinkNode* head, int index1, int index2, int* pc) {
	LinkNode* temp, * p = head, * q = head;

	if (index1 == index2) { //두 인덱스가 같다면 반환
		print(head);
		return head;
	}
	else if (index1 < 0 || index1 >= *pc) { //범위가 틀리면 반환
		printf("Error: The specified index is out of range. Please enter a valid index.\n");
		print(head);
		return head;
	}
	else if (index2 < 0 || index2 >= *pc) { //범위가 틀리면 반환
		printf("Error: The specified index is out of range. Please enter a valid index.\n");
		print(head);
		return head;
	}
	else { //오류가 없다면
		if (index1 == 0) { //index1이 0일때
			while (q->index != index2) q = q->right;
			temp = q;
			q->right->left = p; //q,p 양 옆에 있는 노드들을 바꿔줌.
			q->left->right = p;
			p->right->left = q;

			q->right = p->right;
			p->right = temp->right;
			p->left = temp->left;
			print(head);
			return head;
		}
		else if (index2 == 0) { //index2가 0일떄
			while (p->index != index1) p = p->right;
			temp = p;
			q->right->left = p; //q,p 양 옆에 있는 노드들을 바꿔줌.
			p->right->left = q;
			p->left->right = q;

			p->right = q->right;
			q->right = temp->right;
			q->left = temp->left;
			print(head);
			return head;
		}
		else { //index1, index2가 모두 0이 아닐 때.
			while (p->index != index1) p = p->right;
			while (q->index != index2) q = q->right;

			printf("%.0f %d\n", p->data, p->index);
			printf("%.0f %d\n\n", q->data, q->index);
			//여기까진 정상 작동

			printf("%.0f %d\n", p->right->left->data, p->right->left->index);
			printf("%.0f %d\n", q->right->left->data, q->right->left->index);
			printf("%.0f %d\n", p->left->right->data, p->left->right->index);
			printf("%.0f %d\n\n", q->left->right->data, q->left->right->index);

			temp = q;
			printf("temp->data = %.0f, temp->index = %d\n", temp->data, temp->index);
			printf("temp->data = %.0f, temp->index = %d\n", temp->right->data, temp->right->index);
			printf("temp->data = %.0f, temp->index = %d\n", temp->left->data, temp->left->index);
			q->right->left = p; //q,p 양 옆에 있는 노드들을 바꿔줌.
			q->left->right = p;
			p->right->left = q;
			p->left->right = q;
			printf("%.0f %d\n", p->right->left->data, p->right->left->index);
			printf("%.0f %d\n", q->right->left->data, q->right->left->index);
			printf("%.0f %d\n", p->left->right->data, p->left->right->index);
			printf("%.0f %d\n\n", q->left->right->data, q->left->right->index);
			//양쪽을 변경한 것까지도 정상 작동

			q->right = p->right;
			q->left = p->left;
			printf("%.0f %d\n", q->right->data, q->right->index);
			printf("%.0f %d\n\n", q->left->data, q->left->index);
			//여기까지도 정상 작동

			printf("temp->data = %.0f, temp->index = %d\n", temp->data, temp->index);
			printf("temp->data = %.0f, temp->index = %d\n", temp->right->data, temp->right->index);
			printf("temp->data = %.0f, temp->index = %d\n", temp->left->data, temp->left->index);

			p->right = temp->right;
			p->left = temp->left;
			printf("%.0f %d\n", p->right->data, p->right->index);
			printf("%.0f %d\n\n", p->left->data, p->left->index);

			print(head);
			return head;
		}
	}
}
