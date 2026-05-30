#include<iostream>
using namespace std;

class Clinic{
	private:
		static int p;
		static int q,c;
	public:
		static patient_bill(int n)
		{
			int i=0;
			for(i=0;i<n;i=i+1)
			{
			   cout<<"Enter the price of the item no"<<i+1;
			   cin>>q;
			   p=p+q;
			}
		    c=c+p;
			return p;
		    
		}
		static clinic_earning()
		{
			return c;
		}
};

int Clinic::p=0;
int Clinic::q=0;
int Clinic::c=0;

int main()
{
  int a;
  int b;
  int e;
  string d;
  cout<<"Welcome to the hospital";
  cout<<"Enter 1 if you want patient bill OR 2 if you want CLinic earning";
  cin>>a;
    if(a==1)
    {
  	    cout<<"Enter the patient name and total no of items:";
  		cin>>d and b;
  		e=Clinic::patient_bill(b);
  		cout<<d<<" "<<"has a total payable bill of"<<e;
  	
     }
    else
    {
  	  e=Clinic::clinic_earning();
  	  cout<<e;
      };
}
