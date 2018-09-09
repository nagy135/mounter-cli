#include "dialog.h"

using namespace std;

class Mounter{
    private:
        Dialog d;
    public:
        Mounter(int term_width, int term_height);
        void choice(int height, int width, int starty, int startx);
        void mount(int height, int width, int starty, int startx);
        void umount(int height, int width, int starty, int startx);
};
