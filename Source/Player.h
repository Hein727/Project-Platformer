#pragma once
#include "Character.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include <memory>

class Player : public Character
{
public :

	Player();
	~Player() override {};

	void Update(float elapsedTime);

	void Render(ID3D11DeviceContext* dc, Shader* shader);

	int HpGetter() { return hp; }

	void DamageTaker(bool check) { hp--; }

protected:

	int hp = 0;

	float gravity = -9.8f;

	float moveSpeed = 5.0f;

	float jumpForce = 6.0f;

	float velocityY = 0.0f;

	bool isJumping = false;

	std::unique_ptr<Model> model;
};