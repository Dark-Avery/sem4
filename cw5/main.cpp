#include <iostream>
#include <string>

using namespace std;

int main() {
    string line;
    cin >> line;
    int i = 0;
    while (line[i] == 'a')
        i++;
    if (i != 1) {
        cout << "Errora\n";
        return 1;
    }
    if ((line.size()-2-i) % 2 != 0) {
        cout << "Errorsize\n";
        return 1;
    }
    int count = 0;
    while ((line[i + count] == 'b' || line[i + count] == 'a') && i + count < line.size()-2) {
        if (count % 2 == 0) {
            if (line[i + count] != 'b') {
                cout << "Error aab\n";
                return 1;
            }
        } else {
            if (line[i + count] != 'a') {
                cout << "Error bba\n";
                return 1;
            }
        }
        count++;
    }
    if (count < 2) {
        cout << "Error\n";
        return 1;
    }
    i += count;
    if (line[i] == 'b' && line[i+1] == 'b' && (i + 2) == line.size())
        cout << "YES" << endl;
    else 
        cout << "NO" << endl;
    return 0;
}