#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct Element {
    string data;
    Element *next;
};

Element *first;
Element *trash;

void init() {
    first = new Element;
    first->data = "";
    first-> next = nullptr;
    trash = new Element;
    trash->data = "";
    trash-> next = nullptr;
}
bool isEmpty() {
    return first->next == nullptr;
}
Element* findPrev(string find) {// возвращает ссылку на предыдущую ячейку который указывает на ячейку с даннымим(find) если не находит возвращает null
    Element *f = first;
    do {
        if(f->next->data==find) {
            break;//выходим если нашли
        }
        f = f->next;
    }while (f->next!=nullptr);
    return f;
}
Element* findEl(string find) {// возвращает ссылку на ячейку с даннымим(find) если не находит возвращает null
    Element *f = first;
    do {
        if(f->data==find) {
            break;//выходим если нашли
        }
        f = f->next;
    }while (f!=nullptr);
    return f;
}

void add(string find, string data,bool prev) {
    if(isEmpty()) {
        first->next = new Element;
        first->next->data = data;
        first->next->next = nullptr;
        return;
    }
    Element *f;
    if(prev){
        f = findPrev(find);// находим нужный элемент
    }else {
        f = findEl(find);// находим нужный элемент
    }
    Element *nextEl = f->next; // сохраняем следуюющий
    f->next = new Element; // создаем новый элемент, который будет между ними
    f->next->next = nextEl; // следующийм элементом для нового элемента будет следующий найденного элемента
    f->next->data = data; //заполняем ячейку данными
}

void del(string find) {
    if(isEmpty()) {
        cout << "Стек пуст"<< endl;
        return;
    }
    Element *prev = findPrev(find);// находим предыдущий элемент
    Element *del = prev->next; // сохраняем удаляемый
    prev->next = del->next;
    del->next = nullptr;
    Element* f = trash;
    while(f->next!= nullptr){
        f = f->next;
    }
    f->next = del;
}
void showList() {
    Element *f = first->next;
    do {
        cout << f->data;
        if(f->next != nullptr) cout <<" - ";
        f = f->next;
    }while (f!=nullptr);
    cout<<endl;
}
void showTrash() {
    if(trash->next== nullptr)return;
    Element *f = trash->next;
    do {
        cout << f->data;
        if(f->next != nullptr) cout <<" - ";
        f = f->next;
    }while (f!=nullptr);
    cout<<endl;
}
bool dialog() {
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
            while(!findEl(find)){
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
            while(!findEl(d)){
                cout << "Элемент не найден" << endl;
                d = read_line();
            }
            del(d);
            return true;
        }
        case 3: {
            cout << "Лист:" << endl;
            showList();

            cout << "Корзина:" << endl;
            showTrash();
            return true;
        }
        case 4: {
            cout << "Введите данные:" << endl;
            if(findEl(read_line())!=nullptr) cout << "Элемент найден" << endl;
            else cout << "Элемент не найден" << endl;
            return true;
        }
        case 9: {
            return false;
        }
        default: {
            cout << "Ведена не верная команда" << endl;
        }
    }

}

void task2_5() {
    SetConsoleOutputCP(CP_UTF8);
    init();
    while(dialog());
}