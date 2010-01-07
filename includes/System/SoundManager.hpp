#ifndef SOUNDMANAGER_HPP_INCLUDED
#define SOUNDMANAGER_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>

#include <string>

#include "Hge.hpp"
#include "Dator.hpp"

class SoundManager {
public:
	SoundManager();
	~SoundManager();

	void Setup();
	
	std::string SetUseSound( const bool &predicate );
	std::string SetStreamVolume( const int &val );
	std::string SetMusicVolume( const int &val );
	std::string SetEffectVolume( const int &val );
private:
	int stream_vol, music_vol, effect_vol;
    bool use_sound;
	std::string title_name;

	HgeObj hge;
	
	bool is_setup;
	
	boost::shared_ptr<Dator<int> > soundVol;
	boost::shared_ptr<Dator<int> > musicVol;
	boost::shared_ptr<Dator<int> > effectVol;
	boost::shared_ptr<Dator<bool> > useSound;
};

#endif
