#pragma once
#include "Collider.h"

class AABBCollider : public Collider
{
    Vector3 halfExtents;

public:
    AABBCollider(Transform* tf, const Vector3& he) : Collider(tf), halfExtents(he) {}

    bool CollidesWith(Collider* other) override { return other->CollidesWith(this); }
    bool CollidesWith(SphereCollider* other) override;
    bool CollidesWith(AABBCollider* other) override;
    bool CollidesWith(PlaneCollider* other) override;


    Vector3 GetHalfExtents() const { return halfExtents; }
};
