#ifndef INFOBAR_HPP_INCLUDED
#define INFOBAR_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"
#include "System/Timer.hpp"

#include "WorldListener.hpp"

class Infobar : public WorldListener {
public:
	Infobar();
	
	void SetRageLevel( float rage_perc );
	void ReportEnemyKilled();
	
	void Update( float dt );
	void Render();
private:
	boost::shared_ptr<hgeFont> fnt;
	
	Timer timer;
	
	float rage;
	int enemies_killed;
	
	float render_y;
};

#endif
