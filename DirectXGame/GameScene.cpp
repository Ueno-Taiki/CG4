#include <random>
#include "GameScene.h"

using namespace KamataEngine;
using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

GameScene::~GameScene() {
	// エフェクト解除
	delete modelEffect_;
}

void GameScene::Initialize() {
	// 3Dモデルデータの作成
	modelEffect_ = Model::CreateFromOBJ("diamond", true);

	// エフェクトの生成
	effect_ = new Effect();

	// 乱数設定
	std::uniform_real_distribution<float> sizeDist(0.5f, 2.0f); 
	std::uniform_real_distribution<float> angleDegDist(0.0f, 360.0f); 

	// 回転角度
	float angleInDegrees = angleDegDist(randomEngine);
	float angleInRadians = angleInDegrees * (3.14159265f / 180.0f);

	// 大きさ
	Vector3 radius = { 1.0f, sizeDist(randomEngine), 1.0f };
	// 角度
	Vector3 angle = { 0, 0, angleInRadians };
	// 初期化
	effect_->Initialize(modelEffect_,radius,angle);

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
