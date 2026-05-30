#include <iostream>

#include "P.cpp"

using namespace std;

 

class B: public A{

public:

                B(){

                                cout<< "I am in class B";

                }

};

int main(){

                B b1;

                return 0;

}


