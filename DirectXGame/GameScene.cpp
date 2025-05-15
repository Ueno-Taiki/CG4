#include <random>
#include "GameScene.h"

using namespace KamataEngine;
using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

GameScene::~GameScene() {
	// モデル解除
	delete modelEffect_;
	// エフェクトの解放
	for (Effect* effect : effects_) {
		delete effect;
	}
	effects_.clear();
}

void GameScene::Initialize() {
	// 3Dモデルデータの作成
	modelEffect_ = Model::CreateFromOBJ("diamond", true);

	// 乱数の初期化
	srand((unsigned)time(NULL));

	// カメラの初期化
	camera_.Initialize();
}

void GameScene::Update() {
	// 確率で発生
	if (rand() % 20 == 0) {
		// 発生位置は乱数
		Vector3 position = { -30.0f, 0.0f, 0 };
		// パーティクル発生
		EffectBorn(position);
	}

	// エフェクトを更新
	for (Effect* effect : effects_) {
		effect->Update();
	}

	// 終了フラグの立ったエフェクトを削除
	effects_.remove_if([](Effect* effect) {
		if (effect->IsFinished()) {
			delete effect;
			return true;
		}
		return false;
	});
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// エフェクトの描画
	for (Effect* effect : effects_) {
		effect->Draw(camera_);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();
}

// エフェクト発生
void GameScene::EffectBorn(KamataEngine::Vector3 position) {
	std::uniform_real_distribution<float> sizeDist(0.5f, 2.0f);
	std::uniform_real_distribution<float> angleRadDist(0.0f, 2.0f * 3.14159265f);
	std::uniform_real_distribution<float> colorDist(0.0f, 1.0f); // 色用のランダム分布

	for (int i = 0; i < 10; i++) {
		// 生成
		Effect* effect = new Effect();

		// 回転角度 (ラジアン)
		float angleInRadians = angleRadDist(randomEngine);
	
		// 位置
		Vector3 Position = position;

		// 大きさ
		Vector3 radius = { 1.0f, sizeDist(randomEngine) * 5, 1.0f };

		// 角度
		Vector3 angle = { 0, 0, angleInRadians };

		// ランダムな色の生成
		Vector4 initialColor = {
			colorDist(randomEngine), 
			colorDist(randomEngine), 
			colorDist(randomEngine), 
			1.0f                     
		};

		// 初期化
		effect->Initialize(modelEffect_, position, radius, angle);

		// 色の初期化
		effect->SetInitialColor(initialColor);

		// リストに追加
		effects_.push_back(effect);
	}
}
