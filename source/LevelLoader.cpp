#include "includes/System/ErrorHandling.hpp"
#include "includes/LevelLoader.hpp"

LevelLoader::LevelLoader() : curr( 0 )
{
	boost::shared_ptr<Level> lvl( new Level() );
	
	EnemyInfo i;
	i.time = 0;
	for( int n = 0; n < 10; ++n )
	{
		i.unused_pos.push_back( Vec2D( 10, 10 + n * 40 ) );
	}
	lvl->infos.push_back( i );
	
	levels.push_back( lvl );
}

boost::shared_ptr<Level> LevelLoader::GetNextLevel()
{
	if( curr < levels.size() )
	{
		return levels[curr++];
	}
	else {
		throw( std::out_of_range( "nuthin initialized ffs" ) );
	}
}
boost::shared_ptr<Level> LevelLoader::GetLevel( int num )
{
	return levels.at(num);
}

bool LevelLoader::NoLevels()
{
	return curr == levels.size();
}
