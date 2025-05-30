#include <algorithm>
#include "Particle.h"

using namespace KamataEngine;
using namespace MathUtility;

void Particle::Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position, KamataEngine::Vector3 velocity) {
	// NULLポインタチャック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	worldTransform_.translation_ = position;
	velocity_ = velocity;

	//　色の設定
	objectColor_.Initialize();
	color_ = { 1, 1, 0, 1 };

	// 大きさ
	radius_ = { 0.2f, 0.2f, 0.2f };

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Particle::Update() {
	// 色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	// 移動
	worldTransform_.translation_ += velocity_;
	// スケール
	worldTransform_.scale_ = radius_;

	// 終了なら何もしない
	if (isFinished_) {
		return;
	}

	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// フェード処理
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);

	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// 行列を更新
	worldTransform_.UpdateMatrix();
}

void Particle::Draw(KamataEngine::Camera& camera) {
	model_->Draw(worldTransform_, camera, &objectColor_);
}
