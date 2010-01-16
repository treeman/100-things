#include "includes/SimpleEnemy.hpp"
#include "includes/SimpleBullet.hpp"
#include "includes/World.hpp"
#include "includes/SimpleWeapon.hpp"

PippiAfro::PippiAfro( Vec2D pos ) : Enemy( pos ), max_acc( 2000 ), max_vel( 200 ), w( 26 ), h( 20 )
{
	tex.Load( "gfx/flyingafro.png" );
	spr.reset( new hgeSprite( tex, 0, 0, w, h ) );
}

Shape::Rect PippiAfro::Bounds()
{
	return Shape::Rect( pos.x, pos.y, w, h );
}

bool PippiAfro::HasReachedGoal()
{
	const Vec2D dist = pos - target_pos;
	return dist.Length() < 10;
}
	
void PippiAfro::Update( float dt )
{
	const Vec2D desired = target_pos - pos;
	acc = desired - vel;
	
	acc.TruncateLength( max_acc * stats_mod );
	
	const Vec2D new_vel = vel + acc * dt;
	vel = new_vel;
	vel.TruncateLength( max_vel * stats_mod );
	
	const Vec2D new_pos = pos + new_vel * dt;
	
	SetPos( new_pos );
}
void PippiAfro::Render()
{
	spr->Render( (int)pos.x + (int)shake_x_offset, (int)pos.y + (int)shake_y_offset );
	
	RenderDebug();
}

MutantAfro::MutantAfro( Vec2D pos ) : Enemy( pos ), max_acc( 2000 ), max_vel( 200 ), w( 26 ), h( 20 )
{
	tex.Load( "gfx/mutantafro.png" );
	spr.reset( new hgeSprite( tex, 0, 0, w, h ) );
}

Shape::Rect MutantAfro::Bounds()
{
	return Shape::Rect( pos.x, pos.y, w, h );
}

bool MutantAfro::HasReachedGoal()
{
	const Vec2D dist = pos - target_pos;
	return dist.Length() < 10;
}
	
void MutantAfro::Update( float dt )
{
	const Vec2D desired = target_pos - pos;
	acc = desired - vel;
	
	acc.SetLength( max_acc * stats_mod );
	
	const Vec2D new_vel = vel + acc * dt;
	vel = new_vel;
	vel.SetLength( max_vel * stats_mod );
	
	const Vec2D new_pos = pos + new_vel * dt;

	pos = new_pos;
}
void MutantAfro::Render()
{
	spr->Render( (int)pos.x + (int)shake_x_offset, (int)pos.y + (int)shake_y_offset );
	
	RenderDebug();
}

AfroWorm::AfroWorm( Vec2D pos, float y ) : Enemy( pos ), max_acc( 2000 ), max_vel( 100 ), w( 100 ), h( 73 ), ground_y( y )
{
	tex.Load( "gfx/afroworm.png" );
	spr.reset( new hgeSprite( tex, 0, 0, w, h ) );
	spr->SetHotSpot( 0, h );
	
	FaceLeft();
}

Shape::Rect AfroWorm::Bounds()
{
	return Shape::Rect( pos.x, pos.y - h, w, h );
}

bool AfroWorm::HasReachedGoal()
{
	if( target_pos.x < 400 ) {
		return pos.x + w < 0;
	}
	else {
		return pos.x > 800;
	};
}

void AfroWorm::SetTargetPos( Vec2D target )
{
	if( pos.x < target.x ) {
		target_pos = Vec2D( 800, ground_y );
	}
	else {
		target_pos = Vec2D( -100, ground_y );
	}
}
	
void AfroWorm::Update( float dt )
{
	const Vec2D desired = target_pos - pos;
	acc = desired - vel;
	acc.SetLength( max_acc * stats_mod );
	
	const Vec2D new_vel = vel + acc * dt;
	vel = new_vel;
	vel.TruncateLength( max_vel * stats_mod );
	
	if( vel.x > 0 ) {
		FaceRight();
	}
	else {
		FaceLeft();
	}
	
	const Vec2D new_pos = pos + new_vel * dt;

	pos = new_pos;
	pos.y = ground_y;
}
void AfroWorm::Render()
{
	spr->Render( (int)pos.x + (int)shake_x_offset, (int)pos.y + 4 + (int)shake_y_offset );
	
	RenderDebug();
}

void AfroWorm::FaceLeft()
{
	spr->SetFlip( false, false );
}
void AfroWorm::FaceRight()
{
	spr->SetFlip( true, false );
}

ShooterAfro::ShooterAfro( Vec2D pos, World *const _world ) : Enemy( pos ), max_acc( 2000 ), max_vel( 200 ), w( 42 ), h( 36 )
	, weapon( new AfroShooterWeapon() ), world( _world )
{
	tex.Load( "gfx/shooterafro.png" );
	spr.reset( new hgeSprite( tex, 0, 0, w, h ) );
	
	delay_bag.Add( 1 ).Add( 2 ).Add( 2.5 ).Add( 4 ).Add( 3.5 ).Add( 5 ).
	Add( 10 ).Add( 1 ).Add( 4.2 );
	
	ResetShootDelay();
}

Shape::Rect ShooterAfro::Bounds()
{
	return Shape::Rect( pos.x, pos.y, w, h );
}

bool ShooterAfro::HasReachedGoal()
{
	const Vec2D dist = pos - target_pos;
	return dist.Length() < 10;
}

void ShooterAfro::SetPos( Vec2D p )
{
	pos = p;
	weapon->SetPos( pos );
}
	
void ShooterAfro::Update( float dt )
{
	if( shoot_time.GetTime() * stats_mod > delay ) {
		Shoot();
		ResetShootDelay();
	}
	
	const Vec2D desired = target_pos - pos;
	acc = desired - vel;
	
	acc.TruncateLength( max_acc * stats_mod );
	
	const Vec2D new_vel = vel + acc * dt;
	vel = new_vel;
	vel.TruncateLength( max_vel * stats_mod );
	
	const Vec2D new_pos = pos + new_vel * dt;

	SetPos( new_pos );
}
void ShooterAfro::Render()
{
	spr->Render( (int)pos.x + (int)shake_x_offset, (int)pos.y + (int)shake_y_offset );
	
	RenderDebug();
}

void ShooterAfro::Shoot()
{
	const float target_x = pos.x + hge->Random_Float( -80, 80 ); 
	boost::shared_ptr<Bullet> bullet = weapon->Shoot( Vec2D( target_x, 600 ) );
	if( bullet ) {
		world->PushBullet( bullet );
	}
}

void ShooterAfro::ResetShootDelay()
{
	delay = delay_bag.Get();
	shoot_time.Restart();
}
