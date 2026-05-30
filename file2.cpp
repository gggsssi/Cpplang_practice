//Basics of File IO:RAM or Permanent storage/Secondary storage
//Library <fstream> because of namespace.
//it has (ofstream(writing),ifstream(Reading)  and fstream(raed and Write)
//Opening a file using method and constrcutor
//Method1:ofstream fout("one.txt"); 
//Method2:ofstream fout
//       fout.open("one.txt");
//End of file
//Method 1: ifstream fin("one.txt");
//          while(fin){ }
//Method 2:
//          fin.eof()!=0 (function returns 0 if eof not reached else it returns non-zero value)  
//fstream class and different modes
//ios::in (READING) uesd FOR ifstream fin("one.txt") by default
//ios::out (WRITING) used FOR ofstream fout("one.txt") by default.
//ios::app APPEND
//ios::ate Write in between/overwrite data
//trunc binary also there
//fstream fout("one.txt",ios::in|ios::out);

#include<iostream>
#include<fstream>

using namespace std;
int main()
{
char rel[20];
ofstream fout;
fout.open("one.txt");//open using open method default ios::out mode
fout<<" sairam"<<endl;
fout<<" saigovinda"<<endl;
fout<<" saikrishna"<<endl;
fout<<" saihari"<<endl;
fout.close();//object and the file linked to each other shoud be relaesed before reading.

ifstream fin("one.txt");
while(fin)
{
fin.getline(rel,20);
cout<<rel<<endl;
}
fin.close();
fin.open("one.txt"); 
while(1)
{
if(fin.eof()!=0)
{break;}
fin.getline(rel,20);
cout<<rel<<endl;
}
fstream file("one.txt",ios::in);
while(1)
{
if(fin.eof()!=0)
{break;}
file.getline(rel,20);
cout<<rel<<endl;
}

return 0;
}
