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

	std::unique_ptr<Player> player;

	/*Transform dummyCubeTransform;*/

	std::vector<Block> blocks;
	std::vector<Ground_Block> ground_blocks;
	std::vector<Slope> slopes;
	std::vector<Spike> spikes;
	std::vector<Flag> flags;
	std::vector<Archway> archways;
	std::vector<FloatingPlatform> floatingplatforms;
	std::vector<Box> boxes;


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
	BOX
};