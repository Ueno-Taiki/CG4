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

	// 移動
	worldTransform_.translation_ += {0.5f, 0.0f, 0.0f};
	// 大きさ
	worldTransform_.scale_ = radius_;
	// 角度
	worldTransform_.rotation_ = angle_;

	// 終了なら何もしない
	if (isFinished_) {
		return;
	}

	//　カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 120.0f;

	// フェード処理
	color_.w = std::clamp(1.5f - counter_ / kDuration, 0.0f, 1.0f);

	// 存続時間の上限に達したら
	if (counter_ >= kDuration){
		counter_ = kDuration;
		//　終了扱いにする
		isFinished_ = true;
	}

	//　行列を更新
	worldTransform_.UpdateMatrix();
}

void Effect::Draw(KamataEngine::Camera& camera) {
	model_->Draw(worldTransform_, camera, &objectColor_);
}

// 色の設定
void Effect::SetInitialColor(const KamataEngine::Vector4& color) {
	color_ = color;
}
