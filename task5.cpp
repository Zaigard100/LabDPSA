#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>
#include "dataio.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

const int queue_size = 10;

struct Queue {
    int front, last;
    int array[queue_size];
    int count;

    void init() {
        front = 0;
        last = 0;
        count = 0;
    }

    bool isEmpty() {
        if (count == 0) return true;
        return false;
    }

    bool isFull() {
        if (count == queue_size) return true;
        return false;
    }

    void add(int _value) {
        if (!isFull()) {
            array[last] = _value;
            last++;
            count++;
            last = last % queue_size;
        }
        else {
            cout << "Очередь заполнена. " << endl;
        }
    }

    void delite() {
        if (!isEmpty()) {
            front++;
            count--;
            front = front % queue_size;
        }else {
            cout << "Очередь пуста. " << endl;
        }
    }

    void showQueue() {
        cout << "Состояние очереди: " << endl;
        if (!isEmpty()) {
            int i = front;
            do
            {
                cout << i << " - " << array[i] << endl;
                i++;
                i = i % queue_size;
            } while (i != last);
        }
        else {
            cout << "Очередь пуста. " << endl;
        }
    }
};

Queue queue;

bool dialog() {

    cout << "1. Добавить элемент" << endl;
    cout << "2. Удалить элемент" << endl;
    cout << "3. Вывести элемент" << endl;
    cout << "4. Показать состояние очереди" << endl;
    cout << "5. Очистить очередь" << endl;
    cout << "6. Проверить на пустоту" << endl;
    cout << "7. Проверить на полноту" << endl;
    cout << "9. Выйти из программы" << endl;
    cout << "Введите команду: ";

    switch (read_uint()) {
        case 1: {
            if(queue.isFull()) {
                cout << "Очередь заполнена. " << endl;
            }else{
               queue.add(read_int());
            }
            return true;
        }
        case 2: {
            queue.delite();
            return true;
        }
        case 3: {
            cout << queue.array[queue.front] << endl;
            return true;
        }
        case 4: {
            queue.showQueue();
            return true;
        }
        case 5: {
            while (!queue.isEmpty()) {
                queue.delite();
            }
            queue.init();
            return true;
        }
        case 6: {
            if(queue.isEmpty()) {
                cout << "Очередь пуста" << endl;
            }else {
                cout << "Очередь не пуста" << endl;
            }
            return true;
        }
        case 7: {
            if(queue.isEmpty()) {
                cout << "Очередь полна" << endl;
            }else {
                cout << "Очередь не полна" << endl;
            }
            return true;
        }
        case 9: {
            exit(0);
        }
        default: {
            cout << "Неверная команда" << endl;
            return true;
        }
    }

}

void task5() {
    SetConsoleOutputCP(CP_UTF8);
    queue.init();
    while(dialog());
}