#include "includes/System/SoundManager.hpp"
#include "includes/System/Settings.hpp"

SoundManager::SoundManager() :
	stream_vol(50), music_vol(50), effect_vol(50), use_sound(true), is_setup(false)
{	
	Setup();
}
SoundManager::~SoundManager()
{
    
}

void SoundManager::Setup()
{
	Log::Get().Write( "engine", "Setting up the sound" );
	
	soundVol.reset( new Dator<int>( stream_vol, boost::bind( &SoundManager::SetStreamVolume, this, _1 ) ) );
	musicVol.reset( new Dator<int>( music_vol, boost::bind( &SoundManager::SetMusicVolume, this, _1 ) ) );
	effectVol.reset( new Dator<int>( effect_vol, boost::bind( &SoundManager::SetEffectVolume, this, _1 ) ) );
	useSound.reset( new Dator<bool>( use_sound, boost::bind( &SoundManager::SetUseSound, this, _1 ) ) );

	Settings::Get().RegisterVariable( "stream_volume", boost::weak_ptr<BaseDator>( soundVol ) );
	Settings::Get().RegisterVariable( "music_volume", boost::weak_ptr<BaseDator>( musicVol )) ;
	Settings::Get().RegisterVariable( "effect_volume", boost::weak_ptr<BaseDator>( effectVol ) );
	Settings::Get().RegisterVariable( "sound_enabled", boost::weak_ptr<BaseDator>( useSound ) );
	
	hge->System_SetState( HGE_FXVOLUME, effect_vol );
	hge->System_SetState( HGE_MUSVOLUME, music_vol );
	hge->System_SetState( HGE_STREAMVOLUME, stream_vol );
	hge->System_SetState( HGE_USESOUND, use_sound );
	
	is_setup = true;
}

std::string SoundManager::SetUseSound( const bool &predicate )
{
	use_sound = predicate;
	if( is_setup ) {
		hge->System_SetState( HGE_USESOUND, use_sound );
	}
	if( use_sound ) {
		return "waah - I can hear the sound now";
	}
	else {
		return "huh? Did you say something? I'm deaf";
	}
}
std::string SoundManager::SetStreamVolume( const int &val )
{
	stream_vol = val;
	if( is_setup ) {
		hge->System_SetState( HGE_STREAMVOLUME, stream_vol );
	}
	return "";
}
std::string SoundManager::SetMusicVolume( const int &val )
{
	music_vol = val;
	if( is_setup ) {
		hge->System_SetState( HGE_MUSVOLUME, music_vol );
	}
	return "";
}
std::string SoundManager::SetEffectVolume( const int &val )
{
	effect_vol = val;
	if( is_setup ) {
		hge->System_SetState( HGE_FXVOLUME, effect_vol );
	}
	return "";
}
