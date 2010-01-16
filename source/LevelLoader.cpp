#include <boost/foreach.hpp>

#include "includes/System/ErrorHandling.hpp"
#include "includes/System/Lua.hpp"

#include "includes/LevelLoader.hpp"

struct int2 {
	int2( int _x, int _y ) : x( _x ), y( _y ) { }
	int x, y;
};

LevelLoader::LevelLoader( World *const _world ) : curr( 0 ), world( _world )
{

}

void LevelLoader::LoadLevels( std::string file )
{
	LuaState L;
	
	if( luaL_dofile( L, file.c_str() ) ) {
		const char *str = lua_tostring( L, -1 );
		lua_pop( L, -1 );
		throw( Error::lua_error( str ) );
	}
	
	lua_getglobal( L, "levels" );
	for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) ) 
	{
		//parse a level here
		boost::shared_ptr<Level> lvl( new Level( world ) );
		
		lua_pushstring( L, "total_enemies" );
		lua_gettable( L, -2 );
		
		if( lua_isnumber( L, -1 ) ) {
			lvl->total_enemies = (int)lua_tonumber( L, -1 );
		}
		lua_pop( L, 1 );
		
		//get the enemy appearance percentages
		lua_pushstring( L, "enemy_types" );
		lua_gettable( L,  -2 );
		
		if( lua_istable( L, -1 ) ) {
			float pippis = 0, mutants = 0, worms = 0, shooters = 0;
			
			lua_pushstring( L, "pippi" );
			lua_gettable( L, -2 );
			
			if( lua_isnumber( L, -1 ) ) {
				pippis = (float)lua_tonumber( L, -1 );
			}
			lua_pop( L, 1 );
			
			lua_pushstring( L, "mutant" );
			lua_gettable( L, -2 );
			
			if( lua_isnumber( L, -1 ) ) {
				mutants = (float)lua_tonumber( L, -1 );
			}
			lua_pop( L, 1 );
			
			lua_pushstring( L, "worm" );
			lua_gettable( L, -2 );
			
			if( lua_isnumber( L, -1 ) ) {
				worms = (float)lua_tonumber( L, -1 );
			}
			lua_pop( L, 1 );
			
			lua_pushstring( L, "shooter" );
			lua_gettable( L, -2 );
			
			if( lua_isnumber( L, -1 ) ) {
				shooters = (float)lua_tonumber( L, -1 );
			}
			lua_pop( L, 1 );
			
			lvl->InitEnemyBag( mutants, pippis, shooters, worms );
		}
		lua_pop( L, 1 );
		
		//read formations - EnemyInfo -- bad name I know...
		lua_pushstring( L, "formations" );
		lua_gettable( L, -2 );
		
		if( lua_istable( L, -1 ) ) {
			for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) ) 
			{
				EnemyInfo i;
				
				lua_pushstring( L, "change_time" );
				lua_gettable( L, -2 );
				
				if( lua_isnumber( L, -1 ) ) {
					i.time = (float)lua_tonumber( L, -1 );
				}
				lua_pop( L, 1 );
				
				lua_pushstring( L, "pos" );
				lua_gettable( L, -2 );
				
				if( lua_istable( L, -1 ) ) {
					
					//read formation coordinates
					int iy = 1;
					int ix = 0;
					
					int max_x = 0;
					int max_y = 0;
					
					std::vector<int2> coordinates;
					
					//for each row
					for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) ) 
					{
						if( lua_istable( L, -1 ) ) {
							ix = 0;
							
							//for each string in every row
							for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) ) {
								if( lua_isstring( L, -1 ) ) {
									
									std::string s = lua_tostring( L, -1 );
									
									if( s != " " && s != "" ) {
										coordinates.push_back( int2( ix, iy ) );
									}
								}
								
								++ix;
								if( ix > max_x ) {
									max_x = ix;
								}
							}
						}
						
						++iy;
					}
					
					max_y = iy;
					
					//convert grid coordinate positions to screen positions
					const int screen_w = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_width" ) );
					const int screen_h = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_height" ) );
					
					const int x_blocks = screen_w / max_x;
					const int y_blocks = screen_h / max_y;
					
					BOOST_FOREACH( int2 coord, coordinates ) {
						i.unused_pos.push_back( Vec2D( coord.x * x_blocks, coord.y * y_blocks ) );
					}
				}
				lua_pop( L, 1 );
				
				lvl->infos.push_back( i );	
			}
		}
		else {
			EnemyInfo i;
			i.time = 0;
			lvl->infos.push_back( i );
		}
		lua_pop( L, 1 );
		
		levels.push_back( lvl );
	}
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

void LevelLoader::SetStatsMod( float mod )
{
	BOOST_FOREACH( boost::shared_ptr<Level> lvl, levels )
	{
		lvl->SetStatsMod( mod );
	}
}
