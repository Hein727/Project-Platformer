#pragma once
#include <DirectXMath.h>

class LevelEditorTools
{
private :
	LevelEditorTools() {};
	~LevelEditorTools() {};

public :

	static LevelEditorTools& Instance()
	{
		static LevelEditorTools instance;
		return instance;
	}

	DirectX::XMFLOAT3 placeObject();
};