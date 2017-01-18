#include "GameScene.h"

#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "TileManager.h"

using namespace CocosDenshion;

GameScene * GameScene::create(int column, int row) {
	auto scene = new GameScene();

	scene->init(column, row);
	scene->autorelease();

	return scene;
}

bool GameScene::init(int column, int row) {
	Scene::init();

	//背景の生成
	back();
	//爆弾数の生成
	mineNum();
	//メニューの生成
	menu();

	//盤面の生成
	auto tileMgr = TileManager::create();
	addChild(tileMgr);

	return true;
}

void GameScene::back(){
	auto winSize = Director::getInstance()->getWinSize();

	//背景
	auto back_ground = Sprite::create("back_ground.png");
	back_ground->setScale(winSize.height / back_ground->getContentSize().height);
	back_ground->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	back_ground->setPosition(0, 0);
	addChild(back_ground);
}

void GameScene::mineNum(){
	auto winSize = Director::getInstance()->getWinSize();

	//爆弾アイコン
	auto mine = Sprite::create("mine_logo.png");
	mine->setScale(160.0f / mine->getContentSize().width);
	mine->setPosition(Vec2(winSize.width / 2, winSize.height * 0.8f) - Vec2(80.0f, 0));
	addChild(mine);

	//爆弾数
	auto mine_num = Sprite::create("mine_count.png");
	mine_num->setScale(160.0f / mine_num->getContentSize().width);
	mine_num->setPosition(Vec2(winSize.width / 2, winSize.height * 0.8f) + Vec2(80.0f, 0));
	addChild(mine_num);

}

void GameScene::menu(){
	auto winSize = Director::getInstance()->getWinSize();

	//リセットボタン
	auto sprite_reset_on = Sprite::create("reset.png");
	auto sprite_reset_off = Sprite::create("reset.png");
	sprite_reset_off->setColor(Color3B(180, 180, 180));
	auto reset_item = MenuItemSprite::create(sprite_reset_on, sprite_reset_off, [this](Ref* item) {reset(); });
	reset_item->setScale(winSize.width / 10 / reset_item->getContentSize().height);

	//戻るボタン
	auto sprite_back_on = Sprite::create("back.png");
	auto sprite_back_off = Sprite::create("back.png");
	sprite_back_off->setColor(Color3B(180, 180, 180));
	auto back_item = MenuItemSprite::create(sprite_back_on, sprite_back_off, [this](Ref* item) {backToTitle(); });
	back_item->setScale(winSize.width / 10 / back_item->getContentSize().height);

	//メニューの生成
	auto menu = Menu::create(back_item, reset_item, nullptr);
	menu->alignItemsHorizontallyWithPadding(200.0f);
	menu->setPosition(winSize.width / 2, winSize.height * 0.15f);
	addChild(menu);
}

void GameScene::reset() {
	//ゲームのリセット(シーンを読み込みなおす)
	auto newScene = create(0, 0);
	auto trans = /*TransitionFadeBL*/TransitionCrossFade::create(1, newScene);
	Director::getInstance()->replaceScene(trans);
}

void GameScene::backToTitle(){
	//タイトル画面に戻る
	auto newScene = TitleScene::create();
	auto trans = TransitionFade::create(1, newScene);
	Director::getInstance()->replaceScene(trans);
}

