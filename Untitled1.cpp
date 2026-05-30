#include<iostream>
using namespace std;
class Transportation{
	public:
		int seats;
		int fuelCapacity;
		int Airbags;
		int rpm;
		int tyresize;
		
	Transportation(int a ,int b,int c,int d,int e)
	{
		seats=a;
		fuelCapacity=b;
		Airbags=c;
		rpm=d;
		tyresize=e;
	}
	
	float Mileage(){ //Mileage proportional fuelCapacity
		return fuelCapacity * 100.0 / (rpm + seats + tyresize);
		}
	int Speed(){ //Higher rpm>>higher speed

	    return rpm * tyresize;
		}
	int Torque(){ //Torque relates to engine effort
	    return (rpm * tyresize) / seats;
		}
    int BrakingPower(){//Larger tyres>>more contact area>>better braking
        return (tyresize * Airbags) / rpm;
		}
};
int main()
{
	int a ,b,c,d,e;
	cout<<"Enter your car details in the following fashion:\n"
         "seats \n"
		 "fuelCapacity \n"
		 "Airbags \n"
	     "rpm \n"
		 "tyresize \n";
    cin>>a>>b>>c>>d>>e;
    Transportation obj1(a,b,c,d,e);
    cout << "Mileage: " << obj1.Mileage() << endl;
    cout << "Speed: " << obj1.Speed() << endl;
    cout << "Torque: " << obj1.Torque() << endl;
    cout << "Braking Power: " << obj1.BrakingPower() << endl;

	
}
