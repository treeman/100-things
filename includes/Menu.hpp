#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/InputHandler.hpp"
#include "System/Hge.hpp"

class Menu : public InputHandler {
public:
	Menu();
	
	void Enter();
	void Leave();
	
	bool HandleEvent( hgeInputEvent &event );
	
	bool IsActive();
	
	void Update( float dt );
	void Render();
private:
	HgeObj hge;
	
	boost::shared_ptr<hgeFont> asia30;
	
	bool is_active;
	
	boost::shared_ptr<hgeSprite> shade;
};

#endif
