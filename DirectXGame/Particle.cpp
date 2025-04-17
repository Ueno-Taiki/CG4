#include "Particle.h"

void Particle::Initialize(Model* model) {
	// NULLポインタチャック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Particle::Update() {

}

void Particle::Draw() {

}
