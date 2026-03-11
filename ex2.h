#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constants
#define	MAX  100

// Structures
typedef	struct {
	char	name[20];
	int	id;
	char	grade[10];
} StudentRecord;

// Global variables
StudentRecord r[MAX];      // Student record: name, id, grade
int num_record = 0;             // Total # of records read from file
const char* fname = "grade.txt";  // Grade file name

// Function prototypes
void read_record(const char* fname);
void print_record();
void search_record();
void change_record();
void write_record(const char* fname);
