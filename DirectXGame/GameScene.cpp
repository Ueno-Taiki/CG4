#include "GameScene.h"

GameScene::~GameScene() {
	// 3Dモデルデータの解放
	delete modelParticle_;
	// パーティクルの解放
	for (Particle* particle : particles_){
		delete particle;
	}
	particles_.clear();
}

void GameScene::Initialize() {
	// 3Dモデルデータの作成
	modelParticle_ = Model::CreateSphere(4, 4);

	// パーティクルの生成
	for (int i = 0; i < 150; i++) {
		// 生成
		Particle* particle = new Particle();
		// 位置
		Vector3 position = { 0.5f * i, 0.0f, 0.0f };
		// パーティクルの初期化
		particle->Initialize(modelParticle_, position);
		// リストに追加
		particles_.push_back(particle);
	}

	// カメラの初期化
	camera_.Initialize();
}

void GameScene::Update() {
	// パーティクルの更新
	for (Particle* particle : particles_) {
		particle->Update();
	}
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// パーティクルの描画
	for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();
}
