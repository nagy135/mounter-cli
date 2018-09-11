#include <ncurses.h>
#include <string.h>
#include "mounter.h"
#include <unistd.h> // getuid
#include <stdio.h> // printf


int main(){
    if (getuid()){
        printf("%s", "You must be root to mount devices!\n");
        return -1;
    }

    char title[]="mounter-cli v1.0";
    char mesg[]="press any key to continue (or q to exit)";
    int row,col;
    initscr();
    noecho();
    curs_set(0);
    getmaxyx(stdscr,row,col);
    mvprintw(row/2,(col-strlen(title))/2,"%s",title);
    mvprintw(row/2+2,(col-strlen(mesg))/2,"%s",mesg);
                                    /* print the message at the center of the screen */
    mvprintw(row-2,0,"C++ mounter\n");
    printw("CLI, ncurses based device mounter");

    char quit = 'q';
    int pressed = getch();
    if (pressed == (int)quit){
        endwin();
        return 0;
    } else {
        clear();
        refresh();
        Mounter mntr(col, row);
        /* Note a; */
        /* printw("Presse %c",(char) pressed); */
    }
    refresh();
    endwin();

    return 0;
}
