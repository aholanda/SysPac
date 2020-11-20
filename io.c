#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void flush_buffer() {
    char ch;
    while ((ch = getchar() != '\n') && (ch != EOF));
}

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

