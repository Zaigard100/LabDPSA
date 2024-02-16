#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct Stack {
    int value;
    Stack* next;
};

Stack* stack, * trash;
inline void init() {
    stack = nullptr;
    trash = nullptr;
}

bool isEmpty(Stack* sp) {
    if (sp == nullptr) return true;
    return false;
}

Stack* push(int val, Stack* sp) {
    Stack* new_sp = new Stack;
    new_sp->next = sp;
    new_sp->value = val;
    return new_sp;
}

void remove() {
    if(isEmpty(stack)){
        cout << "Стек пуст" << endl;
        return;
    }
    Stack* st = stack->next;
    delete stack;
    stack = st;
}

void delite() {
    if(isEmpty(stack)){
        cout << "Стек пуст" << endl;
        return;
    }
    Stack* st = stack->next;
    stack->next = trash;
    trash = stack;
    stack = st;
}

void showStack(Stack* sp){
    Stack* temp = sp;
    while (temp != nullptr) {
        cout << temp->value << " -> ";
        temp = temp->next;
    }
    cout << " null|" << endl;
}

bool enter_dialog() {
    cout << "1.Ввести" << endl;
    cout << "2.Достать из корзины" << endl;
    cout << "3.Отмена" << endl;
    cout << "Введите команду: ";
    switch (read_uint()) {
        case 1: {
            stack = push(read_int(),stack);
            return false;
        }
        case 2:{
            if(isEmpty(trash)) {
                cout<<"Корзина пуста"<<endl;
                return false;
            }
            Stack* tr = trash;
            trash = tr->next;
            tr->next = stack;
            stack = tr;
            return false;
        }
        case 3:
            return false;
        default:
            cout << "Неверная команда"<<endl;
    }
    return  true;
}

bool del_dialog() {
    cout << "1.В корзину" << endl;
    cout << "2.Уничтожить" << endl;
    cout << "3.Отмена" << endl;
    cout << "Введите команду: " << endl;
    switch (read_uint()) {
        case 1:
            delite();
            return false;
        break;
        case 2:
            remove();
            return false;
        break;
        case 3:
            return false;
        default:
            cout << "Неверная команда"<<endl;
        break;
    }

    return true;
}

bool dialog() {
    cout << "1.Ввести данные" << endl;
    cout << "2.Показать данные" << endl;
    cout << "3.Удалить данные" << endl;
    cout << "4.Показать состояние" << endl;
    cout << "5.Заполнить случайными данными" << endl;
    cout << "6.Очистить стек" << endl;
    cout << "9.Выйти из программы"<<endl;
    cout << "Введите команду: ";
    switch (read_uint()) {
        case 1:
            while(enter_dialog());
        break;
        case 2:
            cout << stack->value << endl;
            break;
        case 3:
            while(del_dialog());
            break;
        case 4:
            showStack(stack);
            break;
        case 5: {
            cout << "Введите кол-во: ";
            unsigned iter = read_uint();
            srand(time(0));
            for(int i = 0;i<=iter;i++) {
                stack = push(rand(),stack);
            }
            return  true;
        }
        case 6: {
            while (stack!=nullptr) {
                remove();
            }
            break;
        }
        case 9: {
            while (stack!=nullptr) {
                remove();
            }
            while (trash!=nullptr) {
                if(isEmpty(trash)){
                    break;
                }
                Stack* tr = trash->next;
                delete trash;
                trash = tr;
            }
            return false;
        }
    }
    return true;
}

void task4() {
    SetConsoleOutputCP(CP_UTF8);
    init();
    while(dialog());
}