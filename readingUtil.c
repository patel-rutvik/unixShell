/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Name: Rutvik Patel
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "util.h"

/*
The stringCat function is responsible for combining two strings
    Parameters:
        char *s1: first string
        char **s2: second string

    Returns:
        char *ans : the concatanated string
*/
char *stringCat(char *s1, char **s2) {
    char *ans = (char *) malloc(1 + strlen(s1)+ strlen(s2));
    strcpy(ans, s1);
    strcat(ans, s2);  // joining the two strings
    return ans;
}

/*
The readLine function is responsible for reading in a line from stdin
    Parameters:

    Returns:
        char *inputLine : the line read in from stdin
*/
char *readLine() {
    char *inputLine = NULL;
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    getline(&inputLine, &bufferSize, stdin);
    return inputLine;
}

/*
The splitLine function is responsible for splitting the specified line by the delimiters
    Parameters:
        char *line: the line read in from stdin

    Returns:
        char **tokens: the tokens split by the delimiters
*/
char **splitLine(char *line) {
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    char *delims = " \t\r\n\a";  // delimiters of choices
    char **tokens = malloc(tokenBufferSize * sizeof(char*));
    char *tok = strtok(line, delims);
    int pos = 0;
    
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
