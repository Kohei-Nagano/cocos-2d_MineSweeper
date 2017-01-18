#include "TileManager.h"

#include "TileBase.h"
#include <algorithm>

TileManager * TileManager::create() {
	auto tileMgr = new TileManager();

	tileMgr->init();
	tileMgr->autorelease();

	return tileMgr;
}

//初期化
bool TileManager::init()
{
	//配列の初期化
	initTiles();
	//爆弾の設置
	setMines();
	//タイルの生成
	setTiles();

	once_ = false;
	return true;
}

void TileManager::initTiles()
{
	for (int x = 0; x < TILE_WIDTH + 2; x++) {
		for (int y = 0; y < TILE_HEIGHT + 2; y++) {
			mine_[x][y] = false;	// 爆弾無し
			num_[x][y] = 0;			// 周りの爆弾数は0
		}
	}
}

// 爆弾を配置
void TileManager::setMines()
{
	for (int i = 0; i < MINE_NUM; ++i) {
		int x, y;
		do {
			x = rand() % TILE_WIDTH + 1;
			y = rand() % TILE_HEIGHT + 1;
		} while (mine_[x][y]);		// 既に爆弾が置いてある
		mine_[x][y] = true;			//  爆弾配置

									//周囲の爆弾数	
		num_[x][y - 1] += 1;
		num_[x][y + 1] += 1;
		num_[x + 1][y] += 1;
		num_[x + 1][y + 1] += 1;
		num_[x + 1][y - 1] += 1;
		num_[x - 1][y] += 1;
		num_[x - 1][y + 1] += 1;
		num_[x - 1][y - 1] += 1;
	}
}

void TileManager::setTiles() {
	auto winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Vec2(winSize) / 2 - Vec2(BUTTON_SIZE, BUTTON_SIZE) / 2 * 8.0f;

	searchAll([=](int x, int y) {

		Vec2 position = origin + Vec2(x - 1, y - 1) * BUTTON_SIZE;

		auto tile = TileBase::create(mine_[x][y], num_[x][y]);
		tile->setTag(x * 10 + y);
		tile->setPosition(position);
		addChild(tile);

	});
}

void TileManager::openAll() {
	if (once_)return;

	searchAll([=](int x, int y) {

		auto button = (TileBase*)getChildByTag(x * 10 + y);
		button->openTile();

	});

}

void TileManager::clearCheck() {
	for (int x = 1; x <= TILE_WIDTH; x++) {
		for (int y = 1; y <= TILE_HEIGHT; y++) {
			auto button = (TileBase*)getChildByTag(x * 10 + y);
			if (!button->clearJudge()) return;
		}
	}

	if (once_)return;	

	auto winSize = Director::getInstance()->getWinSize();

	auto clear = Sprite::create("clear.png");
	clear->setScale(winSize.height / clear->getContentSize().height * 0.25f);
	clear->setPosition(Vec2(winSize.width / 2, winSize.height * 0.85f));
	addChild(clear);

	once_ = true;
}

void TileManager::failureCheck()
{
	if (once_)return;

	auto winSize = Director::getInstance()->getWinSize();

	auto clear = Sprite::create("failed.png");
	clear->setScale(winSize.height / clear->getContentSize().height * 0.25f);
	clear->setPosition(Vec2(winSize.width / 2, winSize.height * 0.85f));
	addChild(clear);

	once_ = true;

}


//全てのタイルを検索
void TileManager::searchAll(std::function<void(int, int)> func) {
	for (int x = 1; x <= TILE_WIDTH; x++) {
		for (int y = 1; y <= TILE_HEIGHT; y++) {
			func(x, y);
		}
	}
}
