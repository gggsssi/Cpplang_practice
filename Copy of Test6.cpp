//Question 6
#include <iostream>
using namespace std;
int foo(int x, int y, int q) {
    if ((x<=0) && (y<=0))
        return q;
    if (x<=0)
        return foo(x,y-q,q);
    if (y<=0)
        return foo(x-q,y,q);
    return foo(x, y-q,q)+foo(x-q,y,q);
}
int main() {
    int r=foo(15, 15, 10);
    cout<<r;
    return 0;
}
