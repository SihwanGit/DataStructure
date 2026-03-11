#define _CRT_SECURE_NO_WARNINGS
#include"ex2.h"

int main() {
	char c;
	printf("Reading record from %s\n", fname);
	read_record(fname);
	printf("%d records have read.\n", num_record);

	printf("********** 명령어 ********** \n");
	printf("P: Print all records \n");
	printf("S : Search record \n");
	printf("C : Change record \n");
	printf("W : Write record \n");
	printf("Q : Save and quit \n");
	printf("****************************** \n");

	while (1) {
		printf("\nCommand> ");
		rewind(stdin);
		c = getchar();
		c = toupper(c);
		printf("\n");

		switch (c) {
		case 'P':
			print_record();
			break;
		case 'S':
			search_record();
			break;
		case 'C':
			change_record();
			break;
		case 'W':
			write_record(fname);
			break;
		case 'Q':
			printf("\n");
			exit(1);
			break;
		default:
			printf("Unknown command ! \n");
			break;
		}
	}
	return 0;
}

void read_record(const char* fname) {
	int i = 0;
	FILE* ifp;

	ifp = fopen(fname, "r"); //뒤의 r은 읽기모드
	while (fscanf(ifp, "%s %d %s", r[i].name, &r[i].id, r[i].grade) == 3) ++i;
	//printf()와 scanf()함수의 반환값은 그들이 읽은 변수의 수다.
	//fscanf() == 3은 3개의 수를 읽었다는 것이다.

	num_record = i; //전역변수
	fclose(ifp);
}

void print_record() {
	int i = 0;
	while (i < 4) {
		printf("%s %d %s\n", r[i].name, r[i].id, r[i].grade);
		i++;
	}
}
	
void search_record() {
	char namename[10];
	printf("Search name: ");
	scanf("%s", &namename);
	int i = 0;
	while (strcmp(r[i].name, namename) != 0) { //입력한 이름이 구조체에 없으면 반복
		i++;
		if (i >= 4) { //모든 이름을 찾아도 없다면
			printf("No record found for %s! Please confirm name\n", namename); //Error 메세지 출력
			break; //반복문 탈출
		}
	}
	if (strcmp(r[i].name, namename) == 0) { //만약 검색한 이름이 있다면
		printf("%s %d %s\n", r[i].name, r[i].id, r[i].grade);  //학생 정보 출력
	}
}

void change_record() {
	int i = 0;
	char namename[10];

	printf("Search name: ");
	scanf("%s", &namename);
	while (strcmp(r[i].name, namename) != 0) { //입력한 이름이 구조체에 없으면 반복
		i++;
		if (i >= 4) { //모든 이름을 찾아도 없다면
			printf("No record found for %s! Please confirm name\n", namename); //Error 메세지 출력
			break; //반복문 탈출
		}
	}
	if (strcmp(r[i].name, namename) == 0) { //입력한 이름이 메모장에 있으면
		printf("Grade: ");
		scanf("%s", &r[i].grade); //바꾸고 싶은 점수 입력
	}
}

void write_record(const char* fname) {
	int i = 0;
	FILE* ifp;
	ifp = fopen(fname, "w+");
	while (i < 4) {
		fprintf(ifp, "%s %d %s\n", r[i].name, &r[i].id, r[i].grade);
		i++;
	}
	printf("%d records have written to grade.txt.\n", i);
	fclose(ifp); 
}
