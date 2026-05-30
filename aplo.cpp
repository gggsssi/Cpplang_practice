#include <fstream>
#include <string>
using namespace std;

int main() {
    ofstream f("crew.txt");
    if (!f.is_open()) return 1;

    // Writing a string
    string name = "Neil Armstrong";
    f << name << "\n";

    // Writing an integer
    int mission = 11;
    f << "Apollo " << mission << "\n";

    // Mixed in one line
    int alt = 384400;
    f << "Dist: " << alt << " km\n";

    f.close();
    return 0;}
