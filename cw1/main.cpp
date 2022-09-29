#include <iostream>

using namespace std;

class Arr {
    int *arr;
    int size;
public:
    Arr(int s, int date = 0):size(s) {
        arr = new int[s];
        for (int i = 0; i < size; arr[i++] = date);
    }
    Arr(Arr&& a) {
        size = a.size;
        arr = a.arr;
        a.arr = nullptr;
        cout << "&&a\n";
    }
    Arr(const Arr& a) {
        size = a.size;
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = a.arr[i];
        }
    }
    Arr &operator= (Arr && a) {
        if (&a != this)
            delete [] arr;
        size = a.size;
        arr = a.arr;
        a.arr = nullptr;
        cout << "=&&\n";
        return *this;
    }
    Arr operator= (const Arr& a) {
        if (this == &a)
            return a;
        size = a.size;
        arr = new int[a.size];
        for (int i = 0; i < a.size; i++) {
            arr[i] = a.arr[i];
        }
        return *this;
    }
    int &operator[] (int i) {
        return arr[i];
    }
    Arr operator!() {
        Arr a(size);
        for (int i = 0; i < size; i++)
            a.arr[i] = !arr[i];
        return a;
    }
    friend Arr operator&(const Arr a1, const Arr a2);
    friend Arr operator&(const Arr a, int k);
    friend ostream& operator<<(ostream& stream, const Arr &a); 
    ~Arr() {
        delete [] arr;
    }
};

Arr operator&(const Arr a, int k) {
    Arr a1(a.size);
    int i = 0;
    while (i < a.size) {
        a1.arr[i] = a.arr[i] & k;
        i++;
    }
    return a1;
}

Arr operator&(const Arr a1, const Arr a2) {
    int min, max;
    if (a1.size > a2.size) {
        min = a2.size;
        max = a1.size;
    } else {
        min = a1.size;
        max = a2.size;
    }
    Arr a(max);
    int i = 0;
    while (i < max) {
        if (i < min)
            a.arr[i] = a1.arr[i] & a2.arr[i];
        else
            a.arr[i] = 0;
        i++;
    }
    return a;
}

ostream& operator<<(ostream& stream, const Arr &a) {
    for (int i = 0; i < a.size; i++)
        stream << a.arr[i] << ' ';
    stream << '\n';
    return stream;
}

Arr func() {
    Arr a(4,8);
    return a;
}

int main() {
    Arr a1(5), a2(1), a3(4,2);
    const Arr a4(5);
    cout << a1 << a2 << a3 << a4 << "\n----------\n";
    a2 = a2 & 2;
    a3 = (!a2) & a3;
    a1 = a4 & a3;
    a1[1] = 100;
    cout << a1 << a2 << a3 << a4 << "\n----------\n";
    Arr a5 = std::move(func());
    cout << a1 << a2 << a3 << a4 << a5 << "\n----------\n";
    cout << "End of program\n";
    return 0;
}