#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
    float radius = 1.0f;

public:
    SphereCollider(Transform* tf, float r) : Collider(tf), radius(r) {}

    bool CollidesWith(Collider* other) override { return other->CollidesWith(this); }
    bool CollidesWith(SphereCollider* other) override;
    bool CollidesWith(AABBCollider* other) override;

    float GetRadius() const { return radius; }
};
