#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <array>
#include <iterator>

using namespace std;

class Print {
public:
    template <typename T>
    void operator() (T const &t) {
        typename T::const_iterator i;
        for (i = t.begin(); i != t.end(); i++)
            cout << *i;
        cout << "\n";
    }

    template <typename T>
    void operator() (T* t, int n) {
        for (int i = 0; i != n; i++)
            cout << t[i];
        cout << "\n";
    }
};

class Revers {
public:
    template <typename T>
    void operator() (T &t) {
        typename T::iterator i;
        typename T::iterator j;
        for (i = t.begin(), j = t.end(); i != j && i != --j; i++)
            iter_swap(i, j);
    }

    template <typename T>
    void operator() (T* t, size_t n) {
        for (int i = 0; i < n/2; i++) {
            T temp = t[i];
            t[i] = t[n-1-i];
            t[n-1-i] = temp;
            // swap(t[i], t[n-1-i]); 
        }
    }
};

int main () {
    Revers revers;
    Print print;

    list<int> L = {1, 2, 3, 4, 5};
    cout << "list<int> =      ";
    print(L);
    cout << "revers(list) =   ";
    revers(L);
    print(L);

    vector<int> V = {1, 2, 3, 4, 5};
    cout << "vector<int> =    ";
    print(V);
    cout << "revers(vector) = ";
    revers(V);
    print(V);

    string S = "Hello, world!";
    cout << "string =         ";
    print(S);
    cout << "revers(string) = ";
    revers(S);
    print(S);

    array<int, 5> A = {1, 2, 3, 4, 5};
    cout << "array<int, n> =  ";
    print(A);
    cout << "revers(array) =  ";
    revers(A);
    print(A);

    int arr [5] = {1, 2, 3, 4, 5};
    cout << "int arr [n] =    ";
    print(arr, 5);
    cout << "revers(arr) =    ";
    revers(arr, 5);
    print(arr, 5);
    return 0;
}