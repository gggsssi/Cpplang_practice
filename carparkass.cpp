#include<iostream>
using namespace std;

class Car {
    string color;
    int slot;

public:
    static int carsParked;

    Car() {
        color = "White";
        slot = 0;
        carsParked++;
        cout << "Default car parked\n";
    }

    Car(string c, int s) {
        color = c;
        slot = s;
        carsParked++;
        cout << "Car " << color << " parked in slot " << slot << "\n";
    }

    ~Car() {
        carsParked--;
        cout << "Car left slot " << slot << "\n";
    }

    void info() {
        cout << "Color: " << color << " | Slot: " << slot << " | Total parked: " << carsParked << "\n";
    }
};

int Car::carsParked = 0;

void parkCar(Car &c) {
    cout << "Parking info -> ";
    c.info();
}

int main() {
    Car c1;
    Car c2("Red", 3);
    Car c3("Blue", 7);

    parkCar(c2);
    parkCar(c3);

    Car *c4 = new Car("Black", 10);
    parkCar(*c4);
    delete c4;

    cout << "\nCars still parked: " << Car::carsParked << "\n";

    return 0;
}
