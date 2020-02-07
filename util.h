/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Name: Rutvik Patel
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <fcntl.h> 
#include <signal.h>
#include <memory.h>

#define LINE_LENGTH 100
#define MAX_ARGS 7
#define MAX_LENGTH 20
#define MAX_PT_ENTRIES 32
#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64

/* function declarations*/
int numFunctions();
bool isActiveProcess(char *pid);
bool checkForProcess();
void printResources();
void childInterrupt();
char **setBkgd(char **a);
bool checkMaxArgs(int num);
int inputRedirect(char **args, char **inFile);
int outputRedirect(char **args, char **outFile);
char *stringCat(char *s1, char **s2);
char *readLine();
char **splitLine(char *line);
bool displayJobs(char **args);
bool resume(char **args);
bool killProcess(char **args);
bool sleepProcess(char **args);
bool suspendProcess(char **args);
bool waitProcess(char ** args);
void printResources();
bool exitCommand(char **args);
bool checkTooManyArgs(char **args);
bool runCommand(char **args, char *argv, int input, int output);
bool checkNoArgs(char **args);
bool makeProcess(char **args, int input, int output);
void shellInit();
void startShell(int argc, char *argv[]);
#endif
