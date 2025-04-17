#pragma once
#include "KamataEngine.h"
#include "Particle.h"

class GameScene {
public:
	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// パーティクル発生
	void ParticleBorn(KamataEngine::Vector3 position);

private:
	// パーティクル3Dモデルデータ
	KamataEngine::Model* modelParticle_ = nullptr;
	// パーティクル
	std::list<Particle*> particles_;

	// カメラ
	KamataEngine::Camera camera_;
};

