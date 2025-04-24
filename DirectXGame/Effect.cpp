#include "Effect.h"

void Effect::Initialize(KamataEngine::Model* model) {
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	// ワールドの初期化
	worldTransform_.Initialize();
}

void Effect::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Effect::Draw(KamataEngine::Camera& camera) {
	model_->Draw(worldTransform_, camera);
}
