#ifndef GROUND_HPP_INCLUDED
#define GROUND_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"
#include "System/Shape.hpp"

#include "Shakeable.hpp"

class Ground : public Shakeable {
public:
	Ground( float _x, float _y, float _w, float _h );
	
	Shape::Rect Bounds() const {
		return Shape::Rect( x, y, w, h );
	}
	
	void Render();
private:
	boost::shared_ptr<hgeSprite> spr;
	float x, y;
	float w, h;
};

#endif
