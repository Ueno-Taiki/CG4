#include <algorithm>
#include "Effect.h"

using namespace KamataEngine;
using namespace MathUtility;

void Effect::Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position, KamataEngine::Vector3 radius, KamataEngine::Vector3 angle) {
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	worldTransform_.translation_ = position;
	radius_ = radius;
	angle_ = angle;

	// 色の設定
	objectColor_.Initialize();
	color_ = { 1, 1, 1, 1 };

	// ワールドの初期化
	worldTransform_.Initialize();
}

void Effect::Update() {
	// 色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	// xが0以上になるまで移動
	if (!startedTransform_) {
		worldTransform_.translation_ += {0.5f, 0.0f, 0.0f};

		// xが0以上になったら処理開始
		if (worldTransform_.translation_.x >= 0.0f) {
			worldTransform_.translation_.x = 0.0f;  // ちょうど0に固定（ぴたっと止める）
			startedTransform_ = true;
		}
	}

	// 拡大・回転処理
	if (startedTransform_) {
		// 拡大
		worldTransform_.scale_ += scaleGrowRate_;
		// 回転
		worldTransform_.rotation_.y += angleSpeed_;
	}
	else {
		// 初期スケール維持
		worldTransform_.scale_ = radius_;
		// 初期角度も維持
		worldTransform_.rotation_ = angle_;
	}

	// 終了なら何もしない
	if (isFinished_) {
		return;
	}

	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 120.0f;

	// フェード処理
	color_.w = std::clamp(1.5f - counter_ / kDuration, 0.0f, 1.0f);

	// 終了条件
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		isFinished_ = true;
	}

	// 行列を更新
	worldTransform_.UpdateMatrix();
}

void Effect::Draw(KamataEngine::Camera& camera) {
	model_->Draw(worldTransform_, camera, &objectColor_);
}

// 色の設定
void Effect::SetInitialColor(const KamataEngine::Vector4& color) {
	color_ = color;
}
