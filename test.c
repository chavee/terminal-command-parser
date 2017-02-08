#include "term-parse.h"

int main(int argc, char **argv) {
    char command[160];
    char arg1[MAXARGLENGTH+1];
    char arg2[MAXARGLENGTH+1];
    int arg3;
    bool arg4;

    if (argc > 1) {
        // Try enter cli command --> 
        // ./test "AT+CW \"catbus\",\"stud 2559\",15,true"
        scancmd(argv[1],command,arg1,arg2,&arg3,&arg4);
        printf("command = %s\n",command);
        printf("arg1 = %s\n",arg1);
        printf("arg2 = %s\n",arg2);
        printf("arg3 = %d\n",arg3);
        printf("arg4 = %d\n",arg4);
    }
    else {
        //scancmd("AT+CW=\"catbus\",\"stud2559\",28,true",command,arg1,arg2,&arg3,&arg4);
    }
}
