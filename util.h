#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>



#define LINE_LENGTH 100
#define MAX_ARGS 7
#define MAX_LENGTH 20
#define MAX_PT_ENTRIES 32
#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64

bool helperText = true;

int numProcesses = 0;
int userTime = 0;
int sysTime = 0;

void displayJobs();
void resume();
void killProcess();
void sleepProcess();
void suspendProcess();
void waitProcess();
void help();
bool exitCommand();
