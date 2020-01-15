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
    char commands[LINE_LENGTH];
    bool shellRunning = true;

    while (shellRunning) 
    {
        scanf ("%s", commands);
        if (helperText)
        {
            printf ("command entered: %s\n", commands);
        }
        if (strcmp(commands, "exit") == 0)  // add functionality to strip spaces..
        {
            if (helperText)
            {
                printf("shell terminated...\n");
            }
            break;
        } else if (strcmp(commands, "jobs") == 0) 
        {
            displayJobs();
        }
    }
}


int main(int argc, char *argv[]) 
{
    startShell(argc,argv);
    return 0;
}