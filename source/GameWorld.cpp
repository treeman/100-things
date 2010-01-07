#include "includes/GameWorld.hpp"

GameWorld::GameWorld( StateHandler * const _state_handler ) : 
	GameState(_state_handler), state_handler(_state_handler), input_chain( new InputChain() ), 
	world( new World() ), controller( new Controller( world->GetDude() ) ), mouse( new Mouse() )
{
	input_chain->AddHandler( controller.get() );
	input_chain->AddHandler( mouse.get() );
}
GameWorld::~GameWorld()
{
	
}

bool GameWorld::HandleEvent( hgeInputEvent &event )
{
	if( event.type == INPUT_KEYDOWN ) {
		switch( event.key ) {
			case HGEK_F10: state_handler->Exit(); break;
		}
	}
	
	input_chain->HandleEvent( event );
	return true;
}
	
void GameWorld::Update( float dt )
{
	controller->Update( dt );
	world->Update( dt );
}
void GameWorld::Render()
{
	world->Render();
	mouse->Render();
}
