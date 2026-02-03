#pragma once
#include "PhysicsModel.h"

class ParticleModel : public PhysicsModel
{
public:

    ParticleModel(Transform* transform);

    void Update(float deltaTime) override;
};
