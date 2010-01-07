#include <boost/algorithm/string/trim.hpp>

#include "includes/System/Settings.hpp"

Settings::Settings()
{ 
	
}
Settings::~Settings()
{
	
}
void Settings::RegisterVariable( std::string name, boost::weak_ptr<BaseDator> dator )
{
	boost::shared_ptr<BaseDator> real_dator = dator.lock();
	
	StringMap::iterator it = unparsed_settings_map.find( name );
	if( it != unparsed_settings_map.end() && real_dator ) 
	{
//		Log::Get().Write( "engine", "Registering unparsed setting: '%s %s'", name.c_str(), it->second.c_str() );
		
		std::string ret = real_dator->Set( it->second );
		UpdateListeners( ret );
		unparsed_settings_map.erase( it );
	}
	else {
		DatorMap::iterator it = dator_map.find( name );
		if( it != dator_map.end() && real_dator )
		{
//			Log::Get().Write( "engine", "Registering parsed setting: '%s %s'", name.c_str(), it->second.lock()->Get().c_str() );
			
			boost::shared_ptr<BaseDator> other_dator = it->second.lock();
			if( other_dator ) {
				std::string ret = real_dator->Set( other_dator->Get() );
				UpdateListeners( ret );
			}
			else {
				dator_map.erase( it );
			}
		}
	}
	
	if( !dator.expired() ) {
		dator_map.insert( std::make_pair( name, dator ) );
	}
}
void Settings::UnregisterVariable( std::string name )
{
	dator_map.erase( name );
}

std::string Settings::GetValue( std::string name ) 
{
	DatorMap::iterator it = dator_map.find( name );
	if( it != dator_map.end() ) {
		boost::shared_ptr<BaseDator> other_dator = it->second.lock();
		if( other_dator ) {
			return other_dator->Get();
		}
		else {
			dator_map.erase( it );
		}
	}
	return "";
}

std::vector<std::string> Settings::GetSettings()
{
	std::vector<std::string> l;
	for( DatorMap::iterator it = dator_map.begin(); it != dator_map.end(); ++it ) {
		l.insert( l.begin(), it->first );
	}
	std::sort( l.begin(), l.end() );
	std::unique( l.begin(), l.end() );
	return l;
}
std::map<std::string, std::string> Settings::GetSettingsValues()
{
	std::map<std::string, std::string> m;
	for( DatorMap::iterator it = dator_map.begin(); it != dator_map.end(); ++it ) {
		boost::shared_ptr<BaseDator> other_dator = it->second.lock();
		if( other_dator ) {
			m.insert( std::make_pair( it->first, other_dator->Get() ) );
		}
		else {
			dator_map.erase( it );
		}
	}
	return m;
}

void Settings::ParseFile( std::string file ) throw( Error::file_not_found )
{
	Log::Get().Write( "engine", "Parsing setting file: '%s'", file.c_str() );
	
	std::ifstream in( file.c_str() );

	if( !in.is_open() ) {
	    std::string s = "Error opening: " + file;
	    throw( Error::file_not_found( s.c_str() ) );
	}

	while( !in.eof() )
	{
		std::string str;
		std::getline( in, str );
		if( str.size() > 0 ) {
			
			if( str.find( ';' ) != 0 ) {
				ParseSetting( str );
			}
		}
	}
}

void Settings::ParseSetting( std::string str ) throw()
{
	if( !str.size() ) {
		return; //"Parsing an empty setting? Pff...";
	}

	std::string name, value;
	int pos = str.find( ' ' );
	
	if( pos != 0 )
	{
		name = str.substr( 0, pos );
		value = str.substr( pos + 1 );
	} 
	else {
		return; // "Setting malformed: bastard!";
	}
	
	boost::trim( name ); boost::trim( value );
	SetVariable( name, value );
}

void Settings::SetVariable( std::string name, std::string value )
{
	typedef std::pair<DatorMap::iterator, DatorMap::iterator> ItPair;
	ItPair ret = dator_map.equal_range( name );
	
	if( ret.first == ret.second ) {
		//no setting found
		StringMap::iterator it = unparsed_settings_map.find( name );
		if( it != unparsed_settings_map.end() ) {
			it->second = value;
		}
		else {
			unparsed_settings_map.insert( std::make_pair( name, value ) );
		}
	}
	else {
		
		Log::Get().Write( "engine", "Using setting: '%s %s'", name.c_str(), value.c_str() );
		for( DatorMap::iterator it = ret.first; it != ret.second; ++it ) 
		{
			boost::shared_ptr<BaseDator> other_dator = it->second.lock();
			if( other_dator ) {
				std::string temp = other_dator->Set( value );
				UpdateListeners( temp );
			}
			else {
				dator_map.erase( it );
			}
		}
	}
}

void Settings::AddListener( SettingsListener *listener )
{
	listener_list.insert( listener_list.end(), listener );
}

void Settings::UpdateListeners( std::string str )
{
	for( ListenerList::iterator it = listener_list.begin(); it != listener_list.end(); ++it )
	{
		(*it)->HearSetting( str );
	}
}
