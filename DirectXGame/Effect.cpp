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

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	//　行列を更新
	worldTransform_.UpdateMatrix();
}

void Effect::Draw(KamataEngine::Camera& camera) {
	model_->Draw(worldTransform_, camera);
}
