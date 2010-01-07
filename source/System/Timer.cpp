#include "includes/System/Timer.hpp"

Timer::Timer() : start_tick(0), pause_tick(0), time(0), is_started(false), is_paused(false) 
{
	
}
Timer::~Timer()
{
	
}

void Timer::Start() 
{
	if( !is_started || is_paused ) {
		start_tick = hge->Timer_GetTime();
		is_started = true;
		is_paused = false;
	}
}
void Timer::Pause() 
{
	if( is_started && !is_paused ) {
		is_paused = true;
		time += GetTimeStep();
	}
}
void Timer::Stop() 
{
	time = 0;
	is_started = is_paused = false;
}

void Timer::Restart() 
{
	Stop();
	Start();
}
void Timer::Reset()
{
	time = 0;
	is_started = false;
}

float Timer::GetTime() const
{
	if( is_started && !is_paused ) {
		return time + GetTimeStep();
	}
	else {
		return time;
	}
}
void Timer::SetTime( float new_time )
{
	time = new_time;
	start_tick = hge->Timer_GetTime();
}

bool Timer::IsStarted() const
{
	return is_started;
}
bool Timer::IsPaused() const
{
	return is_started && is_paused;
}

float Timer::GetTimeStep() const
{
	return hge->Timer_GetTime() - start_tick;
}
void Timer::UpdateTimeAcc()
{
	time = GetTime();
	start_tick = hge->Timer_GetTime();
}
