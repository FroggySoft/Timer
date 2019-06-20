/*
 * Timer.cpp
 *
 *  Created on: 20 Jun 2019
 *      Author: rob
 */

#include "Timer.h"

Timer::Timer():
	mExpireTimeMs(0),
	mActive(false),
	mObservers()
{

}

Timer::~Timer()
{
}


void Timer::Run(int aTimeMs)
{
	if (IsActive() && (mExpireTimeMs>0))
	{
		mExpireTimeMs -= aTimeMs;
		if (mExpireTimeMs <= 0)
		{
			notifyObservers();
			mExpireTimeMs = 0;
		}
	}
}

void Timer::Reload(int aTimeMs)
{
	mExpireTimeMs = aTimeMs;
	if (mExpireTimeMs>0)
	{
		mActive = true;
	}
}

void Timer::Stop()
{
	mActive = false;
}

bool Timer::HasExpired() const
{
	return (IsActive() && (mExpireTimeMs==0));
}

bool Timer::IsActive() const
{
	return mActive;
}

void Timer::Register(ITimerObserver* aObserver)
{
	mObservers.push_back(aObserver);
}

void Timer::Unregister(ITimerObserver* aObserver)
{
	mObservers.remove(aObserver);
}

void Timer::notifyObservers()
{
    for(auto* observer : mObservers)
    {
    	observer->Update();
    }
}
