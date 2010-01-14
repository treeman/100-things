#include <boost/weak_ptr.hpp>

#include "includes/System/Console.hpp"

Console::Console()
{
	Settings::Get().AddListener( this );
	
	fnt.reset( new hgeFont( "fnt/arial10.fnt" ) );
	fnt->SetColor( 0xFF45DD57 );
	
	x = 10; y = 10;
	w = 400;
	h = 300;
	
	cmd_pos = -1;
	input_line_pos = 0;
	
	sugg_pos = -1;
	
	text_off_left = 5;
	text_off_down = 5;
	text_off_top = 5;
	
	line_height = fnt->GetHeight() - 2;
	
	back.reset( new hgeSprite( 0, 0, 0, w, h ) );
	q.reset( new hgeQuad() );
	
	blinkie_time = 0.5;
	
	suggestion_box_width = 0;
	
	show_debug = false;
	is_active = false;
	
	opacity = 0xDD;
	fnt_opacity = 0xFF;
	blinkie_opacity = 0x55;
	selection_opacity = 0x66;
	delimiter_opacity = 0x22;
	
	fnt_color = 0x45DD57;
	fnt_history_color = 0x45DD57;
	fnt_history_line_sign_color = 0x1AA12A;
	fnt_highlight_color = 0xEBF230;
	fnt_suggestion_color = 0x45DD57;
	blinkie_color = 0x7A7A7A;
	selection_color = 0x7A7A7A;
	
	large_back_color = 0x515151;
	suggestion_back_color = 0x5C5C5C;
	delimiter_color = 0x2C2C2C;
	
	SelectionClear();
	blink_timer.Start();
	
	showDebug.reset( new Dator<bool>( show_debug ) );
	Settings::Get().RegisterVariable( "console_show_debug", boost::weak_ptr<BaseDator>( showDebug ) );
	
	clearHistory.reset( new ColdDator( boost::bind( &Console::Clear, this ) ) );
	Settings::Get().RegisterVariable( "console_clear", boost::weak_ptr<BaseDator>( clearHistory ) );
	
	showCommands.reset( new ColdDator( boost::bind( &Console::ShowCommands, this ) ) );
	Settings::Get().RegisterVariable( "console_show_commands", boost::weak_ptr<BaseDator>( showCommands ) );
	
	showCommandsValues.reset( new ColdDator( boost::bind( &Console::ShowCommandsValues, this ) ) );
	Settings::Get().RegisterVariable( "console_show_commands_values", boost::weak_ptr<BaseDator>( showCommandsValues ) );
}
Console::~Console()
{
	
}

bool Console::HandleEvent( hgeInputEvent &e )
{
	if( !is_active ) {
		if( e.type == INPUT_KEYDOWN && e.key == HGEK_F1 ) {
			Activate();
		}
		else {
			return true;
		}
	}
	else if( e.type == INPUT_KEYDOWN && e.key == HGEK_F1 ) {
		Deactivate();
		return true;
	}
	
	if( e.type == INPUT_KEYDOWN ) 
	{		
		if( e.key == HGEK_ENTER && input_line.size() > 0 ) {
			InputLineExecute();
		}
		else if( e.key == HGEK_SPACE ) {
			SelectionDelete();
			InputLineAddChar( ' ', input_line_pos );
			InputLineMoveRight();
		}
		else if( e.key == HGEK_BACKSPACE ) {
			if( SelectionIsActive() ) {
				SelectionDelete();
			}
			else {
				InputLineDeleteChar( input_line_pos - 1 );
				InputLineMoveLeft();
			}
		}
		else if( e.key == HGEK_A && hge->Input_GetKeyState( HGEK_CTRL ) ) {
			SelectionAll();
		}
		else if( e.key == HGEK_C && hge->Input_GetKeyState( HGEK_CTRL ) ) {
			SelectionCopy();
		}
		else if( e.key == HGEK_V && hge->Input_GetKeyState( HGEK_CTRL ) ) {
			SelectionPaste( input_line_pos );
		}
		else if( e.key == HGEK_DELETE ) {
			if( SelectionIsActive() ) {
				SelectionDelete();
			}
			else {
				InputLineDeleteChar( input_line_pos );
			}
		}
		else if( e.key == HGEK_UP ) {
			SelectionClear();
			if( IsSuggestionLocked() ) {
				MoveUpInSuggestion();
			}
			else {
				MoveBackInHistory();
			}
		}
		else if( e.key == HGEK_DOWN ) {
			SelectionClear();
			if( IsHistoryLocked() ) {
				MoveForwardInHistory();
			}
			else {
				MoveDownInSuggestion();
			}
		}
		else if( e.key == HGEK_TAB ) {
			if( IsSuggestionLocked() ) {
				AutoCompleteSuggestion();
			}
		}
		else if( e.key == HGEK_LEFT ) {
			if( hge->Input_GetKeyState( HGEK_SHIFT ) ) {
				SelectionMoveLeft();
			}
			else {
				SelectionClear();
			}
			InputLineMoveLeft();
		}
		else if( e.key == HGEK_RIGHT ) {
			if( hge->Input_GetKeyState( HGEK_SHIFT ) ) {
				SelectionMoveRight();
			}
			else {
				SelectionClear();
			}
			InputLineMoveRight();
		}
		else if( e.chr > 32 ) {
			SelectionDelete();
			InputLineAddChar( e.chr, input_line_pos );
			InputLineMoveRight();
		}
		else {
			return true;
		}
		blink_timer.Restart();
	}
	return false;
}

void Console::HearSetting( std::string str )
{
	if( str.size() > 0 ) {
		AddHistory( str );
	}
}
std::string Console::Clear()
{
	big_history.clear();
	
	return "";
}
std::string Console::ShowCommands()
{
	AddHistory( "Showing all commands:" );
	StrList cmd_list = Settings::Get().GetSettings();
	for( StrList::iterator it = cmd_list.begin(); it != cmd_list.end(); ++it )
	{
		PushHistory( "* " + *it );
	}
	return "";
}

std::string Console::ShowCommandsValues()
{
	AddHistory( "Showing all commands with values:" );
	StrMap cmd_map = Settings::Get().GetSettingsValues();
	for( StrMap::iterator it = cmd_map.begin(); it != cmd_map.end(); ++it )
	{
		if( !it->second.empty() ) {
			PushHistory( "* " + it->first + ' ' + it->second );
		}
	}
	return "";
}

void Console::Update( float dt )
{
	if( !is_active ) {
		return;
	}
}
void Console::Render()
{
	if( !is_active ) {
		return;
	}
	
	RenderBones();
	RenderHistory();
	RenderInputLine();
	RenderTypeSuggestions();
	RenderDebug();
}

void Console::Activate()
{
	is_active = true;
}
void Console::Deactivate()
{
	is_active = false;
}

bool Console::IsHistoryLocked()
{
	return cmd_pos != -1;
}
void Console::MoveBackInHistory()
{
	if( !IsHistoryLocked() ) {
		InputLineSetBuff();
	}
	if( cmd_pos + 1 < (int)cmd_history.size() ) {
		cmd_pos++;
		InputLineSet( cmd_history.at( cmd_pos ) );
	}
}
void Console::MoveForwardInHistory()
{
	if( cmd_pos > -1 ) {
		cmd_pos--;
		if( cmd_pos != -1 ) {
			InputLineSet( cmd_history.at( cmd_pos ) );
		}
		else {
			InputLineRestoreBuff();
		}
	}
}
void Console::ResetHistoryPos()
{
	cmd_pos = -1;
}
void Console::AddHistory( std::string str )
{
	PushHistory( ">> " + str );
}
void Console::PushCmd( std::string str )
{
	AddHistory( str );
}
void Console::PushHistory( std::string str )
{
	if( fnt->GetStringWidth( str.c_str() ) > ( w - 2 * text_off_left ) ) {
		//find the largest string that isn't too large
		std::string s; int i = 0;
		do {
			s += str[i];
			i++;
		}
		while( fnt->GetStringWidth( s.c_str() ) < ( w - 2 * text_off_left ) && i < (int)str.size() );
		
		//try to split on the nearest space of the new string instead
		int space_pos = s.rfind( ' ' );
		if( space_pos != -1 ) {
			PushHistory( str.substr( 0, space_pos ) );
			PushHistory( str.substr( space_pos + 1 ) );
		}
		//else just split and add
		else {
			PushHistory( str.substr( 0, i ) );
			PushHistory( str.substr( i ) );
		}
		
	}
	else {
		big_history.insert( big_history.begin(), str );
	}
}

bool Console::IsSuggestionLocked()
{
	return sugg_pos != -1;
}
void Console::MoveUpInSuggestion()
{
	if( sugg_pos > -1 ) {
		sugg_pos--;
		if( sugg_pos != -1 ) {
			StrMap::iterator it = suggestion_map.begin();
			std::advance( it, sugg_pos );
			
			InputLineSet( it->first + ' ', false );
		}
		else {
			InputLineRestoreBuff();
		}
	}
}
void Console::MoveDownInSuggestion()
{
	if( !IsSuggestionLocked() ) {
		InputLineSetBuff();
	}
	
	if( sugg_pos + 1 < (int)suggestion_map.size() ) {
		sugg_pos++;
		StrMap::iterator it = suggestion_map.begin();
		std::advance( it, sugg_pos );
		
		InputLineSet( it->first + ' ', false );
	}
}
void Console::AutoCompleteSuggestion()
{
	StrMap::iterator it = suggestion_map.begin();
	std::advance( it, sugg_pos );
	
	InputLineSet( it->first + ' ' + it->second );
}
void Console::UpdateSuggestionList()
{
	suggestion_map.clear();
	suggestion_box_width = 0;
		
	if( input_line.size() == 0 ) {
		return;
	}
	
	StrMap allsettings_map = Settings::Get().GetSettingsValues();
	for( StrMap::iterator it = allsettings_map.begin(); it != allsettings_map.end(); ++it )
	{
		std::string composit = it->first + ' ' + it->second;
		
		if( composit.find( input_line ) == 0 ) {
			suggestion_map.insert( *it );
			float temp = fnt->GetStringWidth( composit.c_str() );
			if( temp > suggestion_box_width ) {
				suggestion_box_width = temp;
			}
		}
	}
	
//	if( !suggestion_map.empty() && !IsSuggestionLocked() ) {
//		MoveDownInSuggestion();
//	}
}
void Console::ResetSuggestionPos()
{
	sugg_pos = -1;
}
void Console::InputLineSet( std::string str, bool update_suggestion )
{
	input_line = str;
	input_line_pos = str.size();
	if( update_suggestion ) {
		UpdateSuggestionList();
	}
}
void Console::InputLineOnInput()
{
	ResetHistoryPos();
	ResetSuggestionPos();
	UpdateSuggestionList();
	SelectionDelete();
}
void Console::InputLineSetBuff()
{
	input_line_buff = input_line;
}
void Console::InputLineRestoreBuff()
{
	InputLineSet( input_line_buff );
}
void Console::InputLineInsert( std::string str, int pos )
{
	input_line.insert( pos, str );
	input_line_pos += str.size();
	InputLineOnInput();
}
void Console::InputLineDeleteChar( int pos )
{
	if( pos < input_line_pos && pos >= 0 ) {
		input_line.erase( pos, 1 );
		InputLineOnInput();
	}
	else if( pos >= input_line_pos && pos != (int)input_line.size() ) {
		input_line.erase( pos, 1 );
		InputLineOnInput();
	}
}
void Console::InputLineAddChar( char ch, int pos )
{
	if( fnt->GetStringWidth( std::string(input_line + ch).c_str() ) < ( w - 2 * text_off_left ) ) {
		input_line.insert( pos, 1, ch );
		InputLineOnInput();
	}
}
void Console::InputLineExecute()
{
	Settings::Get().ParseSetting( input_line );
	PushCmd( input_line );
	InputLineClear();
}
void Console::InputLineClear()
{
	input_line.clear();
	input_line_pos = 0;
	InputLineOnInput();
}
void Console::InputLineMoveLeft()
{
	if( input_line_pos > 0 ) {
		input_line_pos--;
	}
}
void Console::InputLineMoveRight()
{
	if( input_line_pos < (int)input_line.size() ) {
		input_line_pos++;
	}
}
bool Console::SelectionIsActive()
{
	return sel_start != -1 || sel_length != 0;
}
void Console::SelectionAll()
{
	sel_start = 0;
	sel_length = input_line.size();
}
void Console::SelectionMoveLeft()
{
	if( sel_start == -1 ) {
		sel_start = input_line_pos;
	}
	
	if( sel_start + sel_length > 0 ) {
		--sel_length;
	}
}
void Console::SelectionMoveRight()
{
	if( sel_start == -1 ) {
		sel_start = input_line_pos;
	}
	
	if( sel_start + sel_length < (int)input_line.size() ) {
		++sel_length;
	}
}
void Console::SelectionClear()
{
	sel_length = 0;
	sel_start = -1;
}
void Console::SelectionDelete()
{
	if( sel_start != -1 || sel_length != 0 ) {
		
		std::string before, after;
		if( sel_length > 0 ) {
			before = input_line.substr( 0, sel_start );
			after = input_line.substr( sel_start + sel_length );
			input_line_pos = sel_start;
		}
		else {
			before = input_line.substr( 0, sel_start + sel_length );
			after = input_line.substr( sel_start );
			input_line_pos = sel_start + sel_length;
		}
		InputLineSet( before + after );
	}
	SelectionClear();
}

void Console::SelectionCopy()
{
	if( sel_length < 0 ) {
		selection_copy = input_line.substr( sel_start + sel_length, -sel_length );
	}
	else if( sel_length > 0 ) {
		selection_copy = input_line.substr( sel_start, sel_length );
	}
}
void Console::SelectionPaste( int pos )
{
	if( selection_copy.size() > 0 ) {
		InputLineInsert( selection_copy, pos );
	}
}

void Console::RenderBones()
{
	back->SetColor( SETA( large_back_color, opacity ) );
	back->Render( x, y );
	
//	//line above input line
//	const float x1 = x;
//	const float x2 = x + w;
//	const float y1 = y + h - text_off_down - fnt->GetHeight();
//	
//	hge->Gfx_RenderLine( x1, y1, x2, y1, SETA( delimiter_color, delimiter_opacity ) );
	
//	const float x3 = x + w;
//	const float y2 = y + h;
//	const float y3 = y2 - text_off_down - fnt->GetHeight();
//	
//	hge->Gfx_RenderLine( x3, y2, x3, y3, SETA( delimiter_color, delimiter_opacity ) );
}
void Console::RenderHistory()
{
	fnt->SetColor( SETA( fnt_history_color, fnt_opacity ) );
	
	const int max_n = (int)(( h - text_off_top - text_off_down ) / line_height - 2);
	int n = (int)big_history.size() - 1 < max_n ? big_history.size() - 1 : max_n;
	for( StrList::iterator it = big_history.begin(); it != big_history.end(); ++it )
	{
		if( it->substr( 0, 3 ) == ">> " ) 
		{
			fnt->SetColor( SETA( fnt_history_line_sign_color, fnt_opacity ) );
			fnt->Render( x + text_off_left, y + text_off_top + n * line_height, HGETEXT_LEFT, ">> " );
			
			fnt->SetColor( SETA( fnt_history_color, fnt_opacity ) );
			fnt->Render( x + text_off_left + fnt->GetStringWidth( ">> " ), y + text_off_top + n * line_height, 
				HGETEXT_LEFT, it->substr( 3 ).c_str() );
		}
		else {
			fnt->Render( x + text_off_left, y + text_off_top + n * line_height, HGETEXT_LEFT, it->c_str() );
		}
		--n;
		if( n < 0 ) {
			break;
		}
	}
}

void Console::RenderInputLine()
{
	fnt->Render( x + text_off_left, y + h - text_off_down - fnt->GetHeight(), HGETEXT_LEFT, input_line.c_str() );
	
	if( SelectionIsActive() ) {
	
		std::string before, sel;
		if( sel_length > 0 ) {
			before = input_line.substr( 0, sel_start );
			sel = input_line.substr( sel_start, sel_length );
		}
		else {
			before = input_line.substr( 0, sel_start + sel_length );
			sel = input_line.substr( sel_start + sel_length, -sel_length );
		}
		
		const float sel_x1 = x + text_off_left + fnt->GetStringWidth( before.c_str() );
		const float sel_x2 = sel_x1 + fnt->GetStringWidth( sel.c_str() );
		const float sel_y1 = y + h - text_off_down;
		const float sel_y2 = y + h - text_off_down - fnt->GetHeight();
		
		q->v[0].x = sel_x1; q->v[0].y = sel_y1;
		q->v[1].x = sel_x2; q->v[1].y = sel_y1;
		q->v[2].x = sel_x2; q->v[2].y = sel_y2;
		q->v[3].x = sel_x1; q->v[3].y = sel_y2;
		
		q->v[0].col = SETA( selection_color, selection_opacity );
		q->v[1].col = SETA( selection_color, selection_opacity );
		q->v[2].col = SETA( selection_color, selection_opacity );
		q->v[3].col = SETA( selection_color, selection_opacity );
		
		hge->Gfx_RenderQuad( q.get() );
	}
	
	fnt->Render( x + text_off_left, y + h - text_off_down - fnt->GetHeight(), HGETEXT_LEFT, input_line.c_str() );
	
	if( blink_timer.GetTime() < blinkie_time ) {
		
		//the little blinking helper thing
		float line_x = x + text_off_left + fnt->GetStringWidth( input_line.substr( 0, input_line_pos ).c_str() );
		float line_h = fnt->GetHeight();
		float line_y = y + h - text_off_down - fnt->GetHeight();
		
		hge->Gfx_RenderLine( line_x, line_y, line_x, line_y + line_h, SETA( blinkie_color, blinkie_opacity ) );
	}
	else if( blink_timer.GetTime() > 2 * blinkie_time ) {
		blink_timer.Restart();
	}
}
void Console::RenderTypeSuggestions()
{
	if( input_line.size() == 0 || suggestion_map.size() == 0 ) {
		return;
	}
	
	const float x1 = x;
	const float x2 = x1 + suggestion_box_width + 2 * text_off_left;
	const float y1 = y + h;
	const float y2 = y1 + text_off_down + line_height * suggestion_map.size();

	back->SetColor( SETA( suggestion_back_color, opacity ) );
	back->Render4V( x1, y1, x2, y1, x2, y2, x1, y2 );

	int n = 0;
	for( StrMap::iterator it = suggestion_map.begin(); it != suggestion_map.end(); ++it )
	{
		if( n == sugg_pos ) {
			fnt->SetColor( SETA( fnt_highlight_color, fnt_opacity ) );
		}
		else {
			fnt->SetColor( SETA( fnt_suggestion_color, fnt_opacity ) );
		}
		
		std::string s = it->first + ' ' + it->second;
		fnt->Render( x + text_off_left, y + h + line_height * n, HGETEXT_LEFT, s.c_str() );
		n++;
	}
}

void Console::RenderDebug()
{
	if( !show_debug ) return;
	
	fnt->SetColor( 0xffffffff );
	fnt->printf( x + w + text_off_left, y, HGETEXT_LEFT, "line_pos: %i history_pos: %i history_length: %i", 
		input_line_pos, cmd_pos, cmd_history.size() );
	
	std::string s;
	if( sel_start == -1 || sel_length == 0 ) {
		s = "nop";
	}
	else {
		try {
			if( sel_length > 0 ) {
				s = input_line.substr( sel_start, sel_length );
			}
			else {
				s = input_line.substr( sel_start + sel_length, -sel_length );
			}
		}
		catch( ... ) {
			s = "ezxception caught here!";
			Log::Get().Write( "engine", "substr exc caught: sel_start: %i sel_length: %i input_line: %s",
				sel_start, sel_length, input_line.c_str() );
		}
	}
	fnt->printf( x + w + text_off_left, y + line_height, HGETEXT_LEFT, "sel_start: %i sel_length: %i substr: %s", 
		sel_start, sel_length, s.c_str() );
}
