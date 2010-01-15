#ifndef GAMEWORLD_HPP_INCLUDED
#define GAMEWORLD_HPP_INCLUDED

#include "System/Hge.hpp"
#include "System/State.hpp"

#include "World.hpp"
#include "Controller.hpp"
#include "Gui.hpp"
#include "Tracks.hpp"

class GameWorld : public GameState {
public:
	GameWorld( StateHandler * const state_handler );
	~GameWorld();
	
	bool HandleEvent( hgeInputEvent &e );
	
	void Update( float dt );
	void Render();
    
    std::string StateId() {
		return "GameWorld";
	}
private:
	StateHandler * const state_handler;
	
	boost::shared_ptr<InputChain> input_chain;
	
	boost::shared_ptr<World> world;
	boost::shared_ptr<Controller> controller;
	
	boost::shared_ptr<Gui> gui;
	boost::shared_ptr<Tracks> tracks;
	
	HgeObj hge;
};

#endif
