#include <iostream>
using namespace std;

class DroneDelivery
{
private:
    int deliveries;        // number of deliveries
    float *distance;       // dynamic array for delivery distances

public:
    // Constructor
    DroneDelivery()
    {
        deliveries = 0;
        distance = nullptr;
    }

    // Function to take input
    void input()
    {
        cout << "Enter number of deliveries: ";
        cin >> deliveries;

        distance = new float[deliveries];   // dynamic allocation

        cout << "Enter distance (in km) for each delivery:\n";
        for (int i = 0; i < deliveries; i++)
        {
            cin >> distance[i];
        }
    }

    // Function to calculate total distance
    float totalDistance()
    {
        float total = 0;
        for (int i = 0; i < deliveries; i++)
        {
            total += distance[i];
        }
        return total;
    }

    // Function to find longest delivery
    float longestDelivery()
    {
        float max = distance[0];
        for (int i = 1; i < deliveries; i++)
        {
            if (distance[i] > max)
                max = distance[i];
        }
        return max;
    }

    // Destructor
    ~DroneDelivery()
    {
        delete[] distance;
    }
};

int main()
{
    // Dynamically allocate object
    DroneDelivery *drone = new DroneDelivery();

    drone->input();

    cout << "Total Distance Covered = " << drone->totalDistance() << " km" << endl;
    cout

