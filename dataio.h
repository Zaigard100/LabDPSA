#ifndef DATAIO_H
#define DATAIO_H

using std::string;
using std::cin;
using std::cout;
using std::endl;

int read_int() {
    string data;
    bool run = true;
    string buf;
    int iter = 1;
    bool err = false,space = false;
    getline(cin,data);
    while(run){
        for(char c:data) {
            if(c == '-') {
                if(buf.empty()) {
                    buf+=c;
                }else {
                    err = true;
                    cout << "Err: \'" <<c<<"\'("<<iter<<")"<<endl;
                }
            }else if(c == '0') {
                if(space) {
                    err = true;
                    cout << "Err: \'" <<c<<"\'("<<iter<<")"<<endl;
                }else{
                    if(buf == "-") {
                        buf = "0";
                    }else {
                        buf+=c;
                    }
                }
            }else if(isdigit(c)) {
                if(buf!="0") {
                    buf += c;
                }else {
                    err = true;
                    cout << "Err: \'" <<c<<"\'("<<iter<<")"<<endl;
                }
            }else if(c == ' ') {
                if(!buf.empty()) {
                    space = true;
                }
            }else {
                err = true;
                cout << "Err: \'" <<c<<"\'("<<iter<<")"<<endl;
            }
            iter++;
        }
        if(err) {
            buf = "";
            iter = 1;
            err = false;
            space = false;
            data = "";
            getline(cin,data);
        }else{
            try {
                return stoi(buf);
            }catch (std::invalid_argument iaex) {
                cout << "Error!" << endl;
                buf = "";
                iter = 1;
                err = false;
                space = false;
                data = "";
                getline(cin,data);
            }
        }
    }
}

unsigned read_uint() {
    int i = read_int();
    while (i < 0) {
        i = read_int();
    }
    return i;
}

int *read_arr(unsigned n, string data="") {

    string enter = "";
    int *arr = new int[n];
    bool err = false;
    unsigned iter = 0;

    while (true) {
        if (data == "") {
            getline(cin, enter);
        } else {
            enter = data;
        }
        enter += '\n';
        string buf = "";

        for (unsigned i = 0; i < enter.length(); i++) {

            if (enter[i] == '-') {
                if (buf == "") {
                    buf += enter[i];
                } else {
                    err = true;
                    cout << "Недопустимый символ: " << enter[i] << '(' << i << ")\n";
                }
            } else if (isdigit(enter[i])) {
                if (buf == "0") {
                    err = true;
                    cout << "Недопустимый символ: " << enter[i] << '(' << i << ")\n";
                }
                if (enter[i] == '0' && buf == "-") {
                    buf = "0";
                } else {
                    buf += enter[i];
                }
            } else if (enter[i] == ' ' || enter[i] == '\n') {
                if (buf != "") {
                    if (iter > n - 1) {
                        err = true;
                        cout << "Введенное кол-во данных не соответствует " << n << '\n';
                        break;
                    }
                    arr[iter] = stoi(buf);
                    buf = "";
                    iter++;
                } else {
                }
            } else {
                err = true;
                cout << "Недопустимый символ: " << enter[i] << '(' << i << ")\n";
            }
        }
        if (iter != n) {
            err = true;
            cout << "Введенное кол-во данных не соответствует " << n << '\n';
        }
        if (err) {
            if (data != "") {
                return new int[1]{INT_MIN};
            } else {
                enter = "";
                err = false;
                iter = 0;
                cout << "Повторите ввод: ";
            }
        } else {
            return arr;
        }
    }
}
string read_line() {
    string enter;
    getline(cin,enter);
    return enter;
}

#endif //DATAIO_H
