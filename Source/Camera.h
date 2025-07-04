#pragma once

#include <DirectXMath.h>

class Camera
{
private:
	Camera() {};
	~Camera() {};

public :
	
	static Camera& Instance()
	{
		static Camera camera;
		return camera;
	}

private :
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;

};