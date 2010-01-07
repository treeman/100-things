#include "includes/Menu.hpp"
#include "includes/System/Settings.hpp"

Menu::Menu() : asia30( new hgeFont( "fnt/asiaextended30.fnt" ) )
{
	input_priority = 100;
	
	is_active = false;
	
	int w = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_width" ) );
	int h = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_height" ) );	
	shade.reset( new hgeSprite( 0, 0, 0, w, h ) );
}
	
void Menu::Enter()
{
	is_active = true;
}
void Menu::Leave()
{
	is_active = false;
}

bool Menu::HandleEvent( hgeInputEvent &event )
{
	if( !IsActive() ) return true;
	
	return false;
}

bool Menu::IsActive()
{
	return is_active;
}

void Menu::Update( float dt )
{
	if( !IsActive() ) return;
}
void Menu::Render()
{
	if( !IsActive() ) return;
	
	shade->SetColor( 0x77000000 );
	shade->Render( 0, 0 );
	
	const float text_left = 50;
	const float text_top = 385;
	const float line_height = asia30->GetHeight() + 3;
	
	asia30->Render( text_left, text_top, HGETEXT_LEFT, "New Game" );
	asia30->Render( text_left, text_top + line_height, HGETEXT_LEFT, "Save Game" );
	asia30->Render( text_left, text_top + 2 * line_height, HGETEXT_LEFT, "Load Game" );
	asia30->Render( text_left, text_top + 3 * line_height, HGETEXT_LEFT, "Credits" );
	asia30->Render( text_left, text_top + 4 * line_height, HGETEXT_LEFT, "Exit" );
}
