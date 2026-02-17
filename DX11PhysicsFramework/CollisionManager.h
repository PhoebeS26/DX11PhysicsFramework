#pragma once
#include "PhysicsModel.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "Vector3.h"

// Handles collision resolution between physics objects
class CollisionManager
{
public:

    // Sphere collision response 
    static void ResolveCollision(PhysicsModel* p1, PhysicsModel* p2, float restitution = 0.5f);

    // AABB collision response
    static void ResolveAABB(PhysicsModel* p1, PhysicsModel* p2, float restitution);
};
