#include <iostream>
using namespace std;

class health
{ 
private:
    float weight;
    float height;
   
public:
    void input()
    {
        cout << "Enter weight (in kgs):\n";
        cin >> weight;

        cout << "Enter height (in meters):\n";
        cin >> height;
    }

    float bmi()
    {
        return weight / (height * height);
    }
};

int main()
{ 
    // Dynamically allocate object
    health *h = new health();

    h->input();

    cout << "Your BMI is: " << h->bmi() << "\n";

    // Free allocated memory
    delete h;

    return 0;
}

