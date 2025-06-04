#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	// 3Dモデルの解放
	delete model_;

	Model2::StaticFinalize();
}

void GameScene::Initialize() {
	Model2::StaticInitialize();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// 3Dモデルの生成
	model_ = Model2::CreateRing(10);

	// ワールドトランスフォームの初期化
	worldTransforms_.Initialize();
	// カメラの初期化
	camera_.Initialize();
}

void GameScene::Update() {
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model2::PreDraw(dxCommon->GetCommandList());

	// モデル描画
	model_->Draw(worldTransforms_, camera_, textureHandle_);

	// 3Dモデル描画後処理
	Model2::PostDraw();
}
