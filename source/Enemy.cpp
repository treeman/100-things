#include "includes/Enemy.hpp"

const float w = 26;
const float h = 20;

Enemy::Enemy( Vec2D _pos ) : acc( 0,0 ), vel( 0,0 ), pos( _pos ), target_pos( _pos ), can_kill( false ),
	fnt( new hgeFont( "fnt/arial10.fnt" ) )
{
	show_debug = false;
	showDebug.reset( new Dator<bool>( show_debug ) );
	Settings::Get().RegisterVariable( "enemies_debug", boost::weak_ptr<BaseDator>( showDebug ) );
	
	stats_mod = 1.0;
}

Shape::Rect Enemy::Bounds()
{
	return Shape::Rect( pos.x, pos.y, w, h );
}

void Enemy::RenderDebug()
{
	if( show_debug ) {
		fnt->SetColor( 0xff000000 );
		fnt->printf( (int)pos.x, (int)(pos.y - Bounds().h - 5), HGETEXT_LEFT, "p: %.0f,%.0f, tp: %.0f,%.0f v:  %.0f,%.0f", 
			pos.x, pos.y, target_pos.x, target_pos.y, vel.x, vel.y );
	}
}
