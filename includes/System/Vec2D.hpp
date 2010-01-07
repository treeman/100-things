#ifndef VEC2D_HPP_INCLUDED
#define VEC2D_HPP_INCLUDED

#include <cmath>
#include <ostream>

#include "Math.hpp"

class Vec2D {
public:
	Vec2D() : x(0), y(0) { }
	Vec2D( const float _x, const float _y ) : x(_x), y(_y) { }
	Vec2D( const Vec2D &v ) {
		x = v.x; y = v.y;
	}
	Vec2D &operator = ( const Vec2D &v ) {
		if( this != &v ) {
			x = v.x; y = v.y;
		}
		return *this;
	}
	
	Vec2D operator - () const {
		return Vec2D( -x, -y );
	}
	
	Vec2D operator + ( const Vec2D &v ) const {
		return Vec2D( x + v.x, y + v.y );
	}	
	Vec2D operator - ( const Vec2D &v ) const {
		return Vec2D( x - v.x, y - v.y );
	}
	Vec2D &operator += ( const Vec2D &v ) {
		x += v.x; y += v.y;
		return *this;
	}
	Vec2D &operator -= ( const Vec2D &v ) {
		x -= v.x; y -= v.y;
		return *this;
	}
	
	Vec2D operator + ( const float f ) const {
		Vec2D v( x, y ); v += f;
		return v;	
	}
	
	Vec2D operator - ( const float f ) const {
		Vec2D v( x, y ); v -= f;
		return v;	
	}
	
	Vec2D operator * ( const float f ) const {
		if( !f || !x && !y ) return Vec2D( 0, 0 );

		Vec2D v( x, y ); v *= f;
		return v;	
	}
	
	Vec2D operator / ( const float f ) const {
		if( !f ) return Vec2D( x, y );
		if( !x && !y ) return Vec2D( 0, 0 );

		Vec2D v( x, y ); v /= f;
		return v;	
	}
	
	Vec2D &operator += ( const float f ) {
		if( !x && !y ) {
			x = f; y = 0;
		}
		else {
			const float l = Length();
			x = ( l + f ) * x / l;
			y = ( l + f ) * y / l;
		}
		return *this;
	}
	Vec2D &operator -= ( const float f ) {
		if( !x && !y ) {
			x = y = 0;
		}
		else {
			const float l = Length();
			x = ( l - f ) * x / l;
			y = ( l - f ) * y / l;
		}
		return *this;
	}
	
	Vec2D &operator *= ( const float f ) {
		if( !f ) {
			x = y = 0;
		}
		else {
			const float l = Length();
			const float nx = ( l * f ) * x / l;
			const float ny = ( l * f ) * y / l;
			
			x = nx; y = ny;
		}
		return *this;
	}
	Vec2D &operator /= ( const float f ) {
		if( f ) {
			const float l = Length();
			const float nx = ( l / f ) * x / l;
			const float ny = ( l / f ) * y / l;
			
			x = nx; y = ny;
		}
		return *this;
	}
	
	Vec2D &operator = ( const float f ) {
		SetLength( f );
		return *this;
	}
	
	void operator() ( const float f ) {
		SetLength( f );
	}
	
	void operator () ( const float _x, const float _y ) {
		x = _x; y = _y;
	}
	
	void SetLength( const float f ) {
		if( !f ) {
			x = 0; y = 0;
		}
		else if( x || y ) {
			const float l = Length();
			x = f * x / l;
			y = f * y / l;
		}
	}
	
	//calculate the dot product
	float Dot( const Vec2D &v ) const {
		return x * v.x + y *v.y;
	}
	float Length() const {
		if( !x && !y ) return 0;
		return fastmath::sqrt( x * x + y * y );
	}
	float SqLength() const {
		return x * x + y * y;
	}
	void TruncateLength( const float max ) {
		if( Length() > max )
			SetLength( max );
	}
	
	static float Distance( const Vec2D &v1, const Vec2D &v2 ) {
		const float a = v1.x - v2.x;
		const float b = v1.y - v2.y;
		return fastmath::sqrt( a*a + b*b );
	}
	
	static float SqDistance( const Vec2D &v1, const Vec2D &v2 ) {
		const float a = v1.x - v2.x;
		const float b = v1.y - v2.y;
		return a*a + b*b;
	}
	float Angle() const {
		if( !x ) return math::PI_2;
		if( !y ) return 0;
		
		const float val = std::atan( y / x );
		
		if( x > 0 ) {
			return val;
		}
		else if( y > 0 ) {
			return math::PI + val;
		}
		else { //if( y < 0 )
			return -(math::PI - val);
		}
	}
	static float Angle( const Vec2D &v1, const Vec2D &v2 ) {
		const Vec2D v3 = v1.GetNormalized();
		const Vec2D v4 = v2.GetNormalized();
		const float dot = v3.Dot( v4 );

		return std::acos( dot );
	}
	static float RelAngle( const Vec2D &v1, const Vec2D &v2 ) {
		const float a1 = v1.Angle();
		const float a2 = v2.Angle();
		float rel = a1 - a2;
		
		//fix for round-the-clock consistency
		//cw - positive ccw - negative 
		//and clamp values down to -PI > x > PI
		if( a2 < -math::PI_2 && a1 > 0 && rel > math::PI ) {
			rel = -(math::PI2 - rel);
		} 
		else if( rel > math::PI ) {
			rel = math::PI2 - rel;
		}
		else if( rel < -math::PI ) {
			rel = rel + math::PI2;
		}
		
		return rel;
	}
	void SetAngle( const float r ) {
		const float sin_d = fastmath::sin( r );
		const float cos_d = fastmath::cos( r );
		const float l = Length();
		
		x = cos_d * l;
		y = sin_d * l;
	}
	//return unit vector: length == 1
	Vec2D &Normalize() {
		if( !x && !y ) {
			x = 1; y = 0;
		}
		else {
			const float il = fastmath::isqrt( SqLength() );
			x *= il;
			y *= il;
		}
		return *this;
	}
	
	Vec2D GetNormalized() const {
		Vec2D v( x, y );
		v.Normalize();
		return v;
	}
	
	bool operator == ( const Vec2D &v ) const {
		return x == v.x && y == v.y;
	}
	bool operator != ( const Vec2D &v ) const {
		return !(*this == v);
	}
	
	float x, y;
	
	//names for common vectors
	static const Vec2D zero;
	static const Vec2D right;
	static const Vec2D left;
	static const Vec2D up;
	static const Vec2D down;
};

inline Vec2D operator * ( const float f, const Vec2D v ) {
	return f * v;
}

inline std::ostream &operator << ( std::ostream &o, const Vec2D &v ) {
	return o << "(" << v.x << "," << v.y << ")";
}

#endif
