#pragma once
#include "LoadingScene.h"
#include "AudioEngine.h"
using namespace cocos2d;

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	return true;
}
void LoadingScene::onEnter()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	//添加游戏启动画面
	auto splashBg = Sprite::create("splash.png");
	splashBg->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2);
	this->addChild(splashBg);

	//auto logo = Label::createWithTTF("by Yuemei", "Arial", 20);
	//logo->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2 - 200);
	//logo->setColor(Color3B(100, 200, 100));
	//this->addChild(logo);

	//Director调用异步加载纹理进TextureCache
	Director::getInstance()->getTextureCache()->addImageAsync("game.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}
//该函数用于将游戏中需要用到的资源（sprite，animation，audio等）预加载，提升游戏性能？
void LoadingScene::loadingCallBack(Texture2D* texture)
{
	//读取game.plist属性文件，将需要的sprite纹理预加载进缓存中，用texture标识
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist", texture);

	//从缓存中取出birdAnimation需要的每一帧并创建之，其中所需的每一帧都以经过上方代码存入SpriteFrameCache（singleton）
	auto birdAnimation = Animation::create();
	birdAnimation->setDelayPerUnit(0.4f);
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird1.png"));
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird2.png"));
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird3.png"));
	AnimationCache::getInstance()->addAnimation(birdAnimation, "birdAnimation");//将做好的birdAnimation存入缓存中备用

	//将游戏需要的音效预加载到AudioEngine
	AudioEngine::preload("die.mp3");
	AudioEngine::preload("hit.mp3");
	AudioEngine::preload("point.mp3");
	AudioEngine::preload("swooshing.mp3");
	AudioEngine::preload("wing.mp3");

	//loading画面显示完并且preload动作完成后，淡入淡出至游戏主场景gameScene
	//auto gameScene = GameScene::createScene();
	//auto transitionScene = TransitionFade::create(gameScene);
	//Director::getInstance()->replaceScene(transitionScene);
}