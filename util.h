#ifndef _UTIL_H_
#define _UTIL_H_

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

bool displayJobs();
bool resume();
bool killProcess(char **args);
bool sleepProcess();
bool suspendProcess();
bool waitProcess();
void help();
bool exitCommand();
bool checkTooManyArgs(char **args);
bool runCommand(char **args);
bool checkNoArgs(char **args);
void startShell(int argc, char *argv[]);

#endif