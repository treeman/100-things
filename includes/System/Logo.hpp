#ifndef LOGO_HPP_INCLUDED
#define LOGO_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "State.hpp"
#include "Hge.hpp"
#include "Timer.hpp"

class Logo : public GameState {
public:
	Logo( StateHandler *const _state_handler );
	~Logo();
	
	bool HandleEvent( hgeInputEvent &e );
	
	void Update( float dt );
	void Render();
	
	std::string StateId() {
		return "Logo";
	}
private:
	Timer t;
	
	HTEXTURE logo_tex;
	boost::shared_ptr<hgeSprite> logo;
	float x, y;
	
	boost::shared_ptr<hgeSprite> fade;
	int fade_dir;
	DWORD fade_color;
	
	StateHandler *const state_handler;
	
	HgeObj hge;
};

#endif
