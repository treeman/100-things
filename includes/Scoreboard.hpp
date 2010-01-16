#ifndef SCOREBOARD_HPP_INCLUDED
#define SCOREBOARD_HPP_INCLUDED

#include <fstream>
#include <iostream>

#include "System/State.hpp"
#include "System/Timer.hpp"
#include "System/Hge.hpp"

struct Score {
	float time;
	int kills;
};

class Scoreboard : public GameState {
public:
	Scoreboard( StateHandler *const _state_handler );
	~Scoreboard();
	
	void NewScore( float time, int kills );
	
	bool HandleEvent( hgeInputEvent &e );
	
	void Update( float dt );
	void Render();
	
	std::string StateId() {
		return "Scoreboard";
	}
private:
	void ParseScoreLine( std::string line );

	Timer t;
	
	StateHandler *const state_handler;
	
	boost::shared_ptr<hgeFont> fnt;
	
	typedef std::vector<Score> Scores;
	Scores scores;
};

#endif
