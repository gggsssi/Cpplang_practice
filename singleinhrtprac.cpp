#include<iostream>
using namespace std;

class Continent{
	public :
		Continent(){
			cout<<" i am in continent  rn\n"<< endl;
		}
};
class country : public Continent{
	public:
		country(){
		 cout<<"i am in country rn\n"<<endl;}
};

int main(){
	country obj;
	return 0;
}
