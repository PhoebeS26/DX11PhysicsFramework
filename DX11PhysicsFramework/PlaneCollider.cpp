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

