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
        _useGravity = false;
        _useFriction = true;
    }

    // Apply gravity force
    if (_useGravity)
    {
        AddForce(GravityForce());
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




