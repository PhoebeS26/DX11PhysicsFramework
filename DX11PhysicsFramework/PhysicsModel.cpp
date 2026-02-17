#include "PhysicsModel.h"
#include "PlaneCollider.h"
#include "Debug.h"
#include "Collider.h"

// Constructor
PhysicsModel::PhysicsModel(Transform* transform, float mass)
{
    _mass = mass;
    _transform = transform;

    _velocity = Vector3(0.0f, 0.0f, 0.0f);
    _acceleration = Vector3(0.0f, 0.0f, 0.0f);
    _netForce = Vector3(0.0f, 0.0f, 0.0f);

    _isGrounded = false;
    _useFriction = true;
}

void PhysicsModel::Update(float deltaTime)
{
    if (!_transform)
    {
        return;
    }
    if (_mass <= 0.0f)
    {
        return;
    }

    // Apply gravity if enabled
    if (_useGravity)
    {
        AddForce(GravityForce());
    }

    // Apply drag / air resistance if enabled
    if (_useDrag)
    {
        AddForce(DragForce());
    }

    // Apply friction if grounded
    if (_useFriction && _isGrounded)
    {
        AddForce(FrictionForce());
    }

    // Integrate acceleration
    _acceleration += _netForce / _mass;
    _velocity += _acceleration * deltaTime;

    // Stop tiny jitter from friction
    const float velTol = 0.001f;
    if (_velocity.Magnitude() < velTol)
    {
        _velocity = Vector3(0, 0, 0);
    }

    // Update position
    _transform->SetPosition(_transform->GetPosition() + _velocity * deltaTime);

    // Reset forces / acceleration for next frame
    _netForce = Vector3(0, 0, 0);
    _acceleration = Vector3(0, 0, 0);
}

void PhysicsModel::AddForce(const Vector3& force)
{
    _netForce += force;
}

Vector3 PhysicsModel::GravityForce() const
{
    return Vector3(0.0f, -9.81f * _mass, 0.0f);
}

Vector3 PhysicsModel::FrictionForce()
{
    float speed = _velocity.Magnitude();

    if (!_isGrounded)
    {
        return Vector3(0, 0, 0);
    }

    const float tol = 0.01f;
    if (speed <= tol)
    {
        return Vector3(0, 0, 0);
    }

    Vector3 frictionDir = _velocity;
    frictionDir.Normalize();
    frictionDir.Reverse(); 

    const float kineticFriction = 0.6f;
    const float gravityAccel = 9.81f;

    float normalForce = _mass * gravityAccel;
    float frictionMag = kineticFriction * normalForce;

    // prevent overcorrection for low speeds
    if (frictionMag * 0.016f > speed)
    {
        frictionMag = speed / 0.016f;
    }


    return frictionDir * frictionMag;
}

Vector3 PhysicsModel::DragForce()
{
    float speed = _velocity.Magnitude();
    if (speed <= tol)
    {
        return Vector3(0, 0, 0);
    }

    Vector3 dragDir = _velocity;
    dragDir.Normalize();
    dragDir.Reverse();

    const float airDensity = 1.225f;
    const float dragCoeff = 0.47f;
    const float area = 1.0f;

    float dragMag = 0.5f * airDensity * dragCoeff * area * speed * speed;

    return dragDir * dragMag;
}

void PhysicsModel::ApplyImpulse(const Vector3& impulse)
{
    _velocity += impulse;
}
