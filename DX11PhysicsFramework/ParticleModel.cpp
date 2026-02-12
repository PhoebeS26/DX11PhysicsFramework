#include "ParticleModel.h"
#include <cstdlib> 

ParticleModel::ParticleModel(Transform* transform) : PhysicsModel(transform, 1.0f)
{
    startPosition = transform->GetPosition();
    Reset();
}

ParticleModel::ParticleModel(Transform* transform, float resetTime, Vector3 perturbation, bool invertGravity) : PhysicsModel(transform, 1.0f), resetTime(resetTime), perturbation(perturbation), invertGravity(invertGravity)
{
    startPosition = transform->GetPosition();

    _velocity += perturbation;
    _useGravity = !invertGravity;

    Reset();

}

void ParticleModel::Update(float deltaTime)
{
    timeAlive += deltaTime;

    if (timeAlive > resetTime) 
    {
        Reset();
    }

    if (_useGravity)
    {
        Vector3 gravity = PhysicsModel::GravityForce();

        if (invertGravity) 
        {
            gravity.Reverse();
        }

        PhysicsModel::AddForce(gravity);
    }

    PhysicsModel::Update(deltaTime);
}


void ParticleModel::Reset()
{
    float randX = ((rand() % 100) / 100.0f - 0.5f); 
    float randY = ((rand() % 100) / 100.0f);       
    float randZ = ((rand() % 100) / 100.0f - 0.5f);

    Vector3 randomOffset(randX, randY, randZ);
    _transform->SetPosition(startPosition + randomOffset);

    _useGravity = true;

    timeAlive = 0.0f;
}

