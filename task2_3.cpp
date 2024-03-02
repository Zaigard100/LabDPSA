#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;


constexpr int arr_size = 10;

struct List {
    int next{-1};
    string data;
};
List list[arr_size+1];
int count = 0;
void init() {
    for(int i = 1;i <arr_size;i++) {
        list[i].data = "";
        list[i].next = -1;
    }
    list[0].data = "header?";
    list[0].next = 0;
    count = 0;
}

bool isFull() {
    return count == arr_size;
}
bool isEmpty() {
    return count == 0;
}

int findIndex(string data,bool prev){
    if(isEmpty()) return -1;
    if(prev) {
        for (int i = 0; i < count; i++) {
            if (list[list[i].next].data == data) {
                return i;
            }
        }
    }else{
        for (int i = 0; i < count; i++) {
            if (list[i].data == data) {
                return i;
            }
        }
    }
    cout << "Не найдено." << endl;
    return -1;
}

void add(string findData, string data,bool prev) {
    if(isFull()) {
        cout << "Масив полон." << endl;
        return;
    }
    if(isEmpty()) {
        list[1].data = data;
        list[0].next = 1;
        list[1].next = 0;
        count++;
        return;
    }
    int empty = -1,find = findIndex(findData,prev);
    for(int i = 1;i<arr_size+1;i++) {
        if(list[i].next == -1) {
            empty = i;
            break;
        }
    }
    if(find == -1) {
            cout << "Данные не существует."<<endl;
    }else {
        list[empty].data = data;
        list[empty].next = list[find].next;
        list[find].next = empty;
        count++;
    }
}

void delite(string delElement) {
    if(isEmpty()) {
        cout << "Масиив пуст." << endl;
        return;
    }
    int del = -1;
    for(int i = 1;i<arr_size+1;i++) {
        if(list[i].data == delElement) {
            del = i;
            break;
        }
    }
    if(del == -1) {
        cout << "Данные не существуют." << endl;
    }else {
        for (int i = 0;i<arr_size+1;i++) {
            if(list[i].next == del) {
                list[del].data = "";
                list[i].next = list[del].next;
                list[del].next = -1;
                count--;
                break;
            }
        }
    }
}

void showArr() {
    cout << "\nСостояние листа:" << endl;
    int next = list[0].next;
    while (next != 0) {
        cout << list[next].data << " - ";
        next = list[next].next;
    }
    cout << "\nСостояние масива:" << endl;
    for (int i = 0;i<arr_size+1;i++) {
        cout << i << " - {" << list[i].data << ", next: " << list[i].next<< "}" << endl;
    }
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
            if(isEmpty()) {
                cout << "Введите данные:" << endl;
                add("header?",read_line(),false);
                return  true;
            }
            cout << "Введите элемен:" << endl;
            string find = read_line();
            cout << "Введите данные:" << endl;
            cout << "\n1.Перед." << endl;
            cout << "2.После" << endl;
            bool run = true;
            while (run){
                switch (read_uint()) {
                    case 1: {
                        add(find, read_line(), true);
                        run = false;
                        break;
                    }
                    case 2: {
                        add(find, read_line(), false);
                        run = false;
                        break;
                    }

                }
            }

            return true;
        }
        case 2: {
            cout << "Введите удаляемый элемента: ";
            delite(read_line());
            return true;
        }
        case 3: {
            showArr();
            return true;
        }
        case 4: {
            cout << "Введите данные:" << endl;
            int f = findIndex(read_line(), false);
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

void task2_3() {
    SetConsoleOutputCP(CP_UTF8);
    init();
    while(dialog());
}
