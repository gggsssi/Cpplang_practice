//simple example to show exception handling in C++

#include <iostream>
#include<typeinfo>
using namespace std;

 int main()

{   int x = -1; 

     int y;

    // Some code

   cout << "Before try \n";

   cin>>y;

   try {

      cout << "Inside try \n";

      if (typeid(y).name() != int){
      	throw y;
      	cout<<" After throw (Never executed) \n";
	  }
	  
	catch (){
	  
	  if (y> x) // trying / exceptional condition

      {

         throw y;

         cout << "After throw (Never executed) \n";

      }

   catch (int y ) {

      cout << "Exception Caught \n";

   }

    cout << "After catch (Will be executed) \n";

   return 0;

}
