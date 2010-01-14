#ifndef SIMPLEBULLET_HPP_INCLUDED
#define SIMPLEBULLET_HPP_INCLUDED

#include "Bullet.hpp"

class SimpleBullet : public Bullet {
public:
	SimpleBullet( Vec2D pos, Vec2D dir );
	
	Shape::Rect Bounds() const;
	
	void Update( float dt );
	void Render();
private:
	HgeObj hge;
};

class AfroBullet : public Bullet {
public:
	AfroBullet( Vec2D pos, Vec2D dir );
	
	Shape::Rect Bounds() const;
	
	void Update( float dt );
	void Render();
private:
	HgeObj hge;
	const float w, h;
	
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
};

#endif
