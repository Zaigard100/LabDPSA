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
int com = 0;

int getHash(string key,int a){
    int s = a;
    for (int i = 0; i < key.length(); i++)
        s += (int)key[i];
    return s % count;
}

void create(){
    if(table != nullptr) delete[] table;
    table = new string[count];
    for(int i = 0; i < count; i++) table[i] = "";
}
int find(string key){
    int h;
    for (int i = 0; i < count; i++)
    {
        h = getHash(key, i);
        com++;
        if (table[h]==key)
        {
            return h;
        }
    }
    return -1;
}

bool add(string key){
    int h;
    for (int i = 0; i < count; i++)
    {
        h = getHash(key, i);
        com++;
        if (table[h]=="")
        {
            table[h] = key;
            return true;
        }
    }
    return false;
}

void show(){
    for(int i = 0; i < count; i++) cout<<i<<" - "<<table[i]<<endl;
}

bool dialog(){

    cout << "\n1.Добавить." << endl;
    cout << "2.Поиск." << endl;
    cout << "3.Вывести таблицу на экран." << endl;
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
                if (add(key)) {
                    cout << endl << "Успешно. \nСравнений: " << com << endl;
                }else{
                    cout << endl << "Провал" << endl;
                }
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

void task11_2(){

    count = 10;
    SetConsoleOutputCP(CP_UTF8);
    create();
    while(dialog());

}
