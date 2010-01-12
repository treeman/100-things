#include "includes/Enemy.hpp"

const float w = 26;
const float h = 20;

Enemy::Enemy( Vec2D _pos ) : acc( 0,0 ), vel( 0,0 ), pos( _pos ), target_pos( _pos ), can_kill( false ),
	max_acc( 2000 ), max_vel( 200 ), fnt( new hgeFont( "fnt/arial10.fnt" ) )
{
	tex.Load( "gfx/flyingafro.png" );
	spr.reset( new hgeSprite( tex, 0, 0, w, h ) );
	
	show_debug = false;
	showDebug.reset( new Dator<bool>( show_debug ) );
	Settings::Get().RegisterVariable( "enemies_debug", boost::weak_ptr<BaseDator>( showDebug ) );
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

bool Enemy::HasReachedGoal()
{
	const Vec2D dist = pos - target_pos;
	return dist.Length() < 10;
}
	
void Enemy::Update( float dt )
{
	SetTargetPos( target_pos );
	
	acc.TruncateLength( max_acc );
	
	const Vec2D new_vel = vel + acc * dt;
	vel = new_vel;
	vel.TruncateLength( max_vel );
	
	const Vec2D new_pos = pos + new_vel * dt;

	pos = new_pos;
}
void Enemy::Render()
{
	if( show_debug ) {
		fnt->SetColor( 0xff000000 );
		fnt->printf( (int)pos.x, (int)(pos.y - Bounds().h - 5), HGETEXT_LEFT, "p: %.0f,%.0f, tp: %.0f,%.0f v:  %.0f,%.0f", 
			pos.x, pos.y, target_pos.x, target_pos.y, vel.x, vel.y );
	}
	spr->Render( (int)pos.x, (int)pos.y );
}
