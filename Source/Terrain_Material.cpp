#include "Terrain_Material.h"
#include "AABBChecker.h"

Ground::Ground()
{
	box = LoadAABB(model.get());
}

void Ground::Update(float elapsedTime)
{
	UpdateTransform();

	model->UpdateTransform(transform);
}

void Ground::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model.get());
}




void FloatingPlatform::Update(float elapsedTime)
{
	UpdateTransform();

	model->UpdateTransform(transform);
}

void FloatingPlatform::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model.get());
}




void Box::Update(float elapsedTime)
{
	UpdateTransform();

	model->UpdateTransform(transform);
}

void Box::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model.get());
}