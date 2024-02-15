#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct QueueElement {
    char value;
    QueueElement* next;
};

QueueElement* front;
QueueElement* last;

void init() {
    front = new QueueElement;
    front->next = nullptr;
    last = front;
}

bool isEmpty() {
    if (front->next == nullptr) return true;
    return false;
}

void add(char _value) {
    QueueElement* temp = new(std::nothrow) QueueElement;
    if (temp != nullptr)
    {
        temp->value = _value;
        temp->next = nullptr;
        if (isEmpty()) {
            front->next = temp;
        }
        else {
            last->next = temp;
        }
        last = temp;
        cout << "В очередь встала буква " << last->value << ";" << endl;
    }
    else {
        cout << "Нехватка оперативной памяти" <<
            "завершение работы программы" << endl;
        exit(0);
    }
}

void delite() {
    if (!isEmpty()) {
        char deletedValue;
        QueueElement* temp = front->next;
        front->next = temp->next;
        if (isEmpty()) { last = front; }
        deletedValue = temp->value;
        delete temp;
        cout << "Из очереди ушла буква " << deletedValue << ";" << endl;
    }
    else {
        cout << "Уходить некому: очередь пуста. " << endl;
    }
}

void showQueue() {
    cout << "Состояние очереди: " << endl;
    if (!isEmpty()) {
        QueueElement* temp = front->next;
        int i = 1;
        while (temp != nullptr)
        {
            cout << i++ << " - " << temp->value << endl;
            temp = temp->next;
        }
    }
    else {
        cout << "Очередь пуста. " << endl;
    }
}

void start() {
    int counter = 0;
    while (true) {
        int count ;

        if ((((1 + rand()) % 100) % 2) == 0) {
            count = 1 + rand() % 3; // кол-во входящих
            cout << "Кол-во входящих символов: " << count << endl;

            for (int i = 0; i < count; i++)
                add(('A' + rand() % ('Z' - 'A')));
        }

        else {
            count = 1 + rand() % 3;// кол-во выходящих
            cout << "Кол-во выходящих символов: " << count << endl;

            for (int i = 0; i < count; i++)
                if (isEmpty()) {
                    cout << "Очередь пуста. Остановка." << endl;
                    break;
                }else{
                    delite();
                }
        }
        showQueue();
        counter++;

        if (counter % 20 == 0) {
            cout << "Вы хотите выйти(y/n): " << endl;
            char ch;
            cin >> ch;
            if (ch == 'y') {
                cout << "Программа остановлена" << endl;
                while(!isEmpty()) {
                    delite();
                }
                delete front;
                exit(0);
            }
        }
        Sleep(2000);
    }
}

void task7() {
    SetConsoleOutputCP(CP_UTF8);
    srand(static_cast<unsigned int>(time(0)));
    init();
    start();
}