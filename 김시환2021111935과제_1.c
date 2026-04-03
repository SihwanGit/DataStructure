#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct { //다항식 구조체
	float coef;	 //계수
	int x_expon; //x의 차수
	int y_expon; //y의 차수
} polynomial;

void poly_input(polynomial* p, int n); //다항식 입력
void poly_print(polynomial* p, int n); //다항식 출력
void poly_mul(polynomial* pA, polynomial* pB, polynomial* pC, int An, int Bn); //다항식 곱
void poly_sort(polynomial* p, int n); //다항식 정렬

int main() {
	int An, Bn, Cn; //다항식 A,B의 항의 개수
	polynomial* pA, * pB, *pC;
	
	printf("다항식 A를 입력하세요 : \n");
	printf("다항식의 항의 개수를 입력하세요 : ");
	scanf_s("%d", &An);
	pA = (polynomial*)malloc(sizeof(polynomial) * An); //입력한 항의 수만큼 동적할당
	if (!pA) { //메모리 할당 실패시 프로그램 종료
		printf("메모리를 할당할 수 없습니다.");
		return 0;
	}
	poly_input(pA, An);	//다항식 A 입력
	printf("\n");

	printf("다항식 B를 입력하세요 : \n");
	printf("다항식의 항의 개수를 입력하세요 : ");
	scanf_s("%d", &Bn);
	pB = (polynomial*)malloc(sizeof(polynomial) * Bn); //입력한 항의 수만큼 동적할당
	if (!pB) { //메모리 할당 실패시 프로그램 종료
		printf("메모리를 할당할 수 없습니다.");
		return 0;
	}
	poly_input(pB, Bn);	//다항식 B 입력
	printf("\n");

	Cn = An * Bn;
	pC = (polynomial*)malloc(sizeof(polynomial) * Cn);
	if (!pB) { //메모리 할당 실패시 프로그램 종료
		printf("메모리를 할당할 수 없습니다.");
		return 0;
	}

	//다항식 출력
	printf("다항식 A: ");
	poly_print(pA, An);
	printf("\n");
	printf("다항식 B: ");
	poly_print(pB, Bn);
	printf("\n");
	poly_mul(pA, pB, pC, An, Bn);
	printf("다항식 C: ");
	poly_sort(pC, Cn);
	poly_print(pC, Cn);
	printf("\n");

	free(pA); //pA해제
	free(pB); //pB해제
	free(pC); //pC해제
	return 0;
}

void poly_input(polynomial* p, int n) { //다항식 입력
	for (int i = 0; i < n; i++) {
		printf("다항식의 항을 계수 x지수 y지수 형식으로 하나씩 입력해주세요(예시 : 3y^7의 경우 3 0 7로 입력) : ");
		scanf_s("%f %d %d", &(p + i)->coef, &(p + i)->x_expon, &(p + i)->y_expon);
	}
}

void poly_print(polynomial* p, int n) { //다항식 출력
	//맨 처음항 출력
	if (p->coef != 0) {
		if ((p->x_expon == 0) && (p->y_expon != 0)) printf("%.1fy^%d", p->coef, p->y_expon);
		else if ((p->y_expon == 0) && (p->x_expon != 0)) printf("%.1fx^%d", p->coef, p->x_expon);
		else if ((p->x_expon == 0) && (p->y_expon == 0)) printf("%.1f", p->coef);
		else printf("%.1fx^%dy^%d", p->coef, p->x_expon, p->y_expon); //맨 처음항 출력
	}

	//2번째 이후의 항 출력
	for (int i = 1; i < n; i++) {
		if ((p + i)->coef > 0) { //만약 항의 계수가 0보다 크면 항 앞에 +를 붙여서 출력
			if (((p + i)->x_expon == 0) && ((p + i)->y_expon != 0)) { //x지수가 0이면 y^n만 출력
				printf(" +%.1fy^%d", (p + i)->coef, (p + i)->y_expon);
			}
			else if (((p + i)->y_expon == 0) && ((p + i)->x_expon != 0)) {//y지수가 0이면 x^n만 출력
				printf(" +%.1fx^%d", (p + i)->coef, (p + i)->x_expon);
			}
			else if (((p + i)->x_expon == 0) && ((p + i)->y_expon == 0)) { //x,y의 지수가 0이면 계수만 출력
				printf(" +%.1f", (p + i)->coef);
			}
			else { //그렇지 않다면 x^ny^n으로 출력
				printf(" +%.1fx^%dy^%d", (p + i)->coef, (p + i)->x_expon, (p+i)->y_expon);
			}
		}
		else if ((p + i)->coef < 0) { //항의 계수가 0보다 작으면 그냥 출력
			if (((p + i)->x_expon == 0) && ((p + i)->y_expon != 0)) { //x지수가 0이면 y^n만 출력
				printf(" %.1fy^%d", (p + i)->coef, (p + i)->y_expon);
			}
			else if (((p + i)->y_expon == 0) && ((p + i)->x_expon != 0)) {//y지수가 0이면 x^n만 출력
				printf(" %.1fx^%d", (p + i)->coef, (p + i)->x_expon);
			}
			else if (((p + i)->x_expon == 0) && ((p + i)->y_expon == 0)) { //x,y의 지수가 0이면 계수만 출력
				printf(" %.1f", (p + i)->coef);
			}
			else { //그렇지 않다면 x^ny^n으로 출력
				printf(" %.1fx^%dy^%d", (p + i)->coef, (p + i)->x_expon, (p + i)->y_expon);
			}
		}
	}
}

void poly_mul(polynomial* pA, polynomial* pB, polynomial* pC, int An, int Bn) { //다항식 곱
	int k = 0;
	for (int i = 0; i < An; i++) {
		for (int j = 0; j < Bn; j++) {
			(pC + k)->coef = (pA + i)->coef * (pB + j)->coef;
			(pC + k)->x_expon = (pA + i)->x_expon + (pB + j)->x_expon;
			(pC + k)->y_expon = (pA + i)->y_expon + (pB + j)->y_expon;
			k++;
		}
	}
}

void poly_sort(polynomial* p, int n) { //다항식 정렬
	polynomial temp;
	for (int i = n - 1; i > 0; i--) { //정렬은 버블정렬 사용.
		for (int j = 0; j < i; j++) {
			if ((p + j)->x_expon < (p + (j + 1))->x_expon) {
				temp = *(p + j);
				*(p + j) = *(p + j + 1); //x의 내림차순 정렬
				*(p + j + 1) = temp;
			}
			else if (((p + j)->x_expon == (p + j + 1)->x_expon) && ((p + j)->y_expon < (p + j + 1)->y_expon)) {
				temp = *(p + j);
				*(p + j) = *(p + (j + 1)); //x의 내림차순 정렬
				*(p + j + 1) = temp;
			}
			else if (((p + j)->x_expon == (p + j + 1)->x_expon) && ((p + j)->y_expon == (p + j + 1)->y_expon)) {
				(p + j + 1)->coef += (p + j)->coef; //계수가 같으면 두 항의 계수를 합산
				(p + j)->coef = 0;
			}

			//if ((p + j)->x_expon == (p + j + 1)->x_expon) { //x의 지수가 같다면 y의 내림차순 정렬
			//}
		}
	}
}
