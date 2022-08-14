#include "AppDelegate.h"
#include "LogoLayer.h"
#include "SimpleAudioEngine.h"
#include "MainInterface.h"
USING_NS_CC;
using namespace CocosDenshion;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching() {
    // ��ʼ������
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        // ��ʼ������
        glview = GLViewImpl::createWithRect("Game", Rect(0, 0, 1000, 600));
#else
        glview = GLViewImpl::create("Game");
#endif
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    // ��������
   auto scene = LogoLayer::createScene();
   //auto scene = MainInterface::createScene();
    // ������һ������
    director->runWithScene(scene);

    return true;
}

// �����̨
void AppDelegate::applicationDidEnterBackground() {
    // ֹͣ����
    Director::getInstance()->stopAnimation();
    // ��ͣ��������
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// �ص�ǰ̨
void AppDelegate::applicationWillEnterForeground() {
    // ��ʼ����
    Director::getInstance()->startAnimation();
    // �ָ���������
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
