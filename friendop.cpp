#include <iostream>
using namespace std;

class Complex {
private:
    int real, img;
public:
    Complex(int r = 0, int i = 0) : real(r), img(i) {}
    void display() {
        cout << real << " + i" << img << endl;
    }
    // Declare friend function for operator+
    friend Complex operator+( Complex& c1, Complex& c2);
};

// Define the friend function outside the class
Complex operator+(Complex& c1,Complex& c2) {
    Complex temp;
    temp.real = c1.real + c2.real;
    temp.img = c1.img + c2.img;
    return temp;
}

int main() {
    Complex c1(5, 3), c2(10, 5), c3;
    cout << "c1 = "; c1.display();
    cout << "c2 = "; c2.display();
    c3 = c1 + c2;  // Uses overloaded operator+
    cout << "c1 + c2 = "; c3.display();
    return 0;
}
