#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "Linked List.h"

void main()
{
	char c, e;
	list_pointer head, p;

	// dummy head 노드 
	head = (list_pointer)malloc(sizeof(list_node));
	head->data = NULL;
	head->link = NULL;
    //head에는 데이터가 안들어간다. link만 존재.

	while (1) {
		printf("\nCommand> ");
		c = _getch();
		_putch(c);
		c = toupper(c);
        switch (c) {
        case '+':
            e = _getch();
            _putch(e);
            list_insert(head, e); break;
        case '-':
            e = _getch();
            _putch(e);
            list_delete(head, e); break;
        case '?':
            e = _getch();
            _putch(e);
            p = list_search(head, e);
            if (p) {
                printf("\n%c is in the list. \n", e);
                printf("Node address = %p, data = %c, link = %p \n", p, p->data, p->link);
            }
            else printf("\n%c is not in the list \n", e);
            break;
        case 'S':
            printf("\n");
            list_show(head); 
            printf("\n");
            break;
        case 'Q':
            printf("\n");
            exit(1);
        default:  break;
        }
    }
    free(head);
}

void list_insert(list_pointer head, Element e) {
    list_pointer p;
    p = (list_pointer)malloc(sizeof(list_node)); //p노드 생성, 해제는 delete 시
    p->data = e;
    p->link = head->link;
    head->link = p;
}
//삽입 전: head -> NULL 삽입 후: head -> p -> NULL

void list_delete(list_pointer head, Element e) {
    list_pointer pre = NULL; //이전노드
    list_pointer cur = head; //현재
    while (cur != NULL) { //현재가 NULL이 될 떄까지
        if (cur->data == e) {
            pre->link = cur->link;
            free(cur);
            return; //void를 종료시키고 싶다면 이렇게 하면 되는구나
        }
        pre = cur;
        cur = cur->link;
    }
}

list_pointer list_search(list_pointer head, Element e) {
    list_pointer p = head;
    while (p != NULL) {
        if (p->data == e) {
            return p;
        }
        p = p->link;
    }
    return NULL;
}

bool list_empty(list_pointer head) {
    if ((head->data == NULL)&&(head->link == NULL))
        return true;
    else
        return false;
}

void list_show(list_pointer head) {
    list_pointer p = head;
    if (list_empty(p) == true) {
        printf("List is empty");
    } else {
        while (p != NULL) {
            printf("%c ", p->data);
            p = p->link;
        }
    }
}
