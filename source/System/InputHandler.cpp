#include "includes/System/InputHandler.hpp"

InputChain::InputChain() { }
	
bool InputChain::HandleEvent( hgeInputEvent &event )
{
	for( HandlerList::iterator it = handler_list.begin(); it != handler_list.end(); ++it ) {
		if( !(*it)->HandleEvent( event ) ) {
			return false;
		}
	}
	return true;
}

void InputChain::AddHandler( InputHandler *handler )
{
	HandlerList::iterator it;
	for( it = handler_list.begin(); it != handler_list.end(); ++it ) {
		if( (*it)->GetPriority() > handler->GetPriority() ) {
			break;
		}
	}
	handler_list.insert( it, handler );
}
void InputChain::RemoveHandler( InputHandler *handler )
{
	handler_list.remove( handler );
}
