#include "SphereCollider.h"
#include "AABBCollider.h"

bool SphereCollider::CollidesWith(SphereCollider* other)
{
    Vector3 diff = GetPosition() - other->GetPosition();
    float distance = diff.Magnitude();
    return distance < (radius + other->GetRadius());
}

bool SphereCollider::CollidesWith(AABBCollider* other)
{
    return other->CollidesWith(this);
}
