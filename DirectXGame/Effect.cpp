#include <algorithm>
#include "Effect.h"

using namespace KamataEngine;

void Effect::Initialize(KamataEngine::Model* model, KamataEngine::Vector3 radius, KamataEngine::Vector3 angle) {
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	radius_ = radius;
	angle_ = angle;

	// ワールドの初期化
	worldTransform_.Initialize();
}

void Effect::Update() {

	// 大きさ
	worldTransform_.scale_ = radius_;
	// 角度
	worldTransform_.rotation_ = angle_;

	// 終了なら何もしない
	if (isFinished_) {
		return;
	}

	//　カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に達したら
	if (counter_ >= kDuration){
		counter_ = kDuration;
		//　終了扱いにする
		isFinished_ = true;
	}

	// フェード処理
	color.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	//　行列を更新
	worldTransform_.UpdateMatrix();
}

void Effect::Draw(KamataEngine::Camera& camera) {
	model_->Draw(worldTransform_, camera);
}
