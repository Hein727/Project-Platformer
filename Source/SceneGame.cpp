#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "Transform.h"
#include "Camera.h"
#include "LevelEditorTools.h"
#include "Camera_Controller.h"
#include "Input/GamePad.h"
#include "Input/Input.h"
#include "Level_Loader.h"
#include <string>


// 初期化
void SceneGame::Initialize()
{
	stage = std::make_unique<Stage>();

	Player& player = Player::Instance();

	Level_Loader& levelLoader = Level_Loader::Instance();

	levelLoader.Load();

	auto& save_data = levelLoader.getSaveData();

	for (auto& save : save_data)
	{
		if (save.name == "BLOCK")
		{
			Block block;
			block.SetPosition(save.position);
			block.SetScale(save.scale);
			blocks.push_back(std::move(block));
		}
		if (save.name == "GROUND_BLOCK")
		{
			Ground_Block block;
			block.SetPosition(save.position);
			block.SetScale(save.scale);
			ground_blocks.push_back(std::move(block));
		}
		if (save.name == "SLOPE")
		{
			Slope block;
			block.SetPosition(save.position);
			block.SetScale(save.scale);
			slopes.push_back(std::move(block));
		}
		if (save.name == "SPIKE")
		{
			Spike block;
			block.SetPosition(save.position);
			block.SetScale(save.scale);
			spikes.push_back(std::move(block));
		}
		if (save.name == "FLAG")
		{
			Flag block;
			block.SetPosition(save.position);
			block.SetScale(save.scale);
			flags.push_back(std::move(block));
		}
		if (save.name == "FLOATING_PLATFORM")
		{
			FloatingPlatform block;
			block.SetPosition(save.position);
			block.SetScale(save.scale);
			floatingplatforms.push_back(std::move(block));
		}
		if (save.name == "ARCHWAY")
		{
			Archway block;
			block.SetPosition(save.position);
			block.SetScale(save.scale);
			archways.push_back(std::move(block));
		}
		if (save.name == "BOX")
		{
			Box block;
			block.SetPosition(save.position);
			block.SetScale(save.scale);
			boxes.push_back(std::move(block));
		}
		if (save.name == "PLAYER")
		{
			player.SetPosition(save.position);
			player.SetRotation(save.rotation);
			player.SetScale(save.scale);
		}
	}
	save_data.clear();

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
	Level_Loader& levelLoader = Level_Loader::Instance();

	auto& saveData = levelLoader.getSaveData();

	for (auto& block : blocks)
	{
		saveData.emplace_back("BLOCK", block.GetPosition(), block.GetRotation(), block.GetScale());
	}
	for (auto& block : ground_blocks)
	{
		saveData.emplace_back("GROUND_BLOCK", block.GetPosition(), block.GetRotation(), block.GetScale());
	}
	for (auto& block : slopes)
	{
		saveData.emplace_back("SLOPE", block.GetPosition(), block.GetRotation(), block.GetScale());
	}
	for (auto& block : spikes)
	{
		saveData.emplace_back("SPIKE", block.GetPosition(), block.GetRotation(), block.GetScale());
	}
	for (auto& block : flags)
	{
		saveData.emplace_back("FLAG", block.GetPosition(), block.GetRotation(), block.GetScale());
	}
	for (auto& block : floatingplatforms)
	{
		saveData.emplace_back("FLOATING_PLATFORM", block.GetPosition(), block.GetRotation(), block.GetScale());
	}
	for (auto& block : archways)
	{
		saveData.emplace_back("ARCHWAY", block.GetPosition(), block.GetRotation(), block.GetScale());
	}
	for (auto& block : boxes)
	{
		saveData.emplace_back("BOX", block.GetPosition(), block.GetRotation(), block.GetScale());
	}
	

	levelLoader.SaveInTxt();
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	Player& player = Player::Instance();

	stage->Update(elapsedTime);

	player.Update(elapsedTime);

#ifdef _DEBUG

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
	if (GetAsyncKeyState('0') & 0x8000)
	{
		selected_type = DEL;
	}


	LevelEditorTools& leveleditor = LevelEditorTools::Instance();

	bool mousePressed = false;

	cursorPos = leveleditor.placeObject(&mousePressed);

	if (mousePressed)
	{
		switch (selected_type)
		{
		case BLOCK:
		{
			Block block;
			block.SetPosition(cursorPos);
			block.SetScale({ 0.01f, 0.01f, 0.01f });
			blocks.push_back(std::move(block));
			break;
		}
		case GROUND_BLOCK:
		{
			Ground_Block block;
			block.SetPosition(cursorPos);
			block.SetScale({ 0.005f, 0.005f, 0.005f });
			ground_blocks.push_back(std::move(block));
			break;
		}
		case SLOPE:
		{
			Slope block;
			block.SetPosition(cursorPos);
			block.SetScale({ 0.01f, 0.01f, 0.01f });
			slopes.push_back(std::move(block));
			break;
		}
		case SPIKE:
		{
			Spike block;
			block.SetPosition(cursorPos);
			block.SetScale({ 0.01f, 0.01f, 0.01f });
			spikes.push_back(std::move(block));
			break;
		}
		case FLAG:
		{
			Flag block;
			block.SetPosition(cursorPos);
			block.SetScale({ 0.01f, 0.01f, 0.01f });
			flags.push_back(std::move(block));
			break;
		}
		case ARCHWAY:
		{
			Archway block;
			block.SetPosition(cursorPos);
			block.SetScale({ 0.005f, 0.005f, 0.005f });
			archways.push_back(std::move(block));
			break;
		}
		case FLOATINGPLATFORM:
		{
			FloatingPlatform block;
			block.SetPosition(cursorPos);
			block.SetScale({ 0.01f, 0.01f, 0.01f });
			floatingplatforms.push_back(std::move(block));
			break;
		}
		case BOX:
		{
			Box block;
			block.SetPosition(cursorPos);
			block.SetScale({ 0.01f, 0.01f, 0.01f });
			boxes.push_back(std::move(block));
			break;
		}
		case DEL:
		{
			for (auto it = blocks.begin(); it != blocks.end();)
			{
				HitBox& box = it->getHitBox();

				if (leveleditor.objectDelete(box, cursorPos))
				{
					it = blocks.erase(it);
				}
				else
				{
					it++;
				}
			}
			for (auto it = ground_blocks.begin(); it != ground_blocks.end();)
			{
				HitBox& box = it->getHitBox();

				bool check = leveleditor.objectDelete(box, cursorPos);

				if (check)
				{
					it = ground_blocks.erase(it);
				}
				else
				{
					it++;
				}
			}
			for (auto it = slopes.begin(); it != slopes.end();)
			{
				HitBox& box = it->getHitBox();

				bool check = leveleditor.objectDelete(box, cursorPos);

				if (check)
				{
					it = slopes.erase(it);
				}
				else
				{
					it++;
				}
			}
			for (auto it = spikes.begin(); it != spikes.end();)
			{
				HitBox& box = it->getHitBox();

				bool check = leveleditor.objectDelete(box, cursorPos);

				if (check)
				{
					it = spikes.erase(it);
				}
				else
				{
					it++;
				}
			}
			for (auto it = flags.begin(); it != flags.end();)
			{
				HitBox& box = it->getHitBox();

				bool check = leveleditor.objectDelete(box, cursorPos);

				if (check)
				{
					it = flags.erase(it);
				}
				else
				{
					it++;
				}
			}
			for (auto it = archways.begin(); it != archways.end();)
			{
				HitBox& box = it->getHitBox();

				bool check = leveleditor.objectDelete(box, cursorPos);

				if (check)
				{
					it = archways.erase(it);
				}
				else
				{
					it++;
				}
			}
			for (auto it = floatingplatforms.begin(); it != floatingplatforms.end();)
			{
				HitBox& box = it->getHitBox();

				bool check = leveleditor.objectDelete(box, cursorPos);

				if (check)
				{
					it = floatingplatforms.erase(it);
				}
				else
				{
					it++;
				}
			}
			for (auto it = boxes.begin(); it != boxes.end();)
			{
				HitBox& box = it->getHitBox();

				bool check = leveleditor.objectDelete(box, cursorPos);

				if (check)
				{
					it = boxes.erase(it);
				}
				else
				{
					it++;
				}
			}
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
		//stage.get()->Render(dc, shader);
		//player.get()->Render(dc, shader);

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

	 //3Dデバッグ描画
	{

	}

	// 2Dスプライト描画
	{

	}

	// 2DデバッグGUI描画
	{
		static const char* name = "None";

		ImGui::Begin("Selected Block");

		switch (selected_type)
		{
		case BLOCK:
			name = "BLOCK";
			break;

		case GROUND_BLOCK:
			name = "GROUND_BLOCK";
			break;

		case SLOPE:
			name = "SLOPE";
			break;

		case SPIKE:
			name = "SPIKE";
			break;

		case FLAG:
			name = "FLAG";
			break;

		case ARCHWAY:
			name = "ARCHWAY";
			break;

		case FLOATINGPLATFORM:
			name = "FLOATING_PLATFORM";
			break;

		case BOX:
			name = "BOX";
			break;

		case DEL:
			name = "DELETE_MODE";
			break;
		}

		ImGui::Text("Editor Mode:%s", name);

		ImGui::End();

	}
}