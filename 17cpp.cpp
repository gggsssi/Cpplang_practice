    /* C++ Program to add two Complex Numbers */
    #include<iostream>
    using namespace std;
    class Complex{
    private:
        int real; // real part
        int imag;// imaginary part         
	public:
         void setvalue(int i,int j)
        {
            real=i;
			imag=j;
        }
    	
        void display() //Display the complex number
        {
            cout<<real<<"+"<<imag<<"i"<<endl;
        } 
        Complex sum(Complex c1,Complex c2) //Return type is an object
        {
	Complex c3;// Declared to return the object from the function sum
            c3.real=c1.real+c2.real;
            c3.imag=c1.imag+c2.imag;	
	return c3;
        }
        };
    int main()
        {

            Complex c1,c2,c3,c4; //C4 is declared to store the result returned as object from the function sum 
            c1.setvalue(4,5);
	    	cout<<"The first complex number"<<endl;
            c1.display();
            c2.setvalue(6,7);
	    	cout<<"The second complex number"<<endl;
		    c2.display();
            cout<<"Sum of two complex numbers is"<<endl;
            c4=c3.sum(c1,c2); // To store the result
            c4.display();
        return 0;
        }
