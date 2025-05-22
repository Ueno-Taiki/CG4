#pragma once
#include "KamataEngine.h"
#include "Model2.h"

class GameScene {
public:
	GameScene();

	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// モデル
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model2* model2_ = nullptr;
};

