#include <iostream>

using namespace std;

class Arr {
    int *arr;
    int size;
public:
    Arr(int s, int date = 0): size(s) {
        arr = new int[s];
        for(int i = 0; i < size; arr[i++]=date);
    }
    ~Arr() {
        delete [] arr;
    }
};

int main() {
    Arr a1(5);
    Arr a2(10,1);
    Arr a3(4,2);
    const Arr a4(5);
    cout << a1 << a2 << a3 << a4;
    a2 = a2 & 2;
    a3 = (!a2) & a3;
    a1 = a4 & a3;
    a1[1] = 100;
    cout << a1 << a2 << a3 << a4;
    // if (true) 
    //     Arr a = move(a2);
    cout << 2;
    return 0;
}