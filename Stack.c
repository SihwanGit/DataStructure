#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define Size 101 //최대 크기

typedef char element;
typedef struct {
	element OpData[Size]; //연산자 저장 스택
	int NumData[Size]; //숫자 저장 스택
	int OpTop; //연산자 top
	int NumTop; //숫자 top
} StackType;

//초기화
void init_stack(StackType* s);

//연산자 스택 관련 함수
int Op_is_empty(StackType* s);
int Op_is_full(StackType* s);
void Op_push(StackType* s, element item);
element Op_pop(StackType* s);
element Op_peek(StackType* s);

//정수 스택 관련 함수
int Num_is_enpty(StackType* s);
int Num_is_full(StackType* s);
void Num_push(StackType* s, int item);
int Num_pop(StackType* s);
int Num_peek(StackType* s);

void cal(StackType* s) {
	int a, b, c;
	char op;
	b = Num_pop(s);
	a = Num_pop(s);
	if (Op_peek(s) == '+') {
		c = a + b;
		op = Op_pop(s); //연산 끝나고 연산자 pop
		Num_push(s, c); //연산 끝난 정수값을 다시 push
		//pop에 공백 검사 코드가 있어서 한 번 더 안하는거.
	}
	else if (Op_peek(s) == '-') {
		c = a - b;
		op = Op_pop(s);
		Num_push(s, c);
	}
	else if (Op_peek(s) == '*') {
		c = a * b;
		op = Op_pop(s);
		Num_push(s, c);
	}
	else if (Op_peek(s) == '/') {
		c = a / b;
		op = Op_pop(s);
		Num_push(s, c);
	}
}

void StackPrint(StackType* s) { //두 스택의 값을 출력해줄 함수
	printf("Operand Stack: ");
	for (int i = 0; i <= s->NumTop; i++) {
		printf("%d ", s->NumData[i]);
	}
	printf("\nOperator Stack: ");
	for (int i = 0; i <= s->OpTop; i++) {
		printf("%c ", s->OpData[i]);
	}
	printf("\n\n");
}

void infix2StackEval(char exp[]) {
	int i = 0; //인덱스
	element ch;
	int j;
	int len = 0;
	while (exp[len]) len++; //문자열 exp의 길이 len
	StackType s;
	init_stack(&s); // 스택 초기화
	for (i = 0; i < len; i++) {
		ch = exp[i];
		char ch_num[Size] = "\0";
		j = 0;
		switch (ch) {
		case '+': case '-': case '*': case '/': // 연산자 케이스
			//모든 수식이 괄호로 묶이므로 연산자 우선순위는 고려할 필요 없다. 따라서 연산자를 만나면 무조건 push
			Op_push(&s, ch);
			StackPrint(&s);
			break;

		case '(': //왼쪽 괄호는 고려하지 않음.
		case ' ': //띄어쓰기도 고려하지 않음.
			break;
		case ')': // 오른쪽 괄호
			cal(&s); //오른쪽 괄호를 만나면 한 번 계산
			StackPrint(&s);
			break;
		default:
			ch_num[j++] = ch; //ch가 정수면 ch_num 배열에 임시로 넣어놓는다.
			while((exp[i+1] >= '0') && (exp[i+1] <= '9')) {
				//exp[i]가 숫자일 떄 exp[i+1]도 숫자면 두자리수 이상의 숫자인 것이다.
				ch_num[j++] = exp[++i];
			}
			int n = atoi(ch_num); //문자열 ch_num을 정수로 바꿔서 n에 할당 후, n을 정수 스택에 push
			Num_push(&s, n);
			StackPrint(&s);
			break;
		}
	}
	printf("Final result: %d\n", Num_pop(&s));
}

int main() {
	char exp[Size];
	printf("Enter the infix expression (Max length = 100): ");
	scanf("%[^\n]s", exp);
	printf("%s\n\n", exp);
	infix2StackEval(exp);
	return 0;
}

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->OpTop = -1;
	s->NumTop = -1;
}

// 연산자 스택의 공백 상태 검출
int Op_is_empty(StackType* s)
{
	return (s->OpTop == -1);
}

// 정수 스택의 공백 상태 검출
int Num_is_empty(StackType* s) {
	return (s->NumTop == -1);
}

// 연산자 포화 상태 검출 함수
int Op_is_full(StackType* s)
{
	return (s->OpTop == (Size - 1));
}

// 정수 포화 상태 검출 함수
int Num_is_full(StackType* s) {
	return (s->NumTop == (Size - 1));
}

// 연산자 삽입함수
void Op_push(StackType* s, element item)
{
	if (Op_is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->OpData[++(s->OpTop)] = item;
}

// 연산자 삭제함수
element Op_pop(StackType* s)
{
	if (Op_is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->OpData[(s->OpTop)--];
}

// 연산자 peek
element Op_peek(StackType* s) {
	if (Op_is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->OpData[(s->OpTop)];
}

// 정수 삽입함수
void Num_push(StackType* s, int item)
{
	if (Num_is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->NumData[++(s->NumTop)] = item;
}

// 정수 삭제함수
int Num_pop(StackType* s)
{
	if (Num_is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->NumData[(s->NumTop)--];
}

// 정수 peek
int Num_peek(StackType* s) {
	if (Num_is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->NumData[(s->NumTop)];
}