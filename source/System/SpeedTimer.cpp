#include "includes/System/SpeedTimer.hpp"

SpeedTimer::SpeedTimer() : speed(1.0)
{
	
}
SpeedTimer::~SpeedTimer()
{
	
}

void SpeedTimer::SetSpeed( float multiplier )
{
	UpdateTimeAcc();
	speed = multiplier;
}
float SpeedTimer::GetSpeed() const
{
	return speed;
}

float SpeedTimer::GetTimeStep() const
{
	return ( hge->Timer_GetTime() - start_tick ) * speed;
}
void SpeedTimer::UpdateTimeAcc()
{
	time = GetTime();
	start_tick = hge->Timer_GetTime();
}
