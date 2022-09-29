#include <iostream>
#include <cstring>
using namespace std;

class Str{
    char* s;
    int len;
public:
    Str(){
        s = new char[(len = 0)+1];
        *s = '\0';
    };
    Str(const char* s1){
        s = new char[(len = strlen(s1))+1];
        strcpy(s, s1);
    };
    Str(const Str& st){
        s = new char[(len = strlen(st.s))+1];
        strcpy(s, st.s);
        cout << s << ' ' << st.s << '\n';
    };
    Str& operator = (const Str& St) {
        if (this == &St)
            return *this;
        delete [] s;
        s = new char[(St.len)+1];
        len = St.len;
        strcpy(s, St.s);
        return *this;
    };
    ~Str(){
        delete [] s;
    }
};

int main() {
    Str s1;
    Str s2("abc");

    Str s3(s2);
    s1 = s2;
    return 0;
}