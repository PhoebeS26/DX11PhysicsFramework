#pragma once

#include <directxmath.h>
#include <d3d11_1.h>

using namespace DirectX;

// Holds mesh data for rendering
struct Geometry
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int numberOfIndices;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};

// Material info for shading
struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
};

// Controls what an object looks like (mesh, material, texture)
class Appearance
{
private:
	Geometry _geometry;
	Material _material;
	ID3D11ShaderResourceView* _textureRV = nullptr; 

public:

	// Assign geometry to this appearance
	void SetGeometry(Geometry geometry) { _geometry = geometry; }
	Geometry GetGeometry() const { return _geometry; }

	// Assign material (diffuse, ambient, specular)
	void SetMaterial(Material material) { _material = material; }
	Material GetMaterial() const { return _material; }

	// Set or get texture 
	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView* const* GetTextureRV() { return &_textureRV; }

	// True if a texture is assigned
	bool HasTexture() const { return _textureRV != nullptr; }
};
