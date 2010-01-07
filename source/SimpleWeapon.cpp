#include "includes/SimpleWeapon.hpp"

SimpleBullet::SimpleBullet( Vec2D pos, Vec2D dir )
{
	info.pos = pos;
	info.vel = dir;
	info.vel.SetLength( 800 );
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

SimpleWeapon::SimpleWeapon() : Weapon( 0.20 ) 
{ }

boost::shared_ptr<Bullet> SimpleWeapon::GetBullet( Vec2D fire_pos, Vec2D dir ) {
	boost::shared_ptr<Bullet> b( new SimpleBullet( fire_pos, dir ) );
	return b;
}
