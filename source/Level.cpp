#include <boost/foreach.hpp>

#include "includes/Level.hpp"
#include "includes/SimpleEnemy.hpp"

bool has_time_passed( EnemyInfo e )
{
	return e.has_passed;
}

bool operator < ( const EnemyInfo &i1, const EnemyInfo &i2 ) {
	return i1.time < i2.time;
}

Level::Level( World *const _world ) : curr_info( 0 ), level_time( 0 ), fnt( new hgeFont( "fnt/arial10.fnt" ) ), world( _world )
{
	show_debug = false;
	showDebug.reset( new Dator<bool>( show_debug ) );
	Settings::Get().RegisterVariable( "level_debug", boost::weak_ptr<BaseDator>( showDebug ) );
	
	InitEnemyBag( 0.3, 0.49, 0.2, 0.01 );
	
	total_enemies = 300;
	enemies_spawned = 0;
	
	stats_mod = 1.0;
}

void Level::SetTargetPos( Enemies enemies )
{
	for( Enemies::iterator it = enemies.begin(); it != enemies.end(); ++it )
	{
		(*it)->SetTargetPos( GetTargetPos() );
	}
}

bool Level::IsComplete()
{
	return enemies_spawned >= total_enemies;
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
	enemy_bag.MakeAvailable( e->Type() );
}

boost::shared_ptr<Enemy> Level::GetEnemy()
{
	boost::shared_ptr<Enemy> enemy;
	
	if( enemies_spawned < total_enemies ) {
		
		Vec2D pos( hge->Random_Float( 0, 800 ), -40 );
		
		switch( enemy_bag.Get() ) {
			case ENEMY_MUTANT:
				enemy.reset( new MutantAfro( pos ) );
				break;
			case ENEMY_PIPPI:
				enemy.reset( new PippiAfro( pos ) );
				break;
			case ENEMY_SHOOTER:
				enemy.reset( new ShooterAfro( pos, world ) );
				break;
			case ENEMY_WORM:
				pos.x = pos.x < 400 ? -100 : 800;
				enemy.reset( new AfroWorm( pos, 560 ) );
				break;
		}
		
		++enemies_spawned;
		
	}
	
	enemy->SetStatsMod( stats_mod );
	
	return enemy;
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

void Level::InitEnemyBag( float mutant_perc, float pippi_perc, float shooter_perc, float worm_perc )
{
	enemy_bag.Clear();
	
	const int num_mutants = (int)( mutant_perc * 100 );
	for( int i = 0; i < num_mutants; ++i )
	{
		enemy_bag.Add( ENEMY_MUTANT );
	}
	
	const int num_pippis = (int)( pippi_perc * 100 );
	for( int i = 0; i < num_pippis; ++i )
	{
		enemy_bag.Add( ENEMY_PIPPI );
	}
	
	const int num_shooters = (int)( shooter_perc * 100 );
	for( int i = 0; i < num_shooters; ++i )
	{
		enemy_bag.Add( ENEMY_SHOOTER );
	}
	
	const int num_worms = (int)( worm_perc * 100 );
	for( int i = 0; i < num_worms; ++i )
	{
		enemy_bag.Add( ENEMY_WORM );
	}
}
