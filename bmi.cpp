#include<iostream>
using namespace std;
class health
{ 
  private:
   float weight;
   float height;
   
  public:
   void input()
   {
    cout<<"enter weight(in kgs):"<<"\n";
    cin>>weight;
    cout<<"enter height(in mts):"<<"\n";
    cin>>height;
    
    
   }
   float bmi()
   {
    float bmi=weight/(height*height);
    return bmi;
   }
   
   
};
int main()
{ 
 health h;
 h.input();
 cout<<"Your Bmi is:"<< h.bmi()<<"\n";
 
}
