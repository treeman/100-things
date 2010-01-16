#include "includes/System/Log.hpp"
#include "includes/Game.hpp"
#include "includes/GameWorld.hpp"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>

Game::Game( int argc, char *argv[] )
{
	hge->System_SetState( HGE_DONTSUSPEND, true );
	hge->System_SetState( HGE_SHOWSPLASH, false );
	hge->System_SetState( HGE_HIDEMOUSE, true );

	//defaults to curr time =)
	hge->Random_Seed( 0 );
	
	Settings::Get().ParseSetting( "video_screen_windowed 1" );
	Settings::Get().ParseSetting( "video_screen_width 800" );
	Settings::Get().ParseSetting( "video_screen_height 600" );
	Settings::Get().ParseSetting( "video_screen_bpp 32" );
	
	Settings::Get().ParseSetting( "sound_enabled 1" );
	Settings::Get().ParseSetting( "stream_volume 100" );
	Settings::Get().ParseSetting( "music_volume 100" );
	Settings::Get().ParseSetting( "effect_volume 100" );

	Settings::Get().ParseSetting( "video_caption_title The Chronicles of Bim: The 100 Fake Afros" );
	
	try {
		Settings::Get().ParseFile( "settings.ini" );
	}
	catch( Error::file_not_found &e ) {
		Log::Get().Write( "engine", "oops, you've deleted the 'settings.ini' file!" );
		Log::Get().Write( "engine", "God will not forgive you!!! :@" );
	}
	
	//parse command-line arguments, skip program name
	if( argc > 1 ) {
		for( int i = 1; i < argc; ++i ) {
			Settings::Get().ParseSetting( std::string( argv[i] ) );
		}
	}
}
Game::~Game()
{
	
}

bool Game::Logic()
{
	const float dt = hge->Timer_GetDelta();
	
	//set the new state to handle stuff
	curr_state = state_handler->Top();
	
	if( curr_state ) {
		
		hgeInputEvent event;
		while( hge->Input_GetEvent( &event ) ) 
		{
			if( console->HandleEvent( event ) ) {
				curr_state->HandleEvent( event );
			}
		}
		
		console->Update( dt );
		game_debug->Update( dt );
		curr_state->Update( dt );
	}
	
	return state_handler->ShallExit();
}

bool Game::Render()
{	
	hge->Gfx_BeginScene();
	hge->Gfx_Clear( 0xFF000000 );
	
	curr_state->Render();
	game_debug->Render();
	console->Render();

	hge->Gfx_EndScene();
	return false;
}

void Game::Init()
{
	window_manager.reset( new WindowManager() );
	sound_manager.reset( new SoundManager() );
	
	state_handler.reset( new StateHandler() );
	
	boost::shared_ptr<GameState> state( new GameWorld( state_handler.get() ) );
	state_handler->Push( state );
	state.reset( new Logo( state_handler.get() ) );
	state_handler->Push( state );
	
	curr_state = state_handler->Top();
	
	console.reset( new Console() );
	
	console->AddHistory( "starting up the ownage game environment" );
	console->AddHistory( "screen res: " + 
		Settings::Get().GetValue( "video_screen_width" ) + "x" + 
		Settings::Get().GetValue( "video_screen_height" )
	);
	
	game_debug.reset( new GameDebug() );
}
