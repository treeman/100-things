#ifndef SPEEDTIMER_HPP_INCLUDED
#define SPEEDTIMER_HPP_INCLUDED

#include "Timer.hpp"

class SpeedTimer : public Timer {
public:
	SpeedTimer();
	virtual ~SpeedTimer();
	
	void SetSpeed( float multiplier );
	float GetSpeed() const;
private:
	float GetTimeStep() const;
	void UpdateTimeAcc();
	
	float speed;
};

#endif
