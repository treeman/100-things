#include <boost/foreach.hpp>

#include "includes/Dude.hpp"
#include "includes/World.hpp"
#include "includes/SimpleWeapon.hpp"

Dude::Dude( World *const _world ) : Shakeable( 0.5, 0.5 ), rage_decline( 0.1 ), rage_max_acc( 1400 ), rage_min_acc( 400 ), world( _world )
{
	dude_tex.Load( "gfx/dudes.png" );
	
	boost::shared_ptr<Img> d( new Img() );
	
	//lvl0
	d->w = 18; d->h = 37;
	d->spr.reset( new hgeSprite( dude_tex, 18, 33, d->w, d->h ) );
	d->spr->SetHotSpot( 0, d->h );
	dudes.push_back( d );
	
	d.reset( new Img() );
	
	//lvl1
	d->w = 20; d->h = 41;
	d->spr.reset( new hgeSprite( dude_tex, 77, 29, d->w, d->h ) );
	d->spr->SetHotSpot( 0, d->h );
	dudes.push_back( d );
	
	d.reset( new Img() );
	
	//lvl2
	d->w = 23; d->h = 42;
	d->spr.reset( new hgeSprite( dude_tex, 136, 28, d->w, d->h ) );
	d->spr->SetHotSpot( 0, d->h );
	dudes.push_back( d );
	
	d.reset( new Img() );
	
	//lvl3
	d->w = 26; d->h = 49;
	d->spr.reset( new hgeSprite( dude_tex, 195, 22, d->w, d->h ) );
	d->spr->SetHotSpot( 0, d->h );
	dudes.push_back( d );
	
	d.reset( new Img() );
	
	//lvl4
	d->w = 37; d->h = 56;
	d->spr.reset( new hgeSprite( dude_tex, 249, 14, d->w, d->h ) );
	d->spr->SetHotSpot( 0, d->h );
	dudes.push_back( d );
	
	d.reset( new Img() );
	
	//lvl5
	d->w = 52; d->h = 67;
	d->spr.reset( new hgeSprite( dude_tex, 301, 3, d->w, d->h ) );
	d->spr->SetHotSpot( 0, d->h );
	dudes.push_back( d );
	
	dude = dudes[0];
	
	weapon.reset( new SimpleWeapon( 0.10, 30, 2 ) );
	
	SetPos( Vec2D( 20, 600 - dude->h ) );
	
	SetRage( 0 );
	
	rage_decline_timer.Start();
}

void Dude::MoveLeft()
{
	acc += Vec2D( -curr_max_acc, 0 );
}
void Dude::MoveRight()
{
	acc += Vec2D( curr_max_acc, 0 );
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

void Dude::EnemyKilled()
{
	SetRage( rage + 0.01 );
}

void Dude::SetRage( float perc )
{
	rage = perc;
	if( rage > 1.0 ) rage = 1.0;
	
	if( rage < 0.2 ) {
		dude = dudes[0];
		weapon.reset( new SimpleWeapon( 0.12, 20, 2 ) );
	}
	else if( rage < 0.4 ) {
		dude = dudes[1];
		weapon.reset( new SimpleWeapon( 0.1, 25, 2 ) );
	}
	else if( rage < 0.55 ) {
		dude = dudes[2];
		weapon.reset( new SimpleWeapon( 0.09, 30, 3 ) );
	}
	else if( rage < 0.7 ) {
		dude = dudes[3];
		weapon.reset( new SimpleWeapon( 0.08, 30, 3 ) );
	}
	else if( rage < 0.9 ) {
		dude = dudes[4];
		weapon.reset( new SimpleWeapon( 0.07, 30, 4 ) );
	}
	else if( rage >= 0.9 ) {
		dude = dudes[5];
		weapon.reset( new SimpleWeapon( 0.06, 30, 5 ) );
	}
	
	curr_max_acc = rage_min_acc + ( rage_max_acc - rage_min_acc ) * rage;
}

void Dude::SetPos( Vec2D p ) {
	pos = p;
	weapon->SetPos( p );
}

Shape::Rect Dude::Bounds()
{
	return Shape::Rect( pos.x, pos.y - dude->h, dude->w, dude->h );
}

void Dude::Update( float dt )
{
	SetOrientation();
	
	if( rage_decline_timer.GetTime() >= 1.0 ) {
		SetRage( rage - rage * rage_decline * rage_decline_timer.GetTime() );
		rage_decline_timer.Restart();
	}
	
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
	dude->spr->Render( (int)pos.x + (int)shake_x_offset, (int)pos.y + (int)shake_y_offset + 2 );
}

void Dude::SetOrientation()
{
	float mx, my;
	hge->Input_GetMousePos( &mx, &my );
	
	if( mx < pos.x + dude->w / 2 ) {
		FaceLeft();
	}
	else if( mx > pos.x + dude->w / 2 ) {
		FaceRight();
	}
}

void Dude::FaceLeft()
{
	dude->spr->SetFlip( true, false );
}
void Dude::FaceRight()
{
	dude->spr->SetFlip( false, false );
}
