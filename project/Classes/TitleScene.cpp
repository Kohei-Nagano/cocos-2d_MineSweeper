#include "TitleScene.h"
#include "GameScene.h"

TitleScene * TitleScene::create() {
	auto scene = new TitleScene();

	scene->init();
	scene->autorelease();

	return scene;
}

bool TitleScene::init() {
	Scene::init();

	//�w�i
	back();
	//���S
	logo();
	//���j���[
	menu();

	return true;
}

void TitleScene::logo(){
	auto winSize = Director::getInstance()->getWinSize();

	//���S�̔��e�摜
	auto mine_logo = Sprite::create("mine_logo.png");
	mine_logo->setScale(winSize.width / mine_logo->getContentSize().width * 0.25f);
	mine_logo->setPosition(winSize.width * 0.23f, winSize.height * 0.77f);
	addChild(mine_logo);
	//���S�̃^�C�g���摜
	auto titleImage = Sprite::create("title_.png");
	titleImage->setScale(winSize.width / titleImage->getContentSize().width * 0.75f);
	titleImage->setPosition(winSize.width * 0.5f, winSize.height * 0.75f);
	addChild(titleImage);
}

void TitleScene::menu() {
	auto winSize = Director::getInstance()->getWinSize();

	//easy���[�h�̉摜
	auto sprite_easy_on = Sprite::create("game_start.png");
	auto sprite_easy_off = Sprite::create("game_start.png");
	sprite_easy_off->setColor(Color3B(180, 180, 180));
	auto item_easy = MenuItemSprite::create(sprite_easy_on, sprite_easy_off, [this](Ref* item) {startGame(4, 4); });
	item_easy->setScale(winSize.width / item_easy->getContentSize().width * 0.5f);

	////hard���[�h�̉摜
	//auto sprite_hard_on = Sprite::create("hard.png");
	//auto sprite_hard_off = Sprite::create("hard.png");
	//sprite_easy_off->setColor(Color3B(180, 180, 180));
	//auto item_hard = MenuItemSprite::create(sprite_hard_on, sprite_hard_off, [this](Ref* item) {startGame(5, 5); });
	//item_hard->setScale(winSize.width / item_hard->getContentSize().width * 0.25f);

	//���j���[�̐���
	auto menu = Menu::create(item_easy, /*item_hard,*/ nullptr);
	menu->alignItemsVerticallyWithPadding(200.0f);
	menu->setPosition(winSize.width / 2, winSize.height * 3 / 8);
	addChild(menu);
}

void TitleScene::back() {
	auto winSize = Director::getInstance()->getWinSize();

	//4���̔w�i�摜���X�N���[��
	tileAction(winSize / 2);
	tileAction((Vec2)winSize / 2 - Vec2(winSize.width, 0));
	tileAction((Vec2)winSize / 2 - Vec2(0, winSize.height));
	tileAction(winSize / 2 - winSize);
}

void TitleScene::tileAction(Vec2 firstPos) {
	auto winSize = Director::getInstance()->getWinSize();

	//�w�i�摜
	auto back_ground = Sprite::create("title_back.png");
	addChild(back_ground);

	//�X�N���[�����x
	float speed = 10.0f;

	//�A�N�V������o�^
	auto init = CallFunc::create([=]() {back_ground->setPosition(firstPos);	});
	auto move = MoveTo::create(speed, firstPos + winSize);

	auto seq = Sequence::create(init, move, nullptr);
	auto repeat = RepeatForever::create(seq);
	back_ground->runAction(repeat);
}

void TitleScene::startGame(int column, int row) {
	//�t�F�[�h�ŃV�[���J��
	auto newScene = GameScene::create(column, row);
	//auto trans = TransitionTurnOffTiles::create(3.0f, newScene);
	auto trans = TransitionFade::create(1.0f, newScene);
	Director::getInstance()->replaceScene(trans);
}


