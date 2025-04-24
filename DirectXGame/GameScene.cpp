#include <random>
#include "GameScene.h"

using namespace KamataEngine;
using namespace MathUtility;

GameScene::~GameScene() {
	// エフェクト解除
	delete modelEffect_;
}

void GameScene::Initialize() {
	// 3Dモデルデータの作成
	modelEffect_ = Model::CreateFromOBJ("diamond", true);

	// エフェクトの生成
	effect_ = new Effect();
	effect_->Initialize(modelEffect_);

	// カメラの初期化
	camera_.Initialize();
}

void GameScene::Update() {
	// エフェクトを更新
	effect_->Update();
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// エフェクトの描画
	effect_->Draw(camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
}
