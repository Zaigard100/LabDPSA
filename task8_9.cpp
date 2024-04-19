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
    for(int  i = 0; i<c;i++) arr[i] = rand()%1000;
}
void copy(){
    if(copy_arr!= nullptr) delete copy_arr;
    if(arr == nullptr) return;
    copy_arr = new int[count];
    for(int  i = 0; i<count;i++) copy_arr[i] = arr[i];
}
void show(){
    cout<<endl;
    for(int  i = 0; i<count;i++) cout<<arr[i]<<" ";
    cout<<endl;
}
void show_copy(){
    cout<<endl;
    for(int  i = 0; i<count;i++) cout<<copy_arr[i]<<" ";
    cout<<endl;
}
void bubble(){
    copy();
    int com = 0;
    int per = 0;
    for(int i = 0;i<count;i++){
        for(int j = count-1;j>i;j--){
            if(copy_arr[j]<copy_arr[j-1]){
                int temp = copy_arr[j];
                copy_arr[j] = copy_arr[j-1];
                copy_arr[j-1] = temp;
                per++;
            }
            com++;
        }
    }
    show_copy();
    cout<< "Перестановок: "<<per<<endl;
    cout<< "Сравнений: "<<com<<endl;
}
void insert(){
    copy();
    int com = 0;
    int per = 0;
    for(int i = 1;i<count;i++){
        int temp = copy_arr[i];
        per++;
        int j = i-1;
        while (com++ && j>=0 && temp < copy_arr[j]){

            copy_arr[j+1] = copy_arr[j];
            per++;
            j--;
        }
        copy_arr[j+1] = temp;
        per++;
    }
    show_copy();
    cout<< "Перестановок: "<<per/3<<endl;
    cout<< "Сравнений: "<<com<<endl;
}
void choise(){
    copy();
    int com = 0;
    int per = 0;
    int min;
    for(int i = 0;i<count;i++){
        min = i;
        for(int j = min+1;j<count;j++,com++){
            if(copy_arr[j]< copy_arr[min]) min = j;
        }
        if(min!=i){
            int temp = copy_arr[min];
            copy_arr[min] = copy_arr[i];
            copy_arr[i] = temp;
            per++;
        }
    }
    show_copy();
    cout<< "Перестановок: "<<per<<endl;
    cout<< "Сравнений: "<<com<<endl;
}

void shell(int *steps,int steps_count){
    copy();
    int com = 0;
    int per = 0;
    int perestanov = 0;
    for (int m = 0; m < steps_count; m++)
    {
        int k = steps[m];
        for (int i = k; i < count; i++)
        {
            int temp = copy_arr[i];
            perestanov++;
            int j = i - k;
            while (com++ && j >= 0 && temp < copy_arr[j])
            {
                copy_arr[j + k] = copy_arr[j];
                j = j - k;
                perestanov++;
            }
            copy_arr[j + k] = temp;
            per++;
        }
    }
    show_copy();
    cout<< "Перестановок: "<<per<<endl;
    cout<< "Сравнений: "<<com<<endl;
}
int com_q,per_q;
void quickSort(int left=0, int right=count-1)
{
    int i = left;
    int j = right;
    int middle = copy_arr[(left + right) / 2];
    while (i <= j)
    {
        while (++com_q && copy_arr[i] < middle) i++;
        while (++com_q && copy_arr[j] > middle) j--;
        if (i <= j)
        {
            int temp = copy_arr[i];
            copy_arr[i] = copy_arr[j];
            copy_arr[j] = temp;
            i++;
            j--;
            per_q++;
        }
    }
    if (left < j)
        quickSort(left, j);
    if (i < right)
        quickSort(i, right);
}

void s(int k, int n){
    while (true)
    {
        int left = 2 * k + 1;
        int right = 2 * k + 2;
        int largest;
        if (left < n && copy_arr[left] > copy_arr[k])
            largest = left;
        else
            largest = k;
        com_q++;

        if (right < n && copy_arr[right] > copy_arr[largest]) largest = right;
        com_q++;

        if (largest == k) break;

        int temp = copy_arr[k];
        copy_arr[k] = copy_arr[largest];
        copy_arr[largest] = temp;
        per_q++;
        k = largest;
    }
}

void pyramida(){
    for (int i = (count - 1) / 2; i >= 0; i--)
        s(i, count);
    for (int i = count - 1; i >= 1; i--)
    {
        int temp = copy_arr[0];
        copy_arr[0] = copy_arr[i];
        copy_arr[i] = temp;
        per_q++;
        s(0, i);
    }
}

bool dialog() {
    cout << "\n1.Создать массив." << endl;
    cout << "2.Вывести массив." << endl;
    cout << "3.Сортировать пузырьком вывести." << endl;
    cout << "4.Сортировать выбором вывести" << endl;
    cout << "5.Сортировать вставками вывести." << endl;
    cout << "6.Сортировать методом Шела вывести." << endl;
    cout << "7.Сортировать быстро вывести." << endl;
    cout << "7.Сортировать пирамидой вывести." << endl;
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
            show();
            return true;
        }
        case 3:{
            bubble();
            return true;
        }
        case 4:{
            choise();
            return true;
        }
        case 5:{
            insert();
            return true;
        }
        case 6:{
            cout << "Введите кол-во шагов: " << endl;
            int step_c = read_uint();
            cout << "Введите шаги: " << endl;
            int* st = read_arr(step_c);
            shell(st,step_c);
            return true;
        }
        case 7:{
            copy();
            com_q = 0;
            per_q = 0;
            quickSort();
            show_copy();
            cout<< "Перестановок: "<<per_q<<endl;
            cout<< "Сравнений: "<<com_q<<endl;
            return true;
        }
        case 8:{
            copy();
            com_q = 0;
            per_q = 0;
            pyramida();
            show_copy();
            cout<< "Перестановок: "<<per_q<<endl;
            cout<< "Сравнений: "<<com_q<<endl;
            return true;
        }
        case 9:{
            if(arr!= nullptr) delete arr;
            if(copy_arr!= nullptr) delete copy_arr;
            return false;
        }
    }
}



void task8_9() {
    srand(static_cast<unsigned int>(time(0)));
    SetConsoleOutputCP(CP_UTF8);
    while(dialog());
}