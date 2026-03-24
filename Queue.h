#pragma once

#include <stdio.h>
#include <conio.h>
#include<stdlib.h>
#include<ctype.h>

#define	MAX_SIZE 10
#define	boolean	unsigned char
#define	true	1
#define	false	0

typedef char Element;
// Global queue
Element queue[MAX_SIZE];
int front = 0;
int rear = 0;
boolean is_empty = false;

void addq(Element e);
Element deleteq();
void queue_show();