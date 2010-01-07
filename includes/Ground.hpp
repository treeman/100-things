#ifndef GROUND_HPP_INCLUDED
#define GROUND_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"

class Ground {
public:
	Ground( float _x, float _y, float _w, float _h ) : x(_x), y(_y), w(_w), h(_h)
	{
		spr.reset( new hgeSprite( 0, 0, 0, w, h ) );
		spr->SetColor( 0xff000000 );
	}
	
	Shape::Rect Bounds() const {
		return Shape::Rect( x, y, w, h );
	}
	
	void Render() {
		spr->Render( x, y );
	}
private:
	boost::shared_ptr<hgeSprite> spr;
	float x, y;
	float w, h;
};

#endif
