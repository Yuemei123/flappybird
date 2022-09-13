#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class LoadingScene :public Scene
{
public:
	virtual bool init();
	void onEnter();
	CREATE_FUNC(LoadingScene);
private:
	void loadingCallBack(Texture2D* texture);
};