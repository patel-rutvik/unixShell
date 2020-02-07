/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Name: Rutvik Patel
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "util.h"

int numActiveProcesses = 0;  // current number of active processes
long long userTime = 0;  // total user CPU time
long long sysTime = 0;  // total system CPU time
int pidIndex = 0;  // current pid index

bool helperText = false;  // toggle debugging output
bool background = false;  // background flag to indicate if a task is running in the bkgd

/* arrays to hold and model the PCB (process control block) */
char *pids[MAX_PT_ENTRIES];
char *commands[MAX_PT_ENTRIES];
char *seconds[MAX_PT_ENTRIES];
char *comStatus[MAX_PT_ENTRIES];

/* initializing the input and output files to null */
char *inFile = NULL;
char *outFile = NULL;

// list of built in commands
char *builtinNames[] = {
    "jobs",
    "resume",
    "kill",
    "sleep",
    "suspend",
    "wait",
    "exit"
};

// corresponding function to the list above
int (*builtinFuncs[]) (char **) = {
  &displayJobs,
  &resume,
  &killProcess,
  &sleepProcess,
  &suspendProcess,
  &waitProcess,
  &exitCommand
};

/*
The numFunctions function simply returns the number of built-in functions in the shell
*/
int numFunctions() {
  return sizeof(builtinNames) / sizeof(char *);
}

/*
The isActiveProcess function is responsible for checking if the specified process is currently running
    Parameters:
        char *pid: the pid to check

    Returns:
        bool : if the process is active
*/
bool isActiveProcess(char *pid) {
    FILE *p;
    char *psLine = NULL;
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    char **psToks = malloc(tokenBufferSize * sizeof(char*));  // token array

    // pipe the ps command
    if ((p = popen("ps", "r")) == NULL) {
        // error in opening the pipe
        printf("pipe could not be opened\n");
    } else {
        // pipe successful, continue.
        int lineCount = 0;
        // while lines are available to be read...
        while (getline(&psLine, &bufferSize, p) != EOF) {
           lineCount++;
           // ignore the first line
           if (lineCount == 1) {
               continue;
           }
           psToks = splitLine(psLine);  // split the line by the delimiters, saving the tokens
            // if the pid is found
            if (!strcmp(pid, psToks[0])) {
                return true;
            } else {
                // pid is not a match, continue to the next line
                continue;
            } 
        }
        if (pclose(p)) {
            // error closing the pipe
            printf("pipe could not close\n");
        }
    }
    // if we have not yet returned true, it means the pid was not found, return false
    return false;
}

/*
The resume function is responsible for resuming a previously suspended task
    Parameters:
        char **args: the arguments entered

    Returns:
        bool true: resume finished
*/
bool resume(char **args) {   
    if (helperText) {
        printf("resume function call\n");
    }
    // check the argument format
    if (checkNoArgs(args)) {
        printf("\n\nfollow this format: <cmd> <int>\n\n");
        return true;
    }
    // check if the process is in the pcb
    if (isActiveProcess(args[1])) {
        FILE *p;
        char *command = "kill -CONT ";  // command to pipe
        char *catString = (char *) malloc(1 + strlen(command)+ strlen(args[1]));
        strcpy(catString, command);
        strcat(catString, args[1]);  // joining the command and pid strings

        // making the system call with the given pid, using a pipe
        if ((p = popen(catString, "r")) == NULL) {
        printf("pipe could not be opened\n");
        } else {
            // pipe opened successfully...
            printf("process resumed.\n");
        
            if (pclose(p)) {
                // pipe was not successful, therefore process DNE
            printf("process does not exist.\n");
            }
        }
    } else {
        printf("process not found.\n");
    }

    return true;

}

/*
The checkForProcess function is responsible for checking if any processes are currently running
    Parameters:

    Returns:
        bool : if the there is at least one process running
*/
bool checkForProcess() {
    // if there is no pid saved in the first index of the pid array
    if (pids[0] == NULL) {
        // no process running
        return false;
    }
    // a process is running
    return true;
}

/*
The killProcess function is responsible for killing a process with the specified pid
    Parameters:
        char **args: the arguments passed in

    Returns:
        bool : if the value is in the array
*/
bool killProcess(char **args) {   
    if (helperText) {
        printf("kill function call\n");
    }
    // check the argument format
    if (checkNoArgs(args)) {
        printf("\nexpected another parameter...\nfollow this format: <cmd> <int>\n\n");
        return true;
    }

    // check if there is a process running
    if (!checkForProcess()) {
        printf("no processes running...\n");
        return true;
    }

    if (helperText) {
        printf("arg to delete: %s\n", args[1]);
    }

    FILE *p;
    char *command = "kill "; // command to pipe
    char *catString = (char *) malloc(1 + strlen(command)+ strlen(args[1]));
    strcpy(catString, command);
    strcat(catString, args[1]);  // joining the command and the pid strings

    // making the system call with the given pid, using a pipe
    if ((p = popen(catString, "r")) == NULL) {
       printf("pipe could not be opened\n");
    } else {
        // pipe opened successfully...
        numActiveProcesses--;
        printf("process killed.\n");
        if (pclose(p)) {
            // pipe was not successful, therefore process DNE
           printf("process does not exist.\n");
        }
    }
    return true;
}

/*
The sleepProcess function is responsible for sleeping the shell for the specified number of seconds
    Parameters:
        char **args: the arguments passed in

    Returns:
        bool true: continue the shell loop
*/
bool sleepProcess(char **args) {
    if (helperText) {
        printf("going to sleep for %d seconds...\n", atoi(args[1]));
    }
    // check the argument format
    if (checkNoArgs(args)) {
        printf("\nexpected another parameter...\nfollow this format: <cmd> <int>\n\n");
        return true;
    }
    // sleep the shell for args[1] seconds
    sleep(atoi(args[1]));
    return true;
}

/*
The suspendProcess function is responsible for suspending a process with the specified pid
    Parameters:
        char **args: the arguments passed in

    Returns:
        bool true: continue the shell loop
*/
bool suspendProcess(char **args) {   
    if (helperText) {
        printf("suspend function call\n");
    }
    // check argument format
    if (checkNoArgs(args)) {
        printf("\nexpected another parameter...\nfollow this format: <cmd> <int>\n\n");
        return true;
    }

    // check if it is currently in the pcb
    if (isActiveProcess(args[1])) {
        FILE *p;
        char *command = "kill -STOP ";  // command to pipe
        char *catString = (char *) malloc(1 + strlen(command)+ strlen(args[1]));
        strcpy(catString, command);
        strcat(catString, args[1]);  // joining the command and pid strings

        // making the system call with the given pid, using a pipe
        if ((p = popen(catString, "r")) == NULL) {
        printf("pipe could not be opened\n");
        } else {
            // pipe opened successfully...
            printf("process suspended.\n");

            if (pclose(p)) {
                // pipe was not successful, therefore process DNE
            printf("process does not exist.\n");
            }
        }
    } else {
        printf("process not found..\n");
    }
    return true;
}

/*
The waitProcess function is responsible for making a process with the specified pid wait
    Parameters:
        char **args: the arguments passed in

    Returns:
        bool true: continue the shell loop
*/
bool waitProcess(char **args) {
    if (helperText) {
        printf("wait function call\n");
    }

    // check argument format
    if (checkNoArgs(args)) {
        printf("\nexpected another parameter...\nfollow this format: <cmd> <int>\n\n");
        return true;
    }

    // check the return values of wait and put it in if statement to handle error..
    if (isActiveProcess(args[1])) {
        wait(args[1]);
        printf("process is waiting.\n");
    } else {
        printf("process not found...\n");
    }
    return true;
}

/*
The printResources function is responsible for printing out the resources used
*/
void printResources() {
    printf("User time =    %lld seconds\n", userTime);
    printf("Sys  time =    %lld seconds\n\n", sysTime);
}

/*
The displayJobs function is responsible for querying and displaying the current pcb
    Parameters:
        char **args: the arguments passed in

    Returns:
        bool true: continue the shell loop
*/
bool displayJobs(char **args) {
    // check the argument format
    if (!checkNoArgs(args)) {
        printf("JOBS command does not take any arguments.\n");
        return true;
    }
    // reset the pcb 
    for (int i = 0; i < pidIndex; i++) {
        pids[i] = NULL;
        commands[i] = NULL;
        seconds[i] = NULL;
        comStatus[i] = NULL;
    }
    FILE *p;
    char *psLine = NULL;
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    char **psToks = malloc(tokenBufferSize * sizeof(char*));  // token array
    pidIndex = 0;

    // open pipe for the ps command
    if ((p = popen("ps", "r")) == NULL) {
        // error piping
        printf("pipe could not be opened\n");
    } else {
        // pipe opened successfully
        int lineCount = 0;
        printf("\nRunning processes:\n");
        printf("  #   PID   S   SEC COMMAND\n");
        // while there is a line to read..
        while (getline(&psLine, &bufferSize, p) != EOF) {
            lineCount++;
            // ignore the first 3 lines (the ps output, the bash shell, and the ./shell379 lines)
            if (lineCount < 4) {
               continue;
            }
            psToks = splitLine(psLine);  // split the line by the delimiters
            /* update the pcb */
            pids[pidIndex] = psToks[0];
            seconds[pidIndex] = psToks[2]; 
            commands[pidIndex] = psToks[3];
            comStatus[pidIndex] = "R";
            // print out the current running process
            printf("  %d: %s  %s %s  %s\n", pidIndex, pids[pidIndex], comStatus[pidIndex], seconds[pidIndex], commands[pidIndex]);
            pidIndex++;
            numActiveProcesses = lineCount - 3;
       }
       if (pclose(p)) {
           printf("pipe could not close\n");
       }
    }
    /* printing out resources used */
    printf("Processes =    %d active\n", numActiveProcesses);
    printf("Completed processes:\n");
    printResources();
    return true;
}

/*
The exitCommand function is responsible for exiting the shell
    Parameters:
        char **args: the arguments passed in

    Returns:
        bool : if the shell should continue executing
*/
bool exitCommand(char **args) {
    // check the argument formatting
    if (!checkNoArgs(args)) {
        printf("EXIT command does not take any arguments.\n");
        return true;
    }
    wait(0);  // wait for all processes to finish

    /* print out the resources used. */
    printf("Resources used\n");
    printResources();

    return false;
}

/*
The checkTooManyArgs function is responsible for checking if there are too many arguments passed in
    Parameters:
        char **args: the arguments passed in

    Returns:
        bool : if the number of arguments is acceptable
*/
bool checkTooManyArgs(char **args) {
    if (args[2] != NULL) {
        printf("too many commands entered!\n");
        return true;  // go to next iteration of the shell
    }
    return false;  // continue this iteration, arguments are okay
}

/*
The checkNoArgs function is responsible for checking if no arguments were passed in
    Parameters:
        char **args: the arguments passed in

    Returns:
        bool : if the there was 0 arguments passed in
*/
bool checkNoArgs(char **args) {
    if (args[1] == NULL) {
        return true;
    }
    return false;
}

/*
The childInterrupt function is responsible for handling the child interrupt signal by simpling printing
out that the background process has finished.
*/
void childInterrupt() {
    if (background) {
        printf("bkgd process has finished.\n");
    }
}

/*
The makeProcess function is responsible for making a new process using the exec and fork system calls
    Parameters:
        char **args: the arguments passed in

    Returns:
        bool true: shell should continue executing
*/
bool makeProcess(char **args, int input, int output) {
    pid_t cpid;  // child pid
    pid_t wait_pid;  // wait pid
    int status;  // current status

    // checking if the child is finished
    signal(SIGCHLD, childInterrupt);
    cpid = fork();
    // the child process
    if (cpid == 0) {
        numActiveProcesses++;
        /* check redirection flags and redirect accordingly */
        if (input) {
            freopen(inFile, "r", stdin);
        }
        if (output) {
            freopen(outFile, "w+", stdout);
        }
        // execute the command using exec
        if (execvp(args[0], args) < 0) {
            // error doing the exec
            perror("SHELL379: ");
        }
        exit(EXIT_FAILURE);
    } else if (cpid < 0) {
            // There was an error forking...
            perror("SHELL379: ");
    } else {
        // the parent process
        struct rusage usage;  // struct to use for the rusage() call

        // check for background process
        if (!background) {
            // use waitpid() to check for a status change, until the
            // process is EXITED or kill by a SIGNAL
            do {
            wait_pid = waitpid(cpid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        } else {
            sleep(0.1);  // idle slightly
        }
        
        /* get the usage of the process and update the running totals in the pcb*/
        getrusage(RUSAGE_CHILDREN, &usage);
        if (helperText) {
            printf ("%ld.%06ld\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
        }
        userTime += usage.ru_utime.tv_sec + (usage.ru_utime.tv_usec/1000000);
        sysTime += usage.ru_stime.tv_sec + (usage.ru_stime.tv_usec/1000000);
    }
    return true;
}

/*
The runCommand function is responsible for redirecting the command entered to the appropriate functions
    Parameters:
        char **args: the arguments passed in

    Returns:
        bool : if the shell should continue executing
*/
bool runCommand(char **args, char *argv, int input, int output) {
    bool argFlag = false;
    // if no commands entered...
    if (args[0] == NULL) {
        // go to next line in the shell
        return true;
    }
    for (int i = 0; i < numFunctions(); i++) {
        if (strcmp(args[0], builtinNames[i]) == 0) {
            argFlag = checkTooManyArgs(args); // check if too many arguments are passed 
            // too many arguments, don't execute anything, simply run the shell again
            if (argFlag) {
                return argFlag;
            }
            return (*builtinFuncs[i])(args);
        }
    }
    // not a built-in command, make a new process.
    return makeProcess(args, input, output);
}

/*
The shellInit function is responsible for initializing the shell
*/
void shellInit() {
    background = false;
    printf("unixShell: ");
}

/*
The setBkgd function is responsible for handling a background task command
    Parameters:
        char **: the arguments passed in

    Returns:
        char **a : the updated argument array
*/
char **setBkgd(char **a) {
    int elemCount = 0;
        while (a[elemCount] != NULL) {
            elemCount++;
        }
        if (!strcmp(a[elemCount - 1], "&")) {  
            background = true; // set the background flag to true
            a[elemCount - 1] = NULL; // remove the '&' from the arguments array
            printf("%s running in the bkgd.\n", a[0]);
        }
    return a;
}

/*
The checkMaxArgs function is responsible for checking to see if the max arguments have been reached
    Parameters:
        int num: the number of arguments passed in

    Returns:
        bool : if the argument limit has been exceeded
*/
bool checkMaxArgs(int num) {
    if (num > MAX_ARGS) {
        printf("argument limit exceeded...");
        return true;
    } else {
        return false;
    }
}

/*
The startShell function is responsible for running the shell, handling the input and redirecting
to helper functions
    Parameters:
        int argc: the stdin argument
        char *argv[]: the stdin argument

*/
void startShell(int argc, char *argv[]) {
    char *line;  // the current line
    char **arguments;  // holding the arguments
    bool shellRunning = true;  // set the shell to be running
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    int output;
    int input;

    // while the shell is running...
    while (shellRunning) {
        shellInit();  // initialize the shell
        line = readLine();  // read the line 
        arguments = splitLine(line);  // split the line
        /* check for input/output redirection */
        input = inputRedirect(arguments, &inFile);
        output = outputRedirect(arguments, &outFile);

        // check arguments
        if (checkMaxArgs(argc) || arguments[0] == NULL) {
            continue;
        }
        arguments = setBkgd(arguments);  // check for background process
        shellRunning = runCommand(arguments, argv, input, output);  // run the command, and update the status of the shell
    }
    free(line);
    free(arguments);
}
