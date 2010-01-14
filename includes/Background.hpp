#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"
#include "System/Timer.hpp"

#include "WorldListener.hpp"

class Background : public WorldListener {
public:
	virtual ~Background() { }
	
	virtual void Update( float ) { }
	virtual void Render() = 0;
};

struct Cloud {
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	float x, y;
};

class ABackground : public Background {
public:
	ABackground();
	
	void SetRageLevel( float rage_perc );
	void ReportEnemyKilled();
	
	void Update( float dt );
	void Render();
private:
	boost::shared_ptr<hgeSprite> sky_spr;
	
	typedef std::vector<Cloud> Clouds;
	Clouds clouds;
	
	TexObj sign_tex;
	boost::shared_ptr<hgeSprite> sign_spr;
	
	boost::shared_ptr<hgeFont> asia30;
	boost::shared_ptr<hgeFont> asia23;
	
	Timer timer;
	
	float rage;
	int enemies_killed;
	
	HgeObj hge;
};

#endif
