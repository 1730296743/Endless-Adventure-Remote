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
    // 初始化导演
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        // 初始化窗口
        glview = GLViewImpl::createWithRect("Game", Rect(0, 0, 1000, 600));
#else
        glview = GLViewImpl::create("Game");
#endif
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    // 创建场景
   auto scene = LogoLayer::createScene();
   //auto scene = MainInterface::createScene();
    // 启动第一个场景
    director->runWithScene(scene);

    return true;
}

// 进入后台
void AppDelegate::applicationDidEnterBackground() {
    // 停止动画
    Director::getInstance()->stopAnimation();
    // 暂停背景音乐
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// 回到前台
void AppDelegate::applicationWillEnterForeground() {
    // 开始动画
    Director::getInstance()->startAnimation();
    // 恢复背景音乐
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
