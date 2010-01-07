#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#include <stdarg.h>
#include <string>
#include <fstream>
#include <map>

#include "Config.hpp"
#include "Singleton.hpp"
#include "ErrorHandling.hpp"
#include "Hge.hpp"

class Log : public Singleton<Log> {
public:
	Log();
	virtual ~Log();

	bool AddLogFile( std::string id, std::string path, bool set_timestamps = true );
	void Write( std::string id, const char *msg, ... );

	Log &SetLogFile( std::string id ) throw( Error::file_not_found );
	template <class T> Log &operator << ( T obj );
protected:
	struct Streamer {
		std::ofstream *stream;
		bool set_timestamp;
	};
	
	void WriteLog( const char *msg, ... );
	std::ofstream *log;

	typedef std::map<std::string, Streamer> StreamMap;
	StreamMap stream_map;
	
	std::string last_id;
	
	HgeObj hge;
};

template <class T> Log &Log::operator<<(T obj)
{
#ifdef LOGGER
	StreamMap::iterator it = stream_map.find( last_id );
	if( it != stream_map.end() ) {
		(*(*it).second.stream) << obj << std::flush;
	} else {
		WriteLog( "Trying to write on an uninitialized log file, message:\n" );
		(*log) << obj;
	}
#endif
	return *this;
}

#endif
