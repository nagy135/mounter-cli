#include "dialog.h"

using namespace std;

class Mounter{
    private:
        Dialog d;
        int terminal_w, terminal_h;
        int height, width, starty, startx;
    public:
        Mounter(int term_width, int term_height);
        void choice();
        void mount();
        void umount();
};
