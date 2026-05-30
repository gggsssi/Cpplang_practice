#include<iostream>
using namespace std;
class acadscr;
class srdscr;
class acadscr{//this takes in the academic cgpa
	private:
		int student_no, cgpa;
	public:
		void setdata(){
			student_no=16;
			cout<<"enter cgpa:\n";
			cin >> cgpa;
		}
		
		friend int selection(acadscr a,srdscr b);
		
};
class srdscr{//this intakes the srd dept marks
	private :
		int student_no, marks;
	public:
		void setdata(){
			student_no=16;
			cout<<"enter srd marks(out of 10):\n";
			cin >> marks;
		}
	    friend int selection(acadscr a ,srdscr b);
};

int selection(acadscr a , srdscr b){ //this checks if the student is eligible for gold medal
	if(a.cgpa>=7.5 && b.marks>=9){
		return 1;
	}
	else
	    return 0;
	    
}

int main()
{
	int h;
	acadscr a;
	srdscr b;
	a.setdata();
	b.setdata();
	cout<<"if candidate is selected (1) and (0) if not selected\n";
	h=selection( a ,b);
	cout<<h;
}

