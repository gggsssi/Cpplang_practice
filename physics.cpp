#include <iostream>
using namespace std;
class Physics
{ 
  private:
   float v,u;
   float t; // in hour 
  public:
   void input()
   {
    cout<<"enter initial velocity u\n";
    cout<<"enter final velocity v \n";
    cout<<"enter time t \n";
    cin>>u>>v>>t;zaq
   }
   int accelaration()
   {
    int c=v-u;
     {
      int accln= c/t;
      return accln;
     }
     
    
	
   }
};
int main()
{
    Physics p;
    p.input();
    cout << "The acceleration = " << p.accelaration() << endl;
}

