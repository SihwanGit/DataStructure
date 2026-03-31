#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "adj_list.h"

void main()
{
	char c;
	int	i, v;
	front = rear = NULL;

	build_simple_graph();
	printf("\n Graph is built. V = 5, E = 6.\n\n");
	printf("********* Command ********\n");
	printf("D: DFS, B: BFS, Q: Quit \n");
	printf("**************************\n");

	while (1) {
		printf("\nCommand> ");
		c = getch();
		putch(c);
		c = toupper(c);
		switch (c) {
		case 'D':
			printf("\n Start vertex: ");
			scanf("%d", &v);
			for (i = 0; i < MAX_VERTICES; i++) visited[i] = false;
			dfs(v);
			printf("\n");
			break;
		case 'B':
			printf("\n Start vertex: ");
			scanf("%d", &v);
			for (i = 0; i < MAX_VERTICES; i++) visited[i] = false;
			bfs(v);
			printf("\n");
			break;
		case 'Q':
			printf("\n");
			exit(1);
		default: break;
		}
	}
}

void addq(Element e) {
	queue_pointer p = (queue_pointer)malloc(sizeof(queue));
	p->item = e;
	p->link;
	if (front == rear && rear == NULL) {
		front->link = p;
		rear->link = p;
	}
	else {
		rear->link->link = p;
		rear->link = p;
	}
}

Element deleteq() {

}

boolean is_queue_empty() {

}
