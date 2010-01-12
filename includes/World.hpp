#ifndef WORLD_HPP_ICNLUDED
#define WORLD_HPP_ICNLUDED

#include <boost/shared_ptr.hpp>
#include <vector>

#include "System/Hge.hpp"
#include "System/Settings.hpp"
#include "System/Timer.hpp"

#include "Dude.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Ground.hpp"
#include "Notifier.hpp"

class World {
public:
	World();
	
	void Update( float dt );
	void Render();
	
	bool CanDudeJump();
	
	boost::shared_ptr<Dude> GetDude() {
		return dude;
	}
	
	void PushBullet( boost::shared_ptr<Bullet> bullet ) {
		bullets.push_back( bullet );
	}
	
	typedef std::vector<boost::shared_ptr<Enemy> > Enemies;
	
	Enemies GetEnemies() {
		return enemies;
	}
	void SetEnemies( Enemies _enemies ) {
		enemies = _enemies;
	}
	
	void RandomizeTargetPos( boost::shared_ptr<Enemy> a );
private:
	boost::shared_ptr<hgeSprite> sky_spr;
	boost::shared_ptr<Ground> ground;
	
	boost::shared_ptr<Dude> dude;
	
	typedef std::vector<boost::shared_ptr<Bullet> > Bullets;
	Bullets bullets;
	
	Enemies enemies;
	
	boost::shared_ptr<hgeFont> arial10;
	
	boost::shared_ptr<Notifier> notifier;
	
	void Frag();
	
	void RenderDebug();
	
	void InitDators();
	
	bool show_bullets;
	boost::shared_ptr<Dator<bool> > showBullets;
	bool show_bounds;
	boost::shared_ptr<Dator<bool> > showBounds;
	
	HgeObj hge;
};

#endif
