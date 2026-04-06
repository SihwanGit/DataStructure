#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>

typedef struct LinkNode {
	double data; //데이터 섹터
	int index; //이중연결리스트 노드들의 인덱스
	struct LinkNode* right; //오른쪽 링크
	struct LinkNode* left; //왼쪽 링크
} LinkNode;

void input(double n [], int * pc); //정수를 최대 20번 입력하는 함수
int natureError(double n[], int * pc); //자연수 판별 함수
LinkNode* insertFront(LinkNode* head, double n[], int* pc); //이중 연결리스트에 노드들을 삽입할 함수
void print(LinkNode* head); //이증 연결리스트의 노드들을 앞에서부터 출력해줄 함수
void init(LinkNode* head); //헤드를 초기화 함수
LinkNode* change(LinkNode* head, int index1, int index2, int* pc); //이중 연결리스트의 원소들을 교환할 함수
void freeList(LinkNode* head); //동적할당 해제 함수

int main() {
	double n[20];
	int count = 0; //n은 입력할 자연수
	int *pc = &count; //count는 입력된 자연수의 개수
	do {
		input(n, pc);
		if (natureError(n, pc) == -1) printf("Error: 잘못된 입력이 있습니다. 자연수만 입력해 주세요.\n");
	}while(natureError(n, pc) == -1);

	printf("입력 결과: ");
	for (int i = count-1; i > 0; i--) printf("%.0f > ", n[i]);
	printf("%.0f\n", n[0]);

	LinkNode* head = (LinkNode*)malloc(sizeof(LinkNode)); //head 포인터
	init(head);
	head = insertFront(head, n, pc); //이중연결리스트 삽입

	int c1, c2;
	char c[3];
	while (1) {
		printf("위치 변경(형식: 인덱스1 인덱스 2, 종료: q): ");

		scanf("%s", &c);
		if (c[0] == 'q') break; //만약에 입력이 q면 종료
		c1 = atoi(c); //숫자면 atoi
		scanf("%s", &c);
		if (c[0] == 'q') break; //만약에 입력이 q면 종료
		c2 = atoi(c); //숫자면 atoi

		head = change(head, c1, c2, pc);
		rewind(stdin); //버퍼 비우기
	}
	printf("최종 결과: ");
	print(head);
	freeList(head);
	return 0;
}

void input(double n [], int * pc) {
	*pc = 0;
	printf("자연수 리스트 입력(최대 20개, -1로 종료): ");
	for (int i = 0; i < 20; i++) {
		scanf("%lf", &n[i]);
		if (n[i] == -1) break;
		(*pc)++;
	}
}

int natureError(double n[], int * pc) {
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
		p->index = *(pc)- (i+1); //인덱스는 뒤에서부터
		p->right = head; //head와 p를 서로 연결
		head->left = p;
		head = p;
	}
	return head;
}

void print(LinkNode* head) {
	LinkNode* p = head;
	for (p; p->right->right != NULL; p = p->right) { //맨 마지막 노드는 아무런 data도 가지지 않으므로 p->right != NULL까지 반복
		printf("%.0lf > ", p->data);
	}
	printf("%.0lf\n", p->data);  //마지막 직전 노드는 " > "를 출력하지 않음.
}

void init(LinkNode* head) {
	head->right = NULL;
	head->left = NULL;
}

LinkNode* change(LinkNode* head, int index1, int index2, int *pc) {
	LinkNode *p = head, * q = head;
	double temp;

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
		while (p->index != index1) p = p->right;
		while (q->index != index2) q = q->right;

		temp = q->data;
		q->data = p->data;
		p->data = temp;
		//여기까진 정상 작동
		print(head);
		return head;
	}
}

void freeList(LinkNode * head) {
	LinkNode* temp = head, *next;
	while (temp != NULL) {
		next = temp->right;  // 현재 노드의 다음 노드를 임시로 저장
		free(temp);         // 현재 노드 메모리 해제
		temp = next;         // 다음 노드로 이동
	}
}

