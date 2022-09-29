#include <iostream>
#include <cstring>

using namespace std;
class Bank {
    char *name, *date;
    int count, number;
public:
    Bank () {
        name = new char[1];
        *name = '\0';
        date = new char[1];
        *date = '\0';
        count = -1;
        number = -1;
        cout << "//Bank()\n";
    }
    Bank (char* n, int num, int c, char* d) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        date = new char[strlen(d) + 1];
        strcpy(date, d);
        number = num;
        count = c;
        cout << "//Bank create\n";
    }
    Bank (const Bank& St) {
        name = new char[strlen(St.name) + 1];
        date = new char[strlen(St.date) + 1];
        strcpy(name, St.name);
        strcpy(date, St.date);
        count = St.count;
        number = St.number;
        cout << "//Bank(const Bank&)\n";
    }
    Bank (Bank && other) {
        name = other.name;
        date = other.date;
        count = other.count;
        number = other.number;
        other.name = NULL;
        other.date = NULL;
        cout << "//Bank(Bank&&)\n";
    }
    Bank& operator = (const Bank& St) {
        if (this == &St)
            return *this;
        delete [] name;
        delete [] date;
        name = new char[strlen(St.name) + 1];
        date = new char[strlen(St.date) + 1];
        count = St.count;
        number = St.number;
        strcpy(name, St.name);
        strcpy(date, St.date);
        cout << "//Bank=(const Bank&)\n";
        return *this;
    }
    Bank& operator= (Bank && other) {
        if (this == &other) {
            return *this;
        };
        delete [] name;
        delete [] date;
        name = other.name;
        date = other.date;
        count = other.count;
        number = other.number;
        other.name = NULL;
        other.date = NULL;
        cout << "//Bank=(Bank&&)\n";
        return *this;
    }
    void print_Bank () {
        if (number == -1)
            cout << "Empty element\n";
        else {
            cout << name << " ";
            cout << number << " ";
            cout << count << " ";
            cout << date << "\n";
        }
    }
    ~Bank () {
        delete [] name;
        delete [] date;
        cout << "//~Bank\n";
    }
};

struct Node {
    Bank elem;
    Node *next, *prev;
};

class List {
    Node *head, *tail;
public:
    List () {
        head = NULL;
        tail = NULL;
    }
    bool empty() {
        return head == NULL;
    }
    void push_front(Bank x) {
        Node *p = new Node;
        p->elem = x;
        p->next = NULL;
        p->prev = NULL;
        if (empty()) {
            head = p;
            tail = p;
        } else {
            p->next = head;
            head->prev = p;
            head = p;
        }
    }
    void push_back(Bank x) {
        Node *p = new Node;
        p->elem = x;
        p->next = NULL;
        p->prev = NULL;
        if (empty()) {
            head = p;
            tail = p;
        } else {
            p->prev = tail;
            tail->next = p;
            tail = p;
        }
    }
    Bank front() {
        if (empty()) {
            cout << "Empty List(front())\n";
            Bank x;
            return x;
        }
        return head->elem;
    }
    Bank back() {
        if (empty()) {
            cout << "Empty List(back())\n";
            Bank x;
            return x;
        }
        return tail->elem;
    }
    void pop_front() {
        if (empty())
            cout << "Empty List(pop_front())\n";
        else {
            Node *p = head;
            head = head->next;
            if (empty())
                tail = NULL;
            else
                head->prev = NULL;
            delete p;
        }
    }
    void pop_back() {
        if (empty())
            cout << "Empty List(pop_back())\n";
        else {
            Node *p = tail;
            tail = tail->prev;
            if (!tail)
                head = NULL;
            else
                tail->next = NULL;
            delete p;
        }
    }
    void print() {
        Node *p = head;
        if (empty())
            cout << "Empty List\n";
        else {
            int i = 0;
            while (p) {
                cout << i << " - ";
                i++;
                p->elem.print_Bank();
                p = p->next;
            }
        }
    }
    int size() {
        int size_list = 0;
        Node *p = head;
        while (p) {
            size_list++;
            p = p->next;
        }
        return size_list;
    }
    void insert(int pos, Bank x) {
        if (pos < 0) {
            cout << "Error with position insert (pos < 0)";
            return;
        }
        if (empty()) {
            cout << "Empty List (error insert)\n";
            return;
        }
        if (pos > size()) {
            cout << "Error with position insert (pos > size)";
            return;
        }
        Node *p = head;
        for (int i = 0; i < pos; i++)
            p = p->next;
        if (p == head) 
            push_front(x);
        else if (!p)
            push_back(x);
        else {
            Node *h = new Node;
            h->elem = x;
            h->next = p;
            h->prev = p->prev;
            p->prev->next = h;
            p->prev = h;
        }
    }
    void erase(int pos) {
        if (pos < 0) {
            cout << "Error with position erase (pos < 0)";
            return;
        }
        if (empty()) {
            cout << "Empty List (error erase)\n";
            return;
        }
        if (pos > size()-1) {
            cout << "Error with position erase (pos > size)";
            return;
        }
        Node *p = head;
        for (int i = 0; i < pos; i++)
            p = p->next;
        if (p == head) 
            pop_front();
        else if (p == tail)
            pop_back();
        else {
            p->next->prev = p->prev;
            p->prev->next = p->next;
            delete p;
        }
    }
    ~List() {
        Node *p = NULL;
        while (head) {
            p = head;
            head = head->next;
            delete p;
        }
    }
};

class Queue: public List {
    int len, max_len;
public:
    Queue (int n = 6) {
        len = 0;
        max_len = n;
    }
    bool empty () {
        return len == 0;
    }
    bool full () {
        return len == max_len;
    }
    int size () {
        return len;
    }
    void print () {
        if (!empty())
            List::print();
    }
    Bank front () {
        if (empty()) {
            cout << "!!!Queue is empty\n";
            Bank x;
            return x;
        } else
            return(List::front());
    }
    void pop () {
        if (empty())
            cout << "!!!Queue is empty\n";
        else {
            List::pop_front();
            len--;
        }
    }
    void back (Bank x) {
        if (full())
            cout << "!!!Queue is full\n";
        else {
            List::push_back(x);
            len++;
        }
    }
    ~Queue () {

    }
};

Bank func() {
    Bank x((char*)"Anatoliy", 4459, 90000, (char*)"10.02.2022");
    return x;
}

int main() {
    Bank x1 = std::move(func());
    Bank x2((char*)"Ivan", 3242, 124, (char*)"8.02.2022");
    Queue q1;
    Queue q2(2);
    cout << "q1 empty? " << q1.empty() << "\n";
    cout << "q2 empty? " << q2.empty() << "\n";
    q1.back(x1);
    q1.back(x2);
    q1.back(q1.front());
    q1.back(x2);
    q2.back(x2);
    q2.back(q1.front());
    cout << "\nprint q1, size = " << q1.size() << "\n";
    q1.print();
    cout << "\nprint q2, size = " << q2.size() << "\n";
    q2.print();
    cout << "\nq1 full? " << q1.full() << "\n";
    cout << "q2 full? " << q2.full() << "\n";
    q1.pop();
    q2.pop();
    q2.pop();
    cout << "\nprint q1, size = " << q1.size() << "\n";
    q1.print();
    cout << "\nprint q2, size = " << q2.size() << "\n";
    q2.print();
    cout << "\nEnd of program\n";
    return 0;
}