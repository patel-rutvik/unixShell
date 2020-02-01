#include "util.h"


int numActiveProcesses = 0;
long long userTime = 0;
long long sysTime = 0;
int pidIndex = 0;

bool helperText = false;
bool exitSignal = false;
bool background = false;

char *pids[MAX_PT_ENTRIES];
char *commands[MAX_PT_ENTRIES];
char *seconds[MAX_PT_ENTRIES];



// list of built in commands
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

// corresponding function to the list above
int (*builtinFuncs[]) (char **) = 
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


bool isActiveProcess(char *pid) {
    FILE *p;
    char *psLine = NULL;
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    char **psToks = malloc(tokenBufferSize * sizeof(char*));


    if ((p = popen("ps", "r")) == NULL) {
       printf("pipe could not be opened\n");
    } else {
       int lineCount = 0;

       while (getline(&psLine, &bufferSize, p) != EOF) {
           lineCount++;
           if (lineCount == 1) {
               continue;
           }
           psToks = splitLine(psLine);

            if (!strcmp(pid, psToks[0])) {
                numActiveProcesses--;
                return true;
            } else {
                continue;
            }
            
       }
       if (pclose(p)) {
           printf("pipe could not close\n");
       }
    }
    return false;
}

// TODO: check args length, if more than 2, handle error accordingly...
bool resume(char **args) 
{
    printf("resume function call\n");
    if (checkNoArgs(args)) {
        printf("\nexpected another parameter...\nfollow this format: <cmd> <int>\n\n");
        return true;
    }
    if (isActiveProcess(args[1])) {
        //resume(args[1], 0);

        // remove pid from pids array...


        printf("process killed.\n");
    } else {
        printf("invalid pid entered...\n");
    }


    return true;

}

//TODO: not working... fix this...

bool valueInArray(char *val, char *arr[], int size){
    int i;
    printf("size passed in: %d\n", size);
    for (i=0; i < size; i++) {
        printf("searching %d\n", i);
        if (strcmp(arr[i], val) == 0) {
            return true;
        } else {
            printf("not a match\n");
        }
    }
    return false;
}



bool checkForProcess() {
    if (pids[0] == NULL) {
        return false;
    }
    return true;
}



bool killProcess(char **args) 
{
    printf("kill function call\n");
    //printf("the second arg: %s\n", args[1]);
    if (checkNoArgs(args)) {
        printf("\nexpected another parameter...\nfollow this format: <cmd> <int>\n\n");
        return true;
    }

    if (!checkForProcess()) {
        printf("no processes running...\n");
        return true;
    }

    // TODO: NOT WORKING...
    /*
    printf("arg to delete: %s\n", args[1]);
    if (isActiveProcess(args[1])) {
        kill(args[1], 0);

        // remove pid from pids array...


        printf("process killed.\n");
    } else {
        printf("invalid pid entered...\n");
    }
*/
    FILE *p;
    char *psLine = NULL;
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    char **psToks = malloc(tokenBufferSize * sizeof(char*));
    int c;

    if ((p = popen(("kill %s", args[1]), "w")) == NULL) {
       printf("pipe could not be opened\n");
    } else {
       int lineCount = 0;

       while ((c = fgetc(p)) != EOF) {
           putchar(c);
            
       }
       if (pclose(p)) {
           printf("pipe could not close\n");
       }
    }
    return true;

}

bool sleepProcess(char **args) 
{
    //printf("going to sleep for %d seconds...\n", atoi(args[1]));
    if (checkNoArgs(args)) {
        printf("\nexpected another parameter...\nfollow this format: <cmd> <int>\n\n");
        return true;
    }

    sleep(atoi(args[1]));

    return true;

}

bool suspendProcess(char **args) 
{
    printf("suspend function call\n");
    if (checkNoArgs(args)) {
        printf("\nexpected another parameter...\nfollow this format: <cmd> <int>\n\n");
        return true;
    }
    if (isActiveProcess(args[1])) {
        //wait(args[1]);

        // remove pid from pids array...


        printf("process is waiting.\n");
    } else {
        printf("invalid pid entered...\n");
    }

    return true;

}

bool waitProcess(char **args) 
{
    printf("wait function call\n");
    if (checkNoArgs(args)) {
        printf("\nexpected another parameter...\nfollow this format: <cmd> <int>\n\n");
        return true;
    }

    // check the return values of wait and put it in if statement to handle error..
    //wait(pid)
    if (isActiveProcess(args[1])) {
        wait(args[1]);

        // remove pid from pids array...


        printf("process is waiting.\n");
    } else {
        printf("invalid pid entered...\n");
    }
    
    return true;

}

void help() 
{
    printf("help function call\n");
}


void printPids() {
    printf("\n");
    for(int i = 0; i < pidIndex; i++) {
        printf("pid %d: %s\n", i, pids[i]);
        printf("cmd %d: %s\n", i, commands[i]);
        
    }
}


bool displayJobs(char **args)
{
    if (!checkNoArgs(args)) {
        printf("JOBS command does not take any arguments.\n");
        return true;
    }

    printf("pid index is: %d\n", pidIndex);
    for (int i = 0; i < pidIndex; i++) {
        pids[i] = NULL;
        commands[i] = NULL;
        seconds[i] = NULL;
    }

    /* */
    FILE *p;
    char *psLine = NULL;
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    char **psToks = malloc(tokenBufferSize * sizeof(char*));
    pidIndex = 0;


    if ((p = popen("ps", "r")) == NULL) {
       printf("pipe could not be opened\n");
    } else {
       int lineCount = 0;
           printf("\nRunning processes:\n");
        printf("  #   PID   S   SEC COMMAND\n");
       while (getline(&psLine, &bufferSize, p) != EOF) {
           lineCount++;
           if (lineCount < 4) {
               continue;
           }
           psToks = splitLine(psLine);

            /*
            printf("line %d: ", lineCount - 1);
           for (int i = 0; i < 4; i++) {
               printf("%s ", psToks[i]);
           }
           printf("\n");
           */

            pids[pidIndex] = psToks[0];
            seconds[pidIndex] = psToks[2]; 
            commands[pidIndex] = psToks[3];

            //printf("trying to save: %s\n", psToks[0]);
            //printf("pid saved as: %s at index: %d\n", pids[pidIndex], pidIndex);
            printf("  %d: %s   R %s  %s\n", pidIndex, pids[pidIndex], seconds[pidIndex], commands[pidIndex]);
            pidIndex++;
            numActiveProcesses = lineCount -1;
       }

       //printf("lines read: %d\n", lineCount);
       if (pclose(p)) {
           printf("pipe could not close\n");
       }
    }
/**/
/*
    printPids();

    printf("\nRunning processes:\n");
    printf("pid index: %d\n", pidIndex);
    if (numActiveProcesses > 0) {
        //pids[1] = "test";
        printf("  #   PID   S   SEC COMMAND\n");
        for (int i = 0; i < pidIndex; i++) {
            printf("  %d: %s   R %s  %s\n", i, pids[i], seconds[i], commands[i]);
        }
    }
    */
    printf("Processes =    %d active\n", numActiveProcesses);
    printf("Completed processes:\n");
    printf("User time =    %lld seconds\n", userTime);
    printf("Sys  time =    %lld seconds\n\n", sysTime);
    return true;
}

bool exitCommand(char **args) 
{
    if (!checkNoArgs(args)) {
        printf("EXIT command does not take any arguments.\n");
        return true;
    }


    //TODO: WAIT FOR ALL PROCESSES TO FINISH BEFORE exiting..

    printf("\nResources used\n");
    printf("User time =    %lld seconds\n", userTime);
    printf("Sys  time =    %lld seconds\n\n", sysTime);

    exitSignal = true;
    return false;
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
        return true;
    }
    return false;
}

void childInterrupt() {
    if (background) {
        printf("child process has finished.\n");
    }
}

bool makeProcess(char **args) {
    pid_t cpid;  // child pid
    pid_t wait_pid;  // wait pid
    int status;  // current status

/*
    if (checkTooManyArgs(args)) {
        printf("argument limit reached.\n");
        return true;
    }*/
    // checking if the child is finished
    signal(SIGCHLD, childInterrupt);

    cpid = fork();

    // the child process
    if (cpid == 0) {
        numActiveProcesses++;
        if (execvp(args[0], args) < 0) {
            // error doing the exec
            perror("SHELL379: ");
        }
        exit(EXIT_FAILURE);
    } else if (cpid < 0) {
            // There was an error forking...
            perror("SHELL379: ");
    } else {
        // Parent process
        //struct rusage usageBefore;
        struct rusage usage;

        // if pid == (pid from a wait command entered)
        //      wait(NULL)

        if (!background) {
            do {
            wait_pid = waitpid(cpid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        } else {
            printf("else statement.\n");
            //wait(cpid);  // ?????
        }
        
        getrusage(RUSAGE_CHILDREN, &usage);
        //printf ("%ld.%06ld\n", usageAfter.ru_utime.tv_sec, usageAfter.ru_utime.tv_usec);
        userTime += usage.ru_utime.tv_sec + (usage.ru_utime.tv_usec/1000000);
        sysTime += usage.ru_stime.tv_sec + (usage.ru_stime.tv_usec/1000000);

    }

    return true;
}


bool runCommand(char **args) 
{
    bool argFlag = false;

    // if no commands entered...
    if (args[0] == NULL) {
        // go to next line in the shell
        return true;
    }
    
    for (int i = 0; i < numFunctions(); i++) {
        if (strcmp(args[0], builtinNames[i]) == 0) {
            argFlag = checkTooManyArgs(args);

            // too many arguments, don't execute anything, simply run the shell again
            if (argFlag) {
                return argFlag;
            }

            return (*builtinFuncs[i])(args);
        }
    }

    // not a built-in command, make a new process.
    return makeProcess(args);
}

void shellInit() {
    background = false;
    printf("SHELL379: ");
}

char **setBkgd(char **a) {
    int elemCount = 0;
        while (a[elemCount] != NULL) {
            elemCount++;
        }
        //printf("%d\n", elemCount);
        if (!strcmp(a[elemCount - 1], "&")) {  
            background = true;
            a[elemCount - 1] = NULL;
            printf("bkgd process...\n");
        }
    return a;
}

bool checkMaxArgs(int num) {
    if (num > MAX_ARGS) {
        printf("argument limit exceeded...");
        return true;
    } else {
        return false;
    }
}

void startShell(int argc, char *argv[]) 
{
    char *line;
    char **arguments;
    bool shellRunning = true;

    while (shellRunning) {
        shellInit();
        line = readLine();
        arguments = splitLine(line);
        printf("argc: %d\n", argc);
        if (checkMaxArgs(argc) || arguments[0] == NULL) {
            continue;
        }
        /*
        if (arguments[0] == NULL) {
            continue;
        }
        */
        arguments = setBkgd(arguments);

        shellRunning = runCommand(arguments);
        //free(line);
        //free(arguments);

    }
    
}
