#include "RigidBodyModel.h"

RigidBodyModel::RigidBodyModel(Transform* transform, float mass) : PhysicsModel(transform, mass)
{

}

void RigidBodyModel::Update(float deltaTime)
{
    PhysicsModel::Update(deltaTime);
}

void RigidBodyModel::SetMass(float mass)
{
    _mass = mass;

    if (_mass < 0.0f)
        _mass = 0.0f;

    RecalculateInertia();
}

void RigidBodyModel::CalculateAngularVelocity(float deltaTime)
{
    if (_mass == 0.0f) 
    {
        return;
    }
        
}

void RigidBodyModel::RecalculateInertia()
{
    
}
