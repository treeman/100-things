#include "includes/GameWorld.hpp"

GameWorld::GameWorld( StateHandler * const _state_handler ) : 
	GameState(_state_handler), state_handler(_state_handler), input_chain( new InputChain() ), 
	world( new World() ), controller( new Controller( world->GetDude() ) ), gui( new Gui() ), tracks( new Tracks() )
{
	input_chain->AddHandler( controller.get() );
	input_chain->AddHandler( gui.get() );
	
	world->AddListener( gui->GetListener() );
	
	tracks->Play();
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
	
	return input_chain->HandleEvent( event );
}
	
void GameWorld::Update( float dt )
{
	controller->Update( dt );
	world->Update( dt );
	gui->Update( dt );
	tracks->Update( dt );
}
void GameWorld::Render()
{
	world->Render();
	gui->Render();
}
