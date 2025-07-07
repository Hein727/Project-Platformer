#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "Transform.h"
#include "Camera.h"


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
		shader->End(dc);
	}

	// 3Dデバッグ描画
	//{
	//	// Transform → 行列に変換
	//	using namespace DirectX;

	//	XMMATRIX matScale = XMMatrixScaling(
	//		dummyCubeTransform.scale.x,
	//		dummyCubeTransform.scale.y,
	//		dummyCubeTransform.scale.z
	//	);
	//	XMMATRIX matRot = XMMatrixRotationRollPitchYaw(
	//		dummyCubeTransform.rotation.x,
	//		dummyCubeTransform.rotation.y,
	//		dummyCubeTransform.rotation.z
	//	);
	//	XMMATRIX matTrans = XMMatrixTranslation(
	//		dummyCubeTransform.position.x,
	//		dummyCubeTransform.position.y,
	//		dummyCubeTransform.position.z
	//	);
	//	XMMATRIX world = matScale * matRot * matTrans;

	//	// DebugRenderer でダミーキューブ描画
	//	graphics.GetDebugRenderer()->AddBox(
	//		dummyCubeTransform.position,
	//		dummyCubeTransform.scale,
	//		{ 1, 1, 0, 1 } // 黄色
	//	);
	//}
	// 2Dスプライト描画
	{

	}

	// 2DデバッグGUI描画
	{
	// ImGui で Transform を編集できるようにする
	ImGui::Begin("Transform Editor");
	/*ImGui::SliderFloat3("Position", &dummyCubeTransform.position.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("Rotation", &dummyCubeTransform.rotation.x, -DirectX::XM_PI, DirectX::XM_PI);
	ImGui::SliderFloat3("Scale", &dummyCubeTransform.scale.x, 0.1f, 5.0f);*/
	ImGui::End();
	}
}
