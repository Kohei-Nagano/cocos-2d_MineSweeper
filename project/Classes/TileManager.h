#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TileManager : public Node {
public:
	static TileManager* create();
	bool init();

	//������
	void initTiles();

	// ���e��z�u
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

	bool mine_[TILE_WIDTH + 2][TILE_HEIGHT + 2];	// ���e�����邩�ǂ���
	int  num_[TILE_WIDTH + 2][TILE_HEIGHT + 2];		// 0-8: ����̔��e�̐�

	bool once_;
};