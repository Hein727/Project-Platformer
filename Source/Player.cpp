#include "Player.h"
#include "Camera.h"
#include "Input/GamePad.h"
#include "Input/Input.h"
#define KEY_SPACE VK_SPACE 

Player::Player()
{
	model = std::make_unique<Model>("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

	scale.x = scale.y = scale.z = 0.01f;
}

void Player::Update(float elapsedTime)
{
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
		velocityY = jumpForce;
		isJumping = true;
	}

	velocityY += gravity * elapsedTime;
	position.y += velocityY * elapsedTime;

	if (position.y <= 0.0f)
	{
		position.y = 0.0f;
		velocityY = 0.0f;
		isJumping = false;
	}

	Camera& camera = Camera::Instance();

	DirectX::XMFLOAT3 eye = { position.x, position.y + 2, -10.0f };
	DirectX::XMFLOAT3 focus = { position.x, position.y,	0.0f };
	DirectX::XMFLOAT3 up = { 0.0f, 1.0f, 0.0f };

	camera.SetLookAt(eye, focus, up);

	UpdateTransform();

	model->UpdateTransform(transform);
}

void Player::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model.get());
}