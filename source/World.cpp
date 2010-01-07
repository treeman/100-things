#include <boost/foreach.hpp>

#include "includes/System/Settings.hpp"
#include "includes/System/Hge.hpp"

#include "includes/World.hpp"

bool bullet_gone( boost::shared_ptr<Bullet> b )
{
	return b->CanKill() || 
		b->Info().pos.x < 0 || b->Info().pos.x > 800 ||
		b->Info().pos.y < 0 || b->Info().pos.y > 600;
}

bool alien_gone( boost::shared_ptr<Alien> a )
{
	return a->CanKill();
}

World::World() : dude( new Dude( this ) ), arial10( new hgeFont( "fnt/arial10.fnt" ) ), notifier( new Notifier() )
{
	const int w = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_width" ) );
	const int h = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_height" ) );
	
	sky_spr.reset( new hgeSprite( 0, 0, 0, w, h ) );
	sky_spr->SetColor( 0xff7d1eb4 );
	
	ground.reset( new Ground( 0, h - 40, w, 40 ) );
	
	InitDators();
	
	for( int i = 0; i < 100; ++i ) {
		boost::shared_ptr<Alien> a( new Alien( Vec2D( hge->Random_Int( 0, 800 ), hge->Random_Int( 0, 500 ))));
		aliens.push_back( a );
	}
}

void World::Update( float dt )
{
	dude->Update( dt );
	if( dude->Bounds().Collision( ground->Bounds() ) ) {
		dude->SetPos( Vec2D( dude->GetPos().x, ground->Bounds().y ) );
		Vec2D vel = dude->GetVel();
		if( vel.y > 0 ) {
			vel.y = 0;
			dude->SetVel( vel );
		}
	}

	BOOST_FOREACH( boost::shared_ptr<Bullet> b, bullets )
	{
		b->Update( dt );
	}
	
	BOOST_FOREACH( boost::shared_ptr<Alien> a, aliens )
	{
		a->Update( dt );
		
		BOOST_FOREACH( boost::shared_ptr<Bullet> b, bullets )
		{
			if( a->Bounds().Overlap( b->Bounds() ) ) {
				a->Kill();
				b->Kill();
			}
		}
	}
	
	bullets.erase( std::remove_if( bullets.begin(), bullets.end(), bullet_gone ), bullets.end() );
	aliens.erase( std::remove_if( aliens.begin(), aliens.end(), alien_gone ), aliens.end() );
	
	notifier->Update( dt );
}
void World::Render()
{
	//big owl hoho!
	sky_spr->Render( 0, 0 );
	
	dude->Render();
	
	BOOST_FOREACH( boost::shared_ptr<Bullet> b, bullets )
	{
		b->Render();
	}
	
	BOOST_FOREACH( boost::shared_ptr<Alien> a, aliens )
	{
		a->Render();
	}
	
	ground->Render();
	
	notifier->Render();
	
	RenderDebug();
}

void World::InitDators()
{
	show_bullets = true;
	showBullets.reset( new Dator<bool>( show_bullets ) );
	Settings::Get().RegisterVariable( "bullets_show", boost::weak_ptr<BaseDator>( showBullets ) );
	
	show_bounds = false;
	showBounds.reset( new Dator<bool>( show_bounds ) );
	Settings::Get().RegisterVariable( "collision_box_show", boost::weak_ptr<BaseDator>( showBounds ) );
}

void World::RenderDebug()
{
	if( show_bullets ) {
		arial10->SetColor( 0xffffffff );
		arial10->printf( 200, 6, HGETEXT_LEFT, "num_bullets: %i", bullets.size() );
		int n = 0;
		float line_height = arial10->GetHeight() + 2;
		
		for( Bullets::reverse_iterator rit = bullets.rbegin(); rit != bullets.rend() && n < 10; ++rit, ++n ) 
		{
			arial10->printf( 200, 20 + line_height * n, HGETEXT_LEFT, "vel: %.1f", 
			(*rit)->Info().vel.Length() );
		}
	}
	
	if( show_bounds ) {
		const Shape::Rect dbox = dude->Bounds();
		hgeh::render_rect( hge, dbox.x, dbox.y, dbox.x + dbox.w, dbox.y + dbox.h, 0xffffffff );
		
		const Shape::Rect gbox = ground->Bounds();
		hgeh::render_rect( hge, gbox.x, gbox.y, gbox.x + gbox.w, gbox.y + gbox.h, 0xffffffff );
		
		BOOST_FOREACH( boost::shared_ptr<Alien> a, aliens )
		{
			const Shape::Rect box = a->Bounds();
			hgeh::render_rect( hge, box.x, box.y, box.x + box.w, box.y + box.h, 0xffffffff );
		}
	}
}
