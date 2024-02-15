#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
// стек на основе динамического распределения памяти
struct Stack {
    int Value;
    Stack* next;
};

Stack* stack, * trash; // указтели вершин стеков
//инициализация основного и вспомогательного стеков
inline void init() {
    stack = nullptr;
    trash = nullptr;

}
// проверка на пустоту стека
bool isEmpty(Stack* sp) {
    if (sp == nullptr) return true;
    else return false;
}
// функция добавления элемента в стек
Stack* push(int Value, Stack* sp) {
    if (isEmpty(sp) == true) {
        Stack* new_sp = new Stack;
        new_sp->next = nullptr;
        new_sp->Value = Value;
        return new_sp;
    }
    else {
        Stack* new_sp = new Stack;
        new_sp->next = sp;
        new_sp->Value = Value;
        return new_sp;
    }
}

void remove() { //функция уничтожения элемента
    if(isEmpty(stack)){
        cout << "Стек пуст" << endl;
        return;
    }
    Stack* st = stack->next;
    delete stack;
    stack = st;
}
void delite() {
    if(isEmpty(stack)){ //функция удаления элемента в корзину
        cout << "Стек пуст" << endl;
        return;
    }
    Stack* st = stack->next;
    stack->next = trash;
    trash = stack;
    stack = st;
}

int read_int() {
    string data;
    bool run = true;
    string buf;
    int iter = 1;
    bool err = false,space = false;
    getline(cin,data);
    while(run){
        for(char c:data) {
            if(c == '-') {
                if(buf.empty()) {
                    buf+=c;
                }else {
                    err = true;
                    cout << "Err: \'" <<c<<"\'("<<iter<<")"<<endl;
                }
            }else if(c == '0') {
                if(space) {
                    err = true;
                    cout << "Err: \'" <<c<<"\'("<<iter<<")"<<endl;
                }else{
                    if(buf == "-") {
                        buf = "0";
                    }else {
                        buf+=c;
                    }
                }
            }else if(isdigit(c)) {
                if(buf!="0") {
                    buf += c;
                }else {
                    err = true;
                    cout << "Err: \'" <<c<<"\'("<<iter<<")"<<endl;
                }
            }else if(c == ' ') {
                if(!buf.empty()) {
                    space = true;
                }
            }else {
                err = true;
                cout << "Err: \'" <<c<<"\'("<<iter<<")"<<endl;
            }
            iter++;
    }
    if(err) {
        buf = "";
        iter = 1;
        err = false;
        space = false;
        data = "";
        getline(cin,data);
    }else{
        return stoi(buf);
    }
}
}

unsigned read_uint(string data) {
    int i = read_int();
    while (i < 0) {
        if(data == ""){
            i = read_int();
        }else{
            exit(0);
        }
    }
    return i;
}

void showStack(Stack* sp){
    Stack* temp = sp;
    while (temp != nullptr) {
        cout << temp->Value << " -> ";
        temp = temp->next;
    }
    cout << " null|";
}

bool enter_dialog() {
        cout << "1.Ввести" << endl;
        cout << "2.Достать из корзины" << endl;
        cout << "3.Отмена" << endl;
        switch (read_uint("")) {
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
        switch (read_uint("")) {
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
    switch (read_uint("")) {
        case 1:
            while(enter_dialog());
        break;
        case 2:
            cout << stack->Value << endl;
            break;
        case 3:
            while(del_dialog());
            break;
        case 4:
            showStack(stack);
            break;
        case 5: {
            cout << "Введите кол-во: ";
            unsigned iter = read_uint("");
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

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    init();
    while(dialog());
}