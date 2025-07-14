#pragma once
#include <DirectXMath.h>

class Geometry
{
public :
	Geometry() {};
	virtual ~Geometry() {};

	void UpdateTransform();

protected :
	DirectX::XMFLOAT3 position = { 0,0,0 };
	DirectX::XMFLOAT3 rotation = { 0,0,0 };
	DirectX::XMFLOAT3 scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
					1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					0,0,0,1 };
};