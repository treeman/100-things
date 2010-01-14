#include "includes/SimpleBullet.hpp"

SimpleBullet::SimpleBullet( Vec2D pos, Vec2D dir )
{
	info.pos = pos;
	info.vel = dir;
	info.vel.SetLength( 800 );
	info.target = TARGET_ENEMY;
}

Shape::Rect SimpleBullet::Bounds() const {
	return Shape::Rect( info.pos.x, info.pos.y, 2, 2 );
}
	
void SimpleBullet::Update( float dt )
{
	info.pos = info.pos + info.vel * dt;
}
void SimpleBullet::Render()
{
	const float x1 = info.pos.x;
	const float y1 = info.pos.y;
	const float x2 = info.pos.x + 2;
	const float y2 = info.pos.y + 2;
	
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
	spr->Render( info.pos.x, info.pos.y );
}
