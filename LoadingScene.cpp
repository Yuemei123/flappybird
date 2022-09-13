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

	//�����Ϸ��������
	auto splashBg = Sprite::create("splash.png");
	splashBg->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2);
	this->addChild(splashBg);

	//auto logo = Label::createWithTTF("by Yuemei", "Arial", 20);
	//logo->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2 - 200);
	//logo->setColor(Color3B(100, 200, 100));
	//this->addChild(logo);

	//Director�����첽���������TextureCache
	Director::getInstance()->getTextureCache()->addImageAsync("game.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}
//�ú������ڽ���Ϸ����Ҫ�õ�����Դ��sprite��animation��audio�ȣ�Ԥ���أ�������Ϸ���ܣ�
void LoadingScene::loadingCallBack(Texture2D* texture)
{
	//��ȡgame.plist�����ļ�������Ҫ��sprite����Ԥ���ؽ������У���texture��ʶ
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist", texture);

	//�ӻ�����ȡ��birdAnimation��Ҫ��ÿһ֡������֮�����������ÿһ֡���Ծ����Ϸ��������SpriteFrameCache��singleton��
	auto birdAnimation = Animation::create();
	birdAnimation->setDelayPerUnit(0.4f);
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird1.png"));
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird2.png"));
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird3.png"));
	AnimationCache::getInstance()->addAnimation(birdAnimation, "birdAnimation");//�����õ�birdAnimation���뻺���б���

	//����Ϸ��Ҫ����ЧԤ���ص�AudioEngine
	AudioEngine::preload("die.mp3");
	AudioEngine::preload("hit.mp3");
	AudioEngine::preload("point.mp3");
	AudioEngine::preload("swooshing.mp3");
	AudioEngine::preload("wing.mp3");

	//loading������ʾ�겢��preload������ɺ󣬵��뵭������Ϸ������gameScene
	//auto gameScene = GameScene::createScene();
	//auto transitionScene = TransitionFade::create(gameScene);
	//Director::getInstance()->replaceScene(transitionScene);
}