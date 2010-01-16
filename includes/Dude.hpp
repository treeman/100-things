#ifndef DUDE_HPP_INCLUDED
#define DUDE_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <vector>

#include "System/Hge.hpp"
#include "System/Vec2D.hpp"
#include "System/Shape.hpp"

#include "Weapon.hpp"
#include "Shakeable.hpp"

class World;

struct Img {
	boost::shared_ptr<hgeSprite> spr;
	float w, h;
};

class Dude : public Shakeable {
public:
	Dude( World *const world );
	
	void MoveLeft();
	void MoveRight();
	
	void Shoot( Vec2D target );
	
	void Jump();
	void Duck();
	void Roll();
	
	void EnemyKilled();
	
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
	
	float GetRage() const {
		return rage;
	}
	
	Shape::Rect Bounds();
	
	void Update( float dt );
	void Render();
private:
	void SetOrientation();
	void FaceLeft();
	void FaceRight();
	
	TexObj dude_tex;
	boost::shared_ptr<Img> dude;
	
	typedef std::vector<boost::shared_ptr<Img> > Dudes;
	Dudes dudes;
	
	HgeObj hge;
	
	Vec2D pos;
	Vec2D vel;
	Vec2D acc;
	
	void SetRage( float perc );
	
	const float rage_decline;
	Timer rage_decline_timer;
	
	const float rage_max_acc;
	const float rage_min_acc;
	
	float curr_max_acc;
	
	float rage;
	
	boost::shared_ptr<Weapon> weapon;
	
	World *const world;
};

#endif
