#include "MainInterface.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* MainInterface::createScene()
{
	Scene* scene = Scene::create();
	MainInterface* layer = MainInterface::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainInterfaceScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainInterface::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	this->main_part = MainPart::getMainPart();

	cocos2d::ParticleSystemQuad* mitter = new ParticleSystemQuad();
	mitter->initWithTotalParticles(900);
	mitter->setTexture(TextureCache::sharedTextureCache()->addImage("images/konge.png"));
	mitter->setDuration(-1);
	mitter->setGravity(Vec2(0, -100));
	mitter->setAngle(90);
	mitter->setAngleVar(360);
	mitter->setRadialAccel(50);
	mitter->setRadialAccelVar(0);
	mitter->setTangentialAccel(30);
	mitter->setTangentialAccelVar(0);
	mitter->setPosition(Vec2(1000, 600));
	mitter->setLife(4);
	mitter->setLifeVar(2);
	mitter->setStartSpin(30);
	mitter->setStartSpinVar(60);
	mitter->setEndSpin(60);
	mitter->setEndSpinVar(60);
	mitter->setStartSize(30);
	mitter->setStartSizeVar(0);
	mitter->setEndSize(20.f);
	mitter->setEndSizeVar(0);
	mitter->setEmissionRate(100);
	this->addChild(mitter,10);

	lizi();
	auto const visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("musicNew/maps/crown_over_stars.mp3", true);

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainInterface::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else {
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1);




	//-------------------------------------------------------------------------------------------------------
	auto blood_1 = cocos2d::Sprite::create("progressBar/blood_1.png");
	if (blood_1 == nullptr) {
		problemLoading("'progressBar/blood_1.png'");
	}
	else {
		blood_1->setAnchorPoint(cocos2d::Vec2(1, 1));
		float const x = visibleSize.width - 60;
		float const y = visibleSize.height - 10;
		blood_1->setPosition(Vec2(x, y));
		blood_1->setScale(0.4f);

	}
	this->addChild(blood_1, 6);

	auto hp = cocos2d::Sprite::create("progressBar/hp.png");
	if (hp == nullptr) {
		problemLoading("'progressBar/hp.png'");
	}
	else {
		hp->setAnchorPoint(cocos2d::Vec2(1, 1));
		float const x = visibleSize.width - 60;
		float const y = visibleSize.height - 30;
		hp->setPosition(Vec2(x, y));
		hp->setScale(0.4f);

	}
	this->addChild(hp, 7);

	auto coin = cocos2d::Sprite::create("resource/dynamicRes/itemicons/600001.png");
	if (coin == nullptr) {
		problemLoading("'resource/dynamicRes/itemicons/600001.png'");
	}
	else {
		coin->setAnchorPoint(cocos2d::Vec2(1, 1));
		float const x = visibleSize.width - 190;
		float const y = visibleSize.height - 60;
		coin->setPosition(Vec2(x, y));
		coin->setScale(0.4f);

	}
	this->addChild(coin, 7);

	auto avatar = cocos2d::Sprite::create("images/quality_2.png");
	CCASSERT(avatar != nullptr, "avatar not found");
	if (avatar == nullptr) {
		problemLoading("'images/quality_2.png'");
	}
	else {
		avatar->setAnchorPoint(cocos2d::Vec2(1, 1));
		float const x = visibleSize.width;
		float const y = visibleSize.height;
		avatar->setPosition(Vec2(x, y));
		avatar->setScale(0.3f);

	}
	this->addChild(avatar, 7);

	auto avatarCenter = MenuItemImage::create("resource/dynamicRes/newsingleboss/nvzhu.png", "resource/dynamicRes/newsingleboss/nvzhun.png", CC_CALLBACK_1(MainInterface::avatarCenter, this));

	if (avatarCenter == nullptr ||
		avatarCenter->getContentSize().width <= 0 ||
		avatarCenter->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_zhuangbei.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_zhuangbei.png'");
	}
	else {

		avatarCenter->setAnchorPoint(cocos2d::Vec2(1, 1));
		float const x = avatar->getPositionX() - 16 - visibleSize.width / 2;
		float const y = avatar->getPositionY() - 17 - visibleSize.height / 2;
		avatarCenter->setPosition(Vec2(x, y));
		avatarCenter->setScale(0.83f);
	}
	auto menu_activity_avatarCenter = Menu::create(avatarCenter, NULL);
	menu_activity_avatarCenter->setAnchorPoint(Vec2::ZERO);
	this->addChild(menu_activity_avatarCenter, 8);


	auto musicItem = MenuItemImage::create("images/Music1.png", "images/Music2.png", CC_CALLBACK_1(MainInterface::Music, this));

	if (musicItem == nullptr ||
		musicItem->getContentSize().width <= 0 ||
		musicItem->getContentSize().height <= 0) {
		problemLoading("'images/musicItem.png'");
	}
	else {
		float const x = origin.x + musicItem->getContentSize().width / 3 - 400 - 90;
		float const y = origin.y + musicItem->getContentSize().height / 8 - 240 - 50;
		musicItem->setPosition(Vec2(x, y));

	}

	auto Announcement = MenuItemImage::create("images/Announcement1.png", "images/Announcement2.png", CC_CALLBACK_1(MainInterface::Announcement, this));

	if (Announcement == nullptr ||
		Announcement->getContentSize().width <= 0 ||
		Announcement->getContentSize().height <= 0) {
		problemLoading("'images/Announcement.png'");
	}
	else
	{
		float const x = origin.x + Announcement->getContentSize().width / 3 - 400 - 90;
		float const y = origin.y + Announcement->getContentSize().height / 8 - 220;
		Announcement->setPosition(Vec2(x, y));

	}

	auto LeaderBoard = MenuItemImage::create("images/LeaderBoard1.png", "images/LeaderBoard2.png", CC_CALLBACK_1(MainInterface::LeaderBoard, this));

	if (LeaderBoard == nullptr ||
		LeaderBoard->getContentSize().width <= 0 ||
		LeaderBoard->getContentSize().height <= 0) {
		problemLoading("'images/LeaderBoard.png'");
	}
	else
	{
		float const x = origin.x + LeaderBoard->getContentSize().width / 3 - 8 - 400 - 90;
		float const y = origin.y + LeaderBoard->getContentSize().height / 8 + 136 - 190 - 50 - 50;
		LeaderBoard->setPosition(Vec2(x, y));

	}

	auto Commodity = MenuItemImage::create("images/Commodity1.png", "images/Commodity2.png", CC_CALLBACK_1(MainInterface::Commodity, this));

	if (Commodity == nullptr ||
		Commodity->getContentSize().width <= 0 ||
		Commodity->getContentSize().height <= 0) {
		problemLoading("'images/Commodity.png'");
	}
	else
	{
		float const x = origin.x + Commodity->getContentSize().width / 3 - 9 - 400 - 90;
		float const y = origin.y + Commodity->getContentSize().height / 8 + 176 - 190 - 50 - 50;
		Commodity->setPosition(Vec2(x, y));

	}

	auto Evalution = MenuItemImage::create("images/Evalution1.png", "images/Evalution2.png", CC_CALLBACK_1(MainInterface::Evalution, this));

	if (Evalution == nullptr ||
		Evalution->getContentSize().width <= 0 ||
		Evalution->getContentSize().height <= 0) {
		problemLoading("'images/Evalution.png'");
	}
	else
	{
		float const x = origin.x + Evalution->getContentSize().width / 3 + 12 - 400 - 90;
		float const y = origin.y + Evalution->getContentSize().height / 8 + 230 - 190 - 50 - 50;
		Evalution->setPosition(Vec2(x, y));

	}
	auto Lucky_turnable = MenuItemImage::create("images/Lucky_turnable1.png", "images/Lucky_turnable2.png", CC_CALLBACK_1(MainInterface::Lucky_turnable, this));

	if (Lucky_turnable == nullptr ||
		Lucky_turnable->getContentSize().width <= 0 ||
		Lucky_turnable->getContentSize().height <= 0) {
		problemLoading("'images/Lucky_turnable.png'");
	}
	else
	{
		float const x = origin.x + Lucky_turnable->getContentSize().width / 3 + 12 - 400 - 90;
		float const y = origin.y + Lucky_turnable->getContentSize().height / 8 + 304 - 190 - 50 - 50;
		Lucky_turnable->setPosition(Vec2(x, y));

	}
	auto Spike = MenuItemImage::create("images/Spike1.png", "images/Spike2.png", CC_CALLBACK_1(MainInterface::OnlineSpike, this));

	if (Spike == nullptr ||
		Spike->getContentSize().width <= 0 ||
		Spike->getContentSize().height <= 0) {
		problemLoading("'images/Spike.png'");
	}
	else
	{
		float const x = origin.x + Spike->getContentSize().width / 3 - 400 - 90;
		float const y = origin.y + Spike->getContentSize().height / 8 + 366 - 190 - 50 - 50;
		Spike->setPosition(Vec2(x, y));

	}
	auto Call_server = MenuItemImage::create("images/Call_server1.png", "images/Call_server2.png", CC_CALLBACK_1(MainInterface::Call_server, this));

	if (Call_server == nullptr ||
		Call_server->getContentSize().width <= 0 ||
		Call_server->getContentSize().height <= 0) {
		problemLoading("'images/Call_server.png'");
	}
	else
	{
		float const x = origin.x + Call_server->getContentSize().width / 3 - 9 - 400 - 90;
		float const y = origin.y + Call_server->getContentSize().height / 8 + 416 - 190 - 50 - 50;
		Call_server->setPosition(Vec2(x, y));

	}

	//------------------------------------------------------第二排活动------------------------------------------------------
 //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


	auto bimg_gnyg_cijihuangdao = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_gnyg_cijihuangdao.png", "resource/dynamicRes/everydayDo/bimg_gnyg_cijihuangdao1.png", CC_CALLBACK_1(MainInterface::bimg_gnyg_cijihuangdao, this));

	if (bimg_gnyg_cijihuangdao == nullptr ||
		bimg_gnyg_cijihuangdao->getContentSize().width <= 0 ||
		bimg_gnyg_cijihuangdao->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_gnyg_cijihuangdao.png' and 'resource/dynamicRes/everydayDo/bimg_gnyg_cijihuangdao1.png'");
	}
	else {

		float const x = visibleSize.width - bimg_gnyg_cijihuangdao->getContentSize().width / 2 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_gnyg_cijihuangdao->getContentSize().height / 2 - 100 - visibleSize.height / 2;
		bimg_gnyg_cijihuangdao->setPosition(Vec2(x, y));
		bimg_gnyg_cijihuangdao->setScale(0.7f);

	}

	auto bimg_zjm_huashanluenjian = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_huashanluenjian.png", "resource/dynamicRes/everydayDo/bimg_zjm_huashanluenjian1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_huashanluenjian, this));
	if (bimg_zjm_huashanluenjian == nullptr ||
		bimg_zjm_huashanluenjian->getContentSize().width <= 0 ||
		bimg_zjm_huashanluenjian->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_huashanluenjian.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_huashanluenjian1.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_huashanluenjian->getContentSize().width / 2 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_huashanluenjian->getContentSize().height / 2 - 160 - visibleSize.height / 2;
		bimg_zjm_huashanluenjian->setPosition(Vec2(x, y));
		bimg_zjm_huashanluenjian->setScale(0.7f);
	}

	auto bimg_zjm_jianghulilian = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_jianghulilian.png", "resource/dynamicRes/everydayDo/bimg_zjm_jianghulilian1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_jianghulilian, this));
	if (bimg_zjm_jianghulilian == nullptr ||
		bimg_zjm_jianghulilian->getContentSize().width <= 0 ||
		bimg_zjm_jianghulilian->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_jianghulilian.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_jianghulilian1.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_jianghulilian->getContentSize().width / 2 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_jianghulilian->getContentSize().height / 2 - 220 - visibleSize.height / 2;
		bimg_zjm_jianghulilian->setPosition(Vec2(x, y));
		bimg_zjm_jianghulilian->setScale(0.7f);
	}

	auto bimg_zjm_jinjie = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_jinjie.png", "resource/dynamicRes/everydayDo/bimg_zjm_jinjie1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_jinjie, this));

	if (bimg_zjm_jinjie == nullptr ||
		bimg_zjm_jinjie->getContentSize().width <= 0 ||
		bimg_zjm_jinjie->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_jinjie.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_jinjie1.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_jinjie->getContentSize().width / 2 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_jinjie->getContentSize().height / 2 - 280 - visibleSize.height / 2;
		bimg_zjm_jinjie->setPosition(Vec2(x, y));
		bimg_zjm_jinjie->setScale(0.7f);
	}

	auto bimg_zjm_juese = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_juese.png", "resource/dynamicRes/everydayDo/bimg_zjm_juese1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_juese, this));
	if (bimg_zjm_juese == nullptr ||
		bimg_zjm_juese->getContentSize().width <= 0 ||
		bimg_zjm_juese->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_juese.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_juese1.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_juese->getContentSize().width / 2 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_juese->getContentSize().height / 2 - 340 - visibleSize.height / 2;
		bimg_zjm_juese->setPosition(Vec2(x, y));
		bimg_zjm_juese->setScale(0.7f);
	}

	auto bimg_zjm_juezhanhuangcheng = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_juezhanhuangcheng.png", "resource/dynamicRes/everydayDo/bimg_zjm_juezhanhuangcheng1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_juezhanhuangcheng, this));
	if (bimg_zjm_juezhanhuangcheng == nullptr ||
		bimg_zjm_juezhanhuangcheng->getContentSize().width <= 0 ||
		bimg_zjm_juezhanhuangcheng->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_juezhanhuangcheng.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_juezhanhuangcheng1.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_juezhanhuangcheng->getContentSize().width / 2 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_juezhanhuangcheng->getContentSize().height / 2 - 400 - visibleSize.height / 2;
		bimg_zjm_juezhanhuangcheng->setPosition(Vec2(x, y));
		bimg_zjm_juezhanhuangcheng->setScale(0.7f);
	}

	auto bimg_zjm_liangongya = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_liangongya.png", "resource/dynamicRes/everydayDo/bimg_zjm_liangongya1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_liangongya, this));
	if (bimg_zjm_liangongya == nullptr ||
		bimg_zjm_liangongya->getContentSize().width <= 0 ||
		bimg_zjm_liangongya->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_liangongya.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_liangongya1.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_liangongya->getContentSize().width / 2 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_liangongya->getContentSize().height / 2 - 460 - visibleSize.height / 2;
		bimg_zjm_liangongya->setPosition(Vec2(x, y));
		bimg_zjm_liangongya->setScale(0.7f);
	}

	auto bimg_zjm_lingchong = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_lingchong.png", "resource/dynamicRes/everydayDo/bimg_zjm_lingchong1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_lingchong, this));
	CCASSERT(bimg_zjm_lingchong != nullptr, "bimg_zjm_lingchong not found");
	if (bimg_zjm_lingchong == nullptr ||
		bimg_zjm_lingchong->getContentSize().width <= 0 ||
		bimg_zjm_lingchong->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_lingchong.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_lingchong1.png'");
	}
	else {

		float const x = bimg_zjm_lingchong->getContentSize().width / 2 + 280 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_lingchong->getContentSize().height / 2 - visibleSize.height / 2;
		bimg_zjm_lingchong->setPosition(Vec2(x, y));
		bimg_zjm_lingchong->setScale(0.7f);
	}

	auto menu_activity = Menu::create(bimg_gnyg_cijihuangdao, bimg_zjm_huashanluenjian,
		bimg_zjm_jianghulilian, bimg_zjm_jinjie, bimg_zjm_juese, bimg_zjm_juezhanhuangcheng, bimg_zjm_liangongya, bimg_zjm_lingchong, NULL);
	menu_activity->setAnchorPoint(Vec2::ZERO);
	this->addChild(menu_activity, 3);

	auto bimg_zjm_shenbing = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_shenbing.png", "resource/dynamicRes/everydayDo/bimg_zjm_shenbing1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_shenbing, this));
	CCASSERT(bimg_zjm_shenbing != nullptr, "bimg_zjm_lingchong not found");
	if (bimg_zjm_shenbing == nullptr ||
		bimg_zjm_shenbing->getContentSize().width <= 0 ||
		bimg_zjm_shenbing->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_shenbing.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_shenbing1.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_shenbing->getContentSize().width - 20 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_shenbing->getContentSize().height / 2 - 160 - visibleSize.height / 2;
		bimg_zjm_shenbing->setPosition(Vec2(x, y));
		bimg_zjm_shenbing->setScale(0.7f);
	}

	auto bimg_zjm_shijieBOSS = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_shijieBOSS.png", "resource/dynamicRes/everydayDo/bimg_zjm_shijieBOSS1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_shijieBOSS, this));
	CCASSERT(bimg_zjm_shijieBOSS != nullptr, "bimg_zjm_lingchong not found");
	if (bimg_zjm_shijieBOSS == nullptr ||
		bimg_zjm_shijieBOSS->getContentSize().width <= 0 ||
		bimg_zjm_shijieBOSS->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_shijieBOSS.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_shijieBOSS.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_shijieBOSS->getContentSize().width - 20 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_shijieBOSS->getContentSize().height / 2 - 220 - visibleSize.height / 2;
		bimg_zjm_shijieBOSS->setPosition(Vec2(x, y));
		bimg_zjm_shijieBOSS->setScale(0.7f);
	}

	auto bimg_zjm_tianming = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_tianming.png", "resource/dynamicRes/everydayDo/bimg_zjm_tianming1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_tianming, this));
	CCASSERT(bimg_zjm_tianming != nullptr, "bimg_zjm_lingchong not found");
	if (bimg_zjm_tianming == nullptr ||
		bimg_zjm_tianming->getContentSize().width <= 0 ||
		bimg_zjm_tianming->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_tianming.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_tianming.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_tianming->getContentSize().width - 20 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_tianming->getContentSize().height / 2 - 280 - visibleSize.height / 2;
		bimg_zjm_tianming->setPosition(Vec2(x, y));
		bimg_zjm_tianming->setScale(0.7f);
	}

	auto bimg_zjm_tongtianta = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_tongtianta.png", "resource/dynamicRes/everydayDo/bimg_zjm_tongtianta1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_tongtianta, this));
	CCASSERT(bimg_zjm_tongtianta != nullptr, "bimg_zjm_lingchong not found");
	if (bimg_zjm_tongtianta == nullptr ||
		bimg_zjm_tongtianta->getContentSize().width <= 0 ||
		bimg_zjm_tongtianta->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_tongtianta.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_tongtianta1.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_tongtianta->getContentSize().width - 20 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_tongtianta->getContentSize().height / 2 - 340 - visibleSize.height / 2;
		bimg_zjm_tongtianta->setPosition(Vec2(x, y));
		bimg_zjm_tongtianta->setScale(0.7f);
	}

	auto bimg_zjm_weijiaomojiao = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_weijiaomojiao.png", "resource/dynamicRes/everydayDo/bimg_zjm_weijiaomojiao1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_weijiaomojiao, this));
	CCASSERT(bimg_zjm_weijiaomojiao != nullptr, "bimg_zjm_lingchong not found");
	if (bimg_zjm_weijiaomojiao == nullptr ||
		bimg_zjm_weijiaomojiao->getContentSize().width <= 0 ||
		bimg_zjm_weijiaomojiao->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_weijiaomojiao.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_weijiaomojiao1.png'");
	}
	else {

		float const x = visibleSize.width - bimg_zjm_weijiaomojiao->getContentSize().width - 20 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_weijiaomojiao->getContentSize().height / 2 - 400 - visibleSize.height / 2;
		bimg_zjm_weijiaomojiao->setPosition(Vec2(x, y));
		bimg_zjm_weijiaomojiao->setScale(0.7f);
	}

	auto bimg_zjm_xiakexing = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_xiakexing.png", "resource/dynamicRes/everydayDo/bimg_zjm_xiakexing1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_xiakexing, this));
	CCASSERT(bimg_zjm_xiakexing != nullptr, "bimg_zjm_lingchong not found");
	if (bimg_zjm_xiakexing == nullptr ||
		bimg_zjm_xiakexing->getContentSize().width <= 0 ||
		bimg_zjm_xiakexing->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_xiakexing.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_xiakexing.png'");
	}
	else {

		float const x = bimg_zjm_xiakexing->getContentSize().width / 2 + 220 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_xiakexing->getContentSize().height / 2 - visibleSize.height / 2;
		bimg_zjm_xiakexing->setPosition(Vec2(x, y));
		bimg_zjm_xiakexing->setScale(0.7f);
	}

	auto bimg_zjm_xinfa = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_xinfa.png", "resource/dynamicRes/everydayDo/bimg_zjm_xinfa1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_xinfa, this));
	if (bimg_zjm_xinfa == nullptr ||
		bimg_zjm_xinfa->getContentSize().width <= 0 ||
		bimg_zjm_xinfa->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_xinfa.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_xinfa.png'");
	}
	else {

		float const x = bimg_zjm_xinfa->getContentSize().width / 2 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_xinfa->getContentSize().height / 2 - visibleSize.height / 2;
		bimg_zjm_xinfa->setPosition(Vec2(x, y));
		bimg_zjm_xinfa->setScale(0.7f);
	}

	auto bimg_zjm_zhaoshi = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_zhaoshi.png", "resource/dynamicRes/everydayDo/bimg_zjm_zhaoshi1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_zhaoshi, this));

	if (bimg_zjm_zhaoshi == nullptr ||
		bimg_zjm_zhaoshi->getContentSize().width <= 0 ||
		bimg_zjm_zhaoshi->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_zhaoshi.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_zhaoshi.png'");
	}
	else {

		float const x = bimg_zjm_zhaoshi->getContentSize().width / 2 + 60 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_zhaoshi->getContentSize().height / 2 - visibleSize.height / 2;
		bimg_zjm_zhaoshi->setPosition(Vec2(x, y));
		bimg_zjm_zhaoshi->setScale(0.7f);
	}

	auto bimg_zjm_zhuangbei = MenuItemImage::create("resource/dynamicRes/everydayDo/bimg_zjm_zhuangbei.png", "resource/dynamicRes/everydayDo/bimg_zjm_zhuangbei1.png", CC_CALLBACK_1(MainInterface::bimg_zjm_zhuangbei, this));

	if (bimg_zjm_zhuangbei == nullptr ||
		bimg_zjm_zhuangbei->getContentSize().width <= 0 ||
		bimg_zjm_zhuangbei->getContentSize().height <= 0) {
		problemLoading("'resource/dynamicRes/everydayDo/bimg_zjm_zhuangbei.png' and 'resource/dynamicRes/everydayDo/bimg_zjm_zhuangbei.png'");
	}
	else {

		float const x = bimg_zjm_zhuangbei->getContentSize().width / 2 + 120 - visibleSize.width / 2;
		float const y = visibleSize.height - bimg_zjm_zhuangbei->getContentSize().height / 2 - visibleSize.height / 2;
		bimg_zjm_zhuangbei->setPosition(Vec2(x, y));
		bimg_zjm_zhuangbei->setScale(0.7f);
	}
	auto menu_activity_ = Menu::create(bimg_zjm_shenbing, bimg_zjm_shijieBOSS, bimg_zjm_tianming,
		bimg_zjm_tongtianta, bimg_zjm_weijiaomojiao, bimg_zjm_xiakexing, bimg_zjm_xinfa, bimg_zjm_zhaoshi, bimg_zjm_zhuangbei, NULL);
	menu_activity_->setAnchorPoint(Vec2::ZERO);
	this->addChild(menu_activity_, 3);
	//---------------------------------------------------------------------------------------
	//开始
	auto fightItem = MenuItemImage::create("images/Start1.png", "images/Start2.png", CC_CALLBACK_1(MainInterface::enterFight, this));
	fightItem->setScale(0.2);
	if (fightItem == nullptr ||
		fightItem->getContentSize().width <= 0 ||
		fightItem->getContentSize().height <= 0) {
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else {
		fightItem->setPosition(Vec2(0, 0));
	}
	//
// create menu, it's an autorelease object
	auto menuStart = Menu::create(musicItem, Announcement, LeaderBoard, Commodity, Evalution, Lucky_turnable, Spike, Call_server, fightItem, NULL);
	this->addChild(menuStart, 2);


	//---------------------------------------------------------------------------------------------------------------------------
	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Endless Adventure", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr) {
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else {
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));
		label->setScale(1.5f);
		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add "MainInterface" splash screen"
	auto sprite = Sprite::create("resource/dynamicRes/newsingleboss/elite/img_bg01.png");
	if (sprite == nullptr) {
		problemLoading("'MainInterface.png'");
	}
	else {
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}

	this->schedule(schedule_selector(MainInterface::FlushCoin));

	return true;
}
Vector<SpriteFrame*> MainInterface::getAnimation(const char* format, int count) {

	auto spriteFrameCach = SpriteFrameCache::getInstance();

	cocos2d::Vector<cocos2d::SpriteFrame*> spriteFrames;
	char str[100] = {};
	for (size_t i = 0; i < count; i++)
	{
		sprintf(str, format, i);
		spriteFrames.pushBack(spriteFrameCach->getSpriteFrameByName(str));
	}
	return spriteFrames;


}

void MainInterface::enterFight(Ref* pSender)
{
	//this->removeAllChildren();
	this->unschedule(schedule_selector(MainInterface::FlushCoin));
	Director::getInstance()->replaceScene(MenuLayer::createScene());
}

void MainInterface::Music(Ref* pSender) {

	this->music = this->music + 1;
	if (music % 2 == 1)
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("musicNew/maps/crown_over_stars.mp3", true);
	else {

		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}

}

void MainInterface::Announcement(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::LeaderBoard(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::Commodity(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::Evalution(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::Lucky_turnable(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::OnlineSpike(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::Call_server(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::menuCloseCallback(Ref* pSender) {
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MainInterface::bimg_gnyg_cijihuangdao(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
    tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren,6);
}

void MainInterface::bimg_zjm_huashanluenjian(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_jianghulilian(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_jinjie(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_juese(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_juezhanhuangcheng(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_liangongya(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_lingchong(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_shenbing(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_shijieBOSS(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_tianming(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_tongtianta(Ref* pSender) {

	Director::getInstance()->replaceScene(Mall::createScene());
}

void MainInterface::bimg_zjm_weijiaomojiao(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_xiakexing(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_xinfa(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_zhaoshi(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();

	//提示
	tishi = Sprite::create("images/tishiN.png");
	CCASSERT(tishi != nullptr, "images/tishiN.png");
	tishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tishi->setScale(0.56f);
	this->addChild(tishi, 5);

	auto closeItem = MenuItemImage::create(
		"images/queren1.png",
		"images/queren2.png",
		CC_CALLBACK_1(MainInterface::CloseTishi, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		closeItem->setPosition(Vec2(0, -210));
		closeItem->setScale(0.29f);
	}
	Menu* menu_queren = Menu::create(closeItem, NULL);
	tishi->addChild(menu_queren, 6);
}

void MainInterface::bimg_zjm_zhuangbei(Ref* pSender) {
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true); //阻止向下传递
	auto const visibleSize = Director::getInstance()->getVisibleSize();
	zhuangbei = Layer::create();
	this->addChild(zhuangbei, 10);
	Sprite* back = Sprite::create("images/back.png");
	back->setPosition(Vec2(back->getContentSize().width / 2, back->getContentSize().height / 2));
	back->setScale(1, 1.17f);
	zhuangbei->addChild(back);

	auto closeItem = MenuItemImage::create(
		"images/delete.png",
		"images/delete.png",
		CC_CALLBACK_1(MainInterface::Closezhuangbei, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		float const x = back->getPosition().x - visibleSize.width / 2 + back->getContentSize().width / 2 - 61;
		float const y = back->getPosition().y - 19;
		closeItem->setPosition(Vec2(x, y));
		closeItem->setScale(1, 1.17f);
	}
	Menu* menu = Menu::create(closeItem, NULL);
	zhuangbei->addChild(menu);
	if (this->main_part->getEquip().size() != 0) {
		Sprite* sp;
		int rows = 0;
		int columns = 0;
		for (std::string item : this->main_part->getEquip()) {
			sp = Sprite::create(item.c_str());
			sp->setPosition(Vec2(90 + rows, 454 + columns));
			sp->setScale(0.65f);
			zhuangbei->addChild(sp);
			rows += 75;
			if (rows / 75 == 5) {
				rows = 0;
				columns -= 94;
			}
		}
	}
	auto listenerr = EventListenerTouchOneByOne::create();
	listenerr->setSwallowTouches(true); //阻止向下传递
}
void MainInterface::avatarCenter(Ref* pSender) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();
	Dashboard = Layer::create();
	this->addChild(Dashboard, 10);
	Sprite* back = Sprite::create("images/Dashboard1.png");
	//back->setPosition(Vec2(back->getContentSize().width / 2, back->getContentSize().height / 2));
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	back->setScale(0.8f);
	Dashboard->addChild(back);

	auto closeItem = MenuItemImage::create(
		"images/delete.png",
		"images/delete.png",
		CC_CALLBACK_1(MainInterface::CloseDashboard, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'images/delete.png' and 'images/delete.png'");
	}
	else {
		float const x = back->getPosition().x - visibleSize.width / 2 + back->getContentSize().width / 2 - 130;
		float const y = back->getPosition().y - 60;
		closeItem->setPosition(Vec2(x, y));
		closeItem->setScale(1, 1.17f);
	}
	Menu* menu = Menu::create(closeItem, NULL);
	Dashboard->addChild(menu);
	Sprite* shuxing = Sprite::create("images/shuxing.png");
	shuxing->setPosition(Vec2(197, 290));
	//shuxing->setRotation(90);
	shuxing->setScale(0.25f, 0.22f);
	Dashboard->addChild(shuxing);

	//攻击
	char st4[256];
	_itoa(this->main_part->getEnergy(), st4, 10);
	std::string str4 = st4;
	auto Energy = Label::createWithTTF(str4.c_str(), "fonts/arial.ttf", 24);
	Energy->setPosition(Vec2(shuxing->getPosition().x, shuxing->getPosition().y + 150));
	Energy->setScale(0.9f);
	Dashboard->addChild(Energy, 10);

	//防御
	char st1[256];
	_itoa(this->main_part->getDefense(), st1, 10);
	std::string str1 = st1;
	auto deff = Label::createWithTTF(str1.c_str(), "fonts/arial.ttf", 24);
	deff->setPosition(Vec2(shuxing->getPosition().x, shuxing->getPosition().y + 105));
	deff->setScale(0.9f);
	Dashboard->addChild(deff, 10);

	//金币
	char st2[256];
	_itoa(this->main_part->getCoinNum(), st2, 10);
	std::string str2 = st2;
	auto CoinNum = Label::createWithTTF(str2.c_str(), "fonts/arial.ttf", 24);
	CoinNum->setPosition(Vec2(shuxing->getPosition().x, shuxing->getPosition().y + 55));
	CoinNum->setScale(0.9f);
	Dashboard->addChild(CoinNum, 10);

	//等级
	char st[256];
	_itoa(this->main_part->getLevel(), st, 10);
	std::string str = st;
	auto level = Label::createWithTTF(str.c_str(), "fonts/arial.ttf", 24);
	level->setPosition(Vec2(shuxing->getPosition().x , shuxing->getPosition().y + 10));
	level->setScale(0.9f);
	Dashboard->addChild(level, 10);

	//经验值
	char st3[256];
	_itoa(this->main_part->getExp(), st3, 10);
	std::string str3= st3;
	auto Exp = Label::createWithTTF(str3.c_str(), "fonts/arial.ttf", 24);
	Exp->setPosition(Vec2(shuxing->getPosition().x, shuxing->getPosition().y - 38));
	Exp->setScale(0.9f);
	Dashboard->addChild(Exp, 10);

	//钻石
	char st5[256];
	_itoa(this->main_part->getPrice(), st5, 10);
	std::string str5 = st5;
	auto Price = Label::createWithTTF(str5.c_str(), "fonts/arial.ttf", 24);
	Price->setPosition(Vec2(shuxing->getPosition().x, shuxing->getPosition().y - 83));
	Price->setScale(0.9f);
	Dashboard->addChild(Price, 10);

	//人物
	Sprite* zhujue = Sprite::create("resource/dynamicRes/vsview/zd_kc_js2.png");
	zhujue->setPosition(Vec2(Dashboard->getPosition().x / 2 + visibleSize.width / 2 - 80 , Dashboard->getPosition().y / 2 + visibleSize.height / 2 - 45));
	zhujue->setScale(0.45f);
	Dashboard->addChild(zhujue,2);

	//称号
	Sprite* eff = Sprite::create("images/images/CCML_01.png");
	eff->setPosition(Vec2(zhujue->getPosition().x / 2 + 200, zhujue->getPosition().y + 15 + 200));
	eff->setScale(0.45f);
	Animation* animationMouse = Animation::create();
	char mapName[44] = { 0 };
	for (int i = 1; i < 10; i++) {
		sprintf(mapName, "images/images/CCML_0%d.png", i);
		animationMouse->addSpriteFrameWithFileName(mapName);
	}
	animationMouse->setDelayPerUnit(0.23f);
	eff->runAction(RepeatForever::create(Animate::create(animationMouse)));
	Dashboard->addChild(eff);

	//特效底
	Sprite* JSZT_L = Sprite::create("images/images/JSZT_L_00.png");
	CCASSERT(JSZT_L != nullptr,"images/images/JSZT_L_00.png not found");
	JSZT_L->setPosition(Vec2(zhujue->getPosition().x / 2 + 200, zhujue->getPosition().y - 123));
	JSZT_L->setScale(0.8f);
	Animation* animationMousee = Animation::create();
	char mapNamee[44] = { 0 };
	for (int i = 0; i < 10; i++) {
		sprintf(mapNamee, "images/images/JSZT_L_0%d.png", i);
		animationMousee->addSpriteFrameWithFileName(mapNamee);
	}
	animationMousee->setDelayPerUnit(0.21f);
	JSZT_L->runAction(RepeatForever::create(Animate::create(animationMousee)));
	Dashboard->addChild(JSZT_L,1); 

	//英雄之路
	Sprite * road = Sprite::create("resource/dynamicRes/heroroad/item/rumeng.png");
	CCASSERT(road != nullptr, "resource/dynamicRes/heroroad/item/rumeng.png not found");
	road->setPosition(Vec2(zhujue->getPosition().x / 2 + 550, zhujue->getPosition().y + 212));
	road->setScale(0.8f);
	Dashboard->addChild(road, 1);

	//种族
	Sprite* fate = Sprite::create("resource/dynamicRes/fate/sheshou.png");
	CCASSERT(fate != nullptr, "resource/dynamicRes/heroroad/item/rumeng.png not found");
	fate->setPosition(Vec2(zhujue->getPosition().x / 2 + 550, zhujue->getPosition().y + 150));
	fate->setScale(0.13f);
	Dashboard->addChild(fate, 1);

	//段位
	Sprite* duanwei = Sprite::create("resource/dynamicRes/ladder/dan/img_jzhc_d1.png");
	CCASSERT(duanwei != nullptr, "resource/dynamicRes/heroroad/item/rumeng.png not found");
	duanwei->setPosition(Vec2(zhujue->getPosition().x / 2 + 550, zhujue->getPosition().y + 70));
	duanwei->setScale(0.3f);
	Dashboard->addChild(duanwei, 1);

	//宠物
	Sprite* pet = Sprite::create("resource/dynamicRes/pet/petHead/1.png");
	CCASSERT(pet != nullptr, "resource/dynamicRes/heroroad/item/rumeng.png not found");
	pet->setPosition(Vec2(zhujue->getPosition().x / 2 + 550, zhujue->getPosition().y ));
	pet->setScale(0.56f);
	Dashboard->addChild(pet, 1);
}
void MainInterface::Closezhuangbei(Ref* pSender) {

	this->removeChild(zhuangbei);
}
void MainInterface::CloseDashboard(Ref* pSender) {

	this->removeChild(Dashboard);
}
void MainInterface::FlushCoin(float dt) {
	auto const visibleSize = Director::getInstance()->getVisibleSize();
	char st[256];
	_itoa(this->main_part->getCoinNum(), st, 10);
	std::string str = st;
	auto coinNum = Label::createWithTTF(str.c_str(), "fonts/arial.ttf", 24);
	if (coinNum == nullptr) {
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else {
		// position the label on the center of the screen
		float const x = visibleSize.width - 150;
		float const y = visibleSize.height - 76;
		coinNum->setPosition(Vec2(x, y));
		coinNum->setScale(0.9f);
		// add the label as a child to this layer
		this->addChild(coinNum, 1);
	}

}

void MainInterface::CloseTishi(Ref* pSender) {
	this->removeChild(tishi);
}

void MainInterface::lizi() {
	cocos2d::ParticleSystemQuad* mitter = new ParticleSystemQuad();
	mitter->initWithTotalParticles(900);
	mitter->setTexture(TextureCache::sharedTextureCache()->addImage("images/xingchen.png"));
	mitter->setDuration(-1);
	mitter->setGravity(Vec2(0, -100));
	mitter->setAngle(90);
	mitter->setRadialAccel(50);
	mitter->setRadialAccelVar(0);
	mitter->setTangentialAccel(30);
	mitter->setTangentialAccelVar(0);
	mitter->setPosition(Vec2(500, 600));
	mitter->setLife(4);
	mitter->setLifeVar(2);
	mitter->setStartSpin(30);
	mitter->setStartSpinVar(60);
	mitter->setEndSpin(60);
	mitter->setEndSpinVar(60);
	mitter->setStartSize(30);
	mitter->setStartSizeVar(0);
	mitter->setEndSize(20.f);
	mitter->setEndSizeVar(0);
	mitter->setEmissionRate(100);
	this->addChild(mitter,10);
}
