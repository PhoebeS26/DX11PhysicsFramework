#pragma once
#include "Transform.h"
#include "Vector3.h"

class SphereCollider; // forward declaration

class Collider
{
protected:
    Transform* _tf;

public:
    Collider(Transform* tf) : _tf(tf) {}

    virtual bool CollidesWith(Collider* other) = 0;
    virtual bool CollidesWith(SphereCollider* other) = 0;

    Vector3 GetPosition() const { return _tf->GetPosition(); }
};
