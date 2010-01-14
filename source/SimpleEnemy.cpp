#include "includes/SimpleEnemy.hpp"

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
	
	acc.TruncateLength( max_acc );
	
	const Vec2D new_vel = vel + acc * dt;
	vel = new_vel;
	vel.TruncateLength( max_vel );
	
	const Vec2D new_pos = pos + new_vel * dt;

	pos = new_pos;
}
void PippiAfro::Render()
{
	spr->Render( (int)pos.x, (int)pos.y );
	
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
	
	acc.SetLength( max_acc );
	
	const Vec2D new_vel = vel + acc * dt;
	vel = new_vel;
	vel.SetLength( max_vel );
	
	const Vec2D new_pos = pos + new_vel * dt;

	pos = new_pos;
}
void MutantAfro::Render()
{
	spr->Render( (int)pos.x, (int)pos.y );
	
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
	acc.SetLength( max_acc );
	
	const Vec2D new_vel = vel + acc * dt;
	vel = new_vel;
	vel.TruncateLength( max_vel );
	
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
	spr->Render( (int)pos.x, (int)pos.y + 4 );
	
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
