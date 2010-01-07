#ifndef CONTROLLER_HPP_INCLUDED
#define CONTROLLER_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/InputHandler.hpp"

class Dude;

class Controller : public InputHandler {
public:
	Controller( boost::shared_ptr<Dude> dude );
	
	bool HandleEvent( hgeInputEvent &e );
	
	void Update( float dt );
private:
	boost::shared_ptr<Dude> dude;
	HgeObj hge;
};

#endif
