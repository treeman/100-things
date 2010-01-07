#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

#include <cmath>
#include <cstdlib>
#include <cfloat>

namespace math 
{
	static const float PI = 3.14159265358979323846f;
	static const float PI_2 = 1.57079632679489661923f;
	static const float PI_4 = 0.785398163397448309616f;
	static const float PI2 = 6.28318530717958647692f;
	static const float PI_SQR = 9.8696044010893586188344f;
	static const float INVPI = 0.318309886183790671538f;
	static const float INV2PI = 0.636619772367581343076f;
	
	template<class T> T interpolate( float dt, const T &x0, const T &x1 )
	{
		return x0 + ( (x1 - x0) * dt );
	}
	// 0 > x > 1
	inline const float frandom() {
		return (float)rand() / (float)RAND_MAX;
	}
	inline const float frandom( const float min, const float max ) {
		return min + ( frandom() * ( max - min ) );
	}
	
	template<typename T>
	inline const T clip( const T &x, const T &min, const T &max ) {
		if( x < min ) return min;
		if( x > max ) return max;
		return x;
	}
	
	inline const float random_speed( const float curr, const float walkspeed,
		const float min, const float max )
	{
		const float new_speed = curr + frandom( -1, 1 ) * walkspeed;
		if( new_speed < min ) return min;
		if( new_speed > max ) return max;
		return new_speed;
	}
	
	inline const int intervel_comparison( const float x, const float lower, 
		const float upper ) 
	{
		if( x < lower ) return -1;
		if( x > upper ) return 1;
		return 0;
	}
}

namespace fastmath 
{	
	//carmack's quake qsort using newton rhapsons
	//with evil bit level hacking
	inline const float isqrt( const float num )
	{
		const float x2 = num * 0.5F;
		float y = num;
		long i  = * ( long * ) &y;
		i  = 0x5f3759df - ( i >> 1 );
		y  = * ( float * ) &i;
		y  = y * ( 1.5F - ( x2 * y * y ) );
		y  = y * ( 1.5F - ( x2 * y * y ) );
		return y;
	}
	inline const float sqrt( const float num ) 
	{
		return num * isqrt( num );
	}
	
	// sin approximation from
	// http://www.devmaster.net/forums/showthread.php?t=5784
	// uses parabola approx with weighted average
	// very fast with very good precision
	inline const float sin( const float num )
	{
		static const float A = math::INV2PI * 2;
		static const float B = -4 * math::INVPI * math::INVPI;
		
		float x = A * num + B * num * std::abs( num );
		
		static const float P = 0.225;
		
		return P * ( x * std::abs(x) - x ) + x;
	}
	//only valid for -PI >= num => PI
	inline const float cos( const float num )
	{
		return sin( num + math::PI_2 );
	}
	inline const float tan( const float num )
	{
		const float cos_d = cos( num );
		if( !cos_d ) return FLT_MAX;
		return sin( num ) / cos_d;
	}
}

#endif
