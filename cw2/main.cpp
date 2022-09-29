#include <iostream>

using namespace std;

class A {
    int a;
    A (int i = 0): a(i) {};
    A (const A &b) {
        a = b.a;
    }
public:
    void print () {
        cout << a << "\n";
    }
    A* f (int i = 0) {
        A *x;
        x = new A(i);
        return x;
    }
    ~A() {

    }
};

int main () {
    A *a1 = A::f(3);
    a1->print();
    
    return 0;
}