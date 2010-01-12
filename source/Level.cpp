#include <boost/foreach.hpp>

#include "includes/Level.hpp"

bool has_time_passed( EnemyInfo e )
{
	return e.has_passed;
}

bool operator < ( const EnemyInfo &i1, const EnemyInfo &i2 ) {
	return i1.time < i2.time;
}

Level::Level() : curr_info( 0 ), level_time( 0 )
{
	
}

void Level::UpdateTargetPos( Enemies enemies )
{
	EnemyInfo info = infos.at( curr_info );
	
	EnemyInfo::Positions::iterator pit = info.positions.begin();
	Enemies::iterator eit = enemies.begin();
	
	for( ; pit != info.positions.end() && eit != enemies.end(); ++pit, ++eit )
	{
		(*eit)->SetTargetPos( *pit );
	}
	
	for( ; eit != enemies.end(); ++eit )
	{
		RandomizeTargetPos( *eit );
	}
}

void Level::RandomizeTargetPos( boost::shared_ptr<Enemy> a )
{
	a->SetTargetPos( RandomizeTargetPos() );
}

void Level::GoalReached( boost::shared_ptr<Enemy> e )
{
	
}
void Level::EnemyDead( boost::shared_ptr<Enemy> e )
{
	
}

void Level::Update( float dt )
{
	level_time += dt;
}

Vec2D Level::RandomizeTargetPos()
{
	return Vec2D( hge->Random_Int( 0, 800 ), hge->Random_Int( 0, 500 ) );
}

Vec2D Level::GetTargetPos()
{
	
}

void Level::FreeTargetPos( Vec2D target )
{
	
}
