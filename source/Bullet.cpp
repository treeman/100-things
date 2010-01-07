#include "includes/Bullet.hpp"

SimpleBullet::SimpleBullet( Vec2D pos, Vec2D dir )
{
	info.pos = pos;
	info.vel = dir;
	info.vel.SetLength( 200 );
}
	
void SimpleBullet::Update( float dt )
{
	info.pos = info.pos + info.vel * dt;
}
void SimpleBullet::Render()
{
	Vec2D p1 = info.pos;
	Vec2D p2 = p1 + info.vel;
	hge->Gfx_RenderLine( p1.x, p1.y, p1.x + 1, p1.y + 1, 0xff000000 );
}
