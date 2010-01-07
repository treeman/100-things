#include "includes/System/Log.hpp"
#include "includes/System/Windowmanager.hpp"
#include "includes/System/Settings.hpp"

WindowManager::WindowManager() : scr_width( 800 ), scr_height( 600 ), scr_bpp( 32 ),
	scr_is_windowed( true ), title_name( "W00t nuthing initialized!" ), is_setup( false )
{
	Setup();
}

WindowManager::~WindowManager()
{
	
}

void WindowManager::Setup()
{
	Log::Get().Write( "engine", "Setting up the window" );
	
	screenWidth.reset( new Dator<int>( scr_width, boost::bind( &WindowManager::SetScreenWidth, this, _1 ) ) );
	screenHeight.reset( new Dator<int>( scr_height, boost::bind( &WindowManager::SetScreenHeight, this, _1 ) ) );
	screenBPP.reset( new Dator<int>( scr_bpp, boost::bind( &WindowManager::SetScreenBPP, this, _1 ) ) );
	screenIsWindowed.reset( new Dator<bool>( scr_is_windowed, boost::bind( &WindowManager::SetWindowed, this, _1 ) ) );
	titleName.reset( new Dator<std::string>( title_name, boost::bind( &WindowManager::SetScreenTitle, this, _1 ) ) );

    Settings::Get().RegisterVariable( "video_screen_width", boost::weak_ptr<BaseDator>( screenWidth ) );
	Settings::Get().RegisterVariable( "video_screen_height", boost::weak_ptr<BaseDator>( screenHeight ) );
	Settings::Get().RegisterVariable( "video_screen_bpp", boost::weak_ptr<BaseDator>( screenBPP ) );
    Settings::Get().RegisterVariable( "video_screen_windowed", boost::weak_ptr<BaseDator>( screenIsWindowed ) );
	Settings::Get().RegisterVariable( "video_caption_title", boost::weak_ptr<BaseDator>( titleName ) );
	
	hge->System_SetState( HGE_TITLE, title_name.c_str() );
	hge->System_SetState( HGE_WINDOWED, scr_is_windowed );
	hge->System_SetState( HGE_SCREENWIDTH, scr_width );
	hge->System_SetState( HGE_SCREENHEIGHT, scr_height );
	hge->System_SetState( HGE_SCREENBPP, scr_bpp );
	
	is_setup = true;
}

std::string WindowManager::SetWindowed( const bool &predicate )
{
	scr_is_windowed = predicate;
	if( is_setup ) {
		hge->System_SetState( HGE_WINDOWED, scr_is_windowed );
	}
	if( predicate ) {
		return "you're now surfing machine code in windowed mode";
	}
	else {
		return "you're now surfing machine code in fullscreen";
	}
}
std::string WindowManager::SetScreenWidth( const int &val )
{
	scr_width = val;
	if( is_setup ) {
		hge->System_SetState( HGE_SCREENWIDTH, scr_width );
	}
	return "nananana... you can't alter it here :)";
}
std::string WindowManager::SetScreenHeight( const int &val )
{
	scr_height = val;
	if( is_setup ) {
		hge->System_SetState( HGE_SCREENHEIGHT, scr_height );
	}
	return "nananana... you can't alter it here :()";
}
std::string WindowManager::SetScreenBPP( const int &val )
{
	scr_bpp = val;
	if( is_setup ) {
		hge->System_SetState( HGE_SCREENBPP, scr_bpp );
	}
	return "error: can't set bpp value";
}
std::string WindowManager::SetScreenTitle( const std::string &val )
{
	title_name = val;
	if( is_setup ) {
		hge->System_SetState( HGE_TITLE, title_name.c_str() );
	}
	return "setting window title to '" + title_name + "'";
}
