#include<iostream>
using namespace std;
class Percentage
{
 private:
   int n;
   float sub1,sub2,sub3,sub4,sub5;
 
 
 public:
 
   void input()
   {
    cout<<"enter the number of subject"<<"\n";
    cin>>n;
    cout<<"enter the marks of the five subject:"<<"\n";
    cin>>sub1;
    cin>>sub2;
    cin>>sub3;
	cin>>sub4;
    cin>>sub5;
   }
   float percentage()
   { 
    int sum=sub1+sub2+sub3+sub4+sub5;
 
    int percent=(sum/500)*100;
    return percent;
   }
 
};
int main()
{
 Percentage p;
 p.input();
 cout<<"the percentage is "<< p.percentage() <<"\n";
}

