#ifndef GAMEDEBUG_HPP_INCLUDED
#define GAMEDEBUG_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "Hge.hpp"
#include "Settings.hpp"

class GameDebug {
public:
	GameDebug();
	
	void Update( float dt );
	void Render();
private:
	HgeObj hge;
	
	bool show_mouse_pos;
	boost::shared_ptr<Dator<bool> > showMousePos;
	
	bool show_fps;
	boost::shared_ptr<Dator<bool> > showFPS;
	
	boost::shared_ptr<hgeFont> arial10;
	boost::shared_ptr<hgeFont> visitor20;
};

#endif
