#pragma once
#include "Actor.h"

struct BulletDesc : public nu::ActorDesc
{
    float speed = 1000.0f;
};

class Bullet : public nu::Actor
{
public:
    Bullet() = default;
    Bullet(const BulletDesc& BulletDesc) : Actor{ BulletDesc }, m_speed{ BulletDesc.speed } {}

    CLASS_PROTOTYPE(Bullet)

    void Read(const nu::json::value_t& value) override;
    float GetSpeed() const { return m_speed; }

    void Update(float dt) override;

private:
    int ammo = 0;
    float m_speed = 1000.0f;
};