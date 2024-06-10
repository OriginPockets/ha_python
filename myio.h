#ifndef MYIO_H
#define MYIO_H

#include <stdbool.h>

void raw_mode(bool enable);
bool kbhit(void);
void locate(int x, int y);
void cls(void);
void Sleep(int ms);

#endif