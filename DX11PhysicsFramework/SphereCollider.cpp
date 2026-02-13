#include "SphereCollider.h"

bool SphereCollider::CollidesWith(SphereCollider* other)
{
    Vector3 diff = GetPosition() - other->GetPosition();
    float distance = diff.Magnitude();
    return distance < (radius + other->GetRadius());
}
