#include "includes/SimpleWeapon.hpp"

SimpleWeapon::SimpleWeapon() : Weapon( 0.10 ) 
{ }

boost::shared_ptr<Bullet> SimpleWeapon::GetBullet( Vec2D fire_pos, Vec2D dir ) {
	boost::shared_ptr<Bullet> b( new SimpleBullet( fire_pos, dir ) );
	return b;
}
