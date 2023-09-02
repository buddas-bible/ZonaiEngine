#pragma once


namespace ZonaiEngine
{
	class Transform;
	class Entity;
	class Collider;
	class Collision;

	class Component
	{
	public:
		Entity* entity;
		Transform* transform;


		virtual void Awake() noexcept;
		virtual void OnEnable() noexcept;

		virtual void Start() noexcept;

		virtual void FixedUpdate() noexcept;

		virtual void Update() noexcept;
		virtual void LateUpdate() noexcept;

		virtual void OnTriggerEnter(Collider*) noexcept;
		virtual void OnCollisionEnter(Collision*) noexcept;

		virtual void OnDisable() noexcept;
		virtual void OnDestroy() noexcept;
	};
}

