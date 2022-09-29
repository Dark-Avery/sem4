#include <iostream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

template <typename T>
void print(T const &v) {
    typename T::const_iterator i;
    for (i = v.begin(); i != v.end(); i++)
        cout << *i;
    cout << "\n";
}

template <typename T>
void rprint(T const &v) {
    typename T::const_reverse_iterator i;
    for (i = v.rbegin(); i != v.rend(); i++)
        cout << *i;
    cout << "\n";
}

template <typename T1, typename T2>
void change(T1 &v1, T2 const &v2) {
    typename T1::iterator i1;
    typename T2::const_iterator i2;
    int k = 0;
    i2 = v2.begin();
    for (i1 = v1.begin(); i1 != v1.end(); i1++) {
        if (i2 == v2.end())
            break;
        if (k % 2) 
            i1 = v1.insert(i1+1, *i2);
        i2++;
        k++;
    }
}

template <typename T>
void remov(T &v) {
    typename T::iterator i;
    int k = 0;
    for (i = v.begin(); i != v.end(); ) {
        if ((k+1) % 3 == 0)
            i = v.erase(i);
        else
            ++i;
        k++;
    }
}

int main () {
    vector<int> vector1 = {1, 2, 3, 4, 5};
    list<char> list1 = {'a', 'b', 'c', 'd', 'e'};
    const vector<int> vector2 = {1, 2, 3};
    const list<char> list2 = {'a', 'b', 'c'};
    // print(vector1);
    

    list<int> listtemp = {9, 8, 7, 6, 5};
    // print(listtemp);
    change(vector1, listtemp);
    print(vector1);
    remov(vector1);
    print(vector1);
    print(list1);
    remov(list1);
    print(list1);
    return 0;
}