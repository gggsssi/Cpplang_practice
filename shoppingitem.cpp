#include<iostream>
using namespace std;

class shopitem{
	private:
		string itemname;
		int itemprice;
		
	public:
		static int a,b;
		static string *h[b]={/*.......*/};
		shopitem(){
			a=a+1;
			cout<<"obj no "<<a<<"created\n";
			cout << "Constructor\n" << endl;
		};
		
		~shopitem(){
			a=a-1;
			cout<<"obj no "<<a<<"destructed\n";
			cout << "destructor\n" << endl;
		};
		
		
		void createitem(){
			cin>>itemname;
			cin>>itemprice;
		};
		
		shopitem bill(shopitem g,int i){
			h[i]={g.itemname:'g.itemprice'};
			
		};
		
		void show(){
			for (i=0;i<b;i=i+1){
				cout<<h[i];
			};
		   return;
		};
		
		}
		
shopitem::a=0;
shopitem::b=0;
int main(){
	int f=0;
	cout<<"ENTER the total no of items:\n";
	cin>>f;
	b=f;
	h[f]={};
	for (i=0;i<f;i=i+1){
		shopitem g(i+1);
		g(i+1).createitem();
		g.bill(g,i);
	}
	shopitem a;
	show();
		
		
	}
}


