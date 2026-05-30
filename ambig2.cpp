//What if only one copy of base is actually required? Is there some way to prevent
     // two copies from being included in derived3?
 // This solution is achieved using virtual base classes.
 // This program uses virtual base classes.
 //Differnce between normal and virtual base class
 //The only difference between a normal base class and a virtual one is what occurs when
   // an object inherits the base more than once.
 // If virtual base classes are used, then only one base class is present in the object.
   //  Otherwise, multiple copies will be found.
#include <iostream>
using namespace std;
class base {
public:
int i;
};
class derived1 : virtual public base {
// derived1 inherits base as virtual.
public:
int j;
};
// derived2 inherits base as virtual.
class derived2 : virtual public base {
public:
int k;
};
/* derived3 inherits both derived1 and derived2.
This time, there is only one copy of base class. */
class derived3 : public derived1, public derived2 {
public:
int sum;
};
int main()
{
derived3 ob;
ob.i = 10; // now unambiguous
ob.j = 20;
ob.k = 30;
// unambiguous
ob.sum = ob.i + ob.j + ob.k;
// unambiguous
cout << ob.i << " ";
cout << ob.j << " " << ob.k << " ";
cout << ob.sum;
return 0;
}
