#pragma once
#include <DirectXMath.h>

class Character
{
public:
	Character();
	virtual ~Character() {};

	void UpdateTransform();

private :
	DirectX::XMFLOAT3 position = { 0,0,0 };
	DirectX::XMFLOAT3 rotation = { 0,0,0 };
	DirectX::XMFLOAT3 scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
					1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					0,0,0,1 };
};