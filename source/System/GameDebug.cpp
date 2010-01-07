#include "includes/System/GameDebug.hpp"

GameDebug::GameDebug()
{
	show_mouse_pos = false;
	showMousePos.reset( new Dator<bool>( show_mouse_pos ) );
	Settings::Get().RegisterVariable( "mouse_pos_show", boost::weak_ptr<BaseDator>( showMousePos ) );
	
	show_fps = false;
	showFPS.reset( new Dator<bool>( show_fps ) );
	Settings::Get().RegisterVariable( "fps_show", boost::weak_ptr<BaseDator>( showFPS ) );
	
	arial10.reset( new hgeFont( "fnt/arial10.fnt" ) );
	visitor20.reset( new hgeFont( "fnt/visitor20.fnt" ) );
}

void GameDebug::Update( float )
{
	
}
void GameDebug::Render()
{
	if( show_mouse_pos ) {
		float x, y;
		hge->Input_GetMousePos( &x, &y );
		arial10->SetColor( 0xffffffff );
		arial10->printf( 50, 5, HGETEXT_LEFT, "%.0f,%.0f", x, y );
	}
	
	if( show_fps ) {
		visitor20->SetColor( 0xffffffff );
		visitor20->printf( 5, 5, HGETEXT_LEFT, "%i", hge->Timer_GetFPS() );
	}
}
