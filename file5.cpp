#include <iostream>
#include <fstream>

using namespace std;

int main()
{
char rel[60];
    fstream st; // Step 1: Creating object of fstream class
    st.open("test1.txt",ios::out);  // Step 2: Creating new file
    if(!st) // Step 3: Checking whether file exist
    {
        cout<<"File creation failed";
    }
    else
    {
        cout<<"New file created";
        st<<"Sairam";
		st<<"Saikrishna";		    // Step 4: Writing to file
	st.close(); // Step 5: Closing file
    }
    //fstream st;
    st.open("test1.txt",ios::in);
while(1)
{
if(st.eof()!=0)
{break;}
st.getline(rel,20);
cout<<rel<<endl;
}
    return 0;
}
