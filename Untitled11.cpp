#include <iostream>
using namespace std;

class ShoppingCart
{
private:
    int n;              // number of products
    float *prices;      // dynamic array for product prices

public:
    // Constructor
    ShoppingCart()
    {
        n = 0;
        prices = nullptr;
    }

    // Function to take input
    void input()
    {
        cout << "Enter number of products: ";
        cin >> n;

        prices = new float[n];   // dynamic allocation

        cout << "Enter price of each product:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> prices[i];
        }
    }

    // Function to calculate total bill
    float totalBill()
    {
        float total = 0;
        for (int i = 0; i < n; i++)
        {
            total += prices[i];
        }
        return total;
    }

    // Function to calculate average price
    float averagePrice()
    {
        return totalBill() / n;
    }

    // Destructor
    ~ShoppingCart()
    {
        delete[] prices;
    }
};

int main()
{
    // Dynamically allocate object
    ShoppingCart *cart = new ShoppingCart();

    cart->input();

    cout << "Total Bill = " << cart->totalBill() << endl;
    cout << "Average Product Price = " << cart->averagePrice() << endl;

    // Free memory
    delete cart;

    return 0;
}

