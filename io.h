#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

extern void flush_buffer(void);
extern int getch(void);

#endif
