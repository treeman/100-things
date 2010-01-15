#include "includes/Weapon.hpp"

Weapon::Weapon( float _bullet_delay, float _x_off, float _y_off ) : bullet_delay( _bullet_delay )
	,x_off( _x_off ), y_off( _y_off )
{
	
}
	
boost::shared_ptr<Bullet> Weapon::Shoot( Vec2D target )
{
	if( bullet_delay == 0 || delay_timer.GetTime() >= bullet_delay || delay_timer.GetTime() == 0 ) {
		delay_timer.Restart();
		
		Vec2D fire_pos = Vec2D( pos.x + x_off, pos.y - y_off );
		Vec2D dir = target - fire_pos;
		dir.Normalize();
		
		return GetBullet( fire_pos, dir );
	}
	else {
		boost::shared_ptr<Bullet> nothing;
		return nothing;
	}
}
