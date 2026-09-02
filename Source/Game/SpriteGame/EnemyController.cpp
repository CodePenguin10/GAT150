#include "EnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Framework/Scene.h"
#include "Engine.h"
#include "Damager.h"

using namespace nu;

FACTORY_REGISTER(EnemyController)

void EnemyController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void EnemyController::Update(float dt)
{
	Vector2 velocity = m_physicsComponent->GetVelocity();

	switch (m_state)
	{
	case CharacterBase::State::Move:
	{

		float dir = 0.0f;
		auto player = m_scene->GetActorByName<Actor>("PlayerPrototype");
		if (player)
		{
			Vector2 position = GetTransform().position;
			Vector2 playerPosition = player->GetTransform().position;

			if (playerPosition.x < position.x)
			{
				dir = -1.0f;
			}
			else
			{
				dir = 1.0f;
			}
		}

		if (dir != 0)
		{
			velocity.x = dir * 70.0f;
			m_rendererComponent->Play("Run");
		}
		else
		{
			m_rendererComponent->Play("Idle");
		}
		m_rendererComponent->SetFlipH(dir < 0);

	}
		break;
	case CharacterBase::State::Attack:
		break;
	case CharacterBase::State::Hit:
		break;
	case CharacterBase::State::Death:
		break;
	default:
		break;
	}


		m_physicsComponent->SetVelocity(velocity);

	CharacterBase::Update(dt);
}

void EnemyController::OnCollision(Actor* other)
{
	if (other->GetTag() == "PlayerDamager")
	{
		other->SetDestroyed();

		m_state = State::Hit;
		m_rendererComponent->Play("Hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager)
		{
			m_health -= damager->GetDamage();
		}
		else
		{
			m_health -= 1.0f;
		}
		m_health -= 1.0f;
		if (m_health <= 0.0f)
		{
			SetDestroyed();
		}
	}
}

void EnemyController::Read(const nu::json::value_t& value)
{
	CharacterBase::Read(value);
}
