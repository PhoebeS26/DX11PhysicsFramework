#pragma once
#include "Collider.h"
#include "Vector3.h"
#include "SphereCollider.h"

class AABBCollider : public Collider
{
    Vector3 halfExtents;

public:
    AABBCollider(Transform* tf, const Vector3& he) : Collider(tf), halfExtents(he) {
    }

    // Collision overrides
    bool CollidesWith(Collider* other) override;
    bool CollidesWith(SphereCollider* other) override;

    const Vector3& GetHalfExtents() const { return halfExtents; }
};
