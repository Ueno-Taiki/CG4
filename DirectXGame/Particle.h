#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Particle {
public:
	// 初期化
	void Initialize(Model* model, Vector3 position, Vector3 velocity);

	// 更新
	void Update();

	// 描画
	void Draw(Camera& camera);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	// 色変更オブジェクト
	ObjectColor objectColor_;
	// 色の数値
	Vector4 color_;
	// 移動量
	Vector3 velocity_;
	// 大きさ
	Vector3 radius_;
};

