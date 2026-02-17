#pragma once
#include "Collider.h"
#include "Vector3.h"

// Box collider that stays aligned with the axes
class AABBCollider : public Collider
{
    Vector3 halfExtents;  

public:

    // Create a box collider with a transform and size
    AABBCollider(Transform* tf, const Vector3& he) : Collider(tf), halfExtents(he) {}

    // Check collision with any other collider
    bool CollidesWith(Collider* other) override { return other->CollidesWith(this); }

    // Specific collision checks
    bool CollidesWith(SphereCollider* other) override;
    bool CollidesWith(AABBCollider* other) override;
    bool CollidesWith(PlaneCollider* other) override;

    // Get the box size
    Vector3 GetHalfExtents() const { return halfExtents; }
};
