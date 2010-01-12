#ifndef ALIEN_HPP_INCLUDED
#define ALIEN_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"
#include "System/Vec2D.hpp"
#include "System/Shape.hpp"
#include "System/Settings.hpp"

class Enemy {
public:
	Enemy( Vec2D pos );
	
	Shape::Rect Bounds();
	
	bool CanKill() const {
		return can_kill;
	}
	void Kill() {
		can_kill = true;
	}
	
	void SetPos( Vec2D p ) {
		pos = p;
	}
	Vec2D GetPos() {
		return pos;
	}
	
	void SetVel( Vec2D v ) {
		vel = v;
	}
	Vec2D GetVel() {
		return vel;
	}
	
	void SetTargetPos( Vec2D target );
	Vec2D GetTargetPos() {
		return target_pos;
	}
	bool HasReachedGoal();
	
	void Update( float dt );
	void Render();
private:
	Vec2D acc;
	Vec2D vel;
	Vec2D pos;
	
	Vec2D target_pos;
	
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	
	bool can_kill;
	
	float max_acc;
	float max_vel;
	
	HgeObj hge;
	
	boost::shared_ptr<hgeFont> fnt;
	bool show_debug;
	boost::shared_ptr<Dator<bool> > showDebug;
};

#endif
