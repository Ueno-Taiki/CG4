#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() { 
	// 解放処理
	delete modelPlayer_;
	for (int i = 0; i < 2; i++) {
		delete sprite_[i];
	}
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルデータの生成
	modelPlayer_ = Model::CreateFromOBJ("player", true);

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_[0] = TextureManager::Load("Haikei1.png");
	textureHandle_[1] = TextureManager::Load("Haikei2.png");

	// プレイヤーの生成
	player_ = new Player();
	// プレイヤーの座標
	Vector3 positon = { -18, 0, -20 };
	// プレイヤーの初期化
	player_->Initialize(modelPlayer_, positon);

	// 体力バーの生成
	graphBar_ = new GraphBar();
	// 体力バーの初期化
	graphBar_->Initialize();

	// スプライトの生成
	sprite_[0] = Sprite::Create(textureHandle_[0], { 0, 0 });
	sprite_[1] = Sprite::Create(textureHandle_[1], { 0, 0 });

	// カメラの初期化
	camera_.Initialize();

	// ワールド変数の初期化
	worldTransfrom_.Initialize();
}

void GameScene::Update() {
	// 画面スクロール
	bg1X = bg1X - bg_speed;
	bg2X = bg2X - bg_speed;

	if (bg1X < -1270 && bg2X < 0) {
		bg1X = 1270;
	}
	if (bg2X < -1270 && bg1X < 0) {
		bg2X = 1270;
	}

	// 座標の設定
	sprite_[0]->SetPosition({ bg1X, 0 });
	sprite_[1]->SetPosition({ bg2X, 0 });

	// プレイヤー更新
	player_->Update();

	// 体力バー更新
	graphBar_->Update();

	// 行列を更新
	worldTransfrom_.UpdateMatrix();
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// ここに2Dスプライトの描画処理を記述する
	sprite_[0]->Draw();
	sprite_[1]->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// ここに3Dモデルインスタンスの描画処理を記述する
	player_->Draw(camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();

	// スプライト描画後処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// ここに2Dスプライトの描画処理を記述する
	graphBar_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}
