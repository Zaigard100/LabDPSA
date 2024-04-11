#include <iostream>
#include <string>
#include "dataio.h"
#include <vector>
#include <memory>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <locale.h>
#endif

using std::string;
using std::cin;
using std::cout;
using std::endl;

#define LN { std::cout << __LINE__ << std::endl; }
#define DEB(x) { std::cout << #x << "=(" << (x) << ") "; }

static std::string ch_hor = "\u2500" /*─*/, ch_ver = "\u2502" /*│*/, ch_ddia = "\u250C" /*┌*/, ch_rddia = "\u2510" /*┐*/, ch_udia = "\u2514" /*└*/, ch_ver_hor = "\u251C\u2500" /*├─*/, ch_udia_hor = "\u2514\u2500" /*└─*/, ch_ddia_hor = "\u250C\u2500" /*┌─*/, ch_ver_spa = "\u2502 " /*│ */;


struct TreeNode{
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int data = -1;
    int count = 1;
};

TreeNode* treeHead = nullptr;

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
void addNR(TreeNode* tree, int data) {
    TreeNode* t = tree;
    while (true) {
        if (t->data == data) {
            t->count++;
            return;
        }
        if (t->data > data){
            if (t->left == nullptr) {
                t->left = new TreeNode;
                t->left->data = data;
                return;
            }else {
                t = t->left;
            }
        }else {
            if (t->right == nullptr)
            {
                t->right = new TreeNode;
                t->right->data = data;
                return;
            }
            else{
                t = t->right;
            }
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

void reverseSymmetricShow(TreeNode *temp,int lvl = 0){
    if(temp->right != nullptr) reverseSymmetricShow(temp->right,lvl+1);
    for(int i = 0; i < lvl;i++) cout<<"     ";
    cout<<temp->data<<endl;
    if(temp->left != nullptr) reverseSymmetricShow(temp->left,lvl+1);
}

void showInLine(TreeNode* tree){
    if (tree->left != nullptr)
        showInLine(tree->left);
    cout << tree->data << "(" << tree->count << ") ";
    if (tree->right != nullptr)
        showInLine(tree->right);
}

void deleteNode(TreeNode* tree, int del) {
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
}

void dump2(TreeNode const * node, std::string const & rpref = "", std::string const & cpref = "", std::string const & lpref = "") {
    if (!node) return;
    if (node->right)
        dump2(node->right, rpref + "  ", rpref + ch_ddia_hor, rpref + ch_ver_spa);
    std::cout << cpref << std::to_string(node->data) << std::endl;
    if (node->left)
        dump2(node->left, lpref + ch_ver_spa, lpref + ch_udia_hor, lpref + "  ");
}

bool dialog(){
    cout <<"1.Создать дерево" << endl;
    cout <<"2.Добавить вершину" << endl;
    cout <<"3.Поиск" << endl;
    cout <<"4.Показать дерево" << endl;
    cout <<"5.Показать вершины в одну строку по порядку" << endl;
    cout <<"6.Удалить вершину" << endl;
    cout <<"7.Показать вершины, но красиво" << endl;
    cout <<"9.Выход" << endl;
    cout <<"Введите комманду: ";

    switch (read_uint()) {
        case 1: {
            cout << endl;
            cout <<"Введите кол-во элементов: ";
            createTree(read_uint());
            return true;
        }
        case 2: {
            cout << endl;
            cout <<"Добавить" << endl;
            cout <<"Введите элемент: ";
            add(treeHead,read_int());
            return true;
        }
        case 3: {
            cout << endl;
            cout <<"Поиск" << endl;
            cout <<"Введите элемент: ";
            TreeNode* f = find(treeHead,read_int());
            if(f == nullptr) {
                cout <<"Элемент не найден" << endl;
            }else {
                cout <<"Элемент "<< f->data <<" найден в кол-во " << f->count << endl;
            }
            return true;
        }
        case 4: {
            cout << endl;
            reverseSymmetricShow(treeHead);
            return true;
        }
        case 5: {
            cout << endl;
            showInLine(treeHead);
            cout << endl;
            return true;
        }
        case 6: {
            cout << endl;
            cout <<"Удалить" << endl;
            cout <<"Введите элемент: ";
            int d = read_int();
            if(find(treeHead,d) != nullptr) {
                deleteNode(treeHead,d);
            }else {
                cout <<"Элемент не найден" << endl;
            }
            return true;
        }
        case 7: {
            cout << endl;
            dump2(treeHead);
            cout << endl;
            return true;
        }
        case 9: {
            cout << "Выход" << endl;
            return false;
        }
        default: {
            cout<<"Не валидная команда..."<<endl;
            return true;
        }
    }

}

void task6(){
    treeHead = new TreeNode;
    srand(static_cast<unsigned int>(time(0)));
    SetConsoleOutputCP(CP_UTF8);
    while(true) dialog();
}
