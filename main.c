#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LENGTH 100
#define MAX_ARGS 7
#define MAX_LENGTH 20
#define MAX_PT_ENTRIES 32


void startShell(int argc, char *argv[]) 
{
    printf("mini shell running...\n");
    char command[LINE_LENGTH];
    bool shellRunning = true;

    while (shellRunning) 
    {
        scanf ("%s", command);
        printf ("You entered: %s\n", command);

        if (strcmp(command, "exit") == 0)
        {
            break;
        }
    }
    
}


int main(int argc, char *argv[]) 
{
    startShell(argc,argv);
    return 0;
}