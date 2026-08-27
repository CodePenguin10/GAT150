#pragma once
#include "Framework/Actor.h"

struct EnemyDesc : public nu::ActorDesc
{
    float speed{ 0.0f };
    float health{ 1.0f };
};

class Enemy : public nu::Actor
{
public:
    Enemy() = default;
    Enemy(const EnemyDesc& enemyDesc) : Actor{ enemyDesc }, m_speed{ enemyDesc.speed }, m_health{ enemyDesc.health } {}

    void Read(const nu::json::value_t& value) override;
    float GetSpeed() const { return m_speed; }

    void Update(float dt) override;
    void OnCollision(Actor* other) override;

private:
    int ammo = 0;
    float m_health = 1.0f;
    float m_speed = 1000.0f;
};