#include <vector>

#include "includes/System/Hge.hpp"

void hgeh::render_rect( HGE *hge, float x1, float y1, float x2, float y2, DWORD color )
{
	hge->Gfx_RenderLine( x1, y1, x2, y1, color );
	hge->Gfx_RenderLine( x2, y1, x2, y2, color );
	hge->Gfx_RenderLine( x2, y2, x1, y2, color );
	hge->Gfx_RenderLine( x1, y2, x1, y1, color );
}

void hgeh::render_circle( HGE *hge, const Vec2D center, float radius, int segments, DWORD color )
{
	const float increment = math::PI2 / segments;
	float theta = 0.0f;
	
	typedef std::vector<Vec2D> Positions;
	Positions positions;
	for( int i = 0; i < segments; ++i )
	{
		Vec2D p = Vec2D( std::cos( theta ), std::sin( theta ) );
		p *= radius;
		p += center;
		positions.push_back( p );
		theta += increment;
	}
	
	for( Positions::iterator it = positions.begin(); it != positions.end(); )
	{
		Vec2D p1 = *it;
		++it;
		Vec2D p2;
		if( it != positions.end() ) {
			p2 = *it;
		}
		else {
			p2 = *positions.begin();
		}
		hge->Gfx_RenderLine( p1.x, p1.y, p2.x, p2.y, color );
	}
}



void hgeh::render_circle_slice( HGE *hge, const Vec2D center, float radius, int segments, float begin, float end, DWORD color )
{
	const float increment = ( end - begin ) / segments;
	float theta = begin;
	
	typedef std::vector<Vec2D> Positions;
	Positions positions;
	for( int i = 0; i < segments; ++i )
	{
		Vec2D p = Vec2D( std::cos( theta ), std::sin( theta ) );
		p *= radius;
		p += center;
		positions.push_back( p );
		theta += increment;
	}
	
	for( Positions::iterator it = positions.begin(); it != positions.end(); )
	{
		Vec2D p1 = *it;
		++it;
		Vec2D p2;
		if( it != positions.end() ) {
			p2 = *it;
		}
		else {
			break;
		}
		hge->Gfx_RenderLine( p1.x, p1.y, p2.x, p2.y, color );
	}
}

void hgeh::render_solid_circle( HGE *hge, const Vec2D center, float radius, int segments, DWORD color )
{
	render_solid_circle_slice( hge, center, radius, segments, 0.0f, math::PI2, color );
}

void hgeh::render_solid_circle_slice( HGE *hge, const Vec2D center, float radius, int segments, float begin, float end, DWORD color )
{
	const float increment = ( end - begin ) / segments;
	float theta = begin;
	
	typedef std::vector<Vec2D> Positions;
	Positions positions;
	for( int i = 0; i < segments; ++i )
	{
		Vec2D p = Vec2D( std::cos( theta ), std::sin( theta ) );
		p *= radius;
		p += center;
		positions.push_back( p );
		theta += increment;
	}
	
	for( Positions::iterator it = positions.begin(); it != positions.end(); )
	{
		Vec2D p1 = *it;
		++it;
		Vec2D p2;
		if( it != positions.end() ) {
			p2 = *it;
		}
		else {
			p2 = *positions.begin();
		}
		
		hgeTriple t;
		t.blend = BLEND_DEFAULT;
		t.tex = 0;
		
		hgeVertex v;
		v.col = color;
		v.tx = 0.0;
		v.ty = 0.0;
		
		v.x = center.x;
		v.y = center.y;
		t.v[0] = v;
		
		v.x = p1.x;
		v.y = p1.y;
		t.v[1] = v;
		
		v.x = p2.x;
		v.y = p2.y;
		t.v[2] = v;
		
		hge->Gfx_RenderTriple( &t );
	}
}
