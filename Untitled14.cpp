#include <iostream>
using namespace std;

class RiverMonitoring
{
private:
    int days;            // number of days
    float *levels;       // dynamic array for water levels

public:
    // Constructor
    RiverMonitoring()
    {
        days = 0;
        levels = nullptr;
    }

    // Function to take input
    void input()
    {
        cout << "Enter number of days: ";
        cin >> days;

        levels = new float[days];   // dynamic allocation

        cout << "Enter river water level for each day:\n";
        for (int i = 0; i < days; i++)
        {
            cin >> levels[i];
        }
    }

    // Function to calculate average water level
    float averageLevel()
    {
        float sum = 0;
        for (int i = 0; i < days; i++)
        {
            sum += levels[i];
        }
        return sum / days;
    }

    // Function to find highest water level
    float highestLevel()
    {
        float max = levels[0];
        for (int i = 1; i < days; i++)
        {
            if (levels[i] > max)
                max = levels[i];
        }
        return max;
    }

    // Destructor
    ~RiverMonitoring()
    {
        delete[] levels;
    }
};

int main()
{
    // Dynamically allocate object
    RiverMonitoring *river = new RiverMonitoring();

    river->input();

    cout << "Average Water Level = " << river->averageLevel() << endl;
    cout << "Highest Water Level = " << river->highestLevel() << endl;

    // Free memory
    delete river;

    return 0;
}

