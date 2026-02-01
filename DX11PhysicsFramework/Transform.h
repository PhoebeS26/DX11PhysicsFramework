#pragma once
#include <DirectXMath.h>
#include "Vector3.h"

using namespace DirectX;

class Transform
{

private:

	Vector3 _position;
	Vector3 _rotation;
	Vector3 _scale;

	XMFLOAT4X4 _world;


public:

	void SetPosition(Vector3 position) { _position = position; }
	void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }
	Vector3 GetPosition() const { return _position; }

	void SetRotation(Vector3 rotation) { _rotation = rotation; }
	void SetRotation(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }
	Vector3 GetRotation() const { return _rotation; }

	void SetScale(Vector3 scale) { _scale = scale; }
	void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }
	Vector3 GetScale() const { return _scale; }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }
	void UpdateWorldMatrix();

	void Move(XMFLOAT3 direction);

};

