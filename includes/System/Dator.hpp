#ifndef _DATOR_HPP_INCLUDED
#define _DATOR_HPP_INCLUDED

#include <sstream>
#include <string>
#include <list>
#include <map>

#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include "ErrorHandling.hpp"
#include "Log.hpp"

class BaseDator {
public:
	virtual ~BaseDator() { }
	
	virtual std::string Get() = 0;
	virtual std::string Set( const std::string new_val ) = 0;
};

class ColdDator : public BaseDator {
public:
	ColdDator( boost::function<std::string()> func ) :
		call_func( func ) { }
		
	std::string Get() {
		return "";
	}
	std::string Set( const std::string ) {
		return call_func();
	}
private:
	boost::function<std::string()> call_func;
};

template<typename T>
class Dator : public BaseDator {
public:
	Dator( T &new_val ) : 
		val( &new_val ), change_func(0) 
	{ }
	Dator( T &new_val, boost::function<std::string( const T )> func ) :
		val( &new_val ), change_func( func )
	{ }
	virtual ~Dator() { }
	
	typedef T type;

	std::string Get() {
		return boost::lexical_cast<std::string>( *val );
	}
	std::string Set( const std::string new_val )
	{
		if( new_val.size() == 0 ) {
			return "";
		}
		try {
			type call = boost::lexical_cast<type>( new_val );
			*val = call;

			if( change_func ) {
				return change_func( call );
			}
		}
		catch( boost::bad_lexical_cast &e ) 
		{
			Log::Get().Write( "engine", "Dator<%s>::Set(%s): %s", 
				typeid(T).name(), new_val.c_str(), e.what()
			);
		}
		return "";
	}
protected:
	T *val;
	
	boost::function<std::string( const type )> change_func;
};

template<>
class Dator<std::string> : public BaseDator {
public:
	Dator( std::string &new_val ) : 
		val( &new_val ), change_func(0) 
	{ }
	Dator( std::string &new_val, boost::function<std::string( const std::string )> func ) :
		val( &new_val ), change_func( func )
	{ }
	virtual ~Dator() { }
	
	typedef std::string type;

	std::string Get() {
		return *val;
	}
	std::string Set( const std::string new_val )
	{
		if( new_val.size() == 0 ) {
			return "";
		}
		*val = new_val;
		if( change_func ) {
			return change_func( new_val );
		}
		return "";
	}
protected:
	std::string *val;
	boost::function<std::string( const std::string )> change_func;
};

#endif
