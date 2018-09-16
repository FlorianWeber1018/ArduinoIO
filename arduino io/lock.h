/*
 * lock.h
 *
 * Created: 13.09.2018 10:48:21
 *  Author: Florian Weber
 */ 

#include <stdbool.h>
#ifndef LOCK_H_
#define LOCK_H_
class lock{
	public:
		lock();
		void tryLock() volatile;
		void unlock() volatile;
		bool getLock() volatile;
	private:
		volatile bool locked;
};




#endif /* LOCK_H_ */