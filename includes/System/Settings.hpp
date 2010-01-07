#ifndef SETTINGSMANAGER_HPP_INCLUDED
#define SETTINGSMANAGER_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <string>
#include <vector>
#include <map>

#include "Hge.hpp"
#include "Dator.hpp"
#include "Errorhandling.hpp"
#include "Singleton.hpp"

class SettingsListener {
public:
	virtual ~SettingsListener() { }
	//will get the return string from update functions from settings_manager
	virtual void HearSetting( std::string str ) = 0;
};

class Settings : public Singleton<Settings> {
public:
	Settings();
	virtual ~Settings();
	
	void RegisterVariable( std::string name, boost::weak_ptr<BaseDator> dator );
	void UnregisterVariable( std::string name );
	
	std::string GetValue( std::string name );

	std::vector<std::string> GetSettings();
	std::map<std::string, std::string> GetSettingsValues();
	
	void ParseFile( std::string path ) throw( Error::file_not_found );
	void ParseSetting( std::string str ) throw();
	
	void AddListener( SettingsListener *listener );
	
	void ClearExpired();
private:
	typedef std::multimap<std::string, boost::weak_ptr<BaseDator> > DatorMap;
	DatorMap dator_map;
	
	typedef std::map<std::string, std::string> StringMap;
	StringMap unparsed_settings_map;
	
	void SetVariable( std::string name, std::string value );
	
	typedef std::list<SettingsListener*> ListenerList;
	ListenerList listener_list;
	
	void UpdateListeners( std::string str );
};

#endif
