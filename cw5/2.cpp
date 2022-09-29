#include <iostream>
using namespace std;

char c;
void gc() {
    cin >> c;
}   

void Error() {
    cout << "ERROR" << endl;
    exit(1);
}

void A() {
    if (c == 'a') {
        gc();
        A();
    } 
}

void B() {
    if (c == 'b') {
        gc();
        B();
    } 
}

void S() {
    gc();
    if (c == 'a') {
        A();
        if (c != 'b') {
            Error();
        }
    } else if (c == 'c') {
        gc();
        if (c == 'b') {
            B();
            if (c != '.')
                Error();
        } else {
            Error();
        }
    } 
}

int main () {
    S();
    if (c == '.') {
        cout << "CORRECT" << endl;
        return 0;
    }
    gc();
    if (c != '.')
        Error();
    cout << "CORRECT" << endl;
    return 0;
}
