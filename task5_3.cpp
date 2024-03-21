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

void createTree(TreeNode *tr,int count){
    tr->data = rand() % 99;
    count--;
    if (count / 2 + count % 2 > 0)
    {
        tr->left = new TreeNode;
        createTree(tr->left, count / 2 + count % 2);
    }
    if (count / 2 > 0)
    {
        tr->right = new TreeNode;
        createTree(tr->right, count / 2);
    }

}

TreeNode* find(TreeNode* tr,int f) {
    if(tr->data == f) return tr;
    if (tr->left != nullptr) {
        TreeNode* l = find(tr->left, f);
        if(l != nullptr) return l;
    }
    if (tr->right != nullptr) {
        TreeNode* r = find(tr->right, f);
        if(r != nullptr) return r;
    }
    return nullptr;
}

bool add(TreeNode* tr,TreeNode* f,int data) {
    if(f==nullptr){
        cout<<"Элемент не найден"<<endl;
        return false;
    }
    if(f->left == nullptr||f->right == nullptr) cout<<"Введите команду"<<endl;
    else{
        cout<<"Элемент уже заполнен"<<endl;
        return false;
    }
    if (f->left == nullptr) cout<<"1.Добавить влево"<<endl;
    if (f->right == nullptr) cout<<"2.Добавить вправо"<<endl;
    switch (read_uint()) {
        case 1: {
            if (f->left != nullptr){
                cout<<"Неверная команда"<<endl;
                return true;
            }
            f->left = new TreeNode;
            f->left->data = data;
            return false;
        }
        case 2: {
            if (f->right!= nullptr){
                cout<<"Неверная команда"<<endl;
                return true;
            }
            f->right = new TreeNode;
            f->right->data = data;
            return false;
        }
        default: {
            cout<<"Неверная команда"<<endl;
            return true;
        }
    }
}

void deleteTree(TreeNode *temp){
    if(temp->left != nullptr) deleteTree(temp->left);
    if(temp->right != nullptr) deleteTree(temp->right);
    delete temp;
}

void rightOrderTreeShow(TreeNode *temp,int lvl = 0){
    if(temp == nullptr) return;
    for(int i = 0; i < lvl;i++) cout<<"     ";
    cout<<temp->data<<endl;
    rightOrderTreeShow(temp->left,lvl+1);
    rightOrderTreeShow(temp->right,lvl+1);
}

void symmetricShow(TreeNode *temp,int lvl = 0){
    if(temp->left != nullptr) symmetricShow(temp->left,lvl+1);
    for(int i = 0; i < lvl;i++) cout<<"     ";
    cout<<temp->data<<endl;
    if(temp->right != nullptr) symmetricShow(temp->right,lvl+1);
}

bool dialog() {
    cout << "\n1.Создать дерево." << endl;
    cout << "2.Добавить элемент." << endl;
    cout << "3.Показать в прямом порядке." << endl;
    cout << "4.Показать в симметричном порядке" << endl;
    cout << "5.Удалить дерево." << endl;
    cout << "6.Найти элемент." << endl;
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите команду: ";

    switch (read_uint()) {
        case 1: {
            if(tree!=nullptr) {
                deleteTree(tree);
                tree = nullptr;
            }
            cout<<"Введите кол-во элелементов: "<<endl;
            tree = new TreeNode;
            createTree(tree,read_uint());
            return true;
        }
        case 2: {
            cout<<"Введите искомый элелемент: "<<endl;
            int f = read_uint();
            TreeNode* ff = find(tree,f);
            if(ff == nullptr){
                cout<<"Элемент не найден"<<endl;
                return false;
            }
            cout<<"Введите добовляемые элелементы: "<<endl;
            int d = read_uint();
            while(add(tree,ff,d));
            return true;
        }
        case 3: {
            if ( tree != nullptr) rightOrderTreeShow(tree);
            return true;
        }
        case 4: {
            if ( tree != nullptr) symmetricShow(tree);
            return true;
        }
        case 5: {
            if(tree!=nullptr) {
                deleteTree(tree);
                tree = nullptr;
            }
            return true;
        }
        case 9: return false;
        case 6: {
            cout<<"Введите искомый элелемент: "<<endl;
            int f = read_uint();
            TreeNode* ff = find(tree,f);
            if(ff == nullptr){
                cout<<"Элемент не найден"<<endl;
            }else {
                cout<<"Элемент найден"<<endl;
            }
            return true;
        }
        default: {
            cout<<"Не валидная команда..."<<endl;
            return true;
        }
    }

}

void task5_3(){
    tree = new TreeNode;
    srand(static_cast<unsigned int>(time(0)));
    SetConsoleOutputCP(CP_UTF8);
    while(true) dialog();
}