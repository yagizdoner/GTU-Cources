/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_6
			GTUSet.h
*/

#ifndef GTUSET_H
#define GTUSET_H

#include <iostream>
#include <memory>
#include "GTUSetBase.h"

using namespace std;

namespace GTU{
	template<class T>
	class GTUSet : public GTUSetBase{
		public:
			shared_ptr<T> getPtr();
			class GTUIterator{
				bool operator ==(const shared_ptr<T> & other);
				shared_ptr<T> & operator = (const shared_ptr<T> & other);
				T& operator*() const;
				T* operator->() const;
			};
			bool empty();
			int size(); 
			int max_size(); 
			void insert(T element);
			void erase();
			void clear();
			void find();
			void count();
			void begin();
			void end();
		private:
			shared_ptr<T> s;
	}; // GTUSet
} // GTU
#endif //GTUSET_H
