#include<fstream>
#include<iostream>
//Constrcutors of the classes ifstream,ofstream amnd fstream are declared here.
//class-stream(const char *path,int mode=ios::in|ios::out,int prot=filebuff;openprot);
using  namespace std;
int main(){
char name[30];
int mark;
ofstream fout;
fout.open("stu.txt");//file name is passsed as the first parameter in the constructor i.e 
//binds/attaches the stream/object fout to the file stu.txt opened for writing 
//Binds/attches stu.txt to the disk for writing 
cout<<"Enter the name ";
cin>>name;
cout<<"enter the marks secured ";
cin>>mark;
fout<<name<<endl;//the name of the student is passed on to the file stu.txt pointed by the the file pointer fout
fout<<mark<<endl;//the mark of the student is passed on to the file stu.txt pointed by the the file pointer fout
fout.close();//disconnect the stream from the file
ifstream fin;
fin.open("stu.txt");
fin>>name;
fin>>mark;
cout<<name<<endl;
cout<< mark<< endl;
fin.close();
return 0;
}
