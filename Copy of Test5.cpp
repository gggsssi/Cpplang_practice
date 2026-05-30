//Question 5
#include <iostream>
using namespace std;
int funcp() {
    static int x = 1;
    x++;
    return x;
}
int main() {
    int x, y;
    x = funcp();
    y = funcp()+x;
    cout << (x+y)<<endl;
    return 0;
}