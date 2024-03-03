#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct List {
    string data;
    List *next;
    List *prev;
};

List *list;