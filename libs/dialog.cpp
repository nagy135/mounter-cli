#include "ncurses.h"
#include "dialog.h"
#include <string>

using namespace std;

Dialog::Dialog(){
}

Dialog::~Dialog(){
}

int Dialog::fetch_response(string title, int height, int width, int starty, int startx, string choices[], int num_choices){
    main_win = newwin(height, width, starty, startx);
    box(main_win, 0 , 0);
    wrefresh(main_win);
    keypad(main_win, true);

    int left_padding, right_padding;
    for (int i=0; i < num_choices; i++){
        left_padding = (width - 2 - choices[i].length()) / 2;
        right_padding = (width - 2 - choices[i].length()) - left_padding;
        choices[i] = string(left_padding,' ') + choices[i] + string(right_padding, ' ');
    }
    int highlight = 0;
    int choice;
    int size = width - 2 - title.length();
    int clear = 0;
    title = " " + title + " ";
    while(1){
        for (int i=0; i < num_choices; i++){
            if (i == highlight){
                wattron(main_win, A_REVERSE);
            }
            if (clear){
                wattroff(main_win, A_REVERSE);
                mvwprintw(main_win, i+2, 1, string(choices[i].length(), ' ').c_str());
            } else {
                mvwprintw(main_win, i+2, 1, choices[i].c_str());
            }
            wattroff(main_win, A_REVERSE);
        }
        if (clear){
            mvwprintw(main_win, 0, width / 2 - title.length() / 2 - 1, string(title.length(), ' ').c_str());
        } else {
            mvwprintw(main_win, 0, width / 2 - title.length() / 2 - 1, title.c_str());
        }
        if (clear) break;

        choice = wgetch(main_win);
        switch(choice){
            case (int)'k':
                highlight--;
                break;
            case (int)'j':
                highlight++;
                break;
            case (int)'q':
                return -1;
            case KEY_DOWN:
                highlight++;
                break;
            case KEY_UP:
                highlight--;
                break;
            default:
                break;
        }
        if (highlight < 0){
            highlight = 0;
        }
        if (highlight > num_choices - 1){
            highlight = num_choices - 1;
        }
        if (choice == 10 || choice == (int)'l'){
            clear = 1;
        }

    }
    return highlight;
}
void Dialog::clear(){
    /* box(local_win, ' ', ' '); : This won't produce the desired
     * result of erasing the window. It will leave it's four corners
     * and so an ugly remnant of window.
     */
    wborder(main_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    /* The parameters taken are
     * 1. win: the window on which to operate
     * 2. ls: character to be used for the left side of the window
     * 3. rs: character to be used for the right side of the window
     * 4. ts: character to be used for the top side of the window
     * 5. bs: character to be used for the bottom side of the window
     * 6. tl: character to be used for the top left corner of the window
     * 7. tr: character to be used for the top right corner of the window
     * 8. bl: character to be used for the bottom left corner of the window
     * 9. br: character to be used for the bottom right corner of the window
     */
    wrefresh(main_win);
    /* delwin(main_win); */
}
