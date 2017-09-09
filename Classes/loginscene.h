#ifndef __LOGINSCENE_H__
#define __LOGINSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include "TextEditWithCursor.h"
using namespace std;
USING_NS_CC;
using namespace cocos2d::ui;
class LoginScene : public Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoginScene);
	LoginScene();
	~LoginScene();
private:
	TextEditWithCursor* passwordTf;
	TextEditWithCursor* usernameTf;//输入框
	void loginEvent(Ref*, cocos2d::ui::TouchEventType type);
	void aboutEvent(Ref*, cocos2d::ui::TouchEventType type);
	void registerEvent(Ref*, cocos2d::ui::TouchEventType type);//按钮响应事件
	std::string username;
	std::string password;
	std::string getUserName();
	std::string getPassword();//获取用户信息
	CC_SYNTHESIZE_RETAIN(Button* ,loginBtn,LoginButton);//各种控件。。。
	CC_SYNTHESIZE_RETAIN(Button*, aboutBtn, AboutButton);
	CC_SYNTHESIZE_RETAIN(Button*, registerBtn, RegisterButton);
	CC_SYNTHESIZE_RETAIN(Sprite*, loginBackGround, loginBackGround);
	CC_SYNTHESIZE_RETAIN(Label*, gameName, GameName);
	CC_SYNTHESIZE_RETAIN(Layer*, loginLayer, LoginLayer);
	CC_SYNTHESIZE_RETAIN(Sprite*, loginlayerSprite, LoginlayerSprite);
};
#endif
