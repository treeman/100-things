#ifndef WORLD_HPP_ICNLUDED
#define WORLD_HPP_ICNLUDED

#include <boost/shared_ptr.hpp>
#include <vector>

#include "System/Hge.hpp"
#include "System/Settings.hpp"
#include "System/Timer.hpp"

#include "Dude.hpp"
#include "Bullet.hpp"
#include "Alien.hpp"
#include "Ground.hpp"
#include "Notifier.hpp"

class World {
public:
	World();
	
	void Update( float dt );
	void Render();
	
	boost::shared_ptr<Dude> GetDude() {
		return dude;
	}
	
	void PushBullet( boost::shared_ptr<Bullet> bullet ) {
		bullets.push_back( bullet );
	}
private:
	boost::shared_ptr<hgeSprite> sky_spr;
	boost::shared_ptr<Ground> ground;
	
	boost::shared_ptr<Dude> dude;
	
	typedef std::vector<boost::shared_ptr<Bullet> > Bullets;
	Bullets bullets;
	
	typedef std::vector<boost::shared_ptr<Alien> > Aliens;
	Aliens aliens;
	
	boost::shared_ptr<hgeFont> arial10;
	
	boost::shared_ptr<Notifier> notifier;
	
	void RenderDebug();
	
	void InitDators();
	
	bool show_bullets;
	boost::shared_ptr<Dator<bool> > showBullets;
	bool show_bounds;
	boost::shared_ptr<Dator<bool> > showBounds;
	
	HgeObj hge;
};

#endif
