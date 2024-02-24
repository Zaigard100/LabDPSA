#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

const int array_size = 10;

struct List {
    string data1;
};

List list[10];
int count;

void init() {
    for(int i = 0;i<count;i++) {
        list[i].data1 ="";
    }
    count = 0;
}
bool isEmpty() {
    return count == 0;
}
bool isFull() {
    return count == array_size;
}

void add(int index,string data1) {
    if(isFull()) {
        cout<< "Масив заполнен." << endl;
        return;
    }
    if(data1 != "") {
        if(list[index].data1 == "") {
            list[index].data1 = data1;
        }else {
            int i = array_size - 1;
            do{
                list[i] = list[i - 1];
                i--;
            }while(i!=index);
            list[index].data1 = data1;
            count++;
        }
    }
}

void delite(int index) {
    if(isEmpty()) {
        cout << "Масив пустой." << endl;
        return;
    }

    int i = index;
    while(i>array_size-1) {
        list[i]=list[i+1];
        i++;
    }

    list[array_size-1].data1 = "";
    count--;
}

void sort_add(string data) {
    if(isFull()) {
        cout<< "Масив заполнен." << endl;
        return;
    }
    if(isEmpty()) {
        add(0,data);
        return;
    }
    for(int i = 0;i < array_size;i++) {
        if(list[i].data1=="") {
            add(i,data);
            return;
        }
        if(data<list[i].data1) {
            add(i,data);
            return;
        }
    }

}

void showArr() {
    for(int i = 0; i < array_size;i++) {
        cout << i << " - " << list[i].data1<<endl;
    }

}

int findIndex(string data){
    for(int i = 0;i < count;i++) {
        if(list[i].data1 == data) {
            return i;
        }
    }
    cout << "Не найдено." << endl;
    return -1;
}

bool dialog() {

    cout << "\n1.Добавить элемент в список." << endl;
    cout << "2.Удалить опредённый элемент из списка." << endl;
    cout << "3.Вывести текущее состояние списка на экран." << endl;
    cout << "4.Найти индекс элемента списка по его информационной части" << endl;
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите коману: ";

    switch (read_uint()) {
        case 1: {
            sort_add(read_line());
            return true;
        }
        case 2: {
            cout << "Введите номер удаляемого элемента: ";
            delite(read_uint());
            return true;
        }
        case 3: {
            showArr();
            return true;
        }
        case 4: {
            cout << "Введите данные:" << endl;
            int f = findIndex(read_line());
            if(f!=-1) {
                cout << f <<endl;
            }
            return true;
        }
        case 9: {
            return false;
        }
        default: {
            cout << "Ведена не верная команда" << endl;
        }
    }

    return  true;
}

void task2_2() {
    SetConsoleOutputCP(CP_UTF8);
    init();
    while(dialog());
}
