#include<iostream>

using namespace std;

int t=10;// GLOBAL VARIABLE testing

class teststa{

                public:

                static int a;//STATIC VARIABLE even it does not occupy memory:class variables

                                                static void set(){ //static member function

                                a=5; //static member funct0ion can access only static member variables.

                cout<<"The static varaiable intialized inside the functin is "<<a<<endl;

                cout<<"The global varaiable is"<<t<<endl;// it can access the global variable also       

                                }

                };

int teststa::a; // here a's values is 0 DEFINING

int main(){

                cout<<"The intial value is"<<teststa::a<<endl;

                teststa::set();     // class member variables and class member functions

                cout<<teststa::a;            

}
