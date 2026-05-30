#include<iostream>
using namespace std;  // wrapping all the standard libraries

class Interest
{ 
 private:  
   int p;      //initialising the variable p
   int r;       //initialising the variable r
   int t;       //initialising the variable t
   
 public:
   void input()
   {
    cout<<"enter principle:";  // taking input from users and storing in  variable p
    cin>>p;
    cout<<"enter rate:";       // taking input from users and storing in  variable r
    cin>>r;
    cout<<"enter time:";       // taking input from users and storing in  variable t
    cin>>t;
    
   }
   float simple_interest()
   {
    int si=(p*r*t)/100; // computing the interest
    return si;    //returning the answer
    
   }
   float annual()   //func of compound interest
   {
   int annual=(p*r)/100;     //computing compound interest
   return annual;       // returning the computed value.
   }
};
int main()
{
  Interest i;   // interest in terms of i.
  i.input();           // taking input from user
  cout<< "simple interest is"<< i.simple_interest()<<"\n";    // printing simple interest. 
  cout<< "compound interest is" << i.annual()<<"\n";   // print annual interest.
}
