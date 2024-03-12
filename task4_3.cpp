#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct List{
    string data;
    List* next;
    List* prev;
};

struct subList{
    List *list;
    subList *next;
    subList *prev;
};

subList *listOfList;

void init(){
    listOfList = new subList;
    listOfList->next = nullptr;
    listOfList->prev = nullptr;
}

bool isListOfListEmpty(){
    return (listOfList->next == nullptr);
}
bool isListEmpty(List *list){
    return list->next == nullptr;
}
subList *findList(string name){
    if(isListOfListEmpty()) return nullptr;
    subList * l = listOfList->next;
    while(l != nullptr){
        if(l->list->data == name) return l;
        l = l->next;
    }
    return nullptr;
}
List *findEl(string data,subList *l){
    List *el = l->list;
    while(el != nullptr){
        if(el->data == data) return el;
        el = el->next;
    }
    return nullptr;
}
void addList(string name,string find,bool prev){
    //создаем пустой лист
    subList *newList = new subList;
    newList->list = new List;
    newList->list->next = nullptr;
    newList->list->prev = nullptr;
    newList->list->data = name;
    //находим место куда вставить новый лист
    if(isListOfListEmpty()){
        listOfList->next = newList;
        newList->prev = listOfList;
        newList->next = nullptr;
        return;
    }
    subList *f = findList(find);
    if(prev) f = f->prev;
    //вставляем новый лист на выбранное место
    newList->prev = f;
    newList->next = f->next;
    newList->prev->next = newList;
    if(newList->next!= nullptr) newList->next->prev = newList;
}
void add(string data,string find,string name, bool prev){
    //поиск листа
    List * newEl = new List;
    newEl->data = data;
    subList *l = findList(name);
    if(l == nullptr){
        cout << "Лист с таким именем не найден"<<endl;
        return;
    }
    //поиск элемента(место куда вставить новый элемент)
    if(isListEmpty(l->list)){
        newEl->prev = l->list;
        newEl->next = nullptr;
        newEl->prev->next = newEl;
        return;
    }
    List *f = findEl(find,l);
    if(f == nullptr){
        cout << "Элемент с такими данными не найден"<<endl;
        return;
    }
    if(prev)f = f->prev;
    //вставка элемента
    newEl->prev = f;
    newEl->next = f->next;
    newEl->prev->next = newEl;
    newEl->next->prev = newEl;
}

void deleteEl(string el,string name){
    if(isListOfListEmpty()){
        cout << "Лист листов пуст"<<endl;
        return;
    }
    //поиск листа
    subList *l = findList(name);
    if(l == nullptr){
        cout << "Лист с таким именем не найден"<<endl;
        return;
    }
    //поиск удоляемого элемента
    if(isListEmpty(l->list)){
        return;
    }
    List *f = findEl(el,l);
    if(f == nullptr){
        cout << "Элемент с такими данными не найден"<<endl;
        return;
    }
    //удаление
    f->prev->next = f->next;
    if(f->next != nullptr)f->next->prev = f->prev;
    delete f;
}

void deleteList(string name){
    if(isListOfListEmpty()){
        cout << "Лист листов пуст"<<endl;
        return;
    }
    //поиск листа
    subList *l = findList(name);
    if(l == nullptr){
        cout << "Лист с таким именем не найден"<<endl;
        return;
    }
    //если лист пуст удаляем только лист
    if(isListEmpty(l->list)){
        delete l->list;
        l->prev->next = l->next;
        if(l->next!= nullptr) l->next->prev = l->prev;
        delete l;
        return;
    }
    //удаляем элементы листа
    List *del = l->list;
    List *n = del->next;
    do{
        delete del;
        del = n;
        n = del->next;
    }while (n != nullptr);
    delete del;
    //удаляем лист
    l->prev->next = l->next;
    if(l->next!= nullptr) l->next->prev = l->prev;
    delete l;
}

void findInAllList(string data){
    if(isListOfListEmpty()){
        cout << "Лист листов пуст"<<endl;
        return;
    }
    subList* l = listOfList->next;
    List *el;
    while (l!= nullptr){
        el = l->list->next;
        while (el!= nullptr) {
            if (el->data == data) cout << data << " была найдена в листе " << l->list->data << endl;
            el = el->next;
        }
        l = l->next;
    }
}

void showList(List* l){
    cout<<"("<<l->data<<") - ";
    if(isListEmpty(l)){
        cout<<"(empty)"<<endl;
        return;
    }
    List * el = l->next;
    while (el != nullptr){
        cout<<el->data;
        if(el->next != nullptr) cout<<" - ";
        el = el->next;
    }
    cout<<endl;
}

void showAllList(){
    if(isListOfListEmpty()){
        cout << "Лист листов пуст"<<endl;
        return;
    }
    subList *l = listOfList->next;
    while(l!= nullptr){
        cout<<"|"<<endl;
        showList(l->list);
        l = l->next;
    }
}

bool dialog() {
    cout << "\n1.Создать лист." << endl;
    cout << "2.Создать элемент в листе." << endl;
    cout << "3.Удалить элемент в листе." << endl;
    cout << "4.Удалить лист" << endl;
    cout << "5.Найти элемент списка по всей структуре" << endl;
    cout << "6.Найти элемент списка в определенном листе" << endl;
    cout << "7.Показать всю структуру" << endl;
    cout << "8.Показать лист" << endl;
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите команду: ";

    switch (read_uint()) {
        case 1: {
            cout << "Введите название списка:" << endl;
            string name = read_line();
            if (isListOfListEmpty()) {
                addList(name, "", false);
                return true;
            } else {
                cout << "Введите название листа после/перед которого хотите добавить новый лист:" << endl;
                string find = read_line();
                cout << "\n1.Перед." << endl;
                cout << "2.После" << endl;
                cout << "Введите команду: ";
                bool run = true;
                while (run) {
                    switch (read_uint()) {
                        case 1: {
                            addList(name, find, true);
                            run = false;
                            break;
                        }
                        case 2: {
                            addList(name, find, false);
                            run = false;
                            break;
                        }

                    }
                }
            }
            return true;
        }
        case 2: {
            if (isListOfListEmpty()) {
                cout << "Лист листов пуст" << endl;
                return true;
            }
            cout << "Введите название списка:" << endl;
            string name = read_line();
            subList *l = findList(name);
            if (l == nullptr) {
                cout << "Лист с таким именем не найден" << endl;
                return true;
            }
            cout << "Введите данные:" << endl;
            string data = read_line();
            if (isListEmpty(l->list)) {
                add(data, l->list->data, name, true);
                return true;
            }
            cout << "Введите элемент после/перед которого хотите добавить данные:" << endl;
            string find = read_line();
            List *el = findEl(find, l);
            if (el == nullptr) {
                cout << "Элемент с такими данными не найден" << endl;
                return true;
            }
            cout << "\n1.Перед." << endl;
            cout << "2.После" << endl;
            cout << "Введите команду: ";
            bool run = true;
            while (run) {
                switch (read_uint()) {
                    case 1: {
                        add(data, find, name, true);
                        run = false;
                    }
                    case 2: {
                        add(data, find, name, true);
                        run = false;
                    }
                }
                return true;
            }
        }
        case 3:{
            if (isListOfListEmpty()) {
                cout << "Лист листов пуст" << endl;
                return true;
            }
            cout << "Введите название списка:" << endl;
            string name = read_line();
            subList *l = findList(name);
            if (l == nullptr) {
                cout << "Лист с таким именем не найден" << endl;
                return true;
            }
            cout << "Введите удаляемый элемент:" << endl;
            string find = read_line();
            List *el = findEl(find, l);
            if (el == nullptr) {
                cout << "Элемент с такими данными не найден" << endl;
                return true;
            }
            deleteEl(find,name);
            return true;
        }
        case 4:{
            if (isListOfListEmpty()) {
                cout << "Лист листов пуст" << endl;
                return true;
            }
            cout << "Введите название списка:" << endl;
            string name = read_line();
            subList *l = findList(name);
            if (l == nullptr) {
                cout << "Лист с таким именем не найден" << endl;
                return true;
            }
            deleteList(name);
            return true;
        }
        case 5:{
            if (isListOfListEmpty()) {
                cout << "Лист листов пуст" << endl;
                return true;
            }
            cout << "Введите данные:" << endl;
            string data = read_line();
            findInAllList(data);
            return true;
        }
        case 6:{
            if (isListOfListEmpty()) {
                cout << "Лист листов пуст" << endl;
                return true;
            }
            cout << "Введите название списка:" << endl;
            string name = read_line();
            subList *l = findList(name);
            if (l == nullptr) {
                cout << "Лист с таким именем не найден" << endl;
                return true;
            }
            cout << "Введите элемент которого хотите найти:" << endl;
            string find = read_line();
            List *el = findEl(find, l);
            if (el != nullptr) {
                cout << "Элемент с такими данными найден" << endl;
            }else{
                cout << "Элемент с такими данными не найден" << endl;
            }
            return true;
        }
        case 7:{
            showAllList();
            return true;
        }
        case 8:{
            cout << "Введите название списка:" << endl;
            string name = read_line();
            subList *l = findList(name);
            if (l == nullptr) {
                cout << "Лист с таким именем не найден" << endl;
                return true;
            }
            showList(l->list);
            return true;
        }
        case 9:{
            return false;
        }
        default:{
            cout << "Введена не верная команда" << endl;
            return true;
        }
    }
}

void task4_3(){

    SetConsoleOutputCP(CP_UTF8);
    init();
    while(dialog());
}