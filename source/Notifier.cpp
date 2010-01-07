#include <boost/foreach.hpp>

#include "includes/Notifier.hpp"

bool can_kill( Message m )
{
	return m.can_kill;
}

Message::Message( std::string s ) : str( s ), time_alive( 0 ), alpha( 255 ), can_kill( false )
{ }

Notifier::Notifier() : fnt( new hgeFont( "fnt/bannerlight14.fnt" ) ), fade_time( 2 ), pause_before_fade( 2 )
{
	
}
	
void Notifier::Add( std::string str )
{
	messages.push_back( str );
}

void Notifier::Update( float dt )
{
	for( Messages::iterator it = messages.begin(); it != messages.end(); ++it ) 
	{
		it->time_alive += dt;
		if( it->time_alive > fade_time + pause_before_fade ) {
			it->can_kill = true;
		}
		else {
			const float curr_fade_time = it->time_alive - pause_before_fade;
			if( curr_fade_time > 0 ) {
				it->alpha = 255 - (int)( 255 * curr_fade_time / fade_time );
				if( it->alpha < 0 ) {
					it->alpha = 0;
				}
			}
		}
	}
	
	messages.erase( std::remove_if( messages.begin(), messages.end(), can_kill ), messages.end() );
}
void Notifier::Render()
{
	const float line_height = fnt->GetHeight() + 3;
	const float x = 15;
	const float y = 30;
	
	int n = 0;
	for( Messages::reverse_iterator rit = messages.rbegin(); rit != messages.rend(); ++rit, ++n ) 
	{
		const float x_off = 2;
		const float y_off = 2;
		fnt->SetColor( SETA( 0xff000000, rit->alpha ) );
		fnt->Render( x + x_off, y + n * line_height + y_off, HGETEXT_LEFT, rit->str.c_str() );
		
		fnt->SetColor( SETA( 0xffffffff, rit->alpha ) );
		fnt->Render( x, y + n * line_height, HGETEXT_LEFT, rit->str.c_str() );
	}
}
