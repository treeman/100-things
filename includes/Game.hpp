#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <vector>
#include <boost/shared_ptr.hpp>

#include "System/Log.hpp"
#include "System/State.hpp"
#include "System/WindowManager.hpp"
#include "System/SoundManager.hpp"
#include "System/Hge.hpp"
#include "System/Settings.hpp"
#include "System/Console.hpp"
#include "System/GameDebug.hpp"

#include "System/Logo.hpp"

class Game {
public:
	Game( int argc, char *argv[] );
	~Game();
	
	bool Logic();
	bool Render();
	
	//initiate stuff after hge->Sytem_Initiate
	//ex hge resources: textures, streams etc
	void Init();
private:
	boost::shared_ptr<WindowManager> window_manager;
	boost::shared_ptr<SoundManager> sound_manager;
	
	boost::shared_ptr<StateHandler> state_handler;
	
	boost::shared_ptr<Console> console;
	boost::shared_ptr<GameDebug> game_debug;
	
	boost::shared_ptr<GameState> curr_state;
	
	HgeObj hge;
};

#endif
