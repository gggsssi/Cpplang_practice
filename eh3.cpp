//Implicit type conversion does not happen for primitive types.
#include <iostream> 
using namespace std; 
  
int main() 
{ 
char a;
    try  { 
       throw a; 
    } 
    catch (int x)  { 
        cout << "Caught "; // terminates code before catching it
    } 
    return 0; 
}

