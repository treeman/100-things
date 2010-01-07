#include "includes/System/Log.hpp"

Log::Log()
{
#ifdef LOGGER
	last_id = "";
	log = new std::ofstream;
	log->open( "loggers_log.txt" );

	WriteLog( "I Logged teh Logger good!" );
	
	hge->System_SetState( HGE_LOGFILE, "hge_log.txt" );
	WriteLog( "Opening hge log file: 'hge_log.txt'" );
#endif
}

Log::~Log()
{
#ifdef LOGGER
	for( StreamMap::iterator it = stream_map.begin(); it != stream_map.end(); ++it )
	{
		(*it).second.stream->close();
		delete (*it).second.stream;
	}
	stream_map.clear();

	log->close();
	delete log;
#endif
}

bool Log::AddLogFile( std::string id, std::string path, bool set_timestamps )
{
#ifdef LOGGER
	Streamer stream;
	stream.stream = new std::ofstream;
	stream.set_timestamp = set_timestamps;
	
	StreamMap::iterator it = stream_map.insert( stream_map.end(), std::make_pair( id, stream ) );
	(*it).second.stream->open( path.c_str() );
	if( !(*(*it).second.stream) )
		return false;

	if( stream_map.size() == 1 )
		last_id = (*it).first;
		
	WriteLog( "Opening log file '%s' as '%s'", path.c_str(),id.c_str() );
#endif
	return true;
}

void Log::Write( std::string id, const char *msg, ... )
{
#ifdef LOGGER
	va_list args; va_start( args, msg );
	char szBuf[1024];
	vsprintf( szBuf, msg, args );

	StreamMap::iterator it = stream_map.find( id );
	if( it != stream_map.end() )
	{
		if( it->second.set_timestamp && szBuf ) {
			it->second.stream->precision( 4 );;
			char tbuf[1024];
			sprintf( tbuf, "[%.2f] ", hge->Timer_GetTime() );
			(*it->second.stream) << tbuf;
			it->second.stream->precision();
		}
		(*(*it).second.stream) << szBuf << std::endl;
#ifndef NDEBUG
		(*it).second.stream->flush();
#endif
	} else {
		WriteLog( "Trying to write on an unidentified log file, message:\n" );
		(*log) << szBuf << std::endl;
	}

	va_end( args );
#endif
}

void Log::WriteLog( const char *msg, ... )
{
#ifdef LOGGER
	va_list args; va_start( args, msg );
	char szBuf[1024];
	vsprintf( szBuf, msg, args );

	(*log) << szBuf << std::endl;

	va_end( args );
#endif
}

Log &Log::SetLogFile( std::string id ) throw( Error::file_not_found )
{
#ifdef LOGGER
	StreamMap::iterator it = stream_map.find( id );
	if( it != stream_map.end() ) {
		last_id = id;
	}
	else {
		std::string s = "NoLogLike: %s" + id;
		throw( Error::file_not_found( s.c_str() ) );
	}
#endif
	return *this;
}
