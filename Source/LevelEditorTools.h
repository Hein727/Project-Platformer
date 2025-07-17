#pragma once
#include <DirectXMath.h>
#include "AABBChecker.h"

class LevelEditorTools
{
private :
	LevelEditorTools() {};
	~LevelEditorTools() {};

	bool currentState,preState = false;
public :

	static LevelEditorTools& Instance()
	{
		static LevelEditorTools instance;
		return instance;
	}
	DirectX::XMFLOAT3 placeObject(bool* check);

	bool objectDelete(const HitBox& hitbox, const DirectX::XMFLOAT3 cursor);

	
};