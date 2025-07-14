#include "LevelEditorTools.h"
#include "Input/Mouse.h"
#include "Graphics/Graphics.h"
#include "Camera.h"
#include <DirectXCollision.h>

DirectX::XMFLOAT3 LevelEditorTools::placeObject()
{
	// スクリーンサイズ取得
	float screenWidth = Graphics::Instance().GetScreenWidth();
	float screenHeight = Graphics::Instance().GetScreenHeight();

	// マウスカーソル位置の取得
	POINT cursor;
	::GetCursorPos(&cursor);
	::ScreenToClient(Graphics::Instance().GetWindow(), &cursor);

	Camera& camera = Camera::Instance();

	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&camera.GetView());
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&camera.GetProjection());
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

	DirectX::XMVECTOR ScreenPosition, WorldPosition;
	DirectX::XMFLOAT3 screenPosition;
	screenPosition.x = static_cast<float>(cursor.x);
	screenPosition.y = static_cast<float>(cursor.y);
	screenPosition.z = 0.0f;

	DirectX::XMVECTOR NDCPosition = DirectX::XMVectorSet(
		2.0f * screenPosition.x / screenWidth - 1.0f,
		1.0f - 2.0f * (screenPosition.y / screenHeight),
		screenPosition.z / 1.0f, 1.0f
	);

	DirectX::XMMATRIX WVP = World * View * Projection;
	DirectX::XMMATRIX WVPInverse = DirectX::XMMatrixInverse(nullptr, WVP);
	WorldPosition = DirectX::XMVector3TransformCoord(NDCPosition, WVPInverse);

	DirectX::XMFLOAT3 rayStart;
	DirectX::XMStoreFloat3(&rayStart, WorldPosition);

	NDCPosition = DirectX::XMVectorSet(
		2.0f * screenPosition.x / screenWidth - 1.0f,
		1.0f - 2.0f * (screenPosition.y / screenHeight),
		(screenPosition.z + 1.0f) / 1.0f, 1.0f
	);

	WVP = World * View * Projection;
	WVPInverse = DirectX::XMMatrixInverse(nullptr, WVP);
	WorldPosition = DirectX::XMVector3TransformCoord(NDCPosition, WVPInverse);

	DirectX::XMFLOAT3 rayEnd;
	DirectX::XMStoreFloat3(&rayEnd, WorldPosition);

	rayEnd.z = 0.0f;

	return rayEnd;
}