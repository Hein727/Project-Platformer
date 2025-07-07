#pragma once
#include "Stage.h"
#include <memory>
#include "Player.h"


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


private :
	
	std::unique_ptr<Stage> stage;

	std::unique_ptr<Player> player;

	/*Transform dummyCubeTransform;*/
};
