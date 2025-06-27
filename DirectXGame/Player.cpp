#include <cassert>
#include "Player.h"

using namespace KamataEngine;

void Player::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position) {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録
	model_ = model;
	worldTransfrom_.translation_ = position;

	// ワールト座標の初期化
	worldTransfrom_.Initialize();
}

void Player::Update() { 
	// プレイヤー移動
	if (input_->PushKey(DIK_W)) {
		worldTransfrom_.translation_.y += 0.5f;
	}
	if (input_->PushKey(DIK_S)) {
		worldTransfrom_.translation_.y -= 0.5f;
	}
	if (input_->PushKey(DIK_D)) {
		worldTransfrom_.translation_.x += 0.5f;
	}
	if (input_->PushKey(DIK_A)) {
		worldTransfrom_.translation_.x -= 0.5f;
	}

	// 範囲制限
	if (worldTransfrom_.translation_.x >= 21.4) {
		worldTransfrom_.translation_.x = 21.4f;
	}
	if (worldTransfrom_.translation_.y >= 11.8) {
		worldTransfrom_.translation_.y = 11.8f;
	}
	if (worldTransfrom_.translation_.x <= -21.4) {
		worldTransfrom_.translation_.x = -21.4f;
	}

	if (worldTransfrom_.translation_.y <= -11.8) {
		worldTransfrom_.translation_.y = -11.8f;
	}
	
	// 行列を更新
	worldTransfrom_.UpdateMatrix();
}

void Player::Draw(KamataEngine::Camera& camera) {
	// 3Dモデルを描画
	model_->Draw(worldTransfrom_, camera);
}
