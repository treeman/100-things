#include "includes/Mouse.hpp"

Mouse::Mouse() : tex( "gfx/mouse.png" ), is_over( false ), in_click( false )
{
	normal.reset( new hgeSprite( tex, 0, 0, 15, 16 ) );
	normal->SetHotSpot( 8, 8 );
	normal->SetColor( 0xff000000 );
}
	
bool Mouse::HandleEvent( hgeInputEvent &e )
{
	pos.x = e.x;
	pos.y = e.y;
	if( e.type == INPUT_MBUTTONDOWN && e.key == HGEK_LBUTTON ) {
		in_click = true;
	}
	else if( e.type == INPUT_MBUTTONUP && e.key == HGEK_LBUTTON ) {
		in_click = false;
	}
	return true;
}

void Mouse::Render()
{
	normal->Render( pos.x, pos.y );
}
void Mouse::HoverOver( bool b )
{
	is_over = b;
}
