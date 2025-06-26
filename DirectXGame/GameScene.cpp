#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() { 
	// 解放処理
	for (int i = 0; i < 2; i++) {
		delete sprite_[i];
	}
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_[0] = TextureManager::Load("Haikei1.png");
	textureHandle_[1] = TextureManager::Load("Haikei2.png");

	// スプライトの生成
	sprite_[0] = Sprite::Create(textureHandle_[0], { 0, 0 });
	sprite_[1] = Sprite::Create(textureHandle_[1], { 0, 0 });

	// ワールド変数の初期化
	worldTransfrom_.Initialize();
}

void GameScene::Update() {
	// 画面スクロール
	bg1X = bg1X - bg_speed;
	bg2X = bg2X - bg_speed;

	if (bg1X < -1270 && bg2X < 0) {
		bg1X = 1270;
	}
	if (bg2X < -1270 && bg1X < 0) {
		bg2X = 1270;
	}

	// 座標の設定
	sprite_[0]->SetPosition({ bg1X, 0 });
	sprite_[1]->SetPosition({ bg2X, 0 });

	// 行列を更新
	worldTransfrom_.UpdateMatrix();
}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	// 描画
	sprite_[0]->Draw();
	sprite_[1]->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}
