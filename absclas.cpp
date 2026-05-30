#include<iostream>

using namespace std;

class A{

	public:

	 virtual void display()=0;

			};

class B:public A{

	public:

	void display(){

		cout<<"I am in Derived Class B";

	}

};

int main(){

	A a1;//class A

	B b1;//class B

	                //a1.display();
	b1.display();

	return 0;

}
