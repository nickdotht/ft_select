#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

int test()
{
    char buf[1024];
    char buf2[30];
    char *ap = buf2;
    char *clearstr, *gotostr, *standstr, *stendstr;

    tgetent(buf, getenv("TERM"));

    clearstr = tgetstr("cl", &ap);
    gotostr = tgetstr("cm", &ap);
    standstr = tgetstr("so", &ap);
    stendstr = tgetstr("se", &ap);

    fputs(clearstr, stdout);
    fputs(tgoto(gotostr, 20, 10), stdout);
    printf("\033[1;42;33myafc rules\033[0m");
    fputs(standstr, stdout);
    printf("world");
    fputs(stendstr, stdout);
    putchar('!');

    printf("\n%d\n", tgetnum("co"));
    return (0);
}