#include "PhysicsModel.h"

// Constructor
PhysicsModel::PhysicsModel(Transform* transform)
{
    _transform = transform;
    _velocity = Vector3(0.0f, 0.0f, 0.0f); 
    _acceleration = Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsModel::Update(float deltaTime)
{
    if (!_transform) return;

    if (_useAcceleration)
    {
        _velocity += _acceleration * deltaTime; // v = v0 + a * dt
    }

    Vector3 position = _transform->GetPosition();
    position += _velocity * deltaTime; // p = p0 + v * dt
    _transform->SetPosition(position);

}
