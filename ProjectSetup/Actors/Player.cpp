#include "Player.h"
#include <Math\Math.h>
#include "Graphics/ParticleSystem.h"
#include <fstream>

bool Player::Load(const std::string& filename)
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

		std::getline(stream, line);
		m_rotationRate = stof(line);

		stream.close();
	}
	return success;
}

void Player::Update(float dt)
{
    m_fireTimer += dt;

    if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate) {
        m_fireTimer = 0;
        
    }

    //POSITION
    nc::Vector2 force{ 0, 0 };
    if (Core::Input::IsPressed('W')) {
        force = nc::Vector2::forward * m_thrust;
    }
    force = nc::Vector2::Rotate(force, m_transform.angle);

    m_velocity = m_velocity + (force * dt);
    m_velocity = m_velocity * 0.99f;
    m_transform.position += m_velocity * dt;

    //ROTATION
    if (Core::Input::IsPressed('A')) { m_transform.angle -= (nc::math::DegreesToRadians(360.0f) * dt); }
    if (Core::Input::IsPressed('D')) { m_transform.angle += (nc::math::DegreesToRadians(360.0f) * dt); }

    //WRAP AROUND INSTEAD OF CLAMP
    if (m_transform.position.x > 800) m_transform.position.x = 0;
    if (m_transform.position.x < 0) m_transform.position.x = 800;
    if (m_transform.position.y > 600) m_transform.position.y = 0;
    if (m_transform.position.y < 0) m_transform.position.y = 600;
    if (force.LengthSqr() > 0) {
        g_particleSystem.Create(m_transform.position, m_transform.angle + nc::math::PI, 20, 1, nc::Color{ 1, 1, 1 }, 1, 100, 200);
    }

    m_transform.Update();
}
