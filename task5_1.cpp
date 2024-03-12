#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct TreeNode{
    TreeNode *left;
    TreeNode *right;
    int data;
};

unsigned count;
TreeNode *tree;

void createTree(TreeNode *tr,int count){
    tr->data = rand() % 99;
    count--;
    //Если останется нечетное количество вершин, то "лишняя" вершина пойдет влево
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

void rightOrderTreeShow(TreeNode *temp,int lvl){
    if(temp->left == nullptr) return;
    for(int i = 0; i < lvl;i++){
        cout<<"     ";
    }
    cout<<temp->data<<endl;
    rightOrderTreeShow(temp->left,lvl+1);
    rightOrderTreeShow(temp->right,lvl+1);
}
void task5_1(){
    tree = new TreeNode;
    createTree(tree,3);
    rightOrderTreeShow(tree,0);
}