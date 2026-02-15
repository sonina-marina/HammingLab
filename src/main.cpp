#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include "HammingCode.h"
#include "UI.h"

int main() {
    MainWindow window(640, 490, "Расширенный код Хэмминга");

    window.show();

    // HammingCode obj;
    // obj.coding();
    // obj.checking();

    return Fl::run();
}