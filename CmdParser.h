#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BUFFERSIZE 200
#define MAXARG     10
#define MAXCMDSIZE 16
#define MAXARGSIZE 32

#define uint8_t  unsigned char
#define uint16_t unsigned int

class CmdParser {
    public :
        char cmdstopper;
        char argdelimiter;
        char buffer[BUFFERSIZE+1];
        char* argv[MAXARG+1];
        uint8_t argc;

        uint8_t skipSpace(char**);
        uint8_t parse(char*);

        CmdParser();
        CmdParser(char, char);

        char* command();
        char* argString(uint8_t);
        double argFloat(uint8_t);
        uint16_t argInt(uint8_t);

    private :
        uint8_t tokenize(char*, char**, uint8_t, char, char);
        uint8_t getArgBoundary(char*, char**, char**);
        uint8_t strxcpy(char*, char*, int, int); 
};
