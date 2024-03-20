#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct TreeNode{
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int data = -1;
};

struct TreeStack{
    int level = -1;
    TreeNode* tree = nullptr;
    TreeStack* next = nullptr;
};
TreeNode* tree = nullptr;
TreeStack* sp = nullptr;

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

void deleteTree(TreeNode *temp){
    if(temp->left != nullptr) deleteTree(temp->left);
    if(temp->right != nullptr) deleteTree(temp->right);
    delete temp;
}

void symmetricShow(TreeNode *temp,int lvl = 0){
    if(temp->left != nullptr) symmetricShow(temp->left,lvl+1);
    for(int i = 0; i < lvl;i++) cout<<"     ";
    cout<<temp->data<<endl;
    if(temp->right != nullptr) symmetricShow(temp->right,lvl+1);
}

void add(TreeStack* tree){
    if (sp == nullptr) sp = tree;
    else{
        tree->next = sp;
        sp = tree;
    }
}

TreeStack* del(){
    if (sp != nullptr){
        TreeStack* toDelete = sp;
        sp = sp->next;
        toDelete->next = nullptr;
        return toDelete;
    }
    return nullptr;
}

void noRecursionSymmetricShow(TreeNode* tree, int level = 0)
{
    TreeStack* tempStack;
    TreeNode* tempNode = tree;
    while (true) {
        while (tempNode != nullptr){
            tempStack = new TreeStack;
            tempStack->level = level++;
            tempStack->tree = tempNode;
            add(tempStack);
            tempNode = tempNode->left;
        }
        tempStack = del();
        if (tempStack == nullptr) break;
        else {
            level = tempStack->level;
            tempNode = tempStack->tree;
            for (int i = 0; i < level; i++) cout << "     ";
            cout << tempNode->data << endl;
            tempNode = tempNode->right;
            level++;
        }
    }
}

void dialog(){
    cout << "\n1.Создать дерево." << endl;
    cout << "2.Удалить дерево." << endl;
    cout << "3.Показать в рекурсивно-симметричном порядке." << endl;
    cout << "4.Показать в симметричном порядке" << endl;
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите команду: ";

    switch (read_uint()) {
        case 1: {
            if(tree!=nullptr) {
                deleteTree(tree);
                tree = nullptr;
            }
            createTree(tree, read_uint());
            break;
        }
        case 2: {
            if(tree!=nullptr) {
                deleteTree(tree);
                tree = nullptr;
            }
            break;
        }
        case 3: {
            if ( tree != nullptr) symmetricShow(tree);
            break;
        }
        case 4: {
            if ( tree != nullptr) noRecursionSymmetricShow(tree);
            break;
        }
        case 9: {
            if(tree!=nullptr) {
                deleteTree(tree);
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

void task5_2(){
    tree = new TreeNode;
    SetConsoleOutputCP(CP_UTF8);
    while(true) dialog();
}