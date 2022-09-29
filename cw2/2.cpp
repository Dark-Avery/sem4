#include <iostream>
using namespace std;

class A {
    int a;
    ~A() {};
public:
    A (int i = 0): a(i) {};
    A (const A & c) {
        a = c.a;
    };
    A *f (int a1 = 0) {
        A *c = new A(a1);
        return c;
    }
    void g () {
        delete this;
    }
    void print() {
        cout << a << "\n";
    }
};

int main() {
    A *p3 = (A*)::operator new (3 * sizeof(A));
    A *p = new (p3) A;
    p = p->f(1);
    p3 += 1;
    A *p1 = new (p3) A;
    p1 = p1->f(2);
    p3 += 1;
    A *p2 = new (p3) A;
    p2 = p2->f(3);

    p->g();
    p1->g();
    p2->g();

    p3 -= 2;
    ::operator delete(p3);
    return 0;
}