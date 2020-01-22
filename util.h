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

bool displayJobs(char **args);
bool resume(char **args);
bool killProcess(char **args);
bool sleepProcess(char **args);
bool suspendProcess(char **args);
bool waitProcess(char ** args);
void help();
bool exitCommand(char **args);
bool checkTooManyArgs(char **args);
bool runCommand(char **args);
bool checkNoArgs(char **args);
bool makeProcess(char **args);
void startShell(int argc, char *argv[]);

#endif