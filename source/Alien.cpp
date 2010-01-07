#include "includes/Alien.hpp"

const float w = 26;
const float h = 20;

Alien::Alien( Vec2D _pos ) : pos( _pos ), can_kill( false )
{
	tex.Load( "gfx/flyingafro.png" );
	spr.reset( new hgeSprite( tex, 0, 0, w, h ) );
}

Shape::Rect Alien::Bounds()
{
	return Shape::Rect( pos.x, pos.y, w, h );
}
	
void Alien::Update( float dt )
{
	
}
void Alien::Render()
{
	spr->Render( pos.x, pos.y );
}
