#include <iostream>

using namespace std;

// class A {
// public:
//     A* a;
//     A (A* x = NULL) {
//         a = this;
//     }
//     A* operator-> () {
//         return this;
//     }
// };

// int main () {
//     A b;
//     A(b->a);
//     A(b->a->a);
//     return 0;
// }

// class A {
// public:
//     int a;
//     A (A &x = NULL, A &y = NULL) {
//         this->a = 0;
//     }
//     A operator, (A x) const {
//         return x;
//     }
// };

// int main () {
//     A a;
//     A(a,a);
//     A((a,a));
//     return 0;
// }

struct B {
    int b;
    B (int x): b(x) {}
    virtual void f() {
        cout << "B.f\n";
    }
    virtual void h() = 0;
};

struct T {
    int a;
    T(int x = 1): a(x) {}
};

struct D: public B {
    int d;

    D (): B(0) {
        int d = 0;
    }
    void h() {}
    void f() {
        cout << "D.f\n";
    }
};

struct C: public B {
    int c;
    C (): B(0) {
        int c = 0;
    }
    void h() {}
};

struct P {
    T *pt;
    P (T *t1 = NULL) {
        pt = t1;
        if (!t1) {
            pt = new T;
        }
    }
    T* operator* () {
        return pt;
    }
};

int main () {
    D d;
    C c;
    B *pb = &d, *pb1 = &c;
    pb->f();
    pb1->f();
    T t;
    P p(&t);
    (*p).a = 28;
    cout << t.a << endl;
    P p1(NULL);
    cout << (*p1).a << endl;
    return 0;


}