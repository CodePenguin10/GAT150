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
    Bullet(const nu::Transform& transform) : Actor{ transform } {}
    Bullet(const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model } {}

    void Update(float dt) override;

private:
    int ammo = 0;
    float m_speed = 1000.0f;
};