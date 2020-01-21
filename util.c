#include "util.h"

bool helperText = true;

int numProcesses = 0;
int userTime = 0;
int sysTime = 0;
bool exitSignal = false;


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

// TODO: check args length, if more than 2, handle error accordingly...
void resume(char ** args) 
{
    printf("resume function call\n");
    checkNoArgs(args);

}

void killProcess(char ** args) 
{
    printf("kill function call\n");
    printf("the second arg: %s\n", args[1]);
    checkNoArgs(args);

}

void sleepProcess(char ** args) 
{
    printf("sleep function call\n");
    checkNoArgs(args);

}

void suspendProcess(char ** args) 
{
    printf("suspend function call\n");
    checkNoArgs(args);

}

void waitProcess(char ** args) 
{
    printf("wait function call\n");
    checkNoArgs(args);
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

    exitSignal = true;
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
    
    return tokens;    
}

bool checkTooManyArgs(char **args) {
    if (args[2] != NULL) {
        printf("too many commands entered!\n");
        return true;
    }
    return false;
}

bool checkNoArgs(char **args) {
    if (args[1] == NULL) {
        printf("\nexpected another parameter...\nfollow this format: <cmd> <int>\n\n");
        return true;
    }
}
/*
void makeProcess(char **args) {
    pid_t childPid = fork();
        
    
    if (!childPid) {
        // child process
        printf("Child:\nCurrent PID: %d and Child PID: %d\n",
               getpid(), childPid);
    } else {
        printf("### Parent ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), childPid);
    }
}
*/
/*
void makeProcess(char **args) {
    pid_t pid;
    if (fork()) {
        // child process
        if (execvp(args[0], args) == -1) {
            perror(args[0]);
        }
        return;
    } else if (pid < 0) {
        // error forking
        perror(args[0]);
    } else {
        // parent process


    }
    return;
}
*/

bool runCommand(char **args) 
{
    bool argFlag = false;
    // no commands entered...
    if (args[0] == NULL) {
        return true;
    }
    
    //printf("running the command...\n");
    for (int i = 0; i < numFunctions(); i++) {
        if (strcmp(args[0], builtinNames[i]) == 0) {
            argFlag = checkTooManyArgs(args);
            //if (argFlag && strcmp(args[0], "exit") && strcmp(args[0], "jobs")) {
            if (argFlag) {
                return argFlag;
            }
            
            return (*builtinFunc[i])(args);
        }
    }

    printf("yet to create the newProcess function...\n");
    //makeProcess(args);
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

        if (exitSignal) {
            shellRunning = false;
        }
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