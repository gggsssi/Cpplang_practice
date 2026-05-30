#include <iostream>
using namespace std; //ALL the standard C++ libraries are wrapped in a single namespace, which is std(for "Standard").
int main()
{                            //IN C++ main() always has return type of int.
  int i;
  cout<< "This is output.\n";//To be read as "Send the string "This is output" to the object called cout".
                             //this is a single line commengt /* you can still use C style comments */
                             //Input a number using>>
  cout<< "Enter a nummber: ";
  cin>>i;
                            //now,output a number using<<
  cout<< "The number Givern is: " << i << "\n";
  return 0;                 //int return from main().
}
