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

	void SetLookAt(const DirectX::XMFLOAT3& eye, const DirectX::XMFLOAT3& focus, const DirectX::XMFLOAT3& up);

	void SetPerspectiveFov(float fovY, float aspect, float nearZ, float farZ);

	const DirectX::XMFLOAT4X4& GetView() const { return view; }

	const DirectX::XMFLOAT4X4& GetProjection() const { return projection; }

	void setView(const DirectX::XMFLOAT4X4& view) { this->view = view; }

	void setProjection(const DirectX::XMFLOAT4X4& projection) { this->projection = projection; }

private :
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;

};