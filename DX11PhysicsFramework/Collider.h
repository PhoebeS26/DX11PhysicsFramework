#pragma once
#include "Transform.h"
#include "Vector3.h"

class SphereCollider;
class AABBCollider;
class PlaneCollider;

class Collider
{
protected:
    Transform* _tf;

public:
    Collider(Transform* tf) : _tf(tf) {}

    // Generic double-dispatch functions
    virtual bool CollidesWith(Collider* other) = 0;
    virtual bool CollidesWith(SphereCollider* other) = 0;
    virtual bool CollidesWith(AABBCollider* other) = 0;
    virtual bool CollidesWith(PlaneCollider* other) = 0;

    Vector3 GetPosition() const { return _tf->GetPosition(); }
};
