#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "System/Hge.hpp"
#include "System/Vec2D.hpp"
#include "System/Shape.hpp"

#include "Shakeable.hpp"

enum Target {
	TARGET_DUDE,
	TARGET_ENEMY
};

struct BulletInfo {
	Vec2D pos;
	Vec2D vel;
	Target target;
};

class Bullet : public Shakeable {
public:
	Bullet() : can_kill( false ) { }
	virtual ~Bullet() {}
	
	virtual Shape::Rect Bounds() const = 0;
	
	BulletInfo Info() const {
		return info;
	}
	
	bool CanKill() const {
		return can_kill;
	}
	void Kill() {
		can_kill = true;
	}
	
	virtual void Update( float dt ) = 0;
	virtual void Render() = 0;
protected:
	BulletInfo info;
	bool can_kill;
};

#endif
