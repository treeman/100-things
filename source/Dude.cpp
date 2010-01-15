#include "includes/Dude.hpp"
#include "includes/World.hpp"
#include "includes/SimpleWeapon.hpp"

const float dude_w = 30;
const float dude_h = 50;

Dude::Dude( World *const _world ) : Shakeable( 0.5, 0.5 ), world( _world )
{
	tex.Load( "gfx/dude.png" );
	spr.reset( new hgeSprite( tex, 0, 0, dude_w, dude_h ) );
	spr->SetHotSpot( 0, dude_h );
	
	max_acc = 400;
	max_vel = 200;
	
	weapon.reset( new SimpleWeapon() );
	
	SetPos( Vec2D( 20, 600 - dude_h ) );
}

void Dude::MoveLeft()
{
	acc += Vec2D( -max_acc, 0 );
}
void Dude::MoveRight()
{
	acc += Vec2D( max_acc, 0 );
}

void Dude::Shoot( Vec2D target )
{
	boost::shared_ptr<Bullet> bullet = weapon->Shoot( target );
	if( bullet ) {
		world->PushBullet( bullet );
	}
}

void Dude::Jump()
{
	if( world->CanDudeJump() ) {
		vel.y = -600;
	}
}

void Dude::Duck()
{
	
}

void Dude::Roll()
{
	
}

void Dude::SetPos( Vec2D p ) {
	pos = p;
	weapon->SetPos( p );
}

Shape::Rect Dude::Bounds()
{
	return Shape::Rect( pos.x, pos.y - dude_h, dude_w,dude_h );
}

void Dude::Update( float dt )
{
	SetOrientation();
	
	const Vec2D gravity( 0, 1000 );
	
	const Vec2D real_acc = acc + gravity;
	const Vec2D new_vel = vel + real_acc * dt;
	vel = new_vel;
//	vel.TruncateLength( max_vel );
	const Vec2D new_pos = pos + vel * dt;
	SetPos( new_pos );
	
	acc( 0, 0 );
}
void Dude::Render()
{
	spr->Render( (int)pos.x + (int)shake_x_offset, (int)pos.y + (int)shake_y_offset );
}

void Dude::SetOrientation()
{
	float mx, my;
	hge->Input_GetMousePos( &mx, &my );
	
	if( mx < pos.x + dude_w / 2 ) {
		FaceLeft();
	}
	else if( mx > pos.x + dude_w / 2 ) {
		FaceRight();
	}
}

void Dude::FaceLeft()
{
	spr->SetFlip( true, false );
}
void Dude::FaceRight()
{
	spr->SetFlip( false, false );
}
