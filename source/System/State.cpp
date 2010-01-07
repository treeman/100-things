#include "includes/System/State.hpp"
#include "includes/System/ErrorHandling.hpp"
#include "includes/System/Log.hpp"
#include "includes/System/Settings.hpp"

StateHandler::StateHandler() : exit_called( false )
{
	
}

StateHandler::~StateHandler()
{
	
}

void StateHandler::Pop()
{
	state_list.pop_front();
}

void StateHandler::Push( boost::shared_ptr<GameState> p )
{
	state_list.push_front( p );
}
boost::shared_ptr<GameState> StateHandler::Top()
{
	if( !state_list.empty() ) {
		return state_list.front();
	}
	else {
		boost::shared_ptr<GameState> p;
		return p;
	}
}
boost::shared_ptr<GameState> StateHandler::Seek( std::string id )
{
	for( StateList::iterator it = state_list.begin(); it != state_list.end(); ++it )
	{
		if( (*it)->StateId() == id ) {
			return *it;
		}
	}
	boost::shared_ptr<GameState> p;
	return p;
}

void StateHandler::Exit()
{
	exit_called = true;
	Log::Get().Write( "engine", "Exit called!" );
}
bool StateHandler::ShallExit() const
{
	return state_list.empty() || exit_called;
}

int StateHandler::GetWindowWidth()
{
	std::string s = Settings::Get().GetValue( "video_screen_width" );
	return boost::lexical_cast<int>( s );
}
int StateHandler::GetWindowHeight()
{
	std::string s = Settings::Get().GetValue( "video_screen_height" );
	return boost::lexical_cast<int>( s );
}
