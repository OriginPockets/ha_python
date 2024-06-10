#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include "myio.h"

void raw_mode(bool enable)
{
    struct termios term;
    tcgetattr(0, &term);
    if (enable)
    {
        term.c_lflag &= ~(ICANON | ECHO);
    }
    else
    {
        term.c_lflag |= ICANON | ECHO;
    }
    tcsetattr(0, TCSANOW, &term);
}

bool kbhit(void)
{
    int ibwait;
    ioctl(0, FIONREAD, &ibwait);
    return ibwait > 0;
}

void locate(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

void cls(void)
{
    printf("\033[2J");
}

void Sleep(int ms)
{
    time_t nt = ms * CLOCKS_PER_SEC / 1000 + clock();
    while (nt > clock())
        ;
}