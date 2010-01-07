#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Timer.hpp"
#include "System/Vec2D.hpp"

#include "Bullet.hpp"

class Weapon {
public:
	Weapon( float bullet_delay );
	virtual ~Weapon() { }
	
	Vec2D GetPos() const {
		return pos;
	}
	void SetPos( Vec2D p ) {
		pos = p;
	}
	
	boost::shared_ptr<Bullet> Shoot( Vec2D target );
protected:
	virtual boost::shared_ptr<Bullet> GetBullet( Vec2D fire_pos, Vec2D target ) = 0;
private:
	const float bullet_delay;
	
	Timer delay_timer;
	
	Vec2D pos;
};

#endif
