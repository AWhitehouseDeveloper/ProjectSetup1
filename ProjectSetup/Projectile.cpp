#include "Projectile.h"
/*{ 600, 500 }
1
0
bullet.txt
400.0

*/
/*void Projectile::Update(float dt) {
	m_lifetime -= dt;
	m_destroy = (m_lifetime <= 0);

	nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, m_transform.angle);
	nc::Vector2 velocity = direction * m_thrust;
	m_transform.position = m_transform.position + (velocity * dt);

	g_particleSystem.Create(m_transform.position, m_transform.angle + nc::math::PI, 20, 1, nc::Color{ 1, 1, 1 }, 1, 100, 200);

	}*/
void Projectile::OnCollision(Actor* actor) {
	m_destroy = true;
}