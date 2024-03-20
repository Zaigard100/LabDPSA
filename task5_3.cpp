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

TreeNode* find(TreeNode* tr,int find) {
    if(tr->data == find) return tr;
    if (tree->left != nullptr) {
        TreeNode* l = find(tree->left, find);
        if(l != nullptr) return l;
    }
    if (tree->right != nullptr) {
        TreeNode* r = find(tree->right, find);
        if(r != nullptr) return r;
    }
    return nullptr;
}

void add(TreeNode* tr,int find,int data) {
    TreeNode* f = find(tr,find);
    cout<<"Введите команду"<<endl;
    if (f->left == nullptr) cout<<"1.Добавить влево"<<endl;
    if (f->right == nullptr) cout<<"2.Добавить вправо"<<endl;
    switch (read_uint()) {
        case 1: {
            //if (f->left == nullptr)
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
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите команду: ";

    switch (read_uint()) {
        case 1: {
            if(tree!=nullptr) {
                deleteTree(tree);
                tree = nullptr;
            }
            cout<<"Введите кол-во элелементов"<<endl;
            createTree(tree,read_uint());
            return true;
        }
        case 2: {
            // TODO поиск нужной вершины
            // TODO добовление ноды
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
        default: {
            cout<<"Не валидная команда..."<<endl;
            return true;
        }
    }

}

void task5_3(){

}