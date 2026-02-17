#include "PhysicsModel.h"
#include "PlaneCollider.h"
#include "Debug.h"
#include "Collider.h"

// Constructor
PhysicsModel::PhysicsModel(Transform* transform, float mass)
{
    _mass = mass;
    _transform = transform;

    _velocity = Vector3(0.0f, 0.0f, 0.0f);
    _acceleration = Vector3(0.0f, 0.0f, 0.0f);
    _netForce = Vector3(0.0f, 0.0f, 0.0f);

    _isGrounded = false;
    _useFriction = true;
}

// ================= UPDATE =================
void PhysicsModel::Update(float deltaTime)
{
    if (!_transform) return;
    if (_mass <= 0.0f) return;

    // === Apply Gravity ===
    if (_useGravity)
        AddForce(GravityForce());

    // === Apply Drag / Air Resistance ===
    if (_useDrag)
        AddForce(DragForce());
    //AddForce(DragForce());

    // === Apply Friction only if grounded ===
    if (_useFriction && _isGrounded)
    {
        // FrictionForce() returns a force vector
        AddForce(FrictionForce());
    }

    // === Integrate Acceleration ===
    _acceleration += _netForce / _mass;       // a = F/m
    _velocity += _acceleration * deltaTime;   // v = v + a*dt

    // === Prevent tiny jitter for friction ===
    const float velTol = 0.001f;
    if (_velocity.Magnitude() < velTol)
        _velocity = Vector3(0, 0, 0);

    // === Update Position ===
    _transform->SetPosition(_transform->GetPosition() + _velocity * deltaTime);

    // === Reset forces / acceleration for next frame ===
    _netForce = Vector3(0, 0, 0);
    _acceleration = Vector3(0, 0, 0);
}


// ================= FORCES =================
void PhysicsModel::AddForce(const Vector3& force)
{
    _netForce += force;
}

Vector3 PhysicsModel::GravityForce() const
{
    return Vector3(0.0f, -9.81f * _mass, 0.0f);
}

Vector3 PhysicsModel::FrictionForce()
{
    // ===== DEBUG: show every call =====
    float speed = _velocity.Magnitude();
    Debug::DebugPrintF("FrictionForce called | grounded: %d, speed: %f\n", _isGrounded, speed);

    // only apply friction if grounded
    if (!_isGrounded)
        return Vector3(0, 0, 0);

    const float tol = 0.01f; // small velocity threshold to avoid jitter
    if (speed <= tol)
    {
        Debug::DebugPrintF("FrictionForce skipped due to low speed\n");
        return Vector3(0, 0, 0);
    }

    Vector3 frictionDir = _velocity;
    frictionDir.Normalize();
    frictionDir.Reverse(); // opposite to motion

    const float kineticFriction = 0.6f;
    const float gravityAccel = 9.81f;

    float normalForce = _mass * gravityAccel;
    float frictionMag = kineticFriction * normalForce;

    // prevent over-correction for low speeds
    if (frictionMag * 0.016f > speed) // assuming deltaTime ~ 0.016
        frictionMag = speed / 0.016f;

    Debug::DebugPrintF("Friction applied | frictionMag: %f, direction: (%f,%f,%f)\n",
        frictionMag, frictionDir.x, frictionDir.y, frictionDir.z);

    return frictionDir * frictionMag;
}



Vector3 PhysicsModel::DragForce()
{
    float speed = _velocity.Magnitude();
    if (speed <= tol) return Vector3(0, 0, 0);

    Vector3 dragDir = _velocity;
    dragDir.Normalize();
    dragDir.Reverse();

    const float airDensity = 1.225f;
    const float dragCoeff = 0.47f;
    const float area = 1.0f;

    float dragMag = 0.5f * airDensity * dragCoeff * area * speed * speed;

    return dragDir * dragMag;
}

// ================= IMPULSE =================
void PhysicsModel::ApplyImpulse(const Vector3& impulse)
{
    _velocity += impulse;
}
