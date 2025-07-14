#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "Transform.h"
#include "Camera.h"
#include "LevelEditorTools.h"
#include "Camera_Controller.h"
#include "Input/GamePad.h"
#include "Input/Input.h"


// 初期化
void SceneGame::Initialize()
{
	stage = std::make_unique<Stage>();

	player = std::make_unique<Player>();

	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);
}

// 終了化
void SceneGame::Finalize()
{
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	stage->Update(elapsedTime);

	player->Update(elapsedTime);

#ifdef _DEBUG

	auto selected_type = 0;

	if (GetAsyncKeyState('1') & 0x8000)
	{
		selected_type = BLOCK;
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		selected_type = GROUND_BLOCK;
	}
	if (GetAsyncKeyState('3') & 0x8000)
	{
		selected_type = SLOPE;
	}
	if (GetAsyncKeyState('4') & 0x8000)
	{
		selected_type = SPIKE;
	}
	if (GetAsyncKeyState('5') & 0x8000)
	{
		selected_type = FLAG;
	}
	if (GetAsyncKeyState('6') & 0x8000)
	{
		selected_type = ARCHWAY;
	}
	if (GetAsyncKeyState('7') & 0x8000)
	{
		selected_type = FLOATINGPLATFORM;
	}
	if (GetAsyncKeyState('8') & 0x8000)
	{
		selected_type = BOX;
	}


	if (GetAsyncKeyState(VK_LBUTTON) & 0x01)
	{
		LevelEditorTools& leveleditor = LevelEditorTools::Instance();

		auto pos = leveleditor.placeObject();

		switch (selected_type)
		{
		case BLOCK:
		{
			Block block;
			block.SetPosition(pos);
			block.SetScale({ 0.1f, 0.1f, 0.1f });
			blocks.push_back(std::move(block));
			break;
		}
		case GROUND_BLOCK:
		{
			Ground_Block block;
			block.SetPosition(pos);
			block.SetScale({ 0.1f, 0.1f, 0.1f });
			ground_blocks.push_back(std::move(block));
			break;
		}
		case SLOPE:
		{
			Slope block;
			block.SetPosition(pos);
			block.SetScale({ 0.1f, 0.1f, 0.1f });
			slopes.push_back(std::move(block));
			break;
		}
		case SPIKE:
		{
			Spike block;
			block.SetPosition(pos);
			block.SetScale({ 0.1f, 0.1f, 0.1f });
			spikes.push_back(std::move(block));
			break;
		}
		case FLAG:
		{
			Flag block;
			block.SetPosition(pos);
			block.SetScale({ 0.1f, 0.1f, 0.1f });
			flags.push_back(std::move(block));
			break;
		}
		case ARCHWAY:
		{
			Archway block;
			block.SetPosition(pos);
			block.SetScale({ 0.1f, 0.1f, 0.1f });
			archways.push_back(std::move(block));
			break;
		}
		case FLOATINGPLATFORM:
		{
			FloatingPlatform block;
			block.SetPosition(pos);
			block.SetScale({ 0.1f, 0.1f, 0.1f });
			floatingplatforms.push_back(std::move(block));
			break;
		}
		case BOX:
		{
			Box block;
			block.SetPosition(pos);
			block.SetScale({ 0.1f, 0.1f, 0.1f });
			boxes.push_back(std::move(block));
			break;
		}
		}
	}

	Camera_Controller camera_controller;
	camera_controller.Update(elapsedTime);

#endif 

	for (auto& block : blocks)
	{
		block.Update(elapsedTime);
	}
	for (auto& block : ground_blocks)
	{
		block.Update(elapsedTime);
	}
	for (auto& block : slopes)
	{
		block.Update(elapsedTime);
	}
	for (auto& block : spikes)
	{
		block.Update(elapsedTime);
	}
	for (auto& block : flags)
	{
		block.Update(elapsedTime);
	}
	for (auto& block : archways)
	{
		block.Update(elapsedTime);
	}
	for (auto& block : floatingplatforms)
	{
		block.Update(elapsedTime);
	}
	for (auto& block : boxes)
	{
		block.Update(elapsedTime);
	}
}



// 描画処理
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0～1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// 描画処理
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ライト方向（下方向）
	rc.view = Camera::Instance().GetView();
	rc.projection = Camera::Instance().GetProjection();

	// 3Dモデル描画
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);
		stage.get()->Render(dc, shader);
		player.get()->Render(dc, shader);

		//rendering terrain
		for (auto& block : blocks)
		{
			block.Render(dc, shader);
		}
		for (auto& block : ground_blocks)
		{
			block.Render(dc, shader);
		}
		for (auto& block : slopes)
		{
			block.Render(dc, shader);
		}
		for (auto& block : spikes)
		{
			block.Render(dc, shader);
		}
		for (auto& block : flags)
		{
			block.Render(dc, shader);
		}
		for (auto& block : archways)
		{
			block.Render(dc, shader);
		}
		for (auto& block : floatingplatforms)
		{
			block.Render(dc, shader);
		}
		for (auto& block : boxes)
		{
			block.Render(dc, shader);
		}
		shader->End(dc);
	}

	// 3Dデバッグ描画
	//{

	//}
	// 2Dスプライト描画
	{

	}

	// 2DデバッグGUI描画
	{

	}
}
