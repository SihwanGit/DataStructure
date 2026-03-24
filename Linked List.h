#pragma once

#define	Element	char
#define	bool	unsigned char
#define	true	1
#define	false	0

typedef	struct list_node* list_pointer;
typedef	struct list_node {
	Element	data;
	list_pointer link;
} list_node;

void list_insert(list_pointer head, Element e);
void list_delete(list_pointer head, Element e);
list_pointer list_search(list_pointer head, Element e);
bool list_empty(list_pointer head);
void list_show(list_pointer head);
