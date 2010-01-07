#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

#include "Hge.hpp"

class Timer {
public:
	Timer();
	virtual ~Timer();

	void Start();
	void Pause();
	void Stop();
	void Restart();
	void Reset();

	float GetTime() const;
	void SetTime( float time );
	
	bool IsStarted() const;
	bool IsPaused() const;
protected:
	virtual float GetTimeStep() const;
	virtual void UpdateTimeAcc();
	
	float start_tick;
	float pause_tick;
	float time;
	bool is_started;
	bool is_paused;
	
	HgeObj hge;
};

#endif
