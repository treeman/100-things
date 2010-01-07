#include "includes/System/Shape.hpp"

bool Shape::Rect::IsOver( const float _x, const float _y ) const
{
	if( _x < x )
		return false;
	else if( _x > x + w )
		return false;
		
	if( _y < y )
		return false;
	else if( _y > y + h )
		return false;
		
	return true;
}

bool Shape::Rect::Overlap( const Rect &r ) const
{
	if( x + w < r.x )
		return false;
	else if( x > r.x + r.w )
		return false;
		
	if( y + h < r.y )
		return false;
	else if( y > r.y + r.h )
		return false;

	return true;
}
bool Shape::Rect::Collision( const Rect &r ) const
{
	if( x + w <= r.x )
		return false;
	else if( x >= r.x + r.w )
		return false;
		
	if( y + h <= r.y )
		return false;
	else if( y >= r.y + r.h )
		return false;

	return true;
}
