#ifndef HGEOBJSTUFF_HPP_INCLUDED
#define HGEOBJSTUFF_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "HgeIncl.hpp"
#include "../ErrorHandling.hpp"

class HgeObj {
public:
	HgeObj() {
		hge = hgeCreate( HGE_VERSION );
	}
	HgeObj( const HgeObj &o ) {
		hge = hgeCreate( HGE_VERSION );
	}
	HgeObj &operator = ( const HgeObj &o ) {
		hge = hgeCreate( HGE_VERSION );
		return *this;
	}
	~HgeObj() {
		hge->Release();
	}
	inline operator HGE *() const {
		return hge;
	}
	inline HGE *operator ->() const {
		return hge;
	}
private:
	HGE *hge;
};

class TexObj {
public:
	TexObj() { }
	TexObj( std::string file ) {
		Load( file );
	}
	
	void Create( int w, int h ) {
		tex.reset( new HTEXTURE( hge->Texture_Create( w, h ) ) );
	}
	
	void Load( std::string file ) throw( Error::file_not_found ) {
		tex.reset( new HTEXTURE( hge->Texture_Load( file.c_str() ) ) );
		if( !tex ) {
			std::string s = "Couldn't load texture from " + file;
			throw Error::file_not_found( s.c_str() );
		}
	}
	
	inline operator HTEXTURE () const {
		if( !tex ) return 0;
		else return *tex;
	}
private:
	boost::shared_ptr<HTEXTURE> tex;
	
	HgeObj hge;
};

class EffectObj {
public:
	EffectObj() { }
	EffectObj( std::string file ) {
		Load( file );
	}
	
	void Load( std::string file ) throw( Error::file_not_found ) {
		effect.reset( new HEFFECT( hge->Effect_Load( file.c_str() ) ) );
		if( !effect ) {
			std::string s = "Couldn't load effect from " + file;
			throw Error::file_not_found( s.c_str() );
		}
	}
	
	inline operator HEFFECT () const {
		if( !effect ) return 0;
		else return *effect;
	}
private:
	boost::shared_ptr<HEFFECT> effect;
	
	HgeObj hge;
};

class MusicObj {
public:
	MusicObj() { }
	MusicObj( std::string file ) {
		Load( file );
	}
	
	void Load( std::string file ) throw( Error::file_not_found ) {
		music.reset( new HMUSIC( hge->Music_Load( file.c_str() ) ) );
		if( !music ) {
			std::string s = "Couldn't load music from " + file;
			throw Error::file_not_found( s.c_str() );
		}
	}
	
	inline operator HMUSIC () const {
		if( !music ) return 0;
		else return *music;
	}
private:
	boost::shared_ptr<HMUSIC> music;
	
	HgeObj hge;
};

class StreamObj {
public:
	StreamObj() { }
	StreamObj( std::string file ) {
		Load( file );
	}
	
	void Load( std::string file ) throw( Error::file_not_found ) {
		stream.reset( new HSTREAM( hge->Texture_Load( file.c_str() ) ) );
		if( !stream ) {
			std::string s = "Couldn't load stream from " + file;
			throw Error::file_not_found( s.c_str() );
		}
	}
	
	inline operator HSTREAM () const {
		if( !stream ) return 0;
		else return *stream;
	}
private:
	boost::shared_ptr<HSTREAM> stream;
	
	HgeObj hge;
};

#endif
