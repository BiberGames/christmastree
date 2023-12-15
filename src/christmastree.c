////////////////////////////////////////////////////
//
// Author: Benjamin <whateveritwars@web.de>
// Copyright: 2023
//
////////////////////////////////////////////////////

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "christmastree.h"

void moveCursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void clearScreen() {
    printf("\e[1;1H\e[2J");
}

int getTerminalWidth() {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        perror("ioctl");
        return -1;
    }

    return ws.ws_col;
}

void tree() {
    for(int i=1; i<=20; i+=2) {
        moveCursor(lin, col-1);
        for(int j=1; j<=i; j++) {
            printf("\033[32;1m");
            putchar('*');
            printf("\033[0m");
        }
        lin++;
        col--;
    }
}

void trunk() {
    for(int i=1; i<=2; i++) {
        moveCursor(lin++, c-1);
        printf("\033[0m\033[33mmWm\033[0m\n");
    }
}

void effects() {
    while(1) {
        int li = (rand() % 9) + 3;
        int start = c - li + 2;
        int co = rand() % (li-2) * 2 + 1 + start;

        k = rand() % 4;

        if(k == 0) {
            color = rand() % 6;
            printf("\e[0;3%dm", colors[color]);
            moveCursor(li, co);
            putchar('o');
        }
        else {
            moveCursor(li, co);
            printf("\033[32;1m");
            putchar('*');
            printf("\033[0m");
        }

        usleep(10000);
    }
}

int main(void) {
    printf("\033[?25l");

    lin = 3;
    col = getTerminalWidth() / 2;
    c = col - 1;
    est = c - 2;
    color = 0;

    clearScreen();
    tree();
    trunk();
    effects();
	return 0;
}
