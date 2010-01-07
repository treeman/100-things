#include "includes/Dude.hpp"
#include "includes/World.hpp"
#include "includes/SimpleWeapon.hpp"

Dude::Dude( World *const _world ) : world( _world )
{tex.Load( "gfx/dude.png" );
	spr.reset( new hgeSprite( tex, 0, 0, 23, 44 ) );
	spr->SetHotSpot( 0, 44 );
	
	max_acc = 400;
	max_vel = 200;
	
	weapon.reset( new SimpleWeapon() );
	
	SetPos( Vec2D( 20, 560 ) );
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
	vel += Vec2D( 0, -600 );
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
	return Shape::Rect( pos.x, pos.y - 44, 23, 44 );
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
	spr->Render( (int)pos.x, (int)pos.y );
}

void Dude::SetOrientation()
{
	float mx, my;
	hge->Input_GetMousePos( &mx, &my );
	
	if( mx < pos.x + 11.5 ) {
		FaceLeft();
	}
	else if( mx > pos.x + 11.5 ) {
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
