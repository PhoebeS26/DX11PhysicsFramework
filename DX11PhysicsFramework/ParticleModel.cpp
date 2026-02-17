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

    // Reset particle after its lifetime expires
    if (timeAlive > resetTime)
    {
        Reset();
    }

    // Apply gravity if enabled
    if (_useGravity)
    {
        Vector3 gravity = PhysicsModel::GravityForce();

        if (invertGravity)
        {
            gravity.Reverse();
        }

        PhysicsModel::AddForce(gravity);
    }

    // Apply a small sway motion for more natural particle movement
    float swayStrength = 0.02f;
    _velocity.x += sin(timeAlive * swaySpeedX + swayOffsetX) * swayStrength;
    _velocity.z += cos(timeAlive * swaySpeedZ + swayOffsetZ) * swayStrength;

    PhysicsModel::Update(deltaTime);
}

void ParticleModel::Reset()
{
    // Randomize initial position around startPosition
    float randX = ((rand() % 100) / 100.0f - 0.5f);
    float randZ = ((rand() % 100) / 100.0f - 0.5f);

    // Random upward velocity
    float randY = 0.5f + ((rand() % 100) / 100.0f);

    _transform->SetPosition(startPosition + Vector3(randX, 0, randZ));
    _velocity = Vector3(0, randY, 0) + perturbation;

    // Randomize sway for natural motion
    swaySpeedX = 1.0f + ((rand() % 100) / 200.0f);
    swaySpeedZ = 1.0f + ((rand() % 100) / 200.0f);
    swayOffsetX = ((rand() % 100) / 200.0f - 0.25f);
    swayOffsetZ = ((rand() % 100) / 200.0f - 0.25f);

    _useGravity = true;
    timeAlive = 0.0f;
}
