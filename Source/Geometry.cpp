#include "Geometry.h"

void Geometry::UpdateTransform()
{
	DirectX::XMMATRIX Position = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	DirectX::XMMATRIX Rotation = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	DirectX::XMMATRIX Scale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	DirectX::XMMATRIX W = Scale * Rotation * Position;
	DirectX::XMStoreFloat4x4(&transform, W);
}