#ifndef ALIEN_HPP_INCLUDED
#define ALIEN_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"
#include "System/Vec2D.hpp"
#include "System/Shape.hpp"

class Alien {
public:
	Alien( Vec2D pos );
	
	Shape::Rect Bounds();
	
	bool CanKill() const {
		return can_kill;
	}
	void Kill() {
		can_kill = true;
	}
	
	void Update( float dt );
	void Render();
private:
	Vec2D pos;
	
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	
	bool can_kill;
};

#endif
