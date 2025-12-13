#include "user.h"

void main(void) {
    // *((volatile int *) 0x80200000) = 0x1234;
    // printf("Hello World from shell!\n");
    // for (;;);
    while (1) {
prompt:
        printf("> ");
        char cmdline[128];
        int i = 0;
        while (true) {
            char ch = getchar();
            if (ch == '\b' || ch == 127) {   // accept Backspace (0x08) and DEL (0x7f)
                if (i != 0) {
                    cmdline[--i] = '\0';
                    // erase last char on terminal: move back, overwrite with space, move back
                    putchar('\b');
                    putchar(' ');
                    putchar('\b');
                }
            } else if (i == sizeof(cmdline) - 1) {
                printf("\ncommand line too long\n");
                goto prompt;
            } else if (ch == '\r') {
                printf("\n");
                cmdline[i++] = '\0';
                break;
            } else {
                cmdline[i++] = ch;
                putchar(ch);
            }
        }

        if (strcmp(cmdline, "hello") == 0)
            printf("Hello world from shell!\n");
        else if (strcmp(cmdline, "exit") == 0)
            exit();
        else
            printf("unknown command: %s\n", cmdline);
    }
}