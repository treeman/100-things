#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"
#include "System/Vec2D.hpp"
#include "System/Shape.hpp"
#include "System/Settings.hpp"

#include "Shakeable.hpp"

enum EnemyType {
	ENEMY_MUTANT,
	ENEMY_PIPPI,
	ENEMY_SHOOTER,
	ENEMY_WORM
};

class Enemy : public Shakeable {
public:
	Enemy( Vec2D pos );
	virtual ~Enemy() { }
	
	virtual Shape::Rect Bounds() = 0;
	
	virtual EnemyType Type() = 0;
	
	bool CanKill() const {
		return can_kill;
	}
	void Kill() {
		can_kill = true;
	}
	
	virtual void SetPos( Vec2D p ) {
		pos = p;
	}
	Vec2D GetPos() const {
		return pos;
	}
	
	virtual void SetVel( Vec2D v ) {
		vel = v;
	}
	Vec2D GetVel() const {
		return vel;
	}
	
	virtual void SetTargetPos( Vec2D target ) {
		target_pos = target;
	}
	Vec2D GetTargetPos() const {
		return target_pos;
	}
	
	virtual void SetStatsMod( float m ) {
		stats_mod = m;
	}
	
	virtual bool HasReachedGoal() = 0;
	
	virtual void Update( float dt ) = 0;
	virtual void Render() = 0;
protected:
	Vec2D acc;
	Vec2D vel;
	Vec2D pos;
	
	Vec2D target_pos;
	
	bool can_kill;
	float speed_mod;
	
	float stats_mod;
	
	HgeObj hge;
	
	void RenderDebug();
	
	boost::shared_ptr<hgeFont> fnt;
	bool show_debug;
	boost::shared_ptr<Dator<bool> > showDebug;
};

#endif
