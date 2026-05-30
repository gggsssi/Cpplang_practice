#include<iostream>
using namespace std;     // allows use of cin and cout

// Class to calculate properties of a cuboid
class Shapes
{
private:
    float l, b, h;   // length, breadth and height of cuboid

public:
    // Function to take input from user
    void input()
    {
        cout << "Enter length, breadth and height:\n";
        cin >> l >> b >> h;
    }

    // Function to calculate volume of cuboid
    float volume()
    {
        float vol = l * b * h;
        return vol;
    }

    // Function to calculate total surface area (TSA)
    float tsa()
    {
        float tsa = 2 * (l*b + l*h + b*h);
        return tsa;
    }

    // Function to calculate lateral surface area (LSA)
    float lsa()
    {
        float lsa = 2 * h * (l + b);
        return lsa;
    }
};

int main()
{
    Shapes s;      // create object of class
    s.input();     // take input

    // display results
    cout << "Volume = " << s.volume() << endl;
    cout << "TSA = " << s.tsa() << endl;
    cout << "LSA = " << s.lsa() << endl;
}

