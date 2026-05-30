//When an exception is thrown, all objects created inside the enclosing try block are destructed before the control is 
//transferred to catch block.
#include <iostream> 
using namespace std; 
  
class Test { 
public: 
   int i;
   i=10;
   Test() { cout << "Constructor of Test " << endl; } 
   //~Test() { cout << "Destructor of Test "  << endl; } 
}; 
  
int main() { 
  int a;
  try { 
    Test t1; 
    a=t1.i
    throw 10; 
  } catch(int i) { 
    cout << "Caught " << i << endl; 
  } 
  cout<<'a';
} 

