#include "Stage.h"
#include "Level_Loader.h"

Stage::Stage()
{
	model = std::make_unique<Model>("Data/Model/ExampleStage/ExampleStage.mdl");

	Level_Loader::Instance().Save("name", { 1,2,3 }, { 4,5,6 }, { 7,8,9 });
	Level_Loader::Instance().Save("something", { 1,2,3 }, { 4,5,6 }, { 7,8,9 });

	Level_Loader::Instance().SaveInTxt();
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