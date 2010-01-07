#include <boost/scoped_ptr.hpp>

#include "includes/Game.hpp"
#include "includes/System/ErrorHandling.hpp"
#include "includes/System/Hge.hpp"

boost::scoped_ptr<Game> game;

bool frame_func()
{
	return game->Logic();
}

bool render_func()
{
	return game->Render();
}

int main( int argc, char *argv[] )
{	
	try {
		Log::Get().AddLogFile( "engine", "engine_log.txt" );
		
		HgeObj hge;
		
		hge->System_SetState( HGE_FRAMEFUNC, frame_func );
		hge->System_SetState( HGE_RENDERFUNC, render_func );
		hge->System_SetState( HGE_WINDOWED, true );
		
		game.reset( new Game( argc, argv ) );
		
		Log::Get().Write( "engine", "Initiating hge" );
		if( hge->System_Initiate() )
		{
			game->Init();
			Log::Get().Write( "engine", "Let's Rock" );
			hge->System_Start();
		}
	}
	catch( std::exception &e )
	{
		Log::Get().Write( "engine", "Big exception: %s", e.what() );
	}
	catch( ... )
	{
		Log::Get().Write( "engine", "Big unknown exception caught!" );
	}

	return 0;
}
