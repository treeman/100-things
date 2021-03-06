#ifndef SIMPLENEMY_HPP_INCLUDED
#define SIMPLENEMY_HPP_INCLUDED

#include "System/ShuffleBag.hpp"
#include "System/Timer.hpp"

#include "Enemy.hpp"
#include "Weapon.hpp"

class PippiAfro : public Enemy {
public:
	PippiAfro( Vec2D pos );
	
	Shape::Rect Bounds();
	EnemyType Type() {
		return ENEMY_PIPPI;
	}

	bool HasReachedGoal();
	
	void Update( float dt );
	void Render();
private:
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	
	const float max_acc;
	const float max_vel;
	
	const float w, h;
};

class MutantAfro : public Enemy {
public:
	MutantAfro( Vec2D pos );
	
	Shape::Rect Bounds();
	EnemyType Type() {
		return ENEMY_MUTANT;
	}

	bool HasReachedGoal();
	
	void Update( float dt );
	void Render();
private:
	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	
	const float max_acc;
	const float max_vel;
	
	const float w, h;
};

class AfroWorm : public Enemy {
public:
	AfroWorm( Vec2D pos, float ground_y );
	
	Shape::Rect Bounds();
	EnemyType Type() {
		return ENEMY_WORM;
	}

	bool HasReachedGoal();
	
	void SetTargetPos( Vec2D target );
	
	void Update( float dt );
	void Render();
private:
	void FaceLeft();
	void FaceRight();

	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	
	const float max_acc;
	const float max_vel;
	
	const float w, h;
	
	const float ground_y;
};

class World;

class ShooterAfro : public Enemy {
public:
	ShooterAfro( Vec2D pos, World *const world );
	
	Shape::Rect Bounds();
	EnemyType Type() {
		return ENEMY_SHOOTER;
	}

	bool HasReachedGoal();
	
	void SetPos( Vec2D p );
	
	void Update( float dt );
	void Render();
private:
	void Shoot();
	void ResetShootDelay();

	TexObj tex;
	boost::shared_ptr<hgeSprite> spr;
	
	const float max_acc;
	const float max_vel;
	
	const float w, h;
	
	Timer shoot_time;
	float delay;
	
	ShuffleBag<float> delay_bag;
	
	boost::shared_ptr<Weapon> weapon;
	
	World *const world;
};

#endif
