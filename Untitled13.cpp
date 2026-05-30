#include <iostream>
using namespace std;

class Election
{
private:
    int booths;        // number of polling booths
    int *votes;        // dynamic array for votes per booth

public:
    // Constructor
    Election()
    {
        booths = 0;
        votes = nullptr;
    }

    // Function to take input
    void input()
    {
        cout << "Enter number of polling booths: ";
        cin >> booths;

        votes = new int[booths];   // dynamic allocation

        cout << "Enter votes received from each booth:\n";
        for (int i = 0; i < booths; i++)
        {
            cin >> votes[i];
        }
    }

    // Function to calculate total votes
    int totalVotes()
    {
        int total = 0;
        for (int i = 0; i < booths; i++)
        {
            total += votes[i];
        }
        return total;
    }

    // Function to find highest votes from a booth
    int highestVotes()
    {
        int max = votes[0];
        for (int i = 1; i < booths; i++)
        {
            if (votes[i] > max)
                max = votes[i];
        }
        return max;
    }

    // Destructor
    ~Election()
    {
        delete[] votes;
    }
};

int main()
{
    // Dynamically allocate object
    Election *e = new Election();

    e->input();

    cout << "Total Votes Received = " << e->totalVotes() << endl;
    cout << "Highest Votes from a Booth = " << e->highestVotes() << endl;

    // Free memory
    delete e;

    return 0;
}

