#include "Enemy.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Components/PhysicsComponent.h"

#include <iostream>

FACTORY_REGISTER(Enemy)

using namespace nu;

void Enemy::Update(float dt)
{
	Actor* player = m_scene->GetActorByName<Actor>("PlayerPrototype");
	if (player)
	{
		nu::PhysicsComponent* physicsComponent = GetComponent<nu::PhysicsComponent>();
		if (physicsComponent)
		{
			nu::Vector2 forward{ 1, 0 }; // ->
			nu::Vector2 force = forward.Rotate(m_transform.rotation * DegToRad) * m_speed;

			physicsComponent->ApplyForce(force);
		}

		nu::Vector2 direction = player->GetTransform().position - m_transform.position;
		float rotation = direction.Angle();
		physicsComponent->SetRotation(rotation * nu::RadToDeg);
	}

	//particle system
	nu::Particle particle;

	nu::Vector2 offset{ -20.0f, 0.0f };
	offset = offset.Rotate(m_transform.rotation * nu::DegToRad);

	particle.position = m_transform.position + offset;
	particle.color = { 1.0f, 1.0f, 0.0f };
	particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
	particle.velocity = nu::Vector2{ nu::RandomFloat(-30.0f, -100.0f), 0.0f }.Rotate((m_transform.rotation + nu::RandomInt(-10, 10)) * nu::DegToRad);

	nu::Engine::Get().GetPS().AddParticle(particle);

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
	if (other->GetTag() == "PlayerBullet")
	{
		m_health -= 1.0f;

		if (m_health <= 0)
		{
			SetDestroyed();
			other->SetDestroyed();
		}

		((SpaceGame*)m_scene->GetGame())->AddPoints(100);

		for (int i = 0; i < 100; i++)
		{
			nu::Particle particle;
			particle.position = m_transform.position;
			particle.color = { 1.0f, 1.0f, 1.0f };
			particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
			particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

			nu::Engine::Get().GetPS().AddParticle(particle);
		}
	}
}

void Enemy::Read(const nu::json::value_t& value)
{
	Actor::Read(value);

	JSON_READ_NAME(value, "speed", m_speed);
}
