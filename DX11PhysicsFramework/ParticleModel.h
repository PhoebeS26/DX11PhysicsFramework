#pragma once
#include "PhysicsModel.h"

class ParticleModel : public PhysicsModel
{
public:

    // Default constructor
    ParticleModel(Transform* transform);

    // Overloaded constructor (particle system data)
    ParticleModel(Transform* transform, float resetTime, Vector3 perturbation, bool invertGravity);

    void Update(float deltaTime) override;
    void Reset();

private:

    Vector3 startPosition;

    float timeAlive = 0.0f;
    float resetTime = 5.0f;

    Vector3 perturbation = Vector3(0, 0, 0);
    bool invertGravity = false;

    float swaySpeedX;
    float swaySpeedZ;
    float swayOffsetX;
    float swayOffsetZ;
 
};
