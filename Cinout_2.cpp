#include <iostream>
using namespace std;
int main()
{
  char str[50];// the NULL character included as the 50th element, Size enabled at compile time '/0'
  cout<<"Enter the string:"; //reading user input without delimeter nothing but spaces
  cin>>str;
  cout<<"You entered: "<<str[50];
  return 0;
}
