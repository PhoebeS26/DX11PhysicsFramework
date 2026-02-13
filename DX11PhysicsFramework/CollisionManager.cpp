#include "CollisionManager.h"
#include "SphereCollider.h"

void CollisionManager::ResolveCollision(PhysicsModel* p1, PhysicsModel* p2, float restitution)
{
    if (!p1 || !p2) return;

    Collider* c1 = p1->GetCollider();
    Collider* c2 = p2->GetCollider();
    if (!c1 || !c2) return;

    // Vector between objects
    Vector3 delta = p1->GetPosition() - p2->GetPosition();
    float distance = delta.Magnitude();

    float radiusSum = 0.0f;
    
    SphereCollider* s1 = dynamic_cast<SphereCollider*>(c1);
    SphereCollider* s2 = dynamic_cast<SphereCollider*>(c2);

    if (!s1 || !s2) return; 

    radiusSum = s1->GetRadius() + s2->GetRadius();

    // Check for interpenetration
    float penetration = radiusSum - distance;
    if (penetration <= 0.0f) return; 

    // Normalize collision normal
    Vector3 collisionNormal = delta / distance;

    // Resolve positions (interpenetration)
    float invMass1 = 1.0f / p1->GetMass();
    float invMass2 = 1.0f / p2->GetMass();

    Vector3 correction = collisionNormal * (penetration / (invMass1 + invMass2));
    p1->SetPosition(p1->GetPosition() + correction * invMass1);
    p2->SetPosition(p2->GetPosition() - correction * invMass2);

    // Relative velocity
    Vector3 relativeVel = p1->GetVelocity() - p2->GetVelocity();
    float velAlongNormal = relativeVel * collisionNormal; // dot product

    if (velAlongNormal > 0.0f) return; 

    // Calculate impulse
    float j = -(1.0f + restitution) * velAlongNormal;
    j /= (invMass1 + invMass2);

    // Apply impulse
    p1->ApplyImpulse(collisionNormal * (j * invMass1));
    p2->ApplyImpulse(collisionNormal * (-j * invMass2));
}

