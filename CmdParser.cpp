#include "CmdParser.h"

CmdParser::CmdParser(char cmdstopper, char argdelimiter) {
    this->cmdstopper = cmdstopper;
    this->argdelimiter = argdelimiter;
}

CmdParser::CmdParser() {
    CmdParser('=',',');
}

uint8_t CmdParser::strxcpy(char *dest, char *src, int n, int max) {
    if (n > max) n = max;
    strncpy(dest,src,n);
    dest[n] = '\0';
    return n;
}

uint8_t CmdParser::skipSpace(char **p) {
    uint8_t c = 0;
    while (**p == ' '||**p=='\t') {
        c++;
        (*p)++;
    }
    return c;
}

uint8_t CmdParser::getArgBoundary(char *p, char **first, char **last) {
    *first = p;
    while (**first==argdelimiter || **first==' ' || **first=='\0') {
        (*first)++;
    }
    *last = p + strlen(p) -1;
    if (*first < *last) {
        while (**last==argdelimiter || **last==' ' || **last=='\0') {
            (*last)--;
        }
    }
    else {
        *last = *first; 
    }
    return last-first;
}

/*
e.g.
    argcount = tokenizer("AT+SEND=203.185.67.124,8080,arg,10,\"Hello world\"", '=', ',');
*/
uint8_t CmdParser::tokenize(char *buffer, char** argv, uint8_t maxarg, char cmdstopper, char argdelimiter) {
    uint8_t i, argc = 0;
    char *h, *t, *cursor, *f, *l, insq, esc;

    for (i=0; i<=maxarg; i++) {
        argv[i] = NULL;
    }

    h = buffer;
    skipSpace(&h);
    if(*h=='\0') return -1;
    t = h;
    while (*t!=cmdstopper && *t!='\0') {
        t++;
    }
    argv[0] = h;

    if (*t != '\0') {
        cursor = t+1;
        *t='\0';
    }
    else {
        cursor = t;
        return 0;
    }

    while (cursor && argc<maxarg) {
        /* multiple consecutive spaces count as one */
        if (argdelimiter==' ') skipSpace(&cursor);

        h = t = cursor;
        esc = insq = 0;
        while ((*t!=argdelimiter || insq)&& *t!='\0') {
            if (*t=='"' && !esc) insq=insq==0?1:0;
            if (*t=='\\') esc=1; else esc=0;
            t++;
        }

        if (*t != '\0') {
            *t='\0';
            cursor = t+1;
        }
        else {
            cursor = NULL;
        }
        getArgBoundary(h,&f,&l);
        if (*f=='"') {
            if (*l=='"') {
                char* s = f+1;
                char* t = h;
                while (s < l) {
                    if (*s=='\\') {
                        s++;
                        if (*s=='"' || *s=='\\') *t++ = *s;
                        else if(*s=='n') *t++ = '\n';
                        else if(*s=='t') *t++ = '\t';
                        s++;
                    }
                    else *t++ = *s++;
                }
                *t = '\0';
            }
            else {
                h[0] = '\0';
            }
        }
        argv[++argc] = h;
    }
    return argc;
}

uint8_t CmdParser::parse(char *str) {
    strxcpy(buffer, str, strlen(str), BUFFERSIZE);
    argc = tokenize(buffer, argv, MAXARG, cmdstopper, argdelimiter);
    return argc;
}

char* CmdParser::command() {
    return argv[0];
}

char* CmdParser::argString(uint8_t n) {
    return argv[n];
}

double CmdParser::argFloat(uint8_t n) {
    return atof(argv[n]);
}

uint16_t CmdParser::argInt(uint8_t n) {
    return atoi(argv[n]);
}
