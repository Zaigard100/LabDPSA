#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

const int m = 10;
int com = 0;
struct sList{
    string key;
    sList* next;
};

struct mList{
    string key;
    sList* head;
};

mList table[m];

void create()
{
    for (int i = 0; i < m; i++)
    {
        table[i].key.empty();
        table[i].head = new sList;
        table[i].head->next = nullptr;
    }
}

int getHash(string key){
    int s = 0;
    for (int i = 0; i < key.length(); i++)
        s += (int)key[i];
    return s % m;
}

sList* get(int index)
{
    sList* current = table[index].head;
    while (++com && current->next != nullptr)
        current = current->next;
    return current;
}

void add(string key)
{
    int hash = getHash(key);
    if (++com && table[hash].key.empty())
        table[hash].key = key;
    else
    {
        cout << endl << "Возникла конфликтная ситуация." << endl;
        sList* current = get(hash);
        sList* tmp = new sList;
        tmp->key = key;
        tmp->next = nullptr;
        current->next = tmp;
        current = tmp;
    }
}

int find(string key)
{
    int hash = getHash(key);
    if (++com && table[hash].key == key)
        return 1;
    else
    {
        sList* tmp = table[hash].head->next;
        while (++com && tmp != nullptr)
        {
            if (tmp->key == key)
            {
                return 1;
            }
            tmp = tmp->next;
        }
    }
    return -1;
}

void show()
{
    cout << endl;
    for (int i = 0; i < m; i++)
    {
        cout << i << " - ";
        if (table[i].key != "")
            cout << table[i].key;

        sList* tmp = table[i].head->next;
        while (tmp != nullptr)
        {
            cout << " -> " << tmp->key ;
            tmp = tmp->next;
        }
        cout << endl;
    }
}

bool del(string key)
{
    int flag = 0;
    int hash = getHash(key);
    if (table[hash].key == key)
    {
        if (table[hash].head->next == nullptr)
        {
            flag = 1;
            table[hash].key = "";
        }
        else
        {
            table[hash].key = table[hash].head->next->key;
            sList* tmp = table[hash].head->next;
            table[hash].head->next = tmp->next;
            flag = 1;
            delete tmp;
        }
    }
    else
    {
        sList* prev = table[hash].head;
        sList* tmp = table[hash].head->next;
        while (tmp != nullptr)
        {
            if (tmp->key == key)
            {
                prev->next = tmp->next;
                delete tmp;
                flag = 1;
                break;
            }
            else
            {
                prev = tmp;
                tmp = tmp->next;
            }
        }
    }
    return flag==1;
}

bool dialog(){

    cout << "\n1.Добавить." << endl;
    cout << "2.Поиск." << endl;
    cout << "3.Вывести таблицу на экран." << endl;
    cout << "4.Удалить." << endl;
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите команду: ";

    switch (read_uint()) {
        case 1: {
            cout<<endl;
            cout << "Введите значение: " << endl;
            string  key = read_line();
            com = 0;
            if(find(key)!=-1){
                cout << "Данный ключ занят. \nСравнений: " << com << endl;
            }else{
                com = 0;
                add(key);
                cout << endl << "Успешно. \nСравнений: " << com << endl;
            }
            return true;
        }
        case 2:{
            cout << "Введите значение: " << endl;
            string  key = read_line();

            com = 0;
            if(find(key)==-1) {
                cout << "Данный ключ свободен." << com << endl;
            }else{
                cout << "Индекс: " << find(key)<<"\nСравнений: " << com << endl;
            }
            return true;
        }
        case 3:{
            cout<<endl;
            show();
            return true;
        }
        case 4:{
            cout<<endl;

            cout << endl << "Введите значение: ";
            string  key = read_line();
            if (del(key))
                cout << endl << "Значение удалено." << endl;
            else
                cout << endl << "Ключ не найден." << endl;
            return true;
        }
        case 9:{
            return false;
        }
        default:{
            cout<<"Не валидная команда..."<<endl;
            return true;
        }
    }
}

void task11_3(){
    SetConsoleOutputCP(CP_UTF8);
    create();
    while(dialog());
}