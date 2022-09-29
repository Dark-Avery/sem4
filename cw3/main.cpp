#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T>
void print(T const &v) {
    typename T::iterator i;
    for(i = v.begin(); i != v.end(); ++i) {
        cout << *i;
    }
}
 
int main() {
    vector<char> vector = { 'x', 'y', 'z' };
    print(vector);
 
    return 0;
}