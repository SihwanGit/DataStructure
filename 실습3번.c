#include<stdio.h>

int main() {
	int score[10] = { 55, 20, 33, 85, 13, 22, 45, 98, 67, 77 };
	for (int i = 0; i < 10; i++) {
		printf("%d 번: %d 점\n", i, score[i]);
	}

	//find max
	int max = 0;
	for (int i = 0; i < 10; i++) {
		if (score[i] >= score[max]) {
			max = i;
		}
	}
	printf("1등은 %d 번, 성적은 %d 입니다.\n", max, score[max]);

	return 0;

}