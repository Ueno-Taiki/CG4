#include "TitleScene.h"
#include <cassert>

using namespace KamataEngine;

//イーズアウトクアッド
float EaseOutQuad(float x) {
	return 1 - (1 - x) * (1 - x);
}

TitleScene::~TitleScene() { 
	// 解放処理
	for (int i = 0; i < 3; i++) {
		delete sprite_[i];
	}
}

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ワールド変数の初期化
	worldTransfrom_.Initialize();
	worldTransfrom_.scale_ = {2, 2, 2};

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_[0] = TextureManager::Load("Title.png");
	textureHandle_[1] = TextureManager::Load("UI/Moji1.png");
	textureHandle_[2] = TextureManager::Load("UI/Moji2.png");

	// スプライトの生成
	sprite_[0] = Sprite::Create(textureHandle_[0], {0, 0});
	sprite_[1] = Sprite::Create(textureHandle_[1], {0, 0});
	sprite_[2] = Sprite::Create(textureHandle_[2], {250, 450});
}

void TitleScene::Update() {
	// isMoveがtrueの時
	if (isMoveY) {
		frameY++;

		y = static_cast<float>(frameY) / endFrameY;

		posY = startY + (endY - startY) * EaseOutQuad(y);

		sprite_[1]->SetPosition({posX, posY});
	}

	// 時間制限
	if (frameY == endFrameY) {
		isMoveY = false;
		frameY = 0.0f;
	}

	// 点滅用フレームカウント
	frameCount_++;

	// 行列を更新
	worldTransfrom_.UpdateMatrix();
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	// 描画
	sprite_[0]->Draw();
	sprite_[1]->Draw();
	if (frameCount_ % 60 >= 30) {
		sprite_[2]->Draw();
	}
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}

