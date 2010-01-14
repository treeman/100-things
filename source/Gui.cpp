#include "includes/Gui.hpp"

Gui::Gui() : input_chain( new InputChain() ), mouse( new Mouse() ), infobar( new Infobar() )
{
	input_chain->AddHandler( mouse.get() );
}
	
bool Gui::HandleEvent( hgeInputEvent &e )
{
	return input_chain->HandleEvent( e );
}

WorldListener *const Gui::GetListener()
{
	return infobar.get();
}

void Gui::Update( float dt )
{
	
}
void Gui::Render()
{
	mouse->Render();
	infobar->Render();
}
