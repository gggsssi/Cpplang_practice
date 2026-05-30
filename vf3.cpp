#include <iostream>
using namespace std;
class number {
	protected:
int val;
public:
void setval(int i) { val = i; }
// show() is a pure virtual function
virtual void show() = 0;
};
class hextype : public number {
public:
void show() {
cout << hex << val << "\n";
}
};
class dectype : public number {
public:
void show() {
cout << val << "\n";
}
};
class octtype : public number {
public:
void show() {
cout << oct << val << "\n";
}
};
void f(number &n){
	n.show();
}
int main()
{
dectype d;
hextype h;
octtype o;
f(d);
f(h);
f(o);
return 0;
}
