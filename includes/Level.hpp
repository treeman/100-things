#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include <vector>

#include "Enemy.hpp"

class LevelLoader;

struct EnemyInfo {
	EnemyInfo() : has_passed( false ) { }

	bool has_passed;
	float time;
	
	typedef std::vector<Vec2D> Positions;
	Positions positions;
};

class Level {
public:
	Level();
	
	typedef std::vector<boost::shared_ptr<Enemy> > Enemies;
	
	void UpdateTargetPos( Enemies enemies );
	
	void RandomizeTargetPos( boost::shared_ptr<Enemy> e );
	void GoalReached( boost::shared_ptr<Enemy> e );
	void EnemyDead( boost::shared_ptr<Enemy> e );
	
	void Update( float dt );
private:
	void Copy( const Level &lvl );
	
	Vec2D RandomizeTargetPos();
	
	typedef std::vector<EnemyInfo> Infos;
	Infos infos;
	
	Vec2D GetTargetPos();
	void FreeTargetPos( Vec2D target );
	
	size_t curr_info;
	
	float level_time;
	
	friend class LevelLoader;
	
	HgeObj hge;
};

#endif
