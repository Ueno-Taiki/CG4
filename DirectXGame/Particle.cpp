#include "Particle.h"

using namespace MathUtility;

void Particle::Initialize(Model* model) {
	// NULLポインタチャック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//　色の設定
	objectColor_.Initialize();
	color_ = { 1, 1, 0, 1 };

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Particle::Update() {
	// 色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	// 移動
	worldTransform_.translation_ += {0.0f, 0.1f, 0.0f};

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// 行列を更新
	worldTransform_.UpdateMatrix();
}

void Particle::Draw(Camera& camera) {
	model_->Draw(worldTransform_, camera, &objectColor_);
}
