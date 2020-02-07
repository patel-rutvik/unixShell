/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Name: Rutvik Patel
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "util.h"
/*
The inputRedirect function is responsible for redirecting the input of the command
    Parameters:
        char **args: the arguments passed in
        char **inFile: the input file

    Returns:
        int : 1 if successful, 0 or -1 if unsuccessful
 */
int inputRedirect(char **args, char **inFile) {
    for(int i = 0; args[i] != NULL; i++) {
        // search for the < character in the args array
        if(args[i][0] == '<') {
            args[i] = NULL;
            if(args[i+1] != NULL) {
                *inFile = args[i+1];  // save filename
            } else {
                return -1;
            }
            // readjust the array
            for(int k = i; args[k-1] != NULL; k++) {
                args[k] = args[k+2];
            }
            return 1;
        }
  }
  return 0;
}

/*
The outputRedirect function is responsible for redirecting the output of the command
    Parameters:
        char **args: the arguments passed in
        char **outFile: the output file

    Returns:
        int : 1 if successful, 0 or -1 if unsuccessful
 */
int outputRedirect(char **args, char **outFile) {
    for(int i = 0; args[i] != NULL; i++) {
        // search for the > character in the args array
        if(args[i][0] == '>') {
            args[i] = NULL;
            if(args[i+1] != NULL) {
                *outFile = args[i+1];  // save filename
            } else {
                return -1;
            }
            // readjust the array
            for(int k = i; args[k-1] != NULL; k++) {
                args[k] = args[k+2];
            }
            return 1;
        }
    }
    return 0;
}
