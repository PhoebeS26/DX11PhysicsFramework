#include "PhysicsModel.h"

// Constructor
PhysicsModel::PhysicsModel(Transform* transform)
{
    _transform = transform;
    _velocity = Vector3(0.0f, 0.0f, 0.0f); 
}

void PhysicsModel::Update(float deltaTime)
{
    if (!_transform) return; 

    Vector3 position = _transform->GetPosition(); 
    position += _velocity * deltaTime;            
    _transform->SetPosition(position);          
}
