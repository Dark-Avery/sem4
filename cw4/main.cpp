#include <iostream>

using namespace std;

class Circle {
    int x, y, r;
    static int count;
public:
    Circle (int _r = 1, int _x = 1, int _y = 1): r(_r), x(_x), y(_y) {count++;} 
    virtual void print () {
        cout << "r=" << r << " x=" << x << " y=" << y << "\n";
    }
    virtual void multiply (int k) {
        r *= k;
    }
    virtual double S () {
        return r * r * 3.14;
    }
    friend int Circle_count ();
};

class Ring: public Circle {
    int x, y, r, in_r;
    static int count;
public:
    Ring (int _r = 1, int _x = 1, int _y = 1, int _in_r = 0): r(_r), x(_x), y(_y), in_r(_in_r) {
        try {
            if (r < in_r)
                throw -1;
        }
        catch(...) {
            r = in_r;
        }
        count++;
    }
    void print () {
        cout << "r=" << r << " x=" << x << " y=" << y << " in_r=" << in_r << "\n";
    }
    void multiply (int k) {
        r *= k;
        in_r *= k;
    }
    double S () {
        return 3.14 * (r * r - in_r * in_r);
    }
    friend int Ring_count ();
};

int Circle::count = 0;
int Ring::count = 0;

int Ring_count () {
    return Ring::count;
}

int Circle_count () {
    return Circle::count - Ring_count();
}

void ptr_to (const Circle *pC) {
    cout << typeid(*pC).name() + 1 << "\n";
}

class F {
public:
    template <typename T>
    void x(T &t, int k) {
        t.multiply(k);
    }
};

int main () {
    Circle c1, c2, c3;
    ptr_to(&c1);
    c1.print();

    Ring r1(2, 1, 1, 1), r2;
    ptr_to(&r1);
    r1.print();

    F f;
    f.x(c1, 2);
    f.x(r1, 3);

    ptr_to(&c1);
    c1.print();

    ptr_to(&r1);
    r1.print();

    cout << c1.S() << " " << r1.S() << "\n";
    cout << Circle_count() << " " << Ring_count() << "\n";
    return 0;
}