#pragma once
#include "Object/Actor.h"

class Enemy : public nc::Actor {
public:
	Enemy() = default;
	virtual ~Enemy() {}

	virtual eType GetType() { return nc::Actor::eType::ENEMY; }
	
	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	void OnCollision(Actor* actor);

	void SetThrust(float thrust) { m_thrust = thrust; }

	void SetTarget(Actor* actor) { m_target = actor; }
protected:
	float m_thrust{ 0.0f };
	Actor* m_target{ nullptr };
};