#include <iostream>
#include <memory>
#include "GTUSet.h"
#include "GTUSet.cpp"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;
using GTU::GTUSet;

int main(void) {
	GTUSet<int> a;
	cout<<"Firsly, Is Empty ? : " << a.empty() <<endl;
	cout<<"Size(before insertion) -> "<<a.size()<<endl;
	a.insert(5);
	a.insert(6);
	cout<<"Is Empty (after insertion) : "<<a.empty()<<endl;
	cout<<"Insertin element : " << *a.getPtr()<<endl;
	cout<<"New Size : "<< a.size()<<endl;
	cout<<"Clearing..."<<endl;
	a.clear();
	cout<<"After Clear. Is empty : "<<a.empty()<<endl;
	//cout<<*a.getPtr()<<endl;
	cout<<"New Size : "<< a.size()<<endl;
	
	return 0;
}
