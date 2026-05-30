#include <iostream>
using namespace std;
int main()
{
  string str; //NULL character included automatically, Size enabled dynamically at runtime, istraem class
  cout<<"Enter the string:"; //reading user input without delimeter
  cin>>str;
  cout<<"You entered: "<<str;
  return 0;
}
