#pragma once
#include "Stage.h"
#include <memory>
#include <vector>
#include "Player.h"
#include "Terrain_Material.h"



// ゲームシーン
class SceneGame
{
public:
	SceneGame() {}
	~SceneGame() {}

	// 初期化
	void Initialize();

	// 終了化
	void Finalize();

	// 更新処理
	void Update(float elapsedTime);

	// 描画処理
	void Render();


private:

	std::unique_ptr<Stage> stage;

	/*Transform dummyCubeTransform;*/

	std::vector<Block> blocks;
	std::vector<Ground_Block> ground_blocks;
	std::vector<Slope> slopes;
	std::vector<Spike> spikes;
	std::vector<Flag> flags;
	std::vector<Archway> archways;
	std::vector<FloatingPlatform> floatingplatforms;
	std::vector<Box> boxes;

#ifdef _DEBUG
	int selected_type = 0;
	DirectX::XMFLOAT3 cursorPos = { 0,0,0 };

	struct Object
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 rotation;
		DirectX::XMFLOAT3 scale;
	};
	Object obj;
#endif

};

enum LevelEditing
{
	BLOCK = 1,
	GROUND_BLOCK,
	SLOPE,
	SPIKE,
	FLAG,
	ARCHWAY,
	FLOATINGPLATFORM,
	BOX,
	DEL
};