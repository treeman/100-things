#include "includes/SimpleWeapon.hpp"
#include "includes/System/Log.hpp"

SimpleWeapon::SimpleWeapon() : Weapon( 0.10, 11.5, 22 ) 
{ }

boost::shared_ptr<Bullet> SimpleWeapon::GetBullet( Vec2D fire_pos, Vec2D dir ) {
	boost::shared_ptr<Bullet> b( new SimpleBullet( fire_pos, dir ) );
	return b;
}

AfroShooterWeapon::AfroShooterWeapon() : Weapon( 0, 34, 25 ), eff( "sound/bang.wav" )
{ }

boost::shared_ptr<Bullet> AfroShooterWeapon::GetBullet( Vec2D fire_pos, Vec2D dir ) {
	boost::shared_ptr<Bullet> b( new AfroBullet( fire_pos, dir ) );
	return b;
}
void AfroShooterWeapon::PlayShootSound()
{
	hge->Effect_PlayEx( eff, 5 );
}
