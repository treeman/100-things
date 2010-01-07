#include "includes/Controller.hpp"
#include "includes/Dude.hpp"

Controller::Controller( boost::shared_ptr<Dude> _dude ) : dude( _dude )
{
	
}

bool Controller::HandleEvent( hgeInputEvent &e )
{
	if( e.type == INPUT_MBUTTONDOWN && e.key == HGEK_LBUTTON ) {
		dude->Shoot( Vec2D( e.x, e.y ) );
	}
	if( e.type == INPUT_KEYDOWN ) {
		switch( e.key ) {
			case HGEK_SPACE:
				dude->Jump();
				break;
		}
	}
	
	return true;
}

void Controller::Update( float dt )
{
	if( hge->Input_GetKeyState( HGEK_A ) ) {
		dude->MoveLeft();
	}
	if( hge->Input_GetKeyState( HGEK_D ) ) {
		dude->MoveRight();
	}
	if( hge->Input_GetKeyState( HGEK_CTRL ) ) {
		dude->Duck();
	}
}
