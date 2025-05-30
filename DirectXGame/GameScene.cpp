#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	// 3Dモデルの解放
	for (Model2* model : models_) {
		delete model;
	}
	models_.clear();

	Model2::StaticFinalize();
}

void GameScene::Initialize() {
	Model2::StaticInitialize();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// 3Dモデルの生成
	models_ = Model2::CreateSquare();

	// ワールドトランスフォームの初期化
	worldTransforms_.resize(models_.size());
	for (size_t i = 0; i < models_.size(); ++i) {
		worldTransforms_[i].translation_ = { static_cast<float>(i) * 2.0f, 0.0f, 0.0f }; // X方向に間隔を空けて配置
		worldTransforms_[i].Initialize();
	}

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
	for (size_t i = 0; i < models_.size(); ++i) {
		models_[i]->Draw(worldTransforms_[i], camera_);
	}

	// 3Dモデル描画後処理
	Model2::PostDraw();
}
