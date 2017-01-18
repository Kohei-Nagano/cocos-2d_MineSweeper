#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TitleScene : public Scene {
public:
	static TitleScene* create();
	bool init();
private:
	void logo();
	void menu();
	void back();
	void tileAction(Vec2 firstPos);
	void startGame(int column, int row);
};