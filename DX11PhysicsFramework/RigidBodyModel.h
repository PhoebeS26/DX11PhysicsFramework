#pragma once
#include "PhysicsModel.h"

class RigidBodyModel : public PhysicsModel
{
public:
    RigidBodyModel(Transform* transform, float mass = 1.0f);

    void SetMass(float mass) override;
    void Update(float deltaTime) override;

    void CalculateAngularVelocity(float deltaTime); 

private:
    void RecalculateInertia(); 
};
