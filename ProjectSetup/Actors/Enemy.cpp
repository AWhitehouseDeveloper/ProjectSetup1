#include "Enemy.h"
#include "Player.h"
#include <Math\Math.h>
#include "Object\Actor.h"
#include "Graphics\ParticleSystem.h"
#include <fstream>

bool Enemy::Load(const std::string& filename)
{
	bool success = false;
	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		//stream in actor data
		Actor::Load(stream);

		//stream in player data
		std::string line;
		std::getline(stream, line);
		m_thrust = stof(line);

		stream.close();
	}
	return success;
}

void Enemy::Update(float dt)
{
    //ENEMY
    nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
    m_transform.angle = std::atan2(direction.y, direction.x) + nc::math::DegreesToRadians(90.0f);
    nc::Vector2 enemyVelocity = direction.Normalized() * m_thrust;
    m_transform.position += enemyVelocity * dt;
	m_transform.Update();
}

void Enemy::OnCollision(Actor* actor) {
	if (actor->GetType() == eType::PROJECTILE) {
		m_destroy = true;

		nc::Color colors[] = { nc::Color::yellow, nc::Color::blue, nc::Color::green };
		nc::Color color = colors[rand() % 3];

		g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
	}
}
