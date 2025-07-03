#pragma once
#include "KamataEngine.h"

class GraphBar {
public:
	~GraphBar();

	void Initialize();

	void Update();

	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;

	// テクスチャハンドル
	uint32_t textureHandle_[3];

	// スプライト
	KamataEngine::Sprite* sprite_[3];
};

