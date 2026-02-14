#include "AABBCollider.h"
#include "SphereCollider.h"
#include <algorithm>

// AABB vs AABB
bool AABBCollider::CollidesWith(AABBCollider* other)
{
    Vector3 posA = _tf->GetPosition();
    Vector3 posB = other->_tf->GetPosition();

    Vector3 minA = posA - halfExtents;
    Vector3 maxA = posA + halfExtents;
    Vector3 minB = posB - other->GetHalfExtents();
    Vector3 maxB = posB + other->GetHalfExtents();

    return (minA.x <= maxB.x && maxA.x >= minB.x) &&
        (minA.y <= maxB.y && maxA.y >= minB.y) &&
        (minA.z <= maxB.z && maxA.z >= minB.z);
}

// AABB vs Sphere
bool AABBCollider::CollidesWith(SphereCollider* other)
{
    Vector3 posA = _tf->GetPosition();
    Vector3 minA = posA - halfExtents;
    Vector3 maxA = posA + halfExtents;

    Vector3 spherePos = other->GetPosition();
    float radius = other->GetRadius();

    float x = std::max(minA.x, std::min(spherePos.x, maxA.x));
    float y = std::max(minA.y, std::min(spherePos.y, maxA.y));
    float z = std::max(minA.z, std::min(spherePos.z, maxA.z));

    Vector3 closestPoint(x, y, z);
    Vector3 diff = spherePos - closestPoint;
    return diff.Magnitude() < radius;
}
