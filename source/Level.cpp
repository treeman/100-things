#include <boost/foreach.hpp>

#include "includes/Level.hpp"
#include "includes/World.hpp"

bool has_time_passed( EnemyInfo e )
{
	return e.has_passed;
}

bool is_before( EnemyInfo e1, EnemyInfo e2 )
{
	return e1.time < e2.time;
}

Level::Level( World *const _world ) : level_time( 0 ), world( _world )
{
	
}

void Level::Update( float dt )
{
	if( infos.empty() ) return;
	
	level_time += dt;
	
	std::sort( infos.begin(), infos.end(), is_before );
	
	BOOST_FOREACH( EnemyInfo e, infos )
	{
		if( e.time >= level_time ) {
			e.has_passed = true;
			curr_info = &e;
		}
	}
	curr_info->has_passed = false;
	
	infos.erase( std::remove_if( infos.begin(), infos.end(), has_time_passed ), infos.end() );
	
	World::Enemies enemies = world->GetEnemies();
	
	EnemyInfo::Positions::iterator pit = curr_info->positions.begin();
	World::Enemies::iterator eit = enemies.begin();
	
	//set positions for every enemy
	for( ; pit != curr_info->positions.end() && eit != enemies.end(); ++pit, ++eit )
	{
		(*eit)->SetPos( *pit );
	}
	
	//if some enemies don't have a new positons, assign a random one
	for( ; eit != enemies.end(); ++eit )
	{
		world->RandomizeTargetPos( *eit );
	}
}
