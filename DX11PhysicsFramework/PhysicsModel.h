#pragma once
#include "Transform.h"
#include "Vector3.h"

class PhysicsModel
{
protected:

    Transform* _transform;
    Vector3 _velocity;
    Vector3 _acceleration;
    bool _useAcceleration = false;

public:

    PhysicsModel(Transform* transform);   

    void Update(float deltaTime);         

    Vector3 GetVelocity() const { return _velocity; }
    void SetVelocity(const Vector3& velocity) { _velocity = velocity; }

    void SetAcceleration(const Vector3& accel) { _acceleration = accel; }
    Vector3 GetAcceleration() const { return _acceleration; }

    void SetUseAcceleration(bool useAccel) { _useAcceleration = useAccel; }
    bool GetUseAcceleration() const { return _useAcceleration; }

};
