#pragma once
#include "Character.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "AABBChecker.h"
#include <memory>

class Player : public Character
{
public :
	static Player& Instance()
	{
		static Player instance;
		return instance;
	}

	void Update(float elapsedTime);

	void Render(ID3D11DeviceContext* dc, Shader* shader);

	int HpGetter() { return hp; }
	auto HitBoxGetter() const { return box; }

	void SetVelocityY(const float velocityY) { this->velocityY = velocityY; }
	void SetIsJumping(const bool isJumping) { this->isJumping = isJumping; }
	void DamageTaker() { hp--; }


protected:

	int hp = 3;

	int coins = 0;

	float gravity = -9.8f;

	float moveSpeed = 5.0f;

	float jumpForce = 6.0f;

	float velocityY = 0.0f;

	bool isJumping = false;

	DirectX::XMFLOAT3 lastPos;

	std::unique_ptr<Model> model;

	HitBox box;

private :

	Player();
	~Player() override {};

};