#include <iostream>
#include <vector>
using namespace std;

class  A {
public:
   virtual void  f () const { cout << "1отладчик";}
   virtual void  h () { cout << "2редактор связей";}
};

class  B: public A {
public:
             void  f () { cout << "333система программирования";}
             void  h () {cout << "4система автоматизированного тестирования";}
};

int main() {
      B b;
      A & r = b;
    b.f();
 
}