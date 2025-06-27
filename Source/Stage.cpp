#include "Stage.h"

Stage::Stage()
{
	model = std::make_unique<Model>("Data/Model/ExampleStage/ExampleStage.mdl");
}

void Stage::Update(float elapsedTime)
{

}

void Stage::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	if (model)
	{
		shader->Draw(dc, model.get());
	}
}