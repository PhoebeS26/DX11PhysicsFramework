#include "CollisionManager.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include <cmath> 

// Resolve collision between two spheres
void CollisionManager::ResolveCollision(PhysicsModel* p1, PhysicsModel* p2, float restitution)
{
    if (!p1 || !p2)
    {
        return;
    }

    Collider* c1 = p1->GetCollider();
    Collider* c2 = p2->GetCollider();
    if (!c1 || !c2)
    {
        return;
    }

    Vector3 delta = p1->GetPosition() - p2->GetPosition();
    float distance = delta.Magnitude();

    SphereCollider* s1 = dynamic_cast<SphereCollider*>(c1);
    SphereCollider* s2 = dynamic_cast<SphereCollider*>(c2);
    if (!s1 || !s2)
    {
        return;
    }

    float radiusSum = s1->GetRadius() + s2->GetRadius();

    // Skip if spheres are not intersecting
    float penetration = radiusSum - distance;
    if (penetration <= 0.0f)
    {
        return;
    }

    // Collision direction
    Vector3 collisionNormal = delta / distance;

    // Move spheres apart based on mass
    float invMass1 = 1.0f / p1->GetMass();
    float invMass2 = 1.0f / p2->GetMass();
    Vector3 correction = collisionNormal * (penetration / (invMass1 + invMass2));
    p1->SetPosition(p1->GetPosition() + correction * invMass1);
    p2->SetPosition(p2->GetPosition() - correction * invMass2);

    // Relative velocity along collision
    Vector3 relativeVel = p1->GetVelocity() - p2->GetVelocity();
    float velAlongNormal = relativeVel * collisionNormal; 

    if (velAlongNormal > 0.0f)
    {
        return; // already separating
    }

    // Impulse magnitude
    float j = -(1.0f + restitution) * velAlongNormal;
    j /= (invMass1 + invMass2);

    // Apply impulse
    p1->ApplyImpulse(collisionNormal * (j * invMass1));
    p2->ApplyImpulse(collisionNormal * (-j * invMass2));
}

// Resolve collision between two AABBs
void CollisionManager::ResolveAABB(PhysicsModel* p1, PhysicsModel* p2, float restitution)
{
    AABBCollider* a1 = dynamic_cast<AABBCollider*>(p1->GetCollider());
    AABBCollider* a2 = dynamic_cast<AABBCollider*>(p2->GetCollider());
    if (!a1 || !a2)
    {
        return;
    }

    Vector3 pos1 = p1->GetPosition();
    Vector3 pos2 = p2->GetPosition();
    Vector3 he1 = a1->GetHalfExtents();
    Vector3 he2 = a2->GetHalfExtents();

    Vector3 delta = pos1 - pos2;

    // Calculate overlap on each axis
    float overlapX = (he1.x + he2.x) - fabsf(delta.x);
    float overlapY = (he1.y + he2.y) - fabsf(delta.y);
    float overlapZ = (he1.z + he2.z) - fabsf(delta.z);

    if (overlapX <= 0 || overlapY <= 0 || overlapZ <= 0)
    {
        return; 
    }

    // Find axis with smallest penetration
    Vector3 normal;
    float penetration;
    if (overlapX < overlapY && overlapX < overlapZ)
    {
        normal = Vector3((delta.x > 0) ? 1 : -1, 0, 0);
        penetration = overlapX;
    }
    else if (overlapY < overlapZ)
    {
        normal = Vector3(0, (delta.y > 0) ? 1 : -1, 0);
        penetration = overlapY;
    }
    else
    {
        normal = Vector3(0, 0, (delta.z > 0) ? 1 : -1);
        penetration = overlapZ;
    }

    // Separate objects based on mass
    float invMass1 = 1.0f / p1->GetMass();
    float invMass2 = 1.0f / p2->GetMass();
    Vector3 correction = normal * (penetration / (invMass1 + invMass2));
    p1->SetPosition(p1->GetPosition() + correction * invMass1);
    p2->SetPosition(p2->GetPosition() - correction * invMass2);

    // Apply impulse along collision normal
    Vector3 relativeVel = p1->GetVelocity() - p2->GetVelocity();
    float velAlongNormal = relativeVel * normal;
    if (velAlongNormal > 0.0f)
    {
        return; 
    }

    float j = -(1.0f + restitution) * velAlongNormal;
    j /= (invMass1 + invMass2);

    p1->ApplyImpulse(normal * (j * invMass1));
    p2->ApplyImpulse(normal * (-j * invMass2));
}
