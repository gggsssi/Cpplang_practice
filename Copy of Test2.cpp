//Question 2
#include <iostream>
using namespace std;
int main(){
	float sum=0.0,j=1.0,i=2.0;
	while(i/j>0.0625){
		j=j+j;
		sum=sum+i/j;
		cout<<sum<<endl;
	}
	return 0;
}