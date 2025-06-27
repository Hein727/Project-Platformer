#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include <memory>

class Stage
{
public :
	Stage();
	~Stage() {};

	void Update(float elapsedTime);

	void Render(ID3D11DeviceContext* dc, Shader* shader);

private :
	std::unique_ptr<Model> model;
};