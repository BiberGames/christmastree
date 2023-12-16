////////////////////////////////////////////////////
//
// Author: Benjamin <whateveritwars@web.de>
// Copyright: 2023
//
////////////////////////////////////////////////////

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
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

int getTerminalHeight() {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        perror("ioctl");
        return -1;
    }

    return ws.ws_row;
}

void star() {
    printf("\033[0;33m");
    moveCursor(lin-3, col-3);
    printf("  .  \n");
    moveCursor(lin-2, col-3);
    printf(".....\n");
    moveCursor(lin-1, col-3);
    printf(" . . \n");
    moveCursor(lin, col-3);
    printf("\033[0m");
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
    int li = (rand() % 9) + 3;
    int start = c - li + 2;
    int co = rand() % (li-2) * 2 + 1 + start;

    k = rand() % 2;

    if(k == 0) {
        color = rand() % 6;
        printf("\e[0;3%dm", colors[color]);
        moveCursor(li + (lin - 15), co);
        putchar('o');
    }
    else {
        moveCursor(li + (lin - 15), co);
        printf("\033[32;1m");
        putchar('*');
        printf("\033[0m");
    }

    if(s < 10) {
        moveCursor(getTerminalHeight() / 2 - 2, getTerminalWidth() / 2 - 3);
        printf("\033[0;33m");
        printf(". . .\n");
        s++;
    }
    else {
        moveCursor(getTerminalHeight() / 2 - 2, getTerminalWidth() / 2 - 3);
        printf("\033[0;33m");
        printf(".....\n");
        s = 0;
    }
}

void handleCtrlC(int signum) {
    printf("\033[?25h");
    clearScreen();
    printf("Thanks and have a nice christmas!\n");
    exit(signum);
}

int onCtrlC() {
    if (signal(SIGINT, handleCtrlC) == SIG_ERR) {
        perror("Error registering signal handler");
        return 0;
    }
    return 1;
}

int main(void) {
    printf("\033[?25l");

    lin = getTerminalHeight() / 2;
    col = getTerminalWidth() / 2;
    c = col - 1;
    est = c - 2;
    color = 0;

    clearScreen();
    star();
    tree();
    trunk();
    while(onCtrlC()) {
        effects();
        usleep(100000);
    }
	return 0;
}
