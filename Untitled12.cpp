#include <iostream>
using namespace std;

class ElectricityBill
{
private:
    int days;           // number of days
    float *units;       // dynamic array for daily unit consumption
    float rate;         // cost per unit

public:
    // Constructor
    ElectricityBill()
    {
        days = 0;
        units = nullptr;
        rate = 6.0;     // fixed rate per unit (?6)
    }

    // Function to take input
    void input()
    {
        cout << "Enter number of days: ";
        cin >> days;

        units = new float[days];   // dynamic allocation

        cout << "Enter units consumed each day:\n";
        for (int i = 0; i < days; i++)
        {
            cin >> units[i];
        }
    }

    // Function to calculate total units
    float totalUnits()
    {
        float total = 0;
        for (int i = 0; i < days; i++)
        {
            total += units[i];
        }
        return total;
    }

    // Function to calculate total bill
    float calculateBill()
    {
        return totalUnits() * rate;
    }

    // Destructor
    ~ElectricityBill()
    {
        delete[] units;
    }
};

int main()
{
    // Dynamically allocate object
    ElectricityBill *bill = new ElectricityBill();

    bill->input();

    cout << "Total Units Consumed = " << bill->totalUnits() << endl;
    cout << "Total Electricity Bill = ?" << bill->calculateBill() << endl;

    // Free memory
    delete bill;

    return 0;
}

