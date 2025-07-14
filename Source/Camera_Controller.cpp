#include "Camera_Controller.h"
#include "Camera.h"
#include "Input/Input.h"

void Camera_Controller::Update(float elapsedTime)
{
#ifdef NDEBUG
	Camera& camera = Camera::Instance();

	DirectX::XMFLOAT3 eye = { target.x, target.y + 2, -10.0f };
	DirectX::XMFLOAT3 focus = { target.x, target.y,	0.0f };
	DirectX::XMFLOAT3 up = { 0.0f, 1.0f, 0.0f };

	camera.SetLookAt(eye, focus, up);
#endif

#ifdef _DEBUG
	Camera& camera = Camera::Instance();
	static DirectX::XMFLOAT3 cameraPos = { 0.0f, 0.0f, -5.0f };
	static DirectX::XMFLOAT3 cameraTarget = { 0.0f, 0.0f, 0.0f };

	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	float moveSpeed = 5.0f * elapsedTime;

	cameraPos.x += ax * moveSpeed;
	cameraPos.y += ay * moveSpeed;

	cameraTarget = {
		cameraPos.x,
		cameraPos.y,
		cameraPos.z + 1.0f
	};

	DirectX::XMFLOAT3 up = { 0, 1, 0 };
	camera.SetLookAt(cameraPos, cameraTarget, up);
#endif
	
}