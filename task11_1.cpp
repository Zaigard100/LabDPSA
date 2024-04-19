#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

string* table;
int count;

int getHash(string key){
    int s = 0;
    for (int i = 0; i < key.length(); i++)
        s += (int)key[i];
    return s % count;
}

void create(){
    if(table != nullptr) delete[] table;
    table = new string[count];
    for(int i = 0; i < count; i++) table[i] = "";
    for(int i = 0; i < count; i++){
        cout << "Введите ключ: ";
        string key = read_line();
        if(table[getHash(key)]==""){
            table[getHash(key)] = key;
        }else{
            cout << "Конфликт с ключом: " << table[getHash(key)] << "." << endl;
            i--;
            continue;
        }
    }
}
int find(string key){
    if (table[getHash(key)] == key)
        return getHash(key);
    else
        return -1;
}

void show(){
    for(int i = 0; i < count; i++) cout<<i<<" - "<<table[i]<<endl;
}

bool dialog(){

    cout << "\n1.Создать таблицу." << endl;
    cout << "2.Поиск." << endl;
    cout << "3.Вывести таблицу на экран." << endl;
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите команду: ";

    switch (read_uint()) {
        case 1: {
            cout<<endl;
            create();
            return true;
        }
        case 2:{
            if(table == nullptr)  return true;
            cout<<endl;
            cout << "Введите значение: " << endl;
            if(find(read_line())!=1){
                cout << "Индекс: " << find(read_line()) << endl;
            } else{
                cout << "Не найдено" << endl;
            }
            return true;
        }
        case 3:{
            if(table == nullptr)  return true;
            cout<<endl;
            show();
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

void task11_1(){

    count = 10;
    SetConsoleOutputCP(CP_UTF8);
    while(dialog());

}