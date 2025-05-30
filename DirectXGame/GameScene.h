#pragma once
#include "KamataEngine.h"
#include "Model2.h"

class GameScene {
public:

	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 3Dモデル
	KamataEngine::Model2* model_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransforms_;
	// カメラ
	KamataEngine::Camera camera_;
};

