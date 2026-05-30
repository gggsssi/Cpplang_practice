#include <iostream>
using namespace std;

class Percentage
{
private:
    int n;
    float *sub;   // Pointer for dynamic array

public:
    // Constructor
    Percentage()
    {
        n = 0;
        sub = nullptr;
    }

    void input()
    {
        cout << "Enter the number of subjects: ";
        cin >> n;

        // Dynamic memory allocation
        sub = new float[n];

        cout << "Enter the marks of " << n << " subjects:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> sub[i];
        }
    }

    float percentage()
    {
        float sum = 0;

        for (int i = 0; i < n; i++)
        {
            sum += sub[i];
        }

        return (sum / (n * 100)) * 100;
    }

    // Destructor to free memory
    ~Percentage()
    {
        delete[] sub;
    }
};

int main()
{
    // Dynamically allocate object
    Percentage *p = new Percentage();

    p->input();
    cout << "The percentage is " << p->percentage() << endl;

    delete p;   // Free object memory

    return 0;
}

