//Basics of File IO:RAM or Permanent storage/Secondary storage
//Library <fstream> because of namespace.
//it has (ofstream(writing),ifstream(Reading)  and fstream(read and Write)

#include<iostream>
#include<fstream>

using namespace std;
int main()
{
ofstream fout("one.txt");//constrcutor of ofstream class which takes text file(existing/new) as a parameter.
int val1,rel1;
char val2[20],rel2[20];

cout<<"enter the integer"<<endl;
cin>>val1;
cout<<"enter the String"<<endl;
cin>>val2;
fout<<val1<<endl;//Transfer the values to file
fout<<val2;
fout.close();//object and the file linked to each other shoud be relaesed before reading.
ifstream fin("one.txt");
fin>>rel1;//storing the values in rel1 for reading purpose
fin>>rel2;
cout<<"enter the integer value1 is"<< rel1;//checking
cout<<"\nenter the string value2 is"<<rel2;

return 0;
}
