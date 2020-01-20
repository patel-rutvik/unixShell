#include "util.h"

bool helperText = true;

int numProcesses = 0;
int userTime = 0;
int sysTime = 0;

// List of builtin commands, followed by their corresponding functions.
char *builtinNames[] = 
{
    "jobs",
    "resume",
    "kill",
    "sleep",
    "suspend",
    "wait",
    "help",
    "exit"
};

int (*builtinFunc[]) (char **) = 
{
  &displayJobs,
  &resume,
  &killProcess,
  &sleepProcess,
  &suspendProcess,
  &waitProcess,
  &help,
  &exitCommand
};

int numFunctions() 
{
  return sizeof(builtinNames) / sizeof(char *);
}

void resume() 
{
    printf("resume function call\n");
}

void killProcess() 
{
    printf("kill function call\n");
}

void sleepProcess() 
{
    printf("sleep function call\n");
}

void suspendProcess() 
{
    printf("suspend function call\n");
}

void waitProcess() 
{
    printf("wait function call\n");
}

void help() 
{
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

bool runCommand(char **args) 
{
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

void startShell(int argc, char *argv[]) 
{
    if (helperText) 
    {
        printf("mini shell running...\n");
    }
    char *line;
    char **arguments;
    bool shellRunning = true;

    while (shellRunning) {
        printf("SHELL379: ");
        line = readLine();
        arguments = splitLine(line);
        shellRunning = runCommand(arguments);
        /*
        int len = sizeof(arguments)/sizeof(arguments[0]);
        printf("%d\n", sizeof(arguments));
        //printf("\n");

        printf("length of arguments array: %d\n", len);
        for (int i = 0; i < len; i++)
        {
            printf(arguments[i]);
            printf(" ");
        }
        printf("\n");

        if (strcmp(arguments[0], "exit") == 0)  // add functionality to strip spaces..
        {
            // wait until all processes are completed

            // print out total user/system time for each process
            exitCommand();
            shellRunning = false;
        } else if (strcmp(arguments[0], "jobs") == 0) 
        {
            displayJobs();
        }
        */
    }
    /*
    char command[LINE_LENGTH];
    bool shellRunning = true;
    int loopCount = 0;
    char moreCommands[5][10] = {
                                "kill",
                                "resume",
                                "sleep",
                                "suspend",
                                "wait"
                                };
    int moreCommandsLen = sizeof(moreCommands)/sizeof(moreCommands[0]);
    bool moreArgs = false;
    

    //TODO: find a way to read by LINE not each WORD...
    // if you press enter... another "SHELL379:"" should show up...
    while (shellRunning) 
    {
        printf("SHELL379: ");
        scanf ("%s", command);
        //printf("number of commands captured: %d\n", argc);
        for (int i = 0; i < moreCommandsLen; i++)
        {
            if(!strcmp(moreCommands[i], command))
            {
                printf("hit, keep reading more arguments!\n");
                moreArgs = true;
            }
        }
        if (helperText)
        {
            printf("command entered: %s\n", command);
        }
        if (strcmp(command, "exit") == 0)  // add functionality to strip spaces..
        {
            // wait until all processes are completed

            // print out total user/system time for each process
            exitCommand();
            shellRunning = false;
        } else if (strcmp(command, "jobs") == 0) 
        {
            displayJobs();
        } else if(moreArgs) {
            printf("looping again for more one more argument.\n");
        }
        if (helperText)
        {
            printf("times loop ran: %d\n\n", loopCount++);
        }
    }
    */
}