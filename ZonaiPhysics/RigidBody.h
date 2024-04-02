#include "ZonaiMath.h"

namespace Math
{
	class Matrix4x4;
}

namespace Physics
{
	using namespace Zonai;
	using namespace Zonai::Math;

	struct MassData
	{
		float Mass;
		float invMass;
		Matrix4x4 inertia;
		Matrix4x4 invInertia;
	};

	class RigidBody
	{
	public:
		
		MassData massData;


	};
}