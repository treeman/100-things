#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include <vector>

#include "Enemy.hpp"
#include "System/Shufflebag.hpp"

class LevelLoader;

struct EnemyInfo {
	EnemyInfo() { Reset(); }
	
	void Reset() {
		has_passed = false;
		time = 0;
		used_pos.clear();
		unused_pos.clear();
	}

	bool has_passed;
	float time;
	
	typedef std::list<Vec2D> Positions;
	Positions used_pos;
	Positions unused_pos;
};

class World;

class Level {
public:
	Level( World *const world );
	
	typedef std::vector<boost::shared_ptr<Enemy> > Enemies;
	
	void SetTargetPos( Enemies enemies );
	
	bool IsComplete();
	
	void RandomizeTargetPos( boost::shared_ptr<Enemy> e );
	void GoalReached( boost::shared_ptr<Enemy> e );
	void EnemyDead( boost::shared_ptr<Enemy> e );
	
	boost::shared_ptr<Enemy> GetEnemy();
	
	void Update( float dt );
	void Render();
private:
	void Copy( const Level &lvl );
	
	Vec2D RandomizeTargetPos();
	
	typedef std::vector<EnemyInfo> Infos;
	Infos infos;
	
	Vec2D GetTargetPos();
	void FreeTargetPos( Vec2D target );
	
	size_t curr_info;
	
	void InitEnemyBag( float mutant_perc, float pippi_perc, float shooter_perc, float worm_perc );	
	ShuffleBag<EnemyType> enemy_bag;
	
	int total_enemies;
	int enemies_spawned;
	
	float level_time;
	float total_level_time;
	
	friend class LevelLoader;
	
	HgeObj hge;
	
	boost::shared_ptr<hgeFont> fnt;
	bool show_debug;
	boost::shared_ptr<Dator<bool> > showDebug;
	
	World *const world;
};

#endif
