#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "Base Constructor\n"; }
    virtual ~Base() { cout << "Base Destructor\n"; } // ? Virtual
};

class Derived : public Base {
public:
    Derived() { cout << "Derived Constructor\n"; }
    ~Derived() { cout << "Derived Destructor\n"; }// memory restoration happens if we are calling destructors 
};

int main() {
    Base* ptr = new Derived();
    delete ptr;  // ? Calls both Base and Derived destructors correctly!
    return 0;
}

