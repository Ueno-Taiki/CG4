#pragma once
#include "KamataEngine.h"

class Effect {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 radius, KamataEngine::Vector3 angle);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;

	// 大きさ
	KamataEngine::Vector3 radius_;
	// 角度
	KamataEngine::Vector3 angle_;
};

