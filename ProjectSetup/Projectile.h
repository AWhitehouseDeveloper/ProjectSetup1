#pragma once
#include <Object\Actor.h>
class Projectile : public nc::Actor
{
	Projectile() = default;
	virtual ~Projectile() {}

	virtual eType GetType() { return eType::PROJECTILE; }

	//virtual bool Load()
	void OnCollision(Actor* actor);

protected:
	float m_thrust{ 0 };
	float m_llifetime{ 0 };
};

