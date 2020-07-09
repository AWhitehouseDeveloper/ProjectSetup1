#pragma once
#include "Vector2.h"

namespace nc {
	namespace math {
		const float PI = 3.141592f;
		const float TWO_PI = PI * 2;
		const float HALF_PI = PI * 0.5f;
		const float RAD_TO_DEG = (180.0f / PI);
		const float DEG_TO_RAD = (PI / 180.0f);

		inline float RadiansToDegrees(float radians) {
			return radians * (RAD_TO_DEG);
		}

		inline float DregreesToRadians(float degrees) {
			return degrees * (DEG_TO_RAD);
		}

		template <typename T>
		inline T Clamp(T v, T min, T max) {
			if (v < min) v = min;
			if (v > max) v = max;
			return v;
		}

		template <>
		inline nc::Vector2 Clamp<Vector2>(Vector2 v, Vector2 min, Vector2 max) {
			v.x = Clamp(v.x, min.x, max.x);
			v.y = Clamp(v.y, min.y, max.y);
			return v;
		}

		template <typename T>
		inline T Lerp(T a, T b, float t) {
			t = Clamp(t, 0.0f, 1.0f);
			return (a + ((b - a) * t));
		}
	}
}