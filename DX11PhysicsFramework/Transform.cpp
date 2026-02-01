#include "Transform.h"
#include <DirectXMath.h>

using namespace DirectX;

void Transform::UpdateWorldMatrix()
{
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);

	XMMATRIX rotation =
		XMMatrixRotationX(_rotation.x) *
		XMMatrixRotationY(_rotation.y) *
		XMMatrixRotationZ(_rotation.z);

	XMMATRIX translation =
		XMMatrixTranslation(_position.x, _position.y, _position.z);

	XMMATRIX world = scale * rotation * translation;

	XMStoreFloat4x4(&_world, world);
}

void Transform::Move(XMFLOAT3 direction)
{
	_position.x += direction.x;
	_position.y += direction.y;
	_position.z += direction.z;
}

