#include <iostream>
using namespace std;

class Physics
{ 
private:
    float v, u;
    float t; // in hour 

public:
    void input()
    {
        cout << "Enter initial velocity u: ";
        cin >> u;

        cout << "Enter final velocity v: ";
        cin >> v;

        cout << "Enter time t: ";
        cin >> t;
    }

    float acceleration()
    {
        float c = v - u;
        float accln = c / t;
        return accln;
    }
};

int main()
{
    Physics* p = new Physics();   // dynamically allocated object

    p->input();
    cout << "The acceleration = " << p->acceleration() << endl;

    delete p;   // free allocated memory

    return 0;
}

