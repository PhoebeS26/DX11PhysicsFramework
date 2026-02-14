#pragma once
#include "Collider.h"
#include "PhysicsModel.h"


class PlaneCollider : public Collider
{
    Vector3 normal;
    float distance;

public:

    PlaneCollider(Transform* tf, Vector3 n, float d) : Collider(tf), normal(n), distance(d)
    {
        normal.Normalize(); 
    }

    bool CollidesWith(Collider* other) override { return other->CollidesWith(this); }

    bool CollidesWith(SphereCollider* other) override;
    bool CollidesWith(AABBCollider* other) override;
    bool CollidesWith(PlaneCollider* other) override { return false; }

    Vector3 GetNormal() const { return normal; }
    float GetDistance() const { return distance; }

    void ResolveCollision(PhysicsModel* objPhysics);

};
