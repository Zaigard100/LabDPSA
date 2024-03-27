#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct TreeNode
{
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int data = -1;
    int count = 1;
};

TreeNode* treeHead = nullptr;

TreeNode* find(TreeNode* tr,int find) {
    if(tr->data == find) return tr;
    if (tr->left != nullptr) {
        TreeNode* l = find(tr->left, find);
        if(l != nullptr) return l;
    }
    if (tr->right != nullptr) {
        TreeNode* r = find(tr->right, find);
        if(r != nullptr) return r;
    }
    return nullptr;
}

void add(TreeNode* tree, int data){
    if (tree->data == data) {
        tree->count++;
        return;
    }
    if (tree->data > data){
        if (tree->left == nullptr) {
            tree->left = new TreeNode;
            tree->left->data = data;
        }else {
            add(tree->left, data);
        }
    }else {
        if (tree->right == nullptr)
        {
            tree->right = new TreeNode;
            tree->right->data = data;
        }
        else{
            add(tree->right, data);
        }
    }
}

void createTree(int count){
    treeHead = new TreeNode;
    treeHead->data = 1 + rand() % 99;

    for (count--; count > 0; count--)
    {
        int d;
        do {
            d = 1 + rand() % 99;
        } while (find(treeHead, d) != nullptr);
        add(treeHead, d);
    }

}

void deleteTree(TreeNode *temp){
    if(temp->left != nullptr) deleteTree(temp->left);
    if(temp->right != nullptr) deleteTree(temp->right);
    delete temp;
}

void deleteNode(TreeNode* tree, int del){

    TreeNode* t = tree;
    TreeNode* t_from = nullptr;
    while (t->data != del)
    {
        t_from = t;
        if (del < t->data)
            t = t->left;
        else
            t = t->right;
    }

    if (t->left == nullptr && t->right == nullptr)
    {
        if (t_from->left == t)
            t_from->left = nullptr;
        else
            t_from->right = nullptr;
        delete t;
    }
    else if (t->left == nullptr && t->right != nullptr) {
        if (t_from->left == t)
            t_from->left = t->right;
        else
            t_from->right = t->right;
        delete t;
    }
    else if (t->right == nullptr && t->left != nullptr)
    {
        if (t_from->left == t)
            t_from->left = t->left;
        else
            t_from->right = t->left;
        delete t;
    }
    else if (t->right != nullptr && t->left != nullptr)
    {
        TreeNode* tt = t->right;
        TreeNode* tt_from = tt;
        while (tt->left != nullptr)
        {
            tt_from = tt;
            tt = tt->left;
        }

        t->data = tt->data;
        if (tt == t->right)
            t->right = tt->right;
        else
            tt_from->left = tt->right;
        delete tt;
    }


bool dialog() {
    cout <<"1.Создать дерево" << endl;
    cout <<"2.Добавить вершину" << endl;
    cout <<"3.Поиск" << endl;
    cout <<"4.Показать" << endl;
    cout <<"5.Вывод всех вершин в одну строку по порядку" << endl;
    cout <<"6.Удалить вершину" << endl;
    cout <<"9.Выход" << endl;

    switch (read_uint()) {
        case 1: {

            break;
        }
        case 2: {

            break;
        }
        case 3: {

            break;
        }
        case 4: {

            break;
        }
        case 5: {

            break;
        }
        case 6: {

            break;
        }
        case 9: {

            break;
        }
    }

}
