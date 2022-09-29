#include <iostream>
#include <cstring>

using namespace std;
class Str
{
    char *s;
    int len;
public:
    Str()
    {
        s = new char[(len = 0) + 1];
        *s = '\0';
        cout << 1 << endl;
    };
    Str(const char* s1)
    {
        s = new char[(len = strlen(s1)) + 1];
        strcpy(s, s1);
        cout << 2 << endl;
    };
    Str(const Str& St)
    {
        s = new char[(len = strlen(St.s)) + 1];
        strcpy(s, St.s);
        cout << 3 << endl;
    };
    Str& operator = (const Str& St)
    {
        if(this == &St)
            return *this;
        delete []s;
        s = new char[St.len + 1];
        len = St.len;
        strcpy(s, St.s);
        cout << 4 << endl;
        return *this;
    }
    Str(Str && other) {
        s = other.s;
        len = other.len;
        other.s = NULL;
        cout << 5 << endl;
    }
    Str& operator= (Str && rhs) {
        if (&rhs != this)
            delete []s;
        s = rhs.s;
        len = rhs.len;
        rhs.s = NULL;
        cout << 6 << endl;
        return *this;
    }
    ~Str()
    {
        delete []s;
        cout << "~Str" << endl;
    }
};

class Man {
    Str name;
    int year;
public:
    //Man(char* s = "", int y = 0): name(s), year(y){
    //    cout << "Man create";
    //};
    Man(char *s = (char*)"", int y = 0) {
        name = s;
        year = y;
        cout << "Man create" << endl;
    }
    // Man (const Man& other) {
    //     name = other.name;
    //     year = other.year;
    //     cout << "Man copy";
    // }
    Man (const Man& other): name(other.name), year(other.year){
        cout << "Man copy" << endl;
    }
    Man& operator= (const Man& other) {
        if (this == &other) 
            return *this;
        name = other.name;
        year = other.year;
        cout << "Man op" << endl;
        return *this;
    }
    ~Man() {
        cout << "~Man" << endl;
    }
};

Str func() {
    Str s("abcd");
    return s;
}

int main()
{
    // Str s1;
    // Str s2("abc");
    // Str s3(s2);

    // s2 = func();

    // Str s4 = std::move(func());

    Man man1;
    Man man2("asd", 2017);
    Man man3 = man2;

    man1 = man2 = man3;

    return 0;
}