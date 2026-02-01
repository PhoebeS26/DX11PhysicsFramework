#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "Transform.h"
#include "Appearance.h"

using namespace DirectX;
using namespace std;


class GameObject
{
public:
	GameObject(string type, Appearance* appearance, Transform* transform);
	~GameObject();

	Transform* GetTransform() const { return _transform; }
	Appearance* GetAppearance() const { return _appearance; }


	string GetType() const { return _type; }


	void SetParent(GameObject * parent) { _parent = parent; }


	void Update(float dt);
	void Draw(ID3D11DeviceContext * pImmediateContext);

private:
	GameObject* _parent = nullptr;
	Transform* _transform;
	Appearance* _appearance;

	string _type;

};

