#include "GameScene.h"

using namespace KamataEngine;

GameScene::GameScene() { 
	Model2::StaticInitialize();
}

GameScene::~GameScene() {
	Model2::StaticFinalize();
}

void GameScene::Initialize() {

}

void GameScene::Update() {

}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// 3Dモデル描画後処理
	Model::PostDraw();
}
