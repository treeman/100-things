#include "includes/Enemy.hpp"

const float w = 26;
const float h = 20;

Enemy::Enemy( Vec2D _pos ) : pos( _pos ), can_kill( false )
{
	tex.Load( "gfx/flyingafro.png" );
	spr.reset( new hgeSprite( tex, 0, 0, w, h ) );
}

Shape::Rect Enemy::Bounds()
{
	return Shape::Rect( pos.x, pos.y, w, h );
}
	
void Enemy::Update( float dt )
{
	
}
void Enemy::Render()
{
	spr->Render( pos.x, pos.y );
}
