#ifndef INPUTHANDLER_HPP_INCLUDED
#define INPUTHANDLER_HPP_INCLUDED

#include <list>

#include "Hge.hpp"

class InputHandler {
public:
	InputHandler() : input_priority( 1337 ) { }
	virtual ~InputHandler() { }
	
	//return true if event is allowed to be passed to the next handler
	virtual bool HandleEvent( hgeInputEvent& ) = 0;
	
	int GetPriority() {
		return input_priority;
	}
protected:
	int input_priority;
};

class InputChain {
public:
	InputChain();
	
	bool HandleEvent( hgeInputEvent &event );
	
	void AddHandler( InputHandler *handler );
	void RemoveHandler( InputHandler *handler );
private:
	typedef std::list<InputHandler*> HandlerList;
	HandlerList handler_list;
};

#endif
