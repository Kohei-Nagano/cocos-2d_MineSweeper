#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TileManager : public Node {
public:
	static TileManager* create();
	bool init();

	//初期化
	void initTiles();

	// 爆弾を配置
	void setMines();
	void setTiles();
	void openAll();
	void clearCheck();
	void failureCheck();
	void searchAll(std::function<void(int, int)> func);
private:
	static const int MINE_NUM = 10;
	static const int TILE_WIDTH = 9;
	static const int TILE_HEIGHT = 9;

	bool mine_[TILE_WIDTH + 2][TILE_HEIGHT + 2];	// 爆弾があるかどうか
	int  num_[TILE_WIDTH + 2][TILE_HEIGHT + 2];		// 0-8: 周りの爆弾の数

	bool once_;
};