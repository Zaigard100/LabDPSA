#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

int array_size = 10;

struct List {
    string data1,data2;
};

List list[array_size];
int count;

void init() {
    for(int i = 0;i<count;i++) {
        list[i].data1 ="";
        list[i].data2 ="";
    }
    count = 0;
}
bool isEmpty() {
    return count == 0;
}
bool isFull() {
    return count == array_size;
}

void add(int index,string data1,string data2) {
    if(data1 != "" && data2 != "") {
        if(list[index].data1 == "" && list[index].data2 == "") {
            list[index].data1 =data1;
            list[index].data2 =data2;
        }else {
            if(!isFull()) {
                int i = index;
                while(i>array_size-1) {
                    list[i+1]=list[i];
                    i++;
                }
                list[index].data1 = data1;
                list[index].data2 = data2;
            }else {
                cout<< "Масив заполнен." << endl;
            }
        }
    }
}

void delite(int index) {
    if(!isEmpty()) {

    }
}

void task2_2() {

}
