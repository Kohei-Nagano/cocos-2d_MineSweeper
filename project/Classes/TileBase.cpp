#include "TileBase.h"
#include "TileManager.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

TileBase* TileBase::create(bool mine, int num) {
	auto tileButton = new TileBase();

	tileButton->init(mine, num);
	tileButton->autorelease();

	return tileButton;
}

bool TileBase::init(bool mine, int num) {
	Node::init();

	open_ = false;
	mine_ = mine;	//地雷の有無
	num_ = num;		//周囲の地雷数

	setTile();		//初期のマス	

	//タッチ時のイベント登録
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* e) {return onTouchBegan(touch, e); };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//初期画像を設定
void TileBase::setTile() {
	setContentSize(Size(BUTTON_SIZE, BUTTON_SIZE));
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	sprite_ = Sprite::create("tile.png");
	sprite_->setScale(BUTTON_SIZE / sprite_->getContentSize().width);
	sprite_->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite_->setPosition(Vec2(BUTTON_SIZE, BUTTON_SIZE) / 2);
	addChild(sprite_);

	setCascadeColorEnabled(true);
}

void TileBase::setBlank() {
	sprite_->setColor(Color3B(200, 200, 200));

	int x = getTag() / 10;
	int y = getTag() % 10;

	openOther(x, y + 1);
	openOther(x, y - 1);
	openOther(x + 1, y);
	openOther(x + 1, y + 1);
	openOther(x + 1, y - 1);
	openOther(x - 1, y);
	openOther(x - 1, y + 1);
	openOther(x - 1, y - 1);
}

//画像を爆弾に変更
void TileBase::setMine() {
	sprite_->setTexture("mine.png");
	sprite_->setScale(BUTTON_SIZE / sprite_->getContentSize().width);
	sprite_->setColor(Color3B(200, 200, 200));

	//SimpleAudioEngine::getInstance()->preloadEffect("mine.mp3");

	auto mgr = (TileManager*)getParent();
	mgr->failureCheck();
	mgr->openAll();

	setCascadeColorEnabled(true);
}

//画像を番号に変更
void TileBase::setNum(int num) {
	auto label = Label::create(StringUtils::toString(num_), "misaki_mincho.ttf", BUTTON_SIZE / 2);
	label->setColor(Color3B::BLACK);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(Vec2(BUTTON_SIZE, BUTTON_SIZE) / 2);
	addChild(label);

	auto mgr = (TileManager*)getParent();
	mgr->clearCheck();
	setCascadeColorEnabled(true);
}

//タッチイベント
bool TileBase::onTouchBegan(Touch * touch, Event * e)
{
	//タッチ開始時の処理を登録する
	if (getBoundingBox().containsPoint(touch->getLocation())) {
		openTile();
		//SimpleAudioEngine::getInstance()->preloadEffect("click.mp3");
		return true;
	}
	return false;
}

//タッチ時の処理
void TileBase::openTile() {
	if (open_)return;

	open_ = !open_;

	if (mine_)	setMine();
	else if (num_ == 0) setBlank();
	else setNum(num_);
}

void TileBase::openOther(int x, int y)
{
	if (x == 0 || y == 0 || x == 10 || y == 10)return;

	auto button = (TileBase*)getParent()->getChildByTag(x * 10 + y);

	button->openTile();
}

bool TileBase::clearJudge() {
	return open_ || mine_;
}

