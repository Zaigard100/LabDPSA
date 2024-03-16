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

List *head;

void init(){
    head = new List;
    head->data = "";
    head->next = head;
    head->prev = head;
}

bool isEmpty(){ return head->next==head&&head->prev==head; }

List *findEl(string find,bool prev){
    List *temp;
    if(prev) temp = head->prev;
    else temp = head->next;
    while(temp != head){
        if(temp->data == find) return temp;
        if(prev) temp = temp->prev;
        else temp = temp->next;
    }
    return nullptr;
}

void add(string find,string data,bool prev){
    List *f;
    if(isEmpty()) f = head;
    else f = findEl(find,prev);
    if(prev) f = f->prev;
    List *temp = new List;
    temp->data = data;
    temp->prev = f;
    temp->next = f->next;
    f->next = temp;
    temp->next->prev = temp;
}
void del(string find){
    List *f = findEl(find, false);
    f->prev->next = f->next;
    f->next->prev = f->prev;//
    delete f;
}

void show(bool prev){
    List *temp;
    if(prev) temp = head->prev;
    else temp = head->next;
    do{
        cout<<temp->data<<" - ";
        if(prev) temp = temp->prev;
        else temp = temp->next;
    }while(temp != head);
    cout<<endl;
}

bool dialog(){
    cout << "\n1.Добавить элемент в список." << endl;
    cout << "2.Удалить опредённый элемент из списка." << endl;
    cout << "3.Вывести текущее состояние списка на экран." << endl;
    cout << "4.Найти элемента списка по его информационной части" << endl;
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите команду: ";

    switch (read_uint()) {
        case 1: {
            if(isEmpty()) {
                cout << "Введите данные:" << endl;
                add("",read_line(),false);
                return  true;
            }
            cout << "Введите элемен после/перед которого хотите добавить данные:" << endl;
            string find = read_line();
            while(findEl(find, false)== nullptr){
                cout << "Элемент не найден" << endl;
                find = read_line();
            }
            cout << "\n1.Перед." << endl;
            cout << "2.После" << endl;
            cout << "Введите команду: ";
            bool run = true;
            while (run){
                switch (read_uint()) {
                    case 1: {
                        cout << "Введите данные:" << endl;
                        add(find, read_line(), true);
                        run = false;
                        break;
                    }
                    case 2: {
                        cout << "Введите данные:" << endl;
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
            string d = read_line();
            while(findEl(d, false)== nullptr){
                cout << "Элемент не найден" << endl;
                d = read_line();
            }
            del(d);
            return true;
        }
        case 3: {
            cout << "\n1.В обратном" << endl;
            cout << "2.В прямом" << endl;
            cout << "Введите команду: ";
            bool run = true;
            while (run){
                switch (read_uint()) {
                    case 1: {
                        show(true);
                        run = false;
                        break;
                    }
                    case 2: {
                        show(false);
                        run = false;
                        break;
                    }
                }
            }
            return true;
        }
        case 4: {
            cout << "\n1.В обратном" << endl;
            cout << "2.В прямом" << endl;
            cout << "Введите команду: ";
            bool run = true;
            while (run){
                switch (read_uint()) {
                    case 1: {
                        cout << "Введите данные:" << endl;
                        if(findEl(read_line(), true)!=nullptr) cout << "Элемент найден" << endl;
                        else cout << "Элемент не найден" << endl;
                        run = false;
                        break;
                    }
                    case 2: {
                        cout << "Введите данные:" << endl;
                        if(findEl(read_line(),false)!=nullptr) cout << "Элемент найден" << endl;
                        else cout << "Элемент не найден" << endl;
                        run = false;
                        break;
                    }
                }
            }
            return true;
        }
        case 9: {
            return false;
        }
        default: {
            cout << "Ведена не верная команда" << endl;
            return true;
        }
    }

}

void task4_1(){
    SetConsoleOutputCP(CP_UTF8);
    init();
    while(dialog());
}
