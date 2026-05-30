#include<iostream>

    using namespace std;

    class Complex{

    private:

        int real;

        int imag;

         /* Function to set the values of

          * real and imaginary part of each complex number

          */

    public:

         
		 void setvalue()

        {

            cin>>real;

            cin>>imag;

        }

                /* Function to display the sum of two complex numbers */

       
		  Complex() { 
    	  cout << "Constructor" << endl; 
      	}
       	~Complex() { 
    	   cout << "Destructor" << endl; 
        }
		void display()

        {

            cout<<real<<"+"<<imag<<"i"<<endl;

        }

                /* Function to add two complex numbers */

 

        Complex Complex_sum(Complex c1,Complex c2) //.return type is object ,1. objects as parameters

        {

            Complex c3;

            c3.real=c2.real+c1.real; // Reference variable usage

            c3.imag=c2.imag+c1.imag;// by default this pointer points to the current object

                return c3;

        }

        };
        
        int main()
         
 

        {

            
			int b;
			Complex c1,c2,a;

            cout<<"Enter real and imaginary part of first complex number"<<endl;

            c1.setvalue();

 

            cout<<"Enter real and imaginary part of second complex number"<<endl;

 

            c2.setvalue();

 

            cout<<"Sum of two complex numbers is"<<endl;

 

            a=c1.Complex_sum(c1,c2);
            a.display();
            b=sizeof(a);

 

        return 0;

 

        }
