#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/InputHandler.hpp"
#include "Mouse.hpp"
#include "WorldListener.hpp"

class Gui : public InputHandler, public WorldListener {
public:
	Gui();
	
	bool HandleEvent( hgeInputEvent &e );
	
	WorldListener *const GetListener();
	
	void Update( float dt );
	void Render();
private:
	boost::shared_ptr<InputChain> input_chain;
	
	boost::shared_ptr<Mouse> mouse;
};

#endif
