#include <iostream>
using namespace std;

class Interest
{ 
private:  
    float p;   // principal
    float r;   // rate
    float t;   // time
       
public:
    void input()
    {
        cout << "Enter principal: ";
        cin >> p;

        cout << "Enter rate: ";
        cin >> r;

        cout << "Enter time: ";
        cin >> t;
    }

    float simple_interest()
    {
        return (p * r * t) / 100;
    }

    float annual()   // annual compound interest (1 year)
    {
        return (p * r) / 100;
    }
};

int main()
{
    // Dynamically allocate object
    Interest *i = new Interest();

    i->input();

    cout << "Simple interest is " << i->simple_interest() << "\n";
    cout << "Annual interest is " << i->annual() << "\n";

    // Free memory
    delete i;

    return 0;
}

