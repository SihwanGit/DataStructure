#include "arraylist.h"

int main() {
	char c;

	printf("******************** Command ********************\n");
	printf("+<c>: Insert c, -<c>: Delete c, \n");
	printf("E: ListEmpty, F: ListFull, S: ListShow, Q: Quit \n");
	printf("*************************************************\n");

	while (1) {
		printf("\nCommand> ");
		c = _getche();
		c = toupper(c);

		switch (c) {
		case '+':  //+를 누르면 리스트에 삽입
			c = _getche();
			list_insert(c);
			break;
		case '-': //리스트에서 삭제
			c = _getche();
			list_delete(c);
			break;
		case 'E': //리스트가 비어있는지 확인
			if (list_empty()) printf("\nTRUE \n");
			else printf("\nFALSE \n");
			break;
		case 'F': //리스트가 가득차있는지 확인
			if (list_full()) printf("\nTRUE \n");
			else printf("\nFALSE \n");
			break;
		case 'S': //모든 원소 보여주기
			list_show();
			break;
		case 'Q': //탈출
			printf("\n");
			exit(1);
		default:
			break;
		}
	}
	return 0;
}

boolean list_full()
{
	if (size == MaxSize)
		return true;      // 리스트가 가득 차 있으면 true 
	else
		return false;
}

boolean list_empty() {
	if (size == 0)
		return true; // 리스트가 비어 있으면 true
	else
		return false;
}

void list_insert(char c) {
	if (size >= 3) printf("\nList is full !!!\n");
	else {
		List[size++] = c;
	}
}

void list_delete(char c) { //앞에서부터만 삭제되고, 탐색이 제대로 안됨. //else문과 break가 충돌함.

	for (int i = 0; i < size; i++) { //c의 값이 있는지 탐색
		if (List[i] == c) { //c를 찾으면 
			for (int j = i; j < size; j++) { //그 뒤쪽에 있는 배열의 값들을 앞으로 한칸 씩 가져옴.
				List[j] = List[j + 1]; 
			}
			size--; //size를 줄임.
			break;
		}
		else { //만약 c가 없다면...
			if (i < size-1) continue; //끝까지 검사 안했으면 다시 루프
			else {
				printf("\nData does not exist !!!\n"); //끝까지 검사했는데 안나오면 없다고 출력
				break;
			}
		}
	}
}

void list_show() {
	printf("\n");
	if (size == 0) printf("List is Empty !!!");
	else {
		for (int i = 0; i < size; i++) {
		printf("%c ", List[i]); //0부터 size-1까지 모두 출력
		}
		printf("\n");
	}
}