/*
 * Timer.h
 *
 *  Created on: 20 Jun 2019
 *      Author: rob
 */

#pragma once

#include <list>

class ITimerObserver
{
public:
	virtual void Update() = 0;
};

class Timer
{
public:
	Timer();
	virtual ~Timer();

	void Run(int aTimeMs);
	void Reload(int aTimeMs);
	void Stop();
	bool HasExpired() const;
	bool IsActive() const;

	void Register(ITimerObserver* aObserver);
	void Unregister(ITimerObserver* aObserver);

private:
	void notifyObservers();

	int  mExpireTimeMs;
	bool mActive;
	std::list<ITimerObserver*> mObservers;
};
