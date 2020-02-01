#include "util.h"

char *readLine() 
{
    char *inputLine = NULL;
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    getline(&inputLine, &bufferSize, stdin);

    //TODO: STILL ONLY PRINTS FIRST ELEMENT IN THE LINE...
    //commands[pidIndex] = inputLine;
    return inputLine;
}

char **splitLine(char *line) 
{
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    int pos = 0;
    char **tokens = malloc(tokenBufferSize * sizeof(char*));
    char *tok;
    char *delims = " \t\r\n\a";

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
