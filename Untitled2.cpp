#include <iostream>

 int main()

{

    int *ptr = new int{}; // dynamically allocate an integer

    *ptr=7;

    std::cout<<"The pointer is :"<<*ptr;

    int *otherPtr{ ptr }; // otherPtr is now pointed at that same memory location

    std::cout<<"The other pointer is :"<<*otherPtr;

    delete ptr; // return the memory to the operating system.  ptr and otherPtr are now dangling pointers.

    std::cout<<"The other pointer is :"<<*otherPtr;

    ptr = NULL; // ptr is now a nullptr

     // however, otherPtr is still a dangling pointer!

    std::cout<<*otherPtr;

    return 0;

}
