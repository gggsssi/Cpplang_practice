// bad_alloc standard exception
#include <iostream>
#include <exception>
using namespace std;

int main () {
  try
  {
    int* myarray= new int[109869879898];
    delete myarray;
    myarray=NULL  ;
  }
  catch (exception& e)
  {
    cout << "Standard exception: " << e.what() << endl;

  }
  return 0;
}
