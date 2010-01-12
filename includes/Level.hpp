#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include <vector>

#include "Enemy.hpp"

class World;

struct EnemyInfo {
	EnemyInfo() : has_passed( false ) { }
	
	bool has_passed;
	float time;
	
	typedef std::vector<Vec2D> Positions;
	Positions positions;
};

class Level {
public:
	Level( World *const world );
	
	void Update( float dt );
private:
	typedef std::vector<EnemyInfo> Infos;
	Infos infos;
	
	EnemyInfo *curr_info;
	
	float level_time;
	
	World *const world;
};

#endif
