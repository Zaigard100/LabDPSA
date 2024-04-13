#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

int* arr = nullptr;
int* copy_arr = nullptr;
int count = -1;

void create(int c){
    if(arr!= nullptr) delete arr;
    arr = new int[c];
    count = c;
    for(int  i = 0; i<c;i++) arr[i] = rand()%c;
}
void createNo2(int c){
    if(arr!= nullptr) delete arr;
    arr = new int[c];
    count = c;
    int iter = 1;
    arr[0] = rand()%c;
    for(int  i = 1; i<c;i++){
        bool ch = false;
        int a;
        while(true){
            ch = false;
            a = rand()%c;
            for(int j = 0;j<iter;j++){
                if(a == arr[j]) {
                    ch = true;
                    break;
                }
            }
            if(!ch){
                break;
            }
        }
        iter++;
        arr[i] = a;
    }
}
void copy(){
    if(copy_arr!= nullptr) delete copy_arr;
    if(arr == nullptr) return;
    copy_arr = new int[count];
    for(int  i = 0; i<count;i++) copy_arr[i] = arr[i];
}
void show(int* a, int c){
    cout<<endl;
    for(int  i = 0; i<c;i++) cout<<a[i]<<" ";
    cout<<endl;
}
void bucketAddArr(){
    int moves = 0;
    int* sort = new int[count];
    for (int i = 0; i < count; i++, moves++)
        sort[copy_arr[i]] = copy_arr[i];
    show(sort,count);
    cout << endl << "Сравнений не проводилось." << endl
         << "Количество пересылок: " << moves << endl;
    delete[] sort;
};

void bucketNoAddArr(){
    int moves = 0, comps = 0;
    for (int i = 0; i < count; i++)
        while (++comps && copy_arr[i] != i)
        {
            int temp = copy_arr[i];
            copy_arr[i] = copy_arr[temp];
            copy_arr[temp] = temp;
            moves++;
        }
    show(copy_arr, count);
    cout << endl << "Количество сравнений: " << comps << endl
         << "Количество перестановок: " << moves << endl;
}

struct List
{
    int data;
    List* next = nullptr;
};

void add(List* plist, int inf)
{
    while (plist->next != nullptr)
        plist = plist->next;
    plist->next = new List;
    plist->next->data = inf;
    plist->next->next = nullptr;
}

void clear(List* head)
{
    while (head != nullptr)
    {
        List* temp = head;
        head = head->next;
        delete temp;
    }
}

void comonBucketRep(List* massive, int n)
{
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        List* current = massive[i].next;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
    }
    cout << endl;
}

void buketRep()
{
    List* sort = new List[count];
    int moves = 0;

    for (int i = 0; i < count; i++)
        sort[i].next = nullptr;

    for (int i = 0; i < count; i++, moves++)
        add(&sort[copy_arr[i]], copy_arr[i]);

    comonBucketRep(sort, count);
    cout << endl << "Количество пересылок: " << moves << endl;
    for (int i = 0; i < count; i++)
        clear(sort[i].next);
    delete[] sort;
}

void radix()
{
    List* sort = new List[10];
    int k = count - 1;
    int i = 0;
    int permutation = 0;
    while (k >= 1)
    {
        i++;
        k /= 10;
        for (int j = 0; j < 10; j++)
            sort[j].next = nullptr;
        for (int j = 0; j < count; j++)
        {
            int div = 1;
            for (int l = 0; l < i; l++, div *= 10);
            add(&sort[((copy_arr[j] % div) * 10) / div], copy_arr[j]);
            permutation++;
        }
        for (int j = 0, l = 0; l < count; j++) //из sort в array
        {
            List* temp = sort[j].next;
            while (temp != nullptr)
            {
                copy_arr[l] = temp->data;
                temp = temp->next;
                l++;
                permutation++;
            }
        }
        for (int j = 0; j < 10; j++)
            clear(sort[j].next);
    }
    show(copy_arr,count);
    std::cout << "Количество перестановок: " << permutation << std::endl;
    delete[] sort;
}

bool dialog(){
    cout << "\n1.Создать массив." << endl;
    cout << "2.Создать массив без повторок." << endl;
    cout << "3.Вывести массив" << endl;
    cout << "4.Сортировать карманным с доп массивом вывести" << endl;
    cout << "5.Сортировать корманным  без доп массива вывести." << endl;
    cout << "6.Сортировать корманной обобщенной вывести." << endl;
    cout << "7.Сортировать поразрядной вывести." << endl;
    cout << "9.Завершить работу программы." << endl;
    cout << "Введите команду: ";
    switch (read_uint()) {
        case 1:{
            cout << "Введите кол-во элементов: " << endl;
            create(read_uint());
            return true;
        }
        case 2:{
            cout << "Введите кол-во элементов: " << endl;
            createNo2(read_uint());
            return true;
        }
        case 3:{
            show(arr,count);
            return true;
        }
        case 4:{
            copy();
            bucketAddArr();
            return true;
        }
        case 5:{
            copy();
            bucketNoAddArr();
            return true;
        }
        case 6:{
            copy();
            buketRep();
            return true;
        }
        case 7:{
            copy();
            radix();
            return true;
        }
        case 9:{
            if(arr!= nullptr) delete arr;
            if(copy_arr!= nullptr) delete copy_arr;
            return false;
        }
    }
}

void task10(){
    srand(static_cast<unsigned int>(time(0)));
    SetConsoleOutputCP(CP_UTF8);
    while(dialog());
}
