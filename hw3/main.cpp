#include <iostream>

using namespace std;

class base {
public:
    int x;
    virtual int get_x () = 0;
    virtual int calculation () = 0;
};

class square: public base {
public:
    square (int a) {
        x = a;
    }
    int get_x () override {
        return x;
    }
    int calculation () override {
        return x * x;
    }
};

class cube: public base {
public:
    cube (int a) {
        x = a;
    }
    int get_x () override {
        return x;   
    }
    int calculation () override {
        return x * x * x;
    }
};

class Array_Obj {
    int len;
public:
    base** arr;
    Array_Obj (int s = 10) {
        len = s;
        arr = new base*[len];
    }
    ~Array_Obj () {
        for (int i = 0; i < len; i++) {
            delete arr[i];
        }
        delete [] arr;
    }
};

int main () {
    Array_Obj array(4);
    array.arr[0] = new square(2);
    array.arr[1] = new cube(2);
    array.arr[2] = new square(3);
    array.arr[3] = new cube(3);
    
    cout << array.arr[0]->get_x() << "^2 = " << array.arr[0]->calculation() << "\n";
    cout << array.arr[1]->get_x() << "^3 = " << array.arr[1]->calculation() << "\n";
    cout << array.arr[2]->get_x() << "^2 = " << array.arr[2]->calculation() << "\n";
    cout << array.arr[3]->get_x() << "^3 = " << array.arr[3]->calculation() << "\n";

    cout << "End of program\n";
    return 0;
}