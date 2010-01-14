#ifndef WORLDLISTENER_HPP_INCLUDED
#define WORLDLISTENER_HPP_INCLUDED

class WorldListener {
public:
	virtual ~WorldListener() { }
	
	virtual void SetDudePos( Vec2D pos ) { };
	virtual void SetRageLevel( float ) { };
	virtual void ReportEnemyKilled() { };
};

#endif
