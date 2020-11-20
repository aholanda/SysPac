#include <stdio.h>

#include <unistd.h>

#ifdef LINUX
#include <termios.h>
#else
#include <conio.h>
#endif


void flush_buffer() {
    char ch;
    while ((ch = getchar() != '\n') && (ch != EOF));
}

#ifdef LINUX
int getch() {
    struct termios oldtc, newtc;
    int ch;
    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    ch=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
    return ch;
}
#endif
