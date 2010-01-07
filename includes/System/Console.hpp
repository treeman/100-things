#ifndef CONSOLE_HPP_INCLUDED
#define CONSOLE_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/ref.hpp>

#include "InputHandler.hpp"
#include "Hge.hpp"
#include "Timer.hpp"
#include "Dator.hpp"
#include "Settings.hpp"

class Console : public InputHandler, public SettingsListener {
public:
	Console();
	~Console();
 
	bool HandleEvent( hgeInputEvent &e );
	
	void HearSetting( std::string str );
	
	void AddHistory( std::string str );
	
	std::string Clear();
	std::string ShowCommands();
	std::string ShowCommandsValues();

	void Update( float dt );
	void Render();

	std::vector<std::string> GetHistory() const;
private:
	void Activate();
	void Deactivate();
	
	typedef std::vector<std::string> StrList;
	typedef std::map<std::string, std::string> StrMap;
	
	boost::shared_ptr<hgeFont> fnt;
	
	float x, y;
	float w, h;
	
	boost::shared_ptr<hgeSprite> back;
	
	bool IsHistoryLocked();
	
	void MoveBackInHistory();
	void MoveForwardInHistory();
	
	void ResetHistoryPos();
	
	void PushCmd( std::string str );
	StrList cmd_history;
	int cmd_pos;
	
	void PushHistory( std::string str );
	StrList big_history;
	
	bool IsSuggestionLocked();
	
	void MoveUpInSuggestion();
	void MoveDownInSuggestion();
	
	void AutoCompleteSuggestion();
	
	void UpdateSuggestionList();
	void ResetSuggestionPos();
	
	StrMap suggestion_map;
	int sugg_pos;
	float suggestion_box_width;
	boost::shared_ptr<hgeQuad> q;
	
	void InputLineSet( std::string str, bool update_suggestion = true );
	void InputLineOnInput();

	void InputLineSetBuff();
	void InputLineRestoreBuff();
	
	void InputLineInsert( std::string str, int pos );
	
	void InputLineDeleteChar( int pos );
	void InputLineAddChar( char ch, int pos );
	
	void InputLineExecute();
	void InputLineClear();
	
	void InputLineMoveLeft();
	void InputLineMoveRight();
	
	std::string input_line_buff;
	std::string input_line;
	int input_line_pos;
	
	bool SelectionIsActive();
	void SelectionAll();
	void SelectionMoveLeft();
	void SelectionMoveRight();
	void SelectionClear();
	void SelectionDelete();
	
	void SelectionCopy();
	void SelectionPaste( int pos );
	
	int sel_start, sel_length;
	std::string selection_copy;
	
	void RenderBones();
	void RenderHistory();
	void RenderInputLine();
	void RenderTypeSuggestions();
	
	float text_off_left;
	float text_off_down;
	float text_off_top;
	
	float line_height;
	
	Timer blink_timer;
	float blinkie_time;
	
	bool show_debug;
	bool is_active;
	
	int opacity;
	int fnt_opacity;
	int blinkie_opacity;
	int selection_opacity;
	int delimiter_opacity;
	
	int some_stuff;
	
	DWORD fnt_color;
	DWORD fnt_history_color;
	DWORD fnt_history_line_sign_color;
	DWORD fnt_highlight_color;
	DWORD fnt_suggestion_color;
	DWORD blinkie_color;
	
	DWORD large_back_color;
	DWORD suggestion_back_color;
	DWORD selection_color;
	DWORD delimiter_color;
	
	HgeObj hge;
	
	void RenderDebug();
	
	boost::shared_ptr<Dator<bool> > showDebug;
	boost::shared_ptr<ColdDator> clearHistory;
	boost::shared_ptr<ColdDator> showCommands;
	boost::shared_ptr<ColdDator> showCommandsValues;
};

#endif
