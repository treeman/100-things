#ifndef MOUSE_HPP_INCLUDED
#define MOUSE_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"
#include "System/InputHandler.hpp"
#include "System/Vec2D.hpp"

class Mouse : public InputHandler {
public:
	Mouse();
	
	bool HandleEvent( hgeInputEvent &e );
	
	void Render();
	void HoverOver( bool b );
private:
	Vec2D pos;
	
	TexObj tex;
	boost::shared_ptr<hgeSprite> normal;
	
	bool is_over;
	bool in_click;
};

#endif
