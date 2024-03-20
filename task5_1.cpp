#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct TreeNode{
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    int data;
};

TreeNode *tree;


void createTree(TreeNode *tr,int c){
    tr->data = rand() % 99;
    c--;
    if (c / 2 + c % 2 > 0)
    {
        tr->left = new TreeNode;
        createTree(tr->left, c / 2 + c % 2);
    }
    if (c / 2 > 0)
    {
        tr->right = new TreeNode;
        createTree(tr->right, c / 2);
    }

}

void del(TreeNode *temp){
    if(temp->left != nullptr) del(temp->left);
    if(temp->right != nullptr) del(temp->right);
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

void reverseSymmetricShow(TreeNode *temp,int lvl = 0){
    if(temp->right != nullptr) symmetricShow(temp->right,lvl+1);
    for(int i = 0; i < lvl;i++) cout<<"     ";
    cout<<temp->data<<endl;
    if(temp->left != nullptr) symmetricShow(temp->left,lvl+1);
}

void dialog(){
    cout << "\n1.Создать дерево." << endl;
    cout << "2.Удалить дерево." << endl;
    cout << "3.Показать в прямом порядке." << endl;
    cout << "4.Показать в симметричном порядке" << endl;
    cout << "5.Показать в обратно-симметричном порядке" << endl;
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите команду: ";

    switch (read_uint()) {
        case 1: {
            if (tree != nullptr){
                del(tree);
                tree = nullptr;
            }
            tree = new TreeNode;
            createTree(tree, read_uint());
            have = true;
            break;
        }
        case 2: {
            if (tree != nullptr){
                del(tree);
                tree = nullptr;
            }
            break;
        }
        case 3: {
            if ( tree != nullptr) rightOrderTreeShow(tree);
            break;
        }
        case 4: {
            if ( tree != nullptr) symmetricShow(tree);
            break;
        }
        case 5: {
            if ( tree != nullptr) reverseSymmetricShow(tree);
            break;
        }
        case 9: {
            if (tree != nullptr){
                del(tree);
                tree = nullptr;
            }
            exit(0);
            break;
        }
        default:{
            cout << "Не верная команда..." << endl;
            break;
        }
    }
}

void task5_1(){
    tree = new TreeNode;
    SetConsoleOutputCP(CP_UTF8);
    while(true) dialog();
}