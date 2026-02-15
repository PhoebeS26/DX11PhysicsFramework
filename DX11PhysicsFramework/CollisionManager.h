#pragma once
#include "PhysicsModel.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "Vector3.h"

class CollisionManager
{
public:

    static void ResolveCollision(PhysicsModel* p1, PhysicsModel* p2, float restitution = 0.5f);
    static void ResolveAABB(PhysicsModel* p1, PhysicsModel* p2, float restitution);

};
