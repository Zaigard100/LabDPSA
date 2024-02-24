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

string read_line() {
    string enter;
    getline(cin,enter);
    return enter;
}

#endif //DATAIO_H
