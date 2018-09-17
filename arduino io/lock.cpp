/*
 * lock.cpp
 *
 * Created: 13.09.2018 10:47:57
 *  Author: Florian Weber
 */
#include "lock.h"
lock::lock()
{
	locked = false;
}
void lock::tryLock() volatile
{
	
	while(locked){
		asm volatile("nop");
	}
	
	locked = true;
}
void lock::unlock() volatile
{
	this->locked = 0;
}
bool lock::getLock() volatile
{
	return locked;
}