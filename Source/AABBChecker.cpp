#include "AABBChecker.h"

bool HitCheck(const HitBox& box1, const HitBox& box2)
{
	if (box1.max.x < box2.min.x || box1.min.x > box2.max.x) return true;
	if (box1.max.y < box2.min.y || box1.min.y > box2.max.y) return true;
	if (box1.max.z < box2.min.z || box1.min.z > box2.max.z) return true;
	return false;
}

HitBox LoadAABB(const Model* model)
{
	HitBox box;

	bool firstVertex = true;

	auto meshes = model->GetResource()->GetMeshes();

	for (const auto& mesh : meshes)
	{
		auto& vertices = mesh.vertices;
		for (const auto& vertex : vertices)
		{
			if (firstVertex)
			{
				box.min = vertex.position;
				box.max = vertex.position;
				firstVertex = false;
			}
			else
			{
				box.min.x = box.min.x < vertex.position.x ? box.min.x : vertex.position.x;
				box.min.y = box.min.y < vertex.position.y ? box.min.y : vertex.position.y;
				box.min.z = box.min.z < vertex.position.z ? box.min.z : vertex.position.z;

				box.max.x = box.max.x > vertex.position.x ? box.max.x : vertex.position.x;
				box.max.y = box.max.y > vertex.position.y ? box.max.y : vertex.position.y;
				box.max.z = box.max.z > vertex.position.z ? box.max.z : vertex.position.z;
			}
		}
	}

	return box;
}

HitBox UpdateHitBox(HitBox& hitbox, DirectX::XMFLOAT3& pos, DirectX::XMFLOAT3& scale)
{
	DirectX::XMFLOAT3 scaledMax =
	{
		hitbox.max.x * scale.x > hitbox.min.x * scale.x ? hitbox.max.x * scale.x : hitbox.min.x * scale.x,
		hitbox.max.y * scale.y > hitbox.min.y * scale.y ? hitbox.max.y * scale.y : hitbox.min.y * scale.y,
		hitbox.max.z * scale.z > hitbox.min.z * scale.z ? hitbox.max.z * scale.z : hitbox.min.z * scale.z,
	};

	DirectX::XMFLOAT3 scaledMin =
	{
		hitbox.max.x * scale.x < hitbox.min.x * scale.x ? hitbox.max.x * scale.x : hitbox.min.x * scale.x,
		hitbox.max.y * scale.y < hitbox.min.y * scale.y ? hitbox.max.y * scale.y : hitbox.min.y * scale.y,
		hitbox.max.z * scale.z < hitbox.min.z * scale.z ? hitbox.max.z * scale.z : hitbox.min.z * scale.z,
	};

	hitbox.max.x = scaledMax.x + pos.x;
	hitbox.max.y = scaledMax.y + pos.y;
	hitbox.max.z = scaledMax.z + pos.z;

	hitbox.min.x = scaledMin.x + pos.x;
	hitbox.min.y = scaledMin.y + pos.y;
	hitbox.min.z = scaledMin.z + pos.z;

	return hitbox;
}