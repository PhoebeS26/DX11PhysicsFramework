#pragma once
#include "Transform.h"
#include "Vector3.h"

class Collider;

// Base class for physics objects
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
    bool _isGrounded;
    bool _useDrag = false;

    Collider* _collider = nullptr; 

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

    virtual void SetMass(float mass) { _mass = mass; }
    float GetMass() const { return _mass; }

    Vector3 GravityForce() const; 
    void SetUseGravity(bool use) { _useGravity = use; }
    bool GetUseGravity() const { return _useGravity; }
    void SetGrounded(bool grounded) { _isGrounded = grounded; }

    void SetUseFriction(bool use) { _useFriction = use; }
    bool GetUseFriction() const { return _useFriction; }
    Vector3 FrictionForce(); 

    void SetUseDrag(bool use) { _useDrag = use; }
    bool GetUseDrag() const { return _useDrag; }
    Vector3 DragForce(); 

    bool IsCollideable() const { return _collider != nullptr; }
    Collider* GetCollider() const { return _collider; }
    void SetCollider(Collider* collider) { _collider = collider; }

    void ApplyImpulse(const Vector3& impulse); 

    Vector3 GetPosition() const { return _transform->GetPosition(); }
    void SetPosition(const Vector3& pos) { _transform->SetPosition(pos); }
    float GetInverseMass() const { return (_mass != 0.0f) ? 1.0f / _mass : 0.0f; }
};
