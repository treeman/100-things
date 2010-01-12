#include <boost/foreach.hpp>

#include "includes/Level.hpp"

bool has_time_passed( EnemyInfo e )
{
	return e.has_passed;
}

bool operator < ( const EnemyInfo &i1, const EnemyInfo &i2 ) {
	return i1.time < i2.time;
}

Level::Level() : curr_info( 0 ), level_time( 0 ), fnt( new hgeFont( "fnt/arial10.fnt" ) )
{
	show_debug = true;
	showDebug.reset( new Dator<bool>( show_debug ) );
	Settings::Get().RegisterVariable( "level_debug", boost::weak_ptr<BaseDator>( showDebug ) );
}

void Level::SetTargetPos( Enemies enemies )
{
	for( Enemies::iterator it = enemies.begin(); it != enemies.end(); ++it )
	{
		(*it)->SetTargetPos( GetTargetPos() );
	}
}

void Level::RandomizeTargetPos( boost::shared_ptr<Enemy> a )
{
	a->SetTargetPos( RandomizeTargetPos() );
}

void Level::GoalReached( boost::shared_ptr<Enemy> e )
{
	FreeTargetPos( e->GetTargetPos() );
	e->SetTargetPos( GetTargetPos() );
}
void Level::EnemyDead( boost::shared_ptr<Enemy> e )
{
	FreeTargetPos( e->GetTargetPos() );
}

void Level::Update( float dt )
{
	level_time += dt;
	if( infos.size() > curr_info + 1 ) {
		if( infos.at( curr_info + 1 ).time < level_time ) {
			++curr_info;
		}
	}
}

void Level::Render()
{
	if( show_debug ) {
		fnt->SetColor( 0xffffffff );
		
		const float line_height = fnt->GetHeight() + 2;
		EnemyInfo *i = &infos.at( curr_info );
		int n = 0;
		
		fnt->Render( 300, 5, HGETEXT_LEFT, "used_pos" );
		for( EnemyInfo::Positions::iterator it = i->used_pos.begin(); it != i->used_pos.end(); ++it, ++n )
		{
			fnt->printf( 300, 20 + n * line_height, HGETEXT_LEFT, "%.0f,%.0f", it->x, it->y );
		}
		n = 0;
		
		fnt->Render( 350, 5, HGETEXT_LEFT, "unused_pos" );
		for( EnemyInfo::Positions::iterator it = i->unused_pos.begin(); it != i->unused_pos.end(); ++it, ++n )
		{
			fnt->printf( 350, 20 + n * line_height, HGETEXT_LEFT, "%.0f,%.0f", it->x, it->y );
		}
		
		fnt->printf( 430, 5, HGETEXT_LEFT, "time: %f", level_time );
	}
}

Vec2D Level::RandomizeTargetPos()
{
	return Vec2D( hge->Random_Int( 0, 800 ), hge->Random_Int( 0, 500 ) );
}

Vec2D Level::GetTargetPos()
{
	EnemyInfo *i = &infos.at( curr_info );
	if( i->unused_pos.empty() ) {
		return RandomizeTargetPos();
	}
	else {
		const Vec2D p = i->unused_pos.front();
		i->unused_pos.pop_front();
		i->used_pos.push_front( p );
		return p;
	}
}

void Level::FreeTargetPos( Vec2D target )
{
	EnemyInfo *i = &infos.at( curr_info );
	EnemyInfo::Positions::iterator it = std::find( i->used_pos.begin(), i->used_pos.end(), target );
	if( it != i->used_pos.end() )
	{
		i->used_pos.erase( it );
		i->unused_pos.push_front( target );
	}
}
