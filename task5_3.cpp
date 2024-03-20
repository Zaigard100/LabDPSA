#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct TreeNode {
    int data;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

TreeNode* tree = nullptr;
bool dialog() {
    cout << "\n1.Создать дерево." << endl;
    cout << "2.Добавить элемент." << endl;
    cout << "3.Показать в прямом порядке." << endl;
    cout << "4.Показать в симметричном порядке" << endl;
    cout << "5.Показать в обратно-симметричном порядке" << endl;
    cout << "6.Удалить дерево." << endl;
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите команду: ";

    switch (read_uint()) {
        case 1: {
            if(tree!=nullptr) {
                // TODO функция удаление дерева
            }
            // TODO создание дерева
            return true;
        }
        case 2: {
            // TODO поиск нужной вершины
            // TODO добовление ноды
            return true;
        }
        case 3: {
            //TODO из 5.1
            return true;
        }
        case 4: {
            //TODO из 5.1
            return true;
        }
        case 5: {
            //TODO из 5.1
            return true;
        }
        case 6: {
            //TODO из 5.1 функция удаления
            return true;
        }
        case 9: return false;
        default: {
            cout<<"Не валидная команда..."<<endl;
            return true;
        }
    }

}

void task5_3(){

}