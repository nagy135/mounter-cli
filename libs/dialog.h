#include <string>

using namespace std;

class Dialog {
    private:
        WINDOW *main_win;
    public:
        Dialog();
        int fetch_response(string title, int height, int width, int starty, int startx, string choices[], int num_choices);
        ~Dialog();
        void clear();
};
