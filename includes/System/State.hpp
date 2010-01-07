#ifndef STATES_HPP_INCLUDED
#define STATES_HPP_INCLUDED

#include <vector>
#include <list>
#include <map>
#include <string>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "Singleton.hpp"
#include "Log.hpp"
#include "InputHandler.hpp"

class StateHandler;

class GameState : public InputHandler {
public:
	GameState( StateHandler * const state_handler ) { }
	virtual ~GameState() { }

    virtual void Update( float dt ) = 0;
    virtual void Render() = 0;
    
    virtual std::string StateId() = 0;
};

//internally within statehandler
//use for general storage of templated functor
class BasicStateFunctor {
public:
	virtual GameState *operator()( StateHandler * const state_handler ) = 0;
};

//internally within statehandler
//use for getting a dynamically allocated class
template<class T>
class StateFunctor : public BasicStateFunctor {
public:
	StateFunctor() { }
	GameState *operator ()( StateHandler * const state_handler ) {
		return new T( state_handler );
	}
	typedef T type;
};

class StateHandler {
public:
	StateHandler();
	~StateHandler();

	void Pop();
	void Push( boost::shared_ptr<GameState> p );
	boost::shared_ptr<GameState> Top();
	boost::shared_ptr<GameState> Seek( std::string id );
	
	void Exit();
	bool ShallExit() const;
	
	int GetWindowWidth();
	int GetWindowHeight();
private:
	typedef std::list<boost::shared_ptr<GameState> > StateList;
	StateList state_list;
	
	bool exit_called;
	
	StateHandler( const StateHandler &state );
	StateHandler &operator = ( const StateHandler &state );
};

#endif
