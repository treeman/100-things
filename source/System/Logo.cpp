#include "includes/System/Logo.hpp"
#include "includes/System/Settings.hpp"

Logo::Logo( StateHandler *const _state_handler ) : 
	GameState( _state_handler ), state_handler( _state_handler )
{
	logo_tex = hge->Texture_Load( "gfx/treelogo.png" );
	
	const int w = state_handler->GetWindowWidth();
	const int h = state_handler->GetWindowHeight();
	
//	logo dimensions 300x200
	logo.reset( new hgeSprite( logo_tex, 0, 0, 300, 200 ) );
	x = ( w - 300 ) / 2;
	y = ( h - 200 ) / 2 - 50;
	
	fade.reset( new hgeSprite( 0, 0, 0, w, h ) );
	fade_color = 0xFF000000;
	fade_dir = -1;
	
	t.Start();
}
Logo::~Logo()
{
	hge->Texture_Free( logo_tex );
}

bool Logo::HandleEvent( hgeInputEvent &event )
{
	if( event.type == INPUT_KEYDOWN || event.type == INPUT_MBUTTONDOWN ) {
		state_handler->Pop();
	}
	return true;
}

void Logo::Update( float dt )
{
	const float fade_time = 1.0;
	const float fade_pause = 2.0;
	
	int alpha = GETA( fade_color );
	
	if( fade_dir == 1 ) 
	{
		alpha = (int)( 255 * t.GetTime() / fade_time );
		if( alpha > 255 ) {
			alpha = 255;
			state_handler->Pop();
			return;
		}
	}
	else if( fade_dir == -1 ) 
	{
		alpha = 255 - (int)( 255 * t.GetTime() / fade_time );
		if( alpha < 0 ) {
			alpha = 0;
			fade_dir = 0;
			t.Restart();
		}
	}
	else if( fade_dir == 0 ) {
		if( t.GetTime() > fade_pause ) {
			fade_dir = 1;
			t.Restart();
		}
	}
	fade_color = SETA( fade_color, alpha );
}
void Logo::Render()
{
	logo->Render( x, y );
	fade->SetColor( fade_color );
	fade->Render(0,0);
}
