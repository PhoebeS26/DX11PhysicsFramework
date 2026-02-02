#pragma once
#include "Transform.h"
#include "Vector3.h"

class PhysicsModel
{
protected:

    Transform* _transform;
    Vector3 _velocity;

public:

    PhysicsModel(Transform* transform);   

    void Update(float deltaTime);         

    Vector3 GetVelocity() const { return _velocity; }
    void SetVelocity(const Vector3& velocity) { _velocity = velocity; }
};
