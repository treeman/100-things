#include "includes/Alien.hpp"

Alien::Alien( Vec2D _pos ) : pos( _pos ), can_kill( false )
{
	tex.Load( "gfx/alien.png" );
	spr.reset( new hgeSprite( tex, 0, 0, 11, 8 ) );
}

Shape::Rect Alien::Bounds()
{
	return Shape::Rect( pos.x, pos.y, 11, 8 );
}
	
void Alien::Update( float dt )
{
	
}
void Alien::Render()
{
	spr->Render( pos.x, pos.y );
}
