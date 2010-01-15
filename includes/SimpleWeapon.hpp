#ifndef SIMPLEWEAPON_HPP_INCLUDED
#define SIMPLEWEAPON_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Timer.hpp"
#include "System/Vec2D.hpp"
#include "System/Hge.hpp"

#include "Weapon.hpp"
#include "SimpleBullet.hpp"

class SimpleWeapon : public Weapon {
public:
	SimpleWeapon();
protected:
	boost::shared_ptr<Bullet> GetBullet( Vec2D fire_pos, Vec2D dir );
};

class AfroShooterWeapon : public Weapon {
public:
	AfroShooterWeapon();
protected:
	boost::shared_ptr<Bullet> GetBullet( Vec2D fire_pos, Vec2D dir );
	void PlayShootSound();
	
	EffectObj eff;
	HgeObj hge;
};

#endif
