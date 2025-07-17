#pragma once
#include <DirectXMath.h>

class Character
{
public:
	Character() {};
	virtual ~Character() {};

	void UpdateTransform();

	void SetPosition(const DirectX::XMFLOAT3 position) { this->position = position; }

	void SetRotation(const DirectX::XMFLOAT3 rotation) { this->rotation = rotation; }

	void SetScale(const DirectX::XMFLOAT3 scale) { this->scale = scale; }

	auto GetPosition() const { return position; }

	auto GetRotation() const { return rotation; }

	auto GetScale() const { return scale; }

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