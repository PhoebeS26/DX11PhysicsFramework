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

    Vector3 _netForce;
    float _mass = 1.0f;

    bool _useGravity = false;
    bool _useFriction = false;


public:

    PhysicsModel(Transform* transform, float mass);   

    virtual void Update(float deltaTime);      
    void AddForce(const Vector3& force);

    Vector3 GetVelocity() const { return _velocity; }
    void SetVelocity(const Vector3& velocity) { _velocity = velocity; }

    void SetAcceleration(const Vector3& accel) { _acceleration = accel; }
    Vector3 GetAcceleration() const { return _acceleration; }

    void SetUseAcceleration(bool useAccel) { _useAcceleration = useAccel; }
    bool GetUseAcceleration() const { return _useAcceleration; }

    void SetMass(float mass) { _mass = mass; }
    float GetMass() const { return _mass; }

    Vector3 GravityForce() const;
    void SetUseGravity(bool use) { _useGravity = use; }
    bool GetUseGravity() const { return _useGravity; }



};
