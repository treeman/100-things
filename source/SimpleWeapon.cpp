#include "includes/SimpleWeapon.hpp"

SimpleBullet::SimpleBullet( Vec2D pos, Vec2D dir )
{
	info.pos = pos;
	info.vel = dir;
	info.vel.SetLength( 800 );
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

SimpleWeapon::SimpleWeapon() : Weapon( 0.10 ) 
{ }

boost::shared_ptr<Bullet> SimpleWeapon::GetBullet( Vec2D fire_pos, Vec2D dir ) {
	boost::shared_ptr<Bullet> b( new SimpleBullet( fire_pos, dir ) );
	return b;
}
