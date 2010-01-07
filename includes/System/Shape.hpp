#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

#include "Math.hpp"
#include "Vec2D.hpp"

namespace Shape 
{
	class Rect {
	public:
		Rect() : x(0), y(0), w(0), h(0) { }
		Rect( const float _x, const float _y, const float _w, const float _h ) : x(_x), y(_y), w(_w), h(_h) { }
		
		void Encapsulate( const Vec2D &pos ) {
			Encapsulate( pos.x, pos.y );
		}
		void Encapsulate( const float _x, const float _y ) {
			x = _x; y = _y;
			w = h = 0;
		}
		
		bool IsOver( const Vec2D &_pos ) const {
			return IsOver( x, y );
		}
		bool IsOver( const float x, const float y ) const;
		
		bool Overlap( const Rect &r ) const;
		bool Collision( const Rect &r ) const;

		float x, y;
		float w, h;
	};
	
}

#endif
