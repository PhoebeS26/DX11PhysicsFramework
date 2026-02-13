#include "PhysicsModel.h"

// Constructor
PhysicsModel::PhysicsModel(Transform* transform, float mass)
{
    _mass = mass;

    _transform = transform;
    _velocity = Vector3(0.0f, 0.0f, 0.0f); 
    _acceleration = Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsModel::Update(float deltaTime)
{
    if (!_transform) return;

    Vector3 pos = _transform->GetPosition();

    if (pos.y <= 0.5f)
    {
        _transform->SetPosition(Vector3(pos.x, 0.5f, pos.z));
        _velocity.y = 0; 
        _useFriction = true;
    }
    else
    {
        _useGravity = true; 
        _useFriction = false;
    }

    // Apply gravity force
    if (_useGravity)
    {
        AddForce(GravityForce());
    }

    AddForce(DragForce());

    if (_useFriction)
    {
        AddForce(FrictionForce());
    }

    // F = M * A ? A = F / M
    _acceleration += _netForce / _mass;

    // Velocity update
    _velocity += _acceleration * deltaTime;

    // Position update
    Vector3 position = _transform->GetPosition();
    position += _velocity * deltaTime;
    _transform->SetPosition(position);

    // Reset per frame
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
    if (speed <= tol) return Vector3(0, 0, 0); // don't apply if almost stopped

    Vector3 frictionDir = _velocity;
    frictionDir.Normalize();
    frictionDir.Reverse(); // opposite to current motion

    const float kineticFriction = 0.6f;        // kinetic friction coefficient
    const float gravityAcceleration = 9.81f;
    float normalForce = _mass * gravityAcceleration;
    float frictionMagnitude = kineticFriction * normalForce;

    return frictionDir * frictionMagnitude;
}

Vector3 PhysicsModel::DragForce() 
{
    float speed = _velocity.Magnitude();
    if (speed <= tol) return Vector3(0, 0, 0);  // no drag if practically stopped

    Vector3 dragDir = _velocity;
    dragDir.Normalize();
    dragDir.Reverse();  // opposite to velocity

    const float airDensity = 1.225f;
    const float dragCoefficient = 0.47f; 
    const float area = 1.0f;

    float dragMagnitude = 0.5f * airDensity * dragCoefficient * area * speed * speed;

    return dragDir * dragMagnitude;
}




