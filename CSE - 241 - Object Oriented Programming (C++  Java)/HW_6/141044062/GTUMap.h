/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_6
			GTUSet.h
*/

#ifndef GTUMAP_H
#define GTUMAP_H

#include <iostream>
#include <memory>
#include "GTUSet.h"

using namespace std;

namespace GTU{
	template<class K,class V>
	class GTUMap : public GTUSet< pair<K,V> > {
		public:
			V& operator[] (const K& k);
		private:
			
	}; // GTUMap
} // GTU
#endif //GTUMAP_H
