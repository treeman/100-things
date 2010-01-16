#include "includes/SimpleBullet.hpp"

SimpleBullet::SimpleBullet( Vec2D pos, Vec2D dir, int _size ) : size( _size )
{
	info.pos = pos;
	info.vel = dir;
	info.vel.SetLength( 800 );
	info.target = TARGET_ENEMY;
}

Shape::Rect SimpleBullet::Bounds() const {
	return Shape::Rect( info.pos.x, info.pos.y, size, size );
}
	
void SimpleBullet::Update( float dt )
{
	info.pos = info.pos + info.vel * dt;
}
void SimpleBullet::Render()
{
	const float x1 = info.pos.x + shake_x_offset;
	const float y1 = info.pos.y + shake_y_offset;
	const float x2 = info.pos.x + size + shake_x_offset;
	const float y2 = info.pos.y + size + shake_y_offset;
	
	hgeh::render_solid_rect( hge, x1, y1, x2, y2, 0xff000000 );
}

AfroBullet::AfroBullet( Vec2D pos, Vec2D dir ) : w( 10 ), h( 10 ), tex( "gfx/afrobullet.png" ), 
	spr( new hgeSprite( tex, 0, 0, w, h ) )
{
	info.pos = pos;
	info.vel = dir;
	info.vel.SetLength( 500 );
	info.target = TARGET_DUDE;
}

Shape::Rect AfroBullet::Bounds() const {
	return Shape::Rect( info.pos.x, info.pos.y, w, h );
}
	
void AfroBullet::Update( float dt )
{
	info.pos = info.pos + info.vel * dt;
}
void AfroBullet::Render()
{
	spr->Render( info.pos.x + shake_x_offset, info.pos.y + shake_y_offset );
}
