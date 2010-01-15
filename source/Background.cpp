#include <boost/foreach.hpp>
#include <sstream>

#include "includes/System/Settings.hpp"
#include "includes/Background.hpp"

const float sky_height = 600;

ABackground::ABackground() : Shakeable( 0.2, 0.2 ), asia30( new hgeFont( "fnt/asiaextended30.fnt" ) ), 
	asia23( new hgeFont( "fnt/asiaextended23.fnt" ) ), arial10( new hgeFont( "fnt/arial10.fnt" ) ),
	rage( 0 ), enemies_killed( 0 )
{
	const int screen_w = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_width" ) );
	
	sky_spr.reset( new hgeSprite( 0, 0, 0, screen_w, sky_height ) );
	
	sky_spr->SetColor( 0xFFc35454, 0 );
	sky_spr->SetColor( 0xFFc35454, 1 );
	sky_spr->SetColor( 0xFF3e0e50, 2 );
	sky_spr->SetColor( 0xFF3e0e50, 3 );
	
	time_cloud.tex.Load( "gfx/time_cloud.png" );
	time_cloud.spr.reset( new hgeSprite( time_cloud.tex, 0, 0, 177, 100 ) );
	time_cloud.x = 10; time_cloud.y = 40;
	time_cloud.min_x = 70; time_cloud.max_x = 130;
	
	kill_cloud.tex.Load( "gfx/kill_cloud.png" );
	kill_cloud.spr.reset( new hgeSprite( kill_cloud.tex, 0, 0, 263, 100 ) );
	kill_cloud.x = 150; kill_cloud.y = 130;
	kill_cloud.min_x = 130; kill_cloud.max_x = 170;
	
	rage_cloud.tex.Load( "gfx/rage_cloud.png" );
	rage_cloud.spr.reset( new hgeSprite( rage_cloud.tex, 0, 0, 216, 100 ) );
	rage_cloud.x = 400; rage_cloud.y = 80;
	rage_cloud.min_x = 330; rage_cloud.max_x = 470;
	
	timer.Start();
}

void ABackground::SetDudePos( Vec2D pos )
{
	dude_pos = pos;
}
void ABackground::SetRageLevel( float rage_perc )
{
	rage = rage_perc;
}
void ABackground::ReportEnemyKilled()
{
	++enemies_killed;
}
	
void ABackground::Update( float dt )
{
	const float dude_min = 0;
	const float dude_max = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_width" ) );
	
	const float dude_perc = dude_pos.x / ( dude_max - dude_min );
	
	rage_cloud.x = rage_cloud.min_x + dude_perc * ( rage_cloud.max_x - rage_cloud.min_x );
	kill_cloud.x = kill_cloud.min_x + dude_perc * ( kill_cloud.max_x - kill_cloud.min_x );
	time_cloud.x = time_cloud.min_x + dude_perc * ( time_cloud.max_x - time_cloud.min_x );
}

void ABackground::Render()
{
	sky_spr->Render(0,0);
	
	const DWORD cloud_color = 0x77610303;

	time_cloud.spr->SetColor( cloud_color );
	time_cloud.spr->Render( time_cloud.x + shake_x_offset, time_cloud.y + shake_y_offset );
	
	kill_cloud.spr->SetColor( cloud_color );
	kill_cloud.spr->Render( kill_cloud.x + shake_x_offset, kill_cloud.y + shake_y_offset );
	
	rage_cloud.spr->SetColor( cloud_color );
	rage_cloud.spr->Render( rage_cloud.x + shake_x_offset, rage_cloud.y + shake_y_offset );
	
	asia30->SetColor( 0xff953c53 );
	
	asia30->printf( kill_cloud.x + 100 + shake_x_offset, kill_cloud.y + 60 + shake_y_offset, HGETEXT_LEFT, "%i", enemies_killed );
	
	const int minutes = (int)timer.GetTime() / 60;
	const int seconds = (int)timer.GetTime() - minutes * 60;
	
	std::stringstream ss;
	
	ss << minutes << ( seconds < 10 ? ":0" : ":" ) << seconds;
	
	asia30->SetColor( 0xffb64d54 );
	asia30->Render( time_cloud.x + 50 + shake_x_offset, time_cloud.y + 5 + shake_y_offset, HGETEXT_LEFT, ss.str().c_str() );
	
	asia30->SetColor( 0xffad4853 );
	asia30->printf( rage_cloud.x + 50 + shake_x_offset, rage_cloud.y + 4 + shake_y_offset, HGETEXT_LEFT, "%i", rage );
}
