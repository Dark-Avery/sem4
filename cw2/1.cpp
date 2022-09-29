#include <iostream>

using namespace std;

class A {
    int a;
    A(int i = 0): a(i){} //Конструктор закрыт
    A(const A &b) {
        a = b.a;
    }
public:
    static int flag;
    static A* ptr;
    static A* func(int i) {
        if (!flag) {
            A* a1 = new A(i);
            ptr = a1;
            flag = 1;
        }
        return ptr;
    }
    void print() {
        cout << a << "\n";
    }
    ~A () {}
};

int A::flag = 0;
A* A::ptr;

int main() {
    A* a1 = A::func(13);
    a1 -> print();

    A* a2 = A::func(7);
    a2 -> print();
    delete A::ptr;
    return 0;
}