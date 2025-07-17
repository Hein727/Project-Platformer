#include "LevelEditorTools.h"
#include "Input/Mouse.h"
#include "Graphics/Graphics.h"
#include "Camera.h"
#include <DirectXCollision.h>

DirectX::XMFLOAT3 LevelEditorTools::placeObject(bool* check)
{
    currentState = GetAsyncKeyState(VK_LBUTTON) & 0x8000;

    if (currentState != preState)
    {
            float screenWidth = Graphics::Instance().GetScreenWidth();
            float screenHeight = Graphics::Instance().GetScreenHeight();

            // Get mouse position
            POINT cursor;
            ::GetCursorPos(&cursor);
            ::ScreenToClient(Graphics::Instance().GetWindow(), &cursor);

            float px = static_cast<float>(cursor.x);
            float py = static_cast<float>(cursor.y);

            // Convert to NDC
            float ndcX = 2.0f * px / screenWidth - 1.0f;
            float ndcY = 1.0f - 2.0f * py / screenHeight;

            // Set up camera matrices
            Camera& camera = Camera::Instance();
            DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&camera.GetView());
            DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&camera.GetProjection());
            DirectX::XMMATRIX invViewProj = DirectX::XMMatrixInverse(nullptr, view * proj);

            // Unproject near and far points
            DirectX::XMVECTOR nearPoint = DirectX::XMVectorSet(ndcX, ndcY, 0.0f, 1.0f);
            DirectX::XMVECTOR farPoint = DirectX::XMVectorSet(ndcX, ndcY, 1.0f, 1.0f);

            nearPoint = DirectX::XMVector3TransformCoord(nearPoint, invViewProj);
            farPoint = DirectX::XMVector3TransformCoord(farPoint, invViewProj);

            // Direction = far - near
            DirectX::XMVECTOR dir = DirectX::XMVectorSubtract(farPoint, nearPoint);

            // Find t such that Z = 0 (plane at Z = 0)
            float zStart = DirectX::XMVectorGetZ(nearPoint);
            float zDir = DirectX::XMVectorGetZ(dir);

            if (fabs(zDir) < 1e-6f) zDir = 1e-6f; // avoid divide by zero

            float t = -zStart / zDir;

            DirectX::XMVECTOR hitPoint = DirectX::XMVectorAdd(nearPoint, DirectX::XMVectorScale(dir, t));

            DirectX::XMFLOAT3 result;
            DirectX::XMStoreFloat3(&result, hitPoint);

            //making sure mouse input work properly 
            *check = true;
            preState = currentState;
            currentState = false;

            return result;
    }

    return { 0, 0, 0 };
}

bool LevelEditorTools::objectDelete(const HitBox& hitbox, const DirectX::XMFLOAT3 cursor)
{
    bool isInside =
        cursor.x >= hitbox.min.x && cursor.x <= hitbox.max.x &&
        cursor.y >= hitbox.min.y && cursor.y <= hitbox.max.y &&
        cursor.z >= hitbox.min.z && cursor.z <= hitbox.max.z;

    return isInside;
}