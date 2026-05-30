#include <iostream>
using namespace std;

// Class to calculate properties of a cuboid
class Shapes
{
private:
    float l, b, h;   // length, breadth and height of cuboid

public:
    void input()
    {
        cout << "Enter length, breadth and height:\n";
        cin >> l >> b >> h;
    }

    float volume()
    {
        return l * b * h;
    }

    float tsa()
    {
        return 2 * (l*b + l*h + b*h);
    }

    float lsa()
    {
        return 2 * h * (l + b);
    }
};

int main()
{
    // Dynamically allocate object
    Shapes *s = new Shapes();

    s->input();

    cout << "Volume = " << s->volume() << endl;
    cout << "TSA = " << s->tsa() << endl;
    cout << "LSA = " << s->lsa() << endl;

    // Free allocated memory
    delete s;

    return 0;
}

