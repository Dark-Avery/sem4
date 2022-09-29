#include <iostream>

using namespace std;

class A {
public:
    int f1() {
        A i, j;
        return (i,j)[i,j](i,j);
    }  
    operator int () {
        return 42;
    }
    A operator[] (A i) {
        cout << "[]";
        return i;
    }
    A operator() (A i, A j) {
        cout << "()";
        return j;
    }
    A operator() (A i) {
        cout << "()";
        return i;
    }
    A operator, (A i) {
        cout << ",";
        return i;
    }
};

int main () {
    A a1;
    cout << a1.f1();
    return 0;
}