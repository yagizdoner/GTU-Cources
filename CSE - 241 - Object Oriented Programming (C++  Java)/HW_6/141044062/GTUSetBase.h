/*
	Yagiz Doner - 141044062 
		CSE 241 - HW_6
		 GTUSetBase.h
*/

#ifndef GTUSETBASE_H
#define GTUSETBASE_H

namespace GTU{
	class GTUSetBase {
		public:				
			// all of the "=0" are for pure virtual fuction.
			virtual bool empty() = 0;
			virtual int size() = 0; 
			virtual int max_size() = 0; 
			virtual void insert() = 0;
			virtual void erase() = 0;
			virtual void clear() = 0;
			virtual void find() = 0;
			virtual void count() = 0;
			virtual void begin() = 0;
			virtual void end() = 0;
		private:
			
	}; // GTUSetBase
} // GTU
#endif //GTUSETBASE_H
