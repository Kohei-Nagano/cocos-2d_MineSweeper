#pragma once

#include "cocos2d.h"

USING_NS_CC;

static const int BUTTON_SIZE = 96;

class TileBase : public Node {
public:
	static TileBase* create(bool mine, int num);
	bool init(bool mine, int num);
	void setTile();
	void setBlank();
	void setMine();
	void setNum(int num);
	bool onTouchBegan(Touch* touch, Event* e);
	void openTile();
	void openOther(int x, int y);
	bool clearJudge();
private:
	Sprite* sprite_;
	bool open_; //���łɊJ���Ă��邩�ǂ���
	bool mine_;	// ���e�����邩�ǂ���
	int  num_;	// 0-8: ����̔��e�̐�
};