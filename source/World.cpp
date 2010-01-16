#include <boost/foreach.hpp>

#include "includes/System/Settings.hpp"
#include "includes/System/Hge.hpp"

#include "includes/World.hpp"
#include "includes/SimpleEnemy.hpp"
#include "includes/GameWorld.hpp"

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

World::World( GameWorld *const _game_world ) : dude( new Dude( this ) ), arial10( new hgeFont( "fnt/arial10.fnt" ) ), notifier( new Notifier() ),
	level_loader( new LevelLoader( this ) ), shake_time( 0.3 ), num_shakes( 3 ), shake_decline( 0.75 ), max_x_shake( 10 ),
	max_y_shake( 8 ), shake_level( 0 ), shake_num( 0 ), enemies_killed( 0 ), stats_mod( 1.0 ), stats_mod_incr( 0.5 ),
	game_world( _game_world )
{
	const int w = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_width" ) );
	const int h = boost::lexical_cast<int>( Settings::Get().GetValue( "video_screen_height" ) );
	
	ground.reset( new Ground( -w / 2, h - 40, w * 2, 100 ) );
	
	InitDators();
	
	level_loader->LoadLevels( "levels.lua" );
	
	LoadLevel( level_loader->GetNextLevel() );
	
	background.reset( new ABackground() );
	
	AddListener( background.get() );
	
	shake_eff.Load( "sound/quake.wav" );
	
	//reset the shakes
	ShakeDone();
	
	total_timer.Start();
}

void World::PushBullet( boost::shared_ptr<Bullet> bullet )
{
	bullets.push_back( bullet );
	Shake( 0.1 );
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

	for( Bullets::iterator it = bullets.begin(); it != bullets.end(); ++it )
	{
		(*it)->Update( dt );
		
		for( Bullets::iterator it2 = bullets.begin(); it2 != bullets.end(); ++it2 )
		{
			if( (*it)->Info().target != (*it2)->Info().target && (*it)->Bounds().Collision( (*it2)->Bounds() ) )
			{
				(*it)->Kill();
				(*it2)->Kill();
			}
		}
		
		if( (*it)->Info().target != TARGET_ENEMY && (*it)->Bounds().Collision( dude->Bounds() ) ) {
			GameOver();
		}
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
		}
		if( a->HasReachedGoal() ) {
			curr_lvl->GoalReached( a );
		}
		
		if( a->Bounds().Collision( dude->Bounds() ) ) {
			GameOver();
		}
		
	
		a->Update( dt );
	
		BOOST_FOREACH( boost::shared_ptr<Bullet> b, bullets )
		{
			if( b->Info().target == TARGET_ENEMY && a->Bounds().Overlap( b->Bounds() ) ) {
				Frag( a, b );
			}
		}
	}
		
	BOOST_FOREACH( WorldListener *listener, listeners )
	{
		listener->SetDudePos( dude->GetPos() );
		listener->SetRageLevel( dude->GetRage() );
	}
	
	if( curr_lvl ) {
		curr_lvl->Update( dt );
	}
	
	bullets.erase( std::remove_if( bullets.begin(), bullets.end(), bullet_gone ), bullets.end() );
	
	enemies.erase( std::remove_if( enemies.begin(), enemies.end(), enemy_gone ), enemies.end() );
	
	notifier->Update( dt );
	background->Update( dt );
	
	UpdateShake();
	
	CheckLevelCompletion();
}

void World::Render()
{
	background->Render();
	
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

void World::AddListener( WorldListener *const listener )
{
	listeners.push_back( listener );
}

void World::LoadLevel( boost::shared_ptr<Level> lvl )
{
	curr_lvl = lvl;
	for( int i = enemies.size(); i < 100; ++i ) {
		AddEnemy();
	};
}
	
void World::CheckLevelCompletion()
{
	if( curr_lvl->IsComplete() ) {
		LevelCompleted();
	}
}
void World::LevelCompleted()
{
	if( level_loader->NoLevels() ) {
		GameCompleted();
	}
	else {
		LoadLevel( level_loader->GetNextLevel() );
	}
}
void World::GameCompleted()
{
	stats_mod += stats_mod_incr;
	level_loader->SetStatsMod( stats_mod );
}
void World::GameOver()
{
	game_world->GameOver( total_timer.GetTime(), enemies_killed );
}

void World::Frag( boost::shared_ptr<Enemy> enemy, boost::shared_ptr<Bullet> bullet )
{
	enemy->Kill();
	bullet->Kill();
	
	++enemies_killed;
	
	curr_lvl->EnemyDead( enemy );
	notifier->Add( "Eat my shorts" );
	
	dude->EnemyKilled();
	
	BOOST_FOREACH( WorldListener *listener, listeners )
	{
		listener->ReportEnemyKilled();
	}
	
	Shake( 0.6 );
	
	AddEnemy();
}

void World::AddEnemy()
{
	boost::shared_ptr<Enemy> enemy = curr_lvl->GetEnemy();
	if( enemy ) {
		enemies.push_back( enemy );
	}
}

void World::Shake( float level )
{
	if( level > shake_level ) {
		shake_level = level;
		shake_timer.Restart();
		
		const float max_sound = 100;
		const float min_sound = 10;
		
		const float vol = min_sound + ( max_sound - min_sound ) * level;
		
		hge->Effect_PlayEx( shake_eff, (int)vol );
	}
}

void World::UpdateShake()
{
	if( !shake_timer.IsStarted() ) return;

	const float shake_perc = shake_timer.GetTime() / shake_time;
	const float shake_num_time = shake_time / num_shakes;
	shake_num = (int)( shake_timer.GetTime() / shake_num_time );
	
	if( shake_perc >= 1.0 ) {
		ShakeDone();
		return;
	}
	
	const float shake_mod = std::pow( shake_decline, shake_num ) * shake_level;
	
	const float x_shake_distance = ( max_x_shake * 2 ) * shake_mod;
	const float y_shake_distance = ( max_y_shake * 2 ) * shake_mod;
	
	const float this_shake_perc = shake_perc * ( 1 - shake_num / num_shakes );
	
	const float x_pos = x_shake_distance * this_shake_perc;
	const float x_offset = ( shake_num % 2 ? max_x_shake - x_pos : -x_pos );
	
	const float y_pos = y_shake_distance * this_shake_perc;
	const float y_offset = ( shake_num % 2 ? max_y_shake - y_pos : -y_pos );
	
	OffsetScreen( x_offset, y_offset );
}

void World::OffsetScreen( float x_off, float y_off )
{
	background->SetShakeOffset( x_off, y_off );
	ground->SetShakeOffset( x_off, y_off );
	dude->SetShakeOffset( x_off, y_off );
	
	BOOST_FOREACH( boost::shared_ptr<Bullet> b, bullets )
	{
		b->SetShakeOffset( x_off, y_off );
	}
	
	BOOST_FOREACH( boost::shared_ptr<Enemy> e, enemies )
	{
		e->SetShakeOffset( x_off, y_off );
	}
	
	shake_x_offset = x_off;
	shake_y_offset = y_off;
}

void World::ShakeDone()
{
	shake_timer.Stop();
	shake_level = 0;
	shake_num = 0;
	shake_pos = 0;
	
	OffsetScreen( 0, 0 );
}

void World::InitDators()
{
	show_bullets = false;
	showBullets.reset( new Dator<bool>( show_bullets ) );
	Settings::Get().RegisterVariable( "bullets_show", boost::weak_ptr<BaseDator>( showBullets ) );
	
	show_bounds = false;
	showBounds.reset( new Dator<bool>( show_bounds ) );
	Settings::Get().RegisterVariable( "collision_box_show", boost::weak_ptr<BaseDator>( showBounds ) );
	
	show_shakeinfo = false;
	showShakeInfo.reset( new Dator<bool>( show_shakeinfo ) );
	Settings::Get().RegisterVariable( "shake_info_show", boost::weak_ptr<BaseDator>( showShakeInfo ) );
}

void World::RenderDebug()
{
	if( curr_lvl ) {
		curr_lvl->Render();
	}
	
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
		BOOST_FOREACH( boost::shared_ptr<Bullet> b, bullets )
		{
			const Shape::Rect box = b->Bounds();
			hgeh::render_rect( hge, box.x, box.y, box.x + box.w, box.y + box.h, 0xffffffff );
		}
		
	}
	
	if( show_shakeinfo ) {
		
		arial10->printf( 450, 50, HGETEXT_LEFT, "shake_lvl: %.1f, shake_num: %i, shake_timer: %.1f", 
			shake_level, shake_num, shake_timer.GetTime() );
		arial10->printf( 450, 60, HGETEXT_LEFT, "x_off: %.2f y_off %.2f", shake_x_offset, shake_y_offset );
	}
	
	arial10->printf( 450, 100, HGETEXT_LEFT, "num_levels: %i", level_loader->GetNumLevels() );
}
