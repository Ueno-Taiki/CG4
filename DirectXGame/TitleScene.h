#pragma once

#include "KamataEngine.h"

class TitleScene {
public:
	~TitleScene();

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

	// イージング関数
	float posX = 250.0f, posY = -150.0f;
	float y = 0;
	float startY = -150.0f;
	float endY = 150.0f;
	float frameY = 0;
	float endFrameY = 360;

	// フレームカウント
	int frameCount_ = 0;

	// フラグ関数
	bool isMoveY = true;
};