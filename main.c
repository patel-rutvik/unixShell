#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LENGTH 100
#define MAX_ARGS 7
#define MAX_LENGTH 20
#define MAX_PT_ENTRIES 32

bool helperText = true;

void displayJobs()
{
    if (helperText) 
    {
        printf("Displaying the current jobs: \n");
    }
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
    while (shellRunning) 
    {
        scanf ("%s", command);
        printf("number of commands captured: %d\n", argc);
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
            if (helperText)
            {
                printf("shell terminated...\n");
            }
            shellRunning = false;
        } else if (strcmp(command, "jobs") == 0) 
        {
            displayJobs();
        } else if(moreArgs) {
            printf("looping again for more arguments.\n");
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