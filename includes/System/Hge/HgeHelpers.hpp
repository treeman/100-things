#ifndef HGEHELPERS_HPP_INCLUDED
#define HGEHELPERS_HPP_INCLUDED

#include "HgeIncl.hpp"
#include "..\Vec2D.hpp"

namespace hgeh {
	
	void render_rect( HGE *hge, float x1, float y1, float x2, float y2, DWORD color );
	
	void render_circle( HGE *hge, const Vec2D center, float radius, int segments, DWORD color );
	void render_circle_slice( HGE *hge, const Vec2D center, float radius, int segments, float begin, float end, DWORD color );
	
	void render_solid_circle( HGE *hge, const Vec2D center, float radius, int segments, DWORD color );
	void render_solid_circle_slice( HGE *hge, const Vec2D center, float radius, int segments, float begin, float end, DWORD color );
}

#endif
