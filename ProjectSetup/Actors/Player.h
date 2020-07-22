#pragma once
#pragma once
#include "Object/Actor.h"

class Player : public nc::Actor {
public:
	Player() = default;
	virtual ~Player() {}

	virtual eType GetType() { return nc::Actor::eType::PLAYER; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

protected:
	float m_thrust{ 200 };
	float m_rotationRate{ 0 };
	float m_fireRate{ 0.5f };
	float m_fireTimer{};
	nc::Vector2 m_velocity;
};