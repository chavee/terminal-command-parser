#include <stdio.h>
#include "CmdParser.h"

CmdParser *cp;
int argcount;

int main(int argc, char **argv) {
    cp = new CmdParser('=',',');
    argcount = cp->parse("AT+CONNECT=10.0.2.100, 8080,\"Hello world\"");

    printf("argument count == %d\n",argcount);

    printf("command = %s\n",cp->command());
    printf("arg0 = >%s<\n",cp->argString(0));
    printf("arg1 = >%s<\n",cp->argString(1));
    printf("arg2 = >%d<\n",cp->argInt(2));
    printf("arg3 = >%s<\n",cp->argString(3));
}
