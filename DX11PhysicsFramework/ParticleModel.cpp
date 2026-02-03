#include "ParticleModel.h"

ParticleModel::ParticleModel(Transform* transform) : PhysicsModel(transform, 1.0f)
{
	
}

void ParticleModel::Update(float deltaTime)
{
	PhysicsModel::Update(deltaTime);
}
