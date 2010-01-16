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
#include "Shakeable.hpp"

class GameWorld;

class World {
public:
	World( GameWorld *const game_world );
	
	void Update( float dt );
	void Render();
	
	bool CanDudeJump();
	
	boost::shared_ptr<Dude> GetDude() {
		return dude;
	}
	
	void PushBullet( boost::shared_ptr<Bullet> bullet );
	
	void RandomizeTargetPos( boost::shared_ptr<Enemy> a );
	
	void AddListener( WorldListener *const listener );
	
	void Shake( float level );
private:
	void LoadLevel( boost::shared_ptr<Level> lvl );
	
	void CheckLevelCompletion();
	void LevelCompleted();
	void GameCompleted();
	void GameOver();
	
	boost::shared_ptr<Level> curr_lvl;
	
	boost::shared_ptr<Ground> ground;
	
	boost::shared_ptr<Dude> dude;
	
	typedef std::vector<boost::shared_ptr<Bullet> > Bullets;
	
	Bullets bullets;
	
	void AddEnemy();
	typedef std::vector<boost::shared_ptr<Enemy> > Enemies;
	Enemies enemies;
	
	boost::shared_ptr<hgeFont> arial10;
	
	boost::shared_ptr<Notifier> notifier;
	
	void Frag( boost::shared_ptr<Enemy> enemy, boost::shared_ptr<Bullet> bullet );
	
	boost::shared_ptr<LevelLoader> level_loader;
	
	typedef std::vector<WorldListener*> Listeners;
	Listeners listeners;
	
	boost::shared_ptr<Background> background;
	
	void UpdateShake();
	void OffsetScreen( float x_off, float y_off );
	void ShakeDone();
	
	const float shake_time;
	const int num_shakes;
	const float shake_decline;
	
	const float max_x_shake, max_y_shake;
	
	Timer shake_timer;
	float shake_level;
	int shake_num;
	int shake_pos;
	
	float shake_x_offset, shake_y_offset;
	
	EffectObj shake_eff;
	
	int enemies_killed;
	Timer total_timer;
	
	float stats_mod;
	float stats_mod_incr;
	
	void RenderDebug();
	
	void InitDators();
	
	bool show_bullets;
	boost::shared_ptr<Dator<bool> > showBullets;
	bool show_bounds;
	boost::shared_ptr<Dator<bool> > showBounds;
	bool show_shakeinfo;
	boost::shared_ptr<Dator<bool> > showShakeInfo;
	
	HgeObj hge;
	
	GameWorld *const game_world;
};

#endif
