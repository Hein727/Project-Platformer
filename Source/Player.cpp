#include "Player.h"
#include "Camera.h"
#include "Input/GamePad.h"
#include "Input/Input.h"
#include "Camera_Controller.h"
#define KEY_SPACE VK_SPACE 

Player::Player()
{
	model = std::make_unique<Model>("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

	scale.x = scale.y = scale.z = 0.01f;

	box = LoadAABB(model.get());

	box = UpdateHitBox(box, position, scale);
}

void Player::Update(float elapsedTime)
{
#ifdef NDEBUG
	Camera_Controller& camera_controller = Camera_Controller::Camera_Controller();

	GamePad& gamePad = Input::Instance().GetGamePad();

	float ax = gamePad.GetAxisLX();

	float moveSpeed = this->moveSpeed * elapsedTime;

	position.x += moveSpeed * ax;

	if (ax > 0.0f)
	{
		rotation.y = 90.0f;
	}
	else if (ax < 0.0f)
	{
		rotation.y = -90.0f;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !isJumping)
	{
		lastPos = position;
		velocityY = jumpForce;
		isJumping = true;
	}

	velocityY += gravity * elapsedTime;
	position.y += velocityY * elapsedTime;

	camera_controller.SetTarget(position);
	camera_controller.Update(elapsedTime);

#endif // 


	UpdateTransform();

	model->UpdateTransform(transform);
}

void Player::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model.get());
}