#include "GraphBar.h"
#include <cassert>

using namespace KamataEngine;

GraphBar::~GraphBar() {
	// 解放処理
	for (int i = 0; i < 3; i++) {
		delete sprite_[i];
	}
}

void GraphBar::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ワールド変数の初期化
	worldTransfrom_.Initialize();
	worldTransfrom_.scale_ = { 2, 2, 2 };

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_[0] = TextureManager::Load("UI/LifeBar.png");
	textureHandle_[1] = TextureManager::Load("UI/Life2.png");
	textureHandle_[2] = TextureManager::Load("UI/life1.png");

	// スプライトの生成
	sprite_[0] = Sprite::Create(textureHandle_[0], { 100, 20 });
	sprite_[1] = Sprite::Create(textureHandle_[1], { 116, 35 });
	sprite_[2] = Sprite::Create(textureHandle_[2], { 116, 35 });
}

void GraphBar::Update() { 
	// 現在の座標を取得
	Vector2 spriteSize = sprite_[2]->GetSize();

	// 縮小率
	float shrinkSpeed = 1.0f;

	// サイズがゼロ以上の時だけ縮小
	if (spriteSize.x > 0) {
		spriteSize.x -= shrinkSpeed;

		// 最小サイズに制限
		if (spriteSize.x < 0) {
			spriteSize.x = 0;
		}

		// 位置は変えない
		sprite_[2]->SetSize(spriteSize);
	}

	// 行列を更新
	worldTransfrom_.UpdateMatrix();
}

void GraphBar::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	// 描画
	sprite_[0]->Draw();
	sprite_[1]->Draw();
	sprite_[2]->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}


