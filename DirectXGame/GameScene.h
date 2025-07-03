#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "GraphBar.h"

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
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;

	// カメラ
	KamataEngine::Camera camera_;

	// プレイヤー
	Player* player_ = nullptr;
	// プレイヤーモデル
	KamataEngine::Model* modelPlayer_ = nullptr;

	// 体力バー
	GraphBar* graphBar_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_[2];

	// スプライト
	KamataEngine::Sprite* sprite_[2];

	// 背景画像
	float bg1X = 0.0f, bg2X = 1280.0f;
	float bg_speed = 2.0f;
};

