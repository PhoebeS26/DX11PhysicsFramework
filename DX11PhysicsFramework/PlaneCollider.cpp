#include "PlaneCollider.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include <cmath>

// Plane vs Sphere
bool PlaneCollider::CollidesWith(SphereCollider* sphere)
{
    Vector3 spherePos = sphere->GetPosition();

    float distToPlane = (spherePos * normal) - distance; 

    return fabs(distToPlane) <= sphere->GetRadius();
}

// Plane vs AABB
bool PlaneCollider::CollidesWith(AABBCollider* aabb)
{
    Vector3 center = aabb->GetPosition();
    Vector3 he = aabb->GetHalfExtents();

    float projectedRadius =
        he.x * fabs(normal.x) +
        he.y * fabs(normal.y) +
        he.z * fabs(normal.z);

    float distToPlane = (center * normal) - distance; 
    return fabs(distToPlane) <= projectedRadius;
}

void PlaneCollider::ResolveCollision(PhysicsModel* objPhysics)
{
    Vector3 pos = objPhysics->GetPosition();
    Vector3 vel = objPhysics->GetVelocity();

    float distToPlane = (pos * normal) - distance;

    if (distToPlane < 0.0f)
    {
        // Push object out of plane
        pos -= normal * distToPlane;
        objPhysics->SetPosition(pos);

        float vn = vel * normal;

        if (vn < 0.0f)
        {
            float restitution = 0.2f; // 0 = no bounce, 1 = full bounce

            Vector3 normalVel = normal * vn;
            Vector3 tangentVel = vel - normalVel;

            // Bounce only on normal axis
            normalVel *= -restitution;

            vel = tangentVel + normalVel;

            objPhysics->SetVelocity(vel);
        }

        objPhysics->SetGrounded(true);

    }
}
