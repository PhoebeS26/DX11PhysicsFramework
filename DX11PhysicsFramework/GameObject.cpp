#include "GameObject.h"

GameObject::GameObject(string type,  Appearance* appearance, Transform* transform ) : _type(type), _appearance(appearance), _transform(transform)
{
	_parent = nullptr;
	_transform = transform;
	_appearance = appearance;
}

GameObject::~GameObject()
{
	delete _transform;
	delete _appearance;

	_parent = nullptr;
	_transform = nullptr;
	_appearance = nullptr;
}

void GameObject::Update(float dt)
{
	_transform->UpdateWorldMatrix();
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	Geometry geo = _appearance->GetGeometry();

	pImmediateContext->IASetVertexBuffers(0, 1, &geo.vertexBuffer, &geo.vertexBufferStride, &geo.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(geo.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(geo.numberOfIndices, 0, 0);

}
