#include "FlyingEnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Damager.h"
#include "Engine.h"

using namespace nu;

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void FlyingEnemyController::Update(float dt)
{
	Vector2 velocity = m_physicsComponent->GetVelocity();

	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
		auto player = m_scene->GetActorByName<Actor>("PlayerPrototype");
		if (player)
		{
			Vector2 position = GetTransform().position;
			Vector2 playerPosition = player->GetTransform().position;
			Vector2 direction = playerPosition - position;

			m_rendererComponent->SetFlipH(direction.x + 0.0f);

			if (direction.Length() < 100.0f)
			{
				m_rendererComponent->Play("Attack");
				m_state = State::Attack;

				auto damager = Factory::Instance().Create<Damager>("DamagerPrototype");
				damager->SetDamage(5.0f);
				damager->SetPosition(GetTransform().position + Vector2{ 20.0f, 0.0f });
				damager->SetTag("EnemyDamager");
				m_scene->AddActor(std::move(damager));
			}

			m_physicsComponent->ApplyForce(direction.Normalized() * 500.0f);
		}
	}
			break;
		case CharacterBase::State::Attack:
			if (m_rendererComponent->IsAnimationDone())
			{
				m_state = State::Move;
				m_rendererComponent->Play("Idle");
			}
			break;
		case CharacterBase::State::Hit:
			break;
		case CharacterBase::State::Death:
			break;
		default:
			break;
	}

	CharacterBase::Update(dt);
}

void FlyingEnemyController::OnCollision(Actor* other)
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

void FlyingEnemyController::Read(const nu::json::value_t& value)
{
	CharacterBase::Read(value);
}
