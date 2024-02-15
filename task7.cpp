#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

void task7() {
    SetConsoleOutputCP(CP_UTF8);
    queue.init();
    while(dialog());
}