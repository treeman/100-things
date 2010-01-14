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
#include "LevelLoader.hpp"
#include "WorldListener.hpp"
#include "Background.hpp"

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
	
	void RandomizeTargetPos( boost::shared_ptr<Enemy> a );
	
	void AddListener( WorldListener *const listener );
private:
	void LoadLevel( boost::shared_ptr<Level> lvl );
	
	void CheckLevelCompletion();
	void LevelCompleted();
	void GameOver();
	
	boost::shared_ptr<Level> curr_lvl;
	
	boost::shared_ptr<Ground> ground;
	
	boost::shared_ptr<Dude> dude;
	
	typedef std::vector<boost::shared_ptr<Bullet> > Bullets;
	Bullets bullets;
	
	typedef std::vector<boost::shared_ptr<Enemy> > Enemies;
	Enemies enemies;
	
	boost::shared_ptr<hgeFont> arial10;
	
	boost::shared_ptr<Notifier> notifier;
	
	void Frag( boost::shared_ptr<Enemy> enemy, boost::shared_ptr<Bullet> bullet );
	
	boost::shared_ptr<LevelLoader> level_loader;
	
	typedef std::vector<WorldListener*> Listeners;
	Listeners listeners;
	
	boost::shared_ptr<Background> background;
	
	void RenderDebug();
	
	void InitDators();
	
	bool show_bullets;
	boost::shared_ptr<Dator<bool> > showBullets;
	bool show_bounds;
	boost::shared_ptr<Dator<bool> > showBounds;
	
	HgeObj hge;
};

#endif
