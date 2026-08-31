#include "Bullet.h"
#include "Math/MathUtility.h"
#include "Components/PhysicsComponent.h"
#include "Engine.h"

FACTORY_REGISTER(Bullet)

void Bullet::Update(float dt)
{
	nu::PhysicsComponent* physicsComponent = GetComponent<nu::PhysicsComponent>();
	if (physicsComponent)
	{
		nu::Vector2 forward{ 1, 0 }; // ->
		nu::Vector2 force = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;

		physicsComponent->SetVelocity(force);
		//physicsComponent->ApplyTorque(rotate);
	}

	Actor::Update(dt);
}