#include "Geometry.h"
#include "Camera.h"

void Geometry::UpdateTransform()
{
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	DirectX::XMMATRIX W = S * R * T;
	DirectX::XMStoreFloat4x4(&transform, W);
}

void Geometry::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	Camera& camera = Camera::Instance();
	DirectX::XMMATRIX view = XMLoadFloat4x4(&camera.GetView());
	DirectX::XMMATRIX viewInverse = DirectX::XMMatrixInverse(nullptr, view);
	DirectX::XMVECTOR cameraPos = viewInverse.r[3];
	DirectX::XMFLOAT3 camPos;
	DirectX::XMStoreFloat3(&camPos, cameraPos);

	float halfWidth = 1920.0f / 2.0f;
	float halfHeight = 1080.0f / 2.0f;

	DirectX::XMFLOAT2 renderMin = { camPos.x - halfWidth, camPos.y - halfHeight };
	DirectX::XMFLOAT2 renderMax = { camPos.x + halfWidth, camPos.y + halfHeight };

	if (box.max.x >= renderMin.x && box.min.x <= renderMax.x &&
		box.max.y >= renderMin.y && box.min.y <= renderMax.y)
	{
		if (!model) return;
		shader->Draw(dc, model.get());
	}
}