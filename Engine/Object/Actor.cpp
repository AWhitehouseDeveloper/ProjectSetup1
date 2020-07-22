#include "pch.h"
#include "Actor.h"
#include "../Math/Transform.h"
#include <iostream>

namespace nc {
	bool nc::Actor::Load(const std::string& filename)
	{
		bool success = false;
		std::ifstream stream(filename);
		if (stream.is_open()) {
			Load(stream);
			success = true;
			stream.close();
		}
		return success;
	}

	void Actor::Load(std::istream& stream)
	{
		stream >> m_transform;
		std::string shapename;
		std::getline(stream, shapename);
		m_shape.Load(shapename);
	}

	void nc::Actor::Update(float dt)
	{
		//nothing
	}

	void nc::Actor::Draw(Core::Graphics& graphics)
	{
		//draw shape using transform
		GetShape().Draw(graphics, GetTransform());
	}
	float Actor::GetRadius()
	{
		return m_shape.GetRadius() * m_transform.scale;
	}
}
