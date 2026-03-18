#pragma once
#define	MAX_SIZE 100
#define	boolean	unsigned char
#define	true	1
#define	false	0

// Global stack
int stack[MAX_SIZE];
int top = -1;
boolean err_check = false;    //# error 발생 확인

void push(int e);
int pop();

int eval_postfix(char* exp);
boolean is_number(char c);
boolean is_op(char c);