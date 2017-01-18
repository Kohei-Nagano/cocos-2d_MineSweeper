#pragma once

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene {
public:
	static GameScene* create(int column, int row);
	bool init(int column, int row);
private:
	void back();
	void mineNum();
	void menu();
	void reset();
	void backToTitle();
};