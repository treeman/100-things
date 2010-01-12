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

bool enemy_gone( boost::shared_ptr<Enemy> a )
{
	return a->CanKill();
}

bool enemy_out_of_bounds( boost::shared_ptr<Enemy> a )
{
	return a->GetPos().x < 0 || a->GetPos().x > 800 || a->GetPos().y < 0 || a->GetPos().y > 600;
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
		boost::shared_ptr<Enemy> a( new Enemy( Vec2D( 8 * i, 0 ) ) );
		enemies.push_back( a );
	}
}

void World::Update( float dt )
{
	const int screen_w = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_width" ) );
	
	dude->Update( dt );
	if( dude->Bounds().Collision( ground->Bounds() ) ) {
		dude->SetPos( Vec2D( dude->GetPos().x, ground->Bounds().y ) );
		Vec2D vel = dude->GetVel();
		if( vel.y > 0 ) {
			vel.y = 0;
			dude->SetVel( vel );
		}
	}
	if( dude->GetPos().x < 0 ) {
		dude->SetPos( Vec2D( 0, dude->GetPos().y ) );
		
		Vec2D vel = dude->GetVel();
		if( vel.x < 0 ) {
			vel.x = 0;
			dude->SetVel( vel );
		}
	}
	else if( dude->GetPos().x + dude->Bounds().w > screen_w ) {
		dude->SetPos( Vec2D( screen_w - dude->Bounds().w, dude->GetPos().y ) );
		
		Vec2D vel = dude->GetVel();
		if( vel.x > 0 ) {
			vel.x = 0;
			dude->SetVel( vel );
		}
	}

	BOOST_FOREACH( boost::shared_ptr<Bullet> b, bullets )
	{
		b->Update( dt );
	}
	
	BOOST_FOREACH( boost::shared_ptr<Enemy> a, enemies )
	{
		if( enemy_out_of_bounds( a ) ) {
			RandomizeTargetPos( a );
		}
		if( a->Bounds().Collision( ground->Bounds() ) ) {
			a->SetPos( Vec2D( a->GetPos().x, ground->Bounds().y - a->Bounds().h ) );
			Vec2D vel = a->GetVel();
			if( vel.y > 0 ) {
				vel.y = -0;
				a->SetVel( vel );
			}
			RandomizeTargetPos( a );
		}
		
		a->Update( dt );
		
		BOOST_FOREACH( boost::shared_ptr<Bullet> b, bullets )
		{
			if( a->Bounds().Overlap( b->Bounds() ) ) {
				a->Kill();
				b->Kill();
				Frag();
			}
		}
	}
	
	bullets.erase( std::remove_if( bullets.begin(), bullets.end(), bullet_gone ), bullets.end() );
	enemies.erase( std::remove_if( enemies.begin(), enemies.end(), enemy_gone ), enemies.end() );
	
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
	
	BOOST_FOREACH( boost::shared_ptr<Enemy> a, enemies )
	{
		a->Render();
	}
	
	ground->Render();
	
	notifier->Render();
	
	RenderDebug();
}

bool World::CanDudeJump()
{
	Shape::Rect dude_box = dude->Bounds();
	//make it a little easier to jump :)
	dude_box.h += 4;
	return dude_box.Collision( ground->Bounds() );
}

void World::RandomizeTargetPos( boost::shared_ptr<Enemy> a )
{
	a->SetTargetPos( Vec2D( hge->Random_Int( 0, 800 ), hge->Random_Int( 0, 500 ) ) );
}

void World::Frag()
{
	notifier->Add( "Eat my shorts" );
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
		
		BOOST_FOREACH( boost::shared_ptr<Enemy> a, enemies )
		{
			const Shape::Rect box = a->Bounds();
			hgeh::render_rect( hge, box.x, box.y, box.x + box.w, box.y + box.h, 0xffffffff );
		}
	}
}
