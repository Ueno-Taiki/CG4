#include "GameScene.h"

GameScene::~GameScene() {
	// 3Dモデルデータの解放
	delete modelParticle_;
	// パーティクルの解放
	delete particle_;
}

void GameScene::Initialize() {
	// 3Dモデルデータの作成
	modelParticle_ = Model::CreateSphere(4, 4);

	// パーティクルの生成
	particle_ = new Particle();
	// パーティクルの初期化
	particle_->Initialize();

	// カメラの初期化
	camera_.Initialize();
}

void GameScene::Update() {
	// パーティクルの更新
	particle_->Update();
}

void GameScene::Draw() {
	// パーティクルの描画
	particle_->Draw();
}
