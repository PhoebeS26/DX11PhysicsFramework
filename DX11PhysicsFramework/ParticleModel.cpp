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

    float swayStrength = 0.02f;
    _velocity.x += sin(timeAlive * swaySpeedX + swayOffsetX) * swayStrength;
    _velocity.z += cos(timeAlive * swaySpeedZ + swayOffsetZ) * swayStrength;
  
    PhysicsModel::Update(deltaTime);
}

void ParticleModel::Reset()
{
    float randX = ((rand() % 100) / 100.0f - 0.5f); 
    float randZ = ((rand() % 100) / 100.0f - 0.5f);

    float randY = 0.5f + ((rand() % 100) / 100.0f); 

    _transform->SetPosition(startPosition + Vector3(randX, 0, randZ));
    _velocity = Vector3(0, randY, 0) + perturbation;

    swaySpeedX = 1.0f + ((rand() % 100) / 200.0f);
    swaySpeedZ = 1.0f + ((rand() % 100) / 200.0f);
    swayOffsetX = ((rand() % 100) / 200.0f - 0.25f);
    swayOffsetZ = ((rand() % 100) / 200.0f - 0.25f);

    _useGravity = true;

    timeAlive = 0.0f;
}


