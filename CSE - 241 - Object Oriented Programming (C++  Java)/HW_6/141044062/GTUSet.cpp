/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_6
		  GTUSet.cpp
*/

#include <iostream>
#include <memory>
#include "GTUSet.h"
#include "GtuSetBase.h"


using namespace std;
using GTU::GTUSet;

namespace GTU{
	template<class T>
	shared_ptr<T> GTUSet<T>::getPtr(){
		return s;
	}
	
	template<class T>
	bool GTUSet<T>::GTUIterator::operator ==(const shared_ptr<T> & other){
		return( this.get() == other.get());
	}
	
	template<class T>
	shared_ptr<T> & GTUSet<T>::GTUIterator::operator = (const shared_ptr<T> & other){
		return shared_ptr<T>(other).swap(*this);
	}

	template<class T>
	T& GTUSet<T>::GTUIterator::operator*() const{
		return *this.get();
	}
	
	template<class T>
	T* GTUSet<T>::GTUIterator::operator->() const{
		return this.get();
	}
		
	template<class T>	
	bool GTUSet<T>::empty(){			
		if( s == nullptr )	
			return 1;				
		else
			return 0;
	}
	
	template<class T>	
	void GTUSet<T>::clear(){
		s = nullptr;
	}
	
	template<class T>
	int GTUSet<T>::size(){
		s.use_count();
	}
	
	template<class T>
	int GTUSet<T>::max_size(){
		return 10000;
	}
		
	template<class T>
	void GTUSet<T>::insert(T element){
		shared_ptr<T> a = make_shared<T>(element);
		s = a;
	}
} // GTU
