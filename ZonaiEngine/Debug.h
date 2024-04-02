#pragma once

namespace Zonai::Math
{
	class Matrix4x4;
	class Vector3D;
	class Vector4D;
	class Quaternion;
}

namespace Zonai::Debug
{
	class Debug
	{
	public:
		static void DrawLine(
			const Zonai::Math::Vector3D& _point1, 
			const Zonai::Math::Vector3D& _point2,
			const Zonai::Math::Vector4D& _color);
		
		static void DrawQuad(
			const Zonai::Math::Vector3D& _position, 
			const Zonai::Math::Quaternion& _rotation, 
			const Zonai::Math::Vector3D& _scale,
			const Zonai::Math::Vector4D& _color);

		static void DrawSphere(
			const Zonai::Math::Vector3D& _position,
			const Zonai::Math::Quaternion& _rotation,
			const Zonai::Math::Vector3D& _scale,
			const Zonai::Math::Vector4D& _color);

		static void DrawCube(
			const Zonai::Math::Vector3D& _position,
			const Zonai::Math::Quaternion& _rotation,
			const Zonai::Math::Vector3D& _scale,
			const Zonai::Math::Vector4D& _color);

		static void DebugRender();
	};
}
