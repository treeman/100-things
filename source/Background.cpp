#include <boost/foreach.hpp>
#include <sstream>

#include "includes/System/Settings.hpp"
#include "includes/Background.hpp"

const float sky_height = 600;

ABackground::ABackground() : asia30( new hgeFont( "fnt/asiaextended30.fnt" ) ), 
	asia23( new hgeFont( "fnt/asiaextended23.fnt" ) ), rage( 0 ), enemies_killed( 0 )
{
	const int screen_w = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_width" ) );
	
	sky_spr.reset( new hgeSprite( 0, 0, 0, screen_w, sky_height ) );
	
	sky_spr->SetColor( 0xFFc35454, 0 );
	sky_spr->SetColor( 0xFFc35454, 1 );
	sky_spr->SetColor( 0xFF3e0e50, 2 );
	sky_spr->SetColor( 0xFF3e0e50, 3 );
	
	Cloud c;
	
	c.tex.Load( "gfx/cloud1.png" );
	c.spr.reset( new hgeSprite( c.tex, 0, 0, 177, 100 ) );
	c.x = 10; c.y = 40;
	clouds.push_back( c );
	
	c.tex.Load( "gfx/cloud2.png" );
	c.spr.reset( new hgeSprite( c.tex, 0, 0, 216, 100 ) );
	c.x = 400; c.y = 80;
	clouds.push_back( c );
	
	c.tex.Load( "gfx/cloud3.png" );
	c.spr.reset( new hgeSprite( c.tex, 0, 0, 263, 100 ) );
	c.x = 150; c.y = 130;
	clouds.push_back( c );
	
	sign_tex.Load( "gfx/sign.png" );
	sign_spr.reset( new hgeSprite( sign_tex, 0, 0, 120, 130 ) );
	
	timer.Start();
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
	
}
void ABackground::Render()
{
	sky_spr->Render(0,0);
	
	BOOST_FOREACH( Cloud c, clouds )
	{
		c.spr->SetColor( 0x99610303 );
		c.spr->Render( c.x, c.y );
	}
	
//	sign_spr->SetColor( 0xff5d0623 );
//	sign_spr->Render( 217, 440 );
	
//	asia30->SetColor( 0xff420011 );
//	asia30->SetRotation( -(math::PI / 5) );
//	asia30->Render( 238, 501, HGETEXT_LEFT, "R" );
//	asia30->Render( 252, 490, HGETEXT_LEFT, "a" );
//	asia30->Render( 263, 480, HGETEXT_LEFT, "g" );
//	asia30->Render( 273, 477, HGETEXT_LEFT, "e" );
//	
//	asia23->SetColor( 0xff420011 );
//	asia23->SetRotation( -(math::PI / 6) );
//	asia23->printf( 283, 458, HGETEXT_LEFT, "%i", rage );
//	asia30->SetRotation( 0 );
	
	asia30->SetColor( 0xff953c53 );
	
	asia30->printf( clouds[2].x + 100, clouds[2].y + 60, HGETEXT_LEFT, "%i", enemies_killed );
	
	const int minutes = (int)timer.GetTime() / 60;
	const int seconds = (int)timer.GetTime() - minutes * 60;
	
	std::stringstream ss;
	
	ss << minutes << ( seconds < 10 ? ":0" : ":" ) << seconds;
	
	asia30->SetColor( 0xffb64d54 );
	asia30->Render( clouds[0].x + 50, clouds[0].y + 5, HGETEXT_LEFT, ss.str().c_str() );
	
	asia30->SetColor( 0xffad4853 );
	asia30->printf( clouds[1].x + 50, clouds[1].y + 5, HGETEXT_LEFT, "%i", rage );
}
