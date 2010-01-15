#ifndef DUDE_HPP_INCLUDED
#define DUDE_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"
#include "System/Vec2D.hpp"
#include "System/Shape.hpp"

#include "Weapon.hpp"
#include "Shakeable.hpp"

class World;

class Dude : public Shakeable {
public:
	Dude( World *const world );
	
	void MoveLeft();
	void MoveRight();
	
	void Shoot( Vec2D target );
	
	void Jump();
	void Duck();
	void Roll();
	
	Vec2D GetVel() {
		return vel;
	}
	void SetVel( Vec2D v ) {
		vel = v;
	}
	
	Vec2D GetPos() {
		return pos;
	}
	void SetPos( Vec2D p );
	
	Shape::Rect Bounds();
	
	void Update( float dt );
	void Render();
private:
	void SetOrientation();
	void FaceLeft();
	void FaceRight();

	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	
	HgeObj hge;
	
	Vec2D pos;
	Vec2D vel;
	Vec2D acc;
	
	float max_vel;
	float max_acc;
	
	boost::shared_ptr<Weapon> weapon;
	
	World *const world;
};

#endif
