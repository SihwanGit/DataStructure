#include<stdio.h>

int find_size(int score[10], int size) {
	int max = 0;
	for (int i = 0; i < 10; i++) {
		if (score[i] >= score[max]) {
			max = i;
		}
	}
	return max;
}

int main() {
	int score[10] = { 55, 20, 33, 85, 13, 22, 45, 98, 67, 77 };
	for (int i = 0; i < 10; i++) {
		printf("%d 번: %d 점\n", i, score[i]);
	}
	int max = find_size(score, 10);
	printf("1등은 %d 번, 성적은 %d 입니다.\n", max, score[max]);
	return 0;

}