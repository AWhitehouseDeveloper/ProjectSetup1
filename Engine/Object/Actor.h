#pragma once
#include "../Math/Transform.h"
#include "../Math/Shape.h"
namespace nc{
	class Actor{
	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) // make sure to initialize m_transform and m_shape
			~Actor() {}

		bool Load(const std::string& filename);

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		Transform& GetTransform() // return the transform
			Shape& GetShape() // return the shape

	private:
		Transform m_transform;
		Shape m_shape;
	};
}