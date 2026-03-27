#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst_dictionary.h"
void main()
{
	char c, fname[20];
	char w1[100], * w2;
	int	wcount;

	printf("************* Command ************\n");
	printf("R: Read data, S: Search data    \n");
	printf("P: Print inorder, Q: Quit         \n");
	printf("**********************************\n");
	while (1) {
		printf("\nCommand> ");
		c = _getch();
		_putch(c);
		c = toupper(c);
		switch (c) {
		case 'R':
			printf("\n Dictionary file name: ");
			scanf("%s", fname);
			wcount = build_dictionary(fname);
			printf(" Total number of words: %d \n", wcount);
			break;
		case 'S':
			printf("\n Word: ");
			scanf("%s", w1);
			w2 = bst_search(w1);
			if (w2) printf(" Meaning: %s \n", w2);
			else printf(" No such word ! \n");
			break;
		case 'P':
			printf("\n");
			bst_show_inorder(root);
			break;
		case 'Q':
			printf("\n");
			exit(1);
		default: break;
		}
	}
}

int build_dictionary(char* fname) {
	int cnt = 0; char w1[100], w2[100];
	tree_pointer new = (tree_pointer)malloc(sizeof(tree_node));
	FILE* f;
	if ((f = fopen(fname, "r")) == NULL) {
		return 0;
	}
	while (fscanf(f, "%s %s", new->w1, new->w2) != EOF) {
		cnt++;
		bst_insert(new->w1, new->w2);
	}
	fclose(f);
	return cnt;
}
void bst_insert(char* w1, char* w2) {
	tree_pointer prev = NULL;
	tree_pointer curr = root;
	tree_pointer temp = (tree_pointer)malloc(sizeof(tree_node));
	while (curr) {
		if (strcmp(w1, curr->w1) == 0) return;
		prev = curr;
		if (strcmp(w1, curr->w1) < 0) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
	strcpy(temp->w1, w1); strcpy(temp->w2, w2);
	temp->left = temp->right = NULL;
	if (prev) {
		if (strcmp(w1, prev->w1) < 0) prev->left = temp;
		else prev->right = temp;
	}
	else root = temp;
}
char* bst_search(char* w1) {
	tree_pointer temp = root;
	while (temp) {
		if (strcmp(w1, temp->w1) == 0) return temp->w2;
		if (strcmp(w1, temp->w1) < 0) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	return NULL;
}
void bst_show_inorder(tree_pointer ptr) {
	if (ptr == NULL) return;
	bst_show_inorder(ptr->left);
	printf("%s %s\n", ptr->w1, ptr->w2);
	bst_show_inorder(ptr->right);
}

