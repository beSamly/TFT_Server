#pragma once

namespace PhysicsEngine {
	class Vector3
	{
	public:
		float x;
		float y;
		float z;

	public:
		Vector3() : x(0), y(0), z(0) {};
		Vector3(float x, float z) : x(x), y(y), z(z) {};
	};
}
