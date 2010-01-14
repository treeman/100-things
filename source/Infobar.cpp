#include "includes/Infobar.hpp"
#include "includes/System/Log.hpp"

Infobar::Infobar() : fnt( new hgeFont( "fnt/bannerlight14.fnt" ) ), rage( 0 ), enemies_killed( 0 ),
	render_y( 567 )
{
	timer.Start();
}
	
void Infobar::SetRageLevel( float rage_perc )
{
	rage = rage_perc;
}
void Infobar::ReportEnemyKilled()
{
	++enemies_killed;
}
void Infobar::Update( float dt )
{
	
}
void Infobar::Render()
{
	fnt->SetColor( 0xffffffff );
	
	fnt->printf( 5, render_y, HGETEXT_LEFT, "Rage: %.0f", rage );
	
	fnt->printf( 120, render_y, HGETEXT_LEFT, "Time alive: %.1f, Enemies Killed: %i", timer.GetTime(), enemies_killed );
}
