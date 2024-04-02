#pragma once
#include "BaseDefine.h"

namespace Zonai
{
	class Transform;
	class Component;

	class Entity
	{
	public:
		std::wstring name;
		std::wstring tag;
		std::wstring layer;

		Transform* transform;
		std::vector<Component*> components;

		Component* AddComponent();
		Component* GetComponent();
	};
}

