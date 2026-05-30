#include<iostream>
using namespace std;

class hostel_mess{
	
		static int a,c,d,g,x;
		static float e,b,sum;
	public:
		void acc_create(int f)
		{
			b=f*4;
			e[b]={};
			return;
		};
	    int bill(int n){
	    	for(c=0;c<b;c++){
	    		if(c%4==0){
	    			cout<<"Enter the details of student"<<g+1<<':\n';
	    			g=g+1;
				}
				if(c%4==0){
					cout<<"enter the breakfast price:\n";
					cin>>e[c];
					
				}
				ifelse(c%4==1){
					cout<<"enter the lunch price:\n";
					cin>>e[c];
					
				}
				ifelse(c%4==2){
					cout<<"enter the dinner price:\n";
					cin>>e[c];
					
				}
				else(c%4==3){
					cout<<"enter the special item price:\n";
					cin>>e[c];
				};
			}
	}
		int Hostel_earnings(){
			for(x=0;x<b;x=x+1){
				sum=sum+e[x];
				};
			return sum;
		};
			
	
};

int hostel_mess::a=0;
int hostel_mess::b=0;
int hostel_mess::c=0;
int hostel_mess::d=0;
int hostel_mess::g=0;
int hostel_mess::x=0;
float hostel_mess::e=0;
float hostel_mess::sum=0;

int main(){
	cout<<"welcome to hostel mess management\n";
	int i=0,j=0;
	cout<<"enter the total number of students:\n";
	cin>>i;
	hostel_mess::acc_create(i);
	hostel_mess::billO(i);
	j=hostel_mess::hostel_earning();
	
	cout<<"the total earning of hotel is "<<j<<".\n";
	cout<<"Sairam \n";
};
