#include<iostream>
using namespace std;
class Input    //Creating a class
{
	public:
	
      //member variable
      int a; //By default 'a' is private to input class
      
      //member function
      void input(){
           cin>>a; //taking input in a
           }
      void display(){
           cout<<"the number is \endl"<<a; //giving output of a
           }        
}; 

int main() //main function
{
    Input i1; //It is an object in class Input
    
    i1.input();
    i1.display();
}
