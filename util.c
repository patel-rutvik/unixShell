#include "util.h"

//List of builtin commands, followed by their corresponding functions.
char *builtinNames[] = {
    "jobs",
    "resume",
    "kill",
    "sleep",
    "suspend",
    "wait",
    "help",
    "exit"
};

int (*builtinFunc[]) (char **) = {
  &displayJobs,
  &resume,
  &killProcess,
  &sleepProcess,
  &suspendProcess,
  &waitProcess,
  &help,
  &exitCommand
};

int numFunctions() {
  return sizeof(builtinNames) / sizeof(char *);
}

void resume() {
    printf("resume function call\n");
}

void killProcess() {
    printf("kill function call\n");
}

void sleepProcess() {
    printf("sleep function call\n");
}

void suspendProcess() {
    printf("suspend function call\n");
}

void waitProcess() {
    printf("wait function call\n");
}

void help() {
    printf("help function call\n");
}

void displayJobs()
{
    printf("\nRunning processes:\n");
    if (numProcesses != 0) {
        printf("#     PID S SEC COMMAND\n");
    }
    printf("Processes =    %d active\n", numProcesses);
    printf("Completed processes:\n");
    printf("User time =    %d seconds\n", userTime);
    printf("Sys  time =    %d seconds\n\n", sysTime);

    return;
}

bool exitCommand() 
{
    printf("\nResources used\n");
    printf("User time =    %d seconds\n", userTime);
    printf("Sys  time =    %d seconds\n\n", sysTime);
    return false;
}

char *readLine() 
{
    /*
    int bufferSize = BUFFER_SIZE;
    int pos = 0;
    char *buff = malloc(sizeof(char) * bufferSize);
    int ch;

    while(true) 
    {
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            return buff[pos] = '\0';
        } else {
            buff[pos] = ch;
        }
        pos++;
    }
    */
    
    char *inputLine = NULL;
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    getline(&inputLine, &bufferSize, stdin);
    return inputLine;
}

char **splitLine(char *line) 
{
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    int pos = 0;
    char **tokens = malloc(tokenBufferSize * sizeof(char*));
    char **tok;
    char * delims = " \t\r\n\a";

    tok = strtok(line, delims);
    while (tok != NULL) {
        tokens[pos] = tok;
        pos++;

        if (pos >= tokenBufferSize) {
            tokenBufferSize += TOKEN_BUFFER_SIZE;
            tokens = realloc(tokens, tokenBufferSize * sizeof(char*));
        }
        tok = strtok(NULL, delims);
    }
    tokens[pos] = NULL;
    /*
    printf(sizeof(tokens));
    printf("\n");
    printf(sizeof(tokens[0]));
    printf("\n");
    */
    return tokens;    
}

bool runCommand(char **args) {
    // no commands entered...
    if (args[0] == NULL) {
        return true;
    }
    
    //printf("running the command...\n");
    for (int i = 0; i < numFunctions(); i++) {
        if (strcmp(args[0], builtinNames[i]) == 0) {
            return (*builtinFunc[i])(args);
        }
    }

    printf("yet to create the newProcess function...\n");
    return true;
    // not a built in command, must be executed
    //return newProcess(args);
}