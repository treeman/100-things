#include "includes/Scoreboard.hpp"
#include "includes/GameWorld.hpp"

bool operator < ( const Score &s1, const Score &s2 )
{
	return s1.kills > s2.kills;
}

Scoreboard::Scoreboard( StateHandler *const _state_handler ) : GameState( _state_handler ), 
	state_handler( _state_handler ), fnt( new hgeFont( "fnt/asiaextended23.fnt" ) )
{
	std::fstream file( "scores" );
	if( !file.is_open() ) {
		throw( Error::file_not_found( "scores couldn't be opened" ) );
	}
	
	while( !file.eof() )
	{
		std::string line;
		std::getline( file, line );
		
		if( !line.empty() ) {
			ParseScoreLine( line );
		}
	}
	
	file.close();
}

Scoreboard::~Scoreboard()
{
	
}
	
void Scoreboard::NewScore( float time, int kills )
{
	Score score;
	score.time = time;
	score.kills = kills;
	scores.push_back( score );
	
	std::fstream file( "scores", std::ios::out | std::ios::app );
	if( !file.is_open() ) {
		throw( Error::file_not_found( "scores couldn't be opened" ) );
	}
	
	file << score.time << '-' << score.kills << '\n' << std::flush;
	
	file.close();
}

bool Scoreboard::HandleEvent( hgeInputEvent &e )
{
	if( e.type == INPUT_KEYDOWN ) {
		switch( e.key ) {
			case HGEK_ENTER:
				state_handler->Pop();
				boost::shared_ptr<GameWorld> state( new GameWorld( state_handler ) );
				state_handler->Push( state );
		}
	}
	return true;
}
void Scoreboard::Update( float )
{
	std::sort( scores.begin(), scores.end() );
	scores.resize( 10 );
}
void Scoreboard::Render()
{
	const float line_height = fnt->GetHeight() + 3;
	
	fnt->Render( 100, 10, HGETEXT_LEFT, "Showing the top ten runs" );
	
	int n = 0;
	for( Scores::iterator it = scores.begin(); it != scores.end(); ++it, ++n )
	{
		fnt->printf( 100, 50 + line_height * n, HGETEXT_LEFT, "#%i time: %.1f kills: %i", n + 1, it->time, it->kills );
	}
}

void Scoreboard::ParseScoreLine( std::string line )
{
	int split = line.find( '-' );
	
	std::string time = line.substr( 0, split );
	std::string kills = line.substr( split + 1 );
	
	try {
		Score score;
		score.time = boost::lexical_cast<float>( time );
		score.kills = boost::lexical_cast<int>( kills );
		
		scores.push_back( score );
	}
	catch( boost::bad_lexical_cast &e ) { }
}
