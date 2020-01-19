#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define LINE_LENGTH 100
#define MAX_ARGS 7
#define MAX_LENGTH 20
#define MAX_PT_ENTRIES 32

bool helperText = true;
int numProcesses = 0;
int userTime = 0;
int sysTime = 0;

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

void exitCommand() {
    printf("\nResources used\n");
    printf("User time =    %d seconds\n", userTime);
    printf("Sys  time =    %d seconds\n\n", sysTime);
    return;
}

void startShell(int argc, char *argv[]) 
{
    if (helperText) 
    {
        printf("mini shell running...\n");
    }
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
}


int main(int argc, char *argv[]) 
{
    startShell(argc,argv);
    return 0;
}