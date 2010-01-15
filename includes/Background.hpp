#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"
#include "System/Timer.hpp"

#include "WorldListener.hpp"
#include "Shakeable.hpp"

class Background : public WorldListener, virtual public Shakeable {
public:
	virtual ~Background() { }
	
	virtual void Update( float ) { }
	virtual void Render() = 0;
};

struct Cloud {
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	float x, y;
	float min_x, max_x;
};

class ABackground : virtual public Background, virtual public Shakeable {
public:
	ABackground();
	
	void SetDudePos( Vec2D pos );
	void SetRageLevel( float rage_perc );
	void ReportEnemyKilled();
	
	void Update( float dt );
	void Render();
private:
	boost::shared_ptr<hgeSprite> sky_spr;
	
	Cloud time_cloud;
	Cloud kill_cloud;
	Cloud rage_cloud;
	
	TexObj sign_tex;
	boost::shared_ptr<hgeSprite> sign_spr;
	
	boost::shared_ptr<hgeFont> asia30;
	boost::shared_ptr<hgeFont> asia23;
	boost::shared_ptr<hgeFont> arial10;
	
	Timer timer;
	
	float rage;
	int enemies_killed;
	Vec2D dude_pos;
	
	HgeObj hge;
};

#endif
