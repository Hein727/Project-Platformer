#include "Camera_Controller.h"
#include "Camera.h"
#include "Input/Input.h"

void Camera_Controller::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	DirectX::XMFLOAT3 eye;

	eye.x = target.x * range;
	eye.y = target.x * range;
	eye.z = target.x * range;
}