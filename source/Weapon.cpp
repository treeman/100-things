#include "includes/Weapon.hpp"

Weapon::Weapon( float _bullet_delay ) : bullet_delay( _bullet_delay )
{
	
}
	
boost::shared_ptr<Bullet> Weapon::Shoot( Vec2D target )
{
	if( delay_timer.GetTime() > bullet_delay || delay_timer.GetTime() == 0 ) {
		delay_timer.Restart();
		
		Vec2D fire_pos = Vec2D( pos.x + 11.5, pos.y - 22 );
		Vec2D dir = target - fire_pos;
		dir.Normalize();
		
		return GetBullet( fire_pos, dir );
	}
	else {
		boost::shared_ptr<Bullet> nothing;
		return nothing;
	}
}
