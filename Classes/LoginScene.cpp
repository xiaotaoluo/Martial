#include "LoginScene.h"
#include "ui/CocosGUI.h"
#include "PopupWindow.h"
#include "TextEditWithCursor.h"
USING_NS_CC;
using namespace cocos2d::ui;

PopupWindow* pw ;
LoginScene::LoginScene()
{

}

LoginScene::~LoginScene()
{
}

bool LoginScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto winsSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//通过加载XML使用中文
	auto *chnStrings = Dictionary::createWithContentsOfFile("CHN_String.xml");
	const char *contentText = ((String*)chnStrings->objectForKey("contenText"))->getCString();
	const char*login = ((String*)chnStrings->objectForKey("Login"))->getCString();
	const char* account = ((String*)chnStrings->objectForKey("Account"))->getCString();
	const char* password = ((String*)chnStrings->objectForKey("Password"))->getCString();
	const char *titleText = "ABOUT";


	//登录界面背景
	loginBackGround = Sprite::create("loginbackground.jpg");
	loginBackGround->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 ));
	this->addChild(loginBackGround, 0);


	//登录选项层
	loginLayer = Layer::create();
	loginlayerSprite = Sprite::create("loginlayer.png");
	loginlayerSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 70);
	loginLayer->addChild(loginlayerSprite, 0);

	//游戏名字
	gameName = Label::createWithTTF("Martial", "fonts/Paint Boy.ttf", 26);
	gameName->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + 3*visibleSize.height/4-10));
	loginLayer->addChild(gameName, 1);

	//输入框
	passwordTf = TextEditWithCursor::create();
	passwordTf->ignoreAnchorPointForPosition(false);
	passwordTf->setAnchorPoint(ccp(0.5,0.5));
	passwordTf->setPosition(visibleSize.width / 2, visibleSize.height / 2+70);
	passwordTf->setTextEditPasswordEnabled(true);
	passwordTf->setTextEditPlaceHolder(password);
	loginLayer->addChild(passwordTf,1);

	usernameTf = TextEditWithCursor::create();
	usernameTf->ignoreAnchorPointForPosition(false);
	usernameTf->setAnchorPoint(ccp(0.5, 0.5));
	usernameTf->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 150);
	usernameTf->setTextEditPlaceHolder(account);
	loginLayer->addChild(usernameTf, 1);
	
	

	//弹窗
	pw = PopupWindow::getInstance();
	//pw->setWindowSize(480, 360);  //自定义弹窗大小，默认生成自适应尺寸
	pw->setWindowTitle(titleText, "fonts/Dominican-Regular.ttf");
	//pw->setContentText(contentText, "隶书", 22);//通过系统字体创建标题
	pw->setContentTextWithTTF(contentText, "fonts/Qingniaoguying.ttf", 22);
	pw->setWindowBackGround("about_bg.png");
	pw->addMenuButton("buttonnobg.png", "buttonnobg.png", "OK", "fonts/Dominican-Regular.ttf");
	pw->addButton("buttonnobg.png","cacel", "fonts/Dominican-Regular.ttf");
	pw->addButton("buttonnobg.png", "more", "fonts/Dominican-Regular.ttf");
	
	this->addChild(pw, 2);
	pw->setVisible(false);

	//登录按钮
	loginBtn = Button::create("loginbutton.png");
	loginBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-30));
	loginBtn->setTitleText("Login");
	//loginBtn->setTitleFontName("fonts/ALTEA.ttf");//可通过字体文件和系统字体设置
	loginBtn->setTitleFontSize(16);
	loginBtn->addTouchEventListener(this, toucheventselector(LoginScene::loginEvent));
	loginLayer->addChild(loginBtn,1);

	//关于
	aboutBtn = Button::create("buttonnobg.png");
	aboutBtn->setPosition(Vec2(visibleSize.width / 2-100, visibleSize.height / 2 - 150));
	aboutBtn->setTitleText("About");
	aboutBtn->setTitleFontSize(14);
	aboutBtn->addTouchEventListener(this, toucheventselector(LoginScene::aboutEvent));
	loginLayer->addChild(aboutBtn,1);

	//注册
	registerBtn = Button::create("buttonnobg.png");
	registerBtn->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 - 150));
	registerBtn->setTitleText("Register");
	registerBtn->setTitleFontSize(14);
	registerBtn->addTouchEventListener(this, toucheventselector(LoginScene::registerEvent));
	loginLayer->addChild(registerBtn, 1);

	this->addChild(loginLayer);
	return true;
}

Scene* LoginScene::createScene() {
	return LoginScene::create();
}

void LoginScene::loginEvent(Ref*, cocos2d::ui::TouchEventType type) {
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_ENDED:	
		username = usernameTf->getTextEditString();
		password = passwordTf->getTextEditString();
		const char* a = password.c_str();
		log(a);
		break;
	}
}

void LoginScene::aboutEvent(Ref *, cocos2d::ui::TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_ENDED:
		pw->setVisible(true);
		Action* popupAction = Sequence::create(
			RotateTo::create(0.08, 0.05),
			ScaleTo::create(0.05, 0.98),
			RotateTo::create(0.08, 0.99),
			ScaleTo::create(0.05, 1),
			RotateTo::create(0.08, 0),
			NULL);
		pw->runAction(popupAction);
		break;
	}
}

void LoginScene::registerEvent(Ref *, cocos2d::ui::TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_ENDED:
		break;
	}
}

std::string LoginScene::getUserName()
{
	return username;
}

std::string LoginScene::getPassword()
{
	return password;
}

