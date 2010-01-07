#ifndef SIMPLEWEAPON_HPP_INCLUDED
#define SIMPLEWEAPON_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Timer.hpp"
#include "System/Vec2D.hpp"
#include "Weapon.hpp"

class SimpleBullet : public Bullet {
public:
	SimpleBullet( Vec2D pos, Vec2D dir );
	
	Shape::Rect Bounds() const {
		return Shape::Rect( info.pos.x, info.pos.y, 1, 1 );
	}
	
	void Update( float dt );
	void Render();
private:
	HgeObj hge;
};

class SimpleWeapon : public Weapon {
public:
	SimpleWeapon();
protected:
	boost::shared_ptr<Bullet> GetBullet( Vec2D fire_pos, Vec2D dir );
};

#endif
