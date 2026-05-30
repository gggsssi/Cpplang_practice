#include <iostream>
using namespace std;

class CHQ
{
private:
    static int p;   // central fund 
    static int q;   

public:
    // Static function to deduct money
    static void Balance(int x)
    {
        q = p - x;
        p = q;
    }

    // Static function to display remaining balance
    static void showBalance()
    {
        cout << "Remaining Balance: " << p << endl;
    }
};

// Definition of static variables
int CHQ::p = 50;   
int CHQ::q = 0;

int main()
{
    int a, b;

    cout << "Enter the number of sub companies: ";
    cin >> a;

    for (int i = 0; i < a; i++)
    {
        cout << "Enter the money received by sub company " << i + 1 << ": ";
        cin >> b;

        CHQ::Balance(b);
    }

    CHQ::showBalance();

    return 0;
}

