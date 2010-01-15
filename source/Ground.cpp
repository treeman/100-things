#include "includes/Ground.hpp"

Ground::Ground( float _x, float _y, float _w, float _h ) : Shakeable( 0.3, 0.3 ), x(_x), y(_y), w(_w), h(_h)
{
	spr.reset( new hgeSprite( 0, 0, 0, w, h ) );
	spr->SetColor( 0xff000000 );
}

void Ground::Render() {
	spr->Render( x + shake_x_offset, y + shake_y_offset );
}
