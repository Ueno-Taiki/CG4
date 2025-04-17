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
	particle_->Initialize(modelParticle_);

	// カメラの初期化
	camera_.Initialize();
}

void GameScene::Update() {
	// パーティクルの更新
	particle_->Update();
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// パーティクルの描画
	particle_->Draw(camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
}
