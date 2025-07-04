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

};