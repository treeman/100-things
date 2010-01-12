#include "includes/Enemy.hpp"

const float w = 26;
const float h = 20;

Enemy::Enemy( Vec2D _pos ) : acc( 0,0 ), vel( 0,0 ), pos( _pos ), target_pos( _pos ), can_kill( false ),
	max_acc( 2000 ), max_vel( 200 )
{
	tex.Load( "gfx/flyingafro.png" );
	spr.reset( new hgeSprite( tex, 0, 0, w, h ) );
}

Shape::Rect Enemy::Bounds()
{
	return Shape::Rect( pos.x, pos.y, w, h );
}

void Enemy::SetTargetPos( Vec2D target )
{
	const Vec2D desired = target - pos;
	acc = desired - vel;
	target_pos = target;
}
	
void Enemy::Update( float dt )
{
	acc.TruncateLength( max_acc );
	
	const Vec2D new_vel = vel + acc * dt;
	vel = new_vel;
	vel.TruncateLength( max_vel );
	
	const Vec2D new_pos = pos + new_vel * dt;

	pos = new_pos;
	
	const Vec2D dist = pos - target_pos;
	if( dist.Length() < 3 ) {
		SetTargetPos( Vec2D( hge->Random_Float( 0, 800 ), hge->Random_Float( 0, 500 ) ) );
	}
}
void Enemy::Render()
{
	spr->Render( pos.x, pos.y );
}
