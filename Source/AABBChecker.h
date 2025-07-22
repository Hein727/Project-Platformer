#pragma once
#include <DirectXMath.h>
#include "Graphics/Model.h"

struct HitBox
{
	DirectX::XMFLOAT3 max = { FLT_EPSILON, FLT_EPSILON, FLT_EPSILON };
	DirectX::XMFLOAT3 min = { -FLT_EPSILON, -FLT_EPSILON, -FLT_EPSILON };

	HitBox& operator=(const HitBox&) = default;

	bool collision(const HitBox& other)const
	{
		return (min.x <= other.max.x && max.x >= other.min.x) &&
			(min.y <= other.max.y && max.y >= other.min.y) &&
			(min.z <= other.max.z && max.z >= other.min.z);
	}
};
HitBox LoadAABB(const Model* model);
bool HitCheck(const HitBox& box1, const HitBox& box2);
bool HitCheckForJump(const HitBox& box1, const HitBox& box2);
HitBox UpdateHitBox(HitBox& hitbox, DirectX::XMFLOAT3& pos, DirectX::XMFLOAT3& scale);
